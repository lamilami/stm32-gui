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
2.01a   010927 JE     a) Reworked to work with LCD_MIRROR_...
                         and LCD_SWAP_XY
2.01    010814 JE     a) Support for 6bpp added,
                         HLine & 1bpp optimized
2.00    010402 RS     a) LCD_GetDevCaps removed from driver
                         (now LCD.c)
0.92    000122 RS     _GetPixel functionality written
0.91    000121 RS     Default for LCD_VRAMTYPE defined
0.90    991205 RS     Driver accelerated
0.00    990118 RS     First release. 
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
None.
---------------------------LIST OF CONFIG SWITCHES--------------------
The following is a list of additional configuration switches for this
driver. These switches might not be listed in the manual, because
the manual mainly covers the general config switches which are
supported by all drivers.
----------------------------------------------------------------------
define ----------------------Explanation------------------------------
LCD_LSB_SHIFT                Support for both big and little endian
                             systems.
                             0 for little endian (default),
                             8 for big endian.
LCD_OPTIMIZE                 Controls the use of optimized routines.
                             If 1, several (speed) optimizations are used.
                             Default: ON (1)
LCD_VRAMTYPE                 Controls storage area of VRAM
---------------------------END-OF-HEADER------------------------------
*/

#define LCDMEMC_C

#include <string.h>             /* for memset */
#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include "LCD_0.h"            /* Defines for first display */

#ifndef LCD_VRAMTYPE
  #define LCD_VRAMTYPE
#endif



#if (LCD_CONTROLLER   == 0) && ((LCD_FIXEDPALETTE == 111) || (LCD_FIXEDPALETTE == 222)) \
      && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))



   /* Generate code only if selected ! */

#define LCD_BYTESPERLINE (3*(((LCD_VXSIZE_PHYS)+7)/8))

#ifndef WIN32
  #if   (LCD_BITSPERPIXEL == 3)
    LCD_VRAMTYPE U8 LCD_VRam[LCD_BITSPERPIXEL/3][LCD_VYSIZE_PHYS * LCD_BYTESPERLINE];
  #elif (LCD_BITSPERPIXEL == 6)
    LCD_VRAMTYPE U8 LCD_VRam_0[LCD_VYSIZE_PHYS * LCD_BYTESPERLINE];
    LCD_VRAMTYPE U8 LCD_VRam_1[LCD_VYSIZE_PHYS * LCD_BYTESPERLINE];
  #endif
#else
  U8* GetpVRam(int);
  #if   (LCD_BITSPERPIXEL == 3)
    U8* pVRam;
  #elif (LCD_BITSPERPIXEL == 6)
    U8* pVRam_0;
    U8* pVRam_1;
  #endif
#endif



/*
  ********************************************************************
  *                                                                  *
  *            Defaults for configuration                            *
  *                                                                  *
  ********************************************************************

Please be aware that not all configuration errors can be captured !

*/
#ifndef LCD_VERIFY
  #define LCD_VERIFY (0)
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

#ifndef LCD_ISRDATA
  #define LCD_ISRDATA
#endif
  
/* Bit position of least sig. byte when accessing words */
#ifndef LCD_LSB_SHIFT
  #define LCD_LSB_SHIFT                 (0)
#endif

#ifndef LCD_OPTIMIZE
  #define LCD_OPTIMIZE                (1)
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

#define BKCOLOR LCD_BKCOLORINDEX
#define   COLOR LCD_COLORINDEX

/*
  ********************************************************************
  *                                                                  *
  *            Configuration switch checking                         *
  *                                                                  *
  ********************************************************************

Please be aware that not all configuration errors can be captured !

*/

#if (LCD_BITSPERPIXEL != 3) && (LCD_BITSPERPIXEL != 6)
  #error this value for LCD_BITSPERPIXEL not yet supported
#endif

/* Check if number of segments / coms equals resolution */
#if (LCD_NUM_SEGS < LCD_XSIZE_PHYS)
/*  #error Please check segment setup of controller 0 and X/YSIZE !!!*/
#endif
#if (LCD_NUM_COMS < LCD_YSIZE_PHYS)
/*  #error Please check com setup of controller 0 and X/YSIZE !!!*/
#endif


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

