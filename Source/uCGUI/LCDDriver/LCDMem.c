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
File        : LCDMem.C
Purpose     : Driver for LCDs using internal memory
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
2.00a   010926 JE     a) Reworked to work with LCD_MIRROR_...
                         and LCD_SWAP_XY
2.00    010402 RS     a) LCD_GetDevCaps removed from driver
                         (now LCD.c)
1.00.04 990930 RS     Prototyp changed for LCD_Init()
1.00.03 990927 RS     Config defaults added
1.00.02 990925 RS     Bugfix for transparent 4 color bitmaps
1.00.01 990920 RS     Bugfix for DrawHline
1.00    990823 RS     Xor accelerated.
0.00    990118 RS     First release. 
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
None.
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>             /* for memset */
#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include "LCD_0.h"            /* Defines for first display */

#if ((LCD_CONTROLLER   == 0) && ((LCD_FIXEDPALETTE==2) | (LCD_FIXEDPALETTE==1)) ) \
      && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))


#define LCD_BYTESPERLINE (((LCD_VXSIZE_PHYS)+7)/8)
				
#ifndef LCD_VRAMTYPE
  #define LCD_VRAMTYPE
#endif

#ifdef WIN32
  #undef LCD_VRAMTYPE
  #define LCD_VRAMTYPE
#endif

LCD_VRAMTYPE U8 LCD_VRam[LCD_BITSPERPIXEL][LCD_VYSIZE_PHYS * LCD_BYTESPERLINE];



/*
  ********************************************************************
  *                                                                  *
  *            Defaults for configuration                            *
  *                                                                  *
  ********************************************************************

Please be aware that not all configuration errors can be captured !

*/
#ifndef LCD_NUM_EMPTY_LINES
  #define LCD_NUM_EMPTY_LINES 0
#endif
#ifndef LCD_REVERSEMODE_SUPPORT
  #define LCD_REVERSEMODE_SUPPORT (1)
#endif
#ifndef LCD_VERIFY
  #define LCD_VERIFY (0)
#endif

#ifndef LCD_REVERSEMODE_SUPPORT
  #define LCD_REVERSEMODE_SUPPORT (0)
#endif

#ifndef LCD_SUPPORT_VERIFY
  #define LCD_SUPPORT_VERIFY (0)
#endif

/* If disabled, selected drawmode is ignored.
   ==> XOR, REVERSE drawing not supported */
#ifndef LCD_SUPPORT_DRAWMODE
  #define LCD_SUPPORT_DRAWMODE          (1)
#endif

/* Switch support for the LCD_On, LCD_Off functions of the driver */
#ifndef  LCD_SUPPORT_ONOFF
  #define  LCD_SUPPORT_ONOFF            (1)
#endif

/* Switch for support of multiple pages.
 Only available with certain LCD-controllers */
#ifndef LCD_SUPPORT_PAGING
  #define LCD_SUPPORT_PAGING            (0)
#endif

/* Switch for support of run-time inversion of display. */
#ifndef LCD_SUPPORT_REVERSEMODE
  #define LCD_SUPPORT_REVERSEMODE       (0)
#endif

/* Switch support for the LCD_SetOrg function of the driver */
#ifndef LCD_SUPPORT_SETORG
  #define LCD_SUPPORT_SETORG            (1)
#endif

#ifndef LCD_SUPPORT_PALETTE
  #define LCD_SUPPORT_PALETTE            (1)
#endif

#ifndef LCD_SCHEDULE_CNT
  #define LCD_SCHEDULE_CNT        (0)
#endif


/*
  ********************************************************************
  *                                                                  *
  *                SCHEDULING                                        *
  *                                                                  *
  ********************************************************************
*/


#if (LCD_SCHEDULE_CNT !=0)
  static int ScheduleCntRem=LCD_SCHEDULE_CNT;
  #define CHECK_SCHEDULE(PixelCnt)                              \
          if ((ScheduleCntRem-=(PixelCnt)) <=0) {               \
            ScheduleCntRem=LCD_SCHEDULE_CNT;			\
            LCD_SCHEDULE();                                     \
          }
