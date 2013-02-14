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
File        : LCDConf_MEMC_C6_C320x240.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*       General configuration of LCD
*
**********************************************************************
*/

#define LCD_CONTROLLER    0              /* 0 means no LCD controller */
#define LCD_XSIZE         320            /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE         240            /* Y-resolution of LCD, Logical coor. */
#define LCD_INTERFACEBITS 8              /* select 4 or 8 bit interface */
#define LCD_BITSPERPIXEL  6              /* Permitted values here: 3 or 6 */
#define LCD_FIXEDPALETTE  222
#define LCD_SWAP_RB       1              /* Swap red/blue */
  
#define LCD_TIMERINIT0  1300
#define LCD_TIMERINIT1  1600

#endif /* LCDCONF_H */

