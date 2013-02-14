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
File        : LCD159A.C
Purpose     : Driver for LCDs using a Seiko Epson SED159A controller
----------------------------------------------------------------------   
Version-Date---Author-Explanation                                        
----------------------------------------------------------------------   
1.00b   020204 JE     a) Hardwareinterface routines renamed:
                         ...DATA -> ...A1, ...CMD -> ...A0
1.00a   010926 JE     a) Support for LCD_SWAPXY added
1.00.00 010710 JE     a) Speed optimizations added
0.90.00 010709 JE     a) First release
---------------------------LIST OF CONFIG SWITCHES--------------------
The following is a list of additional configuration switches for this
driver. These switches might not be listed in the manual, because
the manual mainly covers the general config switches which are
supported by all drivers.
----------------------------------------------------------------------
define ----------------------Explanation------------------------------
LCD_OPTIMIZE                 Controls the use of optimized routines.
                             If 1, several (speed) optimizations are used.
                             Default: ON (1)
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
a) Cache not supported yet, becuse RAM requirement would be 
   to large. LCD_CACHE must be set to 0
----------------------------------------------------------------------
Open issues
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

#if      (LCD_CONTROLLER == 0x159A) \
      && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))


/*
        *********************************************************
        *
        *           Defaults for config switches
        *
        *********************************************************

*/

#ifndef LCD_OPTIMIZE
  #define LCD_OPTIMIZE                (1)
#endif

#ifndef LCD_CACHE
  #define  LCD_CACHE                  (0)
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
  void SIM_WriteA1C0(U8 Byte);
  void SIM_WriteA0C0(U8 Byte);
  U8   SIM_ReadA1C0(void);
  U8   SIM_ReadA0C0(void);
  #define LCD_WRITE_A1(Byte) SIM_WriteA1C0(Byte) 
  #define LCD_WRITE_A0(Byte) SIM_WriteA0C0(Byte)
  #define LCD_READ_A1(Byte)  Byte = SIM_ReadA1C0()
  #define LCD_READ_A0(Byte)  Byte = SIM_ReadA0C0()
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
        *           Macro calculations
        *
        *********************************************************
*/

/*
        *********************************************************
        *
        *           Configuration switch checking
        *
        *********************************************************
*/

#if (LCD_BITSPERPIXEL != 8)
  #error This controller can handle only 8bpp displays
#endif

/*
        *********************************************************
        *
        *           Macros, standard
        *
        *********************************************************

These macros can be found in any LCD-driver as they serve purposes
that can be found in any class of LCD-driver (Like clipping).

*/

#if (!LCD_SWAP_XY) && (!LCD_MIRROR_X) && (!LCD_MIRROR_Y)
  #define LOG2PHYS(x, y) x, y
#elif (!LCD_SWAP_XY) && (!LCD_MIRROR_X) && (LCD_MIRROR_Y)
  #define LOG2PHYS(x, y) x, LCD_YSIZE_PHYS - 1 - (y)
#elif (!LCD_SWAP_XY) && (LCD_MIRROR_X) && (!LCD_MIRROR_Y)
  #define LOG2PHYS(x, y) LCD_XSIZE_PHYS - 1 - (x), y
#elif (!LCD_SWAP_XY) && (LCD_MIRROR_X) && (LCD_MIRROR_Y)
  #define LOG2PHYS(x, y) LCD_XSIZE_PHYS - 1 - (x), LCD_YSIZE_PHYS - 1 - (y)
#elif (LCD_SWAP_XY) && (!LCD_MIRROR_X) && (!LCD_MIRROR_Y)
  #define LOG2PHYS(x, y) y, x
#elif (LCD_SWAP_XY) && (LCD_MIRROR_X) && (!LCD_MIRROR_Y)
  #define LOG2PHYS(x, y) y, LCD_XSIZE - 1 - (x)
#elif (LCD_SWAP_XY) && (!LCD_MIRROR_X) && (LCD_MIRROR_Y)
  #define LOG2PHYS(x, y) LCD_YSIZE - 1 - (y), x
#elif (LCD_SWAP_XY) && (LCD_MIRROR_X) && (LCD_MIRROR_Y)
  #define LOG2PHYS(x, y) LCD_YSIZE - 1 - (y), LCD_XSIZE - 1 - (x)
