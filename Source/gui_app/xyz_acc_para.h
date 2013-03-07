#include"arm_math.h"

#ifndef _XYZ_ACC_PARA_H
#define _XYZ_ACC_PARA_H


#define GUI_ID_EDIT_CUS   GUI_ID_USER+1

#define GUI_ID_EDIT_PRO   GUI_ID_USER+2
#define GUI_ID_EDIT_RES1   GUI_ID_USER+3


#define GUI_ID_EDIT_START_R   GUI_ID_USER+4
#define GUI_ID_EDIT_STOP_R   GUI_ID_USER+5

#define GUI_ID_EDIT_ELE_ID   GUI_ID_USER+6
#define GUI_ID_SAMPLE_TIME_EDIT   GUI_ID_USER+7

#define GUI_ID_CHECKBOX_AUTO   GUI_ID_USER+8
#define GUI_ID_RADIO_FILTER   GUI_ID_USER+9


#define GUI_ID_RETURN_BUTTON      GUI_ID_USER+10

#define GUI_ID_TEXT1    GUI_ID_USER+11
#define GUI_ID_TEXT2    GUI_ID_USER+12
#define GUI_ID_TEXT3    GUI_ID_USER+13
#define GUI_ID_TEXT4    GUI_ID_USER+14
#define GUI_ID_TEXT5    GUI_ID_USER+15
#define GUI_ID_TEXT6    GUI_ID_USER+16
#define GUI_ID_TEXT7    GUI_ID_USER+17
#define GUI_ID_TEXT8    GUI_ID_USER+18
#define GUI_ID_TEXT9    GUI_ID_USER+19
#define GUI_ID_TEXT10    GUI_ID_USER+20
#define GUI_ID_TEXT11   GUI_ID_USER+21


#define GUI_ID_TEXT12   GUI_ID_USER+22 
#define GUI_ID_TEXT13   GUI_ID_USER+23
#define GUI_ID_TEXT14   GUI_ID_USER+24


typedef enum
{
 FILTER_NO,
 FILTER_20HZ,
 FILTER_30HZ,
 FILTER_50HZ,
 FILTER_100HZ,
 FILTER_200HZ
}EFilter;

typedef struct
{
  	char custorm[30];
	char series_no[15];
	char elevator_productor[20];
	char res1[20];
	char res2[20];
}TXYZ_Cus;

typedef struct
{
	EFilter e_filter;   //select 
	int record_s ;
	int auto_sel;       // auto or not
	float auto_start_za;// 如果 auto 选择 z轴多大加速度 auto 开始
	float auto_stop_za; // 如果 auto 选择 z轴多大加速度 auto 结束
	int res1;		    // 保留
	int res2;
}TXYZ_Pars;


extern TXYZ_Pars xyz_pars;

extern TXYZ_Cus  xyz_cus;


extern arm_fir_instance_q15 FIR_S;

extern unsigned int loc_A;

extern unsigned int loc_B;

void xyz_pars_save(void);

#endif