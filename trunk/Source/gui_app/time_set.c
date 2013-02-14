/******************************************************************************

                  版权所有 (C), 2012-2022, 浙大精益

 ******************************************************************************
  文 件 名   : time_set.c
  版 本 号   : 初稿
  作    者   : ganjinming
  生成日期   : 2012年9月10日
  最近修改   :
  功能描述   : 日历设置模块（对话框）
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月10日
    作    者   : ganjinming
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "gui_app.h"
#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

#include "WM.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "PROGBAR.h"
#include "SCROLLBAR.h"
#include "LISTVIEW.h"

/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/
void static time_set_widget_lock(WM_HWIN hWin,ELock_Unlock lock_unlock);
/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

static WM_HWIN edit_hwin = GUI_ID_EDIT0;
/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/


//EventsFunctionList
void OnButtonClicked_Return_TimeSet(WM_MESSAGE * pMsg);
void OnButtonClicked_NUM_TimeSet(WM_MESSAGE * pMsg);
void OnButtonClicked_OK_TimeSet(WM_MESSAGE * pMsg);
void OnButtonClicked_DEL_TimeSet(WM_MESSAGE * pMsg);
void OnEditClicked_TimeSet(WM_MESSAGE * pMsg);
//EndofEventsFunctionList


/*********************************************************************
*
*       static data
*
**********************************************************************
*/

#define GUI_ID_BUTTON_DEL   GUI_ID_USER+3
#define GUI_ID_BUTTON_OK   GUI_ID_USER+2
#define GUI_ID_BUTTON_RETURN   GUI_ID_USER+1

