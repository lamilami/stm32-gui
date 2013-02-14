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
#include "LimitDraw.h"


extern      TPars   pars;
extern	    TRecord record;
extern      S_GetData get_data;

int button_cr_state;
int i;
WM_HWIN hwin;


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

 GUI_COLOR _aColor[] = {GUI_BLUE,GUI_RED, GUI_GREEN,GUI_CYAN,GUI_MAGENTA,GUI_YELLOW};

 int draw_buf_lim[LIM_SCALE_X_SIZE];

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

	if(disp_mult)
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
	char act_row;
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

	act_row = row_number - row - 1;
	
	record.v1[act_row] = 0;
	record.v2[act_row] = 0;

	 }
}

void OnxxxClicked_DATA(WM_MESSAGE * pMsg)
{
	customer(pMsg);
}

void OnPicDisp(WM_MESSAGE * pMsg)
{
    //limit_draw_run(pMsg);
}


void OnCheckBoxClicked_MUlT(WM_MESSAGE * pMsg)
{
	
}


void OnxxxClicked_Start(WM_MESSAGE * pMsg)
{
	  int lenth;
	  char buf[5];
	  
	  GUI_ConstString _ListBox[] = {"1", "0", "0","E", "", "","R"};
	
	  if(pars.dir == 2)
	  {
		 _ListBox[6] = "D";
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

//	  BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_CR),"正转");
//	  button_cr_state = 1;
//	  pars.dir = 1;

     if(pars.dir !=2)
	{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_CR),"正转中");
	pars.dir = 1;
	}else {
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_CR),"反转中");	
	}
	motor_dir(pars.dir);

	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_STOP),"运行中");
    start_test_init();

	if(!disp_mult)
	{
	draw_clear(&tdraw);
	}
	tdraw.draw_color = _aColor[record.test_times%5];
	tdraw.data_size = 0;
	  	}
	}

	 all_button(0,GUI_ID_BUTTON_DELET);
	 botton_able(1,GUI_ID_BUTTON_STOP);
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
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_STOP),"停止");
	motor_dir(0);
	all_button(1,GUI_ID_BUTTON_DELET );
	
}

void OnxxxClicked_CR(WM_MESSAGE * pMsg)
{
	motor_speed(0);
	if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	{
	
    if(pars.dir == 1)
	{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_CR),"反转");
	pars.dir = 2;
	}else {
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_CR),"正转");	
	pars.dir = 1;
	}
	motor_dir(pars.dir);
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



void delect_now_row(void)
{
	char buf[3];
	int row,row_number,i,j;
		
	LISTVIEW_DeleteRow(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT),0);
	row_number = LISTVIEW_GetNumRows(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT));
		
	for(i=0;i<row_number;i++)
		{
			j = row_number-i;
			sprintf(buf,"%d",j);
			LISTVIEW_SetItemText(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT),0,i,buf);
		 }
		
		record.test_times--;	
}

//
//
#if 0
void Set_Color_cell(unsigned Column, unsigned Row,GUI_COLOR Color)
{
	LISTVIEW_SetItemBkColor(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT),Column,Row,LISTVIEW_CI_UNSEL,Color);
}
#endif



/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/



