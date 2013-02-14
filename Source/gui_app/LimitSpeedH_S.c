/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

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
#include "GRAPH.h"
#include "string.h"
#include "home.h"
#include "gui_app.h"
#include "LimitSpeedH.h"
#include "mot.h"
#include "stdio.h"
#include "gui_app.h"




extern      TPars   pars;
extern	    TRecord record;
extern      S_GetData get_data;

int button_cr_state;

int disp_muit;

int i;


/*********************************************************************
*
*       static data
*
**********************************************************************
*/


 GRAPH_DATA_Handle  _ahData[TEST_TIMES]; /* Array of handles for the GRAPH_DATA objects */
unsigned int exist[TEST_TIMES];
 GRAPH_SCALE_Handle _hScaleV;   /* Handle of vertical scale */
 GRAPH_SCALE_Handle _hScaleH;   /* Handle of horizontal scale */

 I16 _aValue[TEST_TIMES];

GUI_COLOR _aColor[] = {GUI_BLUE,GUI_RED, GUI_GREEN,GUI_CYAN};
//,GUI_MAGENTA,GUI_YELLOW,GUI_LIGHTBLUE,GUI_LIGHTGREEN,GUI_LIGHTRED,	GUI_LIGHTRED,GUI_DARKCYAN,GUI_DARKMAGENTA,GUI_DARKYELLOW,GUI_WHITE,GUI_LIGHTGRAY,GUI_GRAY,GUI_DARKGRAY,GUI_BLUE,GUI_RED, GUI_GREEN}; /* Array of colors for the GRAPH_DATA objects */

/*********************************************************************
*
* _UserDraw
*
* Purpose:
*   This routine is called by the GRAPH object before anything is drawn
*   and after the last drawing operation.
*/
static void _UserDraw(WM_HWIN hWin, int Stage) {
  if (Stage == GRAPH_DRAW_LAST) {
    char acText[] = "Speed";
    GUI_RECT Rect, RectInvalid;
    int FontSizeY;
    GUI_SetFont(&GUI_Font13_ASCII);
    FontSizeY = GUI_GetFontSizeY();
    WM_GetInsideRect(&Rect);
    WM_GetInvalidRect(hWin, &RectInvalid);
    Rect.x1 = Rect.x0 + FontSizeY;
    GUI_SetColor(GUI_YELLOW);
    GUI_DispStringInRectEx(acText, &Rect, GUI_TA_HCENTER, strlen(acText), GUI_ROTATE_CCW);
  }
}


void add_value_graph(int loc , signed short data )
{
	GUI_POINT pPoint;

static act_x_lenth = 0;

#ifdef DISP_YT

	if(disp_muit)
		GRAPH_DATA_YT_AddValue(_ahData[loc], data);
	else
		GRAPH_DATA_YT_AddValue(_ahData[0], data);
#endif

#ifdef DISP_XY

	pPoint.x = act_x_lenth++;
	pPoint.y = data;
	if(pPoint.x >= DISP_XY_X_LENTH)
		act_x_lenth = 0;

if(disp_muit)

	GRAPH_DATA_XY_AddPoint(_ahData[loc],&pPoint);
else
	GRAPH_DATA_XY_AddPoint(_ahData[0],&pPoint);


#endif
}


