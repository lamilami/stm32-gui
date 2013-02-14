/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                             (c) Copyright 2007; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/
										  
/*
*********************************************************************************************************
*
*                                        BOARD SUPPORT PACKAGE
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   STM3210B-EVAL Evaluation Board
*
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : Brian Nagel
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  BSP_GLOBALS
#include <includes.h> 
#include "Touch.h"
#include "flash_AT45DB161D.H"
#include "rtc.h"
#include"MMA8452Q.h"

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
static volatile ErrorStatus HSEStartUpStatus = SUCCESS;

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void RCC_Config(void);
void GPIO_Config(void);
void FSMC_Config(void);
void IIC_Config(void);
void EXTI_Config(void);
void NVIC_Configuration(void) ;
void SPI_Config(void);
void UART_Config(void);



/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
******************************************************************************************************************************
******************************************************************************************************************************
**                                         Global Functions
******************************************************************************************************************************
******************************************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         BSP INITIALIZATION
*
* Description : This function should be called by your application code before you make use of any of the
*               functions found in this module.
*
* Arguments   : none
*********************************************************************************************************
*/
extern void GUI_Line(u16 x0, u16 y0, u16 x1, u16 y1,u16 color);
extern LCD_Clear(u16 c);
void  BSP_Init(void)
{
	unsigned int delay;
    /* Initialize the uC/OS-II tick interrupt    */
	RCC_Config();
	GPIO_Config();
	SPI_Config();
	UART_Config();
	FSMC_Config();
	Lcd_Init();
	
	MMA845x_Init();
	MMA845X_TIM6_Init(); 
	
//	SDCard_Init();
	disk_initialize(0);

	RTC_Config_Init();
  	
	EXTI_Config();
	NVIC_Configuration();

	SPI_Enc28j60_Init();
	tftp_init();
    
	GUI_Init();//��ʼ��GUI
	GUI_SetBkColor(GUI_BLACK);//���ñ�����ɫΪ��ɫ
	GUI_FillRect(0,0,320,240);//����
	LCD_Clear(GUI_BLACK);
	GUI_Line(1, 45, 80, 100,(u16)GUI_BLUE);
	
	GUI_DispString("Hello world!");
	LCD_Clear(GUI_WHITE);
//while(1);
//Touch_Configuration();
   	OS_CPU_SysTickInit();
  
  //spi_at45db161d_initial(); 
}

__asm void delay_asm (unsigned int i)
{
	subs R0, #1
	BNE  delay_asm
	BX LR
}

/*
*********************************************************************************************************
*                                     DISABLE ALL INTERRUPTS
*
* Description : This function disables all interrupts from the interrupt controller.
*
* Arguments   : None.
*
* Returns     : None.
*********************************************************************************************************
*/
void  BSP_IntDisAll (void)
{
  // CPU_IntDis();
}

/*
******************************************************************************************************************************
******************************************************************************************************************************
**                                         uC/OS-II Timer Functions
******************************************************************************************************************************
******************************************************************************************************************************
*/

void RCC_Config(void)
{
	 /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC 
                       | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE  | RCC_APB2Periph_AFIO, ENABLE);

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1,ENABLE); //����1
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2,ENABLE); //����2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,   ENABLE); //SPI1----������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,   ENABLE); //SPI2----����
	#ifndef RED_BULL  //��ţ������
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,   ENABLE); //SPI3----spi�ӿ�flash AT45DB161D
    #endif
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);	   //lcd

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,   ENABLE);	 //TIM4 
}





