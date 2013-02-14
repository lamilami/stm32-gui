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
File        : LCD15XX.C
Purpose     : Driver for LCDs using Seiko Epson SED15XX controllers     
              The current version supports up to 4 LCD controllers in   
              (almost) any hardware configuration. The following
               derivatives are currently supported:
               Epson SED1560
               Epson SED1565  132*65  BW
               Epson SED1566  132*49  BW   (untested due to lack of hardware)
               Epson SED1567  132*33  BW   (untested due to lack of hardware)
               Epson SED1568  132*55  BW   (untested due to lack of hardware)
               Epson SED1569  132*53  BW   (untested due to lack of hardware)
               Epson SED1575  132*200 BW
               Samsung KS0108B
               Hitachi HD61202
               
               Other Epson LCD controllers are very similar and could
               be covered by this driver as well, but are not
               currently supported.
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
2.02e   020716 JE     a) Support for KS0108B & HD61202 added
2.02d   020715 JE     a) Reworked to work with 2 LCD-controllers
2.02c   020204 JE     a) Hardwareinterface routines renamed:
                         ...DATA -> ...A1, ...CMD -> ...A0
2.02b   010706 JE     a) BUGFIXES: DrawBitLine1BPP_NoSwap
2.02a   010402 RS     a) LCD_GetDevCaps removed from driver
                         (now LCD.c)
2.02    010329 JE     a) Completely revised, tested without mirror & swap
2.00    001107 RS     a) New driver interface V2.00 used
1.32.01 000321 RS     a) BUGFIX: LCD__ClearVRam: aCAdr set to LCD_SEGS_MAX-1
                      b) BUGFIX: Flush: DataR_Cache = DataW_Cache inserted
               JE     c) BUGFIX: ASSIGN_PIXEL_FAST now takes account 
                         of LCD_DRAWMODE_XOR
                      d) BUGFIX: DrawBitLine1BPP_NoSwap XORMODE now works
                      e) BUGFIX: DrawBitLine1BPP_NoSwap clipping now works
                      f) BUGFIX: FindByte: -LCD_FIRSTSEG0 removed
                      g) BUGFIX: LCD_RefreshSection: -LCD_FIRSTSEG0 removed
                      h) LCD_DrawBit now checks number of colors
1.32.00 990930 RS     a) LCD_Init now returns an int
                      b) bit changed -> Bit in order to vaoid problems
                         with IAR compilers
1.31.06 990926 RS     a) Code is generated now only if LCD_CONTROLLER
                         is in the range of 1500 - 1599, allowing to
						 compile all LCD drivers with a project, making
						 the selection in the config file.
					  b) Config defaults added
1.31.05 990922 RS/BB  a) Number of Segments for 1575 changed from 168
                         to 200. 200 is correct because the controller
						 has RAM for 200 segments, even thou just 168
						 segment lines
					  b) Transparency support for bitmaps in
					     DrawBitLine1BPP_Swap added
1.31.04 990810 RS     a) LCD__ClearVRam: Cut and paste error elimiated
                         (Relevant only in 4 controller system)
					  b) Transparency problem in DrawBitLine1BPP_Swap
					     eliminated
					  c) CALCXY: LCD_FIRSTSEG had been subtracted,
					     but had already been subtracted before. Could
						 lead to a an offset in the memory area used as
						 video RAM if LCD_FIRSTSEG<x>  != 0.
						 Fixed.
					  d) FlushCache-routine simplified for easier
					     maintanance using a macro
				      e) Bugfix in FlushCache-routine --- untested
					     due to lack of hardware !
1.31.03 990720 RS     a) Compile problem in single-controller system
                         (CurController) fixed
                      b) GotoYPlus1(void) Prototype: Parameterlist:
					     () replaced by (void) to avoid comiler warning
1.31.02 990713 RS     a) All (global/static) variables are initialized in
                         LCD_Init. This turned out to be necessary as not
						 all systems comply with ANSI-"C" and automatically
						 initialize	these variables with 0.
1.31.01 990712 RS     a) Cache locking bug for systems with seg/Com lookup
                         tables fixed. Cache writeout accelerated.
1.31.00 990712 RS     a) FindByte made leaner and converted to a macro
                         for 2 controller systems, resulting in improved
						 performance
					  b) Internal DrawLine /DrawBitmap routines
					     improved for higher performance and better
						 readability
					  c) Inline versions of SetPixel/ClrPixel created, as
					     well as fast versions of ASSIGN_PIXEL
						 (again: for better performance !)
1.30.03 990709 RS     a) Structural changes leading to clearer
                         structure and higher performance
    	              b) FindByte Optimization for 2-Controller system
	        	      c) Bugfix: One of the previous optimizations
		                 could lead to a duplicated byte in video memory
             			 when LCD_DrawByte was called fo very
			             narrow bitmaps. Fixed.
1.30.02 990708 RS     a) ReadData optimized if all bytes are
                         in Cache (macro, no switch statement)
1.30.01 990707 RS     a) Add. Optimization in FindByte
1.30.00 990707 RS     a) Various optimizations impemented, esp.
                         if translation (lookup) table for COMs is
                                          activated
1.21.02 990617 RS     a) Macro bug (created in 1.21.01) cleaned up
                      b) Page 8 of all controllers cleared during
                         init in order to make sure that the COMS
                         signal can be used and the data for it is
                         cleared to 0
                      c) Problem with segment table fixed ...
                         If used, the segments were moved by LCD_FIRSTSEG<X>
1.21.01 990615 RS     a) Some more macros generated in order to
                         keep the driver easy to maintain
                      b) Com-offset is now subtracted from Cache<X>
                         index (in order to avoid potential bounds
                         problem): e.g.:
                         Cache0[Page][Col] --> Cache0[Page][Col-LCD_FIRSTSEG0]
1.21.00 990615 RS     a) When using segment/com lookup tables,
                         the macro-values
                         LCD_NUM_COMS0, LCD_NUM_COMS0
                         LCD_NUM_COMS1, LCD_NUM_COMS1 (controller 1)
                         Have to be defined.
                         Add. configuration checking added.
1.20.02 990614 RS     a) LCD_Init did not clear VMem for 3. and 4.
                         controller. Fixed.
                         configuration switches eliminated
1.20.01 990614 RS     a) Problem with certain combination of
                         configuration switches eliminated
1.20.00 990614 RS     a) Optional segment and com translation tables
                         supported. This turned out to be necessary
                         as with some LCDs the COM/SEG lines are
                         completely mixed up. The translation tables
                         have to be defined in a seperate file
                         (sample supplied in LCDTable.c) in
                         order to make sure that the code in this
                         driver does not have to be changed.
1.10.00 990505 RS     a) Optional support for Cache locking added.
                         It now requires the add. configuration switch
                         LCD_SUPPORT_CACHECONTROL
1.04.00 990420 AW/RS  a) Support for 1560 added.
1.03.03 990322 RS     a) Bitmaps have not been properly cut off at the
                         end of the clipping region. Fixed
                      b) Clipping for horizontal/vert. lines
                         implemented
1.03.02 990319 RS     a) When writing bitmaps in XOR-Mode, the LCD   
                         cache was not automatically flushed.
                         Fixed.
1.03.01 990319 RS     a) (Kuennemann) If multiple LCD-controllers had
                         been used in a horizontal array (different
                         SEG lines with SEG<X> > 0) the page
                         calculation did not take the SEG<X> value
                         into account. Fixed.
                      b) (Kuennemann)
                         LCD_Init(): VRAM of controller2/3 was not
                         cleared in a 3 or 4 controller system.
                         Fixed.
                      c) LCD_SetInverse / LCD_ClrInverse:
                         These routines did not write the command to
                         all LCD-controllers, but only to the first
                         one. Fixed.
1.03.00 990317 RS     a) XOR Mode implemented for all configurations
                      b) DrawVLine accelerated
1.02.03 990218 RS     a) (Kuennemann) If multiple LCD-controllers had
                         been used in a vertical array (different
                         COM lines with COM<X> > 0) the page
                         calculation did not take the COM<X> value
                         into account. Fixed.
                      b) Driver should now also work with 4
                         controllers. However, this configuration is
                         still untested. The #error is taken out.
1.02.02 990217 RS     a) LCD_GetVisPage, LCD_GetSelPage added
1.02.01 990216 RS     a) LCD_GetPixel implemented
                      b) Support for GetDeviceCaps added
                      c) Support for Drawmode can now be disabled via
                         config switch
1.02.00 990212 RS     a) Include file string.h put back in in order to
                      be able to completly reset the LCD, including
                      clearing the cache
                      b) LCD_Refresh implemented
                      c) Support for physical bitmaps added
                      d) Support for LCD_REVERSE added
                      e) Support for Write-thru cache added
1.01.01 990203 RS     a) Include file string.h no longer needed,
                      taken out
1.01.00 990203 RS     a) Cache no longer filled with 0 using memset
                       (We trust the compiler to do the job for us.)
1.00.02 990202 RS     Support for up to 4 controllers implemented
1.00.01 990128 RS     Changes in header-configuration  as discussed
                      with BB
1.00    990118 RS     First release for up to 2 LCD controllers *
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
Due to the change to interface version 2.0,
The draw bitline routines has been temp. disabled
The routines:
LCD_L0_SetPixelIndex
LCD_L0_XorPixel
LCD_L0_GetPixelIndex
need to be proberly implemented
----------------------------------------------------------------------
Possible optimizations
----------------------------------------------------------------------
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>             /* for memset */
#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include "LCD_0.h"            /* Defines for first display */

#if   (   (LCD_CONTROLLER/100 ==    15) \
       || (LCD_CONTROLLER     ==  0713) \
       || (LCD_CONTROLLER     ==   108) \
       || (LCD_CONTROLLER     == 61202) \
      ) \
      && (LCD_CONTROLLER/100 != 0x15E05 ) \
      && (!defined(WIN32) | defined(LCD_SIMCONTROLLER))

/*
        *********************************************************
        *                                                       *
        *           Compiler specific settings                  *
        *                                                       *
        *********************************************************

*/

#ifdef WIN32   /* Avoid warnings in MS-compiler */
  #pragma warning(disable : 4244)  // warning C4244: '=' : conversion from 'long ' to 'unsigned char ', possible loss of data
  #pragma warning(disable : 4761)  // warning C4761: integral size mismatch in argument; conversion supplied
  #pragma warning(disable : 4305)  // warning C4305: '=' : truncation from 'const int ' to ...
#endif


#ifndef LCD_DISPLAY_INDEX
  #define LCD_DISPLAY_INDEX 0
#endif


/*********************************************************************
*
*      Map hardware macros
*
**********************************************************************
*/

