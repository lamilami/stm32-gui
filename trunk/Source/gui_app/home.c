/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                                **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                      **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

#include "gui_app.h"

//EventsFunctionList
void OnButtonClicked_B(WM_MESSAGE * pMsg)// balance
{
	balance_pars(pMsg);
}

void OnButtonClicked_A(WM_MESSAGE * pMsg)//averge
{
  	xyz_acc_parameter(pMsg);
}

void OnButtonClicked_H(WM_MESSAGE * pMsg)//hand
{
	if(h_cus == NULL)
	{
	customer(pMsg);
	}
	else
	{
	LimitSpeedH(pMsg);
	}	
}
void OnButtonClicked_T(WM_MESSAGE * pMsg)//table
{
	hlimit_speed_tlimit_speed = 1;
	if(h_cus == NULL)
	{
	customer(pMsg);
	}
	else
	{
	LimitSpeedT(pMsg);
	}
}

void OnButtonClicked_time(WM_MESSAGE * pMsg)
{

	#ifndef WIN_SIM
	TimeSet(pMsg);
	#endif
}

void OnButtonClicked_tuch(WM_MESSAGE * pMsg)
{
//    Draw(pMsg);

//	eMainTask();

//	_ExecCalibration();	

}


//EndofEventsFunctionList


/*********************************************************************
*
*       static data
*
**********************************************************************
*/



/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Home[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  0,  800,480,0,0},
    { BUTTON_CreateIndirect,    "手持限速器",             GUI_ID_BUTTON0,          150,107,218,49, 0,0},
    { BUTTON_CreateIndirect,    "台式限速器",             GUI_ID_BUTTON1,          412,107,218,49, 0,0},
    { BUTTON_CreateIndirect,    "测振加速度",             GUI_ID_BUTTON2,          150,187,218,49, 0,0},
    { BUTTON_CreateIndirect,    "平衡系数",              GUI_ID_BUTTON3,          412,187,218,49, 0,0},
    { BUTTON_CreateIndirect,    "时间设置",                 GUI_ID_BUTTON4,          150,273,218,49, 0,0},
    { BUTTON_CreateIndirect,    "触摸屏校准",                 GUI_ID_BUTTON5,          412,273,218,49, 0,0},
    { TEXT_CreateIndirect,      "电梯设备综合测试台",         GUI_ID_TEXT0,            150,24, 152,16, 0,0},
    { TEXT_CreateIndirect,      "电梯设备公司",            GUI_ID_TEXT1,            619,363,104,16, 0,0},
    { TEXT_CreateIndirect,      "w.xxx.com",         GUI_ID_TEXT2,            643,389,80, 16, 0,0}
};


/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog_Home(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog_Home(WM_MESSAGE * pMsg)
{
	int i;
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    for(i=GUI_ID_BUTTON0; i< GUI_ID_BUTTON6;i++)
	{
	BUTTON_SetFont(WM_GetDialogItem(hWin,i),&GUI_FontHZ_SongTi_16);
	}
    
    //
    //GUI_ID_TEXT0
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT0),&GUI_FontHZ_SongTi_16);
	TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT1),&GUI_FontHZ_SongTi_16);
	TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT2),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT1
    //
    //
}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback_Home(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog_Home(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog_Home(pMsg);
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
                case GUI_ID_BUTTON1:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_T(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON0:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_H(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON2:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_A(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON3:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_B(pMsg);
                            break;
                    }
                    break;

				case GUI_ID_BUTTON4:
					switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_time(pMsg);
                            break;
                    }
                    break;

				case GUI_ID_BUTTON5:
				switch(NCode)
				{
					case WM_NOTIFICATION_CLICKED:
						OnButtonClicked_tuch(pMsg);
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
void home(WM_MESSAGE * pMsg) 
{ 
	current_interface = HOME; 

	if(pMsg)
	{
	WM_DeleteWindow(pMsg->hWin);
#if 0
	WM_HideWindow(pMsg->hWin);
#endif 
	}
    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */

    current_handle = GUI_CreateDialogBox(_aDialogCreate_Home, GUI_COUNTOF(_aDialogCreate_Home), &_cbCallback_Home, 0, 0, 0);

	h_home = current_handle;
}

