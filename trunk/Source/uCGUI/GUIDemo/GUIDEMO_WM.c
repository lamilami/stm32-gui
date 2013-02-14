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
File        : WM_Sample.c
Purpose     : Demonstrates the window manager
----------------------------------------------------------------------
*/

#include <string.h>
#include "GUI.h"
#include "GUIDEMO.h"
#include "WM.h"
#include "MULTIEDIT.h"


/*******************************************************************
*
*       defines
*
********************************************************************
*/

#define MSG_CHANGE_TEXT WM_USER+0

#define SPEED 1250

/*******************************************************************
*
*       static variables
*
********************************************************************
*/

static char _acInfoText[40];

static GUI_COLOR _WindowColor1  = GUI_GREEN;
static GUI_COLOR _WindowColor2  = GUI_RED;
static GUI_COLOR _ChildColor    = GUI_YELLOW;

static WM_CALLBACK* _cbBkWindowOld;

static WM_HWIN _hWindow1;
static WM_HWIN _hWindow2;
static WM_HWIN _hChild;

static MULTIEDIT_HANDLE _hMEdit;

/*******************************************************************
*
*       static code, helper functions
*
********************************************************************
*/

/*******************************************************************
*
*       _ChangeInfoText

  Sends a message to the background window and invalidate it, so
  the callback of the background window display the new text.
*/
static void _ChangeInfoText(char* pStr) {
  WM_MESSAGE Message;
  Message.MsgId  = MSG_CHANGE_TEXT;
  Message.Data.p = pStr;
  WM_SendMessage(WM_HBKWIN, &Message);
  WM_InvalidateWindow(WM_HBKWIN);
}

/*******************************************************************
*
*       _DrawInfoText

  Drawes the info text directly on the display. This function is for
  the moments when no callback is set.
*/
static void _DrawInfoText(char* pStr) {
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("WindowManager - Sample", 160, 5);
  GUI_SetFont(&GUI_Font8x16);
  GUI_DispStringAtCEOL(pStr, 5, 40);
}

/*******************************************************************
*
*       _LiftUp
*/
static void _LiftUp(int dy) {
  int i, tm;
  for (i = 0; i < (dy/4); i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1, 0, -4);
    WM_MoveWindow(_hWindow2, 0, -4);
    while ((GUI_GetTime() - tm) < 20) {
      WM_Exec();
    }
  }
}

/*******************************************************************
*
*       _LiftDown
*/
static void _LiftDown(int dy) {
  int i, tm;
  for (i = 0; i < (dy/4); i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1, 0, 4);
    WM_MoveWindow(_hWindow2, 0, 4);
    while ((GUI_GetTime() - tm) < 20) {
      WM_Exec();
    }
  }
}

/*******************************************************************
*
*       static code, callbacks for windows
*
********************************************************************
*/

