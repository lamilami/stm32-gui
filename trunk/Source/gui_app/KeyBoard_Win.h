#ifndef KEYBOARD_WIN_H
#define KEYBOARD_WIN_H
#define DATA_SIZE 20
#define CH_DATA_SIZE 120

typedef enum work_state
{
 ENGLISH_S =0 ,
 ENGLISH_B = 1,
 CHINESE = 2,
// NUMBER =3
SFLOAT =3

}EWorkState;


typedef struct  KeyBoard_H
{
  EWorkState work_state;			//调用前切换为一种状态
  char* pdata_head;					//拼音字符串	
  char* pdata_end;
  char* pdata;

  char* pch_data_head;				//汉字字符串
  char* pch_data_end;
  char* pch_data;

  char* pnum_data_head;				//可选区 汉字字符串
  char* pnum_data_end;
  char* pnum_data;

  int  num_ch;

  char* res_ch_data_head;			//最终字符串
  char* res_ch_data_end;
  char* res_ch_data;

  char use_now;// 防止建立多个
	 
}TKeyBoard_H;

extern void KeyBoard_Win(TKeyBoard_H* keyboard_h) ;

#endif

