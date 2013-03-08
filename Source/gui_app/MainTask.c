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
#include "mot.h"
#include "LimitSpeedH.h"
#include "stdio.h"
#include <stdlib.h>
#include "Draw.h"
#include "XYZ.h"
#include "MMA8452Q.h"
#include "xyz_acc_para.h"
#include "ft5x06_ts.h"


extern      TPars   pars;
extern	    TRecord record;
extern      S_GetData get_data;
extern    	tim Tim;
extern 		TSpeed_buf tspeed_buf;

unsigned char reg_get;

float dta;

int buf_data_disp(int pick_rate)
{
	static float mid;
	int pick_size,i,j,loc;

	if(tspeed_buf.in_data_size >= pick_rate)
	{
		pick_size = tspeed_buf.in_data_size/pick_rate;

		for(i=0;i<pick_size;i++)
		{
		   loc = tspeed_buf.out_loc&(BUF_SIZE-1);
		   mid = tspeed_buf.speed_buf[loc];
		   for(j=0;j<pick_rate;j++)
		   {
			   if(mid < tspeed_buf.speed_buf[(tspeed_buf.out_loc+1)&(BUF_SIZE-1)])
			   {
			      mid = tspeed_buf.speed_buf[(tspeed_buf.out_loc+1)&(BUF_SIZE-1)];
			   }
			   tspeed_buf.out_loc++;
			   tspeed_buf.in_data_size--;
		   }
			value_to_graph_lim(mid);
		}

		return 1;
	}else {
	value_to_graph_lim(mid);
		return -1;
	}
}



