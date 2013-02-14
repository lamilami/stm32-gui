/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCDPage1bpp.C
Purpose     : Driver for page-organized LCD-controllers with 1bpp
----------------------------------------------------------------------   
Version-Date---Author-Explanation                                        
----------------------------------------------------------------------   
1.00.08 020820 JE     a) Optimized:
                         _DrawBitLine1BPP, _DrawBitLine8BPP
1.00.06 020814 JE     a) Support for PCF8535 added
1.00.04 020510 JE     a) Bugfix in LCD_L0_FillRect
1.00.02 020425 JE     a) LCD_WRITEM_A1 used in optimized routines
1.00.02 020424 JE     a) Optimized routines added:
                         _DrawBitLine1BPP, LCD_L0_DrawHLine
                         LCD_L0_DrawVLine, LCD_L0_FillRect
1.00.00 020422 JE     a) First release
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>           /* memset */
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include "LCD_0.h"            /* Defines for first display */

#if (LCD_CONTROLLER == 8811) || (LCD_CONTROLLER == 8535)\
    && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#ifndef LCD_INIT_CONTROLLER
  #define LCD_INIT_CONTROLLER()
#endif

#ifndef LCD_OPTIMIZE
  #define LCD_OPTIMIZE 1
#endif

#ifndef LCD_CACHE
  #define  LCD_CACHE 1
#endif

/*********************************************
*
*       Macros for MIRROR_, SWAP_ and LUT_
*
**********************************************
*/

#if (!defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) (x)
    #define LOG2PHYS_Y(x, y) (y)
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) (y)
    #define LOG2PHYS_Y(x, y) (x)
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) (x)
    #define LOG2PHYS_Y(x, y) (LCD_YSIZE - 1 - (y))
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) (LCD_YSIZE - 1 - (y))
    #define LOG2PHYS_Y(x, y) (x)
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) (LCD_XSIZE - 1 - (x))
    #define LOG2PHYS_Y(x, y) (y)
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) (LCD_YSIZE - 1 - (y))
    #define LOG2PHYS_Y(x, y) (x)
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) (LCD_XSIZE - 1 - (x))
    #define LOG2PHYS_Y(x, y) (LCD_YSIZE - 1 - (y))
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #error This combination of mirroring/swapping not yet supported
  #endif
#else
  #if   ( defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) (x)
    #define LOG2PHYS_Y(x, y) LCD__aLine2Com0[y]
  #elif (!defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) LCD__aCol2Seg0[x]
    #define LOG2PHYS_Y(x, y) (y)
  #elif ( defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) LCD__aCol2Seg0[x]
    #define LOG2PHYS_Y(x, y) LCD__aLine2Com0[y]
  #endif
#endif

/*********************************************
*
*       Macros for simulation
*
**********************************************
*/

#ifdef WIN32
  #undef LCD_WRITE_A0
  #undef LCD_WRITE_A1
  #undef LCD_WRITEM_A1
  #undef LCD_READ_A0
  #undef LCD_READ_A1
  void SIM_WriteA1C0(U8 Data);
  void SIM_WriteMA1C0(U8 * pData, int NumberOfBytes);
  void SIM_WriteA0C0(U8 cmd);
  U8   SIM_ReadA1C0(void);
  U8   SIM_ReadA0C0(void);
  #define LCD_WRITE_A1(Byte)                  SIM_WriteA1C0(Byte)
  #define LCD_WRITEM_A1(pData, NumberOfBytes) SIM_WriteMA1C0(pData, NumberOfBytes)
  #define LCD_WRITE_A0(Byte)                  SIM_WriteA0C0(Byte)
  #define LCD_READ_A1()                       SIM_ReadA1C0()
  #define LCD_READ_A0()                       SIM_ReadA0C0()
#endif

/*********************************************
*
*       Hardware access macros
*
**********************************************
*/

#ifndef LCD_CHECK_BUSY
  #define LCD_CHECK_BUSY 0
#endif

#ifndef LCD_XOFF
  #define LCD_XOFF 0
#endif

#if LCD_CHECK_BUSY
  #define CHECK_BUSY() WAIT_WHILE_BUSY()
#else
  #define CHECK_BUSY()
#endif

#ifdef LCD_CACHE
  #if !LCD_CACHE
    #error Using this driver a cache must be defined!
  #endif
#else
  #define LCD_CACHE 1
#endif

#if (LCD_CONTROLLER == 8811) /* PCF8811 */

  #define MAX_PAGE             10
  #define MAX_OFFSET           128
  #define WAIT_WHILE_BUSY()    { U8 Status; do { LCD_READ_A0(Status); } while (Status & (1 << 7)); }
  #define WRITE_DATA(Data)     CHECK_BUSY(); LCD_WRITE_A1(Data); _VRam[_Page][_Offset] = Data
  #define LCD_ON()             CHECK_BUSY(); LCD_WRITE_A0(0xAF)
  #define LCD_OFF()            CHECK_BUSY(); LCD_WRITE_A0(0xAE)
  #define SET_PAGE(Page)       CHECK_BUSY(); LCD_WRITE_A0(Page + 0xB0)
  #define SET_OFFSET(Offset)   CHECK_BUSY(); LCD_WRITE_A0(0x10 + (Offset >> 4)); \
                               CHECK_BUSY(); LCD_WRITE_A0(0x00 + (Offset & 0x0F))
  #ifndef LCD_AUTOINC_Y
    #define LCD_AUTOINC_Y      MAX_OFFSET
  #endif

  #define INCREMENT_XY_VOLATILE