void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/************   ����1     ***************/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	//TX         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);		   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	 //RX       
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/**************  ����2    *******************/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//TX         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);		   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	 //RX       
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//#if defined	 RS485_EN
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //RS485����ѡ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    //Delay(200);
	//GPIO_ResetBits(GPIOA, GPIO_Pin_8);    
	//Delay(200);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);   
	
	//#endif

	/********   ����3   *******************/

	/****************  ������   SPI1  ******************/
  	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;  //Configure SPI1 pins: SCK, MISO and MOSI 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //�����������
  	GPIO_Init(GPIOA,&GPIO_InitStructure); 

	#ifdef RED_BULL  //��ţ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  //������Ƭѡ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	#else 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  //������Ƭѡ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	#endif

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;  //�������ж�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_Init(GPIOD, &GPIO_InitStructure); 

	/*************   ����  SPI2    ***********************/
  	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 	//Configure SPI2 pins: SCK, MISO and MOSI 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;   //�����������
  	GPIO_Init(GPIOA,&GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;  //�����ж�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_Init(GPIOD, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;  //����Ƭѡ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	#ifndef RED_BULL  //��ţ������
	/***********   AT45DB161D  SPI3    *********************/
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);    //JTAG-DP Disabled and SW-DP Enabled   
  	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;  //Configure SPI3 pins: SCK, MISO and MOSI
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   //�����������
  	GPIO_Init(GPIOB,&GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  //AT45DB161Ƭѡ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_Init(GPIOE, &GPIO_InitStructure);
    #endif

	/***********    ������    *******************/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	 
	/*********����IIC1	***********/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7|GPIO_Pin_4; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*********   SD��  *********************/
	     //��sdcard.c �ļ���
		 	 
    /****** TFT **********/
#if 0		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);

  	/* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
     PE.14(D11), PE.15(D12) as alternate function push pull */
  	GPIO_InitStructure.GPIO_Pin =  /*GPIO_Pin_6 |*/ GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                GPIO_Pin_15;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);

 	// GPIO_WriteBit(GPIOE, GPIO_Pin_6, Bit_SET);
  	/* Set PF.00(A0 (RS)) as alternate function push pull */
  	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  	//GPIO_Init(GPIOF, &GPIO_InitStructure);
  
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);

  	/* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */
  	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  	//GPIO_Init(GPIOG, &GPIO_InitStructure);
  
    /* Set (NE1 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  	//reset 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //RS485����ѡ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	TimeDelay(10);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);    
	TimeDelay(10);
	GPIO_SetBits(GPIOA, GPIO_Pin_8); 
#endif

   // AD5410 CS
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/**************TFT  ���ݵ�ַƬѡ   ���� TIM2��  **************/
	     /*===GPIO For the LCD_Bus======*/	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
  								GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 |
  								  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*===========GPIO For the Control========================*/
	/**	
 	*	PA0 -> Light  --����pwm����
 	*	PD4	-> OE	,	PD5	-> WE 
 	*	PD7	-> CS/NE1	,	PD13 -> RS 
 	*/	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_13;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	 
  	GPIO_Init(GPIOD, &GPIO_InitStructure); 
    delay_asm(10);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);    //ssd1963��λ
	delay_asm(10);
	GPIO_SetBits(GPIOA, GPIO_Pin_8); 
	
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);    //�򿪱���LED
	GPIO_SetBits(GPIOA, GPIO_Pin_0);    //�򿪱���LED


	//RTC
	//PWM

	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	 
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/***������������***/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6;		 //SW3_IN SW1_IN SW2_IN
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	 
  	GPIO_Init(GPIOE, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_4;		 //TIM3_CH1,TIM3_CH2
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	 
  	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}

void FSMC_Config(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  	FSMC_NORSRAMTimingInitTypeDef  p;

	/*-- FSMC Configuration ------------------------------------------------------*/
  	p.FSMC_AddressSetupTime = 0;
  	p.FSMC_AddressHoldTime = 0;
  	p.FSMC_DataSetupTime = 1;
  	p.FSMC_BusTurnAroundDuration = 0;
  	p.FSMC_CLKDivision = 0;
  	p.FSMC_DataLatency = 0;
  	p.FSMC_AccessMode = FSMC_AccessMode_B;

  	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;   //
  	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;	// �ر����߸���
  	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;		 //fsmc����ģʽ
  	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;   // ���ݿ��
  	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;  // �ر�ͻ������ģʽ
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;	//	�ȴ��ź�Ϊ�͵�ƽ
  	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;	   // �رջ���ģʽ
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState; //
  	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	   //  д����ʹ��
  	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;	   //	�رյȴ��ź�
  	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;	 //	�ر���չ��ʽ
 	// FSMC_NORSRAMInitStructure.FSMC_AsyncWait = FSMC_AsyncWait_Disable;	  // �ر��첽�ȴ� //gan 2012-07-22
  	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait =FSMC_AsynchronousWait_Disable;//gan 2012-07-22
  	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;	  // �ر�ͻ��д
  	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;		 //
  	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;		   //
  
  	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

  	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE); 	
}

void SPI_Config(void)
{
	SPI_InitTypeDef   SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
  	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
  	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 
  	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; 
 	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   
  	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; 
  	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
    SPI_InitStructure.SPI_CRCPolynomial = 7; 

	#ifdef RED_BULL  //��ţ������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; 		//36Mhz
	#endif
    SPI_Init(SPI1,&SPI_InitStructure); 
	
	SPI_Cmd(SPI1, ENABLE);//������

	SPI_Init(SPI2,&SPI_InitStructure);
	SPI_Cmd(SPI2, ENABLE);	//���ڣ����ô���

    #ifndef RED_BULL  //��ţ������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; 
	SPI_Init(SPI3,&SPI_InitStructure); 
  	SPI_Cmd(SPI3,ENABLE); 	//at45db161d
	#endif
}

