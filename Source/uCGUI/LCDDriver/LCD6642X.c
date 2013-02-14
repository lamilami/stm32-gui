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
File        : 
Purpose     : 
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
1.04f   020204 JE     a) Hardwareinterface routines renamed:
                         ...REG01 -> ...A1, ...REG00 -> ...A0
1.04e   010706 JE     a) Bugfixes in DrawBitLine1BPP_Swap
1.04d   010627 JE     a) Bugfix in DrawBitLine1BPP_Swap
1.04c   010420 JE     a) Defaults for config switches added
1.04b   010418 JE     a) Accelerations of DrawVLine changed 
                         for using with cache
                      b) LCD_L0_DrawBitmap changed
1.04a   010417 RS     a) DrawVLine for "Philips mode" accelerated
1.04    010411 JE     a) 2bpp bitmaps accelerated
                      b) 1bpp bitmaps accelerated
1.02    010406 JE     a) Use of cache completed
                      b) DrawVLine optimized
1.00    010401 RS     a) Major work ...
0.02    010314 JE     a) REORG0 changed
                      b) _GetPixel0 & _GetPixel0 changed
                      c) Superfluous macro definitions SETPIXEL, ... deleted
                      d) PHYS_... new to handle rotation
0.01    010313 JE     a) Initialisation changed
0.00    001019 RS     Start of development
---------------------------LIST OF CONFIG SWITCHES--------------------
The following is a list of additional configuration switches for this
driver. These switches might not be listed in the manual, because
the manual mainly covers the general config switches which are
supported by all drivers.
----------------------------------------------------------------------
define ----------------------Explanation------------------------------
LCD_OPTIMIZE                 Controls the use of optimized routines.
LCD_CACHE                    If active cache is used
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

#if   ((LCD_CONTROLLER == 66420) | (LCD_CONTROLLER == 66421)) \
      && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))



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
        *           Defaults for configuration                  *
        *                                                       *
        *********************************************************
*/

#ifndef LCD_XORG0
  #define LCD_XORG0     (0)     /* leftmost position covered by this controller */
#endif

#ifndef LCD_YORG0
  #define LCD_YORG0     (0)     /* topmost position covered by this controller */
#endif

#ifndef LCD_STATIC
  #define LCD_STATIC static
#endif

#ifndef LCD_CACHE
  #define  LCD_CACHE (0)
#endif

#ifndef LCD_FIRSTSEG0
  #define LCD_FIRSTSEG0   (0)     /* Contr.0: first segment line used */
#endif

#ifndef LCD_LASTSEG0
  #define LCD_LASTSEG0    (LCD_XSIZE_PHYS-1)    /* Contr.0: last segment line used */
#endif

#ifndef LCD_FIRSTCOM0
  #define LCD_FIRSTCOM0   (0)     /* Contr.0: first com line used */
#endif

#ifndef LCD_LASTCOM0
  #define LCD_LASTCOM0    (LCD_YSIZE_PHYS-1)     /* Contr.0: last com line used */
#endif

#ifndef LCD_NUM_CONTROLLERS
  #define LCD_NUM_CONTROLLERS           (1)
#endif

#ifndef LCD_SUPPORT_CHECKINIT
  #define LCD_SUPPORT_CHECKINIT         (0)
#endif

#ifndef LCD_OPTIMIZE
  #define LCD_OPTIMIZE                (1)
#endif

/*      *********************************************************
        *                                                       *
        *              Controller dependend values              *
        *                                                       *
        *********************************************************
*/

#define MAX_REGS   18
#if (LCD_CONTROLLER == 66420)
  #define MAX_SEGS   160
  #define MAX_COMS   80
#elif (LCD_CONTROLLER == 66421)
  #define MAX_SEGS   160
  #define MAX_COMS   100
#endif

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
  U8 SIM_Read00(void);
  U8 SIM_Read01(void);
  U8 SIM_Read10(void);
  U8 SIM_Read11(void);
  void SIM_Write00(U8 Data);
  void SIM_Write01(U8 Data);
  void SIM_Write10(U8 Data);
  void SIM_Write11(U8 Data);
