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
File        : LCD07X1.c
Purpose     : Driver for LCDs using K70741 controllers or compatible.
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
2.00c   020708 JE     a) Changed to work with 2bpp DDP bitmaps
2.00b   020204 JE     a) Hardwareinterface routines renamed:
                         ...DATA -> ...A1, ...CMD -> ...A0
2.00a   010924 JE     a) Bugfixes: LCD_MIRROR_X, LCD_MIRROR_Y
2.00    010402 RS     a) LCD_GetDevCaps removed from driver
                         (now LCD.c)
1.04    000925 RS     a) Support for 8bpp DDBs added
1.03    000505 JE     a) XOR mode inserted
                      b) Renamed this file from LCD0711.C -> LCD07X1.C
1.02    000329 RS     Clean up
1.01    000329 RS     Cache flushing optimized
1.00    000329 RS     First official release. Most routine are
                      optimized, cache control added.
0.00    990118 EZ/RS  First release for Motorola Israel only,
                      not configuarable, not optimized.
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
a) LCD_MIRROR_X,Y can not be used together with LCD_SWAP_XY
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */
#include <string.h> /* memset & memcpy is used in driver! */
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include "LCD_0.h"            /* Defines for first display */

#if   ((LCD_CONTROLLER == 711)|(LCD_CONTROLLER == 741)) \
      && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))



/*
        *********************************************************
        *                                                       *
        *           Defaults for configuration                  *
        *                                                       *
        *********************************************************

*/

#ifndef LCD_STATIC
  #define LCD_STATIC static
#endif

#ifndef LCD_WATCHDOG_TRIGGERCNT
  #define LCD_WATCHDOG_TRIGGERCNT 0
#endif

#ifndef LCD_KICK_WATCHDOG
  #define LCD_KICK_WATCHDOG()
#endif

#ifndef LCD_NUM_EMPTY_LINES
  #define LCD_NUM_EMPTY_LINES           (0)
#endif

#ifndef LCD_FIRSTSEG0
  #define LCD_FIRSTSEG0   (0)     /* Contr.0: first segment line used */
#endif

#ifndef LCD_LASTSEG0
  #if (!LCD_SWAP_XY)
    #define LCD_LASTSEG0    (LCD_XSIZE-1)    /* Contr.0: last segment line used */
  #else
    #define LCD_LASTSEG0    (LCD_YSIZE-1)
  #endif
#endif

#ifndef LCD_FIRSTCOM0
  #define LCD_FIRSTCOM0   (0)     /* Contr.0: first com line used */
#endif

#ifndef LCD_LASTCOM0
  #if (!LCD_SWAP_XY)
    #define LCD_LASTCOM0    (LCD_YSIZE-1)     /* Contr.0: last com line used */
  #else
    #define LCD_LASTCOM0    (LCD_XSIZE-1)     /* Contr.0: last com line used */
  #endif
#endif

#ifndef LCD_CACHE
  #define  LCD_CACHE                    (1)
#endif

#ifndef LCD_SUPPORT_REFRESH
  #define  LCD_SUPPORT_REFRESH LCD_CACHE
#endif

#ifndef LCD_REVERSEMODE_SUPPORT
  #define LCD_REVERSEMODE_SUPPORT       (0)
#endif

#ifndef LCD_SUPPORT_VERIFY
  #define LCD_SUPPORT_VERIFY            (0)
#endif


/* Switch for support of cache control (locking) */
#ifndef  LCD_SUPPORT_CACHECONTROL
  #define  LCD_SUPPORT_CACHECONTROL     LCD_CACHE
#endif

/* If disabled, selected drawmode is ignored.
   ==> XOR, REVERSE drawing not supported */
#ifndef LCD_SUPPORT_DRAWMODE
  #define LCD_SUPPORT_DRAWMODE          (1)
#endif

/* Switch for support of multiple pages.
 Only available with certain LCD-controllers */
#ifndef LCD_SUPPORT_PAGING
  #define LCD_SUPPORT_PAGING            (0)
#endif

#ifndef LCD_SCHEDULE_CNT
  #define LCD_SCHEDULE_CNT              (0)
#endif

#ifndef LCD_NUM_CONTROLLERS
  #define LCD_NUM_CONTROLLERS           (1)
#endif

#ifndef LCD_SUPPORT_CHECKINIT
  #define LCD_SUPPORT_CHECKINIT         (0)
#endif

#ifndef LCD_BUSWIDTH
  #define LCD_BUSWIDTH                  (16)
#endif

/* Bit position of least sig. byte when accessing words */
#ifndef LCD_LSB_SHIFT
  #define LCD_LSB_SHIFT                 (0)
#endif

#ifndef LCD_OPTIMIZE
  #define LCD_OPTIMIZE                (1)
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

#define BKCOLOR LCD_BKCOLORINDEX
#define   COLOR LCD_COLORINDEX
#define LCD_DrawMode GUI_Context.DrawMode

