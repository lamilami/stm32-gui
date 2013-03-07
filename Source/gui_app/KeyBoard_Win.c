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
#include "KeyBoard_Win.h"

extern char *PYSearch(unsigned char *msg ,int *num);

/*********************************************************************
*
*       static data
*
**********************************************************************
*/

#define GUI_ID_EDIT_DATA    (GUI_ID_USER+1)
#define GUI_ID_TEXT_PY		(GUI_ID_USER+2)
#define GUI_ID_EDIT_CH      (GUI_ID_USER+3)
#define GUI_ID_BUTTON_KEY_0   (GUI_ID_USER+4)
#define GUI_ID_BUTTON_KEY_1   (GUI_ID_USER+5)
#define GUI_ID_BUTTON_KEY_2   (GUI_ID_USER+6)
#define GUI_ID_BUTTON_KEY_3   (GUI_ID_USER+7)
#define GUI_ID_BUTTON_KEY_4   (GUI_ID_USER+8)
#define GUI_ID_BUTTON_KEY_5   (GUI_ID_USER+9)
#define GUI_ID_BUTTON_KEY_6   (GUI_ID_USER+10)
#define GUI_ID_BUTTON_KEY_7   (GUI_ID_USER+11)
#define GUI_ID_BUTTON_KEY_8   (GUI_ID_USER+12)
#define GUI_ID_BUTTON_KEY_9   (GUI_ID_USER+13)

#define GUI_ID_BUTTON_KEY_LS   (GUI_ID_USER+14)
#define GUI_ID_BUTTON_KEY_RS   (GUI_ID_USER+15)

#define GUI_ID_BUTTON_KEY_A   (GUI_ID_USER+16)
#define GUI_ID_BUTTON_KEY_B   (GUI_ID_USER+17)
#define GUI_ID_BUTTON_KEY_C   (GUI_ID_USER+18)
#define GUI_ID_BUTTON_KEY_D   (GUI_ID_USER+19)
#define GUI_ID_BUTTON_KEY_E   (GUI_ID_USER+20)
#define GUI_ID_BUTTON_KEY_F   (GUI_ID_USER+21)
#define GUI_ID_BUTTON_KEY_G   (GUI_ID_USER+22)
#define GUI_ID_BUTTON_KEY_H   (GUI_ID_USER+23)
#define GUI_ID_BUTTON_KEY_I   (GUI_ID_USER+24)
#define GUI_ID_BUTTON_KEY_J   (GUI_ID_USER+25)
#define GUI_ID_BUTTON_KEY_K   (GUI_ID_USER+26)
#define GUI_ID_BUTTON_KEY_L   (GUI_ID_USER+27)
#define GUI_ID_BUTTON_KEY_M   (GUI_ID_USER+28)
#define GUI_ID_BUTTON_KEY_N   (GUI_ID_USER+29)
#define GUI_ID_BUTTON_KEY_O   (GUI_ID_USER+30)
#define GUI_ID_BUTTON_KEY_P   (GUI_ID_USER+31)
#define GUI_ID_BUTTON_KEY_Q   (GUI_ID_USER+32)
#define GUI_ID_BUTTON_KEY_R   (GUI_ID_USER+33)
#define GUI_ID_BUTTON_KEY_S   (GUI_ID_USER+34)
#define GUI_ID_BUTTON_KEY_T   (GUI_ID_USER+35)
#define GUI_ID_BUTTON_KEY_U   (GUI_ID_USER+36)
#define GUI_ID_BUTTON_KEY_V   (GUI_ID_USER+37)
#define GUI_ID_BUTTON_KEY_W   (GUI_ID_USER+38)
#define GUI_ID_BUTTON_KEY_X   (GUI_ID_USER+39)
#define GUI_ID_BUTTON_KEY_Y   (GUI_ID_USER+40)
#define GUI_ID_BUTTON_KEY_Z   (GUI_ID_USER+41)

