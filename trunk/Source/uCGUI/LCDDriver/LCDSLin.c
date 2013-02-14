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
File        : LCDSLin.C
Purpose     : Driver for LCDs using simple bus interface

Currently supported controllers:

              Toshiba T6963
              Epson SED1330
              Epson SED1335

----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
2.00g   020319 JE     a) Macro changed to fix NC30-error
2.00f   020204 JE     a) Hardwareinterface routines renamed:
                         ...DATA -> ...A0, ...CMD -> ...A1
2.00e   011112 JE     a) LCD_INIT_CONTROLLER added to be able to
                         execute LCD_X_Init during init
2.00d   010926 JE     a) Support for LCD_SWAP_XY added
2.00c   010706 JE     a) Bugfix in DrawBitLine1BPP
2.00b   010402 RS     a) LCD_GetDevCaps removed from driver
                         (now LCD.c)
2.00a   008026 RS     a) Simulation interface changed
2.00    000525 JE     a) Interface changed
1.02c   000509 JE     a) Simple bus interface changed for SED133x
                      b) Small changes in DrawBitLine1BPP
                      c) Cache initialisation to SED133x added
1.02b   000508 JE     a) Simple bus interface changed for T6963
1.02a   000426 JE     a) Transparent mode in DrawBitLine1BPP changed
                      b) Dummy LCD_L0_SetLUTEntry inserted
1.02    000426 RS     a) Changes for new LCD-driver interface V1.30
1.00a   000410 JE     a) LCD_GetDevCap changed
                      b) LCD_GetpCapFunc deleted
                      c) LCD_DrawBitMap changed
                      d) Definition for aColorIndex changed
1.00    000407 JE     First release
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
none
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>             /* for memset */
#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include "LCD_0.h"            /* Defines for first display */

#if (LCD_CONTROLLER == 6963) || (LCD_CONTROLLER == 1330) || (LCD_CONTROLLER == 1335) \
      && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))



/*
  ********************************************************************
  *                                                                  *
  *                Conversion table
  *                                                                  *
  ********************************************************************
*/

static const LCD_PIXELINDEX LCD_ConversionTable[2] = {0, 1};

/*
        *********************************************************
        *                                                       *
        *           Defaults for configuration                  *
        *                                                       *
        *********************************************************

*/

#ifndef LCD_OPTIMIZE
  #define LCD_OPTIMIZE                  (1)
#endif

#ifndef LCD_CHECKBUSY
  #define LCD_CHECKBUSY                 (1)
#endif

#ifndef LCD_INIT
  #define LCD_INIT()
#endif

#ifndef LCD_WATCHDOG_TRIGGERCNT
  #define LCD_WATCHDOG_TRIGGERCNT       (0)
#endif

#ifndef LCD_KICK_WATCHDOG
  #define LCD_KICK_WATCHDOG()
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

/* Switch support for the LCD_CopyRect function of the driver */
#ifndef  LCD_SUPPORT_COPYRECT
  #define  LCD_SUPPORT_COPYRECT         (1)
#endif

#ifndef LCD_INIT_CONTROLLER
  #define LCD_INIT_CONTROLLER()
#endif


/*
        *********************************************************
        *                                                       *
        *          Internal types                               *
        *                                                       *
        *********************************************************
*/

#if LCD_BITSPERPIXEL == 1
  #define PIXELCOLOR U8
#else
  #error LCD_BITSPERPIXEL != 1 not supported
#endif


/*
        *********************************************************
        *                                                       *
        *      Configuration switch checking                    *
        *                                                       *
        *********************************************************

Please be aware that not all configuration errors can be captured !

*/

/* Check number of controllers */
#if (LCD_NUM_CONTROLLERS != 1)
  #error "Only 1 controller supported by this driver"
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
        *                                                       *
        * Standard variables for driver                         *
        *                                                       *
        *********************************************************
*/

static U8 Cache[((LCD_XSIZE_PHYS+7)>>3)*LCD_YSIZE_PHYS];

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

#if LCD_SUPPORT_COMTRANS
  extern LCD_TYPE_COMTRANS LCD__aLine2Com0[LCD_LASTCOM0-LCD_FIRSTCOM0+1];
#endif

