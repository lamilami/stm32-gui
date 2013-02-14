/*
*********************************************************************************************************
*                                             uC/GUI V3.98
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
File        : WM_SetCaptureMove.c
Purpose     : Implementation of WM_SetCaptureMove
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*        Static data
*
**********************************************************************
*/
static GUI_POINT WM__CapturePoint;

/*********************************************************************
*
*        Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetCaptureMove
*/
void WM_SetCaptureMove(WM_HWIN hWin, const GUI_PID_STATE* pState, int MinVisibility, int LimitTop) {
  if (!WM_HasCaptured(hWin)) {
    WM_SetCapture(hWin, 1);        /* Set capture with auto release */
    WM__CapturePoint.x = pState->x;
    WM__CapturePoint.y = pState->y;
  } else {                         /* Moving ... let the window move ! */
    int dx, dy;
    dx = pState->x - WM__CapturePoint.x;
    dy = pState->y - WM__CapturePoint.y;
    /* Make sure at least a part of the windows stays inside of its parent */
    if ((MinVisibility == 0) && (LimitTop == 0)) {
      WM_MoveWindow(hWin, dx, dy);
    } else {
      GUI_RECT Rect, RectParent;
      WM_GetWindowRectEx(hWin, &Rect);
      /* Check if the top region of the window should be limited */
      if (LimitTop) {
        Rect.y1 = Rect.y0 + LimitTop - 1;
      }
      WM_GetWindowRectEx(WM_GetParent(hWin), &RectParent);
      GUI_MoveRect(&Rect, dx, dy);
      GUI__ReduceRect(&RectParent, &RectParent, MinVisibility);
      if (GUI_RectsIntersect(&Rect, &RectParent)) {
        WM_MoveWindow(hWin, dx, dy);
      }
    }
  }
}


#else
  void WM_SetCaptureMove_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