#else
  #define CHECK_SCHEDULE(PixelCnt)
#endif


/*
  ********************************************************************
  *                                                                  *
  *                Support for Segment/COMLUTs                       *
  *                                                                  *
  ********************************************************************
*/

/* For compatibility with older configs, define defaults */
#ifndef LCD_SUPPORT_COMTRANS
  #define LCD_SUPPORT_COMTRANS 0
#endif
#ifndef LCD_SUPPORT_SEGTRANS
  #define LCD_SUPPORT_SEGTRANS 0
#endif

#if LCD_SUPPORT_COMTRANS
  extern U8 LCD__aLine2Com0[LCD_LASTCOM0-LCD_FIRSTCOM0+1];
#endif

#if LCD_SUPPORT_SEGTRANS
  extern U8 LCD__aRow2Seg0[LCD_LASTSEG0-LCD_FIRSTSEG0+1];
#endif


/*
  ********************************************************************
  *                                                                  *
  *                 Macro calculations                               *
  *                                                                  *
  ********************************************************************
*/

/* Define number of used coms/segments per controller */
#define LCD_NUM_SEGS0 (LCD_LASTSEG0-LCD_FIRSTSEG0+1)
#define LCD_NUM_COMS0 (LCD_LASTCOM0-LCD_FIRSTCOM0+1)
/* Define total number of used coms/segments */
#define LCD_NUM_SEGS LCD_NUM_SEGS0
#define LCD_NUM_COMS LCD_NUM_COMS0

#define LCD_MEMSIZE LCD_VXSIZE_PHYS*(LCD_VYSIZE_PHYS+LCD_NUM_EMPTY_LINES)

/*
  ********************************************************************
  *                                                                  *
  *            Configuration switch checking                         *
  *                                                                  *
  ********************************************************************

Please be aware that not all configuration errors can be captured !

*/

#if (LCD_BITSPERPIXEL != 2) & (LCD_BITSPERPIXEL != 1)
  #error this value for LCD_BITSPERPIXEL not yet supported
#endif

/* Check if number of segments / coms equals resolution */
/*
#if (LCD_NUM_SEGS < LCD_XSIZE_PHYS)
  #error Please check segment setup of controller 0 and X/YSIZE !!!
#endif
#if (LCD_NUM_COMS < LCD_YSIZE_PHYS)
  #error Please check com setup of controller 0 and X/YSIZE !!!
#endif
*/

/*
  ********************************************************************
  *                                                                  *
  *       EXPORTs for ISR                                            *
  *                                                                  *
  ********************************************************************
*/
#ifndef LCD_TIMERINIT1
  #define LCD_TIMERINIT1  1599
#endif
#ifndef LCD_TIMERINIT0
  #define LCD_TIMERINIT0  1065
#endif

U16 LCD__BitsPerPixel = LCD_BITSPERPIXEL;

LCD_VRAMTYPE U8 LCD_VRAMTYPE* LCD__apVRam[LCD_BITSPERPIXEL];

LCD_VRAMTYPE U16 LCD__aTimerReload[LCD_BITSPERPIXEL] = {
  LCD_TIMERINIT0
#if LCD_BITSPERPIXEL > 1
  ,LCD_TIMERINIT1
#endif
};

/*
  ********************************************************************
  *                                                                  *
  *       Standard variables for driver                              *
  *                                                                  *
  ********************************************************************
*/

#define PIXELCOLOR U8

#define BKCOLOR LCD_BKCOLORINDEX
#define   COLOR LCD_COLORINDEX


/*
  ********************************************************************
  *
  *                  ID translation table
  *
  ********************************************************************

This table contains 0, 1, 2, ... and serves as translation table for DDBs

*/

#define INTS(Base)  Base+0,Base+1,Base+2,Base+3,Base+4,Base+5,   \
                    Base+6,Base+7,Base+8,Base+9,Base+10,Base+11, \
                    Base+12,Base+13,Base+14,Base+15