#if LCD_SUPPORT_SEGTRANS
  extern LCD_TYPE_SEGTRANS LCD__aRow2Seg0[LCD_LASTSEG0-LCD_FIRSTSEG0+1];
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
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)  _SetPixel(y, x, c)
    #define GETPIXEL(x, y)     _GetPixel(y, x)
    #define XORPIXEL(x, y)      XorPixel(y, x)
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)  _SetPixel(x, LCD_YSIZE-1-(y), c)
    #define GETPIXEL(x, y)     _GetPixel(x, LCD_YSIZE-1-(y))
    #define XORPIXEL(x, y)     XorPixel (x, LCD_YSIZE-1-(y))
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)  _SetPixel(LCD_YSIZE-1-(y), x, c)
    #define GETPIXEL(x, y)     _GetPixel(LCD_YSIZE-1-(y), x)
    #define XORPIXEL(x, y)      XorPixel(LCD_YSIZE-1-(y), x)
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)  _SetPixel(LCD_XSIZE-1-(x), y, c)
    #define GETPIXEL(x, y)     _GetPixel(LCD_XSIZE-1-(x), y)
    #define XORPIXEL(x, y)     XorPixel (LCD_XSIZE-1-(x), y)
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)  _SetPixel(LCD_YSIZE-1-(y), x, c)
    #define GETPIXEL(x, y)     _GetPixel(LCD_YSIZE-1-(y), x)
    #define XORPIXEL(x, y)      XorPixel(LCD_YSIZE-1-(y), x)
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY) 
    #define SETPIXEL(x, y, c)  _SetPixel(LCD_XSIZE-1-(x), LCD_YSIZE-1-(y), c)
    #define GETPIXEL(x, y)     _GetPixel(LCD_XSIZE-1-(x), LCD_YSIZE-1-(y))
    #define XORPIXEL(x, y)     XorPixel (LCD_XSIZE-1-(x), LCD_YSIZE-1-(y))
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

#define XY2OFF(x,y) ((x>>3)+y*((LCD_XSIZE_PHYS+7)>>3))
#define BKCOLOR LCD_BKCOLORINDEX
#define   COLOR LCD_COLORINDEX




/*
        *********************************************************
        *                                                       *
        *       ID translation table                            *
        *                                                       *
        *********************************************************

This table contains 0, 1, 2, ... and serves as translation table for DDBs

*/

static const U8 TransId[] = { 0,1 };


/*
        *********************************************************
        *                                                       *
        *       LCD Access                                      *
        *                                                       *
        *********************************************************
*/

int LCD_Adr;

#if (!LCD_CHECKBUSY)
  #define LCD_WAIT()
#endif

static U8 result; /* Possibly needed for access macro */


/*
        *********************************************************
        *                                                       *
        *       LCD Access Controller SED133x                   *
        *                                                       *
        *********************************************************
*/

#if (LCD_CONTROLLER == 1330) \
  ||(LCD_CONTROLLER == 1335)

/* Remap ...A0, ...A1 -> ...CMD, ...DATA */

#define LCD_READCMD0    LCD_READ_A0
#define LCD_READDATA0   LCD_READ_A1
#define LCD_WRITECMD0   LCD_WRITE_A1
#define LCD_WRITEDATA0  LCD_WRITE_A0

#ifndef LCD_EXTENDED_WAIT
  #define LCD_EXTENDED_WAIT 1
#endif

#ifndef LCD_WAIT
  #define LCD_WAIT()                \
    while (!(LCD_READCMD0()&0x40)); \
    while (  LCD_READCMD0()&0x40) ;
#endif
#if LCD_EXTENDED_WAIT
  #define LCD_WRITECMD(cmd)      { LCD_WAIT(); LCD_WRITECMD0(cmd);  }
  #define LCD_WRITEDATA(Data)    { LCD_WAIT(); LCD_WRITEDATA0(Data);}
#else
  #define LCD_WRITECMD(cmd)      { LCD_WRITECMD0(cmd);  }
  #define LCD_WRITEDATA(Data)    { LCD_WRITEDATA0(Data);}
#endif

#define GSTART (0x0)
#if (LCD_YSIZE_PHYS >128)
  #define TSTART 30000
#else
  #define TSTART 7000
#endif