LCD_ISRDATA U16 LCD__BitsPerPixel = LCD_BITSPERPIXEL/3;
LCD_ISRDATA U8 LCD_VRAMTYPE* LCD__apVRam[LCD_BITSPERPIXEL/3];
LCD_ISRDATA U16 LCD__aTimerReload[LCD_BITSPERPIXEL/3] = {
  LCD_TIMERINIT0
  #if LCD_BITSPERPIXEL/3 >1
		,LCD_TIMERINIT1
  #endif
};

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
  #if LCD_MAX_LOG_COLORS > 0x40
    INTS(0x40),
    INTS(0x50),
    INTS(0x60),
    INTS(0x70),
  #endif
  #if LCD_MAX_LOG_COLORS > 0x80
    INTS(0x80),
    INTS(0x90),
    INTS(0xa0),
    INTS(0xb0),
    INTS(0xc0),
    INTS(0xd0),
    INTS(0xe0),
    INTS(0xf0)
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
    #define SETPIXEL(x, y, c)      SETPIXELPHYS        ((x), (y), (c))
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS        ((x), (y), (c))
    #define GETPIXEL(x, y)         GetPixel            ((x), (y))
    #define XORPIXEL(x, y)         XorPixel            ((x), (y))
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS        ((y), (x), (c))
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS        ((y), (x), (c))
    #define GETPIXEL(x, y)         GetPixel            ((y), (x))
    #define XORPIXEL(x, y)         XorPixel            ((y), (x))
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS        ((x), (LCD_YSIZE-1-(y)), (c))
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS        ((x), (LCD_YSIZE-1-(y)), (c))
    #define GETPIXEL(x, y)         GetPixel            ((x), (LCD_YSIZE-1-(y)))
    #define XORPIXEL(x, y)         XorPixel            ((x), (LCD_YSIZE-1-(y)))
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS        ((LCD_YSIZE-1-(y)), (x), (c))
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS        ((LCD_YSIZE-1-(y)), (x), (c))
    #define GETPIXEL(x, y)         GetPixel            ((LCD_YSIZE-1-(y)), (x))
    #define XORPIXEL(x, y)         XorPixel            ((LCD_YSIZE-1-(y)), (x))
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS        ((LCD_XSIZE-1-(x)), (y), (c))
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS        ((LCD_XSIZE-1-(x)), (y), (c))
    #define GETPIXEL(x, y)         GetPixel            ((LCD_XSIZE-1-(x)), (y))
    #define XORPIXEL(x, y)         XorPixel            ((LCD_XSIZE-1-(x)), (y))
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS        ((y), (LCD_XSIZE-1-(x)), (c))
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS        ((y), (LCD_XSIZE-1-(x)), (c))
    #define GETPIXEL(x, y)         GetPixel            ((y), (LCD_XSIZE-1-(x)))
    #define XORPIXEL(x, y)         XorPixel            ((y), (LCD_XSIZE-1-(x)))
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)      SETPIXELPHYS        ((LCD_XSIZE-1-(x)), (LCD_YSIZE-1-(y)), (c))
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS        ((LCD_XSIZE-1-(x)), (LCD_YSIZE-1-(y)), (c))
    #define GETPIXEL(x, y)         GetPixel            ((LCD_XSIZE-1-(x)), (LCD_YSIZE-1-(y)))
    #define XORPIXEL(x, y)         XorPixel            ((LCD_XSIZE-1-(x)), (LCD_YSIZE-1-(y)))
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #error This combination of mirroring/swapping not yet supported
  #endif
#elif (LCD_SUPPORT_COMTRANS && !LCD_SUPPORT_SEGTRANS)
  #if (!LCD_SWAP_XY)
    #define SETPIXEL(x, y, c)      SetPixelPhys(x,LCD__aLine2Com0[y], c)
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS(x,LCD__aLine2Com0[y], c)
    #define GETPIXEL(x, y)     LCD_L0_GetPixelIndex(x,LCD__aLine2Com0[y])
    #define XORPIXEL(x, y)      XorPixel(x,LCD__aLine2Com0[y])
  #else
    #define SETPIXEL(x, y, c)      SetPixelPhys(y,LCD__aLine2Com0[x], c)
    #define SETPIXELFAST(x, y, c)  SETPIXELPHYS(y,LCD__aLine2Com0[x], c)
    #define GETPIXEL(x, y)     LCD_L0_GetPixelIndex(y,LCD__aLine2Com0[x])
    #define XORPIXEL(x, y)      XorPixel(y,LCD__aLine2Com0[x])
  #endif
#else
  #error This combination of switches not yet supported
#endif

#define XY2OFF(x,y) (y*LCD_BYTESPERLINE+3*(x>>3))

#ifndef WIN32
  #if   (LCD_BITSPERPIXEL == 3)
    #define OFF2PTR(Off) &LCD_VRam[0][Off]
  #elif (LCD_BITSPERPIXEL == 6)
    #define OFF2PTR_0(Off) &LCD_VRam_0[Off]
    #define OFF2PTR_1(Off) &LCD_VRam_1[Off]
  #endif
#else
  #if   (LCD_BITSPERPIXEL == 3)
    #define OFF2PTR(Off) (pVRam+Off)
  #elif (LCD_BITSPERPIXEL == 6)
    #define OFF2PTR_0(Off) (pVRam_0+Off)
    #define OFF2PTR_1(Off) (pVRam_1+Off)
  #endif
#endif





/*
        *********************************************************
        *                                                       *
        *       Internal set pixel routines                     *
        *                                                       *
        *********************************************************
*/

#if (LCD_BITSPERPIXEL == 3)