#else
  #error unsupported configuration
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
  static U8 VRam[LCD_YSIZE_PHYS][LCD_XSIZE_PHYS];
#endif

static int CurrentX, CurrentY, StartPage, StartColumn, RAM_Mode;

/*
        *********************************************************
        *
        *           Hardware access
        *
        *********************************************************
*/

/*
        *****************************************
        *
        *           Low level macros
        *
        *****************************************
*/

#define RAM_WRITE (0x5c)
#define RAM_READ  (0x5d)

#define INCREMENT_CURSOR() \
  CurrentX++; \
  if (CurrentX >= LCD_XSIZE_PHYS) { \
    CurrentX = StartColumn; \
    CurrentY++; \
    if (CurrentY >= LCD_YSIZE_PHYS) \
      CurrentY = StartPage; \
  }

#define RESET_CURSOR() \
  CurrentX = StartColumn; \
  CurrentY = StartPage

#define SET_RAMMODE(Mode) \
  RAM_Mode = Mode; \
  LCD_WRITECMD0 (Mode); \
  RESET_CURSOR()

#define PASET(y) \
  RAM_Mode = 0; \
  LCD_WRITECMD0 (0x75); \
  LCD_WRITEDATA0(y); \
  LCD_WRITEDATA0(LCD_YSIZE_PHYS - 1); \
  StartPage = y
  
#define CASET(x) \
  RAM_Mode = 0; \
  LCD_WRITECMD0 (0x15); \
  LCD_WRITEDATA0(x); \
  LCD_WRITEDATA0(LCD_XSIZE_PHYS - 1); \
  StartColumn = x

#define LCD_ON() \
  LCD_WRITECMD0 (0xaf); \
  SET_RAMMODE(RAM_WRITE)

#define LCD_OFF() \
  LCD_WRITECMD0 (0xae); \
  SET_RAMMODE(RAM_WRITE)

#define DUMMYREAD(Data) \
  LCD_READDATA0(Data)

#if (LCD_OPTIMIZE)
  
  #define SET_RECT(x1, y1, x2, y2) \
    CurrentX = CurrentY = 0xfff; \
    LCD_WRITECMD0 (0x15); \
    LCD_WRITEDATA0(x1); \
    LCD_WRITEDATA0(x2); \
    LCD_WRITECMD0 (0x75); \
    LCD_WRITEDATA0(y1); \
    LCD_WRITEDATA0(y2); \
    LCD_WRITECMD0 (0x5c)

  #define WRITEDATA_DIRECT(Data) \
    LCD_WRITEDATA0(Data)

#endif

#if LCD_CACHE

  #define WRITEDATA(Data) \
    if (VRam[CurrentX][CurrentY] != Data) { \
      VRam[CurrentX][CurrentY] = Data; \
      LCD_WRITEDATA0(Data); \
    } \
    INCREMENT_CURSOR()

  #define READDATA(Data) \
    Data = VRam[CurrentX][CurrentY]

#else

  #define WRITEDATA(Data) \
    LCD_WRITEDATA0(Data); \
    INCREMENT_CURSOR()

  #define READDATA(Data) \
    LCD_READDATA0(Data); \
    INCREMENT_CURSOR()

#endif

/*
        *****************************************
        *
        *           GotoXY
        *
        *****************************************
*/

void GotoXY(int x, int y, int Mode) {
  if ((CurrentX != x) || (CurrentY != y)) {
    CASET(x);
    PASET(y);
  }
  if (RAM_Mode != Mode) {
    SET_RAMMODE(Mode);
  }
}

#define GOTOXY(x, y, Mode) GotoXY(x, y, Mode)

/*
        *********************************************************
        *
        *           Drawing routines, internal
        *
        *********************************************************
*/

/*
        *****************************************
        *
        *           SET pixel
        *
        *****************************************
*/

static void SetPixel(int x, int y, U8 Color) {
  GOTOXY(x, y, RAM_WRITE);
  WRITEDATA(Color);
}

/*
        *****************************************
        *
        *           GET pixel
        *
        *****************************************
*/

static U8 GetPixel(int x, int y) {
  U8 Color;
  CASET(x);
  PASET(y);
  SET_RAMMODE(RAM_READ);
  DUMMYREAD(Color);
  READDATA(Color);
  return Color;
}

