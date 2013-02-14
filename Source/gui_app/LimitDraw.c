#include"LimitDraw.h"

#include"gui_app.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"
#include "DROPDOWN.h"

#include "BUTTON_Private.h"
#include "Draw.h"
#include "math.h"
#include "LimitSpeedH.h"

WM_MESSAGE Msg;

void (*Pfun[ ])() = {on_start,on_stop,on_dir,on_list_delect,on_save,on_print,on_par,on_mode,on_home}; 

WM_HWIN h_win;
LISTVIEW_Handle  h_list_view;
CHECKBOX_Handle  h_check_box;
BUTTON_Handle h_botton;

extern TScale tscale;
float dt;

WM_HWIN h_win_mid;


char x_unit[]="X /DIV m/s:";
char y_unit[]="Y /DIV ms :";

int draw_buf[LIM_SCALE_X_SIZE];

void on_start()
{
	  int lenth;
	  char buf[5];

	  GUI_ConstString _ListBox[] = {"1", "0", "0","E", "", "","R"};
	  if(pars.dir == 2)
	  {
		 _ListBox[6] = "D";
	  }
#if 0
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
#endif

	 if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	  {
	
	  lenth = LISTVIEW_GetNumRows(h_list_view);
	  
	  if(lenth < TEST_TIMES)
	  {
	  record.test_times++;
	  
	  sprintf(buf,"%d",lenth+1);
	  _ListBox[0]= buf;
	  LISTVIEW_InsertRow(h_list_view,0,_ListBox);

#if 0
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
#endif

//	  BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_CR),"正转");
//	  button_cr_state = 1;
//	  pars.dir = 1;
    if(pars.dir !=2)
	{
	BUTTON_SetText(WM_GetDialogItem(h_win,GUI_BUTTON_DIR),"正转中");
	pars.dir = 1;
	}else {
	BUTTON_SetText(WM_GetDialogItem(h_win,GUI_BUTTON_DIR),"反转中");	
	}
	motor_dir(pars.dir);

	BUTTON_SetText(WM_GetDialogItem(h_win,GUI_BUTTON_STOP),"运行中");
    start_test_init();
	  	}
	}


}



void on_stop()
{
	get_data.e_work_state = HAND_OFF;
	BUTTON_SetText(WM_GetDialogItem(h_win,GUI_BUTTON_STOP),"停止");
	motor_dir(0);
}

void on_dir()
{
	motor_speed(0);
	if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	{
	
    if(pars.dir == 1)
	{
	BUTTON_SetText(WM_GetDialogItem(h_win,GUI_BUTTON_DIR),"反转");
	pars.dir = 2;
	}else {
	BUTTON_SetText(WM_GetDialogItem(h_win,GUI_BUTTON_DIR),"正转");	
	pars.dir = 1;
	}
	motor_dir(pars.dir);
	}
}

void on_list_delect()
{

	char buf[3];
	char act_row;
	int row,row_number,i,j;
	if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	{
	row_number = LISTVIEW_GetNumRows(h_list_view);
	
	row = LISTVIEW_GetSel(h_list_view);
	
	LISTVIEW_DeleteRow(h_list_view,row);
	
	for(i=0;i<row_number-1;i++)
	 {
	    j = row_number-1-i;
	    sprintf(buf,"%d",j);
		LISTVIEW_SetItemText(h_list_view,0,i,buf);
	 }
	
	record.test_times--;

	act_row = row_number - row - 1;
	
	record.v1[act_row] = 0;
	record.v2[act_row] = 0;
	 }

}

void on_mode(void)
{
	save_to_ram();
	hide_wig();
	WM_ShowWindow(h_cus);

	//customer(NULL);
}

void on_par(void)
{
	save_to_ram();
	hide_wig();
	WM_ShowWindow(h_pars);
	//parameter(NULL);
}

void on_print(void)
{
	
}

void on_save(void)
{
	int i,j,k;
	LISTVIEW_Handle hObj;
	char buf[10];
	hObj = h_list_view;
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

//	if(save_state == RemberToSd)
//	{
	tget_record.year = Tim.year;
	tget_record.month = Tim.month;
	tget_record.date = Tim.date;

	file_clear();
    save_custormer();
	save_parameters();
	save_get_record();
//	}

}


void save_to_ram(void)
{
	int i,j,k;
	LISTVIEW_Handle hObj;
	char buf[10];
	hObj = h_list_view;
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
}

void on_home(void)
{
	save_to_ram();
	hide_wig();
	WM_ShowWindow(h_home);
	
	//home(NULL); 
}

void Set_Color_cell(unsigned Column, unsigned Row,GUI_COLOR Color)
{
	LISTVIEW_SetItemBkColor(h_list_view,Column,Row,LISTVIEW_CI_UNSEL,Color);
}