#define GUI_ID_BUTTON_KEY_DT   (GUI_ID_USER+43)
#define GUI_ID_BUTTON_KEY_S1   (GUI_ID_USER+44)
#define GUI_ID_BUTTON_KEY_BU   (GUI_ID_USER+45)
#define GUI_ID_BUTTON_KEY_S2   (GUI_ID_USER+46)
#define GUI_ID_BUTTON_KEY_S3   (GUI_ID_USER+47)
#define GUI_ID_BUTTON_KEY_ENT   (GUI_ID_USER+48)
#define GUI_ID_BUTTON_KEY_CAN   (GUI_ID_USER+49)
#define GUI_ID_BUTTON_KEY_S4   (GUI_ID_USER+50)

#define GUI_ID_A_Z			(GUI_ID_USER+51)
#define GUI_ID_0_9			(GUI_ID_USER+52)
#define GUI_ID_BUTTON_KEY_CN   (GUI_ID_USER+53)

#define ASC_II_a			97
#define ASC_II_A            65
#define ASC_II_0			48
#define ASC_II_DOT			46
#define OFF_SET				(ASC_II_a - GUI_ID_BUTTON_KEY_A)

#define OFF_SET_A           (ASC_II_A - GUI_ID_BUTTON_KEY_A)

#define OFF_SET_0			(ASC_II_0 - GUI_ID_BUTTON_KEY_0)

#define OFF_SET_DT			(ASC_II_DOT- GUI_ID_BUTTON_KEY_DT)		



extern const GUI_FONT GUI_FontHZ_SongTi_16;

TKeyBoard_H* keyboard_win_h;


char dat;
char* ch_dat;
int num ;

char data[DATA_SIZE];
char ch_data[CH_DATA_SIZE];
char key[60];
char num_add_ch[60];
char res_ch[60];

void ID_A_Z(WM_MESSAGE * pMsg)
{
	int i,j,k;
	
	k = 0;
    
	if(keyboard_win_h->work_state == CHINESE)
	{  
	*(keyboard_win_h->pdata++) = WM_GetId(pMsg->hWinSrc) + OFF_SET;
	ch_dat = PYSearch(keyboard_win_h->pdata_head , &(keyboard_win_h->num_ch));
		if(ch_dat == '\0')
		{
		keyboard_win_h->num_ch = 0;
		keyboard_win_h->pdata--;  // 如果查不到 表明当前输入的字母查不到 就退回一位
		return;
		}
	keyboard_win_h->pch_data_head = ch_dat;

	keyboard_win_h->pch_data_end = keyboard_win_h->pch_data_head + 2*(keyboard_win_h->num_ch);

	keyboard_win_h->pch_data = ch_dat;

	keyboard_win_h->pnum_data = keyboard_win_h->pnum_data_head;
	
	if(keyboard_win_h->num_ch > 0)
	{
	//	for(i= 0; i<(keyboard_win_h->num_ch)/7;i++)
		if(keyboard_win_h->pch_data_end - keyboard_win_h->pch_data > 14)
		{
			k = 7;
		}else{
		
			k = (keyboard_win_h->pch_data_end - keyboard_win_h->pch_data)/2;
		}
			
		for(j= 0; j<k; j++)
		{
			*(keyboard_win_h->pnum_data++) = j+'1';
			
			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++);
			
			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++); //14
			
			*(keyboard_win_h->pnum_data++) = ' ';
		}

			if(k<7)
		{
			for(j=0; j<4*(7-k);j++)// 清空
			{
			*(keyboard_win_h->pnum_data++) = '\0';
			}
		//	for(j=0; j<2*(7-k);j++)// 补齐
		//	{
		//	keyboard_win_h->pch_data++;
		//	}
		}

		TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT_PY),keyboard_win_h->pdata_head);
	
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_CH),keyboard_win_h->pnum_data_head);
		
		if(keyboard_win_h->pdata == keyboard_win_h->pdata_end)
		keyboard_win_h->pdata = keyboard_win_h->pdata_head;
	}

	}else if(keyboard_win_h->work_state == ENGLISH_S){
	
		*(keyboard_win_h->res_ch_data++) = WM_GetId(pMsg->hWinSrc) + OFF_SET;

		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_DATA),keyboard_win_h->res_ch_data_head);
	
	}else if(keyboard_win_h->work_state == ENGLISH_B){
	
		*(keyboard_win_h->res_ch_data++) = WM_GetId(pMsg->hWinSrc) +OFF_SET_A;
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_DATA),keyboard_win_h->res_ch_data_head);

	}
}


