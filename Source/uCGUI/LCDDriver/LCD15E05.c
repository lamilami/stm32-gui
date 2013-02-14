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
File        : LCD15E05.C
Purpose     : Driver for LCDs using a Seiko Epson S1D15E05 controller
----------------------------------------------------------------------   
Version-Date---Author-Explanation                                        
----------------------------------------------------------------------   
1.00a   020708 JE     a) Changed to work with 2bpp DDP bitmaps
1.00    020204 JE     a) Hardwareinterface routines renamed:
                         ...DATA -> ...A1, ...CMD -> ...A0
0.90.00 011030 JE     a) First release
---------------------------LIST OF CONFIG SWITCHES--------------------
The following is a list of additional configuration switches for this
driver. These switches might not be listed in the manual, because
the manual mainly covers the general config switches which are
supported by all drivers.
----------------------------------------------------------------------
define ----------------------Explanation------------------------------
LCD_OPTIMIZE                 Controls the use of optimized routines.
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
Driver supports only 2bpp mode
----------------------------------------------------------------------
Open issues
----------------------------------------------------------------------
1bpp mode
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>           /* needed for memset */
#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include "LCD_0.h"            /* Defines for first display */

#if    (LCD_CONTROLLER == 0x15E05) \
       && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))

/*
        *********************************************************
        *
        *           Defaults for config switches
        *
        *********************************************************
*/

#ifndef LCD_CACHE
  #define  LCD_CACHE                  (1)
#endif

#ifndef LCD_INIT_CONTROLLER
  #define LCD_INIT_CONTROLLER()
#endif

/*
        *********************************************************
        *
        *           Defines for simulation
        *
        *********************************************************
*/

#ifdef WIN32
  #undef LCD_WRITE_A0
  #undef LCD_WRITE_A1
  #undef LCD_READ_A0
  #undef LCD_READ_A1
  void SIM_WriteA1C0(U8 Data);
  void SIM_WriteA0C0(U8 cmd);
  U8   SIM_ReadA1C0(void);
  U8   SIM_ReadA0C0(void);
  #define LCD_WRITE_A1(Data) SIM_WriteA1C0(Data) 
  #define LCD_WRITE_A0(cmd)  SIM_WriteA0C0(cmd)
  #define LCD_READ_A1()      SIM_ReadA1C0()
  #define LCD_READ_A0()      SIM_ReadA0C0()
#endif

/*
        *********************************************************
        *
        *          Remap ...A0, ...A1 -> ...CMD, ...DATA
        *
        *********************************************************
*/

#define LCD_READCMD0    LCD_READ_A0
#define LCD_READDATA0   LCD_READ_A1
#define LCD_WRITECMD0   LCD_WRITE_A0
#define LCD_WRITEDATA0  LCD_WRITE_A1

/*
        *********************************************************
        *
        *           Configuration switch checking
        *
        *********************************************************
*/

#if (LCD_BITSPERPIXEL > 2)
  #error This controller can handle only 1bpp and 2bpp displays
#endif

/*
        *********************************************************
        *                                                       *
        *              Macros, standard                         *
        *                                                       *
        *********************************************************

These macros can be found in any LCD-driver as they serve purposes
that can be found in any class of LCD-driver (Like clipping).

*/

#if (!defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS(x, y) x, y
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS(x, y) y, x
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS(x, y) x, LCD_YSIZE - 1 - (y)
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS(x, y) LCD_YSIZE - 1 - (y), x
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS(x, y) LCD_XSIZE - 1 - (x), y
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS(x, y) LCD_YSIZE - 1 - (y), x
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS(x, y) LCD_XSIZE - 1 - (x), LCD_YSIZE - 1 - (y)
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #error This combination of mirroring/swapping not yet supported
  #endif
#else
  #if   ( defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
    #define LOG2PHYS(x, y) x, LCD__aLine2Com0[y]
  #elif (!defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
    #define LOG2PHYS(x, y) LCD__aCol2Seg0[x], y
  #elif ( defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
    #define LOG2PHYS(x, y) LCD__aCol2Seg0[x], LCD__aLine2Com0[y]
  #endif
#endif

#define BKCOLOR LCD_BKCOLORINDEX
#define   COLOR LCD_COLORINDEX


