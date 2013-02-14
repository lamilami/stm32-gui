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
File        : GUITouchConf.h
Purpose     : Configures touch screen module
----------------------------------------------------------------------
*/


#ifndef __GUITOUCH_CONF_H
#define __GUITOUCH_CONF_H

#define GUI_TOUCH_SWAP_XY       0
#define GUI_TOUCH_MIRROR_X      0
#define GUI_TOUCH_MIRROR_Y      0


#define X_MIN  320
#define X_MAX  3750
#define Y_MIN  320
#define Y_MAX  3600


#define GUI_TOUCH_AD_LEFT        X_MAX
#define GUI_TOUCH_AD_RIGHT       X_MIN
#define GUI_TOUCH_AD_TOP       	 Y_MIN 
#define GUI_TOUCH_AD_BOTTOM      Y_MAX





#endif /* GUITOUCH_CONF_H */