void MainTask(void) 
{
	unsigned int speed_start;
    float ratex,ratey;
	WM_MESSAGE * pMsg;
	WM_MESSAGE  Msg;
    char* str_state;
	TSEPoint tsepoint;
    unsigned char sec,min,prec,i,k;
    unsigned int div;
	char buf_exp[30] = {'2','0','1','2','-','1','2','-','1','2','-','1','2','-','3','0',':','2','4'};
	char buf[50]="12-30";
	char buf_c[7];
	float j;

	unsigned int speed;
	float last_frequence,get_the_frequence;
    EMotWorkState mot_state;
	WM_HWIN  hGraph = 0;
	static int y,x;

	div = 0;

	disp_mult = 0;
	i = 0;

	mot_t_cal.cal_flag  = 0;



#ifndef WIN_SIM
    sd_init();
#endif

	GUI_Init();
//	GUI_CURSOR_Show();
	h_home= NULL;
	h_pars = NULL;
	h_cus =NULL;
	flag_paint =0;

// 
#if 0
  while(1)
  {
#ifndef WIN_SIM
	FT5x06_GetData(&x,&y);
	OSTimeDlyHMSM(0,0,0,100);
#endif
  }
#endif



//use dir data test EXP
#if 0
	{
#ifndef WIN_SIM
	print_data_time();
	OSTimeDlyHMSM(0,0,2,0);
#endif
	}
	while(1);
#endif


#if 0
 // LCD test 
 AD54XX_init();
 while(1)
 {
   set_data(20);
   OSTimeDlyHMSM(0,0,0,2);
   i++;
   if(i >= 21)
   i = 0;
 }
#endif 



#if 0
    while(1)
	{
	   GPIO_WriteBit(GPIOB, GPIO_Pin_7,1);
	   GPIO_WriteBit(GPIOB, GPIO_Pin_6,1);
	   OSTimeDlyHMSM(0,0,0,10);

	   GPIO_WriteBit(GPIOB, GPIO_Pin_7,0);
	   GPIO_WriteBit(GPIOB, GPIO_Pin_6,0);
  	   OSTimeDlyHMSM(0,0,0,10);
	}
#endif 

#if 0
	ratex = LCD_XSIZE/abs(GUI_TOUCH_AD_LEFT - GUI_TOUCH_AD_RIGHT);
	ratey = LCD_YSIZE/abs(GUI_TOUCH_AD_TOP - GUI_TOUCH_AD_BOTTOM)
	while(1)
	{
	GUI_DrawCircle(GUI_TOUCH_X_MeasureX()*ratex,GUI_TOUCH_X_MeasureY()*ratey,10);	
	}
#endif	
	
   // motor_int();
	
#ifndef WIN_SIM
//	run_cal();
//	_ExecCalibration();
//	GUI_TOUCH_SetDefaultCalibration();
#endif

   	read_custormer();
	read_parameters();
	get_data_form_file("speedt.lt", (TTPars*)&ttpars,sizeof(TGetRecord),sizeof(TTPars));
						   

    gui_app_init(); 
	motor_int();

	caculate_pars(&mot_t_cal);

#if 0
  	Draw(&Msg);
#endif

#if 0
	for(i=0;i<sizeof(ch);i++)
		*(custormer.custorm+i)= ch[i];

	pars.ak1=1.1;
	pars.ak2=1.2;
	pars.ak3=1.3;
	pars.dir=1;
	pars.limit_current_h=2.1;
	pars.limit_current_l=2.2;
	pars.limit_speed=2.3;
	pars.psh=2.4;
	file_init();
	
	save_custormer();

	pars.ak1=3.1;
	pars.ak2=3.2;
	pars.ak3=1.3;
	pars.dir=1;
	pars.limit_current_h=2.1;
	pars.limit_current_l=2.2;
	pars.limit_speed=2.3;
	pars.psh=2.4;

    file_clear();
	read_parameters();
	read_custormer();
	while(1);
#endif 



#if 0
    Tim.year = 2012;
	Tim.month = 10;
	Tim.date = 12;
	Tim.hour = 12;
	Tim.min = 35;
	Tim.sec = 12;
#ifndef WIN_SIM
	RTC_Set(Tim);
	while(1)
		{
	RTC_Get_Time(&Tim);

	OSTimeDlyHMSM(0,0,0,30);
	GUI_DispDecAt(Tim.min,80,100,4);
	GUI_DispCharAt('-',120,100);
	GUI_DispDecAt(Tim.sec,200,100,4);

	min = Tim.min;
	sec = Tim.sec;
		}
#endif
	
#endif

#if 0
	
	while(1)
	{
    for(j=0;j<12;j++)
	{
    for(i=0;i<20;i++)
    {

	motor_dir(1);
	motor_speed(320);
	GUI_GotoXY(i*40,j*40);

	
	get_the_frequence  =  get_data.frequence;

	{
	GUI_DispFloat(get_the_frequence,5);
	last_frequence = get_the_frequence; 

	}
	 //else
	{
	 
	 //i--;
	}

	GUI_DispDecAt(get_data.times,100,300, 5);

	//OSTimeDlyHMSM(0,0,0,100); 
	}
	}
	GUI_Clear();

	}
#endif

#if 0
	home(0);
	while(1)
	{
		GUI_Exec();
		task_run();
#ifndef WIN_SIM	
		OSTimeDlyHMSM(0,0,0,10);
#endif	
	}
#endif

#if 0

	home(0);

	while(1)
	{

#ifndef WIN_SIM
	    RTC_Get_Time(&Tim);
		RTC_time_to_string(buf ,Tim);
#endif
		GUI_DispStringAt(buf,680,12);

		GUI_Exec();

		get_data.current = 1.23;
		
		sprintf(buf_c,"%.2fA",get_data.current);
		//TEXT_SetText(WM_GetDialogItem(current_handle,GUI_ID_TEXT_CURRENT),buf_c);
		GUI_DispStringAt(buf_c,450,12);
		
		//TEXT_SetText(WM_GetDialogItem(current_handle,GUI_ID_TEXT_DATE_TIME),buf_exp);
		mot_state = get_data.e_work_state;

		if(current_interface == PORTABLE_LIMIT_SPEED)
		{
			if(flag_paint == 0)
			{
			draw_xy();
			flag_paint =1;
			}

		switch(mot_state)
		  {
		case START_TEST:
			//value_to_graph_lim(get_data.speed);
			buf_data_disp(1);
			sprintf(buf_c,"%.3f",get_data.speed);
			LISTVIEW_SetItemText(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT),1,0,buf_c);
			break;
			
		case GET_V1:
			buf_data_disp(1);
			sprintf(buf_c,"%.3f",get_data.speed);
			LISTVIEW_SetItemText(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT),2,0,buf_c);
			break;
			
		case ONE_STOP:
			sprintf(buf_c,"%.3f",get_data.speed);
			LISTVIEW_SetItemText(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT),2,0,buf_c);

			if(record.result[record.test_times])
			LISTVIEW_SetItemText(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT),4,0,"P");
			else
			LISTVIEW_SetItemText(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT),4,0,"N");		
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
		LISTVIEW_SetItemText(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT),3,0,state_string[mot_state -1]);
		}

		if(current_interface == XYZ_ACC_HOME)
		{
			if(xyz_paint_flag == 0)
			{
			GUI_SetColor(GUI_YELLOW);
			draw_scale_y(SCALE_X_START,SCALE_Y_START,SCALE_Y_END);
			GUI_SetColor(GUI_WHITE);
			xyz_paint_flag =1;
			disp_titles();
			disp_mode();
			draw_cm_s2(4900,900);
			}
		  if(sample_status == START)
		  {
#ifdef WIN_SIM			
			Data_Sim(512);
#endif
			save_xyz();

			if(xyz_pars.e_filter != FILTER_NO)
			{
			xyz_fir();
			xyz_value_fir_to_graph();
			}
			else
			{
			xyz_value_dir_to_graph(&Z_acc,GUI_GREEN,Z);
			}
			xyz_value_dir_to_graph(&X_acc,GUI_BLUE,X);
			xyz_value_dir_to_graph(&Y_acc,GUI_RED,Y);
			disp_caculate();
		  }
		}
		
		
		if(current_interface == PORTABLE_LIMIT_SPEED_T)
		{
			if(flag_paint == 0)
			{
			draw_xy_t();
	
			flag_paint =1;
			}
			
			if(etest_mode == TEST_MODE_COM)
			{
			
			switch(mot_state)
				{
			case START_TEST:
			//get_data.speed = rand()%200;
			/*
				for( j =0;j< 456;j++)
				{
					tspeed_buf.speed_buf[(tspeed_buf.in_loc)&(BUF_SIZE-1)]= j;
					tspeed_buf.in_loc++;
					tspeed_buf.in_data_size++;
				}
			*/
#if 0
				for(;tspeed_buf.in_data_size > 0;tspeed_buf.in_data_size--)
				{
					value_to_graph_lim(tspeed_buf.speed_buf[(tspeed_buf.out_loc)&(BUF_SIZE-1)]);
					tspeed_buf.out_loc++;
				}
#endif

			buf_data_disp(1);
			sprintf(buf_c,"%.3f",get_data.speed);
			LISTVIEW_SetItemText(WM_GetDialogItem(current_handle,GUI_ID_LISTVIEW_RESULT_T),3,0,buf_c);
			
			break;

			default:
			break;

				}
			}
		}

		if(current_interface == BALANCE)
		{
			if(flag_paint == 0)
			{
			draw_xy_t();
			flag_paint =1;
			}

		    //get_result();
		}

#ifndef WIN_SIM	
		OSTimeDlyHMSM(0,0,0,5); 
#endif	
	} 
#endif

}