/*
        *********************************************************
        *
        *           Static variables for driver
        *
        *********************************************************
*/

#if LCD_CACHE
  #if   (LCD_BITSPERPIXEL == 1)
    static U8 aVRam[(LCD_YSIZE_PHYS + 7) >> 3][LCD_XSIZE_PHYS];
  #elif (LCD_BITSPERPIXEL == 2)
    static U8 aVRam[(LCD_YSIZE_PHYS + 3) >> 2][LCD_XSIZE_PHYS];
  #endif
#endif

static int Page, Offset;

/*
        *********************************************************
        *
        *           Hardware access macros
        *
        *********************************************************
*/

#define MAX_PAGE   32
#define MAX_OFFSET 159

#define INCREMENT_CURSOR() \
  Offset++; \
  if (Offset > MAX_OFFSET) { \
    Offset = 0; \
    Page ++; \
    if (Page > MAX_PAGE) \
      Page = 0; \
  }

#if LCD_CACHE

  #define READ_DATA(Data) \
    Data = aVRam[Page][Offset]

  #define WRITE_DATA(Data) \
    LCD_WRITECMD0(0x1d); \
    LCD_WRITEDATA0(Data); \
    aVRam[Page][Offset] = Data; \
    INCREMENT_CURSOR()

#else

  #define READ_DATA(Data) \
    LCD_WRITECMD0(0x1c); \
    Data = LCD_READDATA0(); \
    INCREMENT_CURSOR()

  #define WRITE_DATA(Data) \
    LCD_WRITECMD0(0x1d); \
    LCD_WRITEDATA0(Data); \
    INCREMENT_CURSOR()

#endif

#define WRITE_PAGE(NewPage) \
  LCD_WRITECMD0(0xb1); \
  LCD_WRITEDATA0(NewPage); \
  Page = NewPage

#define WRITE_OFFSET(NewOffset) \
  LCD_WRITECMD0(0x13); \
  LCD_WRITEDATA0(NewOffset); \
  Offset = NewOffset

#define SET_PAGE_IF_NEEDED(y) \
  if (Page != (y >> 2)) { \
    WRITE_PAGE(y >> 2); \
  }

#define SET_OFFSET_IF_NEEDED(x) \
  if (Offset != x) { \
    WRITE_OFFSET(x); \
  }

/*
        *********************************************************
        *
        *           Static access routines for pixel access
        *
        *********************************************************

These routines should be only used by access macros to keep
sure, that logical coordinates are mapped to physical level

*/

/*
        *****************************************
        *
        *           SetPixelIndex
        *
        *****************************************
*/

static void SetPixelIndex(int x, int y, LCD_PIXELINDEX ColorIndex) {
  U8 Shift = ((y & 3) << 1);
  U8 AndMask = ~(0x03 << Shift);
  U8 OrMask  = ColorIndex << Shift;
  U8 Data;
  SET_PAGE_IF_NEEDED(y);
  SET_OFFSET_IF_NEEDED(x);
  READ_DATA(Data);
  Data &= AndMask;
  Data |= OrMask;
  SET_OFFSET_IF_NEEDED(x);
  WRITE_DATA(Data);
}

/*
        *****************************************
        *
        *           GetPixelIndex
        *
        *****************************************
*/

static LCD_PIXELINDEX GetPixelIndex(int x, int y) {
  U8 Shift = ((y & 3) << 1);
  U8 AndMask = 0x03 << Shift;
  U8 Data;
  SET_PAGE_IF_NEEDED(y);
  SET_OFFSET_IF_NEEDED(x);
  READ_DATA(Data);
  return (Data & AndMask) >> Shift;
}

/*
        *****************************************
        *
        *           XorPixel
        *
        *****************************************
*/

static void XorPixel(int x, int y) {
  U8 Data = GetPixelIndex(x, y);
  Data = LCD_NUM_COLORS - 1 - Data;
  SetPixelIndex(x, y, Data);
}

/*
        *********************************************************
        *
        *           Access macros for pixel access
        *
        *********************************************************
*/