#elif (LCD_CONTROLLER == 8535) /* PCF8535 */

  static U8 _aMirror[256] = {
    ________, X_______, _X______, XX______, __X_____, X_X_____, _XX_____, XXX_____,
    ___X____, X__X____, _X_X____, XX_X____, __XX____, X_XX____, _XXX____, XXXX____,
    ____X___, X___X___, _X__X___, XX__X___, __X_X___, X_X_X___, _XX_X___, XXX_X___,
    ___XX___, X__XX___, _X_XX___, XX_XX___, __XXX___, X_XXX___, _XXXX___, XXXXX___,
    _____X__, X____X__, _X___X__, XX___X__, __X__X__, X_X__X__, _XX__X__, XXX__X__,
    ___X_X__, X__X_X__, _X_X_X__, XX_X_X__, __XX_X__, X_XX_X__, _XXX_X__, XXXX_X__,
    ____XX__, X___XX__, _X__XX__, XX__XX__, __X_XX__, X_X_XX__, _XX_XX__, XXX_XX__,
    ___XXX__, X__XXX__, _X_XXX__, XX_XXX__, __XXXX__, X_XXXX__, _XXXXX__, XXXXXX__,
    ______X_, X_____X_, _X____X_, XX____X_, __X___X_, X_X___X_, _XX___X_, XXX___X_,
    ___X__X_, X__X__X_, _X_X__X_, XX_X__X_, __XX__X_, X_XX__X_, _XXX__X_, XXXX__X_,
    ____X_X_, X___X_X_, _X__X_X_, XX__X_X_, __X_X_X_, X_X_X_X_, _XX_X_X_, XXX_X_X_,
    ___XX_X_, X__XX_X_, _X_XX_X_, XX_XX_X_, __XXX_X_, X_XXX_X_, _XXXX_X_, XXXXX_X_,
    _____XX_, X____XX_, _X___XX_, XX___XX_, __X__XX_, X_X__XX_, _XX__XX_, XXX__XX_,
    ___X_XX_, X__X_XX_, _X_X_XX_, XX_X_XX_, __XX_XX_, X_XX_XX_, _XXX_XX_, XXXX_XX_,
    ____XXX_, X___XXX_, _X__XXX_, XX__XXX_, __X_XXX_, X_X_XXX_, _XX_XXX_, XXX_XXX_,
    ___XXXX_, X__XXXX_, _X_XXXX_, XX_XXXX_, __XXXXX_, X_XXXXX_, _XXXXXX_, XXXXXXX_,
    _______X, X______X, _X_____X, XX_____X, __X____X, X_X____X, _XX____X, XXX____X,
    ___X___X, X__X___X, _X_X___X, XX_X___X, __XX___X, X_XX___X, _XXX___X, XXXX___X,
    ____X__X, X___X__X, _X__X__X, XX__X__X, __X_X__X, X_X_X__X, _XX_X__X, XXX_X__X,
    ___XX__X, X__XX__X, _X_XX__X, XX_XX__X, __XXX__X, X_XXX__X, _XXXX__X, XXXXX__X,
    _____X_X, X____X_X, _X___X_X, XX___X_X, __X__X_X, X_X__X_X, _XX__X_X, XXX__X_X,
    ___X_X_X, X__X_X_X, _X_X_X_X, XX_X_X_X, __XX_X_X, X_XX_X_X, _XXX_X_X, XXXX_X_X,
    ____XX_X, X___XX_X, _X__XX_X, XX__XX_X, __X_XX_X, X_X_XX_X, _XX_XX_X, XXX_XX_X,
    ___XXX_X, X__XXX_X, _X_XXX_X, XX_XXX_X, __XXXX_X, X_XXXX_X, _XXXXX_X, XXXXXX_X,
    ______XX, X_____XX, _X____XX, XX____XX, __X___XX, X_X___XX, _XX___XX, XXX___XX,
    ___X__XX, X__X__XX, _X_X__XX, XX_X__XX, __XX__XX, X_XX__XX, _XXX__XX, XXXX__XX,
    ____X_XX, X___X_XX, _X__X_XX, XX__X_XX, __X_X_XX, X_X_X_XX, _XX_X_XX, XXX_X_XX,
    ___XX_XX, X__XX_XX, _X_XX_XX, XX_XX_XX, __XXX_XX, X_XXX_XX, _XXXX_XX, XXXXX_XX,
    _____XXX, X____XXX, _X___XXX, XX___XXX, __X__XXX, X_X__XXX, _XX__XXX, XXX__XXX,
    ___X_XXX, X__X_XXX, _X_X_XXX, XX_X_XXX, __XX_XXX, X_XX_XXX, _XXX_XXX, XXXX_XXX,
    ____XXXX, X___XXXX, _X__XXXX, XX__XXXX, __X_XXXX, X_X_XXXX, _XX_XXXX, XXX_XXXX,
    ___XXXXX, X__XXXXX, _X_XXXXX, XX_XXXXX, __XXXXXX, X_XXXXXX, _XXXXXXX, XXXXXXXX
  };

  #define MAX_PAGE             9
  #define MAX_OFFSET           133
  #define WAIT_WHILE_BUSY()    { U8 Status; do { LCD_READ_A0(Status); } while (Status & (1 << 7)); }
  #define WRITE_DATA(Data)     CHECK_BUSY();                 \
                               LCD_WRITE_A1(_aMirror[Data]); \
                               _VRam[_Page][_Offset] = Data
  #define LCD_ON()
  #define LCD_OFF()
  #define SET_PAGE(Page)       CHECK_BUSY(); LCD_WRITE_A0(0x40 + Page)
  #define SET_OFFSET(Offset)   CHECK_BUSY();                                             \
                               LCD_WRITE_A0(0x20 + (((Offset + LCD_XOFF) & 0x80) >> 5)); \
                               LCD_WRITE_A0(0x80 +  ((Offset + LCD_XOFF) & 0x7F))

