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
File        : LCDWin.C
Purpose     : Driver for Simulator under Windows
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
2.00    010402 RS     a) LCD_GetDevCaps removed from driver
                         (now LCD.c)
1.30c   000529 JE     a) Interface changed
1.30b   000428 RS     a) DIB class eliminated
                      b) Internal cleanups, support for high color
1.30a   000417 RS     a) Major cleanup in DIB class
1.30    000309 RS     a) Interface change for emWIn V1.30
                         (LCD_L0_SetLUTEntry, LCD_GetDevCap)
1.10a   000121 RS     a) RECTHEIGHT, RECTWIDTH modified in order to
                         fix bug which would at some time prevent
												 displaying the first line of the display.
1.10.00 000110 RS     a) Modifications in order to make it easy to
                         implement driver in any windows program
1.04.02 991118 RS     a) additional assertion added
                         LCD_MAX_LOG_COLORS
1.04.01 991018 RS     a) Support for LCD_FIXEDPALETTE added
                         with Anitaliasing enabled
1.04.00 991013 JE/RS  a) Support for LCD_FIXEDPALETTE added
                      b) Driver now accepts the same LCDConf.h as
											   the embedded system
											c) Bugfix for ..
1.02.02 990831 RS     a) Small optimization added for 16-color bitmaps
1.02.01 990726 RS     a) Transparency support for 16-color bitmpas
                         added
1.02.00 990212 RS     a) New interface version 1.02 supported
1.00    990118 RS     First release
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
---------------------------END-OF-HEADER------------------------------
*/


#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

#include <windows.h>
#include "LCD.h"
#include "LCD_Private.h"              /* include LCDConf.h */
#include "LCDSim.h"
#include "GUI_Private.h"

#include "memory.h"

#if LCD_BITSPERPIXEL <= 8
  #define PIXELINDEX U8
#else
  #define PIXELINDEX WORD
#endif

#ifdef WIN32
  #ifndef ASSERT
    #define ASSERT(Val) \
    if (!(Val)) \
      MessageBox(NULL,"...in file "__FILE__,"Assertion failed...",MB_OK);
  #endif
#endif

#ifdef LCD_ASSERT
  #undef LCD_ASSERT
#endif
#define LCD_ASSERT(v) ASSERT(v)

#ifndef LCD_DISPLAY_INDEX
  #define LCD_DISPLAY_INDEX 0
#endif


/*
        *********************************************************
        *                                                       *
        *       Macros for internal use                         *
        *                                                       *
        *********************************************************
*/

#define SETPIXEL(x, y, c) LCDSIM_SetPixelIndex(x, y, c)
#define GETPIXEL(x, y)    LCD_GetPixel(x,y)
#define XORPIXEL(x, y)    XorPixel(x,y)

#if LCD_DISPLAY_INDEX == 1     /* Second display in a multi-display configuration */
  #define LCDSIM_SetPixelIndex  LCDSIM_1_SetPixelIndex
  #define LCDSIM_SetLUTEntry    LCDSIM_1_SetLUTEntry
#endif

/*
        *********************************************************
        *                                                       *
        *       ID translation table                            *
        *                                                       *
        *********************************************************

This table contains 0, 1, 2, ... and serves as translation table for DDBs

*/

#define INTS(Base)  Base+0,Base+1,Base+2,Base+3,Base+4,Base+5,   \
                    Base+6,Base+7,Base+8,Base+9,Base+10,Base+11, \
                    Base+12,Base+13,Base+14,Base+15

static void XorPixel   (int x, int y) {
  unsigned int Index = LCD_L0_GetPixelIndex(x,y);
  LCDSIM_SetPixelIndex(x, y, LCD_NUM_COLORS-1-Index);
}


/*
        *********************************************************
        *                                                       *
        *       LCD_L0_SetColorIndex                            *
        *       LCD_L0_SetBkColorIndex                          *
        *                                                       *
        *********************************************************
*/


