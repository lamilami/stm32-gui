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
File        : LISTVIEW_SetTextAlign.c
Purpose     : Implementation of LISTVIEW_SetTextAlign
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTVIEW_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTVIEW_SetTextAlign
*/
void LISTVIEW_SetTextAlign(LISTVIEW_Handle hObj, unsigned int Index, int Align) {
  if (hObj) {
    LISTVIEW_Obj * pObj;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    if (Index < LISTVIEW__GetNumColumns(pObj)) {
      LISTVIEW_COLUMN* pColumn;
      pColumn = (LISTVIEW_COLUMN*) GUI_ARRAY_GetpItem(&pObj->ColumnArray, Index);
      if (Align != pColumn->Align) {
        pColumn->Align = Align;
        LISTVIEW__InvalidateInsideArea(hObj, pObj);
      }
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_SetTextAlign_C(void);
  void LISTVIEW_SetTextAlign_C(void) {}
#endif

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