/*
        *********************************************************
        *                                                       *
        *           Compiler specific settings                  *
        *                                                       *
        *********************************************************

*/
#ifdef WIN32   /* Avoid warnings in MS-compiler */
  #pragma warning(disable : 4761)  // warning C4761: integral size mismatch in argument; conversion supplied
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
  #undef LCD_WRITEM_A1
  #undef LCD_INIT_CONTROLLER
  void SIM_WriteA1C0(U8 Data);
  void SIM_WriteA0C0(U8 cmd);
  void SIM_WriteMA1C0(U8*pData, int NumBytes);
  #define LCD_WRITE_A0(cmd)              SIM_WriteA0C0(cmd)
  #define LCD_WRITE_A1(Data)             SIM_WriteA1C0(Data) 
  #define LCD_WRITEM_A1(Data, NumBytes)  SIM_WriteMA1C0(Data, NumBytes)
  #define LCD_INIT_CONTROLLER()
#endif

/*********************************************************************
*
*                Remap ...A0, ...A1 -> ...CMD, ...DATA
*
**********************************************************************
*/

#define LCD_WRITEDATA1 LCD_WRITE_A1
#define LCD_WRITEMDATA LCD_WRITEM_A1
#define LCD_WRITECMD   LCD_WRITE_A0

/*
        *********************************************************
        *                                                       *
        *          Internal types                               *
        *                                                       *
        *********************************************************
*/

/* Define number of available segments of controller */

#if (LCD_CONTROLLER == 711)
  #define LCD_SEGS_MAX  128
  #define LCD_COMS_MAX 64
#elif (LCD_CONTROLLER == 741)
  #define LCD_SEGS_MAX  128
  #define LCD_COMS_MAX  128
#else
  #error Please define a controller to use !
#endif


/*
        *********************************************************
        *                                                       *
        *          Internal types                               *
        *                                                       *
        *********************************************************
*/

#if LCD_BITSPERPIXEL <=8
  #define PIXELCOLOR U8
#elif (LCD_BITSPERPIXEL >8) && (LCD_BITSPERPIXEL < 16)
  #define PIXELCOLOR U16
#else
  #error LCD_BITSPERPIXEL > 16 not supported
#endif


/*
        *********************************************************
        *                                                       *
        *          SCHEDULING                                   *
        *                                                       *
        *********************************************************
*/

#if (LCD_SCHEDULE_CNT !=0)
  static int ScheduleCntRem=LCD_SCHEDULE_CNT;
  #define CHECK_SCHEDULE(PixelCnt)                              \
          if ((ScheduleCntRem-=(PixelCnt)) <=0) {               \
            ScheduleCntRem=LCD_SCHEDULE_CNT;                    \
            LCD_SCHEDULE();                                     \
          }
#else
  #define CHECK_SCHEDULE(PixelCnt)
#endif


/*
        *********************************************************
        *                                                       *
        *          Support for Segment/COMLUTs                  *
        *                                                       *
        *********************************************************
*/

/* For compatibility with older configs, define defaults */
#ifndef LCD_SUPPORT_COMTRANS
  #define LCD_SUPPORT_COMTRANS 0
#endif
#ifndef LCD_SUPPORT_SEGTRANS
  #define LCD_SUPPORT_SEGTRANS 0
#endif


/*
        *********************************************************
        *                                                       *
        *           Macro calculations                          *
        *                                                       *
        *********************************************************
*/

#define LCD_MSB_SHIFT       (8-LCD_LSB_SHIFT)

/* To make life easier, assign physical x/y size */
#if !LCD_SWAP_XY
  #define LCD_XSIZE_P LCD_XSIZE
  #define LCD_YSIZE_P LCD_YSIZE
  #define LCD_VXSIZE_P LCD_VXSIZE
  #define LCD_VYSIZE_P LCD_VYSIZE
#else
  #define LCD_XSIZE_P LCD_YSIZE
  #define LCD_YSIZE_P LCD_XSIZE
  #define LCD_VXSIZE_P LCD_VYSIZE
  #define LCD_VYSIZE_P LCD_VXSIZE
#endif

/* Define number of used coms/segments per controller */
#define LCD_NUM_SEGS0 (LCD_LASTSEG0-LCD_FIRSTSEG0+1)
#define LCD_NUM_COMS0 (LCD_LASTCOM0-LCD_FIRSTCOM0+1)
#if (LCD_NUM_CONTROLLERS >1)
  #define LCD_NUM_SEGS1 (LCD_LASTSEG1-LCD_FIRSTSEG1+1)
  #define LCD_NUM_COMS1 (LCD_LASTCOM1-LCD_FIRSTCOM1+1)
#endif

/* Define total number of used coms/segments */
#if (LCD_NUM_CONTROLLERS ==1)
  #define LCD_NUM_SEGS LCD_NUM_SEGS0
  #define LCD_NUM_COMS LCD_NUM_COMS0
#elif (LCD_NUM_CONTROLLERS ==2)
  #define LCD_NUM_SEGS (LCD_NUM_SEGS0+LCD_NUM_SEGS1)
  #define LCD_NUM_COMS (LCD_NUM_COMS0+LCD_NUM_COMS1)
