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
#include "stdio.h"
#include "gui_app.h"
#include "Draw.h"
#include "XYZ.h"
#include "xyz_acc_para.h"
#include "MMA8452Q.h"
#include "arm_math.h"


//*1024 ！
q15_t fir_coeffs[5][8]={
	{20,66,170,250,250,170,66,20},// 20hz
	{19,65,170,258,258,170,65,19},//30hz
	{16,60,170,266,266,170,60,16},//50hz
	{4,39,165,304,304,165,39,4},  //100hz
	{-5,-23,99,442,442,99,-23,-5}//200hz
};

TimeBase  time_base;
XYZ_ACC_SAMPLE_STATUS    sample_status;
Dispaly_Acc_struct   tdisp_acc_struct;


TMMA845xFilterResult tfilter_result;

char in_fft;// 0 - in fft state, 1 - in comm state

q15_t FIR_State[FIR_BLOCK_SIZE+FIR_TAPS-1];
arm_fir_instance_q15 FIR_S;


arm_cfft_radix4_instance_q15  fft_S;

TXYZ_Result  txyz_restult;

T_XYZ_FILE_struct xyz_file;

static GUI_CONST_STORAGE GUI_COLOR Colors[] = {
     0xFFFFFF,0x0000AA
};

static GUI_CONST_STORAGE GUI_LOGPALETTE Pal = {
  2,	/* number of entries */
  1, 	/* Has transparency */
  &Colors[0]
};


//GUI_MEMDEV_Handle hMem;

static GUI_CONST_STORAGE unsigned char _arrow_right[] = {
  _____X__,________,
  _____XX_,________,
  _____XXX,________,
  _____XXX,X_______,
  _____XXX,XX______,
  XXXXXXXX,XXX_____,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXXXX__,
  XXXXXXXX,XXXXXXX_,
  XXXXXXXX,XXXXXXXX,
  XXXXXXXX,XXXXXXX_,
  XXXXXXXX,XXXXXX__,
  XXXXXXXX,XXXXX___,
  XXXXXXXX,XXXX____,
  XXXXXXXX,XXX_____,
  _____XXX,XX______,
  _____XXX,X_______,
  _____XXX,________,
  _____XX_,________,
  _____X__,________,
};

static GUI_CONST_STORAGE unsigned char _arrow_left[] = {
  ________,__X_____,
  ________,_XX_____,
  ________,XXX_____,
  _______X,XXX_____,
  ______XX,XXX_____,
  _____XXX,XXXXXXXX,
  ____XXXX,XXXXXXXX,
  ___XXXXX,XXXXXXXX,
  __XXXXXX,XXXXXXXX,
  _XXXXXXX,XXXXXXXX,
  XXXXXXXX,XXXXXXXX,
  _XXXXXXX,XXXXXXXX,
  __XXXXXX,XXXXXXXX,
  ___XXXXX,XXXXXXXX,
  ____XXXX,XXXXXXXX,
  _____XXX,XXXXXXXX,
  ______XX,XXX_____,
  _______X,XXX_____,
  ________,XXX_____,
  ________,_XX_____,
  ________,__X_____,
};

static GUI_CONST_STORAGE GUI_BITMAP arrow_right = {
  16, 
  21, 
  2, 
  1, 
  _arrow_right,  
  &Pal  
};

static GUI_CONST_STORAGE GUI_BITMAP arrow_left = {
  16, 
  21, 
  2, 
  1, 
  _arrow_left,  
  &Pal  
};

//EventsFunctionList
void OnButtonArrowRightClicked(WM_MESSAGE * pMsg);
void OnButtonArrowLeftClicked(WM_MESSAGE * pMsg);
void OnButtonSaveClicked(WM_MESSAGE * pMsg);
void OnButtonPrintClicked(WM_MESSAGE * pMsg);
void OnButtonRevivalClicked(WM_MESSAGE * pMsg);
void OnButtonDisplayABClicked(WM_MESSAGE * pMsg);
void OnButtonTickABClicked(WM_MESSAGE * pMsg);
void OnButtonZ_FFTClicked(WM_MESSAGE * pMsg);
void OnButtonAutoClicked(WM_MESSAGE * pMsg);
void OnButtonStopClicked(WM_MESSAGE * pMsg);
void OnButtonStartClicked(WM_MESSAGE * pMsg);
void OnButton_SetParaClicked(WM_MESSAGE * pMsg);
//EndofEventsFunctionList


/*********************************************************************
*
*       static data
*
**********************************************************************
*/

#define GUI_ID_PARS_BUTTON   GUI_ID_USER+1
#define GUI_ID_START_BUTTON   GUI_ID_USER+2
#define GUI_ID_STOP_BUTTON   GUI_ID_USER+3
#define GUI_ID_AUTO_BUTTON   GUI_ID_USER+4
#define GUI_ID_Z_FFT_BUTTON   GUI_ID_USER+5
#define GUI_ID_TICK_AB_BUTTON   GUI_ID_USER+6
#define GUI_ID_DISPALY_AB_BUTTON   GUI_ID_USER+8
#define GUI_ID_REVIVAL_BUTTON   GUI_ID_USER+9
#define GUI_ID_PRINT_BUTTON   GUI_ID_USER+10
#define GUI_ID_SAVE_BUTTON   GUI_ID_USER+11
#define GUI_ID_ARROW_LEFT_BUTTON   GUI_ID_USER+12
#define GUI_ID_ARROW_RIGHT_BUTTON   GUI_ID_USER+13