/*******************************************************************
*
*       _cbBkWindow
*/
static void _cbBkWindow(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case MSG_CHANGE_TEXT:
    strcpy(_acInfoText, pMsg->Data.p);
  case WM_PAINT:
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt("WindowManager - Sample", 160, 5);
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispStringAt(_acInfoText, 5, 40);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbWindow1
*/
static void _cbWindow1(WM_MESSAGE* pMsg) {
  int x, y;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(_WindowColor1);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    x = WM_GetWindowSizeX(pMsg->hWin);
    y = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DispStringHCenterAt("Window 1", x / 2, (y / 2) - 12);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbWindow2
*/
static void _cbWindow2(WM_MESSAGE* pMsg) {
  int x, y;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(_WindowColor2);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    x = WM_GetWindowSizeX(pMsg->hWin);
    y = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DispStringHCenterAt("Window 2", x / 2, (y / 4) - 12);
    break;
  case WM_SIZE:
    WM_InvalidateWindow(_hChild);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbChild
*/
static void _cbChild(WM_MESSAGE* pMsg) {
  int x, y;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(_ChildColor);
    GUI_Clear();
    GUI_SetColor(GUI_RED);
    GUI_SetFont(&GUI_Font24_ASCII);
    x = WM_GetWindowSizeX(pMsg->hWin);
    y = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DispStringHCenterAt("Child window", x / 2, (y / 2) - 12);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbDemoCallback1
*/
static void _cbDemoCallback1(WM_MESSAGE* pMsg) {
  int x, y;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_GREEN);
    GUI_Clear();
    GUI_SetColor(GUI_RED);
    GUI_SetFont(&GUI_FontComic18B_1);
    x = WM_GetWindowSizeX(pMsg->hWin);
    y = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DispStringHCenterAt("Window 1\nanother Callback", x / 2, (y / 2) - 18);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbDemoCallback2
*/
static void _cbDemoCallback2(WM_MESSAGE* pMsg) {
  int x, y;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_MAGENTA);
    GUI_Clear();
    GUI_SetColor(GUI_YELLOW);
    GUI_SetFont(&GUI_FontComic18B_1);
    x = WM_GetWindowSizeX(pMsg->hWin);
    y = WM_GetWindowSizeY(pMsg->hWin);
    GUI_DispStringHCenterAt("Window 2\nanother Callback", x / 2, (y / 4) - 18);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       static code, functions for demo
*
********************************************************************
*/

/*******************************************************************
*
*       _DemoSetDesktopColor

  Demonstrates the use of WM_SetDesktopColor
*/
static void _DemoSetDesktopColor(void) {
  GUI_SetBkColor(GUI_BLUE);
  GUI_Clear();
  _DrawInfoText("WM_SetDesktopColor()");
//  GUIDEMO_Delay(SPEED*2);
  WM_SetDesktopColor(GUI_BLACK);
  GUIDEMO_Delay(SPEED/2);
  /* Set background color and invalidate desktop color.
     This is needed for the later redrawing demo. */
  GUI_SetBkColor(GUI_BLACK);
  WM_SetDesktopColor(GUI_INVALID_COLOR);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoCreateWindow

  Demonstrates the use of WM_CreateWindow
*/
static void _DemoCreateWindow(void) {
  /* Set callback for background window */
  _cbBkWindowOld = WM_SetCallback(WM_HBKWIN, _cbBkWindow);
  /* Create windows */
  _ChangeInfoText("WM_CreateWindow()");
//  GUIDEMO_Delay(SPEED);
  _hWindow1 = WM_CreateWindow( 50,  70, 165, 100, WM_CF_SHOW | WM_CF_MEMDEV, _cbWindow1, 0);
  GUIDEMO_Delay(SPEED/3);
  _hWindow2 = WM_CreateWindow(105, 125, 165, 100, WM_CF_SHOW | WM_CF_MEMDEV, _cbWindow2, 0);
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoCreateWindowAsChild

  Demonstrates the use of WM_CreateWindowAsChild
*/
static void _DemoCreateWindowAsChild(void) {
  /* Create windows */
  _ChangeInfoText("WM_CreateWindowAsChild()");
//  GUIDEMO_Delay(SPEED);
/*  _hMEdit = MULTIEDIT_Create(10, 50,
  							 145, 40, 
                             _hWindow2, 10, WM_CF_SHOW | WM_CF_MEMDEV,
                             MULTIEDIT_CF_AUTOSCROLLBAR_V, "This is a test of multi edit box\n",
                             200);
*/
  //  MULTIEDIT_SetAutoScrollV(_hMEdit, 1);
  _hChild = WM_CreateWindowAsChild(10, 50, 145, 40, _hWindow2, WM_CF_SHOW | WM_CF_MEMDEV, _cbChild, 0);
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoInvalidateWindow

  Demonstrates the use of WM_InvalidateWindow
*/
static void _DemoInvalidateWindow(void) {
  _ChangeInfoText("WM_InvalidateWindow()");
  _WindowColor1 = GUI_BLUE;
//  GUIDEMO_Delay(SPEED);
  WM_InvalidateWindow(_hWindow1);
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoBringToTop

  Demonstrates the use of WM_BringToTop
*/
static void _DemoBringToTop(void) {
  _ChangeInfoText("WM_BringToTop()");
//  GUIDEMO_Delay(SPEED);
  WM_BringToTop(_hWindow1);    
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoMoveTo

  Demonstrates the use of WM_MoveTo
*/
static void _DemoMoveTo(void) {
  int i, tm, tDiff;
  _ChangeInfoText("WM_MoveTo()");
//  GUIDEMO_Delay(SPEED);
  for (i = 1; i < 56; i++) {
    tm = GUI_GetTime();
    WM_MoveTo(_hWindow1,  50 + i,  70 + i);
    WM_MoveTo(_hWindow2, 105 - i, 125 - i);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 1; i < 56; i++) {
    tm = GUI_GetTime();
    WM_MoveTo(_hWindow1, 105 - i, 125 - i);
    WM_MoveTo(_hWindow2,  50 + i,  70 + i);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoBringToBottom

  Demonstrates the use of WM_BringToBottom
*/
static void _DemoBringToBottom(void) {
  _ChangeInfoText("WM_BringToBottom()");
//  GUIDEMO_Delay(SPEED);
  WM_BringToBottom(_hWindow1);
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoMoveWindow

  Demonstrates the use of WM_MoveWindow
*/
static void _DemoMoveWindow(void) {
  int i, tm, tDiff;
  _ChangeInfoText("WM_MoveWindow()");
//  GUIDEMO_Delay(SPEED);
  for (i = 0; i < 55; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1,  1,  1);
    WM_MoveWindow(_hWindow2, -1, -1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 55; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1, -1, -1);
    WM_MoveWindow(_hWindow2,  1,  1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoHideShowParent

  Demonstrates the use of WM_HideWindow and WM_ShowWindow
*/
static void _DemoHideShowParent(void) {
  _ChangeInfoText("WM_HideWindow(Parent)");
//  GUIDEMO_Delay(SPEED);
  WM_HideWindow(_hWindow2);
  GUIDEMO_Delay(SPEED/3);
  WM_HideWindow(_hWindow1);
  GUIDEMO_Delay(SPEED);
  _ChangeInfoText("WM_ShowWindow(Parent)");
  GUIDEMO_Delay(SPEED);
  WM_ShowWindow(_hWindow1);
  GUIDEMO_Delay(SPEED/3);
  WM_ShowWindow(_hWindow2);
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoHideShowChild

  Demonstrates the use of WM_HideWindow and WM_ShowWindow
*/
static void _DemoHideShowChild(void) {
  _ChangeInfoText("WM_HideWindow(Child)");
//  GUIDEMO_Delay(SPEED);
  WM_HideWindow(_hChild);
  GUIDEMO_Delay(SPEED);
  _ChangeInfoText("WM_ShowWindow(Child)");
  GUIDEMO_Delay(SPEED);
  WM_ShowWindow(_hChild);
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoClipping

  Demonstrates clipping at parent borders
*/
static void _DemoClipping(void) {
  int i, tm, tDiff;
  _ChangeInfoText("Demonstrating clipping of child");
//  GUIDEMO_Delay(SPEED);
  for (i = 0; i < 25; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hChild,  1,  0);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 25; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hChild,  0,  1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 50; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hChild, -1,  0);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 25; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hChild,  0, -1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 25; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hChild,  1,  0);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoRedrawing

  Demonstrates how useful can be a callback
*/
static void _DemoRedrawing(void) {
  int i, tm, tDiff;
  _ChangeInfoText("Demonstrating redrawing");
//  GUIDEMO_Delay(SPEED);
  _LiftUp(40);
  GUIDEMO_Delay(SPEED/3);
  _ChangeInfoText("Using a callback for redrawing");
  GUIDEMO_Delay(SPEED/3);
  for (i = 0; i < 55; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1,  1,  1);
    WM_MoveWindow(_hWindow2, -1, -1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 55; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1, -1, -1);
    WM_MoveWindow(_hWindow2,  1,  1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  GUIDEMO_Delay(SPEED/4);
  _LiftDown(30);
  GUIDEMO_Delay(SPEED/2);
  _ChangeInfoText("Without redrawing");
  GUIDEMO_Delay(SPEED);
  _LiftUp(30);
  GUIDEMO_Delay(SPEED/4);
  WM_SetCallback(WM_HBKWIN, _cbBkWindowOld);
  for (i = 0; i < 55; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1,  1,  1);
    WM_MoveWindow(_hWindow2, -1, -1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 55; i++) {
    tm = GUI_GetTime();
    WM_MoveWindow(_hWindow1, -1, -1);
    WM_MoveWindow(_hWindow2,  1,  1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  GUIDEMO_Delay(SPEED/3);
  WM_SetCallback(WM_HBKWIN, _cbBkWindow);
  _LiftDown(40);
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoResizeWindow

  Demonstrates the use of WM_ResizeWindow
*/
static void _DemoResizeWindow(void) {
  int i, tm,tDiff;
  _ChangeInfoText("WM_ResizeWindow()");
//  GUIDEMO_Delay(SPEED);
  _LiftUp(30);
  for (i = 0; i < 40; i++) {
    tm = GUI_GetTime();
    WM_ResizeWindow(_hWindow1,  1,  1);
    WM_ResizeWindow(_hWindow2, -1, -1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 80; i++) {
    tm = GUI_GetTime();
    WM_ResizeWindow(_hWindow1, -1, -1);
    WM_ResizeWindow(_hWindow2,  1,  1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  for (i = 0; i < 40; i++) {
    tm = GUI_GetTime();
    WM_ResizeWindow(_hWindow1,  1,  1);
    WM_ResizeWindow(_hWindow2, -1, -1);
    tDiff = 15 - (GUI_GetTime() - tm);
    GUI_Delay(tDiff);
  }
  _LiftDown(30);
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoSetCallback

  Demonstrates the use of WM_SetCallback
*/
static void _DemoSetCallback(void) {
  _ChangeInfoText("WM_SetCallback()");
//  GUIDEMO_Delay(SPEED);
  WM_SetCallback(_hWindow1, _cbDemoCallback1);
  WM_InvalidateWindow(_hWindow1);
  GUIDEMO_Delay(SPEED/2);
  WM_SetCallback(_hWindow2, _cbDemoCallback2);
  WM_InvalidateWindow(_hWindow2);
  GUIDEMO_Delay(SPEED*3);
  WM_SetCallback(_hWindow1, _cbWindow1);
  WM_InvalidateWindow(_hWindow1);
  GUIDEMO_Delay(SPEED/2);
  WM_SetCallback(_hWindow2, _cbWindow2);
  WM_InvalidateWindow(_hWindow2);
  GUIDEMO_Delay(SPEED);
  GUIDEMO_NotifyStartNext();
}

/*******************************************************************
*
*       _DemoDeleteWindow

  Demonstrates the use of WM_DeleteWindow
*/
static void _DemoDeleteWindow(void) {
  _ChangeInfoText("WM_DeleteWindow()");
//  GUIDEMO_Delay(SPEED);
  WM_DeleteWindow(_hWindow2);
  GUIDEMO_Delay(SPEED/3);
  WM_DeleteWindow(_hWindow1);
  GUIDEMO_Delay(SPEED);
  _ChangeInfoText("");
  GUIDEMO_Delay(SPEED);
  /* Restore background callback and window colors */
  WM_SetCallback(WM_HBKWIN, _cbBkWindowOld);
  _WindowColor1 = GUI_GREEN;
  _WindowColor2 = GUI_RED;
}

/*******************************************************************
*
*       MainTask
*
*       Demonstrates the use of the window manager
*
********************************************************************
*/

void GUIDEMO_WM(void) {
  /* Show message */
/*
  GUIDEMO_ShowIntro("Windows Manager",
                    "\nExamples for the"
                    "\nWindows manager");
*/
  GUIDEMO_NotifyStartNext();
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();

  WM_SetCreateFlags(WM_CF_MEMDEV);
  WM_EnableMemdev(WM_HBKWIN);

  GUIDEMO_HideInfoWin();
     _DemoSetDesktopColor();
 	 _DemoCreateWindow();
     _DemoCreateWindowAsChild();
     _DemoInvalidateWindow();
     _DemoBringToTop();
     _DemoMoveTo();
     _DemoBringToBottom();
     _DemoMoveWindow();
     _DemoHideShowParent();
     _DemoHideShowChild();
    //_DemoClipping();
     _DemoRedrawing();
     _DemoResizeWindow();
     _DemoSetCallback();
     _DemoDeleteWindow();

}
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
