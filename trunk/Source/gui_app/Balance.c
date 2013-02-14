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
#include "LimitSpeedT.h"
#include "BalancePars.h"



 GUI_ConstString _BListBox[] = {"1","",""};

 void OnButtonBStartClicked(WM_MESSAGE * pMsg)
 {
	 int lenth;
	 char buf[10];
	 
     if( tbalance_pars.test_mode == 0)// auto
	 {
	 _BListBox[1]="Auto";
	 }else 
	 {
	 _BListBox[1]="Self";
	 }

	  lenth = LISTVIEW_GetNumRows(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT_T));
      
	  tbalance_result.times++;

	  sprintf(buf,"%d",lenth+1);
	  _BListBox[0]= buf;
	  LISTVIEW_InsertRow(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT_T),0,_BListBox);
	  BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_TSTOP),"运行中");
	  
//	  balance_start_init();
	  
	  all_button(0,GUI_ID_BUTTON_TMAIN);
	  botton_able(1,GUI_ID_BUTTON_TSTOP);

 }

void  OnButtonBPrintClicked(WM_MESSAGE * pMsg)
{


}

 
 void OnButtonBSaveClicked(WM_MESSAGE * pMsg,ESaveState save_state)
 {
	int i,j,k;
	LISTVIEW_Handle hObj;
	char buf[10];
	hObj = WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT_T);
	
	for(i=0;i<LISTVIEW_GetNumRows(hObj);i++)
		{
		LISTVIEW_GetItemText(hObj,1,i,buf,7);
		tbalance_result.get_value[i] = atof(buf);
		}

	if(save_state == RemberToSd)
	{
		tbalance_result.ymdt.year = Tim.year;
		tbalance_result.ymdt.month = Tim.month;
		tbalance_result.ymdt.date = Tim.date;
		tbalance_result.ymdt.hour = Tim.hour;
		tbalance_result.ymdt.min = Tim.min;
	}

	file_clear();

	save_data_to_file( "balance.lt", (TBalancePars*)&tbalance_pars,sizeof(TBalancePars));
    save_data_to_file( "balance.lt", (TBalanceResult*)&tbalance_result,sizeof(TBalanceResult));

 }

 void OnButtonBParClicked(WM_MESSAGE * pMsg)
 {
	OnButtonTSaveClicked(pMsg,RemberToRam);
	balance_pars(pMsg);
 }

 void OnButtonBDelectClicked(WM_MESSAGE * pMsg)
 {
	char buf[3];
	char act_row;
	int row,row_number,i,j;

	row_number = LISTVIEW_GetNumRows(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT_T));
	
	row = LISTVIEW_GetSel(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT_T));
	
	LISTVIEW_DeleteRow(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW_RESULT_T),row);
	
	for(i=0;i<row_number-1;i++)
	 {
	    j = row_number-1-i;
	    sprintf(buf,"%d",j);
		LISTVIEW_SetItemText(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT_T),0,i,buf);
	 }
	
	tbalance_result.times--;

 }

 void OnButtonBRTClicked(WM_MESSAGE * pMsg)
 {
	 
	if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	{
	
    if(tbalance_pars.dir == 1)
	{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_TRT),"上升");
	tbalance_pars.dir = 2;
	}else {
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_TRT),"下降");	
	tbalance_pars.dir = 1;
	}
	motor_dir(tbalance_pars.dir);
	}
 }

 void OnButtonBStopClicked(WM_MESSAGE * pMsg)
 {
	 get_data.e_work_state = HAND_OFF;
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_TSTOP),"停止");
	motor_dir(0);

	all_button(1,GUI_ID_BUTTON_TMAIN);
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
{ FRAMEWIN_CreateIndirect,  "LIMIT_SPEED_H",     0,                       0,  0,  180,480,0,0},
    { BUTTON_CreateIndirect,    "保留1",              GUI_ID_BUTTON_TPLUS,     1,  52, 100,40, 0,0},
    { BUTTON_CreateIndirect,    "停止",                GUI_ID_BUTTON_TSTOP,     1,  190,100,40, 0,0},
    { BUTTON_CreateIndirect,    "上升/下降",             GUI_ID_BUTTON_TRT,       1,  144,100,40, 0,0},
    { BUTTON_CreateIndirect,    "删除",                GUI_ID_BUTTON_TDEL,      1,  282,100,40, 0,0},
    { BUTTON_CreateIndirect,    "参数设置",              GUI_ID_BUTTON_TPAR,      1,  236,100,40, 0,0},
    { BUTTON_CreateIndirect,    "保存",                GUI_ID_BUTTON_TSAVE,     1,  328,100,40, 0,0},
    { BUTTON_CreateIndirect,    "打印",                GUI_ID_BUTTON_TPRINT,    1,  374,100,40, 0,0},
    { BUTTON_CreateIndirect,    "保留2",              GUI_ID_BUTTON_TCYC,      1,  98, 100,40, 0,0},
    { BUTTON_CreateIndirect,    "主界面",               GUI_ID_BUTTON_TMAIN,     1,  420,100,40, 0,0},
    { LISTVIEW_CreateIndirect,   NULL,               GUI_ID_LISTVIEW_RESULT_T,        107,6,  68, 454,0,0},
    { BUTTON_CreateIndirect,    "升将开始",              GUI_ID_BUTTON_TCOMM,     1,  6,  100,40, 0,0}
};