#endif

#define LCD_MEMSIZE ((LCD_BITSPERPIXEL*LCD_VXSIZE/LCD_BUSWIDTH)*(LCD_VYSIZE+LCD_NUM_EMPTY_LINES))

#if     LCD_BITSPERPIXEL == 2              /* Add by ELIZ 19 Jan 00 */
  #define BYTESPERLINE (LCD_VXSIZE_P/4)    /* Add by ELIZ 19 Jan 00 */
  #define WORDSPERLINE (LCD_VXSIZE_P/8)    /* Add by ELIZ 19 Jan 00 */
#elif   LCD_BITSPERPIXEL == 4
  #define BYTESPERLINE (LCD_VXSIZE_P/2)
  #define WORDSPERLINE (LCD_VXSIZE_P/4)
#elif LCD_BITSPERPIXEL == 8
  #define BYTESPERLINE (LCD_VXSIZE_P)
  #define WORDSPERLINE (LCD_VXSIZE_P/2)
#elif LCD_BITSPERPIXEL == 15
  #define BYTESPERLINE (LCD_VXSIZE_P*2)
  #define WORDSPERLINE (LCD_VXSIZE_P)
#else
  #error This colordepth is not supported !!!
#endif

#define LCD_NUM_PAGES (LCD_NUM_COMS+7)/8


/*
        *********************************************************
        *                                                       *
        *      Configuration switch checking                    *
        *                                                       *
        *********************************************************

Please be aware that not all configuration errors can be captured !

*/

/* Check number of controllers */
#if ((LCD_NUM_CONTROLLERS >1) || (LCD_NUM_CONTROLLERS <0))
  #error "More than 1 controller not supported by this driver"
#endif

/* Check if number of segments / coms equals resolution */
#if (LCD_NUM_SEGS < LCD_XSIZE_P)
/*  #error Please check segment setup of controller 0 and X/YSIZE !!!*/
#endif
#if (LCD_NUM_COMS < LCD_YSIZE_P)
/*  #error Please check com setup of controller 0 and X/YSIZE !!!*/
#endif


/*
        *********************************************************
        *                                                       *
        * Standard variables for driver                         *
        *                                                       *
        *********************************************************
*/

static char CacheLocked =0;
static char CacheStat   =0;
static U8 Cache[LCD_NUM_PAGES][LCD_XSIZE_P][2];
static U8 aCacheDirty[LCD_NUM_PAGES];

#if LCD_WATCHDOG_TRIGGERCNT
  int WatchdogTriggerCnt;
#endif

#if LCD_SUPPORT_VERIFY
  static int ErrCnt;
  static int ErrStat;
#endif



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
    #define SETPIXEL(x, y, c)  _SetPixel(x, y, c)
    #define GETPIXEL(x, y)     _GetPixel(x,y)
    #define XORPIXEL(x, y)     XorPixel(x,y)
    #define XORPIXEL_DATA(x, y,c)  XorPixel_Data(x,y,c)
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)  _SetPixel(y, x, c)
    #define GETPIXEL(x, y)     _GetPixel(y, x)
    #define XORPIXEL(x, y)      XorPixel(y, x)
    #define XORPIXEL_DATA(x, y,c)  XorPixel_Data(y,x,c)
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)  _SetPixel(x, LCD_YSIZE-1-(y), c)
    #define GETPIXEL(x, y)     _GetPixel(x, LCD_YSIZE-1-(y))
    #define XORPIXEL(x, y)     XorPixel (x, LCD_YSIZE-1-(y))
    #define XORPIXEL_DATA(x, y,c)  XorPixel_Data(x,LCD_YSIZE-1-(y),c)
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)  _SetPixel(LCD_YSIZE-1-(y), x, c)
    #define GETPIXEL(x, y)     _GetPixel(LCD_YSIZE-1-(y), x)
    #define XORPIXEL(x, y)      XorPixel(LCD_YSIZE-1-(y), x)
    #define XORPIXEL_DATA(x, y,c)  XorPixel_Data(LCD_YSIZE-1-(y),x,c)
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)  _SetPixel(LCD_XSIZE-1-(x), y, c)
    #define GETPIXEL(x, y)     _GetPixel(LCD_XSIZE-1-(x), y)
    #define XORPIXEL(x, y)     XorPixel (LCD_XSIZE-1-(x), y)
    #define XORPIXEL_DATA(x, y,c)  XorPixel_Data(LCD_XSIZE-1-(x),y,c)
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #error This combination of mirroring/swapping not yet supported
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)  _SetPixel(LCD_XSIZE-1-(x), LCD_YSIZE-1-(y), c)
    #define GETPIXEL(x, y)     _GetPixel(LCD_XSIZE-1-(x), LCD_YSIZE-1-(y))
    #define XORPIXEL(x, y)     XorPixel (LCD_XSIZE-1-(x), LCD_YSIZE-1-(y))
    #define XORPIXEL_DATA(x, y,c)  XorPixel_Data(LCD_XSIZE-1-(x), LCD_YSIZE-1-(y),c)
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #error This combination of mirroring/swapping not yet supported
  #endif