void ID_key_R(WM_MESSAGE * pMsg)
{
	int i,j,k;

	if(keyboard_win_h->pch_data_end - keyboard_win_h->pch_data > 0)
	{
		keyboard_win_h->pnum_data = keyboard_win_h->pnum_data_head;
		
		if(keyboard_win_h->pch_data_end - keyboard_win_h->pch_data > 14)
		{
			k = 7;

		}else{
			k = (keyboard_win_h->pch_data_end - keyboard_win_h->pch_data)/2;

		}

		for(j= 0; j<k; j++)
		{
			*(keyboard_win_h->pnum_data++) = j+'1';
	
			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++);  

			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++);  //28 
			
			*(keyboard_win_h->pnum_data++) = ' ';
		}
		if(k<7)
		{
			for(j=0; j<4*(7-k);j++)// 清空
			{
			*(keyboard_win_h->pnum_data++) = '\0';
			}
			for(j=0; j<2*(7-k);j++)// 补齐
			{
			keyboard_win_h->pch_data++;
			}
		}
	}
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_CH),keyboard_win_h->pnum_data_head);
}


void ID_key_L(WM_MESSAGE * pMsg)
{
	int i,j;
	int k;

	// 28 7个汉字 28个单元
	// (keyboard_win_h->pch_data > 0)  回退测试

	if((keyboard_win_h->pch_data - 28 >= keyboard_win_h->pch_data_head)&&(keyboard_win_h->pch_data > 0))
	{
		keyboard_win_h->pnum_data = keyboard_win_h->pnum_data_head;
		
		keyboard_win_h->pch_data = keyboard_win_h->pch_data - 28;					// 28 - 0x1c

		for(j= 0; (j<7)&& (*(keyboard_win_h->pch_data)!='\0'); j++)
		{
			*(keyboard_win_h->pnum_data++) = j+'1';

			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++);
			
			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++);
			
			*(keyboard_win_h->pnum_data++) = ' ';
		}		
	
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_CH),keyboard_win_h->pnum_data_head);
	}
}



void ID_1_0(WM_MESSAGE * pMsg)
{
	int num,j;
	
	if((keyboard_win_h->work_state == CHINESE)&&(keyboard_win_h->pnum_data != keyboard_win_h->pnum_data_head))
	{
		num = 	WM_GetId(pMsg->hWinSrc)-GUI_ID_BUTTON_KEY_1;// from 0 begin
        num =   num*4;
		*(keyboard_win_h->res_ch_data++) = *(keyboard_win_h->pnum_data_head+num+1);
		*(keyboard_win_h->res_ch_data++) = *(keyboard_win_h->pnum_data_head+num+2);
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_DATA),keyboard_win_h->res_ch_data_head);
		
		keyboard_win_h->pnum_data = keyboard_win_h->pnum_data_head;
		for(j=0;j<28;j++)
		{
		*(keyboard_win_h->pnum_data++) = '\0';	
		}
		keyboard_win_h->pnum_data = keyboard_win_h->pnum_data_head;
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_CH),keyboard_win_h->pnum_data_head);

		for(j=0;(keyboard_win_h->pdata) != (keyboard_win_h->pdata_head);j++)
		{
		*(keyboard_win_h->pdata--) = '\0';
		}
		*(keyboard_win_h->pdata) ='\0';
		TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT_PY),keyboard_win_h->pdata_head);

	}else if(keyboard_win_h->work_state != CHINESE){

		*(keyboard_win_h->res_ch_data++) = WM_GetId(pMsg->hWinSrc) + OFF_SET_0;
		EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_DATA),keyboard_win_h->res_ch_data_head);
	
	}
}

void ID_DT(WM_MESSAGE * pMsg)
{
	*(keyboard_win_h->res_ch_data++) = WM_GetId(pMsg->hWinSrc) + OFF_SET_DT;
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_DATA),keyboard_win_h->res_ch_data_head);
}