/* Write data */
  #undef  LCD_WRITE_A0
  #define LCD_WRITE_A0(Data) SIM_Write00(Data)
  #undef  LCD_WRITE_A1
  #define LCD_WRITE_A1(Data) SIM_Write01(Data)
  #if LCD_NUM_CONTROLLERS > 1
    #undef  LCD_WRITE_A0C1
    #define LCD_WRITE_A0C1(Data) SIM_Write10(Data)
    #undef  LCD_WRITE_A1C1
    #define LCD_WRITE_A1C1(Data) SIM_Write11(Data)
  #endif  /* LCD_NUM_CONTROLLERS > 1 */
/* Read data */
  #undef  LCD_READ_A0
  #define LCD_READ_A0(Data) Data = SIM_Read00()
  #undef  LCD_READ_A1
  #define LCD_READ_A1(Data) Data = SIM_Read01()
  #if LCD_NUM_CONTROLLERS > 1
    #undef  LCD_READ_A0C0
    #define LCD_READ_A0C0(Data) Data = SIM_Read10()
    #undef  LCD_READ_A1C0
    #define LCD_READ_A1C0(Data) Data = SIM_Read11()
  #endif  /* LCD_NUM_CONTROLLERS > 1 */
#endif

/*
        *********************************************************
        *
        *          Remap ...A0, ...A1 -> ...CMD, ...DATA
        *
        *********************************************************
*/

#define LCD_WRITE_REG00 LCD_WRITE_A0
#define LCD_WRITE_REG01 LCD_WRITE_A1
#define LCD_READ_REG00  LCD_READ_A0
#define LCD_READ_REG01  LCD_READ_A1
#if LCD_NUM_CONTROLLERS > 1
  #define LCD_WRITE_REG10 LCD_WRITE_A0C1
  #define LCD_WRITE_REG11 LCD_WRITE_A1C1
  #define LCD_READ_REG10  LCD_READ_A0C1
  #define LCD_READ_REG11  LCD_READ_A1C1
#endif

/*
        *********************************************************
        *                                                       *
        *          Internal types                               *
        *                                                       *
        *********************************************************
*/

#define PIXELCOLOR U8
#define BKCOLOR LCD_BKCOLORINDEX
#define   COLOR LCD_COLORINDEX

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
        *           Macro calculations                          *
        *                                                       *
        *********************************************************
*/

#define LCD_MSB_SHIFT       (8-LCD_LSB_SHIFT)

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

#if (!defined(LCD_INIT_R00)) | (!defined(LCD_INIT_R01))
  #error You have to define init values in the configuration for Registers 0,1
         /* Drivers needs to know as these values can not be read back ! */
#endif


/*********************************************************************
*
*           Static variables
*
**********************************************************************
*/

static struct {
  U8 ConReg0;
  U8 ConReg1;
  U8 x,y;
  #if LCD_CACHE
    U8 aaVMem[MAX_COMS][MAX_SEGS/4];  /* video memory */
  #endif
} aState[LCD_NUM_CONTROLLERS];

/*
        *********************************************************
        *                                                       *
        *              Macros, standard                         *
        *                                                       *
        *********************************************************

These macros can be found in any LCD-driver as they serve purposes
that can be found in any class of LCD-driver.
*/

#if (!LCD_SWAP_XY) && (!LCD_MIRROR_X) && (!LCD_MIRROR_Y)
  #define LOG2PHYS(x,y) x,y
#elif (!LCD_SWAP_XY) && (!LCD_MIRROR_X) && (LCD_MIRROR_Y)
  #define LOG2PHYS(x,y) x,LCD_YSIZE_PHYS-1-(y)
#elif (!LCD_SWAP_XY) && (LCD_MIRROR_X) && (!LCD_MIRROR_Y)
  #define LOG2PHYS(x,y) LCD_XSIZE_PHYS-1-(x),y
#elif (!LCD_SWAP_XY) && (LCD_MIRROR_X) && (LCD_MIRROR_Y)
  #define LOG2PHYS(x,y) LCD_XSIZE_PHYS-1-(x),LCD_YSIZE_PHYS-1-(y)
#elif (LCD_SWAP_XY) && (!LCD_MIRROR_X) && (!LCD_MIRROR_Y)
  #define LOG2PHYS(x,y) y,x
#elif (LCD_SWAP_XY) && (LCD_MIRROR_X) && (!LCD_MIRROR_Y)
  #define LOG2PHYS(x,y) y,LCD_XSIZE-1-(x)
