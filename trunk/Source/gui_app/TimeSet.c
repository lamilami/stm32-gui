/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

#include"gui_app.h"

#define GUI_ID_EDIT_YEAR   GUI_ID_USER+1
#define GUI_ID_EDIT_MONTH   GUI_ID_USER+2
#define GUI_ID_EDIT_DATE   GUI_ID_USER+3
#define GUI_ID_EDIT_HOUR   GUI_ID_USER+4
#define GUI_ID_EDIT_MIN   GUI_ID_USER+5
#define GUI_ID_EDIT_SEC   GUI_ID_USER+6
#define GUI_ID_BUTTON_OK  GUI_ID_USER+7
#define GUI_ID_BUTTON_CAN  GUI_ID_USER+8

extern tim Tim;

extern TKeyBoard_H keyboard_h;

//EventsFunctionList
void OnxxxClicked_TM(WM_MESSAGE * pMsg)
{
	 home(pMsg);	
}

void OnButtonClicked(WM_MESSAGE * pMsg)
{
#ifndef WIN_SIM

	  RTC_Set(Tim);

#endif

	  home(pMsg);
}

void OnEditClicked(WM_MESSAGE * pMsg,int id)
{

	unsigned short dt;
	
 if(!keyboard_h.use_now)
 	{
 	keyboard_h.use_now = 1;
	keyboard_h.work_state = ENGLISH_S;
	
	WidgetLock(pMsg->hWin,LOCK,8,GUI_ID_USER,id);
	KeyBoard_Win(&keyboard_h);
	WidgetLock(pMsg->hWin,UNLOCK,8,GUI_ID_USER,id);

	EDIT_SetFont(WM_GetDialogItem(pMsg->hWin, id), &GUI_Font16_ASCII);
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, id), keyboard_h.res_ch_data_head);

	keyboard_h.use_now = 0;
	
	if(id == GUI_ID_EDIT_YEAR)
	{
		Tim.year = ((*keyboard_h.res_ch_data_head)-'0')*1000+((*(keyboard_h.res_ch_data_head+1))-'0')*100+((*(keyboard_h.res_ch_data_head+2))-'0')*10+((*(keyboard_h.res_ch_data_head+3))-'0');
		
		if(Tim.year <1970 || Tim.year > 2300)
		{
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, id), "");
		return;
		}
	}else{
	
	dt = ((*keyboard_h.res_ch_data_head)-'0')*10+((*(keyboard_h.res_ch_data_head+1))-'0');
	if(id == GUI_ID_EDIT_MONTH){
	
		if(dt>0 && dt<13)
		{
		Tim.month = dt;
		}
	
	}else if(id == GUI_ID_EDIT_DATE)
	{
		if(dt>0 && dt<31)
		{
		Tim.date = dt;
		}
	}else if(id == GUI_ID_EDIT_HOUR)
	{
		if(dt>=0 && dt<=24)
		{
		Tim.hour = dt;
		}
	
	}else if(id == GUI_ID_EDIT_MIN)
	{
		if(dt>=0 && dt<60)
		{
		Tim.min = dt;
		}
	
	}else if(id == GUI_ID_EDIT_SEC)
	{
		if(dt>=0 && dt<60)
		{
		
		Tim.sec = dt;
		}
	}
}
 	}
}




//EndofEventsFunctionList

extern const GUI_FONT GUI_FontHZ_SongTi_16;
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

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_TM[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  0,  800,480,0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_YEAR,        122,76, 75, 21, 0,0},
    { TEXT_CreateIndirect,       NULL,               GUI_ID_TEXT0,            176,85, 0,  12, 0,0},
    { TEXT_CreateIndirect,      "年",                 GUI_ID_TEXT1,            218,81, 24, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_MONTH,       122,112,75, 21, 0,0},
    { TEXT_CreateIndirect,      "月",                 GUI_ID_TEXT2,            218,117,24, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_DATE,        122,160,75, 21, 0,0},
    { TEXT_CreateIndirect,      "日",                 GUI_ID_TEXT3,            218,160,24, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_HOUR,        122,234,75, 21, 0,0},
    { TEXT_CreateIndirect,      "时",                 GUI_ID_TEXT4,            218,239,24, 16, 0,0},
    { TEXT_CreateIndirect,      "分",                 GUI_ID_TEXT5,            218,278,24, 16, 0,0},
    { TEXT_CreateIndirect,      "秒",                 GUI_ID_TEXT6,            218,313,24, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_MIN,         122,273,75, 21, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_SEC,         122,308,75, 21, 0,0},
    { BUTTON_CreateIndirect,    "OK",                GUI_ID_BUTTON_OK,          402,262,83, 32, 0,0},
//    { BUTTON_CreateIndirect,    "Cancel",            GUI_ID_BUTTON_CAN,          402,313,83, 32, 0,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog_TM(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog_TM(WM_MESSAGE * pMsg)
{
    char buf[5];
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
    FRAMEWIN_AddMaxButton(hWin, FRAMEWIN_BUTTON_RIGHT, 1);
    FRAMEWIN_AddMinButton(hWin, FRAMEWIN_BUTTON_RIGHT, 2);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT1),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT2),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT3),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT4),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT5),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT6),&GUI_FontHZ_SongTi_16);
	//
	//
	//
	sprintf(buf,"%d",Tim.year);
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_YEAR),buf);
	sprintf(buf,"%d",Tim.month);
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_MONTH),buf);
	sprintf(buf,"%d",Tim.date);
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_DATE),buf);
	sprintf(buf,"%d",Tim.hour);
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_HOUR),buf);
	sprintf(buf,"%d",Tim.min);
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_MIN),buf);
	sprintf(buf,"%d",Tim.sec);	
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_SEC),buf);
	
	
}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback_TM(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog_TM(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog_TM(pMsg);
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
                case GUI_ID_EDIT_YEAR:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnEditClicked(pMsg,GUI_ID_EDIT_YEAR);
                            break;
                    }
                    break;
                case GUI_ID_EDIT_MONTH:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnEditClicked(pMsg,GUI_ID_EDIT_MONTH);
                            break;
                    }
                    break;
                case GUI_ID_EDIT_DATE:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnEditClicked(pMsg,GUI_ID_EDIT_DATE);
                            break;
                    }
                    break;
                case GUI_ID_EDIT_HOUR:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnEditClicked(pMsg,GUI_ID_EDIT_HOUR);
                            break;
                    }
                    break;
                case GUI_ID_EDIT_MIN:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnEditClicked(pMsg,GUI_ID_EDIT_MIN);
                            break;
                    }
                    break;
                case GUI_ID_EDIT_SEC:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnEditClicked(pMsg,GUI_ID_EDIT_SEC);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_OK:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_CAN:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_TM(pMsg);
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
void TimeSet(WM_MESSAGE * pMsg)  
{ 
    if(pMsg)
	{
		WM_DeleteWindow(pMsg->hWin);
	}

    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
	
#ifndef WIN_SIM
	RTC_Get_Time(&Tim);
#endif
		
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
    GUI_CreateDialogBox(_aDialogCreate_TM, GUI_COUNTOF(_aDialogCreate_TM), &_cbCallback_TM, 0, 0, 0);
	
}
