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
File        : TEXT_SetFont.c
Purpose     : Implementation of TEXT_SetFont
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "TEXT_Private.h"
#include "GUI_Protected.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       TEXT_SetFont
*/
void TEXT_SetFont(TEXT_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont) {
  if (hObj) {
    TEXT_Obj* pObj;
    WM_LOCK();
    pObj = TEXT_H2P(hObj);
    if (pObj->Props.pFont != pFont) {
      pObj->Props.pFont = pFont;
      WM_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}


#else  /* avoid empty object files */

void TEXT_SetFont_c(void);
void TEXT_SetFont_c(void){}

#endif  /* #if GUI_WINSUPPORT */

	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