//EventsFunctionList
void OnxxxClicked_DELET(WM_MESSAGE * pMsg)
{
	char buf[3];
	int row,row_number,i,j;
	if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	{
	row_number = LISTVIEW_GetNumRows(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT));
	
	row = LISTVIEW_GetSel(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT));
	
	LISTVIEW_DeleteRow(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT),row);
	
	for(i=0;i<row_number-1;i++)
	 {
	    j = row_number-1-i;
	    sprintf(buf,"%d",j);

		LISTVIEW_SetItemText(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT),0,i,buf);

	 }
	
	record.test_times--;
	record.v1[row] = 0;
	record.v2[row] = 0;
	 }

}
void OnxxxClicked_DATA(WM_MESSAGE * pMsg)
{
}
void OnCheckBoxClicked_MUlT(WM_MESSAGE * pMsg)
{
   
	disp_muit = CHECKBOX_GetState(WM_GetDialogItem(pMsg->hWin,GUI_ID_CHECKBOX_MULT));
	
}
void OnxxxClicked_Start(WM_MESSAGE * pMsg)
{

	  int lenth;
	  char buf[5];
	
	  GUI_ConstString _ListBox[] = {"1", "0", "0","E", "", "","R"};

	if(!disp_muit && !exist[0])// 如果单曲线显示
	  {

#ifdef DISP_YT
	_ahData[0] = GRAPH_DATA_YT_Create(_aColor[0], 500, 0, 0);//YT
	
#endif

#ifdef DISP_XY

	_ahData[0]  = GRAPH_DATA_XY_Create(_aColor[0],DISP_XY_X_LENTH,0, 0);
     
#endif
	 
    GRAPH_AttachData(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), _ahData[0]);//attaches  data object to graph object
    exist[0] = 1;
	GRAPH_SetUserDraw(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), _UserDraw); /* Enable user draw */
			
    GRAPH_SetGridVis(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), 6);
	GRAPH_SetVSizeY(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), 1000);
    _hScaleV = GRAPH_SCALE_Create( 35, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 10);
    GRAPH_SCALE_SetTextColor(_hScaleV, GUI_YELLOW);
    GRAPH_AttachScale(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), _hScaleV);
	  }

	  if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	  	{
	
	  lenth = LISTVIEW_GetNumRows(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT));
	  
	  if(lenth < TEST_TIMES)
	  {
	  record.test_times++;
	  
	  sprintf(buf,"%d",lenth+1);
	  _ListBox[0]= buf;
	  LISTVIEW_InsertRow(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT),0,_ListBox);
	
	  if(disp_muit)
	  	{
	  	if(!exist[lenth])
	  		{
		_ahData[lenth] = GRAPH_DATA_YT_Create(_aColor[lenth%3], 500, 0, 0);//YT
	 
     	GRAPH_AttachData(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), _ahData[lenth]);//attaches  data object to graph object
     	exist[lenth] = 1;
		
			if(lenth == 0)
			{
			GRAPH_SetUserDraw(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), _UserDraw); /* Enable user draw */	
    		GRAPH_SetGridVis(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), 6);
			GRAPH_SetVSizeY(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), 1000);
    		_hScaleV = GRAPH_SCALE_Create( 35, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 10);
    		GRAPH_SCALE_SetTextColor(_hScaleV, GUI_YELLOW);
    		GRAPH_AttachScale(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), _hScaleV);
			}

	    }
	  }
      
	  BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_CR),"正转");
	  button_cr_state = 1;

	  pars.dir = 1;
	  
	  start_test_init();
	  	}
	}
}

void OnListViewScrollChanged(WM_MESSAGE * pMsg)
{
}

void OnListViewSelChanged(WM_MESSAGE * pMsg)
{


}
void OnxxxClicked_STOP(WM_MESSAGE * pMsg)
{
    
    get_data.e_work_state = HAND_OFF;
	motor_dir(0);
}

void OnxxxClicked_CR(WM_MESSAGE * pMsg)
{
	if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	{
	
    if(button_cr_state)
	{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_CR),"反转");
	button_cr_state = 0;
	}else{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_CR),"正转");
	button_cr_state = 1;	
	}
	}
	 
}
void OnxxxClicked_HOME(WM_MESSAGE * pMsg)
{


	home(pMsg); 
}

//
//
void OnxxxClicked_SAVE(WM_MESSAGE * pMsg,ESaveState save_state)
{
	int i,j,k;
	LISTVIEW_Handle hObj;
	char buf[10];
	hObj = WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT);
	tget_record.act_record_lenth = LISTVIEW_GetNumRows(hObj);
	for(i=0;i<LISTVIEW_GetNumRows(hObj);i++)
		{

	LISTVIEW_GetItemText(hObj,0,i,tget_record.sig_record[i].order,4);

	LISTVIEW_GetItemText(hObj,1,i,tget_record.sig_record[i].V1,5);

	LISTVIEW_GetItemText(hObj,2,i,tget_record.sig_record[i].V2,5);

	LISTVIEW_GetItemText(hObj,3,i,tget_record.sig_record[i].result_r_e,5);
	
	LISTVIEW_GetItemText(hObj,4,i,tget_record.sig_record[i].state,8);

	LISTVIEW_GetItemText(hObj,5,i,tget_record.sig_record[i].time,6);

	LISTVIEW_GetItemText(hObj,6,i,tget_record.sig_record[i].dir,3);

	
		
		}

	if(save_state == RemberToSd)
	{
	tget_record.year = Tim.year;
	tget_record.month = Tim.month;
	tget_record.date = Tim.date;

	
	file_clear();
    save_custormer();
	save_parameters();
	save_get_record();
	}
	

	
}
void OnxxxClicked_PRINT(WM_MESSAGE * pMsg)
{
	

}
void OnButtonClicked_PARM_SET(WM_MESSAGE * pMsg)
{

	
	OnxxxClicked_SAVE(pMsg,RemberToRam);
	parameter(pMsg);
	
	

}
//EndofEventsFunctionList