static const LCD_PIXELINDEX aID[] = {
  INTS(0),
  #if LCD_MAX_LOG_COLORS > 0x10
    INTS(0x10),
  #endif
  #if LCD_MAX_LOG_COLORS > 0x20
    INTS(0x20),
    INTS(0x30),
  #endif
};

/*
        *********************************************************
        *                                                       *
        *       Macros for internal use                         *
        *                                                       *
        *********************************************************
*/


#if (LCD_SUPPORT_COMTRANS)
  #if (LCD_MIRROR_Y)
    #error LCD_MIRROR_Y not supported with COMTrans !
  #endif
  #if (LCD_MIRROR_X)
    #error LCD_MIRROR_X not supported with COMTrans !
  #endif
#endif

#if (!LCD_SUPPORT_COMTRANS && !LCD_SUPPORT_SEGTRANS)
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS((x), (y), (c))
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS((x), (y), (c))
    #define GETPIXEL(x, y)         _GetPixel   ((x), (y))
    #define XORPIXEL(x, y)         XorPixel    ((x), (y))
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS((y), (x), (c))
    #define GETPIXEL(x, y)         _GetPixel   ((y), (x))
    #define XORPIXEL(x, y)         XorPixel    ((y), (x))
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS((x), (LCD_YSIZE-1-(y)), (c))
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS((x), (LCD_YSIZE-1-(y)), (c))
    #define GETPIXEL(x, y)         _GetPixel   ((x), (LCD_YSIZE-1-(y)))
    #define XORPIXEL(x, y)         XorPixel    ((x), (LCD_YSIZE-1-(y)))
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS((LCD_YSIZE-1-(y)), (x), (c))
    #define GETPIXEL(x, y)         _GetPixel   ((LCD_YSIZE-1-(y)), (x))
    #define XORPIXEL(x, y)         XorPixel    ((LCD_YSIZE-1-(y)), (x))
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS((LCD_XSIZE-1-(x)), (y), (c))
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS((LCD_XSIZE-1-(x)), (y), (c))
    #define GETPIXEL(x, y)         _GetPixel   ((LCD_XSIZE-1-(x)), (y))
    #define XORPIXEL(x, y)         XorPixel    ((LCD_XSIZE-1-(x)), (y))
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS((y), (LCD_XSIZE-1-(x)), (c))
    #define GETPIXEL(x, y)         _GetPixel   ((y), (LCD_XSIZE-1-(x)))
    #define XORPIXEL(x, y)         XorPixel    ((y), (LCD_XSIZE-1-(x)))
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS((LCD_XSIZE-1-(x)), (LCD_YSIZE-1-(y)), (c))
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS((LCD_XSIZE-1-(x)), (LCD_YSIZE-1-(y)), (c))
    #define GETPIXEL(x, y)         _GetPixel   ((LCD_XSIZE-1-(x)), (LCD_YSIZE-1-(y)))
    #define XORPIXEL(x, y)         XorPixel    ((LCD_XSIZE-1-(x)), (LCD_YSIZE-1-(y)))
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #error This combination of mirroring/swapping not yet supported
  #endif
#elif (LCD_SUPPORT_COMTRANS && !LCD_SUPPORT_SEGTRANS)
  #if (!LCD_SWAP_XY)
    #define SETPIXEL(x, y, c)      SetPixelPhys(x,LCD__aLine2Com0[y], c)
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS(x,LCD__aLine2Com0[y], c)
    #define GETPIXEL(x, y)     _GetPixel(x,LCD__aLine2Com0[y])
    #define XORPIXEL(x, y)      XorPixel(x,LCD__aLine2Com0[y])
  #else
    #define SETPIXEL(x, y, c)      SetPixelPhys(y,LCD__aLine2Com0[x], c)
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS(y,LCD__aLine2Com0[x], c)
    #define GETPIXEL(x, y)     _GetPixel(y,LCD__aLine2Com0[x])
    #define XORPIXEL(x, y)      XorPixel(y,LCD__aLine2Com0[x])
  #endif