#define SETPIXELPHYS(x,y,c)                       \
{                                                 \
   U8 LCD_VRAMTYPE* p = OFF2PTR(XY2OFF(x,y));     \
  switch (x&7) {                                  \
  case 0:                                         \
    *p = (*p&~(7<<5))|(c<<5);                     \
    break;                                        \
  case 1:                                         \
    *p = (*p&~(7<<2))|(c<<2);                     \
    break;                                        \
  case 2:                                         \
    *p   = (*p&~(3))|(c>>1);                      \
    p++;                                          \
    *p = (*p &~(1<<7))|(c<<7);                    \
    break;                                        \
  case 3:                                         \
    p++;                                          \
    *p = (*p&~(7<<4))|(c<<4);                     \
    break;                                        \
  case 4:                                         \
    p++;                                          \
    *p = (*p&~(7<<1))|(c<<1);                     \
    break;                                        \
  case 5:                                         \
    p++;                                          \
    *p   = (*p&~(1))|(c>>2);                      \
    p++;                                          \
    *p = (*p &~(3<<6))|(c<<6);                    \
    break;                                        \
  case 6:                                         \
    p+=2;                                         \
    *p = (*p&~(7<<3))|(c<<3);                     \
    break;                                        \
  case 7:                                         \
    p+=2;                                         \
    *p = (*p&~(7<<0))|(c);                        \
    break;                                        \
  }                                               \
}

#elif (LCD_BITSPERPIXEL == 6)

void SetPixelPhys222(int x, int y, LCD_PIXELINDEX c) {
  U8 LCD_VRAMTYPE* p0 = OFF2PTR_0(XY2OFF(x,y));
  U8 LCD_VRAMTYPE* p1 = OFF2PTR_1(XY2OFF(x,y));
  U8 c0 = ((c & 0x20) >> 3) + ((c & 0x08) >> 2) + ((c & 0x02) >> 1);
  U8 c1 = ((c & 0x10) >> 2) + ((c & 0x04) >> 1) +  (c & 0x01);
  switch (x&7) {
  case 0:
    *p0 = (*p0&~(7<<5))|(c0<<5);
    *p1 = (*p1&~(7<<5))|(c1<<5);
    break;
  case 1:
    *p0 = (*p0&~(7<<2))|(c0<<2);
    *p1 = (*p1&~(7<<2))|(c1<<2);
    break;
  case 2:
    *p0   = (*p0&~(3))|(c0>>1);
    *p1   = (*p1&~(3))|(c1>>1);
    p0++;
    p1++;
    *p0 = (*p0 &~(1<<7))|(c0<<7);
    *p1 = (*p1 &~(1<<7))|(c1<<7);
    break;
  case 3:
    p0++;
    p1++;
    *p0 = (*p0&~(7<<4))|(c0<<4);
    *p1 = (*p1&~(7<<4))|(c1<<4);
    break;
  case 4:
    p0++;
    p1++;
    *p0 = (*p0&~(7<<1))|(c0<<1);
    *p1 = (*p1&~(7<<1))|(c1<<1);
    break;
  case 5:
    p0++;
    p1++;
    *p0   = (*p0&~(1))|(c0>>2);
    *p1   = (*p1&~(1))|(c1>>2);
    p0++;
    p1++;
    *p0 = (*p0 &~(3<<6))|(c0<<6);
    *p1 = (*p1 &~(3<<6))|(c1<<6);
    break;
  case 6:
    p0+=2;
    p1+=2;
    *p0 = (*p0&~(7<<3))|(c0<<3);
    *p1 = (*p1&~(7<<3))|(c1<<3);
    break;
  case 7:
    p0+=2;
    p1+=2;
    *p0 = (*p0&~(7<<0))|(c0);
    *p1 = (*p1&~(7<<0))|(c1);
    break;
  }
}

#define SETPIXELPHYS(x,y,c) SetPixelPhys222(x,y,c) 

#endif

static void SetPixelPhys(int x, int y, LCD_PIXELINDEX c) {
  SETPIXELPHYS(x,y,c);
}


/*
        *********************************************************
        *                                                       *
        *       Next pixel routines, optimized for 3bpp
        *                                                       *
        *********************************************************
*/

#if      (LCD_OPTIMIZE)             \
      && (!LCD_MIRROR_X)            \
      && (!LCD_MIRROR_Y)            \
      && (!LCD_SWAP_XY)             \
      && (!LCD_SUPPORT_COMTRANS)    \
      && (!LCD_SUPPORT_SEGTRANS)    \
      && (LCD_BITSPERPIXEL == 3)

static int CurPosX;
static U8 LCD_VRAMTYPE* pCurPos;

static void SetPosXY(int x, int y) {
  CurPosX = x;
  pCurPos = OFF2PTR(XY2OFF(x,y));
  switch (x&7) {
  case 3:
  case 4:
  case 5:
    pCurPos++; break;
  case 6:
  case 7:
    pCurPos+=2;
  }
}