void OnCancleCliked(WM_MESSAGE *pMsg)
{
	int i;
	keyboard_win_h->res_ch_data = keyboard_win_h->res_ch_data_head;
	for(i=0; i<60;i++)
	{
	 *(keyboard_win_h->res_ch_data++) = '\0';
	}
	keyboard_win_h->res_ch_data = keyboard_win_h->res_ch_data_head;
	GUI_EndDialog(pMsg->hWin, 0);
}

void ID_KEY_ENTER(WM_MESSAGE *pMsg)
{
	
	GUI_EndDialog(pMsg->hWin, 0);
}


void Show_Work_State(WM_MESSAGE *pMsg)
{

	//if(keyboard_win_h->work_state == NUMBER)
	//{
	//BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON_KEY_CN), "123");
	
	
	//}else 
	if(keyboard_win_h->work_state == ENGLISH_S)
	{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON_KEY_CN), "en");
	}else if(keyboard_win_h->work_state == ENGLISH_B)
	{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON_KEY_CN), "EN");
	}else if(keyboard_win_h->work_state == CHINESE)
	{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON_KEY_CN), "CH");
	}else if(keyboard_win_h->work_state == SFLOAT){
	
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON_KEY_CN), "FL");
	}

	//if(keyboard_win_h->work_state != CHINESE)
	//{
	
	//EDIT_SetFont(WM_GetDialogItem(pMsg->hWin,GUI_ID_EDIT_CH),&GUI_Font10_ASCII);
	//}

}


void ID_Key_CN(WM_MESSAGE * pMsg)
{
	if(keyboard_win_h->work_state == CHINESE)
	{
		keyboard_win_h->work_state = ENGLISH_S;

	}else {
		keyboard_win_h->work_state++;
	}
	
	Show_Work_State(pMsg);
}


void ID_key_S4(WM_MESSAGE *pMsg)
{
	int i,j,k;
	
	k = 0;
    
	if(keyboard_win_h->work_state == CHINESE)
	{ 
		if(keyboard_win_h->pch_data > keyboard_win_h->pch_data_head)
		{
	keyboard_win_h->pdata--;
		}

	*(keyboard_win_h->pdata) ='\0';
	
	ch_dat = PYSearch(keyboard_win_h->pdata_head , &(keyboard_win_h->num_ch));
	if(ch_dat == '\0')
	{
		keyboard_win_h->num_ch = 0;
		//keyboard_win_h->pdata--;  // 如果查不到 表明当前输入的字母查不到 就退回一位
		//return;
	}
	keyboard_win_h->pch_data_head = ch_dat;

	keyboard_win_h->pch_data_end = keyboard_win_h->pch_data_head + 2*(keyboard_win_h->num_ch);

	keyboard_win_h->pch_data = ch_dat;

	keyboard_win_h->pnum_data = keyboard_win_h->pnum_data_head;
	
	if(keyboard_win_h->num_ch > 0)
	{
		if(keyboard_win_h->pch_data_end - keyboard_win_h->pch_data > 14)
		{
			k = 7;
		}else{
		
			k = (keyboard_win_h->pch_data_end - keyboard_win_h->pch_data)/2;
		}
			
		for(j= 0; j<k; j++)
		{
			*(keyboard_win_h->pnum_data++) = j+'1';

			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++);

			*(keyboard_win_h->pnum_data++) = *(keyboard_win_h->pch_data++); //14
			
			*(keyboard_win_h->pnum_data++) = ' ';
		}

			if(k<7)
		{
			for(j=0; j<4*(7-k);j++)// 清空
			{
			*(keyboard_win_h->pnum_data++) = '\0';
			}
		//	for(j=0; j<2*(7-k);j++)// 补齐
		//	{
		//	keyboard_win_h->pch_data++;
		//	}
		}
	}else{
		for(j=0; j<28;j++)// 清空
			{
			*(keyboard_win_h->pnum_data++) = '\0';
			}
	}

	TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT_PY),keyboard_win_h->pdata_head);
	
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_CH),keyboard_win_h->pnum_data_head);

	}else{
	
	keyboard_win_h->res_ch_data--;
	*(keyboard_win_h->res_ch_data--) = '\0';
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_DATA),keyboard_win_h->res_ch_data_head);

	}
}