/* mapping for multi-display configuration */
#if (LCD_NUM_DISPLAYS > 1)
  #if   (LCD_DISPLAY_INDEX == 0)     /* First display in a multi-display configuration */
    #define LCD_WRITE_A0   LCD_WRITE_A0_0
    #define LCD_WRITE_A1   LCD_WRITE_A1_0
    #define LCD_WRITE_A0C1 LCD_WRITE_A0C1_0
    #define LCD_WRITE_A1C1 LCD_WRITE_A1C1_0
    #define LCD_WRITE_A0C2 LCD_WRITE_A0C2_0
    #define LCD_WRITE_A1C2 LCD_WRITE_A1C2_0
    #define LCD_WRITE_A0C3 LCD_WRITE_A0C3_0
    #define LCD_WRITE_A1C3 LCD_WRITE_A1C3_0
    #define LCD_READ_A0    LCD_READ_A0_0
    #define LCD_READ_A0    LCD_READ_A0_0
    #define LCD_READ_A0C1  LCD_READ_A0C1_0
    #define LCD_READ_A0C1  LCD_READ_A0C1_0
    #define LCD_READ_A0C2  LCD_READ_A0C2_0
    #define LCD_READ_A0C2  LCD_READ_A0C2_0
    #define LCD_READ_A0C3  LCD_READ_A0C3_0
    #define LCD_READ_A0C3  LCD_READ_A0C3_0
  #elif (LCD_DISPLAY_INDEX == 1)  /* Second display in a multi-display configuration */
    #define LCD_WRITE_A0   LCD_WRITE_A0_1
    #define LCD_WRITE_A1   LCD_WRITE_A1_1
    #define LCD_WRITE_A0C1 LCD_WRITE_A0C1_1
    #define LCD_WRITE_A1C1 LCD_WRITE_A1C1_1
    #define LCD_WRITE_A0C2 LCD_WRITE_A0C2_1
    #define LCD_WRITE_A1C2 LCD_WRITE_A1C2_1
    #define LCD_WRITE_A0C3 LCD_WRITE_A0C3_1
    #define LCD_WRITE_A1C3 LCD_WRITE_A1C3_1
    #define LCD_READ_A0    LCD_READ_A0_1
    #define LCD_READ_A0    LCD_READ_A0_1
    #define LCD_READ_A0C1  LCD_READ_A0C1_1
    #define LCD_READ_A0C1  LCD_READ_A0C1_1
    #define LCD_READ_A0C2  LCD_READ_A0C2_1
    #define LCD_READ_A0C2  LCD_READ_A0C2_1
    #define LCD_READ_A0C3  LCD_READ_A0C3_1
    #define LCD_READ_A0C3  LCD_READ_A0C3_1
  #else
    #error This many displays not yet supported !
  #endif
#endif

/* Command definitions in dependence of selected LCD-controller */
#if   (LCD_CONTROLLER/100 == 15) || (LCD_CONTROLLER     ==  0713)
  #define SET_PAGE0(Page) LCD_WriteSingleCommand0(0xb0 + Page)
  #define SET_CADR0(Col)  LCD_WriteDoubleCommand0(0x10 + (Col >> 4), 0x00 + (Col & 0xf))
  #define CMD_LCD_ON      0xaf
  #define CMD_LCD_OFF     0xae
  #define WAIT0()
  #define WAIT1()
  #define WAIT2()
  #define WAIT3()
#elif (LCD_CONTROLLER ==  108) || (LCD_CONTROLLER == 61202)
  static int _Status;
  #define SET_PAGE0(Page) LCD_WriteSingleCommand0(0xb8 + Page);
  #define SET_CADR0(Col)  LCD_WriteSingleCommand0(0x40 + Col);
  #if (LCD_NUM_CONTROLLERS > 1)
    #define SET_PAGE1(Page) LCD_WriteSingleCommand1(0xb8 + Page);
    #define SET_CADR1(Col)  LCD_WriteSingleCommand1(0x40 + Col);
  #endif
  #define CMD_LCD_ON      0x3f
  #define CMD_LCD_OFF     0x3e
  #define WAIT0()         do { LCD_READ_A0(_Status); }   while (_Status & 0x80);
  #define WAIT1()         do { LCD_READ_A0C1(_Status); } while (_Status & 0x80);
  #define WAIT2()         do { LCD_READ_A0C2(_Status); } while (_Status & 0x80);
  #define WAIT3()         do { LCD_READ_A0C3(_Status); } while (_Status & 0x80);
#else
  #error LCD-controller not supported!
#endif

#ifdef WIN32     /* SEGGER internal simulation */
  void SIM_WriteA1C0(U8 Data);
  void SIM_WriteA0C0(U8 cmd);
  U8   SIM_ReadA0C0(void);
  U8   SIM_ReadA1C0(void);
  #define WRITE_DATA0(Data) SIM_WriteA1C0(Data) 
  #define WRITE_CMD0(cmd)   SIM_WriteA0C0(cmd)
  #define READ_DATA0(Data)  Data = SIM_ReadA1C0()
  #define READ_CMD0(cmd)    cmd  = SIM_ReadA0C0()
  #define INIT_CONTROLLER()
  #if LCD_NUM_CONTROLLERS > 1
    void SIM_WriteA1C1(U8 Data);
    void SIM_WriteA0C1(U8 cmd);
    U8   SIM_ReadA0C1(void);
    U8   SIM_ReadA1C1(void);
    #define WRITE_DATA1(Data) SIM_WriteA1C1(Data) 
    #define WRITE_CMD1(cmd)   SIM_WriteA0C1(cmd)
    #define READ_DATA1(Data)  Data = SIM_ReadA1C1()
    #define READ_CMD1(cmd)    cmd  = SIM_ReadA0C1()
  #endif
  #if LCD_NUM_CONTROLLERS > 2
    void SIM_WriteA1C2(U8 Data);
    void SIM_WriteA0C2(U8 cmd);
    U8   SIM_ReadA0C2(void);
    U8   SIM_ReadA1C2(void);
    #define WRITE_DATA2(Data) SIM_WriteA1C2(Data) 
    #define WRITE_CMD2(cmd)   SIM_WriteA0C2(cmd)
    #define READ_DATA2(Data)  Data = SIM_ReadA1C2()
    #define READ_CMD2(cmd)    cmd  = SIM_ReadA0C2()
  #endif
  #if LCD_NUM_CONTROLLERS > 3
    void SIM_WriteA1C3(U8 Data);
    void SIM_WriteA0C3(U8 cmd);
    U8   SIM_ReadA0C3(void);
    U8   SIM_ReadA1C3(void);
    #define WRITE_DATA3(Data) SIM_WriteA1C3(Data) 
    #define WRITE_CMD3(cmd)   SIM_WriteA0C3(cmd)
    #define READ_DATA3(Data)  Data = SIM_ReadA1C3()
    #define READ_CMD3(cmd)    cmd  = SIM_ReadA0C3()
  #endif
#else
  #define WRITE_CMD0(cmd)   WAIT0(); LCD_WRITE_A0(cmd)
  #define WRITE_DATA0(Data) WAIT0(); LCD_WRITE_A1(Data)
  #define READ_DATA0(Data)  WAIT0(); LCD_READ_A1(Data)
  #define READ_CMD0(cmd)    WAIT0(); LCD_READ_A0(cmd)
  #define INIT_CONTROLLER  LCD_INIT_CONTROLLER
  #if LCD_NUM_CONTROLLERS > 1
    #define WRITE_CMD1(cmd)   WAIT1(); LCD_WRITE_A0C1(cmd)
    #define WRITE_DATA1(Data) WAIT1(); LCD_WRITE_A1C1(Data)
    #define READ_DATA1(Data)  WAIT1(); LCD_READ_A1C1(Data)
    #define READ_CMD1(cmd)    WAIT1(); LCD_READ_A0C1(cmd)
  #endif
  #if LCD_NUM_CONTROLLERS > 2
    #define WRITE_CMD2(cmd)   WAIT(2); LCD_WRITE_A0C2(cmd)
    #define WRITE_DATA2(Data) WAIT(2); LCD_WRITE_A1C2(Data)
    #define READ_DATA2(Data)  WAIT(2); LCD_READ_A1C2(Data)
    #define READ_CMD2(cmd)    WAIT(2); LCD_READ_A0C2(cmd)
  #endif
  #if LCD_NUM_CONTROLLERS > 3
    #define WRITE_CMD3(cmd)   WAIT(3); LCD_WRITE_A0C3(cmd)
    #define WRITE_DATA3(Data) WAIT(3); LCD_WRITE_A1C3(Data)
    #define READ_DATA3(Data)  WAIT(3); LCD_READ_A1C3(Data)
    #define READ_CMD3(cmd)    WAIT(3); LCD_READ_A0C3(cmd)
  #endif
#endif

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
  ********************************************************************
  *                                                                  *
  *                Defaults for config switches                      *
  *                                                                  *
  ********************************************************************
*/

#ifndef LCD_CACHE
  #define  LCD_CACHE (1)
#endif

#ifndef LCD_SUPPORT_REFRESH
  #define  LCD_SUPPORT_REFRESH LCD_CACHE
#endif

#ifndef LCD_REVERSEMODE_SUPPORT
  #define LCD_REVERSEMODE_SUPPORT (0)
#endif

#ifndef LCD_SUPPORT_VERIFY
  #define LCD_SUPPORT_VERIFY (0)
#endif

/* Drivers supports anti-aliasing if active. */
#ifndef LCD_SUPPORT_ANTIALIASING
  #define LCD_SUPPORT_ANTIALIASING (0)
#endif

/* Switch for support of cache control (locking) */
#ifndef  LCD_SUPPORT_CACHECONTROL
  #define  LCD_SUPPORT_CACHECONTROL     (1)
#endif

/* Switch support for the LCD_CopyRect function of the driver */
#ifndef  LCD_SUPPORT_COPYRECT
  #define  LCD_SUPPORT_COPYRECT         (1)
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
  #define LCD_SUPPORT_SETORG            (0)
#endif

/* Switch for support of refreshing video RAM. */
#ifndef LCD_SUPPORT_REFRESH
  #define LCD_SUPPORT_REFRESH           (0)
#endif

#ifndef LCD_SCHEDULE_CNT
  #define LCD_SCHEDULE_CNT 0
#endif

#ifndef LCD_NUM_CONTROLLERS
  #define LCD_NUM_CONTROLLERS (1)
#endif

#ifndef LCD_LOCK
  #define LCD_LOCK()
#endif

#ifndef LCD_UNLOCK
  #define LCD_UNLOCK()
#endif

#ifndef LCD_READABLE
  #define LCD_READABLE (0)
#endif
  
#ifndef LCD_CACHE_WRITETHRU  
  #define LCD_CACHE_WRITETHRU (0)
#endif

#ifndef LCD_SUPPORT_RT_INVERSION  
  #define LCD_SUPPORT_RT_INVERSION  (0)
#endif

#ifndef LCD_SUPPORT_CHECKINIT
  #define LCD_SUPPORT_CHECKINIT (0)
#endif

/*
  ********************************************************************
  *                                                                  *
  *                Explicit externals                                *
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
  #if (LCD_NUM_CONTROLLERS >1)
    extern U8 LCD__aLine2Com1[LCD_LASTCOM1-LCD_FIRSTCOM1+1];
  #endif
  #if (LCD_NUM_CONTROLLERS >2)
    extern U8 LCD__aLine2Com2[LCD_LASTCOM2-LCD_FIRSTCOM2+1];
  #endif
  #if (LCD_NUM_CONTROLLERS >3)
    extern U8 LCD__aLine2Com3[LCD_LASTCOM3-LCD_FIRSTCOM3+1];
  #endif
#endif

#if LCD_SUPPORT_SEGTRANS
  extern U8 LCD__aRow2Seg0[LCD_LASTSEG0-LCD_FIRSTSEG0+1];
  #if (LCD_NUM_CONTROLLERS >1)
    extern U8 LCD__aRow2Seg1[LCD_LASTSEG1-LCD_FIRSTSEG1+1];
  #endif
  #if (LCD_NUM_CONTROLLERS >2)
    extern U8 LCD__aRow2Seg2[LCD_LASTSEG2-LCD_FIRSTSEG2+1];
  #endif
  #if (LCD_NUM_CONTROLLERS >3)
    extern U8 LCD__aRow2Seg3[LCD_LASTSEG3-LCD_FIRSTSEG3+1];
  #endif
#endif

/*
  ********************************************************************
  *                                                                  *
  *                Internal types                                    *
  *                                                                  *
  ********************************************************************
*/

/*
  ********************************************************************
  *                                                                  *
  *                SCHEDULING                                        *
  *                                                                  *
  ********************************************************************
*/

#if LCD_SCHEDULE_CNT
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
  ********************************************************************
  *                                                                  *
  *                 Macro calculations                               *
  *                                                                  *
  ********************************************************************
*/