#elif (LCD_SWAP_XY) && (!LCD_MIRROR_X) && (LCD_MIRROR_Y)
  #define LOG2PHYS(x,y) LCD_YSIZE-1-(y),x
#elif (LCD_SWAP_XY) && (LCD_MIRROR_X) && (LCD_MIRROR_Y)
  #define LOG2PHYS(x,y) LCD_YSIZE-1-(y),LCD_XSIZE-1-(x)
#else
  #error unsupported configuration
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

#define XORPIXEL_DATA(x, y,c)  XorPixel_Data(x,y,c)

#if (!LCD_SUPPORT_COMTRANS && !LCD_SUPPORT_SEGTRANS)
  #define SETPIXEL(x, y, c)  _SetPixel(x, y, c)
  #define GETPIXEL(x, y)     _GetPixel(x,y)
  #define XORPIXEL(x, y)     XorPixel(x,y)
  #define XORPIXEL_DATA(x, y,c)  XorPixel_Data(x,y,c)
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
********************************************************************
*
*           Hardware access routines
*
********************************************************************
*/

/* Write into controller 0 */
void LCD_WriteReg0(int Reg, U8 Data) {
  LCD_WRITE_REG00(Reg);
  LCD_WRITE_REG01(Data);
}

#if LCD_NUM_CONTROLLERS > 1
void LCD_WriteReg1(int Reg, U8 Data) {
  LCD_WRITE_REG10(Reg);
  LCD_WRITE_REG11(Data);
}
#endif

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

#define SET_X_INCREMENT()                    \
  aState[0].ConReg1 = (LCD_INIT_R01) | ( 2); \
  LCD_WriteReg0( 1, aState[0].ConReg1)

#define SET_Y_INCREMENT()                    \
  aState[0].ConReg1 = (LCD_INIT_R01) & (~2); \
  LCD_WriteReg0( 1, aState[0].ConReg1)

#define SET_X0(xNew) \
  if (aState[0].x != xNew) \
  { LCD_WRITE_REG00(2); LCD_WRITE_REG01(xNew); aState[0].x = xNew; }

#define SET_Y0(yNew) \
  if (aState[0].y != yNew) \
  { LCD_WRITE_REG00(3); LCD_WRITE_REG01(yNew); aState[0].y = yNew; }

#define EXEC_INCREMENT()        \
  if (aState[0].ConReg1 & 1<<1) \
    aState[0].x++;              \
  else                          \
    aState[0].y++

#if LCD_CACHE
  #define WRITE_VMEM0(Data) {     \
    aState[0].aaVMem[aState[0].y][aState[0].x] = Data; \
    LCD_WRITE_REG00(4);           \
    LCD_WRITE_REG01(Data);        \
    EXEC_INCREMENT();             \
  }
#else
  #define WRITE_VMEM0(Data) {     \
    LCD_WRITE_REG00(4);           \
    LCD_WRITE_REG01(Data);        \
    EXEC_INCREMENT();             \
  }
#endif

#if LCD_CACHE
  #define READ_VMEM0(Data)  {     \
    Data = aState[0].aaVMem[aState[0].y][aState[0].x]; \
  }
#else
  #define READ_VMEM0(Data)  {     \
    LCD_WRITE_REG00(4);           \
    LCD_READ_REG01(Data);         \
    LCD_READ_REG01(Data);         \
  }
#endif

/*
        *********************************************************
        *                                                       *
        *       Internal set pixel routines                     *
        *                                                       *
        *********************************************************
*/

static U8 aAndMask[4] = {255-(3<<6), 255-(3<<4), 255-(3<<2), 255-(3<<0)};

static void _SetPixel0_Phys(int x, int y, PIXELCOLOR c) {
  U8 Data;
  int xByte = x>>2;
  int Pos = x&3;
  #if LCD_CACHE ==0
    SET_X0(xByte);
    SET_Y0(y);
    READ_VMEM0(Data);
    Data &= aAndMask[Pos];
    Data |= c<<(6-(Pos<<1));
    WRITE_VMEM0(Data);
  #else
    U8* pData = &aState[0].aaVMem[y][xByte];
    Data = *pData & aAndMask[Pos];
    Data |= c<<(6-(Pos<<1));
    if (Data != *pData) {
      SET_X0(xByte);
      SET_Y0(y);
      WRITE_VMEM0(Data);
    }
  #endif
}