#elif (LCD_SUPPORT_COMTRANS && !LCD_SUPPORT_SEGTRANS)
  #if (!LCD_SWAP_XY)
    #define SETPIXEL(x, y, c)  _SetPixel(x,LCD__aLine2Com0[y], c)
    #define GETPIXEL(x, y)     _GetPixel(x,LCD__aLine2Com0[y])
    #define XORPIXEL(x, y)      XorPixel(x,LCD__aLine2Com0[y])
  #else
    #define SETPIXEL(x, y, c)  _SetPixel(y,LCD__aLine2Com0[x], c)
    #define GETPIXEL(x, y)     _GetPixel(y,LCD__aLine2Com0[x])
    #define XORPIXEL(x, y)      XorPixel(y,LCD__aLine2Com0[x])
  #endif
#elif (!LCD_SUPPORT_COMTRANS && LCD_SUPPORT_SEGTRANS)
  #if (!LCD_SWAP_XY)
    #define SETPIXEL(x, y, c)  _SetPixel(LCD__aRow2Seg0[x],y, c)
    #define GETPIXEL(x, y)     _GetPixel(LCD__aRow2Seg0[x],y)
    #define XORPIXEL(x, y)      XorPixel(LCD__aRow2Seg0[x],y)
  #else
    #define SETPIXEL(x, y, c)  _SetPixel(LCD__aRow2Seg0[y],x, c)
    #define GETPIXEL(x, y)     _GetPixel(LCD__aRow2Seg0[y],x)
    #define XORPIXEL(x, y)      XorPixel(LCD__aRow2Seg0[y],x)
  #endif
#elif (LCD_SUPPORT_COMTRANS && LCD_SUPPORT_SEGTRANS)
  #if (!LCD_SWAP_XY)
    #define SETPIXEL(x, y, c)  _SetPixel(LCD__aRow2Seg0[x],LCD__aLine2Com0[y], c)
    #define GETPIXEL(x, y)     _GetPixel(LCD__aRow2Seg0[x],LCD__aLine2Com0[y])
    #define XORPIXEL(x, y)      XorPixel(LCD__aRow2Seg0[x],LCD__aLine2Com0[y])
  #else
    #define SETPIXEL(x, y, c)  _SetPixel(LCD__aRow2Seg0[y],LCD__aLine2Com0[x], c)
    #define GETPIXEL(x, y)     _GetPixel(LCD__aRow2Seg0[y],LCD__aLine2Com0[x])
    #define XORPIXEL(x, y)      XorPixel(LCD__aRow2Seg0[y],LCD__aLine2Com0[x])
  #endif
#else
  #error This combination of switches not yet supported
#endif


/*
        *********************************************************
        *                                                       *
        *       Next pixel routines                             *
        *                                                       *
        *********************************************************
*/

#if 0 /* Not yet defined ! */
     (LCD_OPTIMIZE)             \
      && (LCD_BUSWIDTH == 8)        \
      && (LCD_MIRROR_X)             \
      && (!LCD_MIRROR_Y)            \
      && (LCD_SWAP_XY)              \
      && (!LCD_SUPPORT_COMTRANS)    \
      && (!LCD_SUPPORT_SEGTRANS)    \
      && (LCD_BITSPERPIXEL == 4)

static int CurPosY;    /* Physical x position !!! */
static int CurOff;

static void SetPosXY(int x, int y) {
  y = LCD_YSIZE-1-y;
  CurPosY = y;
  CurOff = XY2OFF(y,x);
}

static void SetNextPixel(PIXELCOLOR c) {
  U8 Data = LCD_READ_MEM(Off);
  if (CurPosY&1) {
    Data = (Data & ~(15<<0)) | (c<<0);
    CurOff++;
  } else {
    Data = (Data & ~(15<<4)) | (c<<4);
  }
  LCD_WRITE_MEM(Off, Data);
  CurPosY++;
}

#define SETNEXTPIXEL(c) SetNextPixel(c)
#endif


/*
        *********************************************************
        *                                                       *
        *       Palette info                                    *
        *                                                       *
        *********************************************************

The following are "sample" palettes. You might have to create
a table yourself containing the entries corresponding to the
colors which your LCD can display.

*/

#if (LCD_FIXEDPALETTE==0)
  static const LCD_COLOR PhysColors[] = {
    #if (LCD_REVERSE)
      #if   (LCD_BITSPERPIXEL == 1)                   /* black/white */
        0xffffff, 0x000000
      #elif (LCD_BITSPERPIXEL == 2)                   /* 4 gray scales */
        0xffffff, 0xaaaaaa, 0x555555, 0x000000
      #endif
    #else
      #if   (LCD_BITSPERPIXEL == 1)                   /* black/white */
        0x000000, 0xffffff
      #elif (LCD_BITSPERPIXEL == 2)                   /* 4 gray scales */
        0x000000, 0x555555, 0xaaaaaa, 0xffffff
      #endif
    #endif
  };