/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       714,  0,  86, 480,0,0},
    { BUTTON_CreateIndirect,    "参数设置",              GUI_ID_PARS_BUTTON,      1,  6,  80, 30, 0,0},
    { BUTTON_CreateIndirect,    "Start",             GUI_ID_START_BUTTON,     1,  46, 80, 30, 0,0},
    { BUTTON_CreateIndirect,    "Stop",              GUI_ID_STOP_BUTTON,      1,  86, 80, 30, 0,0},
    { BUTTON_CreateIndirect,    "Auto",              GUI_ID_AUTO_BUTTON,      1,  126,80, 30, 0,0},
    { BUTTON_CreateIndirect,    "Z_FFT",             GUI_ID_Z_FFT_BUTTON,     1,  166,80, 30, 0,0},
    { BUTTON_CreateIndirect,    "时基A/B",             GUI_ID_TICK_AB_BUTTON,   1,  211,80, 30, 0,0},
    { BUTTON_CreateIndirect,    "显示AB",              GUI_ID_DISPALY_AB_BUTTON,1,  321,80, 30, 0,0},
    { BUTTON_CreateIndirect,    "还原",                GUI_ID_REVIVAL_BUTTON,   1,  361,80, 30, 0,0},
    { BUTTON_CreateIndirect,    "Print",             GUI_ID_PRINT_BUTTON,     1,  401,80, 30, 0,0},
    { BUTTON_CreateIndirect,    "Save",              GUI_ID_SAVE_BUTTON,      1,  441,80, 30, 0,0},
    { BUTTON_CreateIndirect,     NULL,               GUI_ID_ARROW_LEFT_BUTTON,1,  262,34, 41, 0,0},
    { BUTTON_CreateIndirect,     NULL,               GUI_ID_ARROW_RIGHT_BUTTON,47, 262,34, 41, 0,0}
};

/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
}

/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetTitleVis(hWin,0);
    //
    //GUI_ID_PARS_BUTTON
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_PARS_BUTTON),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_START_BUTTON
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_START_BUTTON),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_STOP_BUTTON
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_STOP_BUTTON),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_AUTO_BUTTON
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_AUTO_BUTTON),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_Z_FFT_BUTTON
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_Z_FFT_BUTTON),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TICK_AB_BUTTON
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_TICK_AB_BUTTON),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_DISPALY_AB_BUTTON
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_DISPALY_AB_BUTTON),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_REVIVAL_BUTTON
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_REVIVAL_BUTTON),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_PRINT_BUTTON
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_PRINT_BUTTON),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_SAVE_BUTTON
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_SAVE_BUTTON),&GUI_FontHZ_SongTi_16);

    //BUTTON_SetBitmapEx(hButton, BUTTON_BI_PRESSED,   &_bmShrink, 12, 2);
	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_ARROW_LEFT_BUTTON),BUTTON_BI_PRESSED,&arrow_left,8,10);
	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_ARROW_LEFT_BUTTON),BUTTON_BI_UNPRESSED,&arrow_left,8,10);
	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_ARROW_RIGHT_BUTTON),BUTTON_BI_PRESSED,&arrow_right,10,10);
	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_ARROW_RIGHT_BUTTON),BUTTON_BI_UNPRESSED,&arrow_right,10,10);
}

/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog(pMsg);
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
                case GUI_ID_PARS_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButton_SetParaClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_START_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonStartClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_STOP_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonStopClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_AUTO_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonAutoClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_Z_FFT_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonZ_FFTClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_TICK_AB_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonTickABClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_DISPALY_AB_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonDisplayABClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_REVIVAL_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonRevivalClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_PRINT_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonPrintClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_SAVE_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonSaveClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_ARROW_LEFT_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonArrowLeftClicked(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_ARROW_RIGHT_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonArrowRightClicked(pMsg);
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
void xyz_acc_home(WM_MESSAGE *pMsg) 
{ 
	if(pMsg)
	{
		WM_DeleteWindow(pMsg->hWin);
	}
//  GUI_SetColor(GUI_BLACK);
	GUI_SetBkColor(GUI_BLACK);
	WM_SetDesktopColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_YELLOW);
	current_interface = XYZ_ACC_HOME;

//	draw_scale_y(SCALE_X_START,SCALE_Y_START,SCALE_Y_END);
//	GUI_SetColor(GUI_WHITE);

	Z_acc.acc_x_pose = SCALE_X_START;
	Z_acc.acc_y_pose = SCALE_Z_ACC_MIDDLE;

	X_acc.acc_x_pose = SCALE_X_START;
	X_acc.acc_y_pose = SCALE_X_ACC_MIDDLE;

	Y_acc.acc_x_pose = SCALE_X_START;
	Y_acc.acc_y_pose = SCALE_Y_ACC_MIDDLE;

	xyz_paint_flag = 0;
	Z_acc.got_acc_num = 0;
	Z_acc.used_acc_num = 0;
	tfilter_result.got_filter_acc_num = 0;
	tfilter_result.used_filter_acc_num = 0;
	xyz_sys_init();
	in_fft = 0;
	sample_status = STOP;

	Z_acc.acc_time = 1;
	X_acc.acc_time = 1;
	Y_acc.acc_time = 1;

#ifndef WIN_SIM
	MMA845X_TIM6_interrupt_conf(DISABLE);//除能采样中断
#endif

	time_base_inital();
    current_handle = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
}

/*******
回调函数
*/
void OnButton_SetParaClicked(WM_MESSAGE *pMsg)
{
	
	xyz_acc_parameter(pMsg);
	
}