#else
  #error This combination of switches not yet supported
#endif




/*
        *********************************************************
        *                                                       *
        *       Internal set pixel routines                     *
        *                                                       *
        *********************************************************
*/

#if LCD_BITSPERPIXEL == 1
  #define SETPIXELPHYS(x,y,c)                       \
  {                                                 \
    unsigned int Off = y*LCD_BYTESPERLINE+((x)>>3);	  \
    U8 Data = 0x80>>((x)&7);						              \
    if (c&1) LCD_VRam[0][Off] |=  Data;				      \
    else     LCD_VRam[0][Off] &= ~Data;				      \
  }
#elif LCD_BITSPERPIXEL == 2
  #define SETPIXELPHYS(x,y,c)                       \
  {                                                 \
    unsigned int Off = y*LCD_BYTESPERLINE+((x)>>3);	  \
    U8 Data = 0x80>>((x)&7);						              \
    if (c&1) LCD_VRam[0][Off] |=  Data;				      \
    else     LCD_VRam[0][Off] &= ~Data;				      \
    if (c&2) LCD_VRam[1][Off] |=  Data;				      \
    else     LCD_VRam[1][Off] &= ~Data;             \
  }
#else
  #error unsupported Configuration
#endif


static void SetPixelPhys(int x, int y, PIXELCOLOR c) {
  SETPIXELPHYS(x,y,c);
}

static U8 _GetPixel(int x, int y) {
#if LCD_BITSPERPIXEL == 1
  unsigned int Off = y*LCD_BYTESPERLINE+(x>>3);
  U8 Data  = (LCD_VRam[0][Off] >> (7-(x&7))) &1;
  return Data;
#elif LCD_BITSPERPIXEL == 2
  unsigned int Off = y*LCD_BYTESPERLINE+(x>>3);
  U8 Data  = (LCD_VRam[0][Off] >> (7-(x&7))) &1;
  Data |= ((LCD_VRam[1][Off] >> (7-(x&7)))<<1) &2;
  return Data;
#else
  #error Colordepth not supported by this driver !
#endif
}