static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Lim[] = {
    { FRAMEWIN_CreateIndirect,  "LIMIT_SPEED_H",     0,                       0,  0,  390,480,0,0},
    { BUTTON_CreateIndirect,    "开始",                GUI_ID_BUTTON_START,          1, 8,  100,40, 0,0},
    { BUTTON_CreateIndirect,    "停止",                 GUI_ID_BUTTON_STOP,          1, 57,100,40, 0,0},
    { BUTTON_CreateIndirect,    "正转/反转",             GUI_ID_BUTTON_CR,          1, 106, 100,40, 0,0},
    { BUTTON_CreateIndirect,    "删除",                GUI_ID_BUTTON_DELET,         1, 155,100,40, 0,0},
    { BUTTON_CreateIndirect,    "参数设置",              GUI_ID_BUTTON_PARM_SET,         1, 302,100,40, 0,0},
    { BUTTON_CreateIndirect,    "保存",                GUI_ID_BUTTON_SAVE,          1, 204,100,40, 0,0},
    { BUTTON_CreateIndirect,    "打印",                GUI_ID_BUTTON_PRINT,          1, 253,100,40, 0,0},
    { BUTTON_CreateIndirect,    "客户",                GUI_ID_BUTTON_DATA,          1, 351,100,40, 0,0},
    { BUTTON_CreateIndirect,    "主界面",               GUI_ID_BUTTON_HOME,          1, 400,100,40, 0,0},
    { LISTVIEW_CreateIndirect,   NULL,               GUI_ID_LISTVIEW_RESULT,        104,8,280,432,0,0}
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
	TSEPoint tsepoint;
	char buf[8];
	GUI_ConstString _ListBox[] = {"1", "0", "0","E", "", "","R"};
    WM_HWIN hWin = pMsg->hWin,hGraph = 0;
	WM_HWIN hDlg, hItem;
	hDlg = pMsg->hWin;
	buf[0] = 'N';
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
	BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_PIC_DISP),&GUI_FontHZ_SongTi_16);

	
    //PROGBAR_SetValue(WM_GetDialogItem(hWin,GUI_ID_PROGBAR0),50);
    //
    //GUI_ID_LISTVIEW_RESULT
    //
	LISTVIEW_SetAutoScrollV(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),1);

    LISTVIEW_SetFont(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),&GUI_FontHZ_SongTi_16);
	
	LISTVIEW_SetRowHeight(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),24);
	
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),30,"order",GUI_TA_VCENTER|GUI_TA_LEFT);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),50,"V1",GUI_TA_VCENTER|GUI_TA_LEFT);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),50,"V2",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),60,"Res",GUI_TA_VCENTER|GUI_TA_LEFT);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),10,"---",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),10,"---",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),50,"Dir",GUI_TA_VCENTER|GUI_TA_LEFT);
	   

    //LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT),_lvTable_100);
    //
    //GUI_ID_BUTTON_START
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_START),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_CHECKBOX_MULT
    //
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
	for(i=0;i< tget_record.act_record_lenth;i++)
	{
		if(tget_record.sig_record[i].state[0] == 'N')//'N'
		{
		list_view_color(0, i,GUI_LIGHTRED); 
		}
	}

	for(i=0;i<TEST_TIMES;i++)
	{
	exist[i] = 0;
	}

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
                        case WM_NOTIFICATION_RELEASED:
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
                        case WM_NOTIFICATION_RELEASED:
                            OnxxxClicked_Start(pMsg);
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

			   case GUI_ID_PIC_DISP:
			   		switch(NCode)
					{
					    case WM_NOTIFICATION_CLICKED:
                            OnPicDisp(pMsg);
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
		flag_paint = 0;
	}
	GUI_SetBkColor(GUI_BLACK);
    WM_SetDesktopColor(GUI_BLACK);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */

    current_handle = GUI_CreateDialogBox(_aDialogCreate_Lim, GUI_COUNTOF(_aDialogCreate_Lim), &_cbCallback_Lim, 0, 0, 0);
	current_interface = PORTABLE_LIMIT_SPEED;
}