void OnButtonStartClicked(WM_MESSAGE * pMsg)
{
	Z_acc.got_acc_num = 0;
	Z_acc.used_acc_num = 0;
	X_acc.got_acc_num = 0;
	X_acc.used_acc_num = 0;
	Y_acc.got_acc_num = 0;
	Y_acc.used_acc_num = 0;

	xyz_paint_flag = 0; 
	sample_status = START;

	xyz_head_save();
	xyz_pars_save();

	GUI_ClearRect(0,XYZ_SCALE_Y_START,XYZ_FFT_X_SIZE,YXZ_FFT_Y_SIZE);

#ifndef WIN_SIM
	  MMA845X_TIM6_interrupt_conf(ENABLE);//使能采样中断
#endif

}

void OnButtonStopClicked(WM_MESSAGE * pMsg)
{
	
	sample_status = STOP;
#ifndef WIN_SIM
	  MMA845X_TIM6_interrupt_conf(DISABLE);//除能采样中断
#endif
	xyz_file_save_end();
}

void OnButtonAutoClicked(WM_MESSAGE * pMsg)
{
	
}

void OnButtonZ_FFTClicked(WM_MESSAGE * pMsg)
{
	int i,fftLen,ifftFlag,bitReverseFlag;
	signed short fft_buf[FFT_LENTH*2];

	in_fft = 1;
	get_za_data(fft_buf,FFT_LENTH*2);
	fftLen = FFT_LENTH;
	ifftFlag = 0;
	bitReverseFlag = 1;
	
	arm_cfft_radix4_init_q15(&fft_S,fftLen,ifftFlag,bitReverseFlag);
	get_data_from_sd(fft_buf ,loc_A,loc_B, FFT_LENTH*2,ONE_AXLE);
	arm_cfft_radix4_q15(&fft_S, fft_buf);
	view_fft(fft_buf);

}

void OnButtonTickABClicked(WM_MESSAGE * pMsg)
{
	static int tick_ab = 2;
	WM_HWIN hWin = pMsg->hWin; 
	if(tick_ab == 1)
	{
		tick_ab = 0;
		BUTTON_SetText(WM_GetDialogItem(hWin,GUI_ID_TICK_AB_BUTTON),"时基B");
		time_base.choice_ab = CHOICE_B;
	}
	else 
	{
		tick_ab = 1;
		BUTTON_SetText(WM_GetDialogItem(hWin,GUI_ID_TICK_AB_BUTTON),"时基A");
		time_base.choice_ab = CHOICE_A;
	}
}

void OnButtonDisplayABClicked(WM_MESSAGE * pMsg)
{
	

}



void OnButtonRevivalClicked(WM_MESSAGE * pMsg)
{
	int i;
	if(in_fft == 0)
	{
		home(pMsg);
	}
	else{
		GUI_ClearRect(0,0,XYZ_FFT_X_SIZE,YXZ_FFT_Y_SIZE+80);
		BUTTON_SetText(WM_GetDialogItem(current_handle,GUI_ID_REVIVAL_BUTTON),"返回");
		for(i=GUI_ID_PARS_BUTTON;i<GUI_ID_ARROW_RIGHT_BUTTON+1;i++)
		{
		WM_EnableWindow(WM_GetDialogItem(current_handle,i));
		}
		in_fft = 0;
		time_base_inital();
		xyz_paint_flag = 0;
	}
}

void OnButtonPrintClicked(WM_MESSAGE * pMsg)
{
}

void OnButtonSaveClicked(WM_MESSAGE * pMsg)
{

 xyz_file_close();
}

void OnButtonArrowLeftClicked(WM_MESSAGE * pMsg)
{
#ifndef WIN_SIM
	if(time_base.choice_ab == CHOICE_A)
	{ 
		if(time_base.A_pos - TIME_BASE_STEP >= SCALE_X_START)	
		{
		
			GUI_SetVLine(time_base.A_pos, 0,470,&time_base.A_color_value[0]);
			time_base.A_pos -= TIME_BASE_STEP;
			GUI_GetVLine(time_base.A_pos, 0,470,&time_base.A_color_value[0]);
			GUI_DrawLine(time_base.A_pos,0,time_base.A_pos,470);
		}
	}
	else
	{
		if(time_base.B_pos - TIME_BASE_STEP > time_base.A_pos)	
		{
		
			GUI_SetVLine(time_base.B_pos, 0,470,&time_base.B_color_value[0]);
			time_base.B_pos -= TIME_BASE_STEP;
			GUI_GetVLine(time_base.B_pos, 0,470,&time_base.B_color_value[0]);
			GUI_DrawLine(time_base.B_pos,0,time_base.B_pos,470);
			
		}
	}
#endif
}

void OnButtonArrowRightClicked(WM_MESSAGE * pMsg)
{
#ifndef WIN_SIM
	if(time_base.choice_ab == CHOICE_A)
	{ 
		if(time_base.A_pos + TIME_BASE_STEP < time_base.B_pos)	
		{
			GUI_SetVLine(time_base.A_pos, 0,470,&time_base.A_color_value[0]);
			time_base.A_pos += TIME_BASE_STEP;
			GUI_GetVLine(time_base.A_pos, 0,470,&time_base.A_color_value[0]);
			GUI_DrawLine(time_base.A_pos,0,time_base.A_pos,470);
	
		}
	}
	else
	{
		if(time_base.B_pos + TIME_BASE_STEP <= SCALE_X_END)	
		{
			GUI_SetVLine(time_base.B_pos, 0,470,&time_base.B_color_value[0]);
			time_base.B_pos += TIME_BASE_STEP;
			GUI_GetVLine(time_base.B_pos, 0,470,&time_base.B_color_value[0]);
			GUI_DrawLine(time_base.B_pos,0,time_base.B_pos,470);
		
		}
	}
#endif
}