/*
        *****************************************
        *
        *           XOR pixel
        *
        *****************************************
*/

static void XorPixel(int x, int y) {
  U8 Color = GetPixel(x, y);
  Color ^= 0xff;
  SET_RAMMODE(RAM_WRITE);
  WRITEDATA(Color);
}

/*
        *********************************************************
        *
        *           Access macros for pixel access
        *
        *********************************************************

Use only this macros for pixel access

*/

#define XORPIXEL(x, y) \
  XorPixel(LOG2PHYS(x, y));

#define SETPIXEL(x, y, Color) \
  SetPixel(LOG2PHYS(x, y), Color);

#define GETPIXEL(x, y, Color) \
  Color = GetPixel(LOG2PHYS(x, y));

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
        *           LCD_L0_XorPixel
        *
        *****************************************

Purpose:  This routine is called by emWin. It writes 1 pixel into the
          display.

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

Purpose:  This routine is called by emWin. It writes 1 pixel into the
          display.

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
  U8 ColorIndex;
  GETPIXEL(x, y, ColorIndex);
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
        ****************************************
        *
        *           LCD_DrawHLine
        *
        ****************************************
*/

#if  (LCD_OPTIMIZE)  \
  && (!LCD_MIRROR_X) \
  && (!LCD_MIRROR_Y) \
  && (!LCD_SWAP_XY)

void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    while (x0 <= x1) {
      XORPIXEL(x0, y);
      x0++;
    }
  } else {
    SET_RECT(x0, y, x1, y);
    while (x0++ <= x1) {
      WRITEDATA_DIRECT(COLOR);
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

/*
        ****************************************
        *
        *           LCD_DrawVLine
        *
        ****************************************
*/

#if  (LCD_OPTIMIZE)  \
  && (!LCD_MIRROR_X) \
  && (!LCD_MIRROR_Y) \
  && (!LCD_SWAP_XY)

void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    while (y0 <= y1) {
      XORPIXEL(x, y0);
      y0++;
    }
  } else {
    SET_RECT(x, y0, x, y1);
    while (y0++ <= y1) {
      WRITEDATA_DIRECT(COLOR);
    }
  }
}

#else

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

#endif

/*
        *****************************************
        *
        *           LCD_L0_FillRect
        *
        *****************************************

*/

#if  (LCD_OPTIMIZE)  \
  && (!LCD_MIRROR_X) \
  && (!LCD_MIRROR_Y) \
  && (!LCD_SWAP_XY)

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; y0 <= y1; y0++) {
      LCD_L0_DrawHLine(x0, y0, x1);
    }
  } else {
    int Bytes = (y1 - y0 + 1) * (x1 - x0 + 1);
    SET_RECT(x0, y0, x1, y1);
    while (Bytes--) {
      WRITEDATA_DIRECT(COLOR);
    }
  }
}

#else

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  for (; y0 <= y1; y0++) {
    LCD_L0_DrawHLine(x0, y0, x1);
  }
}

#endif

/*
        *****************************************
        *
        *           Draw Bitmap 1 BPP
        *           optimized
        *
        *****************************************
*/

