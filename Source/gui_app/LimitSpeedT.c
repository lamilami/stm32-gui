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
#include "LimitDraw.h"


 int draw_buf_lim_t[LIM_SCALE_X_SIZE_T];

 GUI_ConstString _ListBox[] = {"1","","","", "","R",""};

 ETestMode etest_mode;//

 //
 // en_able : enable or disable 
 //
 void botton_able(char able,int number)
 {
	 if(able)
	 {
	WM_EnableWindow(WM_GetDialogItem(current_handle,number));
	 }
	 else
	 {
	WM_DisableWindow(WM_GetDialogItem(current_handle,number));
	 }
 }

void all_button(char able,int max)
 {
	int i;
	for(i= GUI_ID_USER+1 ;i<max+1;i++)
	{
		if(able)
			WM_EnableWindow(WM_GetDialogItem(current_handle,i));
		else
			WM_DisableWindow(WM_GetDialogItem(current_handle,i));
	}
 }

 
 void TestCom(WM_MESSAGE * pMsg,ETestMode etest_mode_in)
 {
	 int lenth;
	 char buf[10];
	 etest_mode = etest_mode_in;

     if(etest_mode == TEST_MODE_COM)
	 {
	 _ListBox[1]="C";
	 }else if(etest_mode == TEST_MODE_T)
	 {
	 _ListBox[1]="T";
	 }else{
	 _ListBox[1]="S";
	 }

	  if(ttpars.dir == 2)
	  {
	  _ListBox[2] = "D";
	   }else{
	  _ListBox[2] = "R";
	   }
	  

	 if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	 {
	  lenth = LISTVIEW_GetNumRows(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT_T));
	  if(lenth < TEST_TIMES)
	  {
		record.test_times++;
	  
		sprintf(buf,"%d",lenth+1);

		_ListBox[0]= buf;
		LISTVIEW_InsertRow(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT_T),0,_ListBox);

		if(ttpars.dir !=2)
		{
		BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_TRT),"正转中");
		ttpars.dir = 1;
		}else {
		BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_TRT),"反转中");	
		}
		motor_dir(ttpars.dir);

		BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_TSTOP),"运行中");
		start_test_init();

		if(!disp_mult)
		{
		draw_clear(&tdraw);
		}
		tdraw.draw_color = _aColor[record.test_times%5];
		tdraw.data_size = 0;
	  }
	  all_button(0,GUI_ID_BUTTON_TMAIN);
	  botton_able(1,GUI_ID_BUTTON_TSTOP);
	}
 }



 void OnButtonCommClicked(WM_MESSAGE * pMsg)
 {
	  TestCom(pMsg,TEST_MODE_COM);
 }

  void OnButtonPlusClicked(WM_MESSAGE * pMsg)
 {
	 TestCom(pMsg,TEST_MODE_T);
 }

 void OnButtonTCycClicked(WM_MESSAGE * pMsg)
 {
	 TestCom(pMsg,TEST_MODE_SIN);
 }

 void OnButtonTPrintClicked(WM_MESSAGE * pMsg)
 {
	mot_t_get_speed_line(&mot_t_cal);
 }

 void OnButtonTSaveClicked(WM_MESSAGE * pMsg,ESaveState save_state)
 {
	int i,j,k;
	LISTVIEW_Handle hObj;
	char buf[10];
	hObj = WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT_T);
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

	save_data_to_file( "speedt.lt", (TCustormer*)&custormer,sizeof(TCustormer));
    save_data_to_file( "speedt.lt", (TTPars*)&ttpars,sizeof(TTPars));
	save_data_to_file( "speedt.lt", (TGetRecord*)&tget_record,sizeof(TGetRecord));
	}
 }

 void OnButtonParClicked(WM_MESSAGE * pMsg)
 {
	OnButtonTSaveClicked(pMsg,RemberToRam);
	tparameter(pMsg);
 }

 void OnButtonDelectClicked(WM_MESSAGE * pMsg)
 {
	char buf[3];
	char act_row;
	int row,row_number,i,j;
	if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	{
	row_number = LISTVIEW_GetNumRows(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT_T));
	
	row = LISTVIEW_GetSel(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT_T));
	
	LISTVIEW_DeleteRow(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT_T),row);
	
	for(i=0;i<row_number-1;i++)
	 {
	    j = row_number-1-i;
	    sprintf(buf,"%d",j);
		LISTVIEW_SetItemText(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT_T),0,i,buf);
	 }
	
	record.test_times--;

	act_row = row_number - row - 1;
	
	record.v1[act_row] = 0;
	record.v2[act_row] = 0;
	 }

 }

 void OnButtonRTClicked(WM_MESSAGE * pMsg)
 {
	motor_speed(0);
	if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	{
	
    if(ttpars.dir == 1)
	{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_TRT),"反转");
	ttpars.dir = 2;
	}else {
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_TRT),"正转");	
	ttpars.dir = 1;
	}
	motor_dir(ttpars.dir);
	}
 }

 void OnButtonTStopClicked(WM_MESSAGE * pMsg)
 {
	 get_data.e_work_state = HAND_OFF;
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_TSTOP),"停止");
	motor_dir(0);

	all_button(1,GUI_ID_BUTTON_TMAIN);
 }

