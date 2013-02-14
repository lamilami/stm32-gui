/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

#include "KeyBoard_Win.h"
#include "gui_app.h"



/*********************************************************************
*
*       static data
*
**********************************************************************
*/
#define GUI_ID_TEXT_USER   GUI_ID_USER+1
#define GUI_ID_TEXT_E_PROD   GUI_ID_USER+2
#define GUI_ID_TEXT_MODLE   GUI_ID_USER+3
#define GUI_ID_EDIT_USER   GUI_ID_USER+4
#define GUI_ID_EDIT_E_PROD   GUI_ID_USER+5
#define GUI_ID_EDIT_MODLE   GUI_ID_USER+6
#define GUI_ID_BUTTON_HOME   GUI_ID_USER+7
#define GUI_ID_BUTTON_NEXT   GUI_ID_USER+8
#define GUI_ID_TEXT_L_PROD   GUI_ID_USER+9
#define GUI_ID_EDIT_L_PROD   GUI_ID_USER+10
#define GUI_ID_TEXT_L_MODE   GUI_ID_USER+11
#define GUI_ID_EDIT_L_MODE   GUI_ID_USER+12

#define ID_BASE 	GUI_ID_USER
#define ID_LENTH (GUI_ID_EDIT_L_PROD - GUI_ID_TEXT_USER +1)


//KeyBoard_Win 调用示例
// TKeyBoard_H keyboard_h; //实例化
// keyboard_h.work_state = CHINESE;// 设置模式
// ... ...
// keyboard_h.res_ch_data_head 显示
extern TKeyBoard_H keyboard_h;

// 判断是哪种限速 


void OnxxxClicked_Lprod(WM_MESSAGE * pMsg)
{

	if(!keyboard_h.use_now)
	{
	keyboard_h.use_now = 1;
	keyboard_h.work_state = CHINESE;
		
	WidgetLock(pMsg->hWin,LOCK,10,GUI_ID_USER,GUI_ID_EDIT_L_PROD);
	KeyBoard_Win(&keyboard_h);
	WidgetLock(pMsg->hWin,UNLOCK,10,GUI_ID_USER,GUI_ID_EDIT_L_PROD);
	
	EDIT_SetFont(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_L_PROD), &GUI_FontHZ_SongTi_16);
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_L_PROD), keyboard_h.res_ch_data_head);
	keyboard_h.use_now = 0;
	
	}	
}
void OnButtonClicked_Next(WM_MESSAGE * pMsg)
{

	if(h_pars == NULL)
	{
	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_USER), custormer.custorm, sizeof(custormer.custorm));
	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_E_PROD), custormer.elevator_productor, sizeof(custormer.elevator_productor));
	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_MODLE), custormer.series_no, sizeof(custormer.series_no));
	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_L_PROD), custormer.limitor_productor, sizeof(custormer.limitor_productor));
	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_L_MODE), custormer.limitor_series, sizeof(custormer.limitor_series));
	if(hlimit_speed_tlimit_speed == 0)
	{
	parameter(pMsg);
	}else{
	tparameter(pMsg);
	}

	}else{
	if(hlimit_speed_tlimit_speed == 0)
	{
	 LimitSpeedH(pMsg);
	}else{
//	 LimitSpeedT(pMsg);
	}
	}

}
void OnButtonClicked_Home(WM_MESSAGE * pMsg)
{
	home(pMsg); 
}
void OnxxxClicked_Model(WM_MESSAGE * pMsg)
{

}
void OnxxxClicked_Eprod(WM_MESSAGE * pMsg)
{

}

void OnEditClicked_Custermor(WM_MESSAGE * pMsg)
{


}
//EndofEventsFunctionList




/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Cus[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  0,  800,480,0,0},
    { TEXT_CreateIndirect,      "用  户",            GUI_ID_TEXT_USER,            107,49, 56, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_USER,            219,49, 245,21, 0,0},
    
    { TEXT_CreateIndirect,      "电梯制造商",        GUI_ID_TEXT_E_PROD,           107,96, 88, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_E_PROD,           219,91, 245,21, 0,0},
    { TEXT_CreateIndirect,      "电梯型号",          GUI_ID_TEXT_MODLE,            107,152,72, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_MODLE,            219,147,245,21, 0,0},

    { TEXT_CreateIndirect,      "限速器制造商",      GUI_ID_TEXT_L_PROD,            107,212,104,16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_L_PROD,            217,207,247,21, 0,0},
    { TEXT_CreateIndirect,      "限速器型号",        GUI_ID_TEXT_L_MODE ,             107,265,88, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_L_MODE,            217,260,247,21, 0,0},
    { BUTTON_CreateIndirect,    "OK",                GUI_ID_BUTTON_NEXT,         585,300,88, 42, 0,0},
   // { BUTTON_CreateIndirect,    "主页面",            GUI_ID_BUTTON_HOME,          694,387,88, 42, 0,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog_Cus(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog_Cus(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //GUI_ID_TEXT_USER
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_USER),&GUI_FontHZ_SongTi_16);
	EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT_USER),&GUI_FontHZ_SongTi_16);
	TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_MODLE),&GUI_FontHZ_SongTi_16);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_USER),500);
    //
    //GUI_ID_TEXT_E_PROD
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_E_PROD),&GUI_FontHZ_SongTi_16);
	EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT_E_PROD),&GUI_FontHZ_SongTi_16);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_E_PROD),500);
    //
    //GUI_ID_TEXT_MODLE
    //

	TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_L_PROD),&GUI_FontHZ_SongTi_16);
	EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT_L_PROD),&GUI_FontHZ_SongTi_16);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_L_PROD),500);
    //
    //GUI_ID_TEXT0
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_L_MODE),&GUI_FontHZ_SongTi_16);
    //
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_HOME),&GUI_FontHZ_SongTi_16);

	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_L_MODE),500);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_MODLE),500);
    //
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_USER),custormer.custorm);
	
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_E_PROD),custormer.elevator_productor);

	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_MODLE),custormer.series_no);
	
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_L_PROD),custormer.limitor_productor);
	
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_L_MODE),custormer.limitor_series);
	
}

/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback_Cus(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:

            PaintDialog_Cus(pMsg);
			
            break;
        case WM_INIT_DIALOG:
            InitDialog_Cus(pMsg);
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
                case GUI_ID_EDIT_USER:
				case GUI_ID_EDIT_E_PROD:
				case GUI_ID_EDIT_L_PROD:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
							UseKeyBoard(pMsg,ID_LENTH,ID_BASE,Id,CHINESE);  
                            break;
                    }
                    break;
           
                case GUI_ID_EDIT_MODLE:
				case GUI_ID_EDIT_L_MODE:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            UseKeyBoard(pMsg,ID_LENTH,ID_BASE,Id,ENGLISH_S);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_HOME:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Home(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_NEXT:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Next(pMsg);
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
void customer(WM_MESSAGE * pMsg) 
{ 
	current_interface = PORTABLE_CUSTOMER;
	if(pMsg)
	{
		WM_DeleteWindow(pMsg->hWin);
#if 0
		WM_HideWindow(pMsg->hWin);
#endif
	}

    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    //CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
    //DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
    //SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
    //SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    //HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
    //RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
    current_handle = GUI_CreateDialogBox(_aDialogCreate_Cus, GUI_COUNTOF(_aDialogCreate_Cus), &_cbCallback_Cus, 0, 0, 0);
	h_cus = current_handle;
}