#endif


/*
        *********************************************************
        *                                                       *
        *                   LCD_SetPaletteEntry                 *
        *                                                       *
        *********************************************************

*/

void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR color) {
  Pos=Pos;
  color=color;
}


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

static const PIXELCOLOR TransId[] = {
  INTS(0*16)
};


/*
  ********************************************************************
  *                                                                  *
  *                  Hardware access, register level                 *
  *                                                                  *
  *           Write Page / Column                                    *
  *                                                                  *
  ********************************************************************

 The following routines are used for all access to the
 LCD-controller(s).

*/

static U8 PageCache, ColCache;            /* Page / column of cache byte */


/*
        *****************************************
        *                                       *
        *         Set Column routines           *
        *                                       *
        *****************************************

These routines set the page-register of their respective
LCD-controller. Note that page is not what you might imagine,
but is a section of the controllers internal video RAM.
For details, please refer to the datasheet.

*/

#define SETCOL(col) {                                             \
  if (ColCache != col) {                                          \
    U8 temp_NewCol = 0x0+(col&15);    /* Set low nibble */        \
    LCD_WRITECMD(temp_NewCol);        /* Send low nibble */       \
    temp_NewCol = 0x10+(col>>4);   /* Set high nibble */       \
    LCD_WRITECMD(temp_NewCol);        /* Send high nibble */      \
    ColCache = col;                                            \
  }                                                               \
}

void SetCol(U8 col) {
  SETCOL(col);
}

#define SETCOL_IF_NEEDED(c) { if (c != ColCache) SETCOL(c); }


/*
        *****************************************
        *                                       *
        *         Set Page routines             *
        *                                       *
        *****************************************

These routines set the page-register of their respective
LCD-controller. Note that page is not what you might imagine,
but is a section of the controllers internal video RAM.
For details, please refer to the datasheet.

*/

#define SETPAGE(p) {              \
  U8 temp_NewPage;                \
  if (PageCache != p) {     \
    PageCache = p;          \
    temp_NewPage = 0xb0+ PageCache; \
    LCD_WRITECMD(temp_NewPage);   \
  }                               \
}

#define SETPAGE_IF_NEEDED(p) { if (p != PageCache) SETPAGE(p); }

void SetPage(U8 p) {
  SETPAGE(p);
}

#define WRITE_VMEM_PAIR(page, col, ptr)  { \
  if (!CacheLocked) {                      \
    SETPAGE_IF_NEEDED(page);               \
    SETCOL_IF_NEEDED(col);                 \
    LCD_WRITEMDATA(ptr,2);                 \
    ColCache++;                            \
  } else {                                 \
    aCacheDirty[page] = CacheStat=1;       \
  }                                        \
}


/*
        *********************************************************
        *                                                       *
        *       Internal set pixel routines                     *
        *                                                       *
        *********************************************************
*/

static void _SetPixel(int x, int y, PIXELCOLOR c) {
  U8 page = (y+LCD_FIRSTSEG0)>>3;
  U8 mask = 1<<((y+LCD_FIRSTSEG0)&7);
  U8 aData[2];
  U8* pCache = &Cache[page][x][0];
/* Read data from cache into 2 byte array */
  aData[0] = *pCache;
  aData[1] = *(pCache+1);
/* Write Data into array */
  if (c&(1<<1))
    aData[0] |= mask;
  else
    aData[0] &= ~mask;
  if (c&(1<<0))
    aData[1] |=  mask;
  else
    aData[1] &= ~mask;
/* Check if we need to write */
  if ((*pCache == aData[0]) &&  (*(pCache+1) == aData[1]))
    return;
/* Write modified data back into cache */
  *pCache    = aData[0];
  *(pCache+1) = aData[1];
/* Write data from cache into 2 byte array */
  WRITE_VMEM_PAIR(page, x, &aData[0]);
}

static PIXELCOLOR _GetPixel(int x, int y) {
  PIXELCOLOR col=0;
  U8 page = (y+LCD_FIRSTSEG0)>>3;
  U8 mask = 1<<((y+LCD_FIRSTSEG0)&7);
  if (Cache[page][x][0] & mask)
    col|=(1<<1);
  if (Cache[page][x][1] & mask)
    col|=(1<<0);
  return col;
}

static void XorPixel   (int x, int y) {
  PIXELCOLOR Index = _GetPixel(x,y);
  _SetPixel(x,y, LCD_NUM_COLORS-1-Index);
}

static void XorPixel_Data(int x, int y, PIXELCOLOR c) {
  PIXELCOLOR Index = _GetPixel(x,y);
  _SetPixel(x,y,Index^c);
}