#endif

#define SET_PAGE_IF_NEEDED(Page)          _SetPageIfNeeded(Page)     /* Function call only in debug version */
#define SET_OFFSET_IF_NEEDED(Offset)      _SetOffsetIfNeeded(Offset) /* Function call only in debug version */
#define WRITE_DATA1(Data)                 _WriteData1(Data)          /* Function call only in debug version */
#define WRITE_DATAM(pData, NumberOfBytes) _WriteDataM(pData, NumberOfBytes)
#define GET_CURRENT_BYTE()                _VRam[_Page][_Offset]
#define GET_BYTE(Page, Offset)            _VRam[Page][Offset]

#if !LCD_CACHE
  #error Not yet supported!
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static int _Page, _Offset;
#if LCD_CACHE
  static U8 _VRam[MAX_PAGE][MAX_OFFSET];
#endif
static const LCD_PIXELINDEX _ConversionTable[2] = {0, 1};

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/

#if defined(INCREMENT_XY_VOLATILE)

static int _VolatileOffset, _VolatilePage;

static void _SetPageIfNeeded(int Page) {
  if (_Page == Page)
    return;
  _Page = Page;
  SET_PAGE(_Page);
  _VolatilePage = 0;
  if (_VolatileOffset) {
    SET_OFFSET(_Offset);
    _VolatileOffset = 0;
  }
}

static void _SetOffsetIfNeeded(int Offset) {
  if (_Offset == Offset)
    return;
  _Offset = Offset;
  SET_OFFSET(_Offset);
  _VolatileOffset = 0;
  if (_VolatilePage) {
    SET_PAGE(_Page);
    _VolatilePage = 0;
  }
}

static void _WriteData1(U8 Data) {
  WRITE_DATA(Data);
  _Offset++;
  _VolatileOffset = 1;
  if (_Offset == MAX_OFFSET) {
    _Offset = 0;
    _VolatilePage = 1;
    if (_Page < (MAX_PAGE - 1)) {
      ++_Page;
    } else {
      _Page = 0;
    }
  }
}

static void _WriteDataM(U8 * pData, int NumberOfBytes) {
  LCD_WRITEM_A1(pData, NumberOfBytes);
  _Offset += NumberOfBytes;
  _VolatileOffset = 1;
  if (_Offset == MAX_OFFSET) {
    _Offset = 0;
    _VolatilePage = 1;
    if (_Page < (MAX_PAGE - 1)) {
      ++_Page;
    } else {
      _Page = 0;
    }
  }
}

#elif defined(INCREMENT_XY)

static void _SetPageIfNeeded(int Page) {
  if (_Page == Page)
    return;
  _Page = Page;
  SET_PAGE(_Page);
}

static void _SetOffsetIfNeeded(int Offset) {
  if (_Offset == Offset)
    return;
  _Offset = Offset;
  SET_OFFSET(_Offset);
}

static void _WriteData1(U8 Data) {
  WRITE_DATA(Data);
  _Offset++;
  if (_Offset == MAX_OFFSET) {
    _Offset = 0;
    if (_Page < (MAX_PAGE - 1)) {
      ++_Page;
    } else {
      _Page = 0;
    }
  }
}

static void _WriteDataM(U8 * pData, int NumberOfBytes) {
  LCD_WRITEM_A1(pData, NumberOfBytes);
  _Offset += NumberOfBytes;
  if (_Offset == MAX_OFFSET) {
    _Offset = 0;
    if (_Page < (MAX_PAGE - 1)) {
      ++_Page;
    } else {
      _Page = 0;
    }
  }
}

#else

