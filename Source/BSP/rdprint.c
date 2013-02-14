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