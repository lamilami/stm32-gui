#include"gui_app.h"
#include"rdprint.h"


void rdprint(char data)
{
#ifndef WIN_SIM
  USART_SendData(USART1,data);
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {
  }
  while(USART_ReceiveData(USART1) == PRINT_BUSY)
  {
  	OSTimeDlyHMSM(0,0,0,10);
  }
#endif

}

void print_ch(int loc, char* str_ch)
{
  int i,j;
  COMM_CHINESE(0);
  if(loc > -1)
  {
  COMM_F(0,loc);
  }
  j = strlen(str_ch);
  for(i=0;i<j;i++)
  {
   rdprint(str_ch[i]);
  }
}

void print_en(int loc, char* str_en,int print_lenth)
{
   int i,j;
   COMM_CHINESE(7);
   if(loc > -1)
   {
   COMM_F(0,loc);
   }
   if(print_lenth < 0)
   {
   j = strlen(str_en);
   }else{
   	j = print_lenth;
   }
   for(i=0;i<j;i++)
   {
    rdprint(str_en[i]);
   }
}

void print_data_time(void)
{
	char buf[50];
#ifndef WIN_SIM
  	RTC_Get_Time(&Tim);
	RTC_time_to_string(buf ,Tim);
	print_ch(0,buf);	
#endif

}

void print_custormer()
{
	char cus[]={"客户信息:"};
	char eser[]={"电梯序列号:"};
	char epro[]={"电梯制造商:"};
	char lmpro[]={"限速器制造商:"};
	char lmser[]={"限速器序列号:"};

 
	print_ch(0,cus);
	print_ch(0,custormer.custorm);
	COMM_LF;

	
	print_ch(0,eser);
	print_ch(0,custormer.series_no);
	COMM_LF;

	
	print_ch(0,epro);
	print_ch(0,custormer.elevator_productor);
	COMM_LF;


	print_ch(0,lmpro);
	print_ch(0,custormer.limitor_productor);
	COMM_LF;

	
	print_ch(0,lmser);
	print_ch(0,custormer.limitor_series);
}