#define _SetPixel(x,y,c)     _SetPixel0_Phys(LOG2PHYS((x-LCD_XORG0),(y-LCD_YORG0)), c)

static PIXELCOLOR _GetPixel0(int x, int y) {
  int xByte = x>>2;
  int Pos = 3-(x&3);
  U8 Data;
  SET_X0(xByte);
  SET_Y0(y);
  READ_VMEM0(Data);
  return 3&(Data>>(Pos<<1));
}

static PIXELCOLOR _GetPixel(int x, int y) {
  return _GetPixel0(LOG2PHYS((x-LCD_XORG0),(y-LCD_YORG0)));
}

static void XorPixel(int x, int y) {
  PIXELCOLOR Index = _GetPixel(x,y);
  _SetPixel(x,y, LCD_NUM_COLORS-1-Index);
}

static void XorPixel_Data(int x, int y, PIXELCOLOR c) {
  PIXELCOLOR Index = _GetPixel(x,y);
  _SetPixel(x,y,Index^c);
}

/*
*********************************************************
*
*                  LCD_L0_GetPixelIndex
*
*********************************************************
*/

unsigned LCD_L0_GetPixelIndex(int x, int y) {
  return _GetPixel(x,y);
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

/*
        *********************************************************
        *
        *          LCD_L0_DrawVLine, optimized
        *
        *********************************************************
*/

#if (LCD_OPTIMIZE)               \
    && (LCD_BITSPERPIXEL == 2)   \
    && (LCD_SWAP_XY ==1)         \
    && (LCD_MIRROR_X==1)         \
    && (LCD_MIRROR_Y==0)         \
    && (!defined (LCD_LUT_SEG))

void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  U8 ColorMask, OrMask, AndMask, Data;
  int y = LCD_XSIZE - x - 1;
  int x0 = y0;
  int x1 = y1;
  int x0Byte = x0 >> 2;
  int x1Byte = (x1 + 1) >> 2;
  int NumBytes = x1Byte - x0Byte;
  SET_X_INCREMENT();
  SET_Y0(y);
  SET_X0(x0Byte);
  ColorMask  = COLOR + (COLOR<<2) + (COLOR<<4) + (COLOR<<6);
  if (x0 & 3) {
    int Pos = (x0 & 3) << 1;
    AndMask = 0xff << (8 - Pos);
    OrMask = ColorMask >> Pos;
    READ_VMEM0(Data);
    if (x0Byte == (x1 >> 2)) {
      if ((x1 & 3) != 3) {
        int Pos = ((x1 + 1) & 3) << 1;
        AndMask |= 0xff >> Pos;
        OrMask &= ColorMask << (8 - Pos);
      }
      NumBytes = 0;
    }
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
      Data ^= (0xff & ~AndMask);
    } else {
      Data &= AndMask;
      Data |= OrMask;
    }
    WRITE_VMEM0(Data);
    if (!NumBytes) {
      SET_Y_INCREMENT();
      return;
    }
    --NumBytes;
  }
  if (NumBytes) {
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
      do {
        READ_VMEM0(Data);
        Data ^= 0xff;
        WRITE_VMEM0(Data);
      } while(--NumBytes);
    } else {
      LCD_WRITE_REG00(4);
      #if LCD_CACHE
        memset(&aState[0].aaVMem[aState[0].y][aState[0].x], ColorMask, NumBytes);
      #endif
      aState[0].x += NumBytes;
      do {
        LCD_WRITE_REG01(ColorMask);
      } while(--NumBytes);
    }
  }
  if ((x1 + 1) & 3) {
    int Pos = ((x1 + 1) & 3) << 1;
    AndMask = 0xff >> Pos;
    OrMask = ColorMask << (8 - Pos);
    READ_VMEM0(Data);
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
      Data ^= (0xff & ~AndMask);
    } else {
      Data &= AndMask;
      Data |= OrMask;
    }
    WRITE_VMEM0(Data);
  }
  SET_Y_INCREMENT();
}

/*
        *********************************************************
        *
        *          LCD_L0_DrawVLine no optimization
        *
        *********************************************************
*/

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

/*********************************************************************
*
*          LCD_FillRect
*
**********************************************************************
*/