/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  0,  320,240,0,0},
    { TEXT_CreateIndirect,      "年:",                GUI_ID_TEXT0,            7,  26, 32, 16, 0,0},
    { TEXT_CreateIndirect,      "月:",                GUI_ID_TEXT1,            7,  57, 32, 16, 0,0},
    { TEXT_CreateIndirect,      "日:",                GUI_ID_TEXT2,            7,  88, 32, 16, 0,0},
    { TEXT_CreateIndirect,      "时:",                GUI_ID_TEXT3,            7,  119,32, 16, 0,0},
    { TEXT_CreateIndirect,      "分:",                GUI_ID_TEXT4,            7,  150,32, 16, 0,0},
    { EDIT_CreateIndirect,      "2012",              GUI_ID_EDIT0,            45, 26, 51, 21, 0,0},
    { EDIT_CreateIndirect,      "10",                GUI_ID_EDIT1,            45, 57, 51, 21, 0,0},
    { EDIT_CreateIndirect,      "05",                GUI_ID_EDIT2,            45, 88, 51, 21, 0,0},
    { EDIT_CreateIndirect,      "23",                GUI_ID_EDIT3,            45, 119,51, 21, 0,0},
    { EDIT_CreateIndirect,      "59",                GUI_ID_EDIT4,            45, 150,51, 21, 0,0},
    { BUTTON_CreateIndirect,    "7",                 GUI_ID_BUTTON7,          143,18, 35, 35, 0,0},
    { BUTTON_CreateIndirect,    "4",                 GUI_ID_BUTTON4,          143,63, 35, 35, 0,0},
    { BUTTON_CreateIndirect,    "1",                 GUI_ID_BUTTON1,          143,108,35, 35, 0,0},
    { BUTTON_CreateIndirect,    "0",                 GUI_ID_BUTTON0,          143,153,35, 35, 0,0},
    { BUTTON_CreateIndirect,    "8",                 GUI_ID_BUTTON8,          188,18, 35, 35, 0,0},
    { BUTTON_CreateIndirect,    "Del",               GUI_ID_BUTTON_DEL,       233,153,35, 35, 0,0},
    { BUTTON_CreateIndirect,    "5",                 GUI_ID_BUTTON5,          188,63, 35, 35, 0,0},
    { BUTTON_CreateIndirect,    "2",                 GUI_ID_BUTTON2,          188,108,35, 35, 0,0},
    { BUTTON_CreateIndirect,    "OK",                GUI_ID_BUTTON_OK,        188,153,35, 35, 0,0},
    { BUTTON_CreateIndirect,    "9",                 GUI_ID_BUTTON9,          233,18, 35, 35, 0,0},
    { BUTTON_CreateIndirect,    "6",                 GUI_ID_BUTTON6,          233,63, 35, 35, 0,0},
    { BUTTON_CreateIndirect,    "3",                 GUI_ID_BUTTON3,          233,108,35, 35, 0,0},
    { BUTTON_CreateIndirect,    "返回",                GUI_ID_BUTTON_RETURN,    222,212,75, 23, 0,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void static PaintDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void static InitDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
	RTC_Get_Time(&w_timer);
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetTitleVis(hWin,0);
    //
    //GUI_ID_TEXT0
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT0),&GUI_FontHZ_SongTi_16);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT0),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT1),&GUI_FontHZ_SongTi_16);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT1),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT2
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT2),&GUI_FontHZ_SongTi_16);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT2),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT3
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT3),&GUI_FontHZ_SongTi_16);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT3),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT4
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT4),&GUI_FontHZ_SongTi_16);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT4),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_EDIT0
    //
    EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT0), 4);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT0),&GUI_FontHZ_SongTi_16);
    EDIT_SetDecMode(WM_GetDialogItem(hWin,GUI_ID_EDIT0),w_timer.year,1970,2099,0,0);
    //
    //GUI_ID_EDIT1
    //
    EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT1), 2);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT1),&GUI_FontHZ_SongTi_16);
    EDIT_SetDecMode(WM_GetDialogItem(hWin,GUI_ID_EDIT1),w_timer.month,1,12,0,0);
    //
    //GUI_ID_EDIT2
    //
    EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT2), 2);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT2),&GUI_FontHZ_SongTi_16);
    EDIT_SetDecMode(WM_GetDialogItem(hWin,GUI_ID_EDIT2),w_timer.date,1,31,0,0);
    //
    //GUI_ID_EDIT3
    //
    EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT3), 2);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT3),&GUI_FontHZ_SongTi_16);
    EDIT_SetDecMode(WM_GetDialogItem(hWin,GUI_ID_EDIT3),w_timer.hour,0,23,0,0);
    //
    //GUI_ID_EDIT4
    //
    EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT4), 2);
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT4),&GUI_FontHZ_SongTi_16);
    EDIT_SetDecMode(WM_GetDialogItem(hWin,GUI_ID_EDIT4),w_timer.min,0,59,0,0);
    //
    //GUI_ID_BUTTON7
    //
    BUTTON_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON7),BUTTON_CI_UNPRESSED,0xff0000);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON7),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON4
    //
    BUTTON_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON4),BUTTON_CI_UNPRESSED,0xff0000);
    //
    //GUI_ID_BUTTON1
    //
    BUTTON_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),BUTTON_CI_UNPRESSED,0xff0000);
    //
    //GUI_ID_BUTTON0
    //
    BUTTON_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),BUTTON_CI_UNPRESSED,0xff0000);
    //
    //GUI_ID_BUTTON8
    //
    BUTTON_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON8),BUTTON_CI_UNPRESSED,0xff0000);
    //
    //GUI_ID_BUTTON5
    //
    BUTTON_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON5),BUTTON_CI_UNPRESSED,0xff0000);
    //
    //GUI_ID_BUTTON2
    //
    BUTTON_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),BUTTON_CI_UNPRESSED,0xff0000);
    //
    //GUI_ID_BUTTON_OK
    //
    BUTTON_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON_OK),BUTTON_CI_UNPRESSED,0x0045ff);
    //
    //GUI_ID_BUTTON9
    //
    BUTTON_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON9),BUTTON_CI_UNPRESSED,0xff0000);
    //
    //GUI_ID_BUTTON6
    //
    BUTTON_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON6),BUTTON_CI_UNPRESSED,0xff0000);
    //
    //GUI_ID_BUTTON3
    //
    BUTTON_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON3),BUTTON_CI_UNPRESSED,0xff0000);
    //
    //GUI_ID_BUTTON_RETURN
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_RETURN),&GUI_FontHZ_SongTi_16);

}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog(pMsg);
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
                case GUI_ID_EDIT0:
                    switch(NCode)
                    {
                        // case WM_NOTIFICATION_CLICKED:
					   case WM_NOTIFICATION_GOT_FOCUS:
                            OnEditClicked_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_EDIT1:
                    switch(NCode)
                    {
                        // case WM_NOTIFICATION_CLICKED:
					   case WM_NOTIFICATION_GOT_FOCUS:
                            OnEditClicked_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_EDIT2:
                    switch(NCode)
                    {
                        // case WM_NOTIFICATION_CLICKED:
					   case WM_NOTIFICATION_GOT_FOCUS:
                            OnEditClicked_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_EDIT3:
                    switch(NCode)
                    {
                        // case WM_NOTIFICATION_CLICKED:
					   case WM_NOTIFICATION_GOT_FOCUS:
                            OnEditClicked_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_EDIT4:
                    switch(NCode)
                    {
                       // case WM_NOTIFICATION_CLICKED:
					   case WM_NOTIFICATION_GOT_FOCUS:
                            OnEditClicked_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON7:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_NUM_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON4:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_NUM_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON1:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_NUM_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON0:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_NUM_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON8:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_NUM_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_DEL:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_DEL_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON5:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_NUM_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON2:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_NUM_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_OK:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_OK_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON9:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_NUM_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON6:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_NUM_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON3:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_NUM_TimeSet(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_RETURN:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_Return_TimeSet(pMsg);
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
void time_set(WM_MESSAGE *pMsg) 
{ 
    display_time_flag = 0;
    WM_DeleteWindow(pMsg->hWin);
    //GUI_Init();
   // WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    //WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
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
    GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
}


/*****************
*
*本模块回调函数
*
******************/

void OnButtonClicked_DEL_TimeSet(WM_MESSAGE * pMsg)
{
    //DIT_SetText(WM_GetDialogItem(pMsg->hWin,edit_hwin),"  ");
    EDIT_SetText(WM_GetDialogItem(pMsg->hWin,edit_hwin),"");
  //  GUI_EditDec(WM_GetDialogItem(pMsg->hWin,edit_hwin),0);
	//GUI_MessageBox("Press Right Number","Warning!!",0); 

}

void OnButtonClicked_OK_TimeSet(WM_MESSAGE * pMsg)
{	 
    tim  timer;
    timer.year  = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_EDIT0));
	timer.month = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_EDIT1));
	timer.date = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_EDIT2));
	timer.hour = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_EDIT3));
	timer.min  = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_EDIT4));
	timer.sec = 0;
    if(RTC_Check(timer) == ERROR)
    {
        time_set_widget_lock(pMsg->hWin,LOCK);
        my_messagebox();
        time_set_widget_lock(pMsg->hWin,UNLOCK);
        
    }
    else
    {
        RTC_Set(timer);
		w_timer = timer;
        
    }
    
}

