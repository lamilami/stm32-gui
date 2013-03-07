/******************************************************************************

                  版权所有 (C), 2012-2022, 浙大精益

 ******************************************************************************
  文 件 名   : gui_app.c
  版 本 号   : 初稿
  作    者   : ganjinming
  生成日期   : 2012年9月11日
  最近修改   :
  功能描述   : gui_app的全局变量定义申明
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月11日
    作    者   : ganjinming
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "SimSwitch.h"

#include "gui_app.h"
#include "mot.h"
#include "rtc.h"

#ifndef WIN_SIM
#include "ff.h"	


#include "sdcard.h"
#include "diskio.h"
#endif
#include "Parameter.h"
#include "LimitSpeedH.h"


/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/
// static  void time_init(void);
/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/
#ifndef WIN_SIM
    FATFS fs;
	FIL fsrc;
#endif
    int  display_time_flag;
	int  update_minute = 0;
	WM_HWIN current_handle;
	int  current_interface;
	 
	S_GetData get_data;
    TPars   pars;
	TRecord record;

	TKeyBoard_H keyboard_h;
	tim Tim;

	TCustormer custormer;
//	TSparameter s_pars;

	TGetRecord tget_record;

	WM_HWIN h_home;
	WM_HWIN h_cus;
	WM_HWIN h_pars;
	WM_HWIN h_main;

	char flag_main_win;

	TScale tscale;

	int flag_paint; // H T B公用

	TDraw tdraw;

	char disp_mult;	 // H T 公用
	int xyz_paint_flag;	

	char hlimit_speed_tlimit_speed;

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/

// attention id must continus 

void UseKeyBoard(WM_MESSAGE * pMsg,int id_lenth,int id_base,int id,EWorkState front_state)
{
	float mid;
	if(!keyboard_h.use_now)
	{
	keyboard_h.use_now = 1;
	keyboard_h.work_state = front_state;
		
	WidgetLock(pMsg->hWin,LOCK,id_lenth,id_base,id);
	KeyBoard_Win(&keyboard_h);
	WidgetLock(pMsg->hWin,UNLOCK,id_lenth,id_base,id);
	
	if(front_state == CHINESE){
	EDIT_SetFont(WM_GetDialogItem(pMsg->hWin, id), &GUI_FontHZ_SongTi_16);
		}
	else if((front_state == ENGLISH_S)||(front_state == ENGLISH_B)){
	EDIT_SetFont(WM_GetDialogItem(pMsg->hWin, id), &GUI_Font16_ASCII);
	}else if(front_state == SFLOAT){

	EDIT_SetFloatMode(WM_GetDialogItem(pMsg->hWin, id),0.0,-9000,9999,1,0);
	
	}
	if(front_state != SFLOAT)
	{
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, id), keyboard_h.res_ch_data_head);
	}else{
	
	EDIT_SetFloatValue(WM_GetDialogItem(pMsg->hWin, id),atof(keyboard_h.res_ch_data_head));
	}
	keyboard_h.use_now = 0;
	
	}
}


void WidgetLock(WM_HWIN hWin,ELock_Unlock lock_unlock,int id_lenth,int id_base,int not_lock_id)
{
	int i;
	if(lock_unlock == LOCK)
		{
	WM_DisableWindow(hWin);
	for(i=0;i<id_lenth;i++){
		WM_DisableWindow(WM_GetDialogItem(hWin,id_base+i+1));
		}
	WM_EnableWindow(WM_GetDialogItem(hWin,not_lock_id));

	}else{
	WM_EnableWindow(hWin);
	for(i=0;i<id_lenth;i++)
		{
	WM_EnableWindow(WM_GetDialogItem(hWin,id_base+i+1));
	}

	}
}


void file_init(void)
{
#ifndef WIN_SIM
	unsigned int i, bw;
		unsigned char res;
		char men;
		
		f_mount(0, &fs);								  //注册到文件系统0区	
		res = f_open(&fsrc, "speed_old.lt",FA_OPEN_ALWAYS|FA_WRITE |FA_READ) ;
		 
		if(res)
		{
			while(1);
		}

		f_close(&fsrc);
		f_mount(0, NULL);

		save_custormer();
		save_parameters();
		save_get_record();
#endif		

}

void file_clear(void)
{
/*
	unsigned int i, bw;
	unsigned char res;
	char men;
	
    f_mount(0, &fs);				                  //注册到文件系统0区	
	res = f_open(&fsrc, "speed.lt",FA_OPEN_ALWAYS|FA_WRITE |FA_READ) ;
	 
	if(res)
	{
		while(1);
	}
	
	if(fsrc.fsize >= HAND_TEST_FILE_MAX_SIZE)
	{	
		f_close(&fsrc);
		res = f_rename("speed_old.lt","speed_mid.lt");
		res = f_rename("speed.lt","speed_old.lt");
		res = f_rename("speed_mid.lt","speed.lt");
		
		res = f_open(&fsrc, "speed.lt",FA_CREATE_ALWAYS|FA_WRITE |FA_READ);
		if(res)
		{
		while(1);
		}
		f_close(&fsrc);
		
	}else{
		
   	f_close(&fsrc);
		}
	f_mount(0, NULL);
*/
}