#if LCD_SWAP_XY
void LCD_L0_FillRect(int x, int y0, int x1, int y1) {
  for (; x <= x1; x++) {
    LCD_L0_DrawVLine(x,y0, y1);
  }
}
#else
void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
  for (; y0 <= y1; y0++) {
    LCD_L0_DrawHLine(x0,y0, x1);
  }
}
#endif

/*
        *********************************************************
        *
        *  Draw Bitmap 1 BPP, optimized
        *
        *********************************************************
*/

#if (LCD_OPTIMIZE)               \
    && (LCD_BITSPERPIXEL == 2)   \
    && (LCD_SWAP_XY ==1)         \
    && (LCD_MIRROR_X==1)         \
    && (LCD_MIRROR_Y==0)         \
    && (!defined (LCD_LUT_SEG))

static void DrawBitLine1BPP_Swap(
  int x,
  int y,
  U8 const * pData,
  int ysize,
  const U8 * pTrans,
  int BytesPerLine,
  U8 Pos)
{
  LCD_PIXELINDEX Index0 = *(pTrans+0);
  LCD_PIXELINDEX Index1 = *(pTrans+1);
  int i;
  int y0 = LCD_XSIZE - x - 1;
  int x0 = y;
  int x0Byte = y >> 2;
  U8 Buffer, DataMask, Index, Data, ShiftPos, BufferMask, Pixel;
  U8 BufferValid = 0;
  SET_Y0(y0);
  SET_X0(x0Byte);
  ShiftPos = Pos & 7;
  BufferMask = 0xC0 >> ((x0  & 3) << 1);
  DataMask =   0x80 >> ShiftPos;
  for (i = 0; i < ysize; i++, pData += BytesPerLine) {
    if (!BufferValid) {
      READ_VMEM0(Buffer);
      BufferValid = 1;
    }
    switch (GUI_Context.DrawMode) {
    case LCD_DRAWMODE_NORMAL:
    case LCD_DRAWMODE_REV:
      Buffer &= ~BufferMask;
      Index = *(pTrans + ((*pData & DataMask) >> (7 - ShiftPos)));
      Data = Index << (6 - (((i + x0) & 3) << 1));
      Buffer |= Data;
      break;
    case LCD_DRAWMODE_XOR:
      Pixel = (*pData & DataMask) >> (7 - ShiftPos);
      if (Pixel) {
        Data = 3 << (6 - (((i + x0) & 3) << 1));
        Buffer ^= Data;
      }
      break;
    case LCD_DRAWMODE_TRANS:
      Pixel = (*pData & DataMask) >> (7 - ShiftPos);
      if (Pixel) {
        Index = *(pTrans + Pixel);
        Buffer &= ~BufferMask;
        Data = Index << (6 - (((i + x0) & 3) << 1));
        Buffer |= Data;
      }
      break;
    }
    if (BufferMask == 3) {
      BufferMask = 0xC0;
      BufferValid = 0;
      WRITE_VMEM0(Buffer);
    } else {
      BufferMask >>= 2;
    }
  }
  if (BufferValid) {
    WRITE_VMEM0(Buffer);
  }
}

#else

/*
        *********************************************************
        *
        *  Draw Bitmap 1 BPP no optimization
        *
        *********************************************************
*/