static void _SetPageIfNeeded(int Page) {
  _Page = Page;
  SET_PAGE(_Page);
}

static void _SetOffsetIfNeeded(int Offset) {
  _Offset = Offset;
  SET_OFFSET(_Offset);
}

static void _WriteData1(U8 Data) {
  WRITE_DATA(Data);
}

static void _WriteDataM(U8 * pData, int NumberOfBytes) {
  while(NumberOfBytes) {
    WRITE_DATA(*pData);
    if (--NumberOfBytes) {
      pData++;
      _Offset++;
      SET_OFFSET(_Offset);
    }
  }
}

#endif

/*********************************************
*
*       Draw Bitmap 1 BPP (optimized)
*
**********************************************
*/

#if LCD_OPTIMIZE \
  && !LCD_SWAP_XY \
  && !LCD_MIRROR_X \
  && !LCD_MIRROR_Y

static void _DrawBitLine1BPP(int x, int y, U8 const * pData, int ysize, const LCD_PIXELINDEX * pTrans, int BytesPerLine, U8 DataMask) {
  LCD_PIXELINDEX Index0 = *(pTrans + 0);
  LCD_PIXELINDEX Index1 = *(pTrans + 1);
  U8 PixelMask = 1 << (y & 7);
  int Page = y >> 3;
  U8 Data;
  Data = _VRam[Page][x];
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      while(ysize--) {
        if (*pData & DataMask) {
          if (Index1) {
            Data |= PixelMask;
          } else {
            Data &= ~PixelMask;
          }
        } else {
          if (Index0) {
            Data |= PixelMask;
          } else {
            Data &= ~PixelMask;
          }
        }
        pData += BytesPerLine;
        PixelMask <<= 1;
        if (!PixelMask || !ysize) {
          _VRam[Page][x] = Data;
          if (ysize) {
            PixelMask = 1;
            Data = _VRam[++Page][x];
          }
        }
      }
      break;
    case LCD_DRAWMODE_TRANS:
      while(ysize--) {
        if (*pData & DataMask) {
          if (Index1) {
            Data |= PixelMask;
          } else {
            Data &= ~PixelMask;
          }
        }
        pData += BytesPerLine;
        PixelMask <<= 1;
        if (!PixelMask || !ysize) {
          _VRam[Page][x] = Data;
          if (ysize) {
            PixelMask = 1;
            Data = _VRam[++Page][x];
          }
        }
      }
      break;
    case LCD_DRAWMODE_XOR:
      while(ysize--) {
        if (*pData & DataMask) {
          Data ^= PixelMask;
        }
        pData += BytesPerLine;
        PixelMask <<= 1;
        if (!PixelMask || !ysize) {
          _VRam[Page][x] = Data;
          if (ysize) {
            PixelMask = 1;
            Data = _VRam[++Page][x];
          }
        }
      }
      break;
	}
}

/*********************************************
*
*       Draw Bitmap 1 BPP (not optimized)
*
**********************************************
*/

#else

static void _DrawBitLine1BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX Index0 = *(pTrans+0);
  LCD_PIXELINDEX Index1 = *(pTrans+1);
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      do {
        LCD_L0_SetPixelIndex(x++, y, (*p & (0x80 >> Diff)) ? Index1 : Index0);
			  if (++Diff == 8) {
          Diff = 0;
				  p++;
			  }
		  } while (--xsize);
      break;
    case LCD_DRAWMODE_TRANS:
      do {
  		  if (*p & (0x80 >> Diff))
          LCD_L0_SetPixelIndex(x, y, Index1);
        x++;
			  if (++Diff == 8) {
          Diff = 0;
				  p++;
			  }
		  } while (--xsize);
      break;
    case LCD_DRAWMODE_XOR:;
      do {
  		  if (*p & (0x80 >> Diff)) {
          int Pixel = LCD_L0_GetPixelIndex(x, y);
          LCD_L0_SetPixelIndex(x, y, LCD_NUM_COLORS - 1 - Pixel);
        }
        x++;
			  if (++Diff == 8) {
          Diff = 0;
				  p++;
			  }
		  } while (--xsize);
      break;
	}
}

#endif

/*********************************************
*
*       Draw Bitmap 2 BPP
*
**********************************************
*/