static void SetNextPixel(LCD_PIXELINDEX c) {
  switch (CurPosX&7) {
  case 0: *pCurPos = (*pCurPos&~(7<<5))|(c<<5); break;
  case 1: *pCurPos = (*pCurPos&~(7<<2))|(c<<2); break;
  case 2: *pCurPos = (*pCurPos&~(3))|(c>>1);
           pCurPos++;
          *pCurPos = (*pCurPos &~(1<<7))|(c<<7);
           break;
  case 3: *pCurPos = (*pCurPos&~(7<<4))|(c<<4); break;
  case 4: *pCurPos = (*pCurPos&~(7<<1))|(c<<1); break;
  case 5: *pCurPos = (*pCurPos&~(1))|(c>>2);
           pCurPos++;
          *pCurPos = (*pCurPos &~(3<<6))|(c<<6);
           break;
  case 6: *pCurPos = (*pCurPos&~(7<<3))|(c<<3); break;
  case 7: *pCurPos = (*pCurPos&~(7<<0))|(c);
           pCurPos++;
           break;
  }
  CurPosX++;
}

/*
        *********************************************************
        *                                                       *
        *       Next pixel routines, optimized for 6bpp
        *                                                       *
        *********************************************************
*/

#elif    (LCD_OPTIMIZE)             \
      && (!LCD_MIRROR_X)            \
      && (!LCD_MIRROR_Y)            \
      && (!LCD_SWAP_XY)             \
      && (!LCD_SUPPORT_COMTRANS)    \
      && (!LCD_SUPPORT_SEGTRANS)    \
      && (LCD_BITSPERPIXEL == 6)

static int CurPosX;
static U8 LCD_VRAMTYPE* pCurPos_0;
static U8 LCD_VRAMTYPE* pCurPos_1;

static void SetPosXY(int x, int y) {
  CurPosX = x;
  pCurPos_0 = OFF2PTR_0(XY2OFF(x,y));
  pCurPos_1 = OFF2PTR_1(XY2OFF(x,y));
  switch (x&7) {
  case 3:
  case 4:
  case 5:
    pCurPos_0++;
    pCurPos_1++;
    break;
  case 6:
  case 7:
    pCurPos_0+=2;
    pCurPos_1+=2;
  }
}

static void SetNextPixel(LCD_PIXELINDEX c) {
  U8 c0 = ((c & 0x20) >> 3) + ((c & 0x08) >> 2) + ((c & 0x02) >> 1);
  U8 c1 = ((c & 0x10) >> 2) + ((c & 0x04) >> 1) +  (c & 0x01);
  switch (CurPosX&7) {
  case 0: 
    *pCurPos_0 = (*pCurPos_0&~(7<<5))|(c0<<5); 
    *pCurPos_1 = (*pCurPos_1&~(7<<5))|(c1<<5); 
    break;
  case 1: 
    *pCurPos_0 = (*pCurPos_0&~(7<<2))|(c0<<2); 
    *pCurPos_1 = (*pCurPos_1&~(7<<2))|(c1<<2); 
    break;
  case 2: 
    *pCurPos_0 = (*pCurPos_0&~(3))|(c0>>1);
    *pCurPos_1 = (*pCurPos_1&~(3))|(c1>>1);
    pCurPos_0++;
    pCurPos_1++;
    *pCurPos_0 = (*pCurPos_0 &~(1<<7))|(c0<<7);
    *pCurPos_1 = (*pCurPos_1 &~(1<<7))|(c1<<7);
    break;
  case 3: 
    *pCurPos_0 = (*pCurPos_0&~(7<<4))|(c0<<4); 
    *pCurPos_1 = (*pCurPos_1&~(7<<4))|(c1<<4); 
    break;
  case 4: 
    *pCurPos_0 = (*pCurPos_0&~(7<<1))|(c0<<1); 
    *pCurPos_1 = (*pCurPos_1&~(7<<1))|(c1<<1); 
    break;
  case 5: 
    *pCurPos_0 = (*pCurPos_0&~(1))|(c0>>2);
    *pCurPos_1 = (*pCurPos_1&~(1))|(c1>>2);
    pCurPos_0++;
    pCurPos_1++;
    *pCurPos_0 = (*pCurPos_0 &~(3<<6))|(c0<<6);
    *pCurPos_1 = (*pCurPos_1 &~(3<<6))|(c1<<6);
    break;
  case 6: 
    *pCurPos_0 = (*pCurPos_0&~(7<<3))|(c0<<3); 
    *pCurPos_1 = (*pCurPos_1&~(7<<3))|(c1<<3); 
    break;
  case 7: 
    *pCurPos_0 = (*pCurPos_0&~(7<<0))|(c0);
    *pCurPos_1 = (*pCurPos_1&~(7<<0))|(c1);
    pCurPos_0++;
    pCurPos_1++;
    break;
  }
  CurPosX++;
}

#endif

#if (LCD_BITSPERPIXEL == 3)

unsigned int GetPixel(int x, int y) {
  U8 LCD_VRAMTYPE* p = OFF2PTR(XY2OFF(x,y));
  switch(x&7) {
    case 0: return (*p>>5);
    case 1: return (*p>>2)&7;
    case 2: return ((*p&(3   )) <<1)|(*(p+1)>>7);
    case 3: return (*(p+1)>>4) &7;
    case 4: return (*(p+1)>>1) &7;
    case 5: return ((*(p+1)&(1)) <<2)|(*(p+2)>>6);
    case 6: return (*(p+2)&(7<<3)) >>3;
  }
  return (*(p+2)&(7<<0)) >>0;
}