static void XorPixel   (int x, int y) {
  PIXELCOLOR Index = _GetPixel(x,y);
  Index = LCD_NUM_COLORS-1-Index;
  SetPixelPhys(x,y,Index);
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


unsigned int LCD_L0_GetPixelIndex(int x, int y) {
  return GETPIXEL(x,y);
}


/*
        *********************************************************
        *                                                       *
        *          LCD_DrawLine  vertical/horizontal            *
        *          LCD_DrawRect                                 *
        *                                                       *
        *********************************************************
*/

#if (!LCD_SWAP_XY)

static const U8 aMask[] = {255,127,63,31,15,7,3,1,0};

void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  int Off0, Off1;
  U8 EndMask;
  #if LCD_MIRROR_X
  {
    int t = (LCD_XSIZE-1-(x0));
    x0 = (LCD_XSIZE-1-(x1));
    x1 = t;
  }
  #endif
  #if LCD_MIRROR_Y
    y = (LCD_YSIZE-1-(y));
  #endif
  EndMask = ~aMask[1+((x1)&7)];
  Off0 = y*LCD_BYTESPERLINE+(x0>>3);
  Off1 = y*LCD_BYTESPERLINE+(x1>>3);
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    if (Off0==Off1) {
      U8 Data = aMask[x0&7] & EndMask;
      LCD_VRam[0][Off0] ^= Data;
      #if LCD_BITSPERPIXEL == 2
        LCD_VRam[1][Off0] ^= Data;
      #endif
    } else {
      U8 Data = aMask[x0&7];
      LCD_VRam[0][Off0] ^= Data;
      #if LCD_BITSPERPIXEL == 2
        LCD_VRam[1][Off0] ^= Data;
      #endif
      for (Off0++;Off0<Off1; Off0++) {
        LCD_VRam[0][Off0] ^= 255;
        #if LCD_BITSPERPIXEL == 2
          LCD_VRam[1][Off0] ^= 255;
        #endif
      }
      LCD_VRam[0][Off0] ^= EndMask;
      #if LCD_BITSPERPIXEL == 2
        LCD_VRam[1][Off0] ^= EndMask;
      #endif
    }
  } else {
    if (Off0==Off1) {
      U8 Data = aMask[x0&7] & EndMask;
      if (COLOR &1) LCD_VRam[0][Off0] |= Data;
      else          LCD_VRam[0][Off0] &= ~Data; 
      #if LCD_BITSPERPIXEL == 2
        if (COLOR &2) LCD_VRam[1][Off0] |= Data;
        else          LCD_VRam[1][Off0] &= ~Data; 
      #endif
    } else {
      U8 Data = aMask[x0&7];
      if (COLOR &1) LCD_VRam[0][Off0] |= Data;
      else          LCD_VRam[0][Off0] &= ~Data; 
      #if LCD_BITSPERPIXEL == 2
        if (COLOR &2) LCD_VRam[1][Off0] |= Data;
        else          LCD_VRam[1][Off0] &= ~Data; 
      #endif
      while (++Off0<Off1) {
        LCD_VRam[0][Off0] = (COLOR &1) ? 255 : 0;
        #if LCD_BITSPERPIXEL == 2
          LCD_VRam[1][Off0] = (COLOR &2) ? 255 : 0;
        #endif
      }
      if (COLOR &1) LCD_VRam[0][Off0] |= EndMask;
      else          LCD_VRam[0][Off0] &= ~EndMask; 
      #if LCD_BITSPERPIXEL == 2
        if (COLOR &2) LCD_VRam[1][Off0] |= EndMask;
        else          LCD_VRam[1][Off0] &= ~EndMask; 
      #endif
    }
  }
}

#else

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

#endif

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
  PIXELCOLOR pixels;
  PIXELCOLOR Index0 = *(pTrans+0);
  PIXELCOLOR Index1 = *(pTrans+1);
/*
   Jump to right entry point
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
    *********************************************
    *                                           *
    *      Draw Bitmap 2 BPP, optimized
    *                                           *
    *********************************************
*/

#if (LCD_MAX_LOG_COLORS > 2)

#if  (!LCD_SWAP_XY)

static void  DrawBitLine2BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  PIXELCOLOR pixels;
/*
   Jump to right entry point
*/
  pixels = *p;
  if (GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) {
    switch (Diff&3) {
    case 0:
      goto WriteTBit0;
    case 1:
      goto WriteTBit1;
    case 2:
      goto WriteTBit2;
    default:
      goto WriteTBit3;
    }
  } else {
    switch (Diff&3) {
    case 0:
      goto WriteBit0;
    case 1:
      goto WriteBit1;
    case 2:
      goto WriteBit2;
    default:
      goto WriteBit3;
    }
  }
/*
        Write without transparency
*/
WriteBit0:
  SETPIXELFAST(x+0, y, *(pTrans+(pixels>>6)));
  if (!--xsize)
    return;
WriteBit1:
  SETPIXELFAST(x+1, y, *(pTrans+(3&(pixels>>4))));
  if (!--xsize)
    return;
WriteBit2:
  SETPIXELFAST(x+2, y, *(pTrans+(3&(pixels>>2))));
  if (!--xsize)
    return;
WriteBit3:
  SETPIXELFAST(x+3, y, *(pTrans+(3&(pixels))));
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
    SETPIXELFAST(x+0, y, *(pTrans+(pixels>>6)));
  if (!--xsize)
    return;
WriteTBit1:
  if (pixels&(3<<4))
    SETPIXELFAST(x+1, y, *(pTrans+(3&(pixels>>4))));
  if (!--xsize)
    return;
WriteTBit2:
  if (pixels&(3<<2))
    SETPIXELFAST(x+2, y, *(pTrans+(3&(pixels>>2))));
  if (!--xsize)
    return;
