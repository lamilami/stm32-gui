/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

#include "gui_app.h"
#include "KeyBoard.h"

//#include "LimitSpeedH.h"

#include "KeyBoard_Win.h"


/*********************************************************************
*
*       static data
*
**********************************************************************
*/
#define GUI_ID_TEXT_V0   GUI_ID_USER+1
#define GUI_ID_EDIT_V0   GUI_ID_USER+2
#define GUI_ID_TEXT_VA1   GUI_ID_USER+3
#define GUI_ID_EDIT_VA1   GUI_ID_USER+4
#define GUI_ID_TEXT_VA2   GUI_ID_USER+5
#define GUI_ID_EDIT_VA2   GUI_ID_USER+6
#define GUI_ID_TEXT_A1   GUI_ID_USER+7
#define GUI_ID_EDIT_A1   GUI_ID_USER+8
#define GUI_ID_TEXT_A2   GUI_ID_USER+9
#define GUI_ID_EDIT_A2   GUI_ID_USER+10
#define GUI_ID_TEXT_RESERVE1   GUI_ID_USER+11
	
#define GUI_ID_EDIT_A3   GUI_ID_USER+12
#define GUI_ID_TEXT_Ve   GUI_ID_USER+13
#define GUI_ID_EDIT_Ve   GUI_ID_USER+14
		
#define GUI_ID_TEXT_R   GUI_ID_USER+15
#define GUI_ID_EDIT_R   GUI_ID_USER+16
#define GUI_ID_TEXT_RESERVE2   GUI_ID_USER+17
#define GUI_ID_EDIT_LIMIT_CURRENT GUI_ID_USER+18
#define GUI_ID_TEXT_RES1   GUI_ID_USER+19
#define GUI_ID_TEXT_RES2   GUI_ID_USER+20
#define GUI_ID_TEXT_A3   GUI_ID_USER+21

#define GUI_ID_BUTTON_OK   GUI_ID_USER+22
#define GUI_ID_BUTTON_CANCLE GUI_ID_USER+23

#define GUI_ID_TEXT_LIMIT_CURRENT GUI_ID_USER+24

#define GUI_ID_CHECK_BOX_MULT	GUI_ID_USER+25


#define ID_LENTH  GUI_ID_TEXT_LIMIT_CURRENT - GUI_ID_TEXT_V0+1
#define ID_BASE   GUI_ID_USER

extern const GUI_FONT GUI_FontHZ_SongTi_16;


//EndofEventsFunctionList

void OnButtonClicked_Lim(WM_MESSAGE * pMsg)
{
// changes and save 
 
	pars.ve = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_Ve));
	
	pars.R_mm = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_R));
	
	pars.start_speed = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_V0));

	pars.v1=  EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_VA1));
		
	pars.v2=  EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_VA2));
		
	pars.ak1=  EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_A1));
	
	pars.ak2= EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_A2));
	
	pars.ak3=  EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_A3));
	
//	save_parameters();
//	limit_speed(pMsg);

	LimitSpeedH(pMsg);
	
//	limit_draw_run(pMsg);

}

void  OnCheckBoxMUlT(WM_MESSAGE * pMsg)
{
	disp_mult = CHECKBOX_GetState(WM_GetDialogItem(pMsg->hWin,GUI_ID_CHECK_BOX_MULT));
}