void UART_Config(void)
{
	USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 

//  USART_ClearITPendingBit(USART1,USART_FLAG_TC);
//	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

	USART_Cmd(USART1, ENABLE);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_Cmd(USART2, ENABLE);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_Cmd(USART3, ENABLE);
}


void TIM3_Encoder_Init(void)
{
/*
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;


	TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaling 
	TIM_TimeBaseStructure.TIM_Period = 10000; //	 max=65536
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;//ICx_FILTER;
	TIM_ICInit(TIM8, &TIM_ICInitStructure);

	// Clear all pending interrupts
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	//Reset counter
	TIM4->CNT = 0;

	TIM_Cmd(TIM4, ENABLE); 	
	*/
}


void IIC_Config(void)
{

}



/*�����ж�����*/
void EXTI_Config(void)
{

}


void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  	int i;
  	static const uint8_t NVIC_IntSet[] = 
  	{
	  SDIO_IRQn,        1, 1
    };

	/* ������3, ��Preemption = 0 ~ 7   subpriority = 0 ~ 1 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
  
	for (i = 0; i < sizeof(NVIC_IntSet); i += 3) 
	{
		NVIC_InitStructure.NVIC_IRQChannel = NVIC_IntSet[i];
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IntSet[i + 1];
       	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IntSet[i + 2];
      	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
      	NVIC_Init(&NVIC_InitStructure);
  	}	  

}


INT32U  OS_CPU_SysTickClkFreq (void)
{	 
	RCC_ClocksTypeDef  rcc_clocks;

    RCC_GetClocksFreq(&rcc_clocks);

    return ((INT32U)rcc_clocks.HCLK_Frequency);
}

/*
unsigned char SPI_WriteByte(unsigned char data) 
{ 
 unsigned char Data = 0; 

   //Wait until the transmit buffer is empty 
  while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET); 
  // Send the byte  
  SPI_I2S_SendData(SPI2,data); 

   //Wait until a data is received 
  while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET); 
  // Get the received data 
  Data = SPI_I2S_ReceiveData(SPI2); 

  // Return the shifted data 
  return Data; 
}  
void SpiDelay(unsigned int DelayCnt)
{
 unsigned int i;
 for(i=0;i<DelayCnt;i++);
}

u16 TPReadX(void)
{ 
   u16 x=0;
   TP_CS();
   SpiDelay(10);
   SPI_WriteByte(0x90);
   SpiDelay(10);
   x=SPI_WriteByte(0x00);
   x<<=8;
   x+=SPI_WriteByte(0x00);
   SpiDelay(10);
   TP_DCS(); 
   x = x>>3;
   return (x);
}

u16 TPReadY(void)
{
 u16 y=0;
  TP_CS();
  SpiDelay(10);
  SPI_WriteByte(0xD0);
  SpiDelay(10);
  y=SPI_WriteByte(0x00);
  y<<=8;
  y+=SPI_WriteByte(0x00);
  SpiDelay(10);
  TP_DCS();
  y = y>>3; 
  return (y);
}	*/


FLASH_Status flash_pro(uint32_t start_address, uint16_t* data,unsigned int lenth)
{
  unsigned int i;
  FLASH_Status  flash_status;
  
  #ifdef STM32F10X_XL
  FLASH_UnlockBank2();
  #endif

  #ifdef STM32F10X_HD
  FLASH_UnlockBank1();
  #endif

  flash_status = FLASH_ErasePage(BANK511_WRITE_START_ADDR );
  if( flash_status != FLASH_COMPLETE)
  return flash_status;

  for(i=0;i<lenth;i++)
  {
  flash_status = FLASH_ProgramHalfWord(start_address+i*2, data[i]);
  if( flash_status != FLASH_COMPLETE)
  return flash_status;
  }

  #ifdef STM32F10X_XL
  FLASH_LockBank2();
  #endif

  #ifdef STM32F10X_HD
  FLASH_LockBank1();
  #endif

  return flash_status;
}

void  MMA845X_TIM6_Init(void)
{
    TIM_TimeBaseInitTypeDef  tim_init;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	  //TIM2 --36MHZ  -- 72MHZ
    tim_init.TIM_Period        = 1000 - 1;			  // 800HZ
    tim_init.TIM_Prescaler     = 90 -1;	   //36M/45 = 0.8M
    tim_init.TIM_ClockDivision = 0x0;
    tim_init.TIM_CounterMode   = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM6, &tim_init);
    TIM_SetCounter(TIM6, 0);
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM6, ENABLE);
}

void MMA845X_TIM6_interrupt_conf(FunctionalState status)
{
	TIM_ITConfig(TIM6, TIM_IT_Update, status);
}