#if  (LCD_OPTIMIZE)  \
  && (!LCD_MIRROR_X) \
  && (!LCD_MIRROR_Y) \
  && (!LCD_SWAP_XY)

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
    WRITEDATA_DIRECT((pixels&(1<<7)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit1:
    WRITEDATA_DIRECT((pixels&(1<<6)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit2:
    WRITEDATA_DIRECT((pixels&(1<<5)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit3:
    WRITEDATA_DIRECT((pixels&(1<<4)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit4:
    WRITEDATA_DIRECT((pixels&(1<<3)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit5:
    WRITEDATA_DIRECT((pixels&(1<<2)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit6:
    WRITEDATA_DIRECT((pixels&(1<<1)) ? Index1 : Index0);
    if (!--xsize)
      return;
  WriteBit7:
    WRITEDATA_DIRECT((pixels&(1<<0)) ? Index1 : Index0);
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

#else

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

#endif

/*
        *****************************************
        *
        *           Draw Bitmap 2 BPP
        *           optimized
        *
        *****************************************
*/

#if (LCD_MAX_LOG_COLORS > 2)

#if  (LCD_OPTIMIZE)  \
  && (!LCD_MIRROR_X) \
  && (!LCD_MIRROR_Y) \
  && (!LCD_SWAP_XY)

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
  WRITEDATA_DIRECT(*(pTrans+(pixels>>6)));
  if (!--xsize)
    return;
WriteBit1:
  WRITEDATA_DIRECT(*(pTrans+(3&(pixels>>4))));
  if (!--xsize)
    return;
WriteBit2:
  WRITEDATA_DIRECT(*(pTrans+(3&(pixels>>2))));
  if (!--xsize)
    return;
WriteBit3:
  WRITEDATA_DIRECT(*(pTrans+(3&(pixels))));
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

#else

/*
        *****************************************
        *
        *           Draw Bitmap 2 BPP
        *           no optimizations
        *
        *****************************************
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
        *****************************************
        *
        *           Draw Bitmap 4 BPP
        *           optimized
        *
        *****************************************
*/

#if (LCD_MAX_LOG_COLORS > 4)

#if  (LCD_OPTIMIZE)  \
  && (!LCD_MIRROR_X) \
  && (!LCD_MIRROR_Y) \
  && (!LCD_SWAP_XY)

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
  WRITEDATA_DIRECT(*(pTrans+(pixels>>4)));
  if (!--xsize)
    return;
WriteBit1:
  WRITEDATA_DIRECT(*(pTrans+(pixels&0xf)));
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

#else

/*
        *****************************************
        *
        *           Draw Bitmap 4 BPP
        *           no optimizations
        *
        *****************************************
*/

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

#endif

#endif

/*
        *****************************************
        *
        *           Draw Bitmap 8 BPP
        *           optimized
        *
        *****************************************
*/

#if (LCD_MAX_LOG_COLORS > 16)

#if  (LCD_OPTIMIZE)  \
  && (!LCD_MIRROR_X) \
  && (!LCD_MIRROR_Y) \
  && (!LCD_SWAP_XY)

static void  DrawBitLine8BPP(int x, int y, U8 const*p, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS)==0) {
    if (pTrans) {
      for (;xsize > 0; xsize--,x++,p++) {
        pixel = *p;
        WRITEDATA_DIRECT(*(pTrans+pixel));
      }
    } else {
      for (;xsize > 0; xsize--,x++,p++) {
        WRITEDATA_DIRECT(*p);
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

#else

/*
        *****************************************
        *
        *           Draw Bitmap 8 BPP
        *           no optimizations
        *
        *****************************************
*/

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

#endif

/*
        *********************************************************
        *
        *           Universal draw Bitmap routine
        *
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
  #if  (LCD_OPTIMIZE)  \
    && (!LCD_MIRROR_X) \
    && (!LCD_MIRROR_Y) \
    && (!LCD_SWAP_XY)
    SET_RECT(x0 + Diff, y0, x0 + Diff + xsize - 1, y0 + ysize - 1);
  #endif
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
        *****************************************
        *
        *           LCD_On, LCD_Off
        *
        *****************************************

Sets the original position of the virtual display.
Has no function at this point with the PC-driver.

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
        *****************************************
        *
        *           LCD_L0_Init
        *
        *****************************************
*/

int  LCD_L0_Init(void) {
  int i;
  GUI_DEBUG_LOG("\nLCD_Init()");
  LCD_INIT_CONTROLLER();
  /* set cursor to illegal value */
  CurrentX = CurrentY = 0xfff;
  /* clear LCD */
  GOTOXY(0, 0, RAM_WRITE);
  for (i = 0; i < LCD_XSIZE_PHYS * LCD_YSIZE_PHYS; i++) {
    LCD_WRITEDATA0(0);
  }
  GOTOXY(0, 0, RAM_WRITE);
  /* clear VRam */
  #if LCD_CACHE
    memset(VRam, 0, sizeof(VRam));
  #endif
  LCD_Off();
  return 0;
}

/*
        *****************************************
        *
        *           LCD_L0_SetLUTEntry
        *
        *****************************************

This function is only a dummy

*/

void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR Color) {
  Pos = Pos;
  Color = Color;
}

#else

void LCD159A(void) { } /* avoid empty object files */

#endif  /* (LCD_CONTROLLER == 0x159A) */