/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/
	static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Par[] = {
		{ FRAMEWIN_CreateIndirect,	"Caption",			 0, 					  0,  0,  840,480,0,0},

		{ TEXT_CreateIndirect,		"额定速度", 		 GUI_ID_TEXT_Ve,		  102,44, 72, 16, 0,0},
		{ EDIT_CreateIndirect,		 NULL,				 GUI_ID_EDIT_Ve,		  209,39, 70, 21, 0,5},
		{ TEXT_CreateIndirect,		"m/s",				 GUI_ID_TEXT1,			  295,42, 23, 12, 0,0},

		{ TEXT_CreateIndirect,		"节经", 		     GUI_ID_TEXT_R,		   134,82, 40, 16, 0,0},
		{ EDIT_CreateIndirect,		 NULL,				 GUI_ID_EDIT_R, 		  209,77, 70, 21, 0,5},
		{ TEXT_CreateIndirect,		"mm",				 GUI_ID_TEXT1,			  295,86, 17, 12, 0,0},

		
		{ TEXT_CreateIndirect,		"初速度",			 GUI_ID_TEXT_V0, 		 118,121,56, 16, 0,0},
		{ EDIT_CreateIndirect,		 NULL,				 GUI_ID_EDIT_V0,		  209,121,70, 21, 0,5},
		{ TEXT_CreateIndirect,		"m/s",				 GUI_ID_TEXT1,			  295,125,23, 12, 0,0},

		{ TEXT_CreateIndirect,		"速度V1",			 GUI_ID_TEXT_VA1, 		118,164,56, 16, 0,0},
		{ EDIT_CreateIndirect,		 NULL,				 GUI_ID_EDIT_VA1,		  209,159,70, 21, 0,5},
		{ TEXT_CreateIndirect,		"m/s",				 GUI_ID_TEXT1,			  295,164,23, 12, 0,0},

		{ TEXT_CreateIndirect,		"速度V2",			 GUI_ID_TEXT_VA2, 		118,204,56, 16, 0,0},
		{ EDIT_CreateIndirect,		 NULL,				 GUI_ID_EDIT_VA2,		  209,199,70, 21, 0,5},
		{ TEXT_CreateIndirect,		"m/s",				 GUI_ID_TEXT1,			  295,204,23, 12, 0,0},

		{ TEXT_CreateIndirect,		"加速度A1", 	     GUI_ID_TEXT_A1, 		 102,245,72, 16, 0,0},
		{ EDIT_CreateIndirect,		 NULL,				 GUI_ID_EDIT_A1,		  209,240,70, 21, 0,5},
		{ TEXT_CreateIndirect,		"m2/s", 			 GUI_ID_TEXT1,			  295,249,29, 12, 0,0},
		
		{ TEXT_CreateIndirect,		"加速度A2", 		 GUI_ID_TEXT_A2, 		 102,291,72, 16, 0,0},
		{ EDIT_CreateIndirect,		 NULL,				 GUI_ID_EDIT_A2,		  209,286,70, 21, 0,5},
		{ TEXT_CreateIndirect,		"m2/s", 			 GUI_ID_TEXT1,			  295,295,29, 12, 0,0},
		
		{ TEXT_CreateIndirect,		"加速度A3", 		 GUI_ID_TEXT_A3, 		 102,328,72, 16, 0,0},
		{ EDIT_CreateIndirect,		 NULL,				 GUI_ID_EDIT_A3,		  209,323,70, 21, 0,5},
		{ TEXT_CreateIndirect,		"m2/s", 			 GUI_ID_TEXT1,			  295,326,29, 12, 0,0},


		{ TEXT_CreateIndirect,		"限流值",			 GUI_ID_TEXT_LIMIT_CURRENT,		 126,366,48, 16, 0,0},
		{ EDIT_CreateIndirect,		 NULL,				 GUI_ID_EDIT_LIMIT_CURRENT,			209,361,70, 21, 0,5},
		{ TEXT_CreateIndirect,		"mA",				 GUI_ID_TEXT1,			 295,366,23, 12, 0,0},
		
		{ TEXT_CreateIndirect,		"保留1",			 GUI_ID_TEXT_RES2,		  126,399,48, 16, 0,0},
		{ TEXT_CreateIndirect,		 NULL,				 GUI_ID_TEXT_RESERVE1,	   102,359,0,  16, 0,5},
		{ TEXT_CreateIndirect,		"xxx",				 GUI_ID_TEXT1,			  295,404,23, 12, 0,0},

		{ BUTTON_CreateIndirect,	"OK",				 GUI_ID_BUTTON_OK,			585,400,88, 42, 0,0},
	//	{ BUTTON_CreateIndirect,	"Cancel",			 GUI_ID_BUTTON_CANCLE,		694,400,88, 42, 0,0}
		{ CHECKBOX_CreateIndirect,  "多曲线显示",        GUI_ID_CHECK_BOX_MULT,     498,35, 78, 16, 0,0},
		
	};