void value_to_graph(float value)
{
	int value_pix;
	int mirro_y;
	float rate;
	rate = Y_RATE(pars.ve);
	value_pix = value*rate;
	mirro_y = Y_MIRRO(value_pix);
	
	if(mirro_y != tdraw.buf[tdraw.data_size-1])
	{
		tdraw.px.y = mirro_y;
		draw(&tdraw);
	}
}


void limit_draw_init(WM_MESSAGE * pMsg)
{
	int i,j,k;
	TSEPoint tsepoint;
	BUTTON_Handle hButton;
   
	GUI_ConstString _ListBox[] = {"1", "0", "0","E", "", "","R"};

	char* a[]={
	"运行",
	"停止",
	"正转/反转",
	"删除",
	"保存",
	"打印",
	"基础参数",
	"型号信息",
	"主页面"
	};

	if(pMsg)
	{
		//WM_DeleteWindow(pMsg->hWin);
		WM_HideWindow(pMsg->hWin);

	}
	
	h_win = WM_GetActiveWindow( );
	Msg.hWin = h_win;

	h_main = h_win;

	WM_Paint(WM_GetDesktopWindow());
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	
	scale_set(&tscale);
	GUI_DispStringAt("GRAPH", 0,0);
	
	h_list_view = LISTVIEW_Create(401, 21, 280,432, h_win, LIST_VIEW, WM_CF_SHOW, 0);

	h_check_box = CHECKBOX_Create(295,35,84,16,h_win,CHECK_BOX, WM_CF_SHOW);

	CHECKBOX_SetFont(h_check_box,&GUI_FontHZ_SongTi_16);
	CHECKBOX_SetText(h_check_box,"多曲线显示");
	
	LISTVIEW_SetAutoScrollV(h_list_view,1);
    LISTVIEW_SetFont(h_list_view,&GUI_FontHZ_SongTi_16);
	LISTVIEW_SetRowHeight(h_list_view,24);
    LISTVIEW_AddColumn(h_list_view,30,"order",GUI_TA_VCENTER|GUI_TA_LEFT);
    LISTVIEW_AddColumn(h_list_view,50,"V1",GUI_TA_VCENTER|GUI_TA_LEFT);
    LISTVIEW_AddColumn(h_list_view,50,"V2",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(h_list_view,65,"Res",GUI_TA_VCENTER|GUI_TA_LEFT);
    LISTVIEW_AddColumn(h_list_view,10,"---",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(h_list_view,10,"---",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(h_list_view,50,"Dir",GUI_TA_VCENTER|GUI_TA_LEFT);
	
	for(i=GUI_BUTTON_RUN;i<BUTTON_LENTH+1;i++)
	{
	h_botton= BUTTON_Create(697, 49*i-42, 100,40,i, WM_CF_SHOW);
	BUTTON_SetFont(h_botton,&GUI_FontHZ_SongTi_16);
	BUTTON_SetText(h_botton,a[i-1]);
	}
	
	tsepoint.start_point.x = 10;
	tsepoint.start_point.y = 440;
	tsepoint.end_point.x = tsepoint.start_point.x + LIM_SCALE_X_SIZE;
	tsepoint.end_point.y = 440;
	draw_scale(tsepoint,0xffff,0);		// X

	tsepoint.start_point.x = 10;
	tsepoint.start_point.y = 21;
	tsepoint.end_point.x = 10;
	tsepoint.end_point.y = tsepoint.start_point.y + LIM_SCALE_Y_SIZE;
	draw_scale(tsepoint,0xffff,0);		// Y
	
	for(i=0;i< tget_record.act_record_lenth;i++)
	{
	_ListBox[0] = tget_record.sig_record[i].order;
	_ListBox[1] = tget_record.sig_record[i].V1;
	_ListBox[2] = tget_record.sig_record[i].V2;
	_ListBox[3] = tget_record.sig_record[i].result_r_e;
	_ListBox[4] = tget_record.sig_record[i].state;
	_ListBox[5] = tget_record.sig_record[i].time;
	_ListBox[6] = tget_record.sig_record[i].dir;

	LISTVIEW_AddRow(h_list_view,_ListBox);
	}
	
	get_data.e_work_state = 0;
	
	GUI_SetColor(GUI_BLUE);
}


void refresh(void)
{
	    char buf_c[6],buf[20];
		
		get_data.current = 1.23;
		sprintf(buf_c,"%.2fA",get_data.current);
		GUI_DispStringAt(buf_c,150,0);

#ifndef WIN_SIM
		RTC_time_to_string(buf ,Tim);
#endif
		GUI_DispStringAt(buf,650,460);

#if 1
	dt=dt+0.1;
	if(dt > pars.ve+0.5)
	{
	dt= 0;
	}

//	get_data.e_work_state = START_TEST;
#endif
		switch(get_data.e_work_state)
		  {
		case START_TEST:
		//	value_to_graph(dt);
			sprintf(buf_c,"%.3f",get_data.speed);
			LISTVIEW_SetItemText(h_list_view,1,0,buf_c);
			break;
			
		case GET_V1:
		//	add_value_graph(record.test_times-1, (signed short)get_data.speed);
			sprintf(buf_c,"%.3f",get_data.speed);
			LISTVIEW_SetItemText(h_list_view,2,0,buf_c);
			break;
			
		case ONE_STOP:
			sprintf(buf_c,"%.3f",get_data.speed);
			LISTVIEW_SetItemText(h_list_view,2,0,buf_c);
			break;
			
		case CURRENT_LIMIT_H:
			break;
			
		case CURRENT_LIMIT_L:
			break;

		case SPEED_LIMIT:
			break;

		case ALL_TEST_STOP:
			break;
			
		case HAND_OFF:
			break;

		case SWI_ERR:
			break;

		default:
			//add_value_graph(record.test_times-1, rand());
			break;
		  }

		
		LISTVIEW_SetItemText(h_list_view,3,0,state_string[get_data.e_work_state -1]);
}


void limit_draw_run(WM_MESSAGE * pMsg)
{
	unsigned  int get_key,i;
	
	tdraw.buf_size = LIM_SCALE_X_SIZE;
	tdraw.data_size = 0;
	tdraw.disp_kind = 1;
	tdraw.p0.x = X1;
	tdraw.p0.y = Y1;
	tdraw.p_rec_lu.x = X0;
	tdraw.p_rec_lu.y = Y0;
	tdraw.p_rec_rd.x = X_E;
	tdraw.p_rec_rd.y = Y1;
	tdraw.draw_color = GUI_BLUE;
	tdraw.buf = draw_buf;

	tscale.x_pix_size = LIM_SCALE_X_SIZE;
	tscale.y_pix_size = LIM_SCALE_Y_SIZE;

	tscale.disp_text_p0.x=100;
	tscale.disp_text_p0.y=465;
	
	tscale.disp_text_p1.x = 250;
	tscale.disp_text_p1.y = 465;
	
    tscale.unit_x = x_unit;
	tscale.unit_y = y_unit;
	
	tscale.y_data_max = pars.ve+0.5/pars.ve;
	tscale.x_data_max = SCALE_X_SIZE;
	
	dt = 0;
	
	
//	draw_open(&tdraw);
	
	limit_draw_init(pMsg);
	
	task_run();
#if 0
	while(1)
  {
	get_key = GUI_GetKey();
	if((get_key >= GUI_BUTTON_RUN)&&(get_key <= GUI_BUTTON_RES))
	{
	
	(*Pfun[get_key -1])();
	
	}

	GUI_Exec();
	refresh();
	#ifndef WIN_SIM
	GUI_TOUCH_Exec(); 
	OSTimeDlyHMSM(0,0,0,10);
	#endif
 }
//	draw_close(&tdraw);
#endif 
}

void release_source(void)
{
	int i;

	GUI_FillRect(0,0,280,280);
}


void hide_wig(void)
{
	int i;
	for(i=GUI_BUTTON_RUN;i<CHECK_BOX+1;i++)
	{
	WM_HideWindow(WM_GetDialogItem(h_main,i));
	}

}


void show_wig(void)
{
	int i,j,k;
	TSEPoint tsepoint;
   
	WM_Paint(WM_GetDesktopWindow());

	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();

	tsepoint.start_point.x = 10;
	tsepoint.start_point.y = 440;
	tsepoint.end_point.x = tsepoint.start_point.x + LIM_SCALE_X_SIZE;
	tsepoint.end_point.y = 440;
	draw_scale(tsepoint,0xffff,0);		// X

	tsepoint.start_point.x = 10;
	tsepoint.start_point.y = 21;
	tsepoint.end_point.x = 10;
	tsepoint.end_point.y = tsepoint.start_point.y + LIM_SCALE_Y_SIZE;
	draw_scale(tsepoint,0xffff,0);		// Y
	
	GUI_SetColor(GUI_BLUE);

	for(i=GUI_BUTTON_RUN;i<CHECK_BOX+1;i++)
	{
	WM_ShowWindow(WM_GetDialogItem(h_main,i));
	}

}

void task_run(void)
{
	int get_key;
	get_key = GUI_GetKey();
	if((get_key >= GUI_BUTTON_RUN)&&(get_key <= GUI_BUTTON_RES))
	{
	
	(*Pfun[get_key -1])();
	
	}

	//GUI_Exec();
	refresh();
	#ifndef WIN_SIM
	GUI_TOUCH_Exec(); 
	//OSTimeDlyHMSM(0,0,0,10);
	#endif
}




