#ifndef LIMIT_SPEED_H_H
#define LIMIT_SPEED_H_H

#include"gui_app.h"


#define GUI_ID_BUTTON_PARM_SET   GUI_ID_USER+1
#define GUI_ID_BUTTON_PRINT   GUI_ID_USER+2
#define GUI_ID_BUTTON_SAVE   GUI_ID_USER+3
#define GUI_ID_BUTTON_HOME   GUI_ID_USER+4
#define GUI_ID_BUTTON_CR   GUI_ID_USER+5
#define GUI_ID_BUTTON_STOP   GUI_ID_USER+6
#define GUI_ID_LISTVIEW_RESULT   GUI_ID_USER+7
static const char * _lvTable_100[1] ={"" };
#define GUI_ID_BUTTON_START   GUI_ID_USER+8

#define GUI_ID_BUTTON_DATA   GUI_ID_USER+9
#define GUI_ID_BUTTON_DELET   GUI_ID_USER+10



#define GUI_ID_TEXT_DATE_TIME GUI_ID_USER+11
#define GUI_ID_TEXT_CURRENT      GUI_ID_USER+12

#define GUI_ID_TEXT_CUR_A      GUI_ID_USER+13

#define GUI_ID_LISTVIEW_RESULT_OP GUI_ID_USER+14
#define	GUI_ID_PIC_DISP			GUI_ID_USER+15

#define COLUMN_LENTH			7


#define LIM_SCALE_X_SIZE 380
#define LIM_SCALE_Y_SIZE 413 //

#define SCALE_X_SIZE_ACT     600   // 要表示的数据 长度

#define Y0    21						// 液晶的物理坐标
#define X0    405

#define Y1    LIM_SCALE_Y_SIZE+Y0		//显示的 液晶坐标
#define X1    X0

#define X_E   LIM_SCALE_X_SIZE+X0

#define X_MIRRO(x)  X1+x			
#define Y_MIRRO(y)  (LIM_SCALE_Y_SIZE+Y0-y) //显示坐标
#define Y_RATE(Ve)	(LIM_SCALE_Y_SIZE )/(Ve*(1+0.5/Ve)) //比例


typedef struct{

	char order[3];
	char V1[8];
	char V2[8];
	char result_r_e[5];
	char state[8];
    char time[6];
	char dir[2];

}TSigRecord;



typedef enum{

	RemberToRam = 0,
		RemberToSd = 1

}ESaveState;

typedef struct{

 unsigned short year;
 unsigned char month;
 unsigned char date;
 unsigned char act_record_lenth;
 TSigRecord sig_record[20];

}TGetRecord;

extern  GUI_COLOR _aColor[];

void LimitSpeedH(WM_MESSAGE * pMsg);
void add_value_graph(int loc , signed short data);

void err_back(EWorkState work_state);

void Set_color_row(unsigned int color);

void Set_Color_cell(unsigned Column, unsigned Row,GUI_COLOR Color);

void draw_xy(void);
void draw_init(void);
void value_to_graph_lim(float value);
void list_view_color(unsigned Column, unsigned Row,GUI_COLOR Color);
void print_head(void);


#endif
