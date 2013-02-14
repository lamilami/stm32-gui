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
File        : GRAPH.h
Purpose     : GRAPH include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef GRAPH_H
#define GRAPH_H

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define GRAPH_CI_BK     0
#define GRAPH_CI_BORDER 1
#define GRAPH_CI_FRAME  2
#define GRAPH_CI_GRID   3

#define GRAPH_SCALE_CF_HORIZONTAL (0 << 0)
#define GRAPH_SCALE_CF_VERTICAL   (1 << 0)

#define GRAPH_SCALE_SF_HORIZONTAL GRAPH_SCALE_CF_HORIZONTAL
#define GRAPH_SCALE_SF_VERTICAL   GRAPH_SCALE_CF_VERTICAL

#define GRAPH_DRAW_FIRST 0
#define GRAPH_DRAW_LAST  1

#define GRAPH_ALIGN_RIGHT (0 << 0)
#define GRAPH_ALIGN_LEFT  (1 << 0)

#define GRAPH_CF_GRID_FIXED_X  (1 << 0)

/*********************************************************************
*
*       Public Types
*
**********************************************************************
*/
typedef WM_HMEM GRAPH_Handle;
typedef WM_HMEM GRAPH_DATA_Handle;
typedef WM_HMEM GRAPH_SCALE_Handle;

/*********************************************************************
*
*       Create functions
*
**********************************************************************
*/

GRAPH_Handle GRAPH_CreateEx      (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id);
GRAPH_Handle GRAPH_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);

GRAPH_DATA_Handle  GRAPH_DATA_XY_Create(GUI_COLOR Color, unsigned MaxNumItems, GUI_POINT * pData, unsigned NumItems);
GRAPH_DATA_Handle  GRAPH_DATA_YT_Create(GUI_COLOR Color, unsigned MaxNumItems, I16 * pData, unsigned NumItems);
GRAPH_SCALE_Handle GRAPH_SCALE_Create  (int Pos, int TextAlign, unsigned Flags, unsigned TickDist);

/*********************************************************************
*
*       The callback ...
*
* Do not call it directly ! It is only to be used from within an
* overwritten callback.
*/
void GRAPH_Callback(WM_MESSAGE * pMsg);

/*********************************************************************
*
*       Standard member functions
*
**********************************************************************
*/

/*********************************************************************
*
*       Member functions
*
**********************************************************************
*/
void      GRAPH_AttachData   (GRAPH_Handle hObj, GRAPH_DATA_Handle hData);
void      GRAPH_AttachScale  (GRAPH_Handle hObj, GRAPH_SCALE_Handle hScale);
void      GRAPH_SetBorder    (GRAPH_Handle hObj, unsigned BorderL, unsigned BorderT, unsigned BorderR, unsigned BorderB);
GUI_COLOR GRAPH_SetColor     (GRAPH_Handle hObj, GUI_COLOR Color, unsigned Index);
unsigned  GRAPH_SetGridFixedX(GRAPH_Handle hObj, unsigned OnOff);
unsigned  GRAPH_SetGridOffY  (GRAPH_Handle hObj, unsigned Value);
unsigned  GRAPH_SetGridVis   (GRAPH_Handle hObj, unsigned OnOff);
unsigned  GRAPH_SetGridDistX (GRAPH_Handle hObj, unsigned Value);
unsigned  GRAPH_SetGridDistY (GRAPH_Handle hObj, unsigned Value);
U8        GRAPH_SetLineStyleH(GRAPH_Handle hObj, U8 Value);
U8        GRAPH_SetLineStyleV(GRAPH_Handle hObj, U8 Value);
void      GRAPH_SetLineStyle (GRAPH_Handle hObj, U8 Value);
unsigned  GRAPH_SetVSizeX    (GRAPH_Handle hObj, unsigned Value);
unsigned  GRAPH_SetVSizeY    (GRAPH_Handle hObj, unsigned Value);
void      GRAPH_SetUserDraw  (GRAPH_Handle hObj, void (* pOwnerDraw)(WM_HWIN hObj, int Stage));

void GRAPH_DATA_YT_AddValue(GRAPH_DATA_Handle hDataObj, I16 Value);
void GRAPH_DATA_YT_SetAlign(GRAPH_DATA_Handle hDataObj, int Value);
void GRAPH_DATA_YT_SetOffY (GRAPH_DATA_Handle hDataObj, int Off);

void GRAPH_DATA_XY_AddPoint    (GRAPH_DATA_Handle hDataObj, GUI_POINT * pPoint);
void GRAPH_DATA_XY_SetLineStyle(GRAPH_DATA_Handle hDataObj, U8 LineStyle);
void GRAPH_DATA_XY_SetOffX     (GRAPH_DATA_Handle hDataObj, int Off);
void GRAPH_DATA_XY_SetOffY     (GRAPH_DATA_Handle hDataObj, int Off);
void GRAPH_DATA_XY_SetPenSize  (GRAPH_DATA_Handle hDataObj, U8 PenSize);

float                        GRAPH_SCALE_SetFactor    (GRAPH_SCALE_Handle hScaleObj, float Factor);
const GUI_FONT GUI_UNI_PTR * GRAPH_SCALE_SetFont      (GRAPH_SCALE_Handle hScaleObj, const GUI_FONT GUI_UNI_PTR * pFont);
int                          GRAPH_SCALE_SetNumDecs   (GRAPH_SCALE_Handle hScaleObj, int NumDecs);
int                          GRAPH_SCALE_SetOff       (GRAPH_SCALE_Handle hScaleObj, int Off);
int                          GRAPH_SCALE_SetPos       (GRAPH_SCALE_Handle hScaleObj, int Pos);
GUI_COLOR                    GRAPH_SCALE_SetTextColor (GRAPH_SCALE_Handle hScaleObj, GUI_COLOR Color);
unsigned                     GRAPH_SCALE_SetTickDist  (GRAPH_SCALE_Handle hScaleObj, unsigned Value);

#if defined(__cplusplus)
  }
#endif

#endif   /* if GUI_WINSUPPORT */
#endif   /* GRAPH_H */
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