void ID_KEY_BU(WM_MESSAGE *pMsg)
{
	if(keyboard_win_h->work_state == CHINESE)
	{
		
	 if(keyboard_win_h->res_ch_data != keyboard_win_h->res_ch_data_end)
	 {
		keyboard_win_h->res_ch_data--;
		*(keyboard_win_h->res_ch_data--)='\0';
		*(keyboard_win_h->res_ch_data) ='\0';
	 }	
	
	}else{
	if(keyboard_win_h->res_ch_data != keyboard_win_h->res_ch_data_end)
	 {
		keyboard_win_h->res_ch_data--;
		*(keyboard_win_h->res_ch_data) ='\0';
	 }	
	
	}
	EDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_DATA),keyboard_win_h->res_ch_data_head);

}


void OnxxxClicked(pMsg)
{
		
   
}


void KeyBoard_Win_Init(void)
{
	int i;
	//keyboard_win_h->work_state = CHINESE;
	keyboard_win_h->pdata = data;
	keyboard_win_h->pdata_head = data;
	keyboard_win_h->pdata_end = keyboard_win_h->pdata_head + DATA_SIZE;
	keyboard_win_h->pch_data = ch_data;
	keyboard_win_h->pch_data_head = ch_data;
	keyboard_win_h->pch_data_end = keyboard_win_h->pch_data_head + CH_DATA_SIZE;

	keyboard_win_h->pnum_data_head = num_add_ch;
	keyboard_win_h->pnum_data = num_add_ch;

	keyboard_win_h->res_ch_data_head = res_ch;
	keyboard_win_h->res_ch_data = res_ch;

	for(i=0;i<DATA_SIZE;i++)
		data[i] = '\0';

	for(i=0;i<60;i++)
		res_ch[i]='\0';

}

//EventsFunctionList
//EndofEventsFunctionList




