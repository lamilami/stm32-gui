/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : LCDDummy.C
Purpose     : Empty driver for emWin GSC
              This driver does no perform any function, but it can be
              used for 2 purposes:
              a) Satisfy all externals so an application can be
                compiled and linked in target hardware even if the
                driver is not already available
              b) Template for a starting point for a new driver.
----------------------------------------------------------------------   
Adapting to a new system (creating a new driver):
  In this case, the first step is to fill the routines 
  LCD_L0_GetPixelIndex, LCD_L0_SetPixelIndex and LCD_L0_Init with
  functionality, which is sufficient to make the hardware work.
  A second (optional) step would be to optimize higher level routines. 
----------------------------------------------------------------------   
Version-Date---Author-Explanation                                        
----------------------------------------------------------------------   
1.00.00 020417 JE     a) Changed to have only to adapt _GetPixelIndex
                         and _SetPixelIndex
0.90.00 020214 JE     a) First release
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include "LCD_0.h"            /* Defines for first display */

#if (LCD_CONTROLLER == 444) \
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

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef unsigned int  tOff;


/*********************************************************************
*
*       Macros
*
**********************************************************************
*/
#define WORDS_PER_LINE  (LCD_VXSIZE * 3 /4)

#define Y2OFF(y)    (WORDS_PER_LINE * y)

/*********************************************
*
*       Macros for MIRROR_, SWAP_ and LUT_
*
**********************************************
*/

#if (!defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) x
    #define LOG2PHYS_Y(x, y) y
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) y
    #define LOG2PHYS_Y(x, y) x
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) x
    #define LOG2PHYS_Y(x, y) LCD_YSIZE - 1 - (y)
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) LCD_YSIZE - 1 - (y)
    #define LOG2PHYS_Y(x, y) x
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) LCD_XSIZE - 1 - (x)
    #define LOG2PHYS_Y(x, y) y
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) LCD_YSIZE - 1 - (y)
    #define LOG2PHYS_Y(x, y) x
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define LOG2PHYS_X(x, y) LCD_XSIZE - 1 - (x)
    #define LOG2PHYS_Y(x, y) LCD_YSIZE - 1 - (y)
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #error This combination of mirroring/swapping not yet supported
  #endif
#else
  #if   ( defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) x
    #define LOG2PHYS_Y(x, y) LCD__aLine2Com0[y]
  #elif (!defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) LCD__aCol2Seg0[x]
    #define LOG2PHYS_Y(x, y) y
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

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
#if defined(WIN32)
  void SIM_WriteMem16(unsigned int Off, int Data);
  int  SIM_ReadMem16(unsigned int Off);

  #undef  LCD_READ_MEM16
  #undef  LCD_WRITE_MEM16

  #define  LCD_READ_MEM16(Off)        SIM_ReadMem16(Off)
  #define  LCD_WRITE_MEM16(Off, Data) SIM_WriteMem16(Off, Data)
#endif

/*********************************************
*
*       Draw Bitmap 1 BPP
*
**********************************************
*/

static void  _DrawBitLine1BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
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

/*********************************************
*
*       Draw Bitmap 2 BPP
*
**********************************************
*/

#if (LCD_MAX_LOG_COLORS > 2)
static void  _DrawBitLine2BPP(int x, int y, U8 const * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
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
static void  _DrawBitLine4BPP(int x, int y, U8 const * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
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
*       Draw Bitmap 8 BPP
*
**********************************************
*/

#if (LCD_MAX_LOG_COLORS > 16)
static void  _DrawBitLine8BPP(int x, int y, U8 const * p, int xsize, const LCD_PIXELINDEX * pTrans) {
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

/*********************************************
*
*       Draw Bitmap 16 BPP
*
**********************************************
*/

#if (LCD_BITSPERPIXEL > 8)
static void  DrawBitLine16BPP(int x, int y, U16 const * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) == 0) {
    if (pTrans) {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        LCD_L0_SetPixelIndex(x, y, *(pTrans + pixel));
      }
    } else {
      for (;xsize > 0; xsize--, x++, p++) {
        LCD_L0_SetPixelIndex(x, y, *p);
      }
    }
  } else {
    if (pTrans) {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          LCD_L0_SetPixelIndex(x, y, *(pTrans + pixel));
        }
      }
    } else {
      for (; xsize > 0; xsize--, x++, p++) {
        pixel = *p;
        if (pixel) {
          LCD_L0_SetPixelIndex(x, y, pixel);
        }
      }
    }
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
Purpose:
  Sets the index of the given pixel. The upper layers of emWin
  calling this routine make sure that the coordinates are in range, so
  that no check on the parameters needs to be performed.
*/