void draw_xy(void)
{
	TSEPoint tsepoint;
	char x_unit[]="X /DIV m/s:";
	char y_unit[]="Y /DIV ms :";

	tscale.x_pix_size = LIM_SCALE_X_SIZE;
	tscale.y_pix_size = LIM_SCALE_Y_SIZE;

	// -- disp_text 显示的是text !!!
	tscale.disp_text_p0.x=480;
	tscale.disp_text_p0.y=460;
	
	tscale.disp_text_p1.x = 600;
	tscale.disp_text_p1.y = 460;
	
    tscale.unit_x = x_unit;
	tscale.unit_y = y_unit;
	
	tscale.y_data_max = pars.ve+0.5/pars.ve;
	tscale.x_data_max = SCALE_X_SIZE;

	// start_point 对应实际的液晶坐标
	tsepoint.start_point.x = 405;
	tsepoint.start_point.y = 435;
	tsepoint.end_point.x = tsepoint.start_point.x + LIM_SCALE_X_SIZE;
	tsepoint.end_point.y = 435;
	draw_scale(tsepoint,0xffff,0);		//X


	tsepoint.start_point.x = 405;
	tsepoint.start_point.y = 435;
	tsepoint.end_point.x = 405;
	tsepoint.end_point.y = tsepoint.start_point.y - LIM_SCALE_Y_SIZE;
	draw_scale(tsepoint,0xffff,0);		//Y

	scale_set(&tscale);
	draw_init();

}

void draw_init(void)
{
	tdraw.buf_size = LIM_SCALE_X_SIZE;
	tdraw.data_size = 0;
	tdraw.disp_kind = 1;
	tdraw.p0.x = X1+10;
	tdraw.p0.y = Y1;
	tdraw.p_rec_lu.x = X0;
	tdraw.p_rec_lu.y = Y0;
	tdraw.p_rec_rd.x = X_E;
	tdraw.p_rec_rd.y = Y1;
	tdraw.draw_color = GUI_BLUE;
	tdraw.buf = draw_buf_lim;
}

void value_to_graph_lim(float value)
{
	int value_pix;
	int mirro_y;
	float rate;

if(current_interface == PORTABLE_LIMIT_SPEED)
	rate = Y_RATE(pars.ve);
else
	rate = Y_RATE(ttpars.Ve);

	value_pix = value*rate;
	mirro_y = Y_MIRRO(value_pix);
	
	//if(mirro_y != tdraw.buf[tdraw.data_size-1])
	{
		tdraw.px.y = mirro_y;
		draw(&tdraw);
	}
}


void list_view_color(unsigned Column, unsigned Row,GUI_COLOR Color)
{
	LISTVIEW_SetItemBkColor(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT),Column,Row,LISTVIEW_CI_UNSEL,Color);
}


void print_head(void)
{
	int i;
 	char ch[]="手持限速器";
	COMM_CHINESE(CH1212);
	for(i=0;i<strlen(ch);i++)
	{
	rdprint(ch[i]);
	}

	COMM_LF;

	for(i =0 ;i<strlen(custormer.custorm);i++)
	{
	rdprint(custormer.custorm[i]);
	}
	
	COMM_LF;

	for(i =0 ;i<strlen(custormer.series_no);i++)
	{
	rdprint(custormer.series_no[i]);
	}

    COMM_LF;

	for(i =0 ;i<strlen(custormer.elevator_productor);i++)
	{
	rdprint(custormer.elevator_productor[i]);
	}

    COMM_LF;

	for(i =0 ;i<strlen(custormer.limitor_productor);i++)
	{
	rdprint(custormer.limitor_productor[i]);
	}

    COMM_LF;

	for(i =0 ;i<strlen(custormer.limitor_series);i++)
	{
	rdprint(custormer.limitor_series[i]);
	}

    COMM_LF;
}

void print_result(void)
{
	int i;
	char ch[]="1234567890123456789";
	COMM_6;
	for(i=0;i<strlen(ch);i++)
	{
	rdprint(ch[i]);
	}
	COMM_Ds;
	COMM_Dm(1);
	COMM_Dm(9);
	COMM_Dm(20);
	COMM_Dm(30);
	COMM_Dm(40);
	COMM_De;

	COMM_HT;
	rdprint('N');
	rdprint('o');

	COMM_HT;
	rdprint('V');
	rdprint('1');


	COMM_HT;
	rdprint('V');
	rdprint('2');


	COMM_HT;
	rdprint('D');
	rdprint('i');
	rdprint('r');

	COMM_HT;
	rdprint('R');
	rdprint('e');
	rdprint('s');

	for(i=1;i<tget_record.act_record_lenth+1;i++);
	
}