/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/




static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Lim[] = {
    { FRAMEWIN_CreateIndirect,  "LIMIT_SPEED_H",     0,                       0,  0,  800,480,FRAMEWIN_CF_MOVEABLE,0},
    { CHECKBOX_CreateIndirect,  "多曲线显示",          GUI_ID_CHECKBOX_MULT,           251,394,107,20, 0,0},
    { BUTTON_CreateIndirect,    "开始",                GUI_ID_BUTTON_START,          30, 389,120,25, 0,0},
    { BUTTON_CreateIndirect,    "停止",                GUI_ID_BUTTON_STOP,         30, 420,120,25, 0,0},
    { BUTTON_CreateIndirect,    "正转/反转",           GUI_ID_BUTTON_CR,          156,387,89, 57, 0,0},
    { BUTTON_CreateIndirect,    "删除",                GUI_ID_BUTTON_DELET,          379,389,120,25, 0,0},
    { BUTTON_CreateIndirect,    "参数设置",            GUI_ID_BUTTON_PARM_SET,          379,419,120,25, 0,0},
    { BUTTON_CreateIndirect,    "保存",                GUI_ID_BUTTON_SAVE,           518,388,120,25, 0,0},
    { BUTTON_CreateIndirect,    "打印",                GUI_ID_BUTTON_PRINT,          518,420,120,25, 0,0},
    { BUTTON_CreateIndirect,    "数据",                GUI_ID_BUTTON_DATA,          660,389,120,25, 0,0},
    { BUTTON_CreateIndirect,    "主界面",              GUI_ID_BUTTON_HOME,         660,420,120,25, 0,0},
    { LISTVIEW_CreateIndirect,   NULL,                 GUI_ID_LISTVIEW_RESULT,        379,27, 401,350,0,0},
//    { PROGBAR_CreateIndirect,    NULL,               GUI_ID_PROGBAR0,         577,6,  100,16, 0,0},
    { TEXT_CreateIndirect,      "Data_Time",           GUI_ID_TEXT_DATE_TIME,           580,10, 179,12, 0,0},
	{ GRAPH_CreateIndirect,      NULL,                 GUI_ID_GRAPH0    ,   10,   27, 350, 350 },
	{ TEXT_CreateIndirect,       "A",                  GUI_ID_TEXT_CURRENT,            404,10, 77, 12, 0,0}
};