/* To make life easier, assign physical x/y size */
#if !LCD_SWAP_XY
  #define LCD_XSIZE_P LCD_XSIZE
  #define LCD_YSIZE_P LCD_YSIZE
#else
  #define LCD_XSIZE_P LCD_YSIZE
  #define LCD_YSIZE_P LCD_XSIZE
#endif


/* Define number of available segments of controller */

#if (LCD_CONTROLLER == 1560)
  #define LCD_COMS_MAX 64
  #define LCD_SEGS_MAX  102
#elif (LCD_CONTROLLER == 1565)
  #define LCD_COMS_MAX 65
  #define LCD_SEGS_MAX  132
#elif (LCD_CONTROLLER == 1566)
  #define LCD_COMS_MAX 49
  #define LCD_SEGS_MAX  132
#elif (LCD_CONTROLLER == 1567)
  #define LCD_COMS_MAX 33
  #define LCD_SEGS_MAX  132
#elif (LCD_CONTROLLER == 1568)
  #define LCD_COMS_MAX 55
  #define LCD_SEGS_MAX  132
#elif (LCD_CONTROLLER == 1569)
  #define LCD_COMS_MAX 53
  #define LCD_SEGS_MAX  132
#elif (LCD_CONTROLLER == 1575)
  #define LCD_COMS_MAX 65
  #define LCD_SEGS_MAX  200
#elif (LCD_CONTROLLER == 0713)
  #define LCD_COMS_MAX 65
  #define LCD_SEGS_MAX  132
#elif (LCD_CONTROLLER == 108)
  #define LCD_COMS_MAX 64
  #define LCD_SEGS_MAX 64
#elif (LCD_CONTROLLER == 61202)
  #define LCD_COMS_MAX 64
  #define LCD_SEGS_MAX 64
#else
  #error Please define a controller to use !
#endif

/* Define number of used coms/segments per controller */
#if !LCD_SUPPORT_SEGTRANS
  #define LCD_NUM_SEGS0 (LCD_LASTSEG0-LCD_FIRSTSEG0+1)
#else
  #ifndef LCD_NUM_SEGS0
    #error Please define LCD_NUM_SEGS0 in your configuratiuon file LCDConf.h
  #endif
#endif

#if !LCD_SUPPORT_COMTRANS
  #define LCD_NUM_COMS0 (LCD_LASTCOM0-LCD_FIRSTCOM0+1)
#else
  #ifndef LCD_NUM_COMS0
    #error Please define LCD_NUM_COMS0 in your configuratiuon file LCDConf.h
  #endif
#endif

#if (LCD_NUM_CONTROLLERS >1)
  #if !LCD_SUPPORT_SEGTRANS
    #define LCD_NUM_SEGS1 (LCD_LASTSEG1-LCD_FIRSTSEG1+1)
  #else
    #ifndef LCD_NUM_SEGS1
      #error Please define LCD_NUM_SEGS1 in your configuratiuon file LCDConf.h
    #endif
  #endif
  #if !LCD_SUPPORT_COMTRANS
    #define LCD_NUM_COMS1 (LCD_LASTCOM1-LCD_FIRSTCOM1+1)
  #else
    #ifndef LCD_NUM_COMS1
      #error Please define LCD_NUM_COMS1 in your configuratiuon file LCDConf.h
    #endif
  #endif
#endif

#if (LCD_NUM_CONTROLLERS >2)
  #define LCD_NUM_SEGS2 (LCD_LASTSEG2-LCD_FIRSTSEG2+1)
  #define LCD_NUM_COMS2 (LCD_LASTCOM2-LCD_FIRSTCOM2+1)
#endif
#if (LCD_NUM_CONTROLLERS >3)
  #define LCD_NUM_SEGS3 (LCD_LASTSEG3-LCD_FIRSTSEG3+1)
  #define LCD_NUM_COMS3 (LCD_LASTCOM3-LCD_FIRSTCOM3+1)
#endif

/* Define total number of used coms/segments */
#if (LCD_NUM_CONTROLLERS ==1)
  #define LCD_NUM_SEGS LCD_NUM_SEGS0
  #define LCD_NUM_COMS LCD_NUM_COMS0
#elif (LCD_NUM_CONTROLLERS ==2)
  #define LCD_NUM_SEGS (LCD_NUM_SEGS0+LCD_NUM_SEGS1)
  #define LCD_NUM_COMS (LCD_NUM_COMS0+LCD_NUM_COMS1)
#elif (LCD_NUM_CONTROLLERS ==3)
  #define LCD_NUM_SEGS (LCD_NUM_SEGS0+LCD_NUM_SEGS1+LCD_NUM_SEGS2)
  #define LCD_NUM_COMS (LCD_NUM_COMS0+LCD_NUM_COMS1+LCD_NUM_COMS2)
#elif (LCD_NUM_CONTROLLERS ==4)
  #define LCD_NUM_SEGS (LCD_NUM_SEGS0+LCD_NUM_SEGS1+LCD_NUM_SEGS2+LCD_NUM_SEGS3)
  #define LCD_NUM_COMS (LCD_NUM_COMS0+LCD_NUM_COMS1+LCD_NUM_COMS2+LCD_NUM_COMS3)
#endif

/* Calc. the first column to actually write to. This is not as
   easy as it seems, because if we mirror X, the controller
   uses different columns in video memory to store the data.
   If you use lookup tables for segment lines, the offsets are 0
   because the right values are in the table
*/
#if LCD_SUPPORT_SEGTRANS==0
  #if !LCD_MIRROR_X
    #define LCD_SEGOFF0 LCD_FIRSTSEG0
    #define LCD_SEGOFF1 (LCD_XORG1 - LCD_FIRSTSEG1)
    #define LCD_SEGOFF2 (LCD_XORG2 - LCD_FIRSTSEG2)
    #define LCD_SEGOFF3 (LCD_XORG3 - LCD_FIRSTSEG3)
  #else
    #define LCD_SEGOFF0 (LCD_SEGS_MAX-LCD_LASTSEG0-1)
    #define LCD_SEGOFF1 (LCD_SEGS_MAX-LCD_LASTSEG1-1)
    #define LCD_SEGOFF2 (LCD_SEGS_MAX-LCD_LASTSEG2-1)
    #define LCD_SEGOFF3 (LCD_SEGS_MAX-LCD_LASTSEG3-1)
  #endif
#else
    #define LCD_SEGOFF0 0
    #define LCD_SEGOFF1 0
    #define LCD_SEGOFF2 0
    #define LCD_SEGOFF3 0
#endif


#if !LCD_REVERSE
  #define  LCD_CMDNORMAL  0xa6
  #define  LCD_CMDREVERSE 0xa7
#else
  #define  LCD_CMDNORMAL  0xa7
  #define  LCD_CMDREVERSE 0xa6
#endif


/*
  ********************************************************************
  *                                                                  *
  *            Configuration switch checking                         *
  *                                                                  *
  ********************************************************************

Please be aware that not all configuration errors can be captured !

*/

#if (LCD_SUPPORT_REFRESH && !LCD_CACHE)
  #error Cache has to be enabled in order to support refresh !
#endif

#if (LCD_BITSPERPIXEL != 1)
  #error This controller can handle only b/w displays
#endif

/* Check number of controllers */
#if ((LCD_NUM_CONTROLLERS >4) || (LCD_NUM_CONTROLLERS <0))
  #error "More than 4 controllers not supported !"
#endif

/* Check if number of segments / coms equals resolution */
#if (LCD_NUM_SEGS < LCD_XSIZE_P)
  #error Please check segment setup of controller 0 and X/YSIZE !!!
#endif
#if (LCD_NUM_COMS < LCD_YSIZE_P)
  #error Please check com setup of controller 0 and X/YSIZE !!!
#endif

/*
  ********************************************************************
  *                                                                  *
  *       Standard variables for driver                              *
  *                                                                  *
  ********************************************************************
*/

#define BKCOLOR LCD_BKCOLORINDEX
#define   COLOR LCD_COLORINDEX

static LCD_RECT ClipRect;
#if LCD_SUPPORT_VERIFY
  static int ErrCnt;
  static int ErrStat;
#endif

/*
        *****************************************
        *                                       *
        *   Memory areas for caching (optional) *
        *                                       *
        *****************************************

The cache stores only the bytes actually used in every controller.
This is also the reason why different arrays are used for every
controller.
*/

#if LCD_CACHE
  /* Handle controller #0 */
  #define NUM_COMS0   (LCD_LASTCOM0-LCD_FIRSTCOM0+1)
  #define NUM_PAGES0  ((NUM_COMS0+7)/8)
  #define NUM_COLS0    (LCD_LASTSEG0-LCD_FIRSTSEG0+1)
  static U8 Cache0[NUM_PAGES0][NUM_COLS0];
/* Check configuration a bit to capture the worst mistakes ...  */
  #if (NUM_COLS0<LCD_NUM_SEGS0)
    #error Configuration error ! Please check LCD_LASTSEG0, LCD_FIRSTSEG0
  #endif
  #if (NUM_COMS0<LCD_NUM_COMS0)
    #error Configuration error ! Please check LCD_LASTCOM0, LCD_FIRSTCOM0
  #endif
  /* Handle controller #1 */
  #if (LCD_NUM_CONTROLLERS >1)
    #define NUM_COMS1   (LCD_LASTCOM1-LCD_FIRSTCOM1+1)
    #define NUM_PAGES1  ((NUM_COMS1+7)/8)
    #define NUM_COLS1    (LCD_LASTSEG1-LCD_FIRSTSEG1+1)
    static U8 Cache1[NUM_PAGES1][NUM_COLS1];
/* Check configuration a bit to capture the worst mistakes ...  */
    #if (NUM_COLS1<LCD_NUM_SEGS1)
      #error Configuration error ! Please check LCD_LASTSEG1, LCD_FIRSTSEG1
    #endif
    #if (NUM_COMS1<LCD_NUM_COMS1)
      #error Configuration error ! Please check LCD_LASTCOM1, LCD_FIRSTCOM1
    #endif
  #endif
  /* Handle controller #2 */
  #if (LCD_NUM_CONTROLLERS >2)
    #define NUM_PAGES2  ((LCD_LASTCOM2-LCD_FIRSTCOM2+1+7)/8)
    #define NUM_COLS2    (LCD_LASTSEG2-LCD_FIRSTSEG2+1)
    static U8 Cache2[NUM_PAGES2][NUM_COLS2];
  #endif
  /* Handle controller #3 */
  #if (LCD_NUM_CONTROLLERS >3)
    #define NUM_PAGES3  ((LCD_LASTCOM3-LCD_FIRSTCOM3+1+7)/8)
    #define NUM_COLS3    (LCD_LASTSEG3-LCD_FIRSTSEG3+1)
    static U8 Cache3[NUM_PAGES3][NUM_COLS3];
  #endif
#endif

/*
  ********************************************************************
  *                                                                  *
  *                Write Cache variables                             *
  *                                                                  *
  ********************************************************************
*/

#if  LCD_SUPPORT_CACHECONTROL
  static char CacheStat   =0;     /* 0: No changes */
  static char CacheLocked =0;     /* 0: Not locked */
  static U8   aaCacheDirtyTag0[NUM_PAGES0][(NUM_COLS0+7)/8];
  #if (LCD_NUM_CONTROLLERS >1)
    static U8   aaCacheDirtyTag1[NUM_PAGES1][(NUM_COLS1+7)/8];
  #endif
  #if (LCD_NUM_CONTROLLERS >2)
    static U8   aaCacheDirtyTag2[NUM_PAGES2][(NUM_COLS2+7)/8];
  #endif
  #if (LCD_NUM_CONTROLLERS >3)
    static U8   aaCacheDirtyTag3[NUM_PAGES3][(NUM_COLS3+7)/8];
  #endif
#endif