void draw_scale_y(int x0, int y0,int y1)
{
	int i,current_size,current_y = y0;
	TSEPoint tsepoint;

	GUI_SetFont(&GUI_Font6x8);
	GUI_DrawVLine(x0,y0,y1);
	for(i=0; i<3; i++)
	{   
		if(i == 0) 
		{
			current_size = SCALE_Z_SPEED_SIZE;
			GUI_DispStringAt("2g",x0-15,current_y-5);
			GUI_DispStringAt("x_m/s",SCALE_X_START+SCALE_X_SIZE + 10,current_y-5);

			GUI_DispStringAt("0g",x0-15,current_y +SCALE_Z_ACC_SIZE/2-2);
			GUI_DispStringAt("x_m/s",SCALE_X_START+SCALE_X_SIZE + 10,current_y +SCALE_Z_ACC_SIZE/2-2);

			GUI_DispStringAt("-2g",x0-20,current_y +SCALE_Z_ACC_SIZE-5);
			GUI_DispStringAt("x_m/s",SCALE_X_START+SCALE_X_SIZE + 10,current_y +SCALE_Z_ACC_SIZE-5);
			GUI_DispStringAt("Z_a_v",SCALE_X_START+SCALE_X_SIZE + 10,current_y +SCALE_Z_ACC_SIZE/2-2);
		}
		else if( i== 1)
		{
			current_size = SCALE_Z_ACC_SIZE;
			current_y    += SCALE_Z_SPEED_SIZE;
			GUI_DispStringAt("2g",x0-15,current_y+4);
			GUI_DispStringAt("0g",x0-15,current_y +SCALE_Z_ACC_SIZE/2-2);
			GUI_DispStringAt("XYa_m2/s",SCALE_X_START+SCALE_X_SIZE + 10,current_y +SCALE_Z_ACC_SIZE/2-2);
			GUI_DispStringAt("-2g",x0-20,current_y +SCALE_Z_ACC_SIZE-5);
		}
		else
		{
			/*
			current_size =SCALE_XY_ACC_SIZE;
			current_y    += SCALE_Z_ACC_SIZE;
			GUI_DispStringAt("2g",x0-15,current_y+4);
			GUI_DispStringAt("0g",x0-15,current_y +SCALE_XY_ACC_SIZE/2-2);
			GUI_DispStringAt("Ya_m2/s",SCALE_X_START+SCALE_X_SIZE + 10,current_y +SCALE_Z_ACC_SIZE/2-2);
			GUI_DispStringAt("-2g",x0-20,current_y +SCALE_XY_ACC_SIZE-4);
			*/
		}
		GUI_DrawHLine(current_y,x0,x0+SCALE_X_SIZE);
		GUI_DrawHLine(current_y+current_size/8,x0,x0+5);
		GUI_DrawHLine(current_y+2*(current_size/8),x0,x0+10);
		GUI_DrawHLine(current_y+3*(current_size/8),x0,x0+5);
		GUI_DrawHLine(current_y+4*(current_size/8),x0,x0+SCALE_X_SIZE);
		GUI_DrawHLine(current_y+5*(current_size/8),x0,x0+5);
		GUI_DrawHLine(current_y+6*(current_size/8),x0,x0+10);
		GUI_DrawHLine(current_y+7*(current_size/8),x0,x0+5);

	}
		tsepoint.start_point.x = x0;
		tsepoint.start_point.y = current_y+8*(current_size/8);
		tsepoint.end_point.x = tsepoint.start_point.x + SCALE_X_SIZE;//凑到0.5div/hz 每格 512
		tsepoint.end_point.y = current_y+8*(current_size/8);
		draw_scale(tsepoint,0xffff,0);		//X
}


void time_base_inital(void)
{
	time_base.A_pos = XYZ_SCALE_X_START+TIME_BASE_STEP;
	time_base.B_pos = XYZ_SCALE_X_END-TIME_BASE_STEP;
#ifndef WIN_SIM
	GUI_GetVLine(0, time_base.A_pos,XYZ_SCALE_Y_END,&time_base.A_color_value[0]);
	GUI_GetVLine(0, time_base.B_pos,XYZ_SCALE_Y_END,&time_base.B_color_value[0]);
#endif

}

void xyz_fir(void)
{
	unsigned int i,j,k,flag,flag_in;
	unsigned int times;
	unsigned int get_data_lenth;
	unsigned int in_addr,out_addr;
	signed short mid_in_buf[2*FIR_BLOCK_SIZE];
	signed short mid_out_buf[FIR_BLOCK_SIZE];
	signed short *p_out,*p_in;
	
	in_fft = 1;
	get_data_lenth = abs(Z_acc.got_acc_num - Z_acc.used_acc_num);
	times = get_data_lenth/FIR_BLOCK_SIZE;
	flag = 0;

	for(i=0;i<times;i++)
	{
		in_addr = (Z_acc.used_acc_num+FIR_BLOCK_SIZE*i)&(MMA845X_Z_ACC_BUF-1);//

		if((in_addr+2*FIR_BLOCK_SIZE)> MMA845X_Z_ACC_BUF)
		{
	 
	 	for(j=0;j<2*FIR_BLOCK_SIZE;j++)
	 	{
	  	mid_in_buf[j]= Z_acc.acc_buf[(in_addr+j)&(MMA845X_Z_ACC_BUF-1)];
	 	}
		p_in = mid_in_buf;
											   
		}else{
		p_in = &Z_acc.acc_buf[in_addr];
		}

		out_addr = (tfilter_result.got_filter_acc_num+FIR_BLOCK_SIZE*i)&(MMA845X_XYZ_FILTER_BUF-1);

		if((out_addr+FIR_BLOCK_SIZE)>MMA845X_XYZ_FILTER_BUF)
		{
		p_out =  mid_out_buf;
		flag = 1;
		}
		else
		{
		p_out = &tfilter_result.filter_acc_buf[out_addr];
		}

		arm_fir_q15(&FIR_S,p_in,p_out,FIR_BLOCK_SIZE);

		if(flag)
		{
			for(j=0;j<FIR_BLOCK_SIZE;j++)
			{
		  	tfilter_result.filter_acc_buf[(out_addr+j)&(MMA845X_XYZ_FILTER_BUF-1)] = mid_out_buf[j];
			}
		}
	}

	Z_acc.used_acc_num = Z_acc.used_acc_num + times*FIR_BLOCK_SIZE;
	tfilter_result.got_filter_acc_num = tfilter_result.got_filter_acc_num + times*FIR_BLOCK_SIZE;
}