unsigned int LCD_L0_GetPixelIndex(int x, int y) {
  return GETPIXEL(x, y);
}

#elif (LCD_BITSPERPIXEL == 6)

unsigned int GetPixel(int x, int y) {
  U8 LCD_VRAMTYPE* p0 = OFF2PTR_0(XY2OFF(x,y));
  U8 LCD_VRAMTYPE* p1 = OFF2PTR_1(XY2OFF(x,y));
  U8 c0, c1;
  switch(x&7) {
    case 0: 
      c0 = (*p0>>5);
      c1 = (*p1>>5);
      break;
    case 1: 
      c0 = (*p0>>2)&7;
      c1 = (*p1>>2)&7;
      break;
    case 2: 
      c0 = ((*p0&3)<<1)|(*(p0+1)>>7);
      c1 = ((*p1&3)<<1)|(*(p1+1)>>7);
      break;
    case 3: 
      c0 = (*(p0+1)>>4) &7;
      c1 = (*(p1+1)>>4) &7;
      break;
    case 4: 
      c0 = (*(p0+1)>>1) &7;
      c1 = (*(p1+1)>>1) &7;
      break;
    case 5: 
      c0 = ((*(p0+1)&(1)) <<2)|(*(p0+2)>>6);
      c1 = ((*(p1+1)&(1)) <<2)|(*(p1+2)>>6);
      break;
    case 6: 
      c0 = (*(p0+2)&(7<<3)) >>3;
      c1 = (*(p1+2)&(7<<3)) >>3;
      break;
    case 7: 
      c0 = (*(p0+2)&(7<<0)) >>0;
      c1 = (*(p1+2)&(7<<0)) >>0;
      break;
  }
  return ((c0 & 0x04) << 3) + ((c0 & 0x02) << 2) + ((c0 & 0x01) << 1)
       + ((c1 & 0x04) << 2) + ((c1 & 0x02) << 1) +  (c1 & 0x01);
}

unsigned int LCD_L0_GetPixelIndex(int x, int y) {
  return GETPIXEL(x, y);
}

#endif


static void XorPixel   (int x, int y) {
  LCD_PIXELINDEX Index = GetPixel(x,y);
  Index = LCD_NUM_COLORS-1-Index;
  SetPixelPhys(x,y,Index);
}

void LCD_L0_XorPixel   (int x, int y) {
  XORPIXEL(x,y);
}

void LCD_L0_SetPixelIndex   (int x, int y, int ColorIndex) {
  SETPIXELFAST(x,y,ColorIndex);
}



/*
        *********************************************************
        *                                                       *
        *          LCD_DrawHLine optimized                      *
        *                                                       *
        *          Normal display, 3 Bpp                        *
        *                                                       *
        *********************************************************
*/

#if      (LCD_OPTIMIZE)             \
      && (!LCD_MIRROR_X)            \
      && (!LCD_MIRROR_Y)            \
      && (!LCD_SWAP_XY)             \
      && (!LCD_SUPPORT_COMTRANS)    \
      && (!LCD_SUPPORT_SEGTRANS)    \
      && (LCD_BITSPERPIXEL == 3)

static U8 MaskLeft[8][3] = {
  { 0xff, 0xff, 0xff},
  { 0x1f, 0xff, 0xff},
  { 0x03, 0xff, 0xff},
  { 0x00, 0x7f, 0xff},
  { 0x00, 0x0f, 0xff},
  { 0x00, 0x01, 0xff},
  { 0x00, 0x00, 0x3f},
  { 0x00, 0x00, 0x07}/*!!!0x0e*/
};

static U8 MaskRight[8][3] = {
  { 0xe0, 0x00, 0x00},
  { 0xfc, 0x00, 0x00},
  { 0xff, 0x80, 0x00},
  { 0xff, 0xf0, 0x00},
  { 0xff, 0xfe, 0x00},
  { 0xff, 0xff, 0xc0},
  { 0xff, 0xff, 0xf8},
  { 0xff, 0xff, 0xff}
};

static U8* GetMaskRight(int x) { return &MaskRight[(x&7)][0]; }
static U8* GetMaskLeft (int x) { return &MaskLeft[(x&7)][0]; }

