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
  EWorkState work_state;			//����ǰ�л�Ϊһ��״̬
  char* pdata_head;					//ƴ���ַ���	
  char* pdata_end;
  char* pdata;

  char* pch_data_head;				//�����ַ���
  char* pch_data_end;
  char* pch_data;

  char* pnum_data_head;				//��ѡ�� �����ַ���
  char* pnum_data_end;
  char* pnum_data;

  int  num_ch;

  char* res_ch_data_head;			//�����ַ���
  char* res_ch_data_end;
  char* res_ch_data;

  char use_now;// ��ֹ�������
	 
}TKeyBoard_H;

extern void KeyBoard_Win(TKeyBoard_H* keyboard_h) ;

#endif