static void  DrawBitLine1BPP(int x, int y, U8 const *p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  PIXELCOLOR pixels;
  PIXELCOLOR Index0 = *(pTrans+0);
  PIXELCOLOR Index1 = *(pTrans+1);
/*
// Jump to right entry point
*/
  pixels = *p;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
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

#endif

/*
        *********************************************************
        *
        *  Draw Bitmap 2 BPP, optimized
        *
        *********************************************************
*/

#if (LCD_MAX_LOG_COLORS > 2)

#if (LCD_OPTIMIZE)               \
    && (LCD_BITSPERPIXEL == 2)   \
    && (LCD_SWAP_XY ==1)         \
    && (LCD_MIRROR_X==1)         \
    && (LCD_MIRROR_Y==0)         \
    && (!defined (LCD_LUT_SEG))

static void DrawBitLine2BPP_Swap(
  int x,
  int y,
  U8 const * pData,
  int ysize,
  const U8 * pTrans,
  int BytesPerLine,
  U8 Pos)
{
  int i;
  int y0 = LCD_XSIZE - x - 1;
  int x0 = y;
  int x0Byte = y >> 2;
  U8 Buffer, DataMask, Index, Data, ShiftPos, BufferMask;
  U8 BufferValid = 0;
  SET_Y0(y0);
  SET_X0(x0Byte);
  ShiftPos = (Pos & 3) << 1;
  BufferMask = 0xC0 >> ((x0  & 3) << 1);
  DataMask =   0xC0 >> ShiftPos;
  for (i = 0; i < ysize; i++, pData += BytesPerLine) {
    if (!BufferValid) {
      READ_VMEM0(Buffer);
      BufferValid = 1;
    }
    switch (GUI_Context.DrawMode) {
    case LCD_DRAWMODE_NORMAL:
    case LCD_DRAWMODE_REV:
      Buffer &= ~BufferMask;
      Index = *(pTrans + ((*pData & DataMask) >> (6 - ShiftPos)));
      Data = Index << (6 - (((i + x0) & 3) << 1));
      Buffer |= Data;
      break;
    case LCD_DRAWMODE_XOR:
      Index = *(pTrans + ((*pData & DataMask) >> (6 - ShiftPos))) * 3;
      Data = Index << (6 - (((i + x0) & 3) << 1));
      Buffer ^= Data;
      break;
    case LCD_DRAWMODE_TRANS:
      Index = *(pTrans + ((*pData & DataMask) >> (6 - ShiftPos)));
      if (Index) {
        Buffer &= ~BufferMask;
        Data = Index << (6 - (((i + x0) & 3) << 1));
        Buffer |= Data;
      }
      break;
    }
    if (BufferMask == 3) {
      BufferMask = 0xC0;
      BufferValid = 0;
      WRITE_VMEM0(Buffer);
    } else {
      BufferMask >>= 2;
    }
  }
  if (BufferValid) {
    WRITE_VMEM0(Buffer);
  }
}

/*
        *********************************************************
        *
        *  Draw Bitmap 2 BPP no optimization
        *
        *********************************************************
*/

#else

static void  DrawBitLine2BPP(int x, int y, U8 const *p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  PIXELCOLOR pixels;
/*
// Jump to right entry point
*/
  pixels = *p;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS|LCD_DRAWMODE_XOR)) {
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
}

#endif

#endif

/*
        *********************************************************
        *                                                       *
        *  Draw Bitmap 4 BPP                                    *
        *                                                       *
        *********************************************************
*/

#if (LCD_MAX_LOG_COLORS > 4)

static void  DrawBitLine4BPP(int x, int y, U8 const *p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  PIXELCOLOR pixels;
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
        *********************************************************
        *                                                       *
        *  Draw Bitmap 8 BPP  (256 colors)                      *
        *                                                       *
        *      Default (no optimization)                        *
        *                                                       *
        *********************************************************
*/

#if (LCD_MAX_LOG_COLORS > 16)
static void  DrawBitLine8BPP(int x, int y, U8 const *p, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixel;
  if (pTrans) {
    if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS)==0) {
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
    if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS)==0) {
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

void LCD_L0_DrawBitmap(int x0, int y0,
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
  /*
     Use DrawBitLineXBPP
  */
  switch (BitsPerPixel) {
  case 1:
    #if (LCD_OPTIMIZE)               \
        && (LCD_BITSPERPIXEL == 2)   \
        && (LCD_SWAP_XY ==1)         \
        && (LCD_MIRROR_X==1)         \
        && (LCD_MIRROR_Y==0)         \
        && (!defined (LCD_LUT_SEG))
      SET_X_INCREMENT();
      xsize += Diff & 7;
      for (i = Diff; i < xsize; i++) {
        DrawBitLine1BPP_Swap(
          x0+i, y0,
          pData + (i>>3),
          ysize,
          pTrans,
          BytesPerLine,
          i
        );
      }
      SET_Y_INCREMENT();
      break;
    #else
      for (i=0; i<ysize; i++) {
        DrawBitLine1BPP(x0, i+y0, pData, Diff, xsize, pTrans);
        pData += BytesPerLine;
      }
      break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 2)
    case 2:
      #if (LCD_OPTIMIZE)               \
          && (LCD_BITSPERPIXEL == 2)   \
          && (LCD_SWAP_XY ==1)         \
          && (LCD_MIRROR_X==1)         \
          && (LCD_MIRROR_Y==0)         \
          && (!defined (LCD_LUT_SEG))
        SET_X_INCREMENT();
        xsize += Diff & 3;
        for (i = Diff; i < xsize; i++) {
          DrawBitLine2BPP_Swap(
            x0+i, y0,
            pData + (i>>2),
            ysize,
            pTrans,
            BytesPerLine,
            i
          );
        }
        SET_Y_INCREMENT();
        break;
      #else
        for (i=0; i<ysize; i++) {
          DrawBitLine2BPP(x0, i+y0, pData, Diff, xsize, pTrans);
          pData += BytesPerLine;
        }
        break;
      #endif
    #endif
    #if (LCD_MAX_LOG_COLORS > 4)
      case 4:
        for (i=0; i<ysize; i++) {
          DrawBitLine4BPP(x0, i+y0, pData, Diff, xsize, pTrans);
          pData += BytesPerLine;
        }
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 16)
      case 8:
        for (i=0; i<ysize; i++) {
          DrawBitLine8BPP(x0, i+y0, pData, xsize, pTrans);
          pData += BytesPerLine;
        }
        break;
    #endif
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
  aState[0].ConReg0 = (LCD_INIT_R00) & ~(1<<6);
  LCD_WriteReg0( 0, aState[0].ConReg0);
}