#if (LCD_MAX_LOG_COLORS > 2)
static void _DrawBitLine2BPP(int x, int y, U8 const * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      do {
        int Shift = (3 - CurrentPixel) << 1;
        int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
        LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
        LCD_L0_SetPixelIndex(x++, y, PixelIndex);
        if (++CurrentPixel == 4) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
      break;
    case LCD_DRAWMODE_TRANS:
      do {
        int Shift = (3 - CurrentPixel) << 1;
        int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
        if (Index) {
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          LCD_L0_SetPixelIndex(x, y, PixelIndex);
        }
        x++;
        if (++CurrentPixel == 4) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
      break;
  }
}
#endif

/*********************************************
*
*       Draw Bitmap 4 BPP
*
**********************************************
*/

#if (LCD_MAX_LOG_COLORS > 4)
static void _DrawBitLine4BPP(int x, int y, U8 const * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      do {
        int Shift = (1 - CurrentPixel) << 2;
        int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
        LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
        LCD_L0_SetPixelIndex(x++, y, PixelIndex);
        if (++CurrentPixel == 2) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
      break;
    case LCD_DRAWMODE_TRANS:
      do {
        int Shift = (1 - CurrentPixel) << 2;
        int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
        if (Index) {
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          LCD_L0_SetPixelIndex(x, y, PixelIndex);
        }
        x++;
        if (++CurrentPixel == 2) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
      break;
  }
}
#endif

/*********************************************
*
*       Draw Bitmap 8 BPP (optimized)
*
**********************************************
*/

#if (LCD_MAX_LOG_COLORS > 16)

#if LCD_OPTIMIZE \
  && !LCD_SWAP_XY \
  && !LCD_MIRROR_X \
  && !LCD_MIRROR_Y

static void _DrawBitLine8BPP(int x, int y, U8 const * pData, int ysize, const LCD_PIXELINDEX * pTrans, int BytesPerLine) {
  U8 PixelMask = 1 << (y & 7);
  int Page = y >> 3;
  U8 Data = _VRam[Page][x];
  if (!pTrans)
    pTrans = _ConversionTable;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      while(ysize--) {
        if (*(pTrans + *pData)) {
          Data |= PixelMask;
        } else {
          Data &= ~PixelMask;
        }
        pData += BytesPerLine;
        PixelMask <<= 1;
        if (!PixelMask || !ysize) {
          _VRam[Page][x] = Data;
          if (ysize) {
            PixelMask = 1;
            Data = _VRam[++Page][x];
          }
        }
      }
      break;
    case LCD_DRAWMODE_TRANS:
      while(ysize--) {
        LCD_PIXELINDEX Pixel = *pData;
        if (Pixel) {
          if (*(pTrans + Pixel)) {
            Data |= PixelMask;
          } else {
            Data &= ~PixelMask;
          }
        }
        pData += BytesPerLine;
        PixelMask <<= 1;
        if (!PixelMask || !ysize) {
          _VRam[Page][x] = Data;
          if (ysize) {
            PixelMask = 1;
            Data = _VRam[++Page][x];
          }
        }
      }
      break;
	}
}

/*********************************************
*
*       Draw Bitmap 8 BPP (not optimized)
*
**********************************************
*/

#else

static void _DrawBitLine8BPP(int x, int y, U8 const * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixel;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          LCD_L0_SetPixelIndex(x, y, *(pTrans + Pixel));
        }
      } else {
        for (; xsize > 0; xsize--, x++, p++) {
          LCD_L0_SetPixelIndex(x, y, *p);
        }
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          if (Pixel) {
            LCD_L0_SetPixelIndex(x, y, *(pTrans + Pixel));
          }
        }
      } else {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          if (Pixel) {
            LCD_L0_SetPixelIndex(x, y, Pixel);
          }
        }
      }
      break;
  }
}
#endif

#endif

/*********************************************
*
*       Draw Bitmap 16 BPP
*
**********************************************
*/

#if (LCD_BITSPERPIXEL > 8)
static void _DrawBitLine16BPP(int x, int y, U16 const * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixel;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
    case 0:
      if (pTrans) {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          LCD_L0_SetPixelIndex(x, y, *(pTrans + Pixel));
        }
      } else {
        for (; xsize > 0; xsize--, x++, p++) {
          LCD_L0_SetPixelIndex(x, y, *p);
        }
      }
      break;
    case LCD_DRAWMODE_TRANS:
      if (pTrans) {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          if (Pixel) {
            LCD_L0_SetPixelIndex(x, y, *(pTrans + Pixel));
          }
        }
      } else {
        for (; xsize > 0; xsize--, x++, p++) {
          Pixel = *p;
          if (Pixel) {
            LCD_L0_SetPixelIndex(x, y, Pixel);
          }
        }
      }
      break;
  }
}
#endif

/*********************************************************************
*
*       Exported functions
*
**********************************************************************
*/

/*********************************************
*
*       LCD_L0_SetPixelIndex
*
**********************************************
*/

void LCD_L0_SetPixelIndex(int x, int y, int PixelIndex) {
  /* Convert logical into physical coordinates (Dep. on LCDConf.h) */
  #if LCD_SWAP_XY | LCD_MIRROR_X | LCD_MIRROR_Y
    int xPhys = LOG2PHYS_X(x, y);
    int yPhys = LOG2PHYS_Y(x, y);
  #else
    #define xPhys x
    #define yPhys y
  #endif
  /* Write into hardware */
  {
    U8 Data = GET_BYTE(yPhys >> 3, xPhys);
    U8 AndMask = ~(1 << (yPhys & 7));
    U8 OrMask  = PixelIndex << (yPhys & 7);
    Data &= AndMask;
    Data |= OrMask;
    SET_PAGE_IF_NEEDED(yPhys >> 3);
    SET_OFFSET_IF_NEEDED(xPhys);
    WRITE_DATA1(Data);
  }
}