/*
  ********************************************************************
  *                                                                  *
  *                  Hardware access, low level                      *
  *                                                                  *
  *           Write Command/Data, Reset                              *
  *           Read  Command/data if possible (LCD readable)          *
  *                                                                  *
  ********************************************************************

  The following routines are used for all access to the
  LCD-controller(s).
*/

/* This macro can be used to check how much time is used up
   for management and how much for hardware access */
#ifdef LCD_TESTSPEED
  #undef  WRITE_DATA0
  #undef  WRITE_CMD0
  #undef  WRITE_DATA1
  #undef  WRITE_CMD1
  #define WRITE_DATA0(p0)
  #define WRITE_CMD0(p0)
  #define WRITE_DATA1(p0)
  #define WRITE_CMD1(p0)
#endif


        /****************************************
        *                                       *
        *        Write Data                     *
        *                                       *
        ****************************************/

static void LCD_WriteData0(char Data) {
  LCD_LOCK();
  WRITE_DATA0(Data);
  LCD_UNLOCK();
}

#if (LCD_NUM_CONTROLLERS >1)
static void LCD_WriteData1(char Data) {
  LCD_LOCK();
  WRITE_DATA1(Data);
  LCD_UNLOCK();
}
#endif

#if (LCD_NUM_CONTROLLERS >2)
static void LCD_WriteData2(char Data) {
  LCD_LOCK();
  LCD_WRITEDATA2(Data);
  LCD_UNLOCK();
}
#endif

#if (LCD_NUM_CONTROLLERS >3)
static void LCD_WriteData3(char Data) {
  LCD_LOCK();
  LCD_WRITEDATA3(Data);
  LCD_UNLOCK();
}
#endif

        /****************************************
        *                                       *
        *        Write single command           *
        *                                       *
        ****************************************/

static void LCD_WriteSingleCommand0(char cmd) {
  LCD_LOCK();
  WRITE_CMD0(cmd);
  LCD_UNLOCK();
}

#if (LCD_NUM_CONTROLLERS >1)
static void LCD_WriteSingleCommand1(char cmd) {
  LCD_LOCK();
  WRITE_CMD1(cmd);
  LCD_UNLOCK();
}
#endif
#if (LCD_NUM_CONTROLLERS >2)
static void LCD_WriteSingleCommand2(char cmd) {
  LCD_LOCK();
  LCD_WRITECMD2(cmd);
  LCD_UNLOCK();
}
#endif
#if (LCD_NUM_CONTROLLERS >3)
static void LCD_WriteSingleCommand3(char cmd) {
  LCD_LOCK();
  LCD_WRITECMD3(cmd);
  LCD_UNLOCK();
}
#endif

        /****************************************
        *                                       *
        *        Write double command           *
        *                                       *
        ****************************************/

static void LCD_WriteDoubleCommand0(char P1, char P2) {
  LCD_LOCK();
  WRITE_CMD0(P1);
  WRITE_CMD0(P2);
  LCD_UNLOCK();
}
#if (LCD_NUM_CONTROLLERS >1)
static void LCD_WriteDoubleCommand1(char P1, char P2) {
  LCD_LOCK();
  WRITE_CMD1(P1);
  WRITE_CMD1(P2);
  LCD_UNLOCK();
}
#endif
#if (LCD_NUM_CONTROLLERS >2)
static void LCD_WriteDoubleCommand2(char P1, char P2) {
  LCD_LOCK();
  LCD_WRITECMD2(P1);
  LCD_WRITECMD2(P2);
  LCD_UNLOCK();
}
#endif
#if (LCD_NUM_CONTROLLERS >3)
static void LCD_WriteDoubleCommand3(char P1, char P2) {
  LCD_LOCK();
  LCD_WRITECMD3(P1);
  LCD_WRITECMD3(P2);
  LCD_UNLOCK();
}
#endif

        /****************************************
        *                                       *
        *          Read data                    *
        *                                       *
        ****************************************/

#if LCD_READABLE
static U8 LCD_ReadData0(void) {
  U8 r;
  LCD_LOCK();
  READ_DATA0(r);
  LCD_UNLOCK();
  return r;
}
#if (LCD_NUM_CONTROLLERS >1)
static U8 LCD_ReadData1(void) {
  U8 r;
  LCD_LOCK();
  READ_DATA1(r);
  LCD_UNLOCK();
  return r;
}
#endif
#if (LCD_NUM_CONTROLLERS >2)
static U8 LCD_ReadData2(void) {
  U8 r;
  LCD_LOCK();
  READ_DATA2(r);
  LCD_UNLOCK();
  return r;
}
#endif
#if (LCD_NUM_CONTROLLERS >3)
static U8 LCD_ReadData3(void) {
  U8 r;
  LCD_LOCK();
  READ_DATA3(r);
  LCD_UNLOCK();
  return r;
}
#endif
#endif

        /****************************************
        *                                       *
        *          Read command (status)        *
        *                                       *
        ****************************************/

#if LCD_READABLE
static U8 LCD_ReadCmd0(void) {
  U8 r;
  LCD_LOCK();
  READ_CMD0(r);
  LCD_UNLOCK();
  return r;
}
#if (LCD_NUM_CONTROLLERS >1)
static U8 LCD_ReadCmd1(void) {
  U8 r;
  LCD_LOCK();
  READ_CMD1(r);
  LCD_UNLOCK();
  return r;
}
#endif
#if (LCD_NUM_CONTROLLERS >2)
static U8 LCD_ReadCmd2(void) {
  U8 r;
  LCD_LOCK();
  READ_CMD2(r);
  LCD_UNLOCK();
  return r;
}
#endif
#if (LCD_NUM_CONTROLLERS >3)
static U8 LCD_ReadCmd3(void) {
  U8 r;
  LCD_LOCK();
  READ_CMD3(r);
  LCD_UNLOCK();
  return r;
}
#endif
#endif

/*
        ****************************************
        *                                      *
        *     Write to  all controllers        *
        *                                      *
        ****************************************

Some commands should be written to all controllers at the same time.
(Commands used in the init-sequence, or display on/off).
With a multi-controller LCD it can come in handy to have a routine to
write to all of them at once.
*/

#if (LCD_NUM_CONTROLLERS ==1)
  #define LCD_WriteSingleCommandAll LCD_WriteSingleCommand0