void LCD_On           (void) {
  aState[0].ConReg0 = (LCD_INIT_R00) |  (1<<6);
  LCD_WriteReg0( 0, aState[0].ConReg0);
}

/*
        *********************************************************
        *                                                       *
        *       LCD_L0_ReInit : Re-Init the display                *
        *                                                       *
        *********************************************************

ReInit contains all of the code that can be re-executed at any point without
changing or even disturbing what can be seen on the LCD.
Note that it is also used as a subroutine by LCD_L0_Init().

*/

void  LCD_L0_ReInit(void) {
  LCD_INIT_CONTROLLER();
  aState[0].ConReg0 = (LCD_INIT_R00) | 0x80;
  aState[0].ConReg1 = (LCD_INIT_R01) & (~2);
/* Write control register 0, 1 */
  LCD_WriteReg0( 0, aState[0].ConReg0); /* Control register 1 */ \
  LCD_WriteReg0( 1, aState[0].ConReg1); /* Control register 2 */ \

}

/*
        *********************************************************
        *                                                       *
        *       LCD_Init : Init the display                     *
        *                                                       *
        *********************************************************
*/

int  LCD_L0_Init(void) {
  U8 Data;
  GUI_DEBUG_LOG("\nLCD_L0_Init()");
/* Invalidate register cache */
  { int i;
    for (i=0; i<LCD_NUM_CONTROLLERS; i++) {
     aState[i].x = aState[i].y = 255;
    }
  }
  LCD_L0_ReInit();
/* Check memory */
  SET_X0(1);
  SET_Y0(2);
  WRITE_VMEM0(0x12);
  SET_X0(3);
  SET_Y0(4);
  WRITE_VMEM0(0x34);
  SET_X0(1);
  SET_Y0(2);
  READ_VMEM0(Data);
  if (Data != 0x12) {
    GUI_DEBUG_ERROROUT("\nLCD6642X: video memory problem");
    return LCD_ERR_MEMORY;
  }
  SET_X0(3);
  SET_Y0(4);
  READ_VMEM0(Data);
  if (Data != 0x34) {
    GUI_DEBUG_ERROROUT("\nLCD6642X: video memory problem");
    return LCD_ERR_MEMORY;
  }
/* Fill LCD memory with gray scale bar */
  #if 1
  {
    int x, y;
    int MaxX, MaxY;
    int IncX = (aState[0].ConReg1 & 1<<1) ? 1 : 0;
    if (IncX) {
      MaxX = MAX_COMS;
      MaxY = MAX_SEGS/4;
    } else {
      MaxY = MAX_COMS;
      MaxX = MAX_SEGS/4;
    }
    for (x=0; x < MaxX; x++) {
      if (IncX) {
        SET_X0(0);
        SET_Y0(x);
      } else {
        SET_X0(x);
        SET_Y0(0);
      }
      for (y=0; y<MaxY; y++) {
        WRITE_VMEM0(0x00);
      }
    }
  }
  #endif
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

void LCD6642X(void) { } /* avoid empty object files */

#endif  /* Right LCD_CONTROLLER */