/*********************************************
*
*       LCD_L0_GetPixelIndex
*
**********************************************
*/

unsigned int LCD_L0_GetPixelIndex(int x, int y) {
  /* Convert logical into physical coordinates (Dep. on LCDConf.h) */
  #if LCD_SWAP_XY | LCD_MIRROR_X| LCD_MIRROR_Y
    int xPhys = LOG2PHYS_X(x, y);
    int yPhys = LOG2PHYS_Y(x, y);
  #else
    #define xPhys x
    #define yPhys y
  #endif
  /* Read from hardware */
  {
    U8 Data = GET_BYTE(yPhys >> 3, xPhys);
    return (Data & (1 << (yPhys & 7))) ? 1 : 0;
  }
}

/*********************************************
*
*       LCD_L0_XorPixel
*
**********************************************
*/

void LCD_L0_XorPixel(int x, int y) {
  LCD_PIXELINDEX PixelIndex = LCD_L0_GetPixelIndex(x, y);
  LCD_L0_SetPixelIndex(x, y, LCD_NUM_COLORS - PixelIndex - 1);
}

/*********************************************
*
*       LCD_L0_DrawHLine (optimized)
*
**********************************************
*/

#if LCD_OPTIMIZE \
  && !LCD_SWAP_XY \
  && !LCD_MIRROR_X \
  && !LCD_MIRROR_Y

void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  #if LCD_CACHE
    U8 Mask = 1 << (y & 7);
    int Page = y >> 3;
    U8 * pData = &_VRam[Page][x0];
    int NumberOfBytes = x1 - x0 + 1;
    SET_PAGE_IF_NEEDED(Page);
    SET_OFFSET_IF_NEEDED(x0);
    for (; x0 <= x1; x0++) {
      if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
        _VRam[Page][x0] ^= Mask;
      } else {
        if (LCD_COLORINDEX) {
          _VRam[Page][x0] |= Mask;
        } else {
          _VRam[Page][x0] &= ~Mask;
        }
      }
    }
    WRITE_DATAM(pData, NumberOfBytes);
  #else
    U8 Mask = 1 << (y & 7);
    SET_PAGE_IF_NEEDED(y >> 3);
    SET_OFFSET_IF_NEEDED(x0);
    for (; x0 <= x1; x0++) {
      U8 Data = GET_CURRENT_BYTE();
      if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
        WRITE_DATA1(Data ^ Mask);
      } else {
        WRITE_DATA1((LCD_COLORINDEX) ? Data | Mask : Data & ~Mask);
      }
    }
  #endif
}

/*********************************************
*
*       LCD_L0_DrawHLine (not optimized)
*
**********************************************
*/

#else

void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; x0 <= x1; x0++) {
      LCD_L0_XorPixel(x0, y);
    }
  } else {
    for (; x0 <= x1; x0++) {
      LCD_L0_SetPixelIndex(x0, y, LCD_COLORINDEX);
    }
  }
}

#endif

/*********************************************
*
*       LCD_L0_DrawVLine (optimized)
*
**********************************************
*/

#if LCD_OPTIMIZE \
  && !LCD_SWAP_XY \
  && !LCD_MIRROR_X \
  && !LCD_MIRROR_Y

void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  int y0_ = y0 & 7;
  int y1_ = (y1 + 1) & 7;
  if (y0_) {
    U8 Data = GET_BYTE(y0 >> 3, x);
    U8 Mask = 0xff << y0_;
    if ((y0 >> 3) == (y1 >> 3)) {
      Mask &= 0xff >> (7 - (y1 & 7));
    }
    SET_PAGE_IF_NEEDED(y0 >> 3);
    SET_OFFSET_IF_NEEDED(x);
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
      WRITE_DATA1(Data ^ Mask);
    } else {
      WRITE_DATA1((LCD_COLORINDEX) ? Data | Mask : Data & ~Mask);
    }
    if ((y0 & 0xfff8) == (y1 & 0xfff8)) {
      return;
    }
  }
  {
    int Page     =  ((y0 + 7) & 0xfff8) >> 3;
    int NumPages = (((y1 + 1) & 0xfff8) >> 3) - Page;
    if (NumPages) {
      while (NumPages--) {
        SET_PAGE_IF_NEEDED(Page++);
        SET_OFFSET_IF_NEEDED(x);
        if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
          WRITE_DATA1(GET_CURRENT_BYTE() ^ 0xff);
        } else {
          WRITE_DATA1((LCD_COLORINDEX) ? 0xff : 0x00);
        }
      }
    }
  }
  if (y1_) {
    U8 Data = GET_BYTE(y1 >> 3, x);
    U8 Mask = 0xff >> (8 - y1_);
    SET_PAGE_IF_NEEDED(y1 >> 3);
    SET_OFFSET_IF_NEEDED(x);
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
      WRITE_DATA1(Data ^ Mask);
    } else {
      WRITE_DATA1((LCD_COLORINDEX) ? Data | Mask : Data & ~Mask);
    }
  }
}