#else
  void LCD_WriteSingleCommandAll(char cmd) {
    LCD_WriteSingleCommand0(cmd);
    LCD_WriteSingleCommand1(cmd);
    #if (LCD_NUM_CONTROLLERS >2)
      LCD_WriteSingleCommand2(cmd);
    #endif
    #if (LCD_NUM_CONTROLLERS >3)
      LCD_WriteSingleCommand3(cmd);
    #endif
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
#if (LCD_NUM_CONTROLLERS > 1)
  static U8 CurController;    /* Currently selected controller. All
                                 hardware operations are executed on
                                 this particular controller. It is
                                 more efficient to have a global
                                 variable than to pass this value as
                                 parameter many times. And in a low 
                                 level driver as this one, the
                                 priority of efficiency is top of
                                 the list.  */
#endif
static U8* pCacheByte;
static U8 aPage[LCD_NUM_CONTROLLERS];   /* Current page of
                                           LCD controller(s) */
static U8 aCAdr[LCD_NUM_CONTROLLERS];   /* Current column adr
                                           of LCD controller(s) */
static U8 Page, Col;            /* Page / column of cache byte */
static U8 DataW_Dirty;          /* Set (1) bits are dirty */
static U8 DataW_Cache;          /* Data to be written
                                  (not all bits may be valid !) */
static U8 DataR_Valid;
static U8 DataR_Cache;

/* The coordinates of the cache byte. We save current X,Y as well
   as Y0/Y1 (min/max) in Y-direction. Note that on this level we
   always talk about physical coordinates ! */
static int DataCacheX=-1;   /* x-adr. of currently cached byte.
                               If it is <0 it is sure invalid ! */
static int DataCacheY;
static int DataCacheY0;
static int DataCacheY1;

#if LCD_SUPPORT_COMTRANS
  static int DataCacheYBit0;
#else
  #define DataCacheYBit0 DataCacheY0
#endif

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

static void SetPage0(void) {
  SET_PAGE0(Page);
  aPage[0] = Page;
}

#if (LCD_NUM_CONTROLLERS > 1)
static void SetPage1(void) {
  SET_PAGE1(Page);
  aPage[1] = Page;
}
#endif

#if (LCD_NUM_CONTROLLERS > 2)
static void SetPage2(void) {
  SET_PAGE2(Page);
  aPage[2] = Page;
}
#endif

#if (LCD_NUM_CONTROLLERS > 3)
static void SetPage3(void) {
  SET_PAGE3(Page);
  aPage[3] = Page;
}
#endif

/*
        *****************************************
        *                                       *
        *         Set column routines           *
        *                                       *
        *****************************************
*/

static void SetCAdr0(void) {
  #if LCD_SEGOFF0
    U8 ColP = Col+LCD_SEGOFF0;
  #else
    #define ColP Col
  #endif
  SET_CADR0(ColP);
  aCAdr[0] = Col;
  #if !LCD_SEGOFF0
    #undef ColP
  #endif
}

#if (LCD_NUM_CONTROLLERS > 1)
static void SetCAdr1(void) {
  #if LCD_SEGOFF1
    U8 ColP = Col+LCD_SEGOFF1;
  #else
    #define ColP Col
  #endif
  SET_CADR1(ColP);
  aCAdr[1] = Col;
  #if !LCD_SEGOFF1
    #undef ColP
  #endif
}
#endif

#if (LCD_NUM_CONTROLLERS > 2)
static void SetCAdr2(void) {
  #if LCD_SEGOFF2
    U8 ColP = Col+LCD_SEGOFF2;
  #else
    #define ColP Col
  #endif
  SET_CADR2(ColP);
  aCAdr[2] = Col;
  #if !LCD_SEGOFF2
    #undef ColP
  #endif
}
#endif

#if (LCD_NUM_CONTROLLERS > 3)
static void SetCAdr3(void) {
  #if LCD_SEGOFF3
    U8 ColP = Col+LCD_SEGOFF3;
  #else
    #define ColP Col
  #endif
  SET_CADR3(ColP);
  aCAdr[3] = Col;
  #if !LCD_SEGOFF3
    #undef ColP
  #endif
}
#endif

/*
        *****************************************
        *                                       *
        *        Read video memory routines     *
        *                                       *
        *****************************************
*/

#if !LCD_CACHE
  static U8 ReadVMem0() {
    if (Page !=aPage[0])
      SetPage0();
    if (Col != aCAdr[0])
      SetCAdr0();
    aCAdr[0]+=2;
    LCD_ReadData0(Data);        /* Dummy read */
    return LCD_ReadData0(Data);
  }
#else
  #define ReadVMem0() (*pCacheByte)
#endif
#if (LCD_NUM_CONTROLLERS > 1)
  #if !LCD_CACHE
    U8 ReadVMem1() {
      if (Page !=aPage[1])
        SetPage1();
      if (Col != aCAdr[1])
        SetCAdr1();
      aCAdr[1]+=2;
      LCD_ReadData1(Data);      /* Dummy read */
      return LCD_ReadData1(Data);
    }
  #else
    #define ReadVMem1() (*pCacheByte)
  #endif
#endif /* LCD_NUM_CONTROLLERS >1 */
#if (LCD_NUM_CONTROLLERS > 2)
  #if !LCD_CACHE
    U8 ReadVMem2() {
      if (Page !=aPage[2])
        SetPage2();
      if (Col != aCAdr[2])
        SetCAdr2();
      aCAdr[2]+=2;
      LCD_ReadData2(Data);      /* Dummy read */
      return LCD_ReadData2(Data);
    }
  #else
    #define ReadVMem2() (*pCacheByte)
  #endif
#endif
#if (LCD_NUM_CONTROLLERS > 3)
  #if !LCD_CACHE
    U8 ReadVMem3() {
      if (Page !=aPage[3])
        SetPage3();
      if (Col != aCAdr[3])
        SetCAdr3();
      aCAdr[3]+=2;
      LCD_ReadData3(Data);      /* Dummy read */
      return LCD_ReadData3(Data);
    }
  #else
    #define ReadVMem3() (*pCacheByte)
  #endif
#endif

/*
        *****************************************
        *                                       *
        *       Write video memory routines     *
        *                                       *
        *****************************************
*/

#if  LCD_SUPPORT_CACHECONTROL
  #define CHECK_CACHE_LOCK(Con)                          \
  if (CacheLocked) {                                     \
    U8 ColOff = Col -LCD_FIRSTSEG##Con;                  \
    U8 Bit = ColOff&7;                                   \
    aaCacheDirtyTag##Con[Page][ColOff>>3] |= (1<<Bit);   \
    CacheStat = 1;         /* Mark cache as dirty */     \
    return;                                              \
  }
#else
  #define CHECK_CACHE_LOCK(LCDCON)
#endif
#define WRITE_VMEM(Con)             \
  CHECK_CACHE_LOCK(Con);            \
  if (Page !=aPage[Con])            \
    SetPage##Con();                 \
  if (Col != aCAdr[Con])            \
    SetCAdr##Con();                 \
  LCD_LOCK();                       \
  WRITE_DATA##Con(DataW_Cache);          \
  LCD_UNLOCK();                     \
  aCAdr[Con]++;

#if !LCD_CACHE_WRITETHRU
  #define RETURN_IF_WRITE_NOT_NEEDED(Con) \
    if ( *pCacheByte == DataW_Cache) \
      return;
#else
  #define RETURN_IF_WRITE_NOT_NEEDED(Con)
#endif

#if LCD_CACHE
  #define CHECK_VMEM_CACHE(Con) \
    RETURN_IF_WRITE_NOT_NEEDED(Con);                                \
    *pCacheByte = DataW_Cache;
#else
  #define CHECK_VMEM_CACHE(Con)
#endif

static void WriteVMem0(void) {
  CHECK_VMEM_CACHE(0);
  WRITE_VMEM(0);
}

#if (LCD_NUM_CONTROLLERS > 1)
static void WriteVMem1(void) {
  CHECK_VMEM_CACHE(1);
  WRITE_VMEM(1);
}
#endif

#if (LCD_NUM_CONTROLLERS > 2)
static void WriteVMem2(void) {
  CHECK_VMEM_CACHE(2);
  WRITE_VMEM(2);
}
#endif

#if (LCD_NUM_CONTROLLERS > 3)
static void WriteVMem3(void) {
  CHECK_VMEM_CACHE(3);
  WRITE_VMEM(3);
}
#endif

/*
  ********************************************************************
  *                                                                  *
  *                Write Cache control                               *
  *                                                                  *
  ********************************************************************

In order to speed up access to the LCD and to avoid flickering, it
can be necessary to lock the write cache. This means that all drawing
commands do not affect the hardware it the cache is locked until
the flush (or unlock) command is given.

Note: The code could be shortened a bit by defining an add. macro
      for the code for every controller. This has not been done
      because it would make debugging even harder.
      (It is already hard enough)
*/

#define CHECK_CACHE_BYTE_DIRTY(Controller,Bit)   \
  if (Dirty&(1<<Bit)) {                          \
    if (page !=aPage[Controller]) {              \
      Page = page;                               \
      SetPage##Controller();                     \
    }                                            \
    if (col+Bit != aCAdr[Controller]) {        \
      Col = col+Bit;                             \
      SetCAdr##Controller();                     \
    }                                            \
    LCD_WriteData##Controller(Cache##Controller[page][col+Bit]); \
    aCAdr[Controller]++;                         \
  }
    
#define FLUSH_CACHE_X(Con)                                      \
  for (page=0; page<NUM_PAGES##Con; page++) {					\
    for (col8=0; col8<(NUM_COLS##Con+7)/8; col8++) {			\
      U8 Dirty;													\
      if ((Dirty=aaCacheDirtyTag##Con[page][col8]) !=0) {		\
        int col   = col8<<3;									\
        aaCacheDirtyTag##Con[page][col8] =0;					\
        CHECK_CACHE_BYTE_DIRTY(Con,0);							\
        CHECK_CACHE_BYTE_DIRTY(Con,1);							\
        CHECK_CACHE_BYTE_DIRTY(Con,2);							\
        CHECK_CACHE_BYTE_DIRTY(Con,3);							\
        CHECK_CACHE_BYTE_DIRTY(Con,4);							\
        CHECK_CACHE_BYTE_DIRTY(Con,5);							\
        CHECK_CACHE_BYTE_DIRTY(Con,6);							\
        CHECK_CACHE_BYTE_DIRTY(Con,7);                          \
      }                                                         \
    }															\
  }

#if  LCD_SUPPORT_CACHECONTROL
static void FlushCache(void) {
  int page;
  int col8;     /* Column index, 1 inc skips 8 bytes */
  FLUSH_CACHE_X(0);
  #if (LCD_NUM_CONTROLLERS >1)
    FLUSH_CACHE_X(1);
  #endif
  #if (LCD_NUM_CONTROLLERS >2)
    FLUSH_CACHE_X(2);
  #endif
  #if (LCD_NUM_CONTROLLERS >3)
    FLUSH_CACHE_X(3);
  #endif
/* Important !!!
  We have to make sure that the byte-level cache is not level
  inconsistent because we have modified the Page/Col values. This
  is done by invalidating the x-position. */
  DataCacheX=-1;
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
      FlushCache();
    }
  }
  return CacheStat;
}
#endif

/*
  ********************************************************************
  *                                                                  *
  *                                                                  *
  *         Internal video memory management                         *
  *                                                                  *
  *                                                                  *
  ********************************************************************

This contains the internal video management of this driver, which is
the core of it. It has been designed with the following goals:

+ Support for all types of orientaions of display
+ Support for multiple controllers
+ Support for both parallel and serial interface
+ Small RAM footprint
+ Fast execution on all CPUs in all configurations
+ Small code

It has taken a considerable amount of time to develop, optimize and
test the concept of this driver. It should pretty much cover most LCDs
using 15XX controllers; if you feel your configuration is not covered
by this driver, please get
in contact with us, preferably via email (support@segger.com).

*/

#define FLUSH() if (DataW_Dirty) Flush()

/* For XOR operations, the byte needs to be loaded in order to
   perform the operation. We also have to make sure that bits which
   have been previously modified are not forgotten.
   This essentially means loading only the unmodified bits (for which
   the bit in DATAW_Dirty is ==0) and leave the other ones unchanged.
*/

#define LOADDATA()                               \
  if (!DataR_Valid) {                            \
    ReadData();                                  \
    DataW_Cache &= DataW_Dirty;                  \
    DataW_Cache |= DataR_Cache&(~DataW_Dirty);   \
  }

#if LCD_CACHE
  #define ReadData() DataR_Cache = *pCacheByte; DataR_Valid= 0xff;
#else
static void ReadData(void) {
  DataR_Valid= 0xff;                    /* All bits are valid. */
  #if (LCD_NUM_CONTROLLERS == 1)
    DataR_Cache= ReadVMem0();
  #else
    switch (CurController) {
    case 0:
      DataR_Cache= ReadVMem0(); break;
    case 1:
      DataR_Cache= ReadVMem1(); break;
    #if (LCD_NUM_CONTROLLERS >2)
    case 2:
      DataR_Cache= ReadVMem2(); break;
    #endif
    #if (LCD_NUM_CONTROLLERS >3)
    case 3:
      DataR_Cache= ReadVMem3(); break;
    #endif
    }
  #endif    /* LCD_NUM_CONTROLLERS == 1 */
}
#endif

#if (LCD_NUM_CONTROLLERS > 1)
typedef void (tWriteVMem)(void);
tWriteVMem* aWriteVMemX[] = {
  WriteVMem0,WriteVMem1
#if (LCD_NUM_CONTROLLERS >2)
  ,WriteVMem2
#endif
#if (LCD_NUM_CONTROLLERS >3)
  ,WriteVMem3
#endif
}; 
#endif 

static void Flush(void) {
  /* Nothing to write ? Then we are done !*/
  if (DataW_Dirty==0)
    return;
  /* All bits are dirty ? Then write`em all, dont read !!*/
  if (DataW_Dirty!=0xff) {
    /* Only some are dirty ... We have to read the byte ! */
    if (!DataR_Valid) {
      ReadData();         /* Get current byte in our cache */
    }
    DataW_Cache &= DataW_Dirty;
    DataW_Cache |= DataR_Cache & (~DataW_Dirty);
  }
  DataR_Cache = DataW_Cache;
#if (LCD_NUM_CONTROLLERS == 1)
  WriteVMem0();
#else
  aWriteVMemX[CurController]();
#endif
  DataW_Dirty = 0;              /* No more bits to write */
}

/*
        *****************************************
        *                                       *
        *         Find Byte                     *
        *                                       *
        *****************************************

Due to the setup options reg. the area of the display which is covered
by one LCD-controller and the fact that different display controllers
can controll arbitrary areas of the display as defined in the
config-file, It can be a tricky job to find out which display
controller is concerned, where in the video memory of that particular
controller the byte is located and how many bits are left (i.e. what
the minimal and maximal physical y-position is).
Note that this job is a lot easier in a single controller system,
where the entire routine could be placed in a macro.
*/
#if (LCD_SUPPORT_SEGTRANS==0)
  #define CALCCOL(Con) Col  = DataCacheX-LCD_XORG##Con
#else
  #define CALCCOL(Con) Col  = LCD__aRow2Seg##Con[DataCacheX-LCD_XORG##Con]
#endif

#if (LCD_SUPPORT_COMTRANS==0)
  #define CALCY(Con) \
    DataCacheY0 = DataCacheY &(~7);    \
    DataCacheY1 = DataCacheY0+  7;     \
    Page = (DataCacheY0-LCD_YORG##Con)>>3
#else
    #define CALCY(Con) \
    DataCacheY1 = DataCacheY0 = DataCacheY; \
    {                                       \
      int Com = LCD__aLine2Com##Con[DataCacheY-LCD_YORG##Con]; \
      Page = Com>>3;                                   \
      DataCacheYBit0 = DataCacheY-(Com&7);             \
    }
#endif

#define IF_INLEFT(Con)   if (DataCacheX >= LCD_XORG##Con)
#define IF_INRIGHT(Con)  if (DataCacheX <= LCD_XORG##Con+LCD_NUM_SEGS##Con-1)
#define IF_INTOP(Con)    if (DataCacheY >= LCD_YORG##Con)
#define IF_INBOTTOM(Con) if (DataCacheY <= LCD_YORG##Con+LCD_NUM_COMS##Con-1)

#define IF_INAREA(Con)                                    \
   IF_INRIGHT(Con)                                        \
   IF_INLEFT(Con)                                         \
   IF_INTOP(Con)                                          \
   IF_INBOTTOM(Con)


#define CALCXY(Con) \
  CALCCOL(Con);      \
  CALCY(Con);      \
  pCacheByte = &Cache##Con[Page][Col];  \
  CurController = Con;

/* This is an optimization for a single controller system */
  #if (LCD_NUM_CONTROLLERS == 1)
	#define FindByte() \
	CALCCOL(0); CALCY(0); pCacheByte = &Cache0[Page][Col];
/*	CALCCOL(0); CALCY(0); pCacheByte = &Cache0[Page][Col-LCD_FIRSTSEG0];*/
  #endif

/* This is an optimization for a 2 controller system */
#if (LCD_NUM_CONTROLLERS == 2)
  #if (LCD_XORG0==LCD_XORG1)
    #undef IF_INAREA
    #if (LCD_YORG0 == LCD_YORG)
      #define IF_INAREA(Con) IF_INBOTTOM(Con)
    #else
      #define IF_INAREA(Con) IF_INTOP(Con)
    #endif
	#define FindByte() IF_INAREA(0) { CALCXY(0); } else { CALCXY(1); }
  #endif
#endif

/* The actual routine ... */
#ifndef FindByte
static void FindByte(void) {
  #if (LCD_NUM_CONTROLLERS > 1)
  /* Check if controller 0 is concerned */
    IF_INAREA(0)
    {
      CALCXY(0);
      return;
    }
  /* Check if controller 1 is concerned, but only
     in a system with more than 2 controllers */
  #if (LCD_NUM_CONTROLLERS > 2)
    IF_INAREA(1)
  #endif
    {
      CALCXY(1);
      return;
    }
  /* Check if controller 2 is concerned */
    #if (LCD_NUM_CONTROLLERS > 3)
      #if (LCD_NUM_CONTROLLERS > 3)
      IF_INAREA(2)
      #endif
    {
      CALCXY(2);
      return;
    }
    #endif
  /* Check if controller 3 is concerned */
    #if (LCD_NUM_CONTROLLERS >3)
      #if (LCD_NUM_CONTROLLERS >4)
      IF_INAREA(3)
      #endif
    {
      CALCXY(3);
      return;
    }
    #endif
    /* This should never happen ! */
  #endif
}
#endif

/*
        *****************************************
        *                                       *
        *         Set new Position              *
        *                                       *
        *****************************************
*/

static void Goto(void) {
  U8* pCacheByteTemp[2];
  U8  PageTemp[2];
  U8  ColTemp[2];
  #if (LCD_NUM_CONTROLLERS > 1)
    U8  CurControllerTemp[2];
  #endif
  DataR_Valid=0;       /* No info about what's in the data byte */
  if (DataW_Dirty == 0) {
    FindByte();
    return;
  }
  /* Save the current values because FindByte will overwrite them */
  pCacheByteTemp[0]        = pCacheByte;
  PageTemp[0]              = Page;
  ColTemp[0]               = Col;
  #if (LCD_NUM_CONTROLLERS > 1)
    CurControllerTemp[0]     = CurController;
  #endif
  FindByte();
  if (pCacheByteTemp[0] != pCacheByte) {
    /* Save the new values */
    pCacheByteTemp[1]        = pCacheByte;
    PageTemp[1]              = Page;
    ColTemp[1]               = Col;
    #if (LCD_NUM_CONTROLLERS > 1)
      CurControllerTemp[1] = CurController;
    #endif
    /* Restore the old values for writing */
    pCacheByte        = pCacheByteTemp[0];
    Page              = PageTemp[0];
    Col               = ColTemp[0];
    #if (LCD_NUM_CONTROLLERS > 1)
      CurController = CurControllerTemp[0];
    #endif
    Flush();
    /* Restore the new (current) values */
    pCacheByte        = pCacheByteTemp[1];
    Page              = PageTemp[1];
    Col               = ColTemp[1];
    DataR_Valid=0;       /* We have no more info about what's in the data byte */
    #if (LCD_NUM_CONTROLLERS > 1)
      CurController = CurControllerTemp[1];
    #endif
  }
}

/*
        *****************************************
        *                                       *
        *         Set X and Y- Position         *
        *                                       *
        *****************************************

   Check if we already have the right byte in the buffer.
   This works only if COM-Lines are straight, otherwise it is just
   a waste of CPU-time.
*/

#if (LCD_SUPPORT_COMTRANS)
  #define GotoXY(x,y)                     \
    DataCacheY = y;                                                      \
    DataCacheX = x;                         \
    Goto()
#else
static void GotoXY(int x, int y) {
  DataCacheY = y;                                                          
  if ((x == DataCacheX) &&                  
      (y >= DataCacheY0) &&     (y <= DataCacheY1))
  {
    return;                                 
  }                                         
  DataCacheX = x;                         
  Goto();
}
#endif

/*
        *****************************************
        *                                       *
        *         Set Y- Position               *
        *                                       *
        *****************************************
*/

#if (!LCD_SUPPORT_COMTRANS)     /* Only used if COMs are straight ! */
static void GotoY(int y) {
/* Check if we already have the right byte in the buffer.
   This works only if COM-Lines are straight, otherwise it is just
   a waste of CPU-time.
 */
  DataCacheY = y;    
  if ((y >= DataCacheY0) && (y <= DataCacheY1))
    return;
  Goto();
}
#endif


#if (LCD_SUPPORT_COMTRANS)
#define GotoYPlus1()           \
  DataCacheY++;                \
        Goto()
#else
static void GotoYPlus1(void) {
  DataCacheY++;
  if ((DataCacheY >= DataCacheY0) && (DataCacheY <= DataCacheY1))
    return;
        Goto();
}
#endif

/*
  ********************************************************************
  *                                                                  *
  *                Drawing routines, internal                        *
  *                                                                  *
  ********************************************************************
*/

static const U8 Bit2Mask[] = { 1,2,4,8,16,32,64,128 };

/*
        *****************************************
        *                                       *
        *           Xor pixel                   *
        *                                       *
        *****************************************
*/

/*
static void XORPIXEL() {
  U8 HWMask;
  LOADDATA();
  HWMask = Bit2Mask[DataCacheY-DataCacheYBit0];
  DataW_Dirty |= HWMask;
  DataW_Cache ^= HWMask;
}
*/
#define XORPIXEL() {                             \
  U8 HWMask;\
  LOADDATA(); /* For XOR operations, the byte needs to be loaded */ \
  HWMask = Bit2Mask[DataCacheY-DataCacheYBit0];\
  DataW_Dirty |= HWMask;\
  DataW_Cache ^= HWMask;\
}

static void XorPixel(void) {
  XORPIXEL();
}

/*
        *****************************************
        *                                       *
        *     Set pixel, internal drawing       *
        *                                       *
        *****************************************
*/
/*
static void SETPIXEL() {
  U8 HWMask;
  HWMask = Bit2Mask[DataCacheY-DataCacheYBit0];
  DataW_Dirty |= HWMask;
  DataW_Cache |= HWMask;
}
*/
#define SETPIXEL() {                             \
  U8 HWMask;										 \
  HWMask = Bit2Mask[DataCacheY-DataCacheYBit0];	 \
  DataW_Dirty |= HWMask;							 \
  DataW_Cache |= HWMask;							 \
}

