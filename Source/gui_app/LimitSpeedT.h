#ifndef LIMIT_SPEED_T_H
#define LIMIT_SPEED_T_H


/*********************************************************************
*
*       static data
*
**********************************************************************
*/
#define GUI_ID_BUTTON_TCOMM   GUI_ID_USER+1
#define GUI_ID_BUTTON_TPLUS   GUI_ID_USER+2
#define GUI_ID_BUTTON_TSTOP   GUI_ID_USER+3
#define GUI_ID_BUTTON_TRT   GUI_ID_USER+4
#define GUI_ID_BUTTON_TDEL   GUI_ID_USER+5
#define GUI_ID_BUTTON_TPAR   GUI_ID_USER+6
#define GUI_ID_BUTTON_TSAVE   GUI_ID_USER+7
#define GUI_ID_BUTTON_TPRINT   GUI_ID_USER+8
#define GUI_ID_BUTTON_TCYC   GUI_ID_USER+9
#define GUI_ID_BUTTON_TMAIN   GUI_ID_USER+10
#define GUI_ID_LISTVIEW_RESULT_T GUI_ID_USER+11

#define LIM_SCALE_X_SIZE_T (800 - 400)
#define LIM_SCALE_Y_SIZE_T (413)        // ---- tsepoint.start_point.y = 435; 
										// 413+21 -1 
#define SCALE_X_SIZE_ACT_T 600

#define Y0_T    21						// 液晶的物理坐标
#define X0_T    200+190

#define X1_T    X0_T
#define Y1_T    Y0_T+LIM_SCALE_Y_SIZE_T						//显示的 液晶坐标

#define X_E_T   X0_T+LIM_SCALE_X_SIZE_T

typedef enum{
  
	TEST_MODE_COM = 1,
	TEST_MODE_T = 2,
	TEST_MODE_SIN =3

}ETestMode;

extern ETestMode etest_mode;

void draw_init_t(void);
void draw_xy_t(void);
void botton_able(char able,int number);
void all_button(char able,int max);

#endif