void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (x0>x1) return;  /* Check if nothing to draw */
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    while (x0 <= x1) {
      XORPIXEL(x0, y);
      x0++;
    }
  } else {
    int i;
    U8 LCD_VRAMTYPE* p = OFF2PTR(XY2OFF(x0,y));
    U8* pMask = GetMaskLeft(x0);
    U8 aData[3];
    U8 aDataMasked[3];
    aData[0] = (COLOR<<5)|(COLOR<<2)|(COLOR>>1);            /* hhhgggff */
    aData[1] = (COLOR<<7)|(COLOR<<4)|(COLOR<<1)|(COLOR>>2); /* feeedddc */
    aData[2] = (COLOR<<6)|(COLOR<<3)|(COLOR);               /* ccbbbaaa */
    for (i=0; i<3; i++, pMask++) {
      aDataMasked[i] = (*(p+i) &~*pMask) | (aData[i] &*pMask);
    }
    if ((x0&~7) == (x1&~7)) {    /* Do we have to clip left and right side ? */
      U8* pMask = GetMaskRight(x1);
#if 0
      for (i=0; i<3; i++, pMask++) {
        *(p+i) = (*(p+i) &~*pMask) | (aDataMasked[i]&*pMask);
      }
#else
      *(p+0) = (*(p+0) &~*(pMask+0)) | (aDataMasked[0]&*(pMask+0));
      *(p+1) = (*(p+1) &~*(pMask+1)) | (aDataMasked[1]&*(pMask+1));
      *(p+2) = (*(p+2) &~*(pMask+2)) | (aDataMasked[2]&*(pMask+2));
#endif
      return;
    }
    *p = aDataMasked[0];
    *(p+1) = aDataMasked[1];
    *(p+2) = aDataMasked[2];
    p+=3;
    x0 = (x0&~7)+8;
/* Draw optimized portion */
    {
      int Len = (x1-x0+1)>>3;
      if (Len >0) {
        x0 += Len<<3;
        do {
          *p     = aData[0];
          *(p+1) = aData[1];
          *(p+2) = aData[2];
          p+=3;
        } while (--Len);
      }
    }
    /* Draw right portion */
    if ((x1&7)!=7) {
      U8* pMask = GetMaskRight(x1);
      for (i=0; i<3; i++, pMask++) {
        *(p+i) = (*(p+i) &~*pMask) | (aData[i]&*pMask);
      }
    }
    
  }
}

/*
        *********************************************************
        *                                                       *
        *          LCD_DrawHLine optimized                      *
        *                                                       *
        *          Normal display, 6 Bpp                        *
        *                                                       *
        *********************************************************
*/

#elif    (LCD_OPTIMIZE)             \
      && (!LCD_MIRROR_X)            \
      && (!LCD_MIRROR_Y)            \
      && (!LCD_SWAP_XY)             \
      && (!LCD_SUPPORT_COMTRANS)    \
      && (!LCD_SUPPORT_SEGTRANS)    \
      && (LCD_BITSPERPIXEL == 6)

static U8 MaskLeft[8][3] = {
  { 0xff, 0xff, 0xff},
  { 0x1f, 0xff, 0xff},
  { 0x03, 0xff, 0xff},
  { 0x00, 0x7f, 0xff},
  { 0x00, 0x0f, 0xff},
  { 0x00, 0x01, 0xff},
  { 0x00, 0x00, 0x3f},
  { 0x00, 0x00, 0x07}/*!!!0x0e*/
};

static U8 MaskRight[8][3] = {
  { 0xe0, 0x00, 0x00},
  { 0xfc, 0x00, 0x00},
  { 0xff, 0x80, 0x00},
  { 0xff, 0xf0, 0x00},
  { 0xff, 0xfe, 0x00},
  { 0xff, 0xff, 0xc0},
  { 0xff, 0xff, 0xf8},
  { 0xff, 0xff, 0xff}
};

static U8* GetMaskRight(int x) { return &MaskRight[(x&7)][0]; }
static U8* GetMaskLeft (int x) { return &MaskLeft[(x&7)][0]; }