//x -- 1
//y -- 2
//z -- 3
void xyz_value_fir_to_graph(void)
{
	int i;
	static signed short last_acc ;
	signed short temp;
	signed short acc_buf[34];//
	int          acc_nums = 0;
	
	short nums;

	int acc_nums_of_one_pixel;
	acc_nums_of_one_pixel = tdisp_acc_struct.acc_nums_of_one_pixel;

		while((tfilter_result.got_filter_acc_num - tfilter_result.used_filter_acc_num >= acc_nums_of_one_pixel) && (acc_nums < 32))
		{
			temp = tfilter_result.filter_acc_buf[tfilter_result.used_filter_acc_num & (MMA845X_XYZ_FILTER_BUF-1)];
			tfilter_result.used_filter_acc_num++;
			for(i=1; i<acc_nums_of_one_pixel; i++)
			{
				if(temp < tfilter_result.filter_acc_buf[tfilter_result.used_filter_acc_num  & (MMA845X_XYZ_FILTER_BUF-1)])
				{
					temp = tfilter_result.filter_acc_buf[tfilter_result.used_filter_acc_num  & (MMA845X_XYZ_FILTER_BUF-1)];
				}
				tfilter_result.used_filter_acc_num++;
			}
		//	acc_buf[acc_nums+1] = (temp - MMA845X_Z_DEFAULT)/128; //acc的范围是 -8192 —— +8191(2^13) 使用128个点表示 -2g —— +2g
		//	acc_buf[acc_nums+1] = (temp - MMA845X_Z_DEFAULT)/32;  //acc的范围是 -8192 —— +8191(2^13) 使用128个点表示 -2g —— +2g, FIR 压缩严重 放大32倍
		//  FIR 结果 缩小29倍！
			acc_buf[acc_nums+1] = 0-((temp&0x8000)|((temp)>>4));  //acc的范围是 -8192 —— +8191(2^13) 使用128个点表示 -2g —— +2g
			acc_nums++;
		}
		
		if((acc_nums > 0)&&(Z_acc.acc_x_pose < (SCALE_X_START+SCALE_X_SIZE)))
		{
			acc_buf[0] = last_acc;
			last_acc = acc_buf[acc_nums-1];
			GUI_DrawGraph(acc_buf,acc_nums+1, Z_acc.acc_x_pose-1,Z_acc.acc_y_pose);
		}
		
		Z_acc.acc_x_pose += acc_nums;
		acc_nums = 0;
		if(Z_acc.acc_x_pose  >= (SCALE_X_START+SCALE_X_SIZE))
		{
			sample_status = STOP;
		    xyz_file_save_end();
		}
}



void xyz_value_dir_to_graph(MMA845X_struct* _acc,GUI_COLOR col,EXYZ xyz)
{
	int i;
	static signed short last_acc[3];
	signed short temp;
	signed short acc_buf[34];
	signed short mid;
	int          acc_nums = 0;
	short nums;
	int acc_nums_of_one_pixel;

	GUI_COLOR  get_col;

	acc_nums_of_one_pixel = tdisp_acc_struct.acc_nums_of_one_pixel;

	get_col = GUI_GetColor();
	GUI_SetColor(col);
		while((_acc->got_acc_num - _acc->used_acc_num >= acc_nums_of_one_pixel) && (acc_nums < 32))
		{
			temp = _acc->acc_buf[_acc->used_acc_num & (MMA845X_XYZ_ACC_BUF - 1)];
			_acc->used_acc_num++;

			for(i=1; i<acc_nums_of_one_pixel; i++)
			{
				if(temp < _acc->acc_buf[_acc->used_acc_num & (MMA845X_XYZ_ACC_BUF - 1)])
				{
				   temp = _acc->acc_buf[_acc->used_acc_num & (MMA845X_XYZ_ACC_BUF - 1)];
				}
				_acc->used_acc_num++;
			}
			//acc_buf[acc_nums+1] = (temp - MMA845X_Z_DEFAULT)/128;  //acc的范围是 -8192 —— +8191(2^13) 使用128个点表示 -2g —— +2g
			//(temp&0x8000) - 符号位
			// 0 - xxx - Y轴 
			// temp>>2 - 实际的范围
			// temp>>7 - 使用128个点表示 -2g —— +2g

			// 问题 temp >> 2 ,符号位 仍然存在
			
			mid = temp>>9;  //acc的范围是 -8192 —— +8191(2^13) 使用128个点表示 -2g —— +2g
			acc_buf[acc_nums+1] = 0-mid;
			//acc_buf[acc_nums+1] = (temp>>9);  //acc的范围是 -8192 —— +8191(2^13) 使用128个点表示 -2g —— +2g
			//acc_buf[acc_nums+1] = 0-((temp&0x8000)|((temp)>>9));  //acc的范围是 -8192 —— +8191(2^13) 使用128个点表示 -2g —— +2g
			acc_nums++;
		}
		
		if((acc_nums > 0)&&(_acc->acc_x_pose < (SCALE_X_START+SCALE_X_SIZE)))
		{
			acc_buf[0] = last_acc[xyz];
			last_acc[xyz] = acc_buf[acc_nums - 1];
			GUI_DrawGraph(acc_buf,acc_nums+1,_acc->acc_x_pose - 1,_acc->acc_y_pose);
		}

		_acc->acc_x_pose += acc_nums;
		acc_nums = 0;
		if(_acc->acc_x_pose >= (SCALE_X_START+SCALE_X_SIZE))
		{
		sample_status = STOP;
		 xyz_file_save_end();
		}
		GUI_SetColor(get_col);
}