/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/
/*
static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Key[] = {
    { FRAMEWIN_CreateIndirect,  "KEY_BOARD",         0,                       0,  0,  320,265,FRAMEWIN_CF_MOVEABLE,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_DATA,        8,  11, 298,21, 0,0},
    { TEXT_CreateIndirect,      "len",             GUI_ID_TEXT_PY,          8,  35, 48, 16, 0,0},
    { EDIT_CreateIndirect,      "len",             GUI_ID_EDIT_CH,          8,  51, 48, 16, 0,0},
    { BUTTON_CreateIndirect,    "1",                 GUI_ID_BUTTON_KEY_1,     8,  74, 28, 28, 0,0},
    { BUTTON_CreateIndirect,    "2",                 GUI_ID_BUTTON_KEY_2,     38, 74, 28, 28, 0,0},
    { BUTTON_CreateIndirect,    "3",                 GUI_ID_BUTTON_KEY_3,     68, 74, 28, 28, 0,0},
    { BUTTON_CreateIndirect,    "4",                 GUI_ID_BUTTON_KEY_4,     98, 74, 28, 28, 0,0},
    { BUTTON_CreateIndirect,    "5",                 GUI_ID_BUTTON_KEY_5,     128,74, 28, 28, 0,0},
    { BUTTON_CreateIndirect,    "6",                 GUI_ID_BUTTON_KEY_6,     158,74, 28, 28, 0,0},
    { BUTTON_CreateIndirect,    "7",                 GUI_ID_BUTTON_KEY_7,     188,74, 28, 28, 0,0},
    { BUTTON_CreateIndirect,    "8",                 GUI_ID_BUTTON_KEY_8,     218,74, 28, 28, 0,0},
    { BUTTON_CreateIndirect,    "9",                 GUI_ID_BUTTON_KEY_9,     248,74, 28, 28, 0,0},
    { BUTTON_CreateIndirect,    "0",                 GUI_ID_BUTTON_KEY_0,     278,74, 28, 28, 0,0},
    { BUTTON_CreateIndirect,    "<",                 GUI_ID_BUTTON_KEY_LS,     248,40, 28, 28, 0,0},
    { BUTTON_CreateIndirect,    ">",                 GUI_ID_BUTTON_KEY_RS,     278,40, 28, 28, 0,0},
    { BUTTON_CreateIndirect,    "q",                 GUI_ID_BUTTON_KEY_Q,     8,  108,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "w",                 GUI_ID_BUTTON_KEY_W,     38, 108,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "e",                 GUI_ID_BUTTON_KEY_E,     68, 108,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "r",                 GUI_ID_BUTTON_KEY_R,     98, 108,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "t",                 GUI_ID_BUTTON_KEY_T,     128,108,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "y",                 GUI_ID_BUTTON_KEY_Y,     158,108,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "u",                 GUI_ID_BUTTON_KEY_U,     188,108,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "i",                 GUI_ID_BUTTON_KEY_I,     218,108,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "o",                 GUI_ID_BUTTON_KEY_O,     248,108,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "p",                 GUI_ID_BUTTON_KEY_P,     278,108,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "a",                 GUI_ID_BUTTON_KEY_A,     8,  142,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "s",                 GUI_ID_BUTTON_KEY_S,     38, 142,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "d",                 GUI_ID_BUTTON_KEY_D,     68, 142,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "f",                 GUI_ID_BUTTON_KEY_F,     98, 142,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "g",                 GUI_ID_BUTTON_KEY_G,     128,142,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "h",                 GUI_ID_BUTTON_KEY_H,     158,142,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "j",                 GUI_ID_BUTTON_KEY_J,     188,142,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "k",                 GUI_ID_BUTTON_KEY_K,     218,142,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "l",                 GUI_ID_BUTTON_KEY_L,     248,142,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "EC1",                GUI_ID_BUTTON_KEY_CN,    278,142,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "z",                 GUI_ID_BUTTON_KEY_Z,     8,  176,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "x",                 GUI_ID_BUTTON_KEY_X,     38, 176,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "c",                 GUI_ID_BUTTON_KEY_C,     68, 176,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "v",                 GUI_ID_BUTTON_KEY_V,     98, 176,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "b",                 GUI_ID_BUTTON_KEY_B,     128,176,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "n",                 GUI_ID_BUTTON_KEY_N,     158,176,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "m",                 GUI_ID_BUTTON_KEY_M,     188,176,28, 28, 0,0},
    { BUTTON_CreateIndirect,    ".",                 GUI_ID_BUTTON_KEY_DT,    218,176,28, 28, 0,0},
    { BUTTON_CreateIndirect,     NULL,               GUI_ID_BUTTON_KEY_S1,     248,176,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "Aa",                GUI_ID_BUTTON_KEY_BU,    278,176,28, 28, 0,0},
    { BUTTON_CreateIndirect,     NULL,               GUI_ID_BUTTON_KEY_S2,     8,  210,28, 28, 0,0},
    { BUTTON_CreateIndirect,     NULL,               GUI_ID_BUTTON_KEY_S3,     38, 210,28, 28, 0,0},
    { BUTTON_CreateIndirect,    "enter",             GUI_ID_BUTTON_KEY_ENT,   72, 210,114,28, 0,0},
    { BUTTON_CreateIndirect,    "cancel",            GUI_ID_BUTTON_KEY_CAN,   192,210,80, 28, 0,0},
    { BUTTON_CreateIndirect,     "<-",               GUI_ID_BUTTON_KEY_S4,     278,210,28, 28, 0,0}
};
*/