static void SetPixel(void) {
  SETPIXEL();
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
  GotoXY(x,y);
  LOADDATA();
  XORPIXEL();
}

/*
        *****************************************
        *                                       *
        *       Clear pixel                     *
        *                                       *
        *****************************************
*/

/*
static void CLRPIXEL() {
  U8 HWMask;
  HWMask = Bit2Mask[DataCacheY-DataCacheYBit0];
  DataW_Dirty |=  HWMask;
  DataW_Cache &= ~HWMask;
}
*/
#define CLRPIXEL() {                             \
  U8 HWMask;    								 \
  HWMask = Bit2Mask[DataCacheY-DataCacheYBit0]; \
  DataW_Dirty |=  HWMask;	  					 \
  DataW_Cache &= ~HWMask;	  					 \
}

static void ClrPixel(void) {
  CLRPIXEL();
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
  GotoXY(x,y);
  LOADDATA();
  if (ColorIndex) {
    SETPIXEL();
  } else {
    CLRPIXEL();
  }
  FLUSH();
}

unsigned int LCD_L0_GetPixelIndex(int x, int y) {
  unsigned int Result;
  GotoXY(x,y);
  LOADDATA();
  Result = DataR_Cache & (1<<(DataCacheY&7));
  if (Result)
    return 1;
  else
    return 0;
}

/*
        *****************************************
        *                                       *
        *       Assign pixel                    *
        *                                       *
        *****************************************
*/

#define ASSIGN_PIXEL(c)          { if(c) { SetPixel(); } else ClrPixel();}
/*
static void ASSIGN_PIXEL_FAST(U8 c)
{
  if(c) {
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
      XORPIXEL();
    } else {
      SETPIXEL();
    }
  } else {
    CLRPIXEL();
  }
}
*/
#define ASSIGN_PIXEL_FAST(c) \
{ \
  if(c) { \
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) { \
      XORPIXEL(); \
    } else { \
      SETPIXEL(); \
    } \
  } else { \
    CLRPIXEL(); \
  } \
}

#define ASSIGN_PIXEL_REV(c)      { if(c) { ClrPixel(); } else SetPixel();}
#define ASSIGN_PIXEL_REV_FAST(c) { if(c) { CLRPIXEL(); } else SETPIXEL();}

/*
  ********************************************************************
  *                                                                  *
  *           Line drawing routines, internal                        *
  *                                                                  *
  ********************************************************************

There are 2 line drawing routines for horizontal and vertical
line drawing. Due to the organization of the controllers video ram,
one of them (the vertical line draw routine) is a lot faster,
since it cam write up to 8 pixels at a time. This routine is therefor
used internally for filling of rectangles.
*/

#if (!LCD_SUPPORT_COMTRANS)
  static const U8 aMaskStart[8] = { 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80 };
  static const U8 aMaskEnd  [8] = { 0xff, 0x7f, 0x3f, 0x1f, 0xf,  0x7,  0x3,  0x1 };
#endif

static void DrawVLinePhys  (int x, int y0,  int y1) {
#if (!LCD_SUPPORT_COMTRANS)
  int yByte = y0 &(~7);
  U8  Mask = aMaskStart[y0-yByte];
  if (yByte+7 > y1) {   /* do we have to cut off the end ? */
    Mask &= aMaskEnd[yByte+7-y1];
  }
  CHECK_SCHEDULE(y1-y0+1);
  GotoXY(x,y0);
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_XOR) ==0) {
    if(COLOR) {   /* Set Line */
      /* Draw first byte */
      DataW_Dirty |= Mask;
      DataW_Cache |= Mask;
      /* Draw middle bytes */
      yByte+=8;
      for (; yByte+7 <= y1; yByte+=8) {
        GotoY(yByte);
        DataW_Dirty = 0xff;
        DataW_Cache = 0xff;
      }
      /* Draw last (incomplete) byte */
      if (yByte <= y1) {
        GotoY(yByte);
        Mask = aMaskEnd[yByte-y1+7];
        DataW_Dirty |= Mask;
        DataW_Cache |= Mask;   
      }
    } else {      /* Clear Line */
      /* Draw first byte */
      DataW_Dirty |=  Mask;
      DataW_Cache &= ~Mask;
      /* Draw middle bytes */
      yByte+=8;
      for (; yByte+7 <= y1; yByte+=8) {
        GotoY(yByte);
        DataW_Dirty = 0xff;
        DataW_Cache = 0;
      }
      /* Draw last (incomplete) byte */
      if (yByte <= y1) {
        GotoY(yByte);
        Mask = aMaskEnd[yByte-y1+7];
        DataW_Dirty |=  Mask;
        DataW_Cache &= ~Mask;   
      }
    }
  } else { /* Xor Line */
    LOADDATA();
    /* Draw first byte */
    DataW_Dirty |= Mask;
    DataW_Cache ^= Mask;
    /* Draw middle bytes */
    yByte+=8;
    for (; yByte+7 <= y1; yByte+=8) {
      GotoY(yByte);
      LOADDATA();           /* for xor, data needs to be in cache */
      DataW_Dirty  = 0xff;
      DataW_Cache ^= 0xff;
    }
    /* Draw last (incomplete) byte */
    if (yByte <= y1) {
      GotoY(yByte);
      LOADDATA();           /* for xor, data needs to be in cache */
      Mask = aMaskEnd[yByte-y1+7];
      DataW_Dirty |= Mask;
      DataW_Cache ^= Mask;   
    }
  }