void fir_init(int get_id)
{
	arm_fir_init_q15(&FIR_S,FIR_TAPS,&fir_coeffs[get_id-1][0],&FIR_State[0],FIR_BLOCK_SIZE);
}

void get_data_from_sd(signed short* data ,unsigned int loc1,unsigned int loc2, unsigned int size,EGetDataMode mode)
{

}

void draw_fft_scale(void)
{
	TSEPoint tsepoint;
	TScale tscale;
	char x_unit[]="X /DIV HZ:";
	char y_unit[]="Y /DIV RANG:";

	tscale.x_pix_size = XYZ_SCALE_X_SIZE-88;// 凑到0.5div/hz 每格 512
	tscale.y_pix_size = XYZ_SCALE_Y_SIZE;    

	tscale.disp_text_p0.x=480;
	tscale.disp_text_p0.y=460;
	
	tscale.disp_text_p1.x = 600;
	tscale.disp_text_p1.y = 460;
	
    tscale.unit_x = x_unit;
	tscale.unit_y = y_unit;
	
	tscale.y_data_max = FFT_SCALE_Y_MAX;

	tscale.x_data_max = FFT_SCALE_X_MAX;

	// start_point 对应实际的液晶坐标
	tsepoint.start_point.x = XYZ_SCALE_X_START;
	tsepoint.start_point.y = XYZ_SCALE_Y_END;
	tsepoint.end_point.x = tsepoint.start_point.x + XYZ_SCALE_X_SIZE-88;//凑到0.5div/hz 每格 512
	tsepoint.end_point.y = XYZ_SCALE_Y_END;
	draw_scale(tsepoint,0xffff,0);		//X

	tsepoint.start_point.x = XYZ_SCALE_X_START;
	tsepoint.start_point.y = XYZ_SCALE_Y_END;
	tsepoint.end_point.x = XYZ_SCALE_X_START;
	tsepoint.end_point.y = tsepoint.start_point.y - XYZ_SCALE_Y_SIZE;
	draw_scale(tsepoint,0xffff,0);		//Y

	scale_set(&tscale);
}

// |---------------------------| 1024 point lenth    in 2  select 1 point	
// |-----------------------|     512 dip point 2.5Hz per div  (520/5 = 104)
// |-----------------|           256Hz

//	|?
//	|
//	|
//	|
//------------------------------ Y0     ?= 2Y0 - y  ---->GUI_DrawGraph -> 0- ...
//	|
//	|
//	|
//	|
//	|y

void view_fft(signed short* buf)
{
	int i,j;
	unsigned int color;
	signed short data_buf[FFT_LENTH/2];
	TSEPoint sepoint;
	color = GUI_GetColor();
	charge_button_fft_fun();
	GUI_ClearRect(0,XYZ_SCALE_Y_START,XYZ_FFT_X_SIZE,YXZ_FFT_Y_SIZE);
	draw_fft_scale();
	
	for(i=0,j=0;i< FFT_LENTH;i++,j++)
	{
		if(abs(buf[i])>abs(buf[i+1]))
		{
		data_buf[j] = -buf[i];
		}else{
		data_buf[j] = -buf[i+1];
		}
		i++;
	}

	GUI_SetColor(GUI_CYAN);
	GUI_DrawGraph(data_buf,FFT_LENTH/2,SCALE_X_START,XYZ_SCALE_Y_END);
	GUI_SetColor(color);
	charge_button_fft_fun();
}

void charge_button_fft_fun(void)
{
	int i;
	BUTTON_SetText(WM_GetDialogItem(current_handle,GUI_ID_REVIVAL_BUTTON),"FFT返回");
	
	for(i=GUI_ID_PARS_BUTTON;i<GUI_ID_ARROW_RIGHT_BUTTON+1;i++)
	{
	WM_DisableWindow(WM_GetDialogItem(current_handle,i));
	}
	WM_EnableWindow(WM_GetDialogItem(current_handle,GUI_ID_REVIVAL_BUTTON));
	BUTTON_SetPressed(WM_GetDialogItem(current_handle,GUI_ID_Z_FFT_BUTTON),0);
}

void xyz_sys_init(void)
{
   #ifndef WIN_SIM
    NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

   #endif
}