/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog_Lim(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog_Lim(WM_MESSAGE * pMsg)
{
	int i,j;
	char buf[8];
	GUI_ConstString _ListBox[] = {"1", "0", "0","E", "", "","R"};
    WM_HWIN hWin = pMsg->hWin,hGraph = 0;
	WM_HWIN hDlg, hItem;
	hDlg = pMsg->hWin;
    //
    //FRAMEWIN
    //
    //FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
    //FRAMEWIN_AddMaxButton(hWin, FRAMEWIN_BUTTON_RIGHT, 1);
    //FRAMEWIN_AddMinButton(hWin, FRAMEWIN_BUTTON_RIGHT, 2);
    //
    //GUI_ID_BUTTON_PARM_SET
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_PARM_SET),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON_PRINT
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_PRINT),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON_SAVE
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_SAVE),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON_HOME
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_HOME),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON_CR
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_CR),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON_STOP
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_STOP),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_PROGBAR0
    //
    PROGBAR_SetValue(WM_GetDialogItem(hWin,GUI_ID_PROGBAR0),50);
    //
    //GUI_ID_LISTVIEW_RESULT
    //
    //LISTBOX_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),0,0xffffff);
    LISTVIEW_SetFont(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),&GUI_FontHZ_SongTi_16);
    LISTVIEW_SetAutoScrollH(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),1);
    LISTVIEW_SetAutoScrollV(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),1);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),30,"order",GUI_TA_VCENTER|GUI_TA_LEFT);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),70,"V1",GUI_TA_VCENTER|GUI_TA_LEFT);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),70,"V2",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),65,"Res",GUI_TA_VCENTER|GUI_TA_LEFT);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),60,"State",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),70,"Time",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),50,"Dir",GUI_TA_VCENTER|GUI_TA_LEFT);

    //LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),_lvTable_100);
    //
    //GUI_ID_BUTTON_START
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_START),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_CHECKBOX_MULT
    //
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECKBOX_MULT),"多曲线显示");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECKBOX_MULT),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON_DATA
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_DATA),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON_DELET
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_DELET),&GUI_FontHZ_SongTi_16);




	for(i=0;i< tget_record.act_record_lenth;i++)
	{
	_ListBox[0] = tget_record.sig_record[i].order;
	_ListBox[1] = tget_record.sig_record[i].V1;
	_ListBox[2] = tget_record.sig_record[i].V2;
	_ListBox[3] = tget_record.sig_record[i].result_r_e;
	_ListBox[4] = tget_record.sig_record[i].state;
	_ListBox[5] = tget_record.sig_record[i].time;
	_ListBox[6] = tget_record.sig_record[i].dir;

	LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),_ListBox);
		
	}

	for(i=0;i<TEST_TIMES;i++)
	{
	exist[i] = 0;
	}


	
	#if 0
	hItem = WM_GetDialogItem(hDlg, GUI_ID_GRAPH0);
	/* Add graphs */
    for (i = 0; i < GUI_COUNTOF(_aColor); i++) {
      _aValue[i] = rand() % 180;
      _ahData[i] = GRAPH_DATA_YT_Create(_aColor[i], 500, 0, 0);
      GRAPH_AttachData(hItem, _ahData[i]);
    }
	 /* Set graph attributes */
    GRAPH_SetGridDistY(hItem, 2);
    GRAPH_SetGridVis(hItem, 1);
    GRAPH_SetGridFixedX(hItem, 1);
    GRAPH_SetUserDraw(hItem, _UserDraw);
    /* Create and add vertical scale */
    _hScaleV = GRAPH_SCALE_Create( 5, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 5);
    GRAPH_SCALE_SetTextColor(_hScaleV, GUI_YELLOW);
    GRAPH_AttachScale(hItem, _hScaleV);
    /* Create and add horizontal scale */
    _hScaleH = GRAPH_SCALE_Create(15, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 5);
    GRAPH_SCALE_SetTextColor(_hScaleH, GUI_DARKGREEN);
    GRAPH_AttachScale(hItem, _hScaleH);
	#endif 
}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback_Lim(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog_Lim(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog_Lim(pMsg);
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
                case GUI_ID_BUTTON_PARM_SET:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_PARM_SET(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_PRINT:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_PRINT(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_SAVE:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_SAVE(pMsg,RemberToSd);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_HOME:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_HOME(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_CR:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_CR(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_STOP:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_STOP(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_LISTVIEW_RESULT:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_SCROLL_CHANGED:
                            OnListViewScrollChanged(pMsg);
                            break;
                        case WM_NOTIFICATION_SEL_CHANGED:
                            OnListViewSelChanged(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_START:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_Start(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_CHECKBOX_MULT:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnCheckBoxClicked_MUlT(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_DATA:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_DATA(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_DELET:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_DELET(pMsg);
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
void LimitSpeedH(WM_MESSAGE * pMsg)
{ 
	WM_HWIN hGraph = 0;
	if(pMsg)
	{
		WM_DeleteWindow(pMsg->hWin);
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
    current_handle = GUI_CreateDialogBox(_aDialogCreate_Lim, GUI_COUNTOF(_aDialogCreate_Lim), &_cbCallback_Lim, 0, 0, 0);
	current_interface = PORTABLE_LIMIT_SPEED;

}