#define SETPIXEL(x, y, c)  SetPixelIndex(LOG2PHYS(x, y), c)
#define GETPIXEL(x, y)     GetPixelIndex(LOG2PHYS(x, y))
#define XORPIXEL(x, y)     XorPixel     (LOG2PHYS(x, y))

/*
        *********************************************************
        *
        *           Static DrawBitLineXBPP functions
        *
        *********************************************************
*/

/*
        *****************************************
        *
        *           Draw Bitmap 1 BPP
        *           no optimizations
        *
        *****************************************
*/

static void  DrawBitLine1BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixels;
  LCD_PIXELINDEX Index0 = *(pTrans+0);
  LCD_PIXELINDEX Index1 = *(pTrans+1);
/*
// Jump to right entry point
*/
  pixels = *p;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
  case 0:
    switch (Diff&7) {
    case 0:   
      goto WriteBit0;
    case 1:   
      goto WriteBit1;
    case 2:
      goto WriteBit2;
    case 3:
      goto WriteBit3;
    case 4:
      goto WriteBit4;
    case 5:   
      goto WriteBit5;
    case 6:   
      goto WriteBit6;
    case 7:   
      goto WriteBit7;
    }
    break;
  case LCD_DRAWMODE_TRANS:
    switch (Diff&7) {
    case 0:
      goto WriteTBit0;
    case 1:
      goto WriteTBit1;
    case 2:
      goto WriteTBit2;
    case 3:
      goto WriteTBit3;
    case 4:
      goto WriteTBit4;
    case 5:   
      goto WriteTBit5;
    case 6:   
      goto WriteTBit6;
    case 7:   
      goto WriteTBit7;
    }
    break;
  case LCD_DRAWMODE_XOR:
    switch (Diff&7) {
    case 0:   
      goto WriteXBit0;
    case 1:   
      goto WriteXBit1;
    case 2:
      goto WriteXBit2;
    case 3:
      goto WriteXBit3;
    case 4:
      goto WriteXBit4;
    case 5:   
      goto WriteXBit5;
    case 6:   
      goto WriteXBit6;
    case 7:   
      goto WriteXBit7;
    }
  }
/*
        Write with transparency
*/
  WriteTBit0:
    if (pixels&(1<<7)) SETPIXEL(x+0, y, Index1);
    if (!--xsize)
      return;
  WriteTBit1:
    if (pixels&(1<<6)) SETPIXEL(x+1, y, Index1);
    if (!--xsize)
      return;
  WriteTBit2:
    if (pixels&(1<<5)) SETPIXEL(x+2, y, Index1);
    if (!--xsize)
      return;
  WriteTBit3:
    if (pixels&(1<<4)) SETPIXEL(x+3, y, Index1);
    if (!--xsize)
      return;
  WriteTBit4:
    if (pixels&(1<<3)) SETPIXEL(x+4, y, Index1);
    if (!--xsize)
      return;
  WriteTBit5:
    if (pixels&(1<<2)) SETPIXEL(x+5, y, Index1);
    if (!--xsize)
      return;
  WriteTBit6:
    if (pixels&(1<<1)) SETPIXEL(x+6, y, Index1);
    if (!--xsize)
      return;
  WriteTBit7:
    if (pixels&(1<<0)) SETPIXEL(x+7, y, Index1);
    if (!--xsize)
      return;
    x+=8;
    pixels = *(++p);
    goto WriteTBit0;