#define   COLORINDEX LCD_COLORINDEX
#define BKCOLORINDEX LCD_BKCOLORINDEX

/*
        *********************************************************
        *                                                       *
        *       LCD_L0_DrawPixel                                   *
        *                                                       *
        *********************************************************

Purpose:  This routine is called by emWin. It writes 1 pixel into the
          display.

*/


void LCD_L0_DrawPixel(int x, int y) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    XORPIXEL(x, y);
  } else {
    SETPIXEL(x, y, COLORINDEX);
  }
}

/*
        *********************************************************
        *                                                       *
        *          LCD_DrawLine  vertical/horizontal            *
        *          LCD_DrawRect                                 *
        *                                                       *
        *********************************************************
*/

void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (;x0 <= x1; x0++) {
      XORPIXEL(x0, y);
    }
  } else {
//    LCDSIM_FillLine(x0,y,x1,COLORINDEX);
    for (;x0 <= x1; x0++) {
      SETPIXEL(x0, y, COLORINDEX);
    }
  }
}

void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    while (y0 <= y1) {
      XORPIXEL(x, y0);
      y0++;
    }
  } else {
    while (y0 <= y1) {
      SETPIXEL(x, y0, COLORINDEX);
      y0++;
    }
  }
}

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  for (; y0 <= y1; y0++) {
    LCD_L0_DrawHLine(x0,y0, x1);
  }
}



/*
  ***************************************************************
  *                                                             *
  *            Internal bitmap routines                         *
  *                                                             *
  ***************************************************************

*/


/*
    *********************************************
    *                                           *
    *      Draw Bitmap 1 BPP                    *
    *                                           *
    *********************************************
*/

static void  DrawBitLine1BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX Index0 = *(pTrans+0);
  LCD_PIXELINDEX Index1 = *(pTrans+1);
  x+=Diff;
/*
// Jump to right entry point
*/
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    do {
      LCDSIM_SetPixelIndex(x++,y, (*p & (0x80>>Diff)) ? Index1 : Index0);
			if (++Diff==8) {
        Diff=0;
				p++;
			}
		} while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
  		if (*p & (0x80>>Diff))
        LCDSIM_SetPixelIndex(x,y, Index1);
      x++;
			if (++Diff==8) {
        Diff=0;
				p++;
			}
		} while (--xsize);
    break;
  case LCD_DRAWMODE_XOR:;
    do {
  		if (*p & (0x80>>Diff)) {
        int Pixel = LCDSIM_GetPixelIndex(x,y);
        LCDSIM_SetPixelIndex(x,y, LCD_NUM_COLORS-1-Pixel);
      }
      x++;
			if (++Diff==8) {
        Diff=0;
				p++;
			}
		} while (--xsize);
    break;
	}
}

/*
    *********************************************
    *                                           *
    *      Draw Bitmap 2 BPP                    *
    *                                           *
    *********************************************
*/

#if (LCD_MAX_LOG_COLORS > 2)
static void  DrawBitLine2BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  PIXELINDEX pixels;
/*
// Jump to right entry point
*/
  pixels = *p;
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
}
#endif


/*
    *********************************************
    *                                           *
    *      Draw Bitmap 4 BPP                    *
    *                                           *
    *********************************************
*/
#if (LCD_MAX_LOG_COLORS > 4)
static void  DrawBitLine4BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  U8 pixels;
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
#endif

/*
    *********************************************
    *                                           *
    *      Draw Bitmap 8 BPP  (256 colors)      *
    *                                           *
    *********************************************
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
#endif

/*
    *********************************************
    *                                           *
    *      Draw Bitmap 16 BPP  (65536 colors)   *
    *                                           *
    *********************************************
*/