/*********************************************
*
*       LCD_L0_DrawVLine (not optimized)
*
**********************************************
*/

#else

void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; y0 <= y1; y0++) {
      LCD_L0_XorPixel(x, y0);
    }
  } else {
    for (; y0 <= y1; y0++) {
      LCD_L0_SetPixelIndex(x, y0, LCD_COLORINDEX);
    }
  }
}

#endif

/*********************************************
*
*       LCD_L0_FillRect (optimized)
*
**********************************************
*/

#if LCD_OPTIMIZE \
  && !LCD_SWAP_XY \
  && !LCD_MIRROR_X \
  && !LCD_MIRROR_Y

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  #if LCD_CACHE
    int y0_ = y0 & 7;
    int y1_ = (y1 + 1) & 7;
    int NumberOfBytes = x1 - x0 + 1;
    if (y0_) {
      U8 * pData;
      int x0_ = x0;
      U8 Mask = 0xff << y0_;
      int Page = y0 >> 3;
      if ((y0 & 0xfff8) == ((y1 + 1) & 0xfff8)) {
        Mask &= 0xff >> (8 - y1_);
      }
      SET_PAGE_IF_NEEDED(Page);
      SET_OFFSET_IF_NEEDED(x0);
      pData = &_VRam[_Page][_Offset];
      for (; x0_ <= x1; x0_++) {
        if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
          _VRam[Page][x0_] ^= Mask;
        } else {
          if (LCD_COLORINDEX) {
            _VRam[Page][x0_] |= Mask;
          } else {
            _VRam[Page][x0_] &= ~Mask;
          }
        }
      }
      WRITE_DATAM(pData, NumberOfBytes);
      if ((y0 & 0xfff8) == (y1 & 0xfff8)) {
        return;
      }
    }
    {
      int Page     =  ((y0 + 7) & 0xfff8) >> 3;
      int NumPages = (((y1 + 1) & 0xfff8) >> 3) - Page;
      if (NumPages) {
        while (NumPages--) {
          U8 * pData;
          int x0_ = x0;
          SET_PAGE_IF_NEEDED(Page++);
          SET_OFFSET_IF_NEEDED(x0);
          pData = &_VRam[_Page][_Offset];
          for (; x0_ <= x1; x0_++) {
            if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
              _VRam[_Page][x0_] ^= 0xff;
            } else {
              if (LCD_COLORINDEX) {
                _VRam[_Page][x0_] = 0xff;
              } else {
                _VRam[_Page][x0_] = 0x00;
              }
            }
          }
          WRITE_DATAM(pData, NumberOfBytes);
        }
      }
    }
    if (y1_) {
      U8 * pData;
      int x0_ = x0;
      U8 Mask = 0xff >> (8 - y1_);
      int Page = y1 >> 3;
      SET_PAGE_IF_NEEDED(Page);
      SET_OFFSET_IF_NEEDED(x0);
      pData = &_VRam[Page][_Offset];
      for (; x0_ <= x1; x0_++) {
        if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
          _VRam[Page][x0_] ^= Mask;
        } else {
          if (LCD_COLORINDEX) {
            _VRam[Page][x0_] |= Mask;
          } else {
            _VRam[Page][x0_] &= ~Mask;
          }
        }
      }
      WRITE_DATAM(pData, NumberOfBytes);
    }
  #else
    int y0_ = y0 & 7;
    int y1_ = (y1 + 1) & 7;
    if (y0_) {
      int x0_ = x0;
      U8 Mask = 0xff << y0_;
      if ((y0 & 0xfff8) == (y1 & 0xfff8)) {
        Mask &= 0xff >> (8 - y1_);
      }
      SET_PAGE_IF_NEEDED(y0 >> 3);
      SET_OFFSET_IF_NEEDED(x0);
      for (; x0_ <= x1; x0_++) {
        U8 Data = GET_CURRENT_BYTE();
        if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
          WRITE_DATA1(Data ^ Mask);
        } else {
          WRITE_DATA1((LCD_COLORINDEX) ? Data | Mask : Data & ~Mask);
        }
      }
      if ((y0 & 0xfff8) == (y1 & 0xfff8)) {
        return;
      }
    }
    {
      int Page     =  ((y0 + 7) & 0xfff8) >> 3;
      int NumPages = (((y1 + 1) & 0xfff8) >> 3) - Page;
      if (NumPages) {
        while (NumPages--) {
          int x0_ = x0;
          SET_PAGE_IF_NEEDED(Page++);
          SET_OFFSET_IF_NEEDED(x0);
          for (; x0_ <= x1; x0_++) {
            if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
              WRITE_DATA1(GET_CURRENT_BYTE() ^ 0xff);
            } else {
              WRITE_DATA1((LCD_COLORINDEX) ? 0xff : 0x00);
            }
          }
        }
      }
    }
    if (y1_) {
      int x0_ = x0;
      U8 Mask = 0xff >> (8 - y1_);
      SET_PAGE_IF_NEEDED(y1 >> 3);
      SET_OFFSET_IF_NEEDED(x0);
      for (; x0_ <= x1; x0_++) {
        U8 Data = GET_CURRENT_BYTE();
        if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
          WRITE_DATA1(Data ^ Mask);
        } else {
          WRITE_DATA1((LCD_COLORINDEX) ? Data | Mask : Data & ~Mask);
        }
      }
    }
  #endif
}