static void LCD_SetSystem(void) {
  LCD_WRITECMD (0x40);
  LCD_WRITEDATA(0x30);                 /* P1                                    */
  LCD_WRITEDATA(0x87);                 /* P2 : FX : hor. char size-1            */
  LCD_WRITEDATA(0x7);                  /* P3 : FY : ver. char size-1 (not imp.) */
  LCD_WRITEDATA(((LCD_XSIZE_PHYS+7)>>3)-1); /* P4 : Characters per row               */
  LCD_WRITEDATA(0x4a);                 /* P5 : Timing charcters per row         */
  LCD_WRITEDATA(LCD_YSIZE_PHYS-1);          /* P6 : Number of lines per screen       */
  LCD_WRITEDATA((LCD_XSIZE_PHYS+7)>>3);     /* P7 : Address pitch low                */
  LCD_WRITEDATA(0x00);                 /* P8 : Address pitch high               */
}

static void LCD_SetScroll(int Adr) {
  LCD_WRITECMD(0x44);
  LCD_WRITEDATA(TSTART&255);               /* address of screen 1 (text)            */
  LCD_WRITEDATA(TSTART>>8);
  LCD_WRITEDATA((LCD_YSIZE_PHYS)-1);
  LCD_WRITEDATA(Adr);                  /* address of screen 2 (graphic)         */
  LCD_WRITEDATA(Adr>>8);
  LCD_WRITEDATA((LCD_YSIZE_PHYS)-1);
}

static void LCD_SetAdr(int Off) {
  LCD_Adr=Off;
  #if (!LCD_EXTENDED_WAIT)
    LCD_WAIT();
  #endif
  LCD_WRITECMD (0x46);
  LCD_WRITEDATA(Off&255);
  LCD_WRITEDATA(Off>>8);
}

#define LCD_SETADR(Off) LCD_SetAdr(Off)

static void LCD_Write1(char Byte) {
  #if (!LCD_EXTENDED_WAIT)
    LCD_WAIT();
  #endif
  LCD_WRITECMD (0x42);
  LCD_WRITEDATA(Byte);
  LCD_Adr++;
}

#define LCD_WRITE1(Byte) LCD_Write1(Byte)

/* LCD_L0_ReInit */
void LCD_L0_ReInit(void) {
  int i;
  LCD_INIT_CONTROLLER();
  LCD_SetSystem();
  LCD_SetScroll(GSTART) ;
  LCD_WRITECMD (0x4c);                 /* Set cursor move direction             */
  LCD_WRITECMD (0x5a);                 /* HDOT SCR : Set horiz. scroll position */
  LCD_WRITEDATA(0);
  LCD_WRITECMD (0x5b);                 /* OVLAY                                 */
  LCD_WRITEDATA(1);
  /* Clear display memory */
  LCD_SETADR(0);
  LCD_WRITECMD (0x42);
  #if (LCD_YSIZE_PHYS >128)
    for (i=0; i<32000; i++)
  #else
    for (i=0; i<8000; i++)
  #endif
      LCD_WRITEDATA(0);
  #if (LCD_REVERSE)
    LCD_SETADR(GSTART);
    LCD_WRITECMD (0x42);
    for (i=GSTART; i<GSTART+((LCD_XSIZE_PHYS+7)>>3)*LCD_YSIZE_PHYS; i++)
      LCD_WRITEDATA(0xff);
  #endif
  if(COLOR)
    memset(Cache,0xff,sizeof(Cache));
  else
    memset(Cache,0x0,sizeof(Cache));
  LCD_WRITECMD (0x59);                 /* Display on                            */
  LCD_WRITEDATA(0x14);                 /* All screens on, curosr off            */
}

/* LCD_FirstInit */
static void LCD_FirstInit(void) {
  LCD_L0_ReInit();
}

#endif /* SED133x */


/*
        *********************************************************
        *                                                       *
        *       LCD Access Controller T6963                     *
        *                                                       *
        *********************************************************
*/

#if (LCD_CONTROLLER == 6963)

/* Remap ...A0, ...A1 -> ...CMD, ...DATA */

#define LCD_READCMD0    LCD_READ_A1
#define LCD_READDATA0   LCD_READ_A0
#define LCD_WRITECMD0   LCD_WRITE_A1
#define LCD_WRITEDATA0  LCD_WRITE_A0

#ifndef LCD_WAIT
  #define LCD_WAIT() while ((LCD_READ_A1()&3)!=3) /* Do not use LCD_READCMD0 to fix NC30-problem (JE) */
#endif

#define LCD_WRITECMD(cmd)      { LCD_WAIT(); LCD_WRITECMD0(cmd);  }
#define LCD_WRITEDATA(Data)    { LCD_WAIT(); LCD_WRITEDATA0(Data);}