#else
  int NumPixels = y1-y0+1;
  if (NumPixels<=0)
    return;
  CHECK_SCHEDULE(NumPixels);
  GotoXY(x,y0);
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_XOR) ==0) {
    if(COLOR) {   /* Set Line */
      for (; --NumPixels; ) {
        SETPIXEL();
        GotoYPlus1();
      }
      SetPixel();
    } else {      /* Clear Line */
      for (; --NumPixels; ) {
        CLRPIXEL();
        GotoYPlus1();
      }
      ClrPixel();
    }
  } else { /* Xor Line */
      for (; --NumPixels; ) {
      XorPixel();
      GotoYPlus1();
    }
    XorPixel();
  }
#endif
}

/*
        *****************************************
        *                                       *
        *       Draw horizontal line            *
        *                                       *
        *****************************************

Due to the organisation of the RAM of the LCD-controller, this is the
slow routine. It is not used by the driver unless there is no
other choice; for this reason it is not very important to try to
squeeze the last CPU-bus cycle out of it.
*/

static void DrawHLinePhys  (int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for ( ;x0 <= x1; x0++) {
      GotoXY(x0,y);
      XorPixel();
    }
  } else {
    if(COLOR) {
      for ( ;x0 <= x1; x0++) {
        GotoXY(x0,y);
        SetPixel();
      }
    } else {
      for ( ;x0 <= x1; x0++) {
        GotoXY(x0,y);
        ClrPixel();
      }
    }
  }
}

/*
  ********************************************************************
  *                                                                  *
  *                Drawing routines, public                          *
  *                                                                  *
  ********************************************************************
*/

/*
        *****************************************
        *                                       *
        *       LCD_DrawPixel                   *
        *                                       *
        *****************************************

Purpose:  This routine is called by the upper layers of emWin.
          It writes 1 pixel into the display.

*/

void LCD_L0_DrawPixel(int x, int y) {
  #if !LCD_SWAP_XY
    #define xP x
    #define yP y
  #else
    #define xP y
    #define yP x
  #endif
  GotoXY(xP,yP);
  ASSIGN_PIXEL_FAST(COLOR);
  FLUSH();
}

/*
        ****************************************
        *                                      *
        *     LCD_DrawHLine                    *
        *                                      *
        ****************************************
*/

void LCD_L0_DrawHLine  (int x0, int y,  int x1) {
  #if !LCD_SWAP_XY
    DrawHLinePhys(x0, y, x1);
  #else
    DrawVLinePhys(y,x0, x1);
  #endif
  FLUSH();
}

/*
        ****************************************
        *                                      *
        *     LCD_DrawVLine                    *
        *                                      *
        ****************************************
*/
void LCD_L0_DrawVLine  (int x, int y0,  int y1) {
  #if !LCD_SWAP_XY
    DrawVLinePhys(x,y0,y1);
  #else
    DrawHLinePhys(y0,x,y1);
  #endif
  FLUSH();
}

/*
        *****************************************
        *                                       *
        *          LCD_DrawRect                 *
        *                                       *
        *****************************************

*/

void LCD_L0_FillRect(int x0, int y0, int x1, int y1) {
/* Now map logical to physical coordinates.
  Phys. and log. coordinates are identical unless x and y are swapped,
  in which case we simply assign x to y and vice versa.
*/
  #if !LCD_SWAP_XY
     #define x0P x0
     #define y0P y0
     #define x1P x1
     #define y1P y1
  #else
     #define x0P y0
     #define y0P x0
     #define x1P y1
     #define y1P x1
  #endif
  for (; x0P <= x1P; x0P++) {
    DrawVLinePhys (x0P, y0P, y1P);
  }
  FLUSH();
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
    *      Draw Bitmap 1 BPP optimized          *
    *                                           *
    *********************************************

There are 2 versions of this routine, depending on if the display
is turned (X<-->Y swapped) or not.
*/

#if !LCD_SWAP_XY
static void  DrawBitLine1BPP_NoSwap(
             int x, int y
             ,U8 const*pData
             ,int size
             ,const LCD_PIXELINDEX*pTrans
              ,int BytesPerLine
              ,U8 Mask)
{
/*
// Check if there is something left to draw
*/
  GotoXY(x,y);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR | LCD_DRAWMODE_REV)) {
  case LCD_DRAWMODE_NORMAL:
  case LCD_DRAWMODE_REV:
    for (; size>0; size--, pData+=BytesPerLine) {
      if(*pData & Mask) {
        if (*(pTrans+1)) { SETPIXEL(); }
        else             { CLRPIXEL(); }
      } else {
        if (*(pTrans  )) { SETPIXEL(); }
        else             { CLRPIXEL(); }
      }
      GotoYPlus1();
    }
    break;
  case LCD_DRAWMODE_XOR:
    for (; size>=1; size--, pData+=BytesPerLine) {
      if (*pData & Mask) { XORPIXEL(); }
      GotoYPlus1();
    }
    break;
  case LCD_DRAWMODE_TRANS:
    if (*(pTrans+1)) {  /* foreground positiv */
      for (; size>0; size--, pData+=BytesPerLine) {
        if(*pData & Mask) { SETPIXEL(); }
        GotoYPlus1();
      }
    } else {
      for (; size>0; size--, pData+=BytesPerLine) {
        if(*pData & Mask) { CLRPIXEL(); }
        GotoYPlus1();
      }
    }
    break;
  }
}
#else
static void  DrawBitLine1BPP_Swap(
             int x, int y
             ,U8 const*pData
             ,int size
             ,const U8*pTrans
             ,int BitNo)
{
  U8 Mask = 0x80>>(BitNo&7);
  pData += (BitNo>>3);
/*
// Check if there is something left to draw
*/
  if (size <=0)
    return;
  GotoXY(x,y);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    if (*(pTrans+1)) {  /* foreground positiv */
      for (; size>1; size--) {
        ASSIGN_PIXEL_FAST(*pData & Mask);
        GotoYPlus1();
        if ((Mask >>=1)==0) {
          Mask =0x80;
          pData++;
        }
      }
      ASSIGN_PIXEL(*pData & Mask);
    } else {
      for (; size>1; size--) {
        ASSIGN_PIXEL_REV_FAST(*pData & Mask);
        GotoYPlus1();
        if ((Mask >>=1)==0) {
           Mask =0x80;
          pData++;
        }
      }
      ASSIGN_PIXEL_REV(*pData & Mask);
    }
    break;
  case LCD_DRAWMODE_TRANS:
    if (*(pTrans+1)) {  /* foreground positiv */
      for (; size>1; size--) {
        if(*pData & Mask) { SETPIXEL(); }
        GotoYPlus1();
        if ((Mask >>=1)==0) {
          Mask =0x80;
          pData++;
        }
      }
      ASSIGN_PIXEL(*pData & Mask);
    } else {
      for (; size>1; size--) {
        if(*pData & Mask) { CLRPIXEL(); }
        GotoYPlus1();
        if ((Mask >>=1)==0) {
           Mask =0x80;
          pData++;
        }
      }
      ASSIGN_PIXEL_REV(*pData & Mask);
    }
    break;
  case LCD_DRAWMODE_XOR:
    /* todo bugfix */
    for (; size>1; size--,y++) {
      if (*pData & Mask)
        XorPixel();
      GotoYPlus1();
      if ((Mask >>=1)==0) {
        Mask =0x80;
        pData++;
      }
    }
    if (*pData & Mask)
      XorPixel();
    break;
  }
}
#endif

/*
    *********************************************
    *                                           *
    *      Draw Bitmap 2 BPP                    *
    *                                           *
    *********************************************
*/

#if (LCD_MAX_LOG_COLORS > 2)

static void  DrawBitLine2BPP(int x, int y, U8 const*p, int Diff, int xsize, const LCD_PIXELINDEX*pTrans) {
  LCD_PIXELINDEX pixel;
/*
        Jump to right entry point
*/
  pixel = *p;
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
  LCD_L0_SetPixelIndex(x+0, y, *(pTrans+(pixel>>6)));
  if (!--xsize)
    return;
WriteBit1:
  LCD_L0_SetPixelIndex(x+1, y, *(pTrans+(3&(pixel>>4))));
  if (!--xsize)
    return;
WriteBit2:
  LCD_L0_SetPixelIndex(x+2, y, *(pTrans+(3&(pixel>>2))));
  if (!--xsize)
    return;
WriteBit3:
  LCD_L0_SetPixelIndex(x+3, y, *(pTrans+(3&(pixel))));
  if (!--xsize)
    return;
  pixel = *(++p);
  x+=4;
  goto WriteBit0;
/*
        Write with transparency
*/
WriteTBit0:
  if (pixel&(3<<6))
    LCD_L0_SetPixelIndex(x+0, y, *(pTrans+(pixel>>6)));
  if (!--xsize)
    return;
WriteTBit1:
  if (pixel&(3<<4))
    LCD_L0_SetPixelIndex(x+1, y, *(pTrans+(3&(pixel>>4))));
  if (!--xsize)
    return;
WriteTBit2:
  if (pixel&(3<<2))
    LCD_L0_SetPixelIndex(x+2, y, *(pTrans+(3&(pixel>>2))));
  if (!--xsize)
    return;
WriteTBit3:
  if (pixel&(3<<0))
    LCD_L0_SetPixelIndex(x+3, y, *(pTrans+(3&(pixel))));
  if (!--xsize)
    return;
  pixel = *(++p);
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
  LCD_PIXELINDEX pixel;
/*
        Jump to right entry point
*/
  pixel = *p;
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
  LCD_L0_SetPixelIndex(x+0, y, *(pTrans+(pixel>>4)));
  if (!--xsize)
    return;
WriteBit1:
  LCD_L0_SetPixelIndex(x+1, y, *(pTrans+(pixel&0xf)));
  if (!--xsize)
    return;
  x+=2;
  pixel = *(++p);
  goto WriteBit0;
/*
        Write with transparency
*/
WriteTBit0:
  if (pixel>>4)
    LCD_L0_SetPixelIndex(x+0, y, *(pTrans+(pixel>>4)));
  if (!--xsize)
    return;
WriteTBit1:
  if (pixel&0xf)
    LCD_L0_SetPixelIndex(x+1, y, *(pTrans+(pixel&0xf)));
  if (!--xsize)
    return;
  x+=2;
  pixel = *(++p);
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
    while (xsize > 0) {
      pixel = *p;
      LCD_L0_SetPixelIndex(x+0, y, *(pTrans+pixel));
      xsize--;
      x++;
      p++;
    }
  } else {   /* Handle transparent bitmap */
    while (xsize > 0) {
      pixel = *p;
      if (pixel)
        LCD_L0_SetPixelIndex(x+0, y, *(pTrans+pixel));
      xsize--;
      x++;
      p++;
    }
  }
}

#endif

/*
    ******************************************************************
    *                                                                *
    *             Universal draw Bitmap routine                      *
    *                                                                *
    ******************************************************************
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
  /*
     Use DrawBitLineXBPP
  */
  #if !LCD_SWAP_XY
    switch (BitsPerPixel) {
    case 1:
      xsize+=Diff&7;
      for (i=Diff; i<xsize; i++) {
        DrawBitLine1BPP_NoSwap(x0+i, y0,
                               pData+(i>>3),
                               ysize,
                               pTrans,
                               BytesPerLine,
                               0x80>>(i&7));
      }
      break;
      #if (LCD_MAX_LOG_COLORS > 2)
        case 2:
          for (i=0; i<ysize; i++) {
            DrawBitLine2BPP(x0, i+y0, pData, Diff, xsize, pTrans);
            pData += BytesPerLine;
          }
          break;
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
  #else
    switch (BitsPerPixel) {
    case 1:
      for (i=0; i<ysize; i++) {
        DrawBitLine1BPP_NoSwap(x0+i, y0,
                               pData+(i>>3),
                               ysize,
                               pTrans,
                               BytesPerLine,
                               0x80>>(i&7));
        pData += BytesPerLine;
      }
      break;
    }
  #endif
  FLUSH();
}