/*********************************************
*
*       LCD_L0_FillRect (not optimized)
*
**********************************************
*/

#else

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  for (; y0 <= y1; y0++) {
    LCD_L0_DrawHLine(x0, y0, x1);
  }
}

#endif

/*********************************************
*
*       LCD_L0_DrawBitmap
*
**********************************************
*/

void LCD_L0_DrawBitmap(int x0, int y0,
                       int xsize, int ysize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8* pData, int Diff,
                       const LCD_PIXELINDEX* pTrans)
{
  int i;
  #if LCD_OPTIMIZE \
    && !LCD_SWAP_XY \
    && !LCD_MIRROR_X \
    && !LCD_MIRROR_Y
    int Page0 = y0 >> 3;
    int Page1 = (y0 + ysize - 1) >> 3;
    int Opt = 0;
    switch (BitsPerPixel) {
      case 1:
        Opt = 1;
        xsize += Diff & 7;
        for (i = Diff; i < xsize; i++) {
          _DrawBitLine1BPP(x0 + i, y0, pData + (i >> 3), ysize, pTrans, BytesPerLine, 0x80 >> (i & 7));
        }
        break;
      case 8:
        Opt = 1;
        for (i = Diff; i < xsize; i++) {
          _DrawBitLine8BPP(x0 + i, y0, pData + i, ysize, pTrans, BytesPerLine);
        }
        break;
    }
    if (Opt) {
      for (; Page0 <= Page1; Page0++) {
        U8 * p = &_VRam[Page0][x0];
        SET_PAGE_IF_NEEDED(Page0);
        SET_OFFSET_IF_NEEDED(x0);
        WRITE_DATAM(p, xsize);
      }
      return;
    }
  #endif
  /* Use _DrawBitLineXBPP */
  for (i=0; i<ysize; i++) {
    switch (BitsPerPixel) {
      #if !LCD_OPTIMIZE \
        || LCD_SWAP_XY \
        || LCD_MIRROR_X \
        || LCD_MIRROR_Y
        case 1:
          _DrawBitLine1BPP(x0, i + y0, pData, Diff, xsize, pTrans);
          break;
      #endif
      #if (LCD_MAX_LOG_COLORS > 2)
        case 2:
          _DrawBitLine2BPP(x0, i + y0, pData, Diff, xsize, pTrans);
          break;
      #endif
      #if (LCD_MAX_LOG_COLORS > 4)
        case 4:
          _DrawBitLine4BPP(x0, i + y0, pData, Diff, xsize, pTrans);
          break;
      #endif
      #if (LCD_MAX_LOG_COLORS > 16)
        #if !LCD_OPTIMIZE \
          || LCD_SWAP_XY \
          || LCD_MIRROR_X \
          || LCD_MIRROR_Y
          case 8:
            _DrawBitLine8BPP(x0, i + y0, pData, xsize, pTrans);
            break;
        #endif
      #endif
      #if (LCD_BITSPERPIXEL > 8)
        case 16:
          _DrawBitLine16BPP(x0, i + y0, (const U16 *)pData, xsize, pTrans);
          break;
      #endif
    }
    pData += BytesPerLine;
  }
}

/*********************************************
*
*       LCD_L0_SetOrg
*
**********************************************
*/

void LCD_L0_SetOrg(int x, int y) {
  GUI_USE_PARA(x);
  GUI_USE_PARA(y);
}

/*********************************************
*
*       LCD_On / LCD_Off
*
**********************************************
*/

void LCD_On (void) {
#ifdef LCD_ON
  LCD_ON();
#endif
}

void LCD_Off (void) {
#ifdef LCD_OFF
  LCD_OFF();
#endif
}

/*********************************************
*
*       LCD_L0_Init
*
**********************************************
Purpose:
  Initialises the LCD-controller.
*/

int  LCD_L0_Init(void) {
  #if LCD_CACHE
    memset(_VRam, 0, sizeof(_VRam));
  #endif
  LCD_INIT_CONTROLLER();
  LCD_ON();
  /* Clear display RAM */
  {
    int x, y;
    U8 Data = 0x00;
    for (y = 0; y < ((LCD_YSIZE + 7) >> 3); y++) {
      SET_PAGE(y);
      for (x = 0; x < LCD_XSIZE; x++) {
        SET_OFFSET(x);
        WRITE_DATA(Data);
      }
    }
  }
  return 0;
}

/*********************************************
*
*       LCD_L0_SetLUTEntry
*
**********************************************
*/

void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR Color) {
  GUI_USE_PARA(Pos);
  GUI_USE_PARA(Color);
}

#else

void LCDPage1bpp(void) { } /* avoid empty object files */

#endif /* (LCD_CONTROLLER undefined) */