/* Access Macros */
#define LCD_READDATA()        \
  LCD_WRITECMD(0xC5);         \
  return LCD_DATA0;

#define LCD_SETADR(Adr)       \
  LCD_WRITEDATA((U8)Adr);     \
  LCD_WRITEDATA((U8)(Adr>>8));\
  LCD_WRITECMD(0x24);         \
  LCD_Adr=Adr;

#define LCD_WRITE1(Byte)      \
  LCD_WRITEDATA(Byte);        \
  LCD_WRITECMD(0xC0);         \
  LCD_Adr++;


/* LCD_L0_ReInit */
#define LCD_RAMSIZE (0x2000)
#define LCD_GSTART  (0x0)
#define LCD_XSIZEB  ((LCD_XSIZE_PHYS+7)>>3)
#define LCD_TSTART  (LCD_RAMSIZE-(LCD_XSIZEB)-(LCD_YSIZE_PHYS>>3))

void LCD_L0_ReInit(void) {
  LCD_WRITECMD(0x81);           /* SetModeXor */

  LCD_WRITEDATA((U8)LCD_TSTART);/* SetTextAdr */
  LCD_WRITEDATA((U8)(LCD_TSTART>>8));
  LCD_WRITECMD(0x40);

  LCD_WRITEDATA(1);             /* SetTextArea */
  LCD_WRITEDATA(1>>8);
  LCD_WRITECMD(0x41);

  LCD_WRITECMD(0x9C);           /* SetTextGraph */

  LCD_WRITEDATA(LCD_GSTART);    /* SetGraphAdr */
  LCD_WRITEDATA(LCD_GSTART>>8);
  LCD_WRITECMD(0x42);

  LCD_WRITEDATA(LCD_XSIZEB);    /* SetGraphArea */
  LCD_WRITEDATA(LCD_XSIZEB>>8);
  LCD_WRITECMD(0x43);
}


/* LCD_FirstInit */
void LCD_FirstInit(void) {
  int i;
  LCD_INIT_CONTROLLER();
  LCD_SETADR(0);
  for (i=0; i<100; i++) {
    LCD_WRITE1(0xff);
  }
  LCD_SETADR(0);
  for (i=0;i<LCD_RAMSIZE;i++) {
    LCD_WRITE1(0x0);
  }
}

#endif /* T6963 */


/*
        *********************************************************
        *                                                       *
        *       Write 1 byte and manage cache                   *
        *                                                       *
        *********************************************************
*/

static void LCD_Write(int Adr, U8 Byte) {
  if (Cache[Adr]!=Byte) {
    Cache[Adr]=Byte;
    if (LCD_Adr!=Adr) {
      LCD_SETADR(Adr);
    }
    LCD_WRITE1(Byte);
  }
}

#define LCD_WRITE(Adr,Byte) LCD_Write(Adr,Byte);


/*
        *********************************************************
        *                                                       *
        *       Internal set pixel routines                     *
        *                                                       *
        *********************************************************
*/

static void _SetPixel(int x, int y, LCD_PIXELINDEX c) {
  U8 Mask=1<<(7-(x&7));
  int Adr=XY2OFF(x,y);
  U8 CacheByte=Cache[Adr];
  if (c)
    CacheByte|= Mask;
  else
    CacheByte&=~Mask;
  LCD_WRITE(Adr,CacheByte)
}

static PIXELCOLOR _GetPixel(int x, int y) {
  int Adr=XY2OFF(x,y);
  U8 Mask=1<<(7-(x&7));
  return (Cache[Adr]&Mask) ? 1 : 0;
}