/*
        *********************************************************
        *                                                       *
        *       LCD_L0_SetOrg                                   *
        *                                                       *
        *********************************************************

Purpose: 
  Sets the original position of the virtual display.
  Has no function at this point with this driver,
  because the 15XX uses built-in memory as video memory.
  This memory is just big enough to store the info needed
  for the max. display resolution supported.
*/

#if LCD_SUPPORT_SETORG

int OrgX, OrgY;
void LCD_L0_SetOrg(int x, int y) {
  OrgX = x;
  OrgY = y;
}
#endif

/*
        *********************************************************
        *                                                       *
        *       Support for dynamic inversion of LCD            *
        *                                                       *
        *********************************************************

*/

#if LCD_SUPPORT_RT_INVERSION
void LCD_SetInverse   (void) {
  LCD_WriteSingleCommandAll(LCD_CMDREVERSE);  
}

/* This function is always available, it can not be eliminated
   by means of a configuration switch ! */
void LCD_ClrInverse   (void) {
  LCD_WriteSingleCommandAll(LCD_CMDNORMAL);  
}
#endif

/*
  ********************************************************************
  *                                                                  *
  *                       Refresh the Display                        *
  *                                                                  *
  ********************************************************************
*/

/*
        *************************************************
        *                                               *
        *           Refresh display partially           *
        *                                               *
        *************************************************
*/

#if LCD_SUPPORT_REFRESH

static U8 RefreshPage;

static void LCD_RefreshSection(void) {
  U8 OldPage = Page;
  U8 OldCol  = Col;
  U8* pData;
  Page = RefreshPage++;
  SetPage0();
  Col=0;
  SetCAdr0();
  pData = &Cache0[Page][Col];
  for (; Col<=LCD_NUM_SEGS0; Col++) {
    LCD_WriteData0(*pData++);
  }
  Page = OldPage;
  Col  = OldCol;
  if (RefreshPage >= NUM_PAGES0) {
    RefreshPage=0;
  }
}

/*
        *************************************************
        *                                               *
        *           Refresh entire display              *
        *                                               *
        *************************************************
*/

void LCD_L0_Refresh(void) {
  int i;
  for (i=0; i<NUM_PAGES0; i++) {
    LCD_RefreshSection();
  }
}
#endif

/*
        *********************************************************
        *                                                       *
        *           Support for verification                    *
        *                                                       *
        *********************************************************
*/

#if LCD_SUPPORT_VERIFY
static int ErrCnt;
static int ErrStat;

int  LCD_GetErrStat(void) {
  return ErrStat;
}

void LCD_ClrErrStat(void) {
  ErrStat = ErrCnt=0;
}

int  LCD_GetErrCnt (void) {
  return ErrCnt;
}
#endif  

/*
        *********************************************************
        *                                                       *
        *       LCD_On                                          *
        *       LCD_Off                                         *
        *                                                       *
        *********************************************************
*/

#if LCD_SUPPORT_CHECKINIT
  static char IsOn;           /* Only needed for init check ! */
#endif

void LCD_On           (void) {
  LCD_WriteSingleCommandAll(CMD_LCD_ON);  
  #if LCD_SUPPORT_CHECKINIT
    IsOn =1;
  #endif
}

void LCD_Off          (void) {
  LCD_WriteSingleCommandAll(CMD_LCD_OFF);  
  #if LCD_SUPPORT_CHECKINIT
    IsOn =0;
  #endif
}

/*
        *********************************************************
        *                                                       *
        *       Support for different pages                     *
        *                                                       *
        *********************************************************
*/

#if LCD_SUPPORT_PAGING
static U8 VisPage;
static U8 SelPage;
static int    XAdd;

int LCD_SelPage  (int Page) {
  int r = SelPage;
  SelPage = Page;
  XAdd = Page * LCD_XSIZE;
  return r;
}

int LCD_ShowPage (int Page) {
  int r = SelPage;
  SelPage = Page;
/* Update hardware */
  return r;
}

/* returns selected page */
int LCD_GetSelPage (void) {
  return SelPage;
}
/* returns visible page */
int LCD_GetVisPage (void) {
  return VisPage;
}

#endif


/*
*********************************************************
*
*       LCD_L0_ReInit : Re-Init the display
*
*********************************************************

ReInit contains all of the code that can be re-executed at any point without
changing or even disturbing what can be seen on the LCD.
Note that it is also used as a subroutine by LCD_Init().

*/

#if LCD_MIRROR_X
  #define LCD_CMDSETADC 0xa1     /* ADC select: reverse  segment
                                    driver output (mirroring X) */
#else
  #define LCD_CMDSETADC 0xa0     /* ADC select: normal segment driver output */
#endif

#if LCD_MIRROR_Y
  #if LCD_CONTROLLER == 1560
    #error MIRROR_Y not supported for 1560 ! (Use LCD_INIT_CONTROLLER instead)
  #endif
  #define LCD_CMDCOMMODE  0xc8   /* Common mode : reverse output (mirroring Y) */
#else
  #define LCD_CMDCOMMODE  0xc0   /* Common mode : normal */
#endif

void  LCD_L0_ReInit(void) {
  int i;
  for (i=0; i<LCD_NUM_CONTROLLERS; i++) {
    aPage[i] = aCAdr[i] = 255;
  }
  INIT_CONTROLLER();                     /* macro defined in config */
  #if (LCD_CONTROLLER/100 == 15)
    LCD_WriteSingleCommandAll(LCD_CMDSETADC);      /* ADC select   */
    #if LCD_CONTROLLER != 1560                     /* This command is not available for the 1560 ! */
      LCD_WriteSingleCommandAll(LCD_CMDCOMMODE);   /* Set common mode */
    #endif
    LCD_WriteSingleCommandAll(LCD_FIRSTCOM0+0x40); /* Set start adress */
    LCD_WriteSingleCommandAll(0xA4);               /* Data Display Mode (not all on)  */
    LCD_WriteSingleCommandAll(LCD_CMDNORMAL);      /* Normal (Not reversed) mode  */
  #endif
}

static void LCD__ClearVRam(void) {
  for (Page=0; Page <=8; Page++) {
    SetPage0();
    #if (LCD_NUM_CONTROLLERS >1)
      SetPage1();
    #endif
    #if (LCD_NUM_CONTROLLERS >2)
      SetPage2();
    #endif
    #if (LCD_NUM_CONTROLLERS >3)
      SetPage3();
    #endif
    Col=0;
    SetCAdr0();
    #if (LCD_NUM_CONTROLLERS >1)
      SetCAdr1();
    #endif
    #if (LCD_NUM_CONTROLLERS >2)
      SetCAdr2();
    #endif
    #if (LCD_NUM_CONTROLLERS >3)
      SetCAdr3();
    #endif
    for (; Col<=LCD_SEGS_MAX; Col++) {
      LCD_WriteData0(0);
      #if (LCD_NUM_CONTROLLERS >1)
        LCD_WriteData1(0);
      #endif
      #if (LCD_NUM_CONTROLLERS >2)
        LCD_WriteData2(0);
      #endif
      #if (LCD_NUM_CONTROLLERS >3)
        LCD_WriteData3(0);
      #endif
    }
    memset (&aCAdr, LCD_SEGS_MAX-1, sizeof(aCAdr));    /* Invalidate register caches */
  }
}

/********************************************************
*
*       LCD_L0_SetOrg
*
*********************************************************
*/
void LCD_L0_SetOrg(int x, int y) {
  LCD_USE_PARA(x);
  LCD_USE_PARA(y);
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
/* Initialize static variables */
/* Clear Cache (If a cache has been configured) */
  #if LCD_CACHE
    ZEROINIT(Cache0);
    #if (LCD_NUM_CONTROLLERS >1)
      ZEROINIT(Cache1);
    #endif
    #if (LCD_NUM_CONTROLLERS >2)
      ZEROINIT(Cache2);
    #endif
    #if (LCD_NUM_CONTROLLERS >3)
      ZEROINIT(Cache3);
    #endif
  #endif
  #if  LCD_SUPPORT_CACHECONTROL
    CacheStat   =0;     /* 0: No changes */
    CacheLocked =0;     /* 0: Not locked */
    ZEROINIT(aaCacheDirtyTag0);
    #if (LCD_NUM_CONTROLLERS >1)
      ZEROINIT(aaCacheDirtyTag1);
    #endif
    #if (LCD_NUM_CONTROLLERS >2)
      ZEROINIT(aaCacheDirtyTag2);
    #endif
    #if (LCD_NUM_CONTROLLERS >3)
      ZEROINIT(aaCacheDirtyTag3);
    #endif
  #endif
  memset (&aPage, 255, sizeof(aPage));    /* Invalidate register caches */
  memset (&aCAdr, 255, sizeof(aCAdr));    /* Invalidate register caches */
  DataCacheX=-1;         /* Invalidate byte level cache */
  #if LCD_SUPPORT_VERIFY
    ErrCnt =0;
    ErrStat=0;
  #endif
  LCD_Off();
  LCD_L0_ReInit();
#if 0 /* For LCD-Test */
  LCD__ClearVRam();
  for (Page=0; Page <=8; Page++) {
    int Bit;
    SetPage0();
        for (Bit=0; Bit<=7; Bit++) {
      int Data = ((2<<Bit)-1);
          for (Col=0, SetCAdr0(); Col<=LCD_SEGS_MAX; Col++) {
        LCD_WriteData0(Data);
          }
        }
  }
  for (Page=0; Page <=8; Page++) {
    int Bit;
    SetPage1();
        for (Bit=0; Bit<=7; Bit++) {
      int Data = ((2<<Bit)-1);
          for (Col=0, SetCAdr1(); Col<=LCD_SEGS_MAX; Col++) {
        LCD_WriteData1(Data);
          }
        }
  }
#endif
  LCD__ClearVRam();
  LCD_On();
  return 0;
}

/*
        *********************************************************
        *                                                       *
        *                   LCD_L0_SetLUTEntry                     *
        *                                                       *
        *********************************************************

  This function is required, but has no functionality
  with 15XX controllers
*/

void LCD_L0_SetLUTEntry(U8 Pos, LCD_COLOR color) {
  LCD_USE_PARA(Pos);
  LCD_USE_PARA(color);
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

Return value:   0 => No error, init is O.K.
*/

/* Create the mask to compare statuss with.
   The mask depends on the configuration.
   For details, refer to the manual page 8-49.
*/

#if LCD_SUPPORT_CHECKINIT
int LCD_L0_CheckInit(void) {
  #if !LCD_READABLE
    return 0;           /* If LCD is not readable, there is
                           no way to check the configuration ! */
  #else
    /* Unfortunately, we can not read back the controller .
       The only thing that we can do is a status check.  */
    U8 Stat = LCD_ReadCmd0();
    /* Status of all controllers should be identical */
    #if (LCD_NUM_CONTROLLERS >1)
      if (Stat != LCD_ReadCmd1())
        return 1;
    #endif
    #if (LCD_NUM_CONTROLLERS >2)
      if (Stat != LCD_ReadCmd2())
        return 1;
    #endif
    #if (LCD_NUM_CONTROLLERS >3)
      if (Stat != LCD_ReadCmd3())
        return 1;
    #endif
    if (IsOn)
      Stat ^= (1<<5);   /* xor the on/off bit,
                          result should be 0 if O.K. */
    #if !LCD_MIRROR_X
      Stat ^= (1<<6);   /* xor the adc bit,
                          result should be 0 if O.K. */
    #endif
    return Stat;        /* will be 0 if all bits are O.K. */
  #endif
}
#endif


#else

void LCD15XX(void) { } /* avoid empty object files */

#endif /* (LCD_CONTROLLER/100 == 15) */

/* **************** END OF FILE ********************* */