WriteTBit3:
  if (pixels&(3<<0))
    SETPIXELFAST(x+3, y, *(pTrans+(3&(pixels))));
  if (!--xsize)
    return;
  pixels = *(++p);
  x+=4;
  goto WriteTBit0;
}

#else

/*
    *********************************************
    *                                           *
    *      Draw Bitmap 2 BPP, not optimized
    *                                           *
    *********************************************
*/

static void  DrawBitLine2BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixels;
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
  PIXELCOLOR pixels;
/*
   Jump to right entry point
*/
  pixels = *p;
   if (GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) {
     if ((Diff&1) ==0) {
       goto WriteBit0;
     } else {
        goto WriteBit1;
     }
   } else {
     if ((Diff&1) ==0) {
       goto WriteTBit0;
     } else {
        goto WriteTBit1;
     }
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


static void  DrawBitLine8BPP(int x, int y, U8 const*p, int xsize, const PIXELCOLOR*pTrans) {
  PIXELCOLOR Pixels;
  if (pTrans != aID) {
    do {
      Pixels = *p;
      SETPIXEL(x, y, *(pTrans + Pixels));
      xsize--;
      x++;
      p++;
    } while (xsize > 0);
  } else {
    do {
      SETPIXEL(x, y, *p);
      xsize--;
      x++;
      p++;
    } while (xsize > 0);

  }
}


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
  /* Use aID for bitmaps without palette */
  if (!pTrans) {
    pTrans = aID;
  }
  /* Use DrawBitLineXBPP */
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
    case 8:
      DrawBitLine8BPP(x0, i+y0, pData, xsize, pTrans);
      break;
    }
    pData += BytesPerLine;
  }
}



/*
        *********************************************************
        *                                                       *
        *       LCD_L0_SetOrg                                   *
        *                                                       *
        *********************************************************

Purpose:        Sets the original position of the virtual display.
                Has no function at this point with the PC-driver.
*/

#if LCD_SUPPORT_SETORG
  void LCD_L0_SetOrg(int x, int y) {
    int i;
    int Off;
    if (y>(LCD_VYSIZE_PHYS-LCD_YSIZE_PHYS))
      y = LCD_VYSIZE_PHYS-LCD_YSIZE_PHYS;
    Off = y*LCD_BYTESPERLINE+(x>>3);
    for (i=0; i<LCD_BITSPERPIXEL; i++) {
      LCD__apVRam[i] = & LCD_VRam[i][0] +Off;
    }
  }
#endif

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


/********************************************************
*
*       LCD_L0_On
*       LCD_L0_Off
*
*********************************************************
These funtions are not implemented for this driver, they
have to be in the external modul which refreshes the LCD
regularily.
*/

#ifndef WIN32


void LCD_L0_Off          (void) {
#ifdef LCD_OFF
    LCD_OFF(); 
#endif
}
#endif

#ifndef WIN32
void LCD_L0_On           (void) {
#ifdef LCD_ON
    LCD_ON(); 
#endif
}
#endif




/*
        *********************************************************
        *                                                       *
        *       LCD_L0_ReInit : Re-Init the display                *
        *                                                       *
        *********************************************************

ReInit contains all of the code that can be re-executed at any point without
changing or even disturbing what can be seen on the LCD.
Note that it is also used as a subroutine by LCD_Init().

*/


void  LCD_L0_ReInit(void) {}


/*
        *********************************************************
        *                                                       *
        *       LCD_Init : Init the display                     *
        *                                                       *
        *********************************************************
*/

int  LCD_L0_Init(void) {
  LCD_L0_Off();
  LCD_L0_ReInit();
  LCD_L0_SetOrg(0,0);
  /* Clear entire video RAM */
  LCD_L0_On();
  return 0;
}

void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR color) {
  LCD_USE_PARA(Pos);
  LCD_USE_PARA(color);
}

#else

void LCDMem(void) { } /* avoid empty object files */

#endif  /*(LCD_CONTROLLER/100 == 13) */