static const GUI_WIDGET_CREATE_INFO _aDialogCreate_Key[] = {
    { FRAMEWIN_CreateIndirect,  "KEY_BOARD",         0,                       0,  0,  472,354,0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_DATA,        8,  11, 298,21, 0,30},
    { TEXT_CreateIndirect,      "TEXT0",             GUI_ID_TEXT_PY,          8,  35, 48, 16, 0,0},
    { BUTTON_CreateIndirect,    "1",                 GUI_ID_BUTTON_KEY_1,     7,  105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "2",                 GUI_ID_BUTTON_KEY_2,     53, 105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "3",                 GUI_ID_BUTTON_KEY_3,     99, 105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "4",                 GUI_ID_BUTTON_KEY_4,     145,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "5",                 GUI_ID_BUTTON_KEY_5,     191,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "6",                 GUI_ID_BUTTON_KEY_6,     237,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "7",                 GUI_ID_BUTTON_KEY_7,     283,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "8",                 GUI_ID_BUTTON_KEY_8,     329,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "9",                 GUI_ID_BUTTON_KEY_9,     375,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "0",                 GUI_ID_BUTTON_KEY_0,     421,105,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "<",                 GUI_ID_BUTTON_KEY_LS,     260,57, 58, 28, 0,0},
    { BUTTON_CreateIndirect,    ">",                 GUI_ID_BUTTON_KEY_RS,     329,57, 64, 28, 0,0},
    { BUTTON_CreateIndirect,    "q",                 GUI_ID_BUTTON_KEY_Q,     8,  151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "w",                 GUI_ID_BUTTON_KEY_W,     53, 151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "e",                 GUI_ID_BUTTON_KEY_E,     99, 151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "r",                 GUI_ID_BUTTON_KEY_R,     145,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "t",                 GUI_ID_BUTTON_KEY_T,     192,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "y",                 GUI_ID_BUTTON_KEY_Y,     237,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "u",                 GUI_ID_BUTTON_KEY_U,     283,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "i",                 GUI_ID_BUTTON_KEY_I,     329,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "o",                 GUI_ID_BUTTON_KEY_O,     375,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "p",                 GUI_ID_BUTTON_KEY_P,     421,151,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "a",                 GUI_ID_BUTTON_KEY_A,     7,  197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "s",                 GUI_ID_BUTTON_KEY_S,     53, 197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "d",                 GUI_ID_BUTTON_KEY_D,     99, 199,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "f",                 GUI_ID_BUTTON_KEY_F,     145,197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "g",                 GUI_ID_BUTTON_KEY_G,     191,197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "h",                 GUI_ID_BUTTON_KEY_H,     237,197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "j",                 GUI_ID_BUTTON_KEY_J,     283,197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "k",                 GUI_ID_BUTTON_KEY_K,     329,197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "l",                 GUI_ID_BUTTON_KEY_L,     375,197,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "CN",                GUI_ID_BUTTON_KEY_CN,     421,197,40, 86, 0,0},
    { BUTTON_CreateIndirect,    "z",                 GUI_ID_BUTTON_KEY_Z,     7,  243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "x",                 GUI_ID_BUTTON_KEY_X,     53, 243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "c",                 GUI_ID_BUTTON_KEY_C,     99, 243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "v",                 GUI_ID_BUTTON_KEY_V,     145,243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "b",                 GUI_ID_BUTTON_KEY_B,     191,243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "n",                 GUI_ID_BUTTON_KEY_N,     237,243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "m",                 GUI_ID_BUTTON_KEY_M,     283,243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    ".",                 GUI_ID_BUTTON_KEY_DT,    329,243,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "BUTTON",            GUI_ID_BUTTON_KEY_S1,    375,243,37, 37, 0,0},
	{ BUTTON_CreateIndirect,  "<Del",                GUI_ID_BUTTON_KEY_BU,    421,2, 37, 37, 0,0},
	{ BUTTON_CreateIndirect,    "BUTTON",            GUI_ID_BUTTON_KEY_S2,    8,  287,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "BUTTON",            GUI_ID_BUTTON_KEY_S3,    53, 287,37, 37, 0,0},
    { BUTTON_CreateIndirect,    "enter",             GUI_ID_BUTTON_KEY_ENT,   99, 291,160,36, 0,0},
    { BUTTON_CreateIndirect,    "cancel",            GUI_ID_BUTTON_KEY_CAN,   265,291,196,36, 0,0},
    { BUTTON_CreateIndirect,    "<Del",            GUI_ID_BUTTON_KEY_S4,    421,53, 37, 37, 0,0},


    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_CH,          8,  54, 234,31, 0,30}
};