#if (LCD_BITSPERPIXEL > 8)
static void  DrawBitLine16BPP(int x, int y, U16 const*p, int xsize, const LCD_PIXELINDEX*pTrans) {
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
#endif

/*
        *********************************************************
        *                                                       *
        *         Universal draw Bitmap routine                 *
        *                                                       *
        *********************************************************
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
      DrawBitLine1BPP(x0, i+y0, pData, Diff, xsize, pTrans);
      break;
    #if (LCD_MAX_LOG_COLORS > 2)
      case 2:
        DrawBitLine2BPP(x0, i+y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 4)
      case 4:
        DrawBitLine4BPP(x0, i+y0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 16)
      case 8:
        DrawBitLine8BPP(x0, i+y0, pData, xsize, pTrans);
        break;
    #endif
    #if (LCD_BITSPERPIXEL > 8)
      case 16:
        DrawBitLine16BPP(x0, i+y0, (const U16 *)pData, xsize, pTrans);
        break;
    #endif
    }
    pData += BytesPerLine;
  }
}


/********************************************************
*
*       LCD_L0_SetOrg
*
*********************************************************

Purpose:        Sets the original position of the virtual display.
                Has no function at this point with the PC-driver.
*/

int OrgX, OrgY;
void LCD_L0_SetOrg(int x, int y) {
  OrgX = x;
  OrgY = y;
}

/*
        *********************************************************
        *                                                       *
        *           Support for verification                    *
        *                                                       *
        *********************************************************

The following routines are implemented, but have no functionility
at this point. The reason is that these functions are supposed
to supervise the hardware, which for obvious reasons can not be
done in a simulation.

*/
#if LCD_VERIFY
int  LCD_GetErrStat(void) {
  return 0;
}
void LCD_ClrErrStat(void) {
}
int  LCD_GetErrCnt (void) {
  return 0;
}
#endif  

/*
        *********************************************************
        *                                                       *
        *       LCD_On                                          *
        *       LCD_Off                                         *
        *                                                       *
        *********************************************************

(Not supported in Simulation)
*/

void LCD_Off          (void) {}
void LCD_On           (void) {}

/*
        *********************************************************
        *                                                       *
        *       LUT routines (lookup tables)                    *
        *                                                       *
        *********************************************************
*/
void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR color) {
  LCDSIM_SetLUTEntry(Pos, color);
}


/*
        *********************************************************
        *                                                       *
        *       LCD_Init : Init the display                     *
        *                                                       *
        *********************************************************
*/

int  LCD_L0_Init(void) {
  int x,y;
  // Create Bitmaps to simulate LCD (pages)
  for (x=0; x< LCD_XSIZE; x++)
    for (y=0; y< LCD_YSIZE; y++)
      SETPIXEL( x, y, BKCOLORINDEX);
	return 0;
}

int  LCD_L0_CheckInit(void) {
  return 0;
} 

/*
        ******************************************
        *                                        *
        *    Re-initialize LCD                   *
        *                                        *
        ******************************************

This routine is supplied for compatibility and interchangability of
"C"-sources with embedded versions of the driver. It has no real
effect in the PC-version as there is simply no need to re-initialize
the LCD since it is just simulated anyhow.
*/

void LCD_L0_ReInit       (void) {}

unsigned LCD_L0_GetPixelIndex(int x, int y)  {
  return LCDSIM_GetPixelIndex(x,y);
}

/*
        *********************************************************
        *                                                       *
        *       LCD_L0_XorPixel                                 *
        *                                                       *
        *********************************************************

Purpose:  This routine is called by emWin. It writes 1 pixel into the
          display.

*/

void LCD_L0_XorPixel(int x, int y) {
  XORPIXEL(x, y);
}


/*
        *********************************************************
        *                                                       *
        *       LCD_L0_SetPixelIndex                            *
        *                                                       *
        *********************************************************

Purpose:  This routine is called by emWin. It writes 1 pixel into the
          display.

*/

void LCD_L0_SetPixelIndex(int x, int y, int ColorIndex) {
  SETPIXEL(x, y, ColorIndex);
}


#else
  void LCDWin(void) { } /* avoid empty object files */
#endif /* defined(WIN32) && defined(LCD_USE_WINSIM) */