void save_custormer(void)
{
#ifndef WIN_SIM
	unsigned int i, bw;
	unsigned char res;
	char men;
	
    f_mount(0, &fs);//注册到文件系统0区	
	
	res = f_open(&fsrc, "speed.lt",FA_OPEN_ALWAYS|FA_WRITE |FA_READ) ;
	 
	if(res)
	{
		while(1);
	}
	res = f_lseek(&fsrc, fsrc.fsize); 
	res = f_write(&fsrc,&custormer,sizeof(TCustormer),&bw);
   	f_close(&fsrc);
	f_mount(0, NULL);
#endif
}


void read_custormer(void)
{
#ifndef WIN_SIM
	unsigned int i, br;
	unsigned char res;
	unsigned int size;

    f_mount(0, &fs);				                  //注册到文件系统0区	
	res = f_open(&fsrc, "speed.lt",FA_OPEN_ALWAYS|FA_WRITE |FA_READ);
	if(res)
	{
		while(1);
	}

	res = f_lseek(&fsrc, fsrc.fsize - sizeof(TPars)-sizeof(TCustormer)- sizeof(TGetRecord));
	res = f_read(&fsrc,&custormer,sizeof(TCustormer),&br);
	
	f_close(&fsrc);
	f_mount(0, NULL);
#endif
}


void read_parameters(void)
{
#ifndef WIN_SIM
	unsigned int i, br;
	unsigned char res;
	unsigned int off_loc;
	
    f_mount(0, &fs);				                  //注册到文件系统0区	
	res = f_open(&fsrc, "speed.lt", FA_OPEN_ALWAYS|FA_WRITE |FA_READ) ;
	if(res)
	{
		while(1);
	}
	
	res = f_lseek(&fsrc, fsrc.fsize - sizeof(TPars) - sizeof(TGetRecord));// 从下往上找
	res = f_read(&fsrc,&pars,sizeof(TPars),&br);
	
	f_close(&fsrc);
	f_mount(0, NULL);
#endif
}



void save_parameters(void)
{
#ifndef WIN_SIM
	unsigned int i,bw;
	unsigned char res;

    f_mount(0, &fs);				                  //注册到文件系统0区	
	res = f_open(&fsrc, "speed.lt",FA_OPEN_ALWAYS|FA_WRITE |FA_READ) ;
	if(res)
	{
		while(1);
	}
	res = f_lseek(&fsrc, fsrc.fsize);
	
	res = f_write(&fsrc,&pars,sizeof(TPars),&bw);

   	f_close(&fsrc);
	f_mount(0, NULL);
#endif
}


void save_get_record(void)
{
#ifndef WIN_SIM
	unsigned int i, bw;
	unsigned char res;
	
	f_mount(0, &fs);								  //注册到文件系统0区	
	res = f_open(&fsrc, "speed.lt",FA_OPEN_ALWAYS| FA_WRITE |FA_READ) ;
	if(res)
	{
		while(1);
	}
	res = f_lseek(&fsrc, fsrc.fsize); 
	res = f_write(&fsrc,&tget_record,sizeof(TGetRecord),&bw);
	
	f_close(&fsrc);
	f_mount(0, NULL);
#endif
}

void gui_app_init(void)
{
	get_data.e_work_state = INIT;
	tget_record.act_record_lenth;
	
 // time_init();
}

// -- 最后增加 /0
void get_data_form_file( char* file_name, void* pstru, unsigned int off_set,unsigned int size)
{
#ifndef WIN_SIM
    FATFS fs;
	FIL fsrc;
	unsigned int i, bw;
	unsigned char res;
	
	f_mount(0, &fs);								  //注册到文件系统0区	
	res = f_open(&fsrc, file_name,FA_OPEN_ALWAYS| FA_WRITE |FA_READ) ;
	if(res)
	{
		while(1);
	}
	if(fsrc.fsize > 0)
	{
	res = f_lseek(&fsrc,fsrc.fsize - off_set);
	 
	res = f_read(&fsrc,pstru,size,&bw);
	}
	
	f_close(&fsrc);
	f_mount(0, NULL);
#endif
}

void save_data_to_file( char* file_name, void* psource, unsigned int size)
{

#ifndef WIN_SIM
	unsigned int i, bw;
	unsigned char res;

	FATFS fs;
	FIL fsrc;
	
	f_mount(0, &fs);								  //注册到文件系统0区	
	res = f_open(&fsrc, file_name,FA_OPEN_ALWAYS| FA_WRITE |FA_READ) ;
	if(res)
	{
		while(1);
	}
	res = f_lseek(&fsrc, fsrc.fsize); 
	res = f_write(&fsrc,psource,size,&bw);
	
	f_close(&fsrc);
	f_mount(0, NULL);
#endif

}