void LCD_L0_SetPixelIndex(int x, int y, int PixelIndex) {
  unsigned Off;
  U16 Data;
  /* Convert logical into physical coordinates (Dep. on LCDConf.h) */
  #if LCD_SWAP_XY | LCD_MIRROR_X| LCD_MIRROR_Y
    int xPhys = LOG2PHYS_X(x, y);
    int yPhys = LOG2PHYS_Y(x, y);
  #else
    #define xPhys x
    #define yPhys y
  #endif
  /* Write into hardware ... Adapt to your system */
  {
    Off = Y2OFF(yPhys);
    Off += 3 * x/4;
    switch (x&3) {
    case 0:
      Data = LCD_READ_MEM16(Off);
      Data &= 0xf000;
      Data |= PixelIndex;
      LCD_WRITE_MEM16(Off, Data);
      break;
    case 1:;
      Data = LCD_READ_MEM16(Off);
      Data &= 0xfff;
      Data |= (U16)(PixelIndex << 12);
      LCD_WRITE_MEM16(Off, Data);
      Off++;
      Data = LCD_READ_MEM16(Off);
      Data &= 0xff00;
      Data |= PixelIndex>>4;
      LCD_WRITE_MEM16(Off, Data);
      break;
    case 2:;
      Data = LCD_READ_MEM16(Off);
      Data &= 0xff;
      Data |= (U16)(PixelIndex << 8);
      LCD_WRITE_MEM16(Off, Data);
      Off++;
      Data = LCD_READ_MEM16(Off);
      Data &= 0xfff0;
      Data |= PixelIndex>>8;
      LCD_WRITE_MEM16(Off, Data);
      break;
    case 3:;
      Data = LCD_READ_MEM16(Off);
      Data &= 0xf;
      Data |= PixelIndex << 4;
      LCD_WRITE_MEM16(Off, Data);
      break;
    }
    /* ... */
  }
}

/*********************************************
*
*       LCD_L0_GetPixelIndex
*
**********************************************
Purpose:
  Returns the index of the given pixel. The upper layers of emWin
  calling this routine make sure that the coordinates are in range, so
  that no check on the parameters needs to be performed.
*/

unsigned int LCD_L0_GetPixelIndex(int x, int y) {
  LCD_PIXELINDEX PixelIndex;
  U16 Data0, Data1;
  unsigned Off;
  /* Convert logical into physical coordinates (Dep. on LCDConf.h) */
  #if LCD_SWAP_XY | LCD_MIRROR_X| LCD_MIRROR_Y
    int xPhys = LOG2PHYS_X(x, y);
    int yPhys = LOG2PHYS_Y(x, y);
  #else
    #define xPhys x
    #define yPhys y
  #endif
  /* Write into hardware ... Adapt to your system */
  {
    Off = Y2OFF(yPhys);
    Off += 3 * x/4;
    switch (x&3) {
    case 0:
      PixelIndex = LCD_READ_MEM16(Off) & 0xfff;
      break;
    case 1:
      Data0 = LCD_READ_MEM16(Off);
      Off++;
      Data1 = LCD_READ_MEM16(Off);
      PixelIndex  = Data0 >> 12;
      PixelIndex |= (Data1 & 255) << 4;
      break;
    case 2:
      Data0 = LCD_READ_MEM16(Off);
      Off++;
      Data1 = LCD_READ_MEM16(Off);
      PixelIndex  = Data0 >> 8;
      PixelIndex |= (Data1 & 15) << 8;
      break;
    case 3:
      PixelIndex = LCD_READ_MEM16(Off);
      PixelIndex >>= 4;
      break;
    }
  }
  return PixelIndex;
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
*       LCD_L0_DrawHLine
*
**********************************************
*/

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

/*********************************************
*
*       LCD_L0_DrawVLine
*
**********************************************
*/

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

/*********************************************
*
*       LCD_L0_FillRect
*
**********************************************
*/

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  for (; y0 <= y1; y0++) {
    LCD_L0_DrawHLine(x0, y0, x1);
  }
}

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
  /* Use _DrawBitLineXBPP */
  for (i=0; i<ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
      _DrawBitLine1BPP(x0, i + y0, pData, Diff, xsize, pTrans);
      break;
      case 2:
        _DrawBitLine2BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
      case 4:
        _DrawBitLine4BPP(x0, i + y0, pData, Diff, xsize, pTrans);
        break;
      case 8:
        _DrawBitLine8BPP(x0, i + y0, pData, xsize, pTrans);
        break;
      case 16:
        DrawBitLine16BPP(x0, i + y0, (const U16 *)pData, xsize, pTrans);
        break;
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
  LCD_INIT_CONTROLLER();
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

void LCD444_c(void) { } /* avoid empty object files */

#endif /* (LCD_CONTROLLER undefined) */