static void XorPixel   (int x, int y) {
  LCD_PIXELINDEX Index = _GetPixel(x,y);
  _SetPixel(x,y, LCD_NUM_COLORS-1-Index);
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
        *          LCD_L0_DrawHLine optimized                   *
        *                                                       *
        *********************************************************
*/

#if (LCD_OPTIMIZE)               \
      && (!LCD_SWAP_XY)          \
      && (!LCD_MIRROR_X)         \
      && (!LCD_MIRROR_Y)         \
      && (!LCD_SUPPORT_COMTRANS) \
      && (!LCD_SUPPORT_SEGTRANS)

void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  register int Off = XY2OFF(x0,y);
  int iByte = x0>>3;
  int Byte1 = x1>>3;
  U8 Mask =    0xff   >> (x0&7);
  U8 EndMask = 0xff80 >> (x1&7);
  U8 Data;
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; iByte<Byte1; iByte++) {
      Data = Cache[Off];
      Data ^= Mask; 
      LCD_WRITE(Off++,Data);
      Mask = 0xff;
    }
    Mask &= EndMask;
    Data = Cache[Off];
    Data ^= Mask; 
    LCD_WRITE(Off++,Data);
  } else {                                  /* Clear pixels in line */
    int NumBytes = Byte1-iByte;
    if (COLOR==0) {
      if (NumBytes) {
        Data = Cache[Off] & (~Mask);
        LCD_WRITE(Off++,Data);
        NumBytes--;
      /* Fill bytes in 2 loops for speed reasons ... */
        for (; NumBytes>=4; NumBytes-=4) {
          LCD_WRITE(Off++,0);
          LCD_WRITE(Off++,0);
          LCD_WRITE(Off++,0);
          LCD_WRITE(Off++,0);
        }
        for (; NumBytes; NumBytes--) {
          LCD_WRITE(Off++,0);
        }
        Mask = 0xff;
      }
      Mask &= EndMask;
      Data = Cache[Off];
      Data &= ~Mask; 
      LCD_WRITE(Off++,Data);
    } else {                                  /* Set pixels in line */
      if (NumBytes) {
        Data = Cache[Off] | Mask; 
        LCD_WRITE(Off++,Data);
        NumBytes--;
      /* Fill bytes in 2 loops for speed reasons ... */
        for (; NumBytes>=4; NumBytes-=4) {
          LCD_WRITE(Off++,0xff);
          LCD_WRITE(Off++,0xff);
          LCD_WRITE(Off++,0xff);
          LCD_WRITE(Off++,0xff);
        }
        for (; NumBytes; NumBytes--) {
          LCD_WRITE(Off++,0xff);
        }
        Mask = 0xff;
      }
      Mask &= EndMask;
      Data = Cache[Off] | Mask; 
      LCD_WRITE(Off++,Data);
    }
  }
}

#else

/*
        *********************************************************
        *                                                       *
        *          LCD_L0_DrawHLine unoptimized                 *
        *                                                       *
        *********************************************************
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

#endif


/*
        *********************************************************
        *                                                       *
        *          LCD_L0_DrawVLine                             *
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


/*
        *********************************************************
        *                                                       *
        *          LCD_FillRect, unoptimized                    *
        *                                                       *
        *********************************************************
*/

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  for (; y0 <= y1; y0++) {
    LCD_L0_DrawHLine(x0,y0, x1);
  }
}


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
        *          Draw Bitmap 1 BPP, optimized                 *
        *                                                       *
        *********************************************************
*/

#if (LCD_OPTIMIZE)               \
      && (!LCD_SWAP_XY)          \
      && (!LCD_MIRROR_X)         \
      && (!LCD_MIRROR_Y)         \
      && (!LCD_SUPPORT_COMTRANS) \
      && (!LCD_SUPPORT_SEGTRANS)

