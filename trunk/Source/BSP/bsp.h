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
* Filename      : bsp.h
* Version       : V1.00
* Programmer(s) : Brian Nagel
*********************************************************************************************************
*/

#ifndef  __BSP_H__
#define  __BSP_H__

/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/
#include "stm32f10x.h"
#ifdef   BSP_GLOBALS
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif


#ifdef STM32F10X_XL
#define FLASH_PAGE_SIZE    ((uint16_t)0x800)
#define BANK511_WRITE_START_ADDR  ((uint32_t)0x080FF800)
#define BANK511_WRITE_END_ADDR   ((uint32_t)0x080FFFFF)
#endif

#ifdef STM32F10X_HD
#define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#define BANK511_WRITE_START_ADDR  ((uint32_t)0x0807F800)
#define BANK511_WRITE_END_ADDR   ((uint32_t)0x0807FFFF)
#endif
//#define TP_CS()  GPIO_ResetBits(GPIOB,GPIO_Pin_12)
//#define TP_DCS() GPIO_SetBits(GPIOB,GPIO_Pin_12)
/*
#define SetSCK() GPIO_SetBits(GPIOA,GPIO_Pin_5) 
#define ClearSCK() GPIO_ResetBits(GPIOA,GPIO_Pin_5) 
#define SetMOSI()  GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define ClearMOSI() GPIO_ResetBits(GPIOA,GPIO_Pin_7)
#define ReadMISO() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)*/
#define WaitTPReady() while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)

#define TOUCH_PRESSING    GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4)

#if defined  SDHC_TEST

void sdhc_test(void);
#endif
/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void BSP_Init(void);
void BSP_IntDisAll(void);
unsigned int  OS_CPU_SysTickClkFreq (void);
u16 TPReadX(void);
u16 TPReadY(void);
FLASH_Status flash_pro(uint32_t start_address, uint16_t* data,unsigned int lenth);
void  MMA845X_TIM6_Init(void);
void MMA845X_TIM6_interrupt_conf(FunctionalState status);


#endif                                                          /* End of module include.                               */