/*
        Write without transparency
*/
  WriteBit0:
    SETPIXEL(x+0, y, (pixels&(1<<7)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit1:
    SETPIXEL(x+1, y, (pixels&(1<<6)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit2:
    SETPIXEL(x+2, y, (pixels&(1<<5)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit3:
    SETPIXEL(x+3, y, (pixels&(1<<4)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit4:
    SETPIXEL(x+4, y, (pixels&(1<<3)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit5:
    SETPIXEL(x+5, y, (pixels&(1<<2)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit6:
    SETPIXEL(x+6, y, (pixels&(1<<1)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit7:
    SETPIXEL(x+7, y, (pixels&(1<<0)) ? Index1 : Index0);
    if (!--xsize)
      return;
    x+=8;
    pixels = *(++p);
    goto WriteBit0;
/*
        Write XOR mode
*/
  WriteXBit0:
    if (pixels&(1<<7))
      XORPIXEL(x+0, y);
    if (!--xsize)
      return;
  WriteXBit1:
    if (pixels&(1<<6))
      XORPIXEL(x+1, y);
    if (!--xsize)
      return;
  WriteXBit2:
    if (pixels&(1<<5))
      XORPIXEL(x+2, y);
    if (!--xsize)
      return;
  WriteXBit3:
    if (pixels&(1<<4))
      XORPIXEL(x+3, y);
    if (!--xsize)
      return;
  WriteXBit4:
    if (pixels&(1<<3))
      XORPIXEL(x+4, y);
    if (!--xsize)
      return;
  WriteXBit5:
    if (pixels&(1<<2))
      XORPIXEL(x+5, y);
    if (!--xsize)
      return;
  WriteXBit6:
    if (pixels&(1<<1))
      XORPIXEL(x+6, y);
    if (!--xsize)
      return;
  WriteXBit7:
    if (pixels&(1<<0))
      XORPIXEL(x+7, y);
    if (!--xsize)
      return;
    x+=8;
    pixels = *(++p);
    goto WriteXBit0;
}

/*
        *****************************************
        *
        *           Draw Bitmap 2 BPP
        *           no optimizations
        *
        *****************************************
*/

#if (LCD_MAX_LOG_COLORS > 2)

static void  DrawBitLine2BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixels;
/*
// Jump to right entry point
*/
  pixels = *p;
  if (pTrans) {
    /*
      with palette
    */
    if (GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) switch (Diff&3) {
    case 0:
      goto WriteTBit0;
    case 1:
      goto WriteTBit1;
    case 2:
      goto WriteTBit2;
    default:
      goto WriteTBit3;
    } else switch (Diff&3) {
    case 0:
      goto WriteBit0;
    case 1:
      goto WriteBit1;
    case 2:
      goto WriteBit2;
    default:
      goto WriteBit3;
    }
  /*
          Write without transparency
  */
  WriteBit0:
    SETPIXEL(x+0, y, *(pTrans+(pixels>>6)));
    if (!--xsize)
      return;
  WriteBit1:
    SETPIXEL(x+1, y, *(pTrans+(3&(pixels>>4))));
    if (!--xsize)
      return;
  WriteBit2:
    SETPIXEL(x+2, y, *(pTrans+(3&(pixels>>2))));
    if (!--xsize)
      return;
  WriteBit3:
    SETPIXEL(x+3, y, *(pTrans+(3&(pixels))));
    if (!--xsize)
      return;
    pixels = *(++p);
    x+=4;
    goto WriteBit0;
  /*
          Write with transparency
  */
  WriteTBit0:
    if (pixels&(3<<6))
      SETPIXEL(x+0, y, *(pTrans+(pixels>>6)));
    if (!--xsize)
      return;
  WriteTBit1:
    if (pixels&(3<<4))
      SETPIXEL(x+1, y, *(pTrans+(3&(pixels>>4))));
    if (!--xsize)
      return;
  WriteTBit2:
    if (pixels&(3<<2))
      SETPIXEL(x+2, y, *(pTrans+(3&(pixels>>2))));
    if (!--xsize)
      return;
  WriteTBit3:
    if (pixels&(3<<0))
      SETPIXEL(x+3, y, *(pTrans+(3&(pixels))));
    if (!--xsize)
      return;
    pixels = *(++p);
    x+=4;
    goto WriteTBit0;
  } else { 
    /* 
      without palette 
    */
    if (GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) switch (Diff&3) {
    case 0:
      goto WriteDDPTBit0;
    case 1:
      goto WriteDDPTBit1;
    case 2:
      goto WriteDDPTBit2;
    default:
      goto WriteDDPTBit3;
    } else switch (Diff&3) {
    case 0:
      goto WriteDDPBit0;
    case 1:
      goto WriteDDPBit1;
    case 2:
      goto WriteDDPBit2;
    default:
      goto WriteDDPBit3;
    }
  /*
          Write without transparency
  */
  WriteDDPBit0:
    SETPIXEL(x+0, y, (pixels>>6));
    if (!--xsize)
      return;
  WriteDDPBit1:
    SETPIXEL(x+1, y, (3&(pixels>>4)));
    if (!--xsize)
      return;
  WriteDDPBit2:
    SETPIXEL(x+2, y, (3&(pixels>>2)));
    if (!--xsize)
      return;
  WriteDDPBit3:
    SETPIXEL(x+3, y, (3&(pixels)));
    if (!--xsize)
      return;
    pixels = *(++p);
    x+=4;
    goto WriteDDPBit0;
  /*
          Write with transparency
  */
  WriteDDPTBit0:
    if (pixels&(3<<6))
      SETPIXEL(x+0, y, (pixels>>6));
    if (!--xsize)
      return;
  WriteDDPTBit1:
    if (pixels&(3<<4))
      SETPIXEL(x+1, y, (3&(pixels>>4)));
    if (!--xsize)
      return;
  WriteDDPTBit2:
    if (pixels&(3<<2))
      SETPIXEL(x+2, y, (3&(pixels>>2)));
    if (!--xsize)
      return;
  WriteDDPTBit3:
    if (pixels&(3<<0))
      SETPIXEL(x+3, y, (3&(pixels)));
    if (!--xsize)
      return;
    pixels = *(++p);
    x+=4;
    goto WriteDDPTBit0;
  }
}

#endif /* (LCD_MAX_LOG_COLORS > 2) */

/*
        *****************************************
        *
        *           Draw Bitmap 4 BPP
        *           no optimizations
        *
        *****************************************
*/

#if (LCD_MAX_LOG_COLORS > 4)

static void  DrawBitLine4BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixels;
/*
// Jump to right entry point
*/
  pixels = *p;
  if (GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) {
    if ((Diff&1) ==0)
      goto WriteTBit0;
    goto WriteTBit1;
  } else {
    if ((Diff&1) ==0)
      goto WriteBit0;
    goto WriteBit1;
  }
/*
        Write without transparency
*/
WriteBit0:
  SETPIXEL(x+0, y, *(pTrans+(pixels>>4)));
  if (!--xsize)
    return;
WriteBit1:
  SETPIXEL(x+1, y, *(pTrans+(pixels&0xf)));
  if (!--xsize)
    return;
  x+=2;
  pixels = *(++p);
  goto WriteBit0;
/*
        Write with transparency
*/
WriteTBit0:
  if (pixels>>4)
    SETPIXEL(x+0, y, *(pTrans+(pixels>>4)));
  if (!--xsize)
    return;
WriteTBit1:
  if (pixels&0xf)
    SETPIXEL(x+1, y, *(pTrans+(pixels&0xf)));
  if (!--xsize)
    return;
  x+=2;
  pixels = *(++p);
  goto WriteTBit0;
}

#endif /* (LCD_MAX_LOG_COLORS > 4) */

/*
        *****************************************
        *
        *           Draw Bitmap 8 BPP
        *           no optimizations
        *
        *****************************************
*/

#if (LCD_MAX_LOG_COLORS > 16)

static void  DrawBitLine8BPP(int x, int y, U8 const*p, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS)==0) {
    if (pTrans) {
      for (;xsize > 0; xsize--,x++,p++) {
        pixel = *p;
        SETPIXEL(x, y, *(pTrans+pixel));
      }
    } else {
      for (;xsize > 0; xsize--,x++,p++) {
        SETPIXEL(x, y, *p);
      }
    }
  } else {   /* Handle transparent bitmap */
    if (pTrans) {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          SETPIXEL(x+0, y, *(pTrans+pixel));
        }
      }
    } else {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          SETPIXEL(x+0, y, pixel);
        }
      }
    }
  }
}

#endif /* (LCD_MAX_LOG_COLORS > 16) */

/*
        *********************************************************
        *
        *           Exported, but not currently supported
        *
        *********************************************************
*/

/*
        *****************************************
        *
        *           LCD_L0_SetLUTEntry
        *
        *****************************************
*/

void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR Color) {
  Pos = Pos;
  Color = Color;
}

/*
        *********************************************************
        *
        *           Exported routines
        *
        *********************************************************
*/

/*
        *****************************************
        *
        *           LCD_L0_On
        *
        *****************************************
*/

void LCD_L0_On(void) {
  LCD_WRITECMD0(0xaf);
}

/*
        *****************************************
        *
        *           LCD_L0_Off
        *
        *****************************************
*/

void LCD_L0_Off(void) {
  LCD_WRITECMD0(0xae);
}

/*
        *****************************************
        *
        *           LCD_L0_XorPixel
        *
        *****************************************
*/

void LCD_L0_XorPixel(int x, int y) {
  XORPIXEL(x, y);
}

/*
        *****************************************
        *
        *           LCD_L0_SetPixelIndex
        *
        *****************************************
*/

void LCD_L0_SetPixelIndex(int x, int y, int ColorIndex) {
  SETPIXEL(x, y, ColorIndex);
}

/*
        *****************************************
        *
        *           LCD_L0_GetPixelIndex
        *
        *****************************************
*/

unsigned int LCD_L0_GetPixelIndex(int x, int y) {
  U8 ColorIndex = GETPIXEL(x, y);
  return ColorIndex;
}

/*
        *****************************************
        *
        *           LCD_L0_DrawPixel
        *
        *****************************************
*/

void LCD_L0_DrawPixel(int x, int y) {
  SETPIXEL(x, y, COLOR);
}

/*
        *****************************************
        *
        *           LCD_L0_DrawHLine
        *
        *****************************************
*/

void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    while (x0 <= x1) {
      XORPIXEL(x0, y);
      x0++;
    }
  } else {
    while (x0 <= x1) {
      SETPIXEL(x0, y, COLOR);
      x0++;
    }
  }
}

/*
        *****************************************
        *
        *           LCD_L0_DrawVLine
        *
        *****************************************
*/

void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    while (y0 <= y1) {
      XORPIXEL(x, y0);
      y0++;
    }
  } else {
    while (y0 <= y1) {
      SETPIXEL(x, y0, COLOR);
      y0++;
    }
  }
}