static void  DrawBitLine1BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX Index0 = *(pTrans+0);
  LCD_PIXELINDEX Index1 = *(pTrans+1);
  x+=Diff;
  if ((Index0==Index1) & (!(GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)))) {
    LCD_PIXELINDEX ColorIndexOld= COLOR;
    COLOR = Index0;
    LCD_L0_DrawHLine(x,y,x+xsize-1);
    COLOR = ColorIndexOld;
    return;
  }
  {
    int Adr=XY2OFF(x,y);
    int x1 = x+xsize-1;
    U8 Mask    = 0xff   >> (x &7);
    U8 EndMask = 0xff80 >> (x1&7);
    U8 CacheByte;
    U16 PixelData;
    int NumBytes = (x1>>3) - (x>>3);
    if (NumBytes) {
      CacheByte=Cache[Adr];
      PixelData   = (*(p+1) | ((*p)<<8));
      PixelData >>= (8+(x&7)-(Diff&7));
      switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
      case 0:
        if (!COLOR)
          PixelData ^= 255;
        CacheByte = (CacheByte&~Mask)|(PixelData&Mask);
        break;
      case LCD_DRAWMODE_TRANS:
        if (COLOR)
          CacheByte |= (PixelData&Mask);
        else
          CacheByte &= ~(PixelData&Mask);
        break;
      case LCD_DRAWMODE_XOR:
        CacheByte ^= (PixelData&Mask);
        break;
      }
      LCD_WRITE(Adr++,CacheByte);
      { 
        int DiffOld = Diff;
        Diff+= 8-(x&7); 
        if ((DiffOld&~7) != (Diff&~7))
          p++;
      }
      x=0;
      NumBytes--;
      for (; NumBytes; NumBytes--) {
        PixelData   = (*(p+1) | ((*p)<<8));
        PixelData >>= (8-(Diff&7));
        p++;
        switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
        case 0:
          if (!COLOR)
            PixelData ^= 255;
          CacheByte=PixelData&255;
          break;
        case LCD_DRAWMODE_TRANS:
          CacheByte=Cache[Adr];
          if (COLOR)
            CacheByte |= PixelData;
          else
            CacheByte &= ~PixelData;
          break;
        case LCD_DRAWMODE_XOR:
          CacheByte=Cache[Adr] ^ PixelData;
          break;
        }
        LCD_WRITE(Adr++,CacheByte);
      }
      Mask = 0xff;
    }
    PixelData   = (*(p+1) | ((*p)<<8));
    PixelData >>= (8+(x&7)-(Diff&7));
    Mask &= EndMask;
    CacheByte = Cache[Adr];
    switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
    case 0:
      if (!COLOR)
        PixelData ^= 255;
      CacheByte = (CacheByte&~Mask)|(PixelData&Mask);
      break;
    case LCD_DRAWMODE_TRANS:
      if (COLOR)
        CacheByte |= (PixelData&Mask);
      else
        CacheByte &= ~(PixelData&Mask);
      break;
    case LCD_DRAWMODE_XOR:
      CacheByte ^= (PixelData&Mask);
      break;
    }
    LCD_WRITE(Adr++,CacheByte);
  }
}

#else


/*
        *********************************************************
        *                                                       *
        *          Draw Bitmap 1 BPP, no optimization           *
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

#endif


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
/*  
        Do x-Clipping
*/
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS)==0) {
    while (xsize > 0) {
      pixel = *p;
      SETPIXEL(x+0, y, *(pTrans+pixel));
      xsize--;
      x++;
      p++;
    }
  } else {   /* Handle transparent bitmap */
    while (xsize > 0) {
      pixel = *p;
      if (pixel)
        SETPIXEL(x+0, y, *(pTrans+pixel));
      xsize--;
      x++;
      p++;
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
  if (!pTrans)
    pTrans = LCD_ConversionTable;
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

#if LCD_SUPPORT_VERIFY

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
        *               Copy rectangle                          *
        *                                                       *
        *********************************************************

This function is used for scrolling. If scrolling is not required
(as is sometimes the case) this routine can be eliminated via
configuration switch.

*/

#if  LCD_SUPPORT_COPYRECT

static void Copy_Line (int y,int x0,int x1,int dx,int dy) {
  if (dy >=0) {
    int x;
    for (x=x0; x<=x1; x++) {
      _SetPixel(x+dx, y+dy, _GetPixel(x,y));
    }
  } else {
    int x;
    for (x=x1; x>=x0; x--) {
      _SetPixel(x+dx, y+dy, _GetPixel(x,y));
    }
  }
}

void LCD_CopyRect     (int x0, int y0, int x1, int y1, int dx, int dy) {
  if (dy >=0) {
    int y;
    for (y=y0; y<=y1; y++) {
      Copy_Line (y,x0,x1,dx,dy);
    }
  } else {
    int y;
    for (y=y1; y>=y0; y--) {
      Copy_Line (y,x0,x1,dx,dy);
    }
  }
}
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

unsigned int LCD_L0_GetPixelIndex(int x, int y) {
  return GETPIXEL(x,y);
}


/*
        *********************************************************
        *                                                       *
        *       LCD_Init : Init the display                     *
        *                                                       *
        *********************************************************
*/

int  LCD_L0_Init(void) {
  /* Controller independent */
  #if LCD_WATCHDOG_TRIGGERCNT
    WatchdogTriggerCnt =0;
  #endif
  /* Controller initialisation */
  LCD_FirstInit();
  LCD_L0_ReInit();
  LCD_Adr=0xffff;
  /* Init successfull */
  return 0;
}

#else

void LCDSLin(void) { } /* avoid empty object files */

#endif