//EventsFunctionList
void OnButtonMainClicked(WM_MESSAGE * pMsg)
{
 	home(pMsg);
}



//EndofEventsFunctionList

/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_LimT[] = {
{ FRAMEWIN_CreateIndirect,  "LIMIT_SPEED_H",     0,                       0,  0,  380,480,0,0},
    { BUTTON_CreateIndirect,    "跳变测试",              GUI_ID_BUTTON_TPLUS,     1,  52, 100,40, 0,0},
    { BUTTON_CreateIndirect,    "停止",                GUI_ID_BUTTON_TSTOP,     1,  190,100,40, 0,0},
    { BUTTON_CreateIndirect,    "正转/反转",             GUI_ID_BUTTON_TRT,       1,  144,100,40, 0,0},
    { BUTTON_CreateIndirect,    "删除",                GUI_ID_BUTTON_TDEL,      1,  282,100,40, 0,0},
    { BUTTON_CreateIndirect,    "参数设置",              GUI_ID_BUTTON_TPAR,      1,  236,100,40, 0,0},
    { BUTTON_CreateIndirect,    "保存",                GUI_ID_BUTTON_TSAVE,     1,  328,100,40, 0,0},
    { BUTTON_CreateIndirect,    "参数提取",                GUI_ID_BUTTON_TPRINT,    1,  374,100,40, 0,0},
    { BUTTON_CreateIndirect,    "周期测试",              GUI_ID_BUTTON_TCYC,      1,  98, 100,40, 0,0},
    { BUTTON_CreateIndirect,    "主界面",               GUI_ID_BUTTON_TMAIN,     1,  420,100,40, 0,0},
    { LISTVIEW_CreateIndirect,   NULL,               GUI_ID_LISTVIEW_RESULT_T,        107,6,268, 454,0,0},
    { BUTTON_CreateIndirect,    "常规测试",              GUI_ID_BUTTON_TCOMM,     1,  6,  100,40, 0,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog_LimT(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog_LimT(WM_MESSAGE * pMsg)
{
	int i;
    WM_HWIN hWin = pMsg->hWin;

    //
    //FRAMEWIN
    //
    FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
    FRAMEWIN_AddMaxButton(hWin, FRAMEWIN_BUTTON_RIGHT, 1);
    FRAMEWIN_AddMinButton(hWin, FRAMEWIN_BUTTON_RIGHT, 2);

	for(i=GUI_ID_BUTTON_TCOMM;i<GUI_ID_BUTTON_TMAIN+1;i++)
	{

	BUTTON_SetFont(WM_GetDialogItem(hWin,i),&GUI_FontHZ_SongTi_16);
	
	}

	LISTVIEW_SetAutoScrollV(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT_T),1);

    LISTVIEW_SetFont(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT_T),&GUI_FontHZ_SongTi_16);
	
	LISTVIEW_SetRowHeight(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT_T),20);

	// 60 
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT_T),20,"O",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT_T),20,"M",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT_T),50,"D",GUI_TA_VCENTER|GUI_TA_LEFT);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT_T),50,"V1",GUI_TA_VCENTER|GUI_TA_LEFT);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT_T),50,"V2",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT_T),50,"Res",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT_T),2,"---",GUI_TA_VCENTER|GUI_TA_LEFT);
	// LISTBOX_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),0,0xffffff);
}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback_LimT(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog_LimT(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog_LimT(pMsg);
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

				
                case GUI_ID_BUTTON_TCOMM:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonCommClicked(pMsg);
                            break;
                    }
                    break;


                case GUI_ID_BUTTON_TPLUS:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonPlusClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TSTOP:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonTStopClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TRT:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonRTClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TDEL:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonDelectClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TPAR:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonParClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TSAVE:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonTSaveClicked(pMsg,RemberToSd);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TPRINT:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonTPrintClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TCYC:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonTCycClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TMAIN:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonMainClicked(pMsg);
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
void LimitSpeedT(WM_MESSAGE * pMsg)
{ 

	current_interface = PORTABLE_LIMIT_SPEED_T;
	if(pMsg)
	{
		WM_DeleteWindow(pMsg->hWin);
		flag_paint = 0;
	}

   WM_SetDesktopColor(GUI_BLACK);      /* Automacally update desktop window */
   WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */

   current_handle = GUI_CreateDialogBox(_aDialogCreate_LimT, GUI_COUNTOF(_aDialogCreate_LimT), &_cbCallback_LimT, 0, 0, 0);

}


void draw_init_t()
{
	tdraw.buf_size = LIM_SCALE_X_SIZE_T;
	tdraw.data_size = 0;
	tdraw.disp_kind = 1;
	tdraw.p0.x = X1_T+200+10;// 防止坐标清除
	tdraw.p0.y = Y1_T;
	tdraw.p_rec_lu.x = X0_T;
	tdraw.p_rec_lu.y = Y0_T;
	tdraw.p_rec_rd.x = X_E_T;
	tdraw.p_rec_rd.y = Y1_T;
	tdraw.draw_color = GUI_BLUE;
	tdraw.buf = draw_buf_lim_t;
}


void draw_xy_t()
{
	TSEPoint tsepoint;
	char x_unit[]="X /DIV m/s:";
	char y_unit[]="Y /DIV ms :";

	tscale.x_pix_size = LIM_SCALE_X_SIZE_T;
	tscale.y_pix_size = LIM_SCALE_Y_SIZE_T;

	tscale.disp_text_p0.x=580;
	tscale.disp_text_p0.y=460;
	
	tscale.disp_text_p1.x = 700;
	tscale.disp_text_p1.y = 460;
	
    tscale.unit_x = x_unit;
	tscale.unit_y = y_unit;
	
	tscale.y_data_max = ttpars.Ve+0.5/ttpars.Ve;
	tscale.x_data_max = SCALE_X_SIZE_ACT_T;

	// start_point 对应实际的液晶坐标
	tsepoint.start_point.x = X0_T;
	tsepoint.start_point.y = 435;
	tsepoint.end_point.x = tsepoint.start_point.x + LIM_SCALE_X_SIZE_T;
	tsepoint.end_point.y = 435;
	draw_scale(tsepoint,0xffff,0);		//X

	tsepoint.start_point.x = X0_T;
	tsepoint.start_point.y = 435;
	tsepoint.end_point.x = X0_T;
	tsepoint.end_point.y = tsepoint.start_point.y - LIM_SCALE_Y_SIZE_T;
	draw_scale(tsepoint,0xffff,0);		//Y

	scale_set(&tscale);
	draw_init_t();
	
}







