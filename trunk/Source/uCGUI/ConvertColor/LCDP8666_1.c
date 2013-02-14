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
File        : LCDP8666_1.C
Purpose     : Color conversion routines for 86661 mode
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Public code,
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_8666_1
*/
unsigned LCD_Color2Index_8666_1(LCD_COLOR Color) {
  int r, g, b, Index;
  r = Color & 255;
  g = (Color >> 8) & 255;
  b = Color >> 16;
/* Check if image is a gray scale ... */
	if ((r == g) && (g == b)) {
    return 120 + (r + 8) / 17;  /* Convert into colors from 120 - 135 */
	}
/* Convert into the 6*6*6 colors ... */
  r = (r * 5 + 127) / 255;
  g = (g * 5 + 127) / 255;
  b = (b * 5 + 127) / 255;
  Index = r + 6 * g + 36 * b;
  return (Index < 108) ? Index + 12 : Index + 28;
}

/*********************************************************************
*
*       LCD_Index2Color_8666_1
*/
LCD_COLOR LCD_Index2Color_8666_1(int Index) {
  unsigned int r,g;
  U32 b;
  /* 16 Gray scale range ? */
  if ((Index >= 120) && (Index < 136)) {
    return (U32)0x111111 * (U32)(Index - 120);
	}
  if ((Index < 12) || (Index > 243)) {
    return 0;  /* Black for illegal indices */
  }
  if (Index >= 120) {
    Index -= 28;
  } else {
    Index -= 12;
  }
  r = (Index % 6) * (255 / 5);
  g = ((Index / 6) % 6) * (255 / 5);
  b = (Index / 36) * (255 / 5);
  return r + (g << 8) + ((U32)b << 16);
}

/*********************************************************************
*
*       LCD_GetIndexMask_8666_1
*/
unsigned LCD_GetIndexMask_8666_1(void) {
  return 0xff;
}

/*************************** End of file ****************************/
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