void disp_titles(void)
{
	int x,y,det;
	GUI_COLOR color;
	const GUI_FONT *pfont;
	pfont = GUI_GetFont();

	color = GUI_GetColor();
	x = 10;
	y = 420-96;
	det = 78*1.5;

	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_Font8x16);

	GUI_DispStringAt("Za(Max)_m2/s|", x+det*0,y);
	GUI_DispStringAt("Za(AVE)_m2/s|", x+det*1,y);
	GUI_DispStringAt("Za(TIME)_s|", x+det*2,y);
	GUI_DispStringAt("Zd(Max)_m2/s|", x+det*3,y);
	GUI_DispStringAt("Zd(AVE)_m2/s|", x+det*4,y);

	GUI_DispStringAt("Zd(TIME)_s|", x+det*0,y+64);
	GUI_DispStringAt("Z(Max)_m2/s|", x+det*1,y+64);
	GUI_DispStringAt("X(Max)_m2/s|", x+det*2,y+64);
	GUI_DispStringAt("Y(Max)_m2/s|", x+det*3,y+64);
	
	GUI_SetColor(color);
	GUI_SetFont(pfont);
}

void disp_caculate(void)
{
	int x,y,det;
	float mid;
	GUI_COLOR color;
 const	GUI_FONT *pfont;
	color = GUI_GetColor();
	x = 10;
	y = 440-96;
	det = 78*1.5;

	
	pfont = GUI_GetFont();

	GUI_SetFont(&GUI_Font8x16);
	GUI_SetColor(GUI_BLUE);

	GUI_GotoXY(x+det*0,y);
	// Z_acc.acc_max >> 2
	// ---> 2 -- 4095*2
	// ---> 1 -- 4096
	//.4096 --> >> 12
	mid = Z_acc.acc_max>>14;
	GUI_DispFloat(mid,5);

	GUI_GotoXY(x+det*1,y);
    mid = Z_acc.acc_ave_add >> 14;
	mid = mid/Z_acc.acc_time;
	GUI_DispFloat(mid,5);

	GUI_GotoXY(x+det*2,y);
	GUI_DispFloat((float)(Z_acc.acc_time*0.00125),5);

	GUI_GotoXY(x+det*3,y);
	mid = ((Z_acc.dec_max)&(0x7FFF))>> 14;
	GUI_DispFloat(-mid,5);


	GUI_GotoXY(x+det*4,y);
	mid = (((Z_acc.dec_max)&(0x7FFF))>> 14)/Z_acc.acc_time;
	GUI_DispFloat(-mid,5);

	GUI_GotoXY(x+det*0,y+64);
	GUI_DispFloat((float)(Z_acc.dec_time*0.00125),5);

	GUI_GotoXY(x+det*1,y+64);
	mid = Z_acc.acc_dec_abs_max >> 14;
	GUI_DispFloat(mid,5);

	GUI_GotoXY(x+det*2,y+64);
	mid = X_acc.acc_dec_abs_max >> 14;
	GUI_DispFloat(mid,5);

	GUI_GotoXY(x+det*3,y+64);
	mid = Y_acc.acc_dec_abs_max >> 14;
	GUI_DispFloat(mid,5);

	GUI_SetColor(color);
	GUI_SetFont(pfont);
}


//文件的最后一条记录 记录最终一条记录的在文件中的偏移位置
int xyz_file_init(int status)
{

#ifndef WIN_SIM
	    unsigned int i, bw;
		unsigned char res;
	    unsigned int last_fragment_start;
		char men;
		if(status)
		f_mount(0, &fs);									  //注册到文件系统0区	
		res = f_open(&fsrc, "xyz_a.ld",FA_OPEN_ALWAYS|FA_WRITE |FA_READ) ;
		f_sync(&fsrc);
		 
		if(res)
		{
			return res;
		}
		
		res = f_lseek(&fsrc,fsrc.fsize);  // 规定 最后数据 指向 本条记录在文件中所在的位置
		
		if(fsrc.fsize >  sizeof(xyz_file)+4)
		{
			res = f_lseek(&fsrc, fsrc.fsize-4);
			res = f_read(&fsrc,&last_fragment_start,sizeof(last_fragment_start),&bw);// 读取上一条记录的位置	
			res = f_lseek(&fsrc,last_fragment_start);
			res = f_read(&fsrc,&xyz_file,sizeof(xyz_file),&bw); //读出文件头
		}
		return 0;	
#endif
}



int xyz_head_save(void)
{
 #ifndef WIN_SIM
	    unsigned int i, bw;
		unsigned char res;
		char men;

		res = f_lseek(&fsrc, fsrc.fsize);
		
		if(fsrc.fsize >  sizeof(xyz_file)+4)// 是否是第一次
		{
			xyz_file.fragment_start = fsrc.fsize; //记录本次的起始位置	
		}
		else
		{
			xyz_file.fragment_start = 0; //记录本次的起始位置
		}
		res = f_write(&fsrc,&xyz_file,sizeof(xyz_file),&bw); //存储文件头

		return res;
#endif	
	
}

int xyz_file_data_save(unsigned char *buf, unsigned int data_size)
{
#ifndef WIN_SIM
	unsigned char static res;
	unsigned int  bw;
	res = f_lseek(&fsrc, fsrc.fsize);
	res = f_write(&fsrc,buf,data_size,&bw); //存储数据	
	return res;
#endif	
}

void xyz_file_save_end(void)
{
#ifndef WIN_SIM
 	unsigned char res;
	unsigned int  bw;
	res = f_lseek(&fsrc, fsrc.fsize);
	res = f_write(&fsrc,&xyz_file.fragment_start ,4,&bw); //存储本条记录在文件中的其实位置
	if(bw!=4 || (res != 0))	// FR_OK
	{
		while(1);
	}
#endif
}

void xyz_file_close(void)
{
	static int test = 0;
#ifndef WIN_SIM
	unsigned char res;
	unsigned int  bw;

	res = f_close(&fsrc);
if(res != 0) //FR_OK == 0
{
	while(1);
}
	f_mount(0, NULL);
		
#endif
}