/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog_B(WM_MESSAGE * pMsg)
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
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT_T),40,"M",GUI_TA_VCENTER|GUI_TA_LEFT);
	LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW_RESULT_T),5,"---",GUI_TA_VCENTER|GUI_TA_LEFT);

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
            InitDialog_B(pMsg);
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
                            OnButtonBStartClicked(pMsg);
                            break;
                    }
                    break;


                case GUI_ID_BUTTON_TPLUS:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                           
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TSTOP:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonBStopClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TRT:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonBRTClicked(pMsg);
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
                            OnButtonBParClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TSAVE:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonSaveClicked(pMsg,RemberToSd);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TPRINT:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonBPrintClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_TCYC:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            //OnButtonTCycClicked(pMsg);
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
void balance(WM_MESSAGE * pMsg)
{ 
    GUI_Init();

	if(pMsg)
	{
		WM_DeleteWindow(pMsg->hWin);
		flag_paint = 0;
	}

   
   WM_SetDesktopColor(GUI_BLACK);      /* Automacally update desktop window */
   WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */

   current_handle = GUI_CreateDialogBox(_aDialogCreate_LimT, GUI_COUNTOF(_aDialogCreate_LimT), &_cbCallback_LimT, 0, 0, 0);

   current_interface = BALANCE;
}

