/******************************************************************************

                  版权所有 (C), 2012-2022, 浙大精益

 ******************************************************************************
  文 件 名   : gui_app.h
  版 本 号   : 初稿
  作    者   : ganjinming
  生成日期   : 2012年9月10日
  最近修改   :
  功能描述   : gui_app.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月10日
    作    者   : ganjinming
    修改内容   : 创建文件

******************************************************************************/
#ifndef __GUI_APP_H__
#define __GUI_APP_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "SimSwitch.h"
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
#include "graph.h"
#include "keyboard_win.h"
#include "TimeSet.h"
#include "gui_app.h"
#include "rtc.h"
#include "TouchCalibration.h"
#include "home.h"
#include "Custormer.h"
#include "Parameter.h"
#include "TParameter.h"
#include "LimitspeedH.h"
#include <stdlib.h>
#include <string.h>
#include "Draw.h"
#include "XYZ.h"
#include "LimitSpeedT.h"
#include "AD54XX.h"
#include "BalancePars.h"



#include"rdprint.h"

#include"CTPM.h"

#ifndef WIN_SIM
#include "sd_spi_driver.h"
#include "ff.h"
#endif

#define DISP_XY_X_LENTH 1000

#define TEST_TIMES  40

#define MAX_RECORD_NO    4
#define SIZE_OF_SIG_RECORD (sizeof(TPars)+sizeof(TGetRecord)+sizeof(TCustormer))
#define HAND_TEST_FILE_MAX_SIZE (SIZE_OF_SIG_RECORD*MAX_RECORD_NO)


/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/
 #ifndef WIN_SIM

    extern FATFS fs;
	extern FIL fsrc;
#endif

 extern int  display_time_flag;
 extern int update_minute ;
 extern WM_HWIN current_handle;
 extern int  current_interface;
 
 extern  TKeyBoard_H keyboard_h;
 extern  tim Tim;
 extern  TCustormer custormer;

// extern TSparameter s_pars;

 extern 	WM_HWIN h_home;
 extern 	WM_HWIN h_cus;
 extern  	WM_HWIN h_pars;
 extern     WM_HWIN h_main;
 extern const GUI_FONT GUI_FontHZ_SongTi_16;
 extern TScale tscale;
 extern int flag_paint;
 extern TDraw tdraw;
 extern char disp_mult;

 extern int xyz_paint_flag;

 extern char hlimit_speed_tlimit_speed;

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/
    extern void home(WM_MESSAGE *pMsg);
    extern void customer(WM_MESSAGE *pMsg);
	extern void parameter(WM_MESSAGE * pMsg);
    extern void ExecCalibration(WM_MESSAGE *pMsg);
    extern void time_set(WM_MESSAGE *pMsg) ;
    extern void my_messagebox(void) ;
	extern void gui_app_init(void);
	extern void limit_speed(WM_MESSAGE *pMsg);
	extern char* state_str;

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/
 typedef enum Lock_Unlock
{
    UNLOCK = 0,
    LOCK = 1

}ELock_Unlock;

static char* state_string[]={
	"Start",
	"GetV1",
	"OneStop",//
	"CurL_H",
	"CurL_L",//CL
	"SL", 	 //SpeedL
	"AF",    //AllOff
	"HF",	 //HandOff
	"Init",
	"Swich_err",
	"T_Mot_Cal"
	};


typedef enum {
	
	START_TEST = 1,
	GET_V1  = 2,
	ONE_STOP = 3,
	CURRENT_LIMIT_H = 4,
	CURRENT_LIMIT_L = 5,
	SPEED_LIMIT = 6,
	ALL_TEST_STOP = 7,
	HAND_OFF = 8,
	INIT = 9,
	SWI_ERR = 10,

}EMotWorkState;




 typedef struct{
 	
	float ve;
	float R_mm;

    float pwm_acc;	

	float start_speed;
	float v1;
	float v2;

	float ak1;
	float ak2;
	float ak3;

	float limit_current_h ;
	
	float psh;
	float psl;
	float limit_current_l ;
	float limit_speed;
	
	char dir;
	
	char switch_No;
	
 }TPars;



 typedef struct {

	  unsigned char test_times;
	  unsigned char time_second; //??
	  EMotWorkState e_work_state[TEST_TIMES];
	  
	  float v1[TEST_TIMES];
	  float v2[TEST_TIMES];

	  char result[TEST_TIMES];
	  char dir[TEST_TIMES];

}TRecord;


extern  TPars   pars;
extern  TGetRecord tget_record;
extern  tim Tim;

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/

#define HOME                      1
#define PORTABLE_CUSTOMER        100  //(1-0-0)
#define PORTABLE_PARAMETER            101
#define PORTABLE_LIMIT_SPEED          102
#define PORTABLE_LIMIT_TPARS		  103

#define XYZ_ACC_HOME             104 //
#define XYZ_ACC_PARAMETER        105

#define PORTABLE_LIMIT_SPEED_T   106
#define BALANCE_PAR				 107
#define BALANCE					 108



#define FILE_HEAD_SIZE sizeof(file_head);

void WidgetLock(WM_HWIN hWin,ELock_Unlock lock_unlock,int id_lenth,int id_base,int not_lock_id);

void save_custormer(void);
void save_parameters(void);
void read_parameters(void);
void save_get_record(void);

void save_data_to_file( char* file_name, void* psource, unsigned int size);
void get_data_form_file( char* file_name, void* pstru, unsigned int off_set,unsigned int size);

void file_clear(void);

void file_init(void);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __GUI_APP_H__ */