/*
        *********************************************************
        *                                                       *
        *                  LCD_GetPixelIndex                    *
        *                                                       *
        *********************************************************
*/
unsigned LCD_L0_GetPixelIndex(int x, int y) {
  return GETPIXEL(x,y);
  /*return _GetPixel(x,y);*/
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



/*
        *********************************************************
        *                                                       *
        *          LCD_L0_DrawHLine unoptimized                    *
        *                                                       *
        *********************************************************
*/

void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  LCD_KICK_WATCHDOG();
  if (LCD_DrawMode & LCD_DRAWMODE_XOR) {
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
        *********************************************************
        *                                                       *
        *          LCD_L0_DrawVLine no optimization                *
        *                                                       *
        *********************************************************
*/

void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  LCD_KICK_WATCHDOG();
  if (LCD_DrawMode & LCD_DRAWMODE_XOR) {
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
        *********************************************************
        *                                                       *
        *          LCD_FillRect, no swap, optimized             *
        *                                                       *
        *********************************************************
*/

#if (!LCD_SWAP_XY) && (LCD_OPTIMIZE)

static const U8 aStartMask[] = { 255, 255-1, 255-3, 255-7, 255-15, 255-31, 255-63, 255-127 };
static const U8 aEndMask[] = { 1,3,7,15,31,63,127,255 };

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  U8 MaskStart, MaskEnd;
  U8 Page, Page0, Page1;
  int x;
  #if LCD_MIRROR_X
    #define X0 (LCD_XSIZE - 1 - x1)
    #define X1 (LCD_XSIZE - 1 - x0)
  #else
    #define X0 x0
    #define X1 x1
  #endif
  #if LCD_MIRROR_Y
    #define Y0 (LCD_YSIZE - 1 - y1)
    #define Y1 (LCD_YSIZE - 1 - y0)
  #else
    #define Y0 y0
    #define Y1 y1
  #endif
  if ((LCD_DrawMode & LCD_DRAWMODE_XOR) ==0) {
    MaskStart = aStartMask[Y0&7];
    MaskEnd   = aEndMask[Y1&7];
    Page0     = Y0>>3;
    Page1     = Y1>>3;
    for (Page =Page0; Page<= Page1; Page++) {
      U8 Mask =0xff;
      if (Page==Page0) {
        Mask  = MaskStart;
      }
      if (Page==Page1) {
        Mask &= MaskEnd;
      }
      for (x=X0; x<=X1; x++) {
        U8 aData[2];
        aData[0] = Cache[Page][x][0];
        aData[1] = Cache[Page][x][1];
        if (COLOR&(1<<1)) {
          aData[0] |= Mask;
        } else {
          aData[0] &= ~Mask;
        }
        if (COLOR&(1<<0)) {
          aData[1] |= Mask;
        } else {
          aData[1] &= ~Mask;
        }
        if (memcmp(&aData[0], &Cache[Page][x],2)) {
          Cache[Page][x][0]      = aData[0];
          Cache[Page][x][1]      = aData[1];
          WRITE_VMEM_PAIR(Page, x, &aData[0]);
        }
      }
    }
/* ... */
  } else {
    int x;
    for (x=X0; x <= X1; x++) {
      LCD_L0_DrawVLine(x,Y0, Y1);
    }
  }
  #undef X0
  #undef Y0
  #undef X1
  #undef Y1
}

/*
        *********************************************************
        *                                                       *
        *          LCD_FillRect, unoptimized                    *
        *                                                       *
        *********************************************************
*/

#else

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  for (; y0 <= y1; y0++) {
    LCD_L0_DrawHLine(x0,y0, x1);
  }
}

#endif


/*
        *********************************************************
        *                                                       *
        *    Support for dynamic inversion of entire LCD        *
        *                                                       *
        *********************************************************

*/

#if LCD_REVERSEMODE_SUPPORT

void LCD_SetNormalDispMode    (void) {
}
void LCD_SetReverseDispMode   (void) {
}

#endif


/*
        *********************************************************
        *                                                       *
        *          Draw Bitmap 1 BPP                            *
        *                                                       *
        *********************************************************
*/

static void  DrawBitLine1BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  PIXELCOLOR pixels;
  PIXELCOLOR Index0 = *(pTrans+0);
  PIXELCOLOR Index1 = *(pTrans+1);
/*
   Jump to right entry point
*/
  pixels = *p;
  switch (LCD_DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
  case 0:
    #if defined (SETNEXTPIXEL)
      SetPosXY(x,y);
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
#if defined (SETNEXTPIXEL)   /* Optimization ! */
  WriteBit0:
    SetNextPixel(x+0, y, (pixels&(1<<7)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit1:
    SetNextPixel(x+1, y, (pixels&(1<<6)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit2:
    SetNextPixel(x+2, y, (pixels&(1<<5)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit3:
    SetNextPixel(x+3, y, (pixels&(1<<4)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit4:
    SetNextPixel(x+4, y, (pixels&(1<<3)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit5:
    SetNextPixel(x+5, y, (pixels&(1<<2)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit6:
    SetNextPixel(x+6, y, (pixels&(1<<1)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit7:
    SetNextPixel(x+7, y, (pixels&(1<<0)) ? Index1 : Index0);
    if (!--xsize)
      return;
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
        *********************************************************
        *                                                       *
        *  Draw Bitmap 2 BPP                                    *
        *                                                       *
        *********************************************************
*/

#if (LCD_MAX_LOG_COLORS > 2)

static void  DrawBitLine2BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  PIXELCOLOR pixels;
/*
   Jump to right entry point
*/
  pixels = *p;
  if (pTrans) { 
    /* 
      with palette 
    */
    switch (LCD_DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
    case 0:
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
    case LCD_DRAWMODE_TRANS:
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
    case LCD_DRAWMODE_XOR:
      switch (Diff&3) {
      case 0:
        goto WriteXBit0;
      case 1:
        goto WriteXBit1;
      case 2:
        goto WriteXBit2;
      default:
        goto WriteXBit3;
      }
    case LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR:
      switch (Diff&3) {
      case 0:
        goto WriteTXBit0;
      case 1:
        goto WriteTXBit1;
      case 2:
        goto WriteTXBit2;
      default:
        goto WriteTXBit3;
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
  /*
          Write without transparency, xor
  */
  WriteXBit0:
    XORPIXEL_DATA(x+0, y, *(pTrans+(pixels>>6)));
    if (!--xsize)
      return;
  WriteXBit1:
    XORPIXEL_DATA(x+1, y, *(pTrans+(3&(pixels>>4))));
    if (!--xsize)
      return;
  WriteXBit2:
    XORPIXEL_DATA(x+2, y, *(pTrans+(3&(pixels>>2))));
    if (!--xsize)
      return;
  WriteXBit3:
    XORPIXEL_DATA(x+3, y, *(pTrans+(3&(pixels))));
    if (!--xsize)
      return;
    pixels = *(++p);
    x+=4;
    goto WriteXBit0;
  /*
          Write with transparency, xor
  */
  WriteTXBit0:
    if (pixels&(3<<6))
      XORPIXEL_DATA(x+0, y, *(pTrans+(pixels>>6)));
    if (!--xsize)
      return;
  WriteTXBit1:
    if (pixels&(3<<4))
      XORPIXEL_DATA(x+1, y, *(pTrans+(3&(pixels>>4))));
    if (!--xsize)
      return;
  WriteTXBit2:
    if (pixels&(3<<2))
      XORPIXEL_DATA(x+2, y, *(pTrans+(3&(pixels>>2))));
    if (!--xsize)
      return;
  WriteTXBit3:
    if (pixels&(3<<0))
      XORPIXEL_DATA(x+3, y, *(pTrans+(3&(pixels))));
    if (!--xsize)
      return;
    pixels = *(++p);
    x+=4;
    goto WriteTXBit0;
  } else { 
    /* 
      without palette 
    */
    switch (LCD_DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
    case 0:
      switch (Diff&3) {
      case 0:
        goto WriteDDPBit0;
      case 1:
        goto WriteDDPBit1;
      case 2:
        goto WriteDDPBit2;
      default:
        goto WriteDDPBit3;
      }
    case LCD_DRAWMODE_TRANS:
      switch (Diff&3) {
      case 0:
        goto WriteDDPTBit0;
      case 1:
        goto WriteDDPTBit1;
      case 2:
        goto WriteDDPTBit2;
      default:
        goto WriteDDPTBit3;
      }
    case LCD_DRAWMODE_XOR:
      switch (Diff&3) {
      case 0:
        goto WriteDDPXBit0;
      case 1:
        goto WriteDDPXBit1;
      case 2:
        goto WriteDDPXBit2;
      default:
        goto WriteDDPXBit3;
      }
    case LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR:
      switch (Diff&3) {
      case 0:
        goto WriteDDPTXBit0;
      case 1:
        goto WriteDDPTXBit1;
      case 2:
        goto WriteDDPTXBit2;
      default:
        goto WriteDDPTXBit3;
      }
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
  /*
          Write without transparency, xor
  */
  WriteDDPXBit0:
    XORPIXEL_DATA(x+0, y, (pixels>>6));
    if (!--xsize)
      return;
  WriteDDPXBit1:
    XORPIXEL_DATA(x+1, y, (3&(pixels>>4)));
    if (!--xsize)
      return;
  WriteDDPXBit2:
    XORPIXEL_DATA(x+2, y, (3&(pixels>>2)));
    if (!--xsize)
      return;
  WriteDDPXBit3:
    XORPIXEL_DATA(x+3, y, (3&(pixels)));
    if (!--xsize)
      return;
    pixels = *(++p);
    x+=4;
    goto WriteDDPXBit0;
  /*
          Write with transparency, xor
  */
  WriteDDPTXBit0:
    if (pixels&(3<<6))
      XORPIXEL_DATA(x+0, y, (pixels>>6));
    if (!--xsize)
      return;
  WriteDDPTXBit1:
    if (pixels&(3<<4))
      XORPIXEL_DATA(x+1, y, (3&(pixels>>4)));
    if (!--xsize)
      return;
  WriteDDPTXBit2:
    if (pixels&(3<<2))
      XORPIXEL_DATA(x+2, y, (3&(pixels>>2)));
    if (!--xsize)
      return;
  WriteDDPTXBit3:
    if (pixels&(3<<0))
      XORPIXEL_DATA(x+3, y, (3&(pixels)));
    if (!--xsize)
      return;
    pixels = *(++p);
    x+=4;
    goto WriteDDPTXBit0;
  }
}

#endif


/*
        *********************************************************
        *                                                       *
        *  Draw Bitmap 4 BPP                                    *
        *                                                       *
        *********************************************************
*/

#if (LCD_MAX_LOG_COLORS > 4)

static void  DrawBitLine4BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  PIXELCOLOR pixels;
/*
   Jump to right entry point
*/
  pixels = *p;
  if (LCD_DrawMode & LCD_DRAWMODE_TRANS) {
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
        *********************************************************
        *                                                       *
        *  Draw Bitmap 8 BPP  (256 colors)                      *
        *                                                       *
        *      Default (no optimization)                        *
        *                                                       *
        *********************************************************
*/

#if (LCD_MAX_LOG_COLORS > 16)
static void  DrawBitLine8BPP(int x, int y, U8 const*p, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixel;
  if (pTrans) {
    if ((LCD_DrawMode & LCD_DRAWMODE_TRANS)==0) {
      while (xsize > 0) {
        pixel = *p;
        SETPIXEL(x+0, y, *(pTrans+pixel));
        xsize--; x++; p++;
      }
    } else {   /* Handle transparent bitmap */
      while (xsize > 0) {
        pixel = *p;
        if (pixel)
          SETPIXEL(x+0, y, *(pTrans+pixel));
        xsize--; x++; p++;
      }
    }
  } else {
    if ((LCD_DrawMode & LCD_DRAWMODE_TRANS)==0) {
      while (xsize > 0) {
        pixel = *p;
        SETPIXEL(x+0, y, pixel);
        xsize--; x++; p++;
      }
    } else {   /* Handle transparent bitmap */
      while (xsize > 0) {
        pixel = *p;
        if (pixel)
          SETPIXEL(x+0, y, pixel);
        xsize--; x++; p++;
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

int OrgX, OrgY;
void LCD_L0_SetOrg(int x, int y) {
  OrgX = x;
  OrgY = y;
}






/*
        *********************************************************
        *                                                       *
        *       LCD_On                                          *
        *       LCD_Off                                         *
        *                                                       *
        *********************************************************
*/

void LCD_Off          (void) {
  #ifdef LCD_OFF
    LCD_OFF();
  #endif
}

void LCD_On           (void) {
  #ifdef LCD_ON
    LCD_ON();
  #endif
}


/*
*********************************************************
*                                                       *
*       LCD_L0_ControlCache                                *
*                                                       *
*********************************************************

*/

void LCD_FlushCache(void) {
  int page;
  for (page=0; page < (LCD_COMS_MAX+7)/8; page++) {
    if (aCacheDirty[page]) {
      aCacheDirty[page]=0;
      SetPage(page);
      SetCol(0);
      LCD_WRITEMDATA(&Cache[page][0][0], 2*LCD_NUM_SEGS0);
    }
  }
  ColCache = LCD_NUM_SEGS0;
}

U8 LCD_L0_ControlCache(U8 cmd) {
  switch (cmd) {
  case LCD_CC_LOCK:   /* Set Cache to lock state.*/
    CacheLocked =1;
    break;
  case LCD_CC_UNLOCK: /* Set Cache to unlock state ... must flush !*/
    CacheLocked =0;
  case LCD_CC_FLUSH:  /* Flush cache */
    if (CacheStat) {
      CacheStat =0;
      LCD_FlushCache();
    }
  }
  return CacheStat;
}


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

void  LCD_L0_ReInit(void) {
  LCD_Init();              /* Recall LCD init */ 
}


/*
        *********************************************************
        *                                                       *
        *       LCD_Init : Init the display                     *
        *                                                       *
        *********************************************************
*/
#define ZEROINIT(var) memset(&var,0,sizeof(var))

int  LCD_L0_Init(void) {
  #if LCD_WATCHDOG_TRIGGERCNT
    WatchdogTriggerCnt =0;
  #endif
  #if  LCD_SUPPORT_CACHECONTROL
    CacheStat   =0;     /* 0: No changes */
    CacheLocked =0;     /* 0: Not locked */
  #endif
  ZEROINIT(Cache);
  memset(aCacheDirty,1, sizeof(aCacheDirty));
  LCD_INIT_CONTROLLER();    
  LCD_FlushCache();
  return 0;    /* Init successfull ! */
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

#if LCD_SUPPORT_CHECKINIT

char LCD_L0_CheckInit(void) {
  return 0;
}
#endif

#else

void LCD07X1(void) { } /* avoid empty object files */

#endif  /* Right LCD_CONTROLLER */

