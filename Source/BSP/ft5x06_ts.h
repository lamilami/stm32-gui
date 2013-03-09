/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : i2c_ee.h
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : Header for i2c_ee.c module
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __I2C_EE_H
#define __I2C_EE_H
/* Includes ------------------------------------------------------------------*/
#include "gui_app.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define FT5x06_SDA      PBout(7) 
#define READ_SDA 		PBin(7) 
#define FT5x06_SCL 		PBout(6)


/* Address for each register */
#define FT5x06_CHIP_ID     0xA3

#define FW_VERSION         0xA6

#define CFG_MAX_TOUCH_POINTS  5
#define CFG_FTS_CTP_DRIVER_VERSION "3.0"

#define SCREEN_MAX_X    1024
#define SCREEN_MAX_Y    600
#define PRESS_MAX       255

/* Address for FT5x06 register */
#define	FT5X0X_REG_THGROUP					0x80     /* touch threshold, related to sensitivity */
#define	FT5X0X_REG_THPEAK						0x81
#define	FT5X0X_REG_THCAL						0x82
#define	FT5X0X_REG_THWATER					0x83
#define	FT5X0X_REG_THTEMP					0x84
#define	FT5X0X_REG_THDIFF						0x85				
#define	FT5X0X_REG_CTRL						0x86
#define	FT5X0X_REG_TIMEENTERMONITOR			0x87
#define	FT5X0X_REG_PERIODACTIVE				0x88      /* report rate */
#define	FT5X0X_REG_PERIODMONITOR			0x89
#define	FT5X0X_REG_HEIGHT_B					0x8a
#define	FT5X0X_REG_MAX_FRAME				0x8b
#define	FT5X0X_REG_DIST_MOVE				0x8c
#define	FT5X0X_REG_DIST_POINT				0x8d
#define	FT5X0X_REG_FEG_FRAME				0x8e
#define	FT5X0X_REG_SINGLE_CLICK_OFFSET		0x8f
#define	FT5X0X_REG_DOUBLE_CLICK_TIME_MIN	0x90
#define	FT5X0X_REG_SINGLE_CLICK_TIME		0x91
#define	FT5X0X_REG_LEFT_RIGHT_OFFSET		0x92
#define	FT5X0X_REG_UP_DOWN_OFFSET			0x93
#define	FT5X0X_REG_DISTANCE_LEFT_RIGHT		0x94
#define	FT5X0X_REG_DISTANCE_UP_DOWN			0x95
#define	FT5X0X_REG_ZOOM_DIS_SQR				0x96
#define	FT5X0X_REG_RADIAN_VALUE				0x97
#define	FT5X0X_REG_MAX_X_HIGH                       0x98
#define	FT5X0X_REG_MAX_X_LOW             			0x99
#define	FT5X0X_REG_MAX_Y_HIGH            			0x9a
#define	FT5X0X_REG_MAX_Y_LOW             			0x9b
#define	FT5X0X_REG_K_X_HIGH            			0x9c
#define	FT5X0X_REG_K_X_LOW             			0x9d
#define	FT5X0X_REG_K_Y_HIGH            			0x9e
#define	FT5X0X_REG_K_Y_LOW             			0x9f
#define	FT5X0X_REG_AUTO_CLB_MODE				0xa0
#define	FT5X0X_REG_LIB_VERSION_H 				0xa1
#define	FT5X0X_REG_LIB_VERSION_L 				0xa2		
#define	FT5X0X_REG_CIPHER						0xa3
#define	FT5X0X_REG_MODE							0xa4
#define	FT5X0X_REG_PMODE						0xa5	  /* Power Consume Mode		*/	
#define	FT5X0X_REG_FIRMID						0xa6 /* Firmware version */
#define	FT5X0X_REG_STATE						0xa7
#define	FT5X0X_REG_FT5201ID						0xa8
#define	FT5X0X_REG_ERR							0xa9
#define	FT5X0X_REG_CLB							0xaa

#define   FT5X0X_REG_TOUCH1_XH					0x03
#define   FT5X0X_REG_TOUCH1_XL					0x04
#define   FT5X0X_REG_TOUCH1_YH					0x05
#define   FT5X0X_REG_TOUCH1_YL					0x06
#define   FT5x06_ADD   0x76

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void FT5x06_GPIO_Config(void);
void FT5x06_Start (void);
void FT5x06_Stop(void);
unsigned char FT5x06_WriteByte (unsigned char txByte);
unsigned char FT5x06_ReadByte (etI2cAck ack);
void FT5x06_RegReadN(unsigned char reg1, unsigned char N, unsigned char *array);
void FT5x06_RegWriteN(unsigned char reg1,unsigned char N,unsigned char *array);

bool FT5x06_identify(void);
void FT5x06_init(void);
unsigned char FT_IIC_RegRead(unsigned char reg);
void FT5x06_GetData(int* x, int* y);

#endif /* __I2C_EE_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/