void OnButtonClicked_NUM_TimeSet(WM_MESSAGE * pMsg)
{
    int Id;
    Id = WM_GetId(pMsg->hWinSrc);  
    switch(Id)
    {
        case GUI_ID_BUTTON0:
        case GUI_ID_BUTTON1:
        case GUI_ID_BUTTON2:
        case GUI_ID_BUTTON3:
        case GUI_ID_BUTTON4:
        case GUI_ID_BUTTON5:
        case GUI_ID_BUTTON6:
        case GUI_ID_BUTTON7:
        case GUI_ID_BUTTON8:
        case GUI_ID_BUTTON9:
            EDIT_AddKey(WM_GetDialogItem(pMsg->hWin,edit_hwin),Id-GUI_ID_BUTTON0+'0');
            break;
            
    }

}

void OnEditClicked_TimeSet(WM_MESSAGE * pMsg)
{
    edit_hwin = WM_GetId(pMsg->hWinSrc);
/*
    int Id;
    Id = WM_GetId(pMsg->hWinSrc);  
    switch(Id)
    {
        case GUI_ID_EDIT0:
        case GUI_ID_EDIT1:
        case GUI_ID_EDIT2:
        case GUI_ID_EDIT3:
        case GUI_ID_EDIT4:
            edit_hwin = Id;
            break;
     }
*/
}

void OnButtonClicked_Return_TimeSet(WM_MESSAGE * pMsg)
{
    tim	 timer;
    timer.year  = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_EDIT0));
	timer.month = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_EDIT1));
	timer.date = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_EDIT2));
	timer.hour = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_EDIT3));
	timer.min  = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_EDIT4));
	timer.sec = 0;
    if(RTC_Check(timer) == ERROR)
    {
        time_set_widget_lock(pMsg->hWin,LOCK);
        my_messagebox();
        time_set_widget_lock(pMsg->hWin,UNLOCK);
        return;
        
    }
    else
    {
        RTC_Set(timer);
		w_timer = timer;
        
    }
    home((WM_MESSAGE *)pMsg);
}

void static time_set_widget_lock(WM_HWIN hWin,ELock_Unlock lock_unlock)
{
	if(lock_unlock == LOCK)
	{
        WM_DisableWindow(hWin);
	    WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT0));
	    WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT1));
	    WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT2));
	    WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT3));
        WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT4));
	    WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON0));
	    WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON1));
        WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON2));
	    WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON1));
        WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON3));
	    WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON4));
        WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON5));
	    WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON6));
        WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON7));
	    WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON8));
        WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON9));
	    WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON_DEL));
        WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON_OK));
        WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON_RETURN));
	}
    else
    {
	    WM_EnableWindow(hWin);
	    WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT0));
	    WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT1));
	    WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT2));
	    WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT3));
	    WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT4));
	    WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON0));
	    WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON1));
	    WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON2));
	    WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON1));
        WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON3));
        WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON4));
        WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON5));
        WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON6));
        WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON7));
        WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON8));
        WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON9));
        WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON_DEL));
        WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON_OK));
        WM_EnableWindow(WM_GetDialogItem(hWin,GUI_ID_BUTTON_RETURN));
     }
}










