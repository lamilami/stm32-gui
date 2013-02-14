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
File        : LCDConf_1335_M1_M240x128.h
Purpose     : Sample configuration file
----------------------------------------------------------------------
*/

#ifndef LCDCONF_H
#define LCDCONF_H

/*********************************************************************
*
*                   General configuration of LCD
*
**********************************************************************
*/

#define LCD_XSIZE          (240)       /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE          (128)       /* Y-resolution of LCD, Logical coor. */
#define LCD_CONTROLLER     (6901)
#define LCD_BITSPERPIXEL   (1)
#define LCD_EXTENDED_WAIT  (1)
#define LCD_FIXEDPALETTE   (1)

/*********************************************************************
*
*                   Simple bus configuration
*
**********************************************************************
*/

void LCD_X_Write00(char c);
void LCD_X_Write01(char c);
char LCD_X_Read00(void);
#define LCD_WRITE_A1(Byte) LCD_X_Write01(Byte)
#define LCD_WRITE_A0(Byte) LCD_X_Write00(Byte)
#define LCD_READ_A0()      LCD_X_Read00()

#endif /* LCDCONF_H */