/*
        *****************************************
        *
        *           LCD_L0_FillRect
        *
        *****************************************
*/

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  for (; y0 <= y1; y0++) {
    LCD_L0_DrawHLine(x0, y0, x1);
  }
}

/*
        *****************************************
        *
        *           LCD_L0_DrawBitmap
        *
        *****************************************
*/

void LCD_L0_DrawBitmap   (int x0, int y0,
                       int xsize, int ysize,
                       int BitsPerPixel, 
                       int BytesPerLine,
                       const U8* pData, int Diff,
                       const LCD_PIXELINDEX* pTrans)
{
  int i;
  /*
     Use DrawBitLineXBPP
  */
  for (i=0; i<ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
      DrawBitLine1BPP(x0, i + y0, pData, Diff, xsize, pTrans);
      break;
    #if (LCD_MAX_LOG_COLORS > 2)
      case 2:
        DrawBitLine2BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 4)
      case 4:
        DrawBitLine4BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 16)
      case 8:
        DrawBitLine8BPP(x0, i + y0, pData, xsize, pTrans);
        break;
    #endif
    }
    pData += BytesPerLine;
  }
}

/*
        *****************************************
        *
        *           LCD_L0_SetOrg
        *
        *****************************************
*/

int OrgX, OrgY;
void LCD_L0_SetOrg(int x, int y) {
  OrgX = x;
  OrgY = y;
}

/*
        *****************************************
        *
        *           LCD_L0_Init
        *
        *****************************************
*/

int  LCD_L0_Init(void) {
  GUI_DEBUG_LOG("\nLCD_Init()");
  LCD_INIT_CONTROLLER();
  /* set cursor to illegal value */
  Page = Offset = 0xfff;
  /* clear LCD */
  {
    int pg;
    for (pg = 0; pg < ((LCD_YSIZE_PHYS + 3) >> 2); pg++) {
      int x = LCD_XSIZE_PHYS;
      WRITE_PAGE(pg);
      WRITE_OFFSET(0);
      while(x--) {
        WRITE_DATA(0);
      }
    }
  }
  /* clear aVRam */
  memset(aVRam, 0, sizeof(aVRam));
  /* turn off */
  LCD_Off();
  return 0;
}

#else

void LCD15E05(void) { } /* avoid empty object files */

#endif /* LCD_COMPILE_DRIVER */