void get_result(void)
{
	int i,j,l;
	int srcRows, srcColumns;
	float r[10],d[10],k[10],see[50];
	float end[10];
	float* mmen;
	float* mmen_b;
	float* mmen_c;
	float* mmen_d;
	float* mmen_e;
	
	arm_matrix_instance_f32 A;      /* Matrix A Instance */ 
    arm_matrix_instance_f32 AT;     /* Matrix AT(A transpose) instance */
	arm_matrix_instance_f32 ATMA;   /* Matrix ATMA( AT multiply with A) instance */ 
	arm_matrix_instance_f32 ATMAI;  /* Matrix ATMAI(Inverse of ATMA) instance */ 
	arm_matrix_instance_f32 MID;      /* Matrix K instance */ 
	arm_matrix_instance_f32 Y;      /* Matrix Y instance */ 
	arm_matrix_instance_f32 END;      /* Matrix END instance */

	arm_status status; 
	srcColumns = 3;
	
	for(i=0;i<30;i++)
		tbalance_result.get_value[i] = i*5;

	for(i=0;i< tbalance_pars.test_times;i++)
	{
		r[i] = tbalance_result.get_value[i];
		i++;
		d[i] = tbalance_result.get_value[i]; 
	}	

	for(i=0;i< 6;i++)
	{

		r[i] = 5*i;
	
	}

	
	if(tbalance_pars.test_mode == AUTO)
	{
		for(i=0;i<6;i++)
		{
			k[i] = i*25;
		}
		if(tbalance_pars.test_times == 12)
		{
			k[i] = 110;
		}
		

	}else{
		
		k[0] = tbalance_pars.first_value;
		k[1] = tbalance_pars.second_value;

		if(!tbalance_pars.third_value)
		{
			tbalance_pars.test_times = 4;

		}else{

			k[2] = tbalance_pars.third_value;

			if(!tbalance_pars.forth_value )
			{
				tbalance_pars.test_times = 6;
			}else{

				k[3] = tbalance_pars.forth_value;

				if(!tbalance_pars.fifth_value)
				{
					tbalance_pars.test_times = 8;

				}else{
					k[4] = tbalance_pars.fifth_value;

					if(!tbalance_pars.sixth_value)
					{
						tbalance_pars.test_times = 10;
					}else{
						
						k[5] = tbalance_pars.sixth_value;
						if(!tbalance_pars.seventh_value)
						{
							tbalance_pars.test_times = 12;
							
						}else{
						
							k[6] = tbalance_pars.seventh_value;
							if(!tbalance_pars.eighth_value)
							{
								tbalance_pars.test_times = 14;

							}else{
								k[7] = tbalance_pars.eighth_value;
								tbalance_pars.test_times = 16;
							}
						}
					}
				}
			}	
		}
	}

	srcRows = tbalance_pars.test_times/2;

	mmen =(float *)malloc(sizeof(float)*srcRows*3);
	mmen_b = (float *)malloc(sizeof(float)*srcRows*3);
	mmen_c = (float *)malloc(sizeof(float)*srcRows*3);
	mmen_d = (float *)malloc(sizeof(float)*srcRows*3);
	mmen_e = (float *)malloc(sizeof(float)*srcRows*3);

	//0  0.25  0.50 0.75 1 1.1 
	//                     1.25 

	for(i=0;i< (tbalance_pars.test_times/2);i++)
	{
		mmen[i*3] = 1;
		mmen[(i+1)*3-2] = i*0.25;
		mmen[(i+1)*3-1] = (i*0.25)*(i*0.25);
	}

	arm_mat_init_f32(&A, srcRows, srcColumns, (float32_t *)mmen);
	arm_mat_init_f32(&AT, srcColumns, srcRows, (float32_t *)mmen_b);
	arm_mat_init_f32(&ATMA, srcColumns, srcColumns, (float32_t *)mmen_c);

	arm_mat_init_f32(&ATMAI, srcColumns, srcColumns, (float32_t *)mmen_d);
	arm_mat_init_f32(&MID, srcColumns, srcRows, (float32_t *)mmen_e);
	arm_mat_init_f32(&Y, srcRows, 1, r);
	arm_mat_init_f32(&END, srcColumns, 1, end);
	

	for(i=0;i<srcRows*3;i++)
	see[i] = mmen[i];
// (AT*A)(-1)*AT*Y

	/* calculation of A transpose */ 
    status = arm_mat_trans_f32(&A, &AT); //AT 

	for(i=0;i<srcRows*3;i++)
	see[i] = mmen_b[i];

	/* calculation of AT Multiply with A */ 
    status = arm_mat_mult_f32(&AT, &A, &ATMA); // AT*A

	for(i=0;i<srcRows*3;i++)
	see[i] = mmen_c[i];

	/* calculation of Inverse((Transpose(A) * A) */ 
    status = arm_mat_inverse_f32(&ATMA, &ATMAI);  // (AT*A)(-1)

	for(i=0;i<srcRows*3;i++)
		see[i] = mmen_d[i];

	/* calculation of AT Multiply with A */ 
    status = arm_mat_mult_f32(&ATMAI, &AT, &MID); //(AT*A)(-1)*(AT)

	for(i=0;i<srcRows*3;i++)
		see[i] = mmen_e[i];

	/* calculation of AT Multiply with A */ 
    status = arm_mat_mult_f32(&MID, &Y, &END);//(AT*A)(-1)*(AT)*Y
	
	for(i=0;i<srcRows*3;i++)
		see[i] = end[i];

}