/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog_Par(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
}

/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog_Par(WM_MESSAGE * pMsg)
{
	 int i;
	 WM_HWIN hWin = pMsg->hWin;
	 char buf[4];
    //
    //FRAMEWIN
    //
    FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
    FRAMEWIN_AddMaxButton(hWin, FRAMEWIN_BUTTON_RIGHT, 1);
    FRAMEWIN_AddMinButton(hWin, FRAMEWIN_BUTTON_RIGHT, 2);
    //
    //GUI_ID_TEXT_V0
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_V0),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT_VA1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_VA1),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT_VA2
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_VA2),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT_A1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_A1),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT_A2
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_A2),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT_A2
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_A2),&GUI_FontHZ_SongTi_16);

	TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_A3),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT_V0
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_R),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT_V0
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_Ve),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT_RESERVE
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_RESERVE1),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT_RES1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_RES1),&GUI_FontHZ_SongTi_16);
    //
	//GUI_ID_TEXT_RES1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_RES2),&GUI_FontHZ_SongTi_16);
    //
    //
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_A2),&GUI_FontHZ_SongTi_16);
	
	TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_RESERVE2),&GUI_FontHZ_SongTi_16);

	TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_LIMIT_CURRENT),&GUI_FontHZ_SongTi_16);

	/*
	sprintf(buf,"%f",1.23);
	
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_A1),5);

	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_A1),buf);
	*/
	
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_A1),6);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_A2),6);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_A3),6);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_LIMIT_CURRENT),6);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_R),6);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_V0),6);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_VA1),6);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_VA2),6);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_Ve),6);
	
	
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_A1),pars.ak1,0,99999,3,2);

	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_A2),pars.ak2,0,99999,3,2);

	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_A3),pars.ak3,0,99999,2,2);

	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_LIMIT_CURRENT),pars.limit_current_h,0,9999,2,2);

	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_R),pars.R_mm,0,9999,2,2);

	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_V0),pars.start_speed,0,9999,2,2);

	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_VA1),pars.v1,0,9999,2,2);

	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_VA2),pars.v2,0,9999,2,2);

	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_Ve),pars.ve,0,9999,2,2);

	 
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK_BOX_MULT),&GUI_FontHZ_SongTi_16);
	CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK_BOX_MULT),"多曲线显示");
	
    if(disp_mult)
	{
		CHECKBOX_Check(WM_GetDialogItem(hWin,GUI_ID_CHECK_BOX_MULT));
	}

}



/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback_Par(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog_Par(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog_Par(pMsg);
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
				
			    case GUI_ID_EDIT_Ve:
				case GUI_ID_EDIT_V0:
				case GUI_ID_EDIT_VA1:
				case GUI_ID_EDIT_VA2:
				case GUI_ID_EDIT_A1:
				case GUI_ID_EDIT_A2:
				case GUI_ID_EDIT_A3:
				case GUI_ID_EDIT_R:
				case GUI_ID_EDIT_LIMIT_CURRENT:
					
					if(NCode==WM_NOTIFICATION_RELEASED)
					{
					UseKeyBoard(pMsg,ID_LENTH,ID_BASE,Id,SFLOAT);
					break;
					}
					
					break;
					
				case GUI_ID_BUTTON_OK:
					switch(NCode)
					{
						case WM_NOTIFICATION_CLICKED:
							OnButtonClicked_Lim(pMsg);
							break;
					}
					break;

				 case GUI_ID_CHECK_BOX_MULT:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnCheckBoxMUlT(pMsg);
                            break;
                    }
                    break;
            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}


/*********************************************************************
*
*       MainTask
*
**********************************************************************
*/
void parameter(WM_MESSAGE * pMsg)
{ 
	current_interface = PORTABLE_PARAMETER;
	if(pMsg)
	{
		WM_DeleteWindow(pMsg->hWin);

#if 0
		WM_HideWindow(pMsg->hWin);
#endif
	}
    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
   
    current_handle = GUI_CreateDialogBox(_aDialogCreate_Par, GUI_COUNTOF(_aDialogCreate_Par), &_cbCallback_Par, 0, 0, 0);
	h_pars = current_handle;
}