void disp_mode(void)
{
	int x,y,det;
	float div;
	char buf[10];

	GUI_COLOR color;
	color = GUI_GetColor();
	x = 8;
	y = 420;
	det = 45;

	GUI_SetColor(GUI_GREEN);

	GUI_DispStringAt("MODE:", x+det*0,470);
	if(xyz_pars.auto_sel)
	{
	GUI_DispStringAt("AUTO", x+det*1,470);
	GUI_DispStringAt("START:", x+det*2,470);

	sprintf(buf,"%01.3fg",xyz_pars.auto_start_za);
	GUI_DispStringAt(buf, x+det*3,470);

	GUI_DispStringAt("STOP:", x+det*4,470);

	sprintf(buf,"%01.3fg",xyz_pars.auto_stop_za);
	GUI_DispStringAt(buf, x+det*5,470);
	
	}else{
	GUI_DispStringAt("SET", x+det*1,470);
	GUI_DispStringAt("TIME:", x+det*2,470);
	sprintf(buf,"%ds",xyz_pars.record_s);
	GUI_DispStringAt(buf, x+det*3,470);
	}
	GUI_DispStringAt("FILTER:", x+det*6,470);
	if(xyz_pars.e_filter == 0)
		GUI_DispStringAt("No", x+det*7,470);
	else if(xyz_pars.e_filter == 1)
		GUI_DispStringAt("20Hz", x+det*7,470);
	else if(xyz_pars.e_filter == 2)
		GUI_DispStringAt("30Hz", x+det*7,470);
	else if(xyz_pars.e_filter == 3)
		GUI_DispStringAt("50Hz", x+det*7,470);
	else  if(xyz_pars.e_filter == 4)
		GUI_DispStringAt("100Hz", x+det*7,470);
	else  if(xyz_pars.e_filter == 5)
		GUI_DispStringAt("200Hz", x+det*7,470);
	GUI_SetColor(color);
	
	if(xyz_pars.record_s > 600)
	{
		xyz_pars.record_s = 600;
	}
}



int save_xyz(void)
{
	int i,j,k;
	unsigned char xyz_data[3*2*400];
	unsigned int first_part,second_part;
	
	if(Z_acc.got_acc_num - Z_acc.used_acc_num >= tdisp_acc_struct.acc_nums_of_one_pixel)
	{
		if((Z_acc.used_acc_num & (MMA845X_Z_ACC_BUF - 1)) + tdisp_acc_struct.acc_nums_of_one_pixel > MMA845X_Z_ACC_BUF)
		{
		 first_part = MMA845X_Z_ACC_BUF - (Z_acc.used_acc_num & (MMA845X_Z_ACC_BUF - 1));
		 second_part = (tdisp_acc_struct.acc_nums_of_one_pixel-first_part);
		 
		 for(i=0;i<(first_part*2);i++)
		 {
		 xyz_data[i] = X_acc.acc_buf[X_acc.used_acc_num & (MMA845X_X_ACC_BUF - 1)+i];
		 i++;
		 xyz_data[i] =  X_acc.acc_buf[X_acc.used_acc_num & (MMA845X_X_ACC_BUF - 1)+i];
		 i--;

		 xyz_data[i] =  Y_acc.acc_buf[Y_acc.used_acc_num & (MMA845X_Y_ACC_BUF - 1)+i];
		 i++;

		 xyz_data[i] =  Y_acc.acc_buf[Y_acc.used_acc_num & (MMA845X_Y_ACC_BUF - 1)+i];
		 i--;

		 xyz_data[i] =  Z_acc.acc_buf[Z_acc.used_acc_num & (MMA845X_Z_ACC_BUF - 1)+i];
		 i++;
		 xyz_data[i] =  Z_acc.acc_buf[Z_acc.used_acc_num & (MMA845X_Z_ACC_BUF - 1)+i];
		 
		 }

		 i--;
		 i--;
		 
		 for(j=0;j<(second_part*2);j++)
		 {
		 xyz_data[i+j] = X_acc.acc_buf[j];
		 j++;
		 xyz_data[i+j] = X_acc.acc_buf[j];
		 j--;
		 xyz_data[i+j] = Y_acc.acc_buf[j];
		 j++;
		 xyz_data[i+j] = Y_acc.acc_buf[j];
		 j--;
		 xyz_data[i+j] = Z_acc.acc_buf[j];
		 j++;
		 xyz_data[i+j] = Z_acc.acc_buf[j];

		 }

		}else{
		
		 for(i=0;i< tdisp_acc_struct.acc_nums_of_one_pixel*2;i++)
		 {
		 xyz_data[i] = X_acc.acc_buf[X_acc.used_acc_num & (MMA845X_X_ACC_BUF - 1)+i];
		 i++;
		 xyz_data[i] =  X_acc.acc_buf[X_acc.used_acc_num & (MMA845X_X_ACC_BUF - 1)+i];
		 i--;
		 
		 xyz_data[i] =  Y_acc.acc_buf[Y_acc.used_acc_num & (MMA845X_Y_ACC_BUF - 1)+i];
		 i++;
		 xyz_data[i] =  Y_acc.acc_buf[Y_acc.used_acc_num & (MMA845X_Y_ACC_BUF - 1)+i];
		 i--;

		 xyz_data[i] =  Z_acc.acc_buf[Z_acc.used_acc_num & (MMA845X_Z_ACC_BUF - 1)+i];
		 i++;
		 xyz_data[i] =  Z_acc.acc_buf[Z_acc.used_acc_num & (MMA845X_Z_ACC_BUF - 1)+i];
		 
		 }
		}
	}
	xyz_file_data_save(xyz_data, tdisp_acc_struct.acc_nums_of_one_pixel);
}









