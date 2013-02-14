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
#include "KeyBoard.h"

#include "LCD_ConfDefaults.h"      /* valid LCD configuration */
#include "pinyin/PY_DEF.h"

#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))

static int langue = 0;	//0表示中文，1表示英文
static int left_flag = 0;	//1表示当前条目左侧有未显示汉字
static int right_flag = 0;	//1表示当前条目右侧有未显示汉字

static char _acText[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '='
                          ,0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'P'
                          ,0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'q'
                          ,0, 'z', 'x', 'c', 'v', 'b', 'n', 'm', '<', '>', '*'
                          ,' ', ' ', ' ', ' ', ' ', 0, 0 };


extern const GUI_FONT GUI_FontHZ_SongTi_16;

int WaitKey(void) {
	int r = 0;
	int tMax = GUI_GetTime() + 1000;
	int tDiff;
	while (1)
	{
		GUI_Delay(10);
		if ((r = GUI_GetKey()) != 0)
		{
			break;
		}
	}
	return r;
}


int ExecKeyboard(char *sget) {
																								
	int i;
	int Key;
    char sDest[15];
	char buf[256];
	char text_buf[1024];
	char hz_buf[512];
	int off=0;
	int hz_num;
	int hz_off;
	int text_off;

	TEXT_Handle ahText[2];
	BUTTON_Handle ahButton[52];
	BUTTON_Handle hButtonESC;
	EDIT_Handle   hEdit;
	GUI_RECT rText = {000,0, LCD_XSIZE, 20};
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	//GUI_DrawBitmap(&bmMicriumLogo, 0, 0);
	GUI_SetFont(&GUI_FontHZ_SongTi_16);
	GUI_SetColor(GUI_BLUE);
	GUI_DispStringInRect("GUI", &rText, GUI_TA_RIGHT | GUI_TA_VCENTER);
	rText.y0 +=20;
	rText.y1 +=20;
	GUI_DispStringInRect("T9 demo", &rText, GUI_TA_RIGHT | GUI_TA_VCENTER);

	ahText[0] = TEXT_Create( rText.x0+10, rText.y0, 160, 18, GUI_ID_TEXT0, WM_CF_SHOW ,"",TEXT_CF_LEFT | TEXT_CF_BOTTOM );
	TEXT_SetFont(ahText[0],&GUI_FontHZ_SongTi_16);
	rText.y0 +=20;
	rText.y1 +=20;
	ahText[1] = TEXT_Create( rText.x0+10, rText.y0, 200, 18, GUI_ID_TEXT0, WM_CF_SHOW ,"",TEXT_CF_LEFT | TEXT_CF_BOTTOM );
	TEXT_SetFont(ahText[1],&GUI_FontHZ_SongTi_16);
	TEXT_SetTextColor(ahText[1],GUI_RED);
     
     
	/* Create Keyboard Buttons */
	for (i=0; i< 51; i++) 
	{
		int Pos = (i < 47) ? i : i+4;
		int x0 = 5  + 28*(Pos%11);
		int y0 = 100 + 28*(Pos/11);
		char c = _acText[i];
		int Id = c ? c : 1;
		char ac[2] = {0};
		char *s= ac;
		ac[0] = c;
		ahButton[i] = BUTTON_Create( x0, y0, 25, 25, Id,BUTTON_CF_SHOW );
		BUTTON_SetText   (ahButton[i], s);
	#if GUI_SUPPORT_MEMDEV
		BUTTON_EnableMemdev(ahButton[i]);
	#endif
	}

	BUTTON_SetText   (ahButton[43], "CN");
	
	ahButton[i] = BUTTON_Create( 89, 212, 109, 25, '#',BUTTON_CF_SHOW );
	BUTTON_SetFont(ahButton[i],&GUI_FontHZ_SongTi_16);	
	BUTTON_SetText(ahButton[i], "确定");
	
	hButtonESC = BUTTON_Create( 230, 40, 80, 25, GUI_ID_CANCEL,BUTTON_CF_SHOW );
	BUTTON_SetText   (hButtonESC, "ESC");
	hEdit = EDIT_Create( 5, 70, 310, 25, ' ', 80, 0 );
	EDIT_SetFont(hEdit, &GUI_FontHZ_SongTi_16);
	BUTTON_SetBkColor(ahButton[49], 0, GUI_RED);
	BUTTON_SetBkColor(ahButton[50], 0, GUI_BLUE);


	for (off=0;off<512;off++)
	{
		hz_buf[off]=0;
	}

	for (off=0;off<1024;off++)
	{
		text_buf[off]=0;
	}
	text_off = 0;
	for (off=0;off<256;off++)
	{
		buf[off]=0;
	}
	off=0;
	langue = 0;
	/* Handle Keyboard until ESC or ENTER is pressed */
	do 
	{
		Key = WaitKey();

		switch (Key)
		{
		case '*':			
			if(langue ==0)
			{
				langue = 1;
				BUTTON_SetText   (ahButton[43], "EN");				
			}
			else
			{
				langue = 0;
				BUTTON_SetText   (ahButton[43], "CN");
			}
			TEXT_SetBkColor(ahText[0],GUI_WHITE);
			TEXT_SetText(ahText[0],"");
			TEXT_SetBkColor(ahText[1],GUI_WHITE);
			TEXT_SetText(ahText[1],"");
			for (off=0;off<512;off++)
			{
				hz_buf[off]=0;
			}

			for (off=0;off<256;off++)
			{
				buf[off]=0;
			}
			off=0;
			hz_off =0 ;
			hz_num = 0;	
			break;				
		case 0:
		case GUI_ID_CANCEL:	
			TEXT_SetBkColor(ahText[0],GUI_WHITE);
			TEXT_SetText(ahText[0],"");
			TEXT_SetBkColor(ahText[1],GUI_WHITE);
			TEXT_SetText(ahText[1],"");
			for (off=0;off<512;off++)
			{
				hz_buf[off]=0;
			}

			for (off=0;off<256;off++)
			{
				buf[off]=0;
			}
			for (off=0;off<1024;off++)
			{
				text_buf[off]=0;
			}
			text_off = 0;
			off=0;
			hz_off =0 ;
			hz_num = 0;	
			break;				
		case '#':

			EDIT_GetText(hEdit, sget, 10);
			goto end;
			break;	
			
		default:
			if (((Key>='a')&&(Key<='z')) || ((Key>='A')&&(Key<='Z')) || ((Key>='1')&&(Key<='7')))
			{
				if(langue == 0)//中文
				{		
					int j;
					char *ptr;
					char buf_view[128];
					if(Key == '1')
					{
						if(left_flag == 1)
						{
							if(hz_off%5 == 0)
								hz_off -= 5;
							else
								hz_off = hz_off - (hz_off%5);
							
							hz_off -= 5;
							
							right_flag = 1;
							
							if(hz_off >= 5)
							{
								buf_view[0] = '1';
								buf_view[1] = '<';
								buf_view[2] = ' ';
								for (j = 0; j < 5;j++)
								{
									buf_view[j*4+3] = j+'2';
									buf_view[j*4+4] = hz_buf[(hz_off)*2];
									buf_view[j*4+5] = hz_buf[(hz_off)*2+1];
									buf_view[j*4+6] = ' ';
									hz_off++;
								}

								buf_view[23] = '7';
								buf_view[24] = '>';
								buf_view[25] = 0;
								left_flag = 1;
							}
							else
							{	
								left_flag = 0;
								for (j = 0; j < 5;j++)
								{
									buf_view[j*4+0] = j+'1';
									buf_view[j*4+1] = hz_buf[(hz_off)*2];
									buf_view[j*4+2] = hz_buf[(hz_off)*2+1];
									buf_view[j*4+3] = ' ';
									hz_off++;
								}

								buf_view[20] = '6';
								buf_view[21] = '>';
								buf_view[22] = 0;
								buf_view[23] = 0;
								buf_view[24] = 0;
							}
						}
						else
						{
							text_buf[text_off++]=hz_buf[0];
							text_buf[text_off++]=hz_buf[1];
							text_buf[text_off]=0;						
							EDIT_SetText(hEdit,text_buf);
						}
						TEXT_SetText(ahText[1],buf_view);
					}			
					else if(Key == '6')
					{
						if(left_flag == 1)
						{
							if(hz_off%5 == 0)
							{							
								text_buf[text_off++]=hz_buf[(hz_off - 1)*2];
								text_buf[text_off++]=hz_buf[(hz_off - 1)*2+1];
							}
							text_buf[text_off]=0;
							EDIT_SetText(hEdit,text_buf);
						}
						else
						{
							if(right_flag == 1)	//1表示当前条目右侧有未显示汉字
							{
								left_flag = 1;
								buf_view[0] = '1';
								buf_view[1] = '<';
								buf_view[2] = ' ';		
								if ((hz_off +5) >= hz_num )
								{
									int k = hz_num - hz_off;
									for (j = 0; j < k;j++)
									{
										buf_view[j*4+3] = j+'2';
										buf_view[j*4+4] = hz_buf[(hz_off)*2];
										buf_view[j*4+5] = hz_buf[(hz_off)*2+1];
										buf_view[j*4+6] = ' ';
										hz_off++;
									}
									buf_view[k*4+3] = 0;	
									right_flag = 0;
								}
								else
								{
									for (j = 0; j < 5;j++)
									{
										buf_view[j*4+3] = j+'2';
										buf_view[j*4+4] = hz_buf[(hz_off)*2];
										buf_view[j*4+5] = hz_buf[(hz_off)*2+1];
										buf_view[j*4+6] = ' ';
										hz_off++;
									}
									buf_view[23] = '7';
									buf_view[24] = '>';
									buf_view[25] = 0;
									right_flag = 1;
								}
							}
						}
						
						TEXT_SetText(ahText[1],buf_view);						
					}
					else if(Key == '7')
					{
						if((left_flag == 1)&&(right_flag == 1))
						{
							left_flag = 1;
							buf_view[0] = '1';
							buf_view[1] = '<';
							buf_view[2] = ' ';		
							if ((hz_off +5) >= hz_num )
							{
								int k = hz_num - hz_off;
								for (j = 0; j < k;j++)
								{
									buf_view[j*4+3] = j+'2';
									buf_view[j*4+4] = hz_buf[(hz_off)*2];
									buf_view[j*4+5] = hz_buf[(hz_off)*2+1];
									buf_view[j*4+6] = ' ';
									hz_off++;
								}
								buf_view[k*4+3] = 0;	
								right_flag = 0;
							}
							else
							{
								for (j = 0; j < 5;j++)
								{
									buf_view[j*4+3] = j+'2';
									buf_view[j*4+4] = hz_buf[(hz_off)*2];
									buf_view[j*4+5] = hz_buf[(hz_off)*2+1];
									buf_view[j*4+6] = ' ';
									hz_off++;
								}
								buf_view[23] = '7';
								buf_view[24] = '>';
								buf_view[25] = 0;
								right_flag = 1;
							}
						}						
						TEXT_SetText(ahText[1],buf_view);
					}
					else if((Key>='2')&&(Key<='5'))
					{
						if(left_flag == 1)
						{
							if(hz_off%5 == 0)
							{
								text_buf[text_off++]=hz_buf[(Key-'2' + hz_off - 5)*2];
								text_buf[text_off++]=hz_buf[(Key-'2' + hz_off - 5)*2+1];
							}
							else
							{
								text_buf[text_off++]=hz_buf[(Key-'2' + (hz_off/5)*5)*2];
								text_buf[text_off++]=hz_buf[(Key-'2' + (hz_off/5)*5)*2+1];
							}
							text_buf[text_off]=0;						
							EDIT_SetText(hEdit,text_buf);
						}
						else
						{
							text_buf[text_off++]=hz_buf[(Key-'1')*2];
							text_buf[text_off++]=hz_buf[(Key-'1')*2+1];
							text_buf[text_off]=0;						
							EDIT_SetText(hEdit,text_buf);
						}
					}
					else
					{			
						//extern char *PYSearch_all(unsigned char *msg,int *num);
						TEXT_SetBkColor(ahText[0],GUI_LIGHTGRAY);
						buf[off++]= Key;
						TEXT_SetText(ahText[0],buf);
						ptr = PYSearch(buf,&hz_num);
						if (ptr != '\0')
						{
							for (j = 0; j<hz_num*2;j++)
							{
								hz_buf[j] = *ptr++;
							}
							hz_buf[hz_num*2] = 0;
							hz_off = 0;
							TEXT_SetBkColor(ahText[1],GUI_LIGHTGRAY);
							
							if (hz_off < hz_num)
							{
								left_flag = 0;	//1表示当前条目左侧有未显示汉字

								if ((hz_off +5) >= hz_num )
								{
									int k = hz_num - hz_off;
									for (j = 0; j < k;j++)
									{
										buf_view[j*4+0] = j+'1';
										buf_view[j*4+1] = hz_buf[(hz_off)*2];
										buf_view[j*4+2] = hz_buf[(hz_off)*2+1];
										buf_view[j*4+3] = ' ';
										hz_off++;
									}
									buf_view[k*4] = 0;									
								}
								else
								{
									for (j = 0; j < 5;j++)
									{
										buf_view[j*4+0] = j+'1';
										buf_view[j*4+1] = hz_buf[(hz_off)*2];
										buf_view[j*4+2] = hz_buf[(hz_off)*2+1];
										buf_view[j*4+3] = ' ';
										hz_off++;
									}
									buf_view[20] = '6';
									buf_view[21] = '>';
									buf_view[22] = 0;
									
									right_flag = 1;	//1表示当前条目右侧有未显示汉字
								}
							}

							TEXT_SetText(ahText[1],buf_view);
						}
						else
						{
							TEXT_SetBkColor(ahText[1],GUI_WHITE);
							TEXT_SetText(ahText[1],"");
						}
					}
				}
				else
				{
					text_buf[text_off++]=Key;
					text_buf[text_off]=0;
					EDIT_SetText(hEdit,text_buf);
					
					//EDIT_AddKey(hEdit, Key);
				}
			}
		}
	} while ((Key!=GUI_ID_CANCEL) && (Key!=0));
	/* Cleanup */
end:	
	for (i=0; i< countof(ahButton); i++)
	{
		BUTTON_Delete(ahButton[i]);
	}
	BUTTON_Delete(hButtonESC);
	EDIT_Delete(hEdit);
	return Key;
}