void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (x0>x1) return;  /* Check if nothing to draw */
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    while (x0 <= x1) {
      XORPIXEL(x0, y);
      x0++;
    }
  } else {
    int i;
    U8 LCD_VRAMTYPE* p0 = OFF2PTR_0(XY2OFF(x0,y));
    U8 LCD_VRAMTYPE* p1 = OFF2PTR_1(XY2OFF(x0,y));
    U8* pMask = GetMaskLeft(x0);
    U8 aData[2][3];
    U8 aDataMasked[2][3];
    U8 c0 = ((COLOR & 0x20) >> 3) + ((COLOR & 0x08) >> 2) + ((COLOR & 0x02) >> 1);
    U8 c1 = ((COLOR & 0x10) >> 2) + ((COLOR & 0x04) >> 1) +  (COLOR & 0x01);
    aData[0][0] = (c0<<5)|(c0<<2)|(c0>>1);         /* hhhgggff */
    aData[0][1] = (c0<<7)|(c0<<4)|(c0<<1)|(c0>>2); /* feeedddc */
    aData[0][2] = (c0<<6)|(c0<<3)|(c0);            /* ccbbbaaa */
    aData[1][0] = (c1<<5)|(c1<<2)|(c1>>1);         /* hhhgggff */
    aData[1][1] = (c1<<7)|(c1<<4)|(c1<<1)|(c1>>2); /* feeedddc */
    aData[1][2] = (c1<<6)|(c1<<3)|(c1);            /* ccbbbaaa */
    for (i=0; i<3; i++, pMask++) {
      aDataMasked[0][i] = (*(p0+i) &~*pMask) | (aData[0][i] &*pMask);
      aDataMasked[1][i] = (*(p1+i) &~*pMask) | (aData[1][i] &*pMask);
    }
    if ((x0&~7) == (x1&~7)) {    /* Do we have to clip left and right side ? */
      U8* pMask = GetMaskRight(x1);
      *(p0+0) = (*(p0+0) &~*(pMask+0)) | (aDataMasked[0][0]&*(pMask+0));
      *(p0+1) = (*(p0+1) &~*(pMask+1)) | (aDataMasked[0][1]&*(pMask+1));
      *(p0+2) = (*(p0+2) &~*(pMask+2)) | (aDataMasked[0][2]&*(pMask+2));
      *(p1+0) = (*(p1+0) &~*(pMask+0)) | (aDataMasked[1][0]&*(pMask+0));
      *(p1+1) = (*(p1+1) &~*(pMask+1)) | (aDataMasked[1][1]&*(pMask+1));
      *(p1+2) = (*(p1+2) &~*(pMask+2)) | (aDataMasked[1][2]&*(pMask+2));
      return;
    }
    *p0     = aDataMasked[0][0];
    *(p0+1) = aDataMasked[0][1];
    *(p0+2) = aDataMasked[0][2];
    p0+=3;
    *p1     = aDataMasked[1][0];
    *(p1+1) = aDataMasked[1][1];
    *(p1+2) = aDataMasked[1][2];
    p1+=3;
    x0 = (x0&~7)+8;
/* Draw optimized portion */
    {
      int Len = (x1-x0+1)>>3;
      if (Len >0) {
        x0 += Len<<3;
        do {
          *p0     = aData[0][0];
          *(p0+1) = aData[0][1];
          *(p0+2) = aData[0][2];
          p0+=3;
          *p1     = aData[1][0];
          *(p1+1) = aData[1][1];
          *(p1+2) = aData[1][2];
          p1+=3;
        } while (--Len);
      }
    }
    /* Draw right portion */
    if ((x1&7)!=7) {
      U8* pMask = GetMaskRight(x1);
      for (i=0; i<3; i++, pMask++) {
        *(p0+i) = (*(p0+i) &~*pMask) | (aData[0][i]&*pMask);
        *(p1+i) = (*(p1+i) &~*pMask) | (aData[1][i]&*pMask);
      }
    }
  }
}

/*
        *********************************************************
        *                                                       *
        *          LCD_DrawHLine                                *
        *                                                       *
        *          Unoptimized                                  *
        *                                                       *
        *********************************************************
*/

