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
File        : GUI_CursorCrossM.C
Purpose     : Defines the cross cursor, medium
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "GUI_Protected.h"

GUI_CONST_STORAGE GUI_BITMAP GUI_BitmapCrossM = {
 21,                   /* XSize */
 21,                   /* YSize */
 6,                    /* BytesPerLine */
 2,                    /* BitsPerPixel */
 GUI_Pixels_CrossM,    /* Pointer to picture data (indices) */
 &GUI_CursorPal       /* Pointer to palette */
};


GUI_CONST_STORAGE GUI_CURSOR GUI_CursorCrossM = {
  &GUI_BitmapCrossM, 10, 10
};


/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