/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog_Key(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}


/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog_Key(WM_MESSAGE * pMsg)
{
	int i;
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetFont(hWin,&GUI_FontHZ_SongTi_16);
    
    //
    //GUI_ID_TEXT_PY
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT_PY),&GUI_Font16_ASCII);
    //
    //GUI_ID_TEXT_CH
    //
	if(keyboard_win_h->work_state != CHINESE)
	{
	 EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT_CH),&GUI_Font16_ASCII);	
	}else{
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT_CH),&GUI_FontHZ_SongTi_16);
	}

	EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT_DATA),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON_KEY_CN
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_KEY_CN),&GUI_Font10_1);
    BUTTON_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_BUTTON_KEY_CN),GUI_TA_TOP|GUI_TA_CENTER);
    //
    //GUI_ID_BUTTON_KEY_BU
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON_KEY_BU),&GUI_Font10_ASCII);
	
//	EDIT_SetMaxLen(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_CH), 30);
//	EDIT_SetMaxLen(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_DATA), 30);
	
	Show_Work_State(pMsg);
}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback_Key(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog_Key(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog_Key(pMsg);
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
			
			 
				if((Id >= GUI_ID_BUTTON_KEY_A)&&(Id <= GUI_ID_BUTTON_KEY_Z))
				{
					if(NCode == WM_NOTIFICATION_CLICKED)
					{
					ID_A_Z(pMsg);
					break;
					}
				}else if((Id >= GUI_ID_BUTTON_KEY_0)&&(Id <= GUI_ID_BUTTON_KEY_9)){
					if(NCode == WM_NOTIFICATION_CLICKED)
					{
					ID_1_0(pMsg);
					break;
					}
				}
			else
			{
				switch (Id) 
				{
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_CLICKED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_CLICKED)
                        GUI_EndDialog(hWin, 0);
                    break;
				case GUI_ID_BUTTON_KEY_CAN:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
							
							OnCancleCliked(pMsg);
                            //OnxxxClicked(pMsg);
                            break;
                    }
			   
				case GUI_ID_BUTTON_KEY_CN:
					switch(NCode)
					{
						case WM_NOTIFICATION_CLICKED:
							ID_Key_CN(pMsg);
							break;	
					}
					break;

				case GUI_ID_BUTTON_KEY_RS:
					switch(NCode)
					{
						case WM_NOTIFICATION_CLICKED:
							ID_key_R(pMsg);
						break;
					}
					break;

				case GUI_ID_BUTTON_KEY_LS:
					switch(NCode)
					{
						case WM_NOTIFICATION_CLICKED:
						ID_key_L(pMsg);
						break;
					}
                    break;
				
				case GUI_ID_BUTTON_KEY_S4:
					switch(NCode)
					{
						case WM_NOTIFICATION_CLICKED:
						ID_key_S4(pMsg);
						break;
					
					}
					break;
				case GUI_ID_BUTTON_KEY_DT:
					switch(NCode)
					{
					case WM_NOTIFICATION_CLICKED:
					ID_DT(pMsg);
					break;
					}
					break;

				case GUI_ID_BUTTON_KEY_BU:
					switch(NCode)
					{
						case WM_NOTIFICATION_CLICKED:
						ID_KEY_BU(pMsg);
						break;
					}
					break;

					case  GUI_ID_BUTTON_KEY_ENT:
					switch(NCode)
					{
						case WM_NOTIFICATION_CLICKED:
						ID_KEY_ENTER(pMsg);
						break;
					}
					break;
				}
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
void KeyBoard_Win(TKeyBoard_H* keyboard_h) 
{ 
//	keyboard_win_h->pdata = data;
//	keyboard_win_h->pch_data = ch_data;

	keyboard_win_h = keyboard_h;
	
    WM_SetDesktopColor(GUI_WHITE);    /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
	KeyBoard_Win_Init();
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    //CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
    //DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
    //SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
    //SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    //HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
    //RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
    GUI_ExecDialogBox(_aDialogCreate_Key, GUI_COUNTOF(_aDialogCreate_Key), &_cbCallback_Key, 0, 200, 50);

}