#else
void LCD_L0_DrawHLine(int x0, int y,  int x1) {
  if (x0>x1) return;  /* Check if nothing to draw */
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


/*
        *********************************************************
        *                                                       *
        *          LCD_DrawVLine                                *
        *                                                       *
        *          Unoptimized                                  *
        *                                                       *
        *********************************************************
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
  LCD_PIXELINDEX pixels;
  LCD_PIXELINDEX Index0 = *(pTrans+0);
  LCD_PIXELINDEX Index1 = *(pTrans+1);
/*
// Jump to right entry point
*/
  pixels = *p;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
  case 0:
#if      (LCD_OPTIMIZE)             \
      && (!LCD_MIRROR_X)            \
      && (!LCD_MIRROR_Y)            \
      && (!LCD_SWAP_XY)             \
      && (!LCD_SUPPORT_COMTRANS)    \
      && (!LCD_SUPPORT_SEGTRANS)    \
      && ((LCD_BITSPERPIXEL == 3) || (LCD_BITSPERPIXEL == 6))
    SetPosXY(x+(Diff&7),y);
#endif
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
#if      (LCD_OPTIMIZE)             \
      && (!LCD_MIRROR_X)            \
      && (!LCD_MIRROR_Y)            \
      && (!LCD_SWAP_XY)             \
      && (!LCD_SUPPORT_COMTRANS)    \
      && (!LCD_SUPPORT_SEGTRANS)    \
      && ((LCD_BITSPERPIXEL == 3) || (LCD_BITSPERPIXEL == 6))

  WriteBit0:
    SetNextPixel((pixels&(1<<7)) ? Index1 : Index0);
    if (!--xsize) return;
  WriteBit1:
    SetNextPixel((pixels&(1<<6)) ? Index1 : Index0);
    if (!--xsize) return;
  WriteBit2:
    SetNextPixel((pixels&(1<<5)) ? Index1 : Index0);
    if (!--xsize) return;
  WriteBit3:
    SetNextPixel((pixels&(1<<4)) ? Index1 : Index0);
    if (!--xsize) return;
  WriteBit4:
    SetNextPixel((pixels&(1<<3)) ? Index1 : Index0);
    if (!--xsize) return;
  WriteBit5:
    SetNextPixel((pixels&(1<<2)) ? Index1 : Index0);
    if (!--xsize) return;
  WriteBit6:
    SetNextPixel((pixels&(1<<1)) ? Index1 : Index0);
    if (!--xsize) return;
  WriteBit7:
    SetNextPixel((pixels&(1<<0)) ? Index1 : Index0);
    if (!--xsize) return;
    x+=8;
    pixels = *(++p);
    goto WriteBit0;
#else
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
#endif
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
    *      Draw Bitmap 2 BPP                    *
    *                                           *
    *********************************************
*/

#if (LCD_MAX_LOG_COLORS > 2)
static void  DrawBitLine2BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixels;
/*
// Jump to right entry point
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
  LCD_PIXELINDEX pixels;
/*
// Jump to right entry point
*/
  pixels = *p;
   if (GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) {
     if ((Diff&1) ==0) {
       goto WriteTBit0;
     } else {
        goto WriteTBit1;
     }
   } else {
     if ((Diff&1) ==0) {
       goto WriteBit0;
     } else {
        goto WriteBit1;
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

#if (LCD_MAX_LOG_COLORS > 16)
static void  DrawBitLine8BPP(int x, int y, U8 const*p, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixels;
  do {
    pixels = *p;
    SETPIXEL(x+0, y, *(pTrans+pixels));
    x++;
    p++;
  } while (--xsize);
}
#endif


/*
    **********************************************************************
    *                                                                    *
    *             Universal draw Bitmap routine                          *
    *                                                                    *
    **********************************************************************
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
    #if (LCD_MAX_LOG_COLORS > 16)
        DrawBitLine8BPP(x0, i+y0, pData, xsize, pTrans);
    #else
        DEBUG_WARN("\nCan not display 8bpp bitmaps, please #define LCD_MAX_LOG_COLORS 256");
    #endif
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
  int Off;
  if (y>(LCD_VYSIZE_PHYS-LCD_YSIZE_PHYS))
  y = LCD_VYSIZE_PHYS-LCD_YSIZE_PHYS;
  Off = y*LCD_BYTESPERLINE+(x>>3);
  #if   (LCD_BITSPERPIXEL == 3)
  {
    int i;
    for (i=0; i<LCD_BITSPERPIXEL/3; i++) {
      #ifndef WIN32
        LCD__apVRam[i] = &LCD_VRam[i][0] +Off;
      #endif
    }
  }
  #elif (LCD_BITSPERPIXEL == 6)
    #ifndef WIN32
      LCD__apVRam[0] = &LCD_VRam_0[0] +Off;
      LCD__apVRam[1] = &LCD_VRam_1[0] +Off;
    #endif
  #endif
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



/*
        *********************************************************
        *                                                       *
        *       LCD_On                                          *
        *       LCD_Off                                         *
        *                                                       *
        *********************************************************
These funtions are not implemented for this driver, they
have to be in the external modul which refreshes the LCD
regularily.
*/

#ifndef WIN32
void LCD_Off          (void) {
#ifdef LCD_OFF
    LCD_OFF(); 
#endif
}
#endif

#ifndef WIN32
void LCD_On           (void) {
#ifdef LCD_ON
    LCD_ON(); 
#endif
}
#endif

/*
        *********************************************************
        *                                                       *
        *       LCD_ReInit : Re-Init the display                *
        *                                                       *
        *********************************************************

ReInit contains all of the code that can be re-executed at any point without
changing or even disturbing what can be seen on the LCD.
Note that it is also used as a subroutine by LCD_Init().

*/

void  LCD_ReInit(void) {
}


/*
        *********************************************************
        *                                                       *
        *       LCD_Init : Init the display                     *
        *                                                       *
        *********************************************************
*/

int  LCD_L0_Init(void) {
#ifdef WIN32
  #if   (LCD_BITSPERPIXEL == 3)
    pVRam = GetpVRam(LCD_VYSIZE_PHYS*LCD_BYTESPERLINE);
  #elif (LCD_BITSPERPIXEL == 6)
    pVRam_0 = GetpVRam(LCD_VYSIZE_PHYS*LCD_BYTESPERLINE);
    pVRam_1 = pVRam_0 + LCD_VYSIZE_PHYS * LCD_BYTESPERLINE;
  #endif
#endif
  LCD_Off();
  LCD_ReInit();
  LCD_L0_SetOrg(0,0);
  /* Clear entire video RAM */
  LCD_SetDrawMode(LCD_DRAWMODE_REV);
  LCD_FillRect(0,0,4095,4095);
  LCD_SetDrawMode(0);
  LCD_On();
  return 0;
}


/*
        *********************************************************
        *                                                       *
        *       LCD_L0_CheckInit                                   *
        *                                                       *
        *  Check if display controller(s) is/are still          *
        *  properly initialized                                 *
        *                                                       *
        *********************************************************

Return value:	0 => No error, init is O.K.
*/

int LCD_L0_CheckInit(void) {
    return 0;
}


/*
        *********************************************************
        *                                                       *
        *                   LCD_L0_SetLUTEntry                  *
        *                                                       *
        *********************************************************

*/

void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR color) {
  LCD_USE_PARA(Pos);
  LCD_USE_PARA(color);
}


#endif  /*(LCD_CONTROLLER/100 == 0) */

void LCDMemC(void) { } /* avoid empty object files */


