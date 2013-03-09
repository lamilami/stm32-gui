/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : i2c_ee.c
* Author             : MCD Application Team
* Version            : V2.0.1
* Date               : 06/13/2008
* Description        : This file provides a set of functions needed to manage the
*                      communication between I2C peripheral and I2C M24C08 EEPROM.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "ft5x06_ts.h"
#include "MMA8452Q.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : FT5x06_GPIO_Config
* Description    : Configure the used I/O ports pin
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FT5x06_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
  /* Configure I2C1 pins: SCL and SDA */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
}

#if 1


/*****************************************************************************
 函 数 名  : FT5x06_Start
 功能描述  : IIC启动信号
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月25日
    作    者   : SiminLee
    修改内容   : 新生成函数

*****************************************************************************/
void FT5x06_Start (void)
{
	FT5x06_SDA=HIGH;
	FT5x06_SCL=HIGH;
	delay_asm1(6*2);
	FT5x06_SDA=LOW;
	delay_asm1(6*2);
	FT5x06_SCL=LOW;
	delay_asm1(6);
	
}
/*****************************************************************************
 函 数 名  : FT5x06_Stop
 功能描述  : IIC结束信号
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月25日
    作    者   : SiminLee
    修改内容   : 新生成函数

*****************************************************************************/
void FT5x06_Stop (void)
{
	FT5x06_SDA=LOW;
	FT5x06_SCL=LOW;
	delay_asm1(6*2);
	FT5x06_SCL=HIGH;
	delay_asm1(6*2);
	FT5x06_SDA=HIGH;
	delay_asm1(6*4);
}

/*****************************************************************************
 函 数 名  : FT5x06_WriteByte
 功能描述  : IIC写入一个字节
 输入参数  : u8 txByte--> 待写入的字节
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月25日
    作    者   : SiminLee
    修改内容   : 新生成函数

*****************************************************************************/
u8 FT5x06_WriteByte (u8 txByte)
{
    u8 mask,erro=0;
    for (mask=0x80; mask>0; mask>>=1) 
    { 
	    if ((mask & txByte) == 0) FT5x06_SDA=LOW;
		else FT5x06_SDA=HIGH;
		delay_asm1(6);
		FT5x06_SCL=HIGH; 
		delay_asm1(6*3);
		FT5x06_SCL=LOW;
		delay_asm1(6*3);
    }
    FT5x06_SDA=HIGH; //release SDA-line
    FT5x06_SCL=HIGH; //clk #9 for ack
    delay_asm1(6*3);
	if(READ_SDA==HIGH) erro=ACK_ERROR;
    FT5x06_SCL=LOW;
	delay_asm1(6*3);
    return erro; //return error code
}

/*****************************************************************************
 函 数 名  : FT5x06_ReadByte
 功能描述  : IIC读取一个字节
 输入参数  : etI2cAck ack  ACK主机响应从机 NO_ACK 主机不响应从机
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月25日
    作    者   : SiminLee
    修改内容   : 新生成函数

*****************************************************************************/
u8 FT5x06_ReadByte (etI2cAck ack)
{
	u8 mask,rxByte=0;
	FT5x06_SDA=HIGH; 
	delay_asm1(6);
	for (mask=0x80; mask>0; mask>>=1) 
	{ 
	    FT5x06_SCL=HIGH; //start clock on SCL-line
		delay_asm1(6*3);
		if(READ_SDA==1) rxByte=(rxByte | mask); 
		FT5x06_SCL=LOW;
		delay_asm1(6*3);
	}
	FT5x06_SDA=ack; 
	delay_asm1(6);
	FT5x06_SCL=HIGH; //clk #9 for ack
	delay_asm1(6*3);
	FT5x06_SCL=LOW;
	FT5x06_SDA=HIGH;
	delay_asm1(6*3);
	return rxByte; 
}

/*****************************************************************************
 函 数 名  : IIC_RegWrite
 功能描述  : 配置FT5x06的一个寄存器
 输入参数  : u8 device_add  -->FT5x06的地址
             u8 reg         --> FT5x06的寄存器地址
             u8 val         --> 写入响应寄存器的值
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月25日
    作    者   : SiminLee
    修改内容   : 新生成函数

*****************************************************************************/
void FT5x06_RegWrite(u8 reg,u8 val)
{
  FT5x06_Start();                                  
  FT5x06_WriteByte(FT5x06_ADD);                      
  FT5x06_WriteByte(reg);                         
  FT5x06_WriteByte(val);                         
  FT5x06_Stop();                               
}

/*****************************************************************************
 函 数 名  : FT_IIC_RegRead
 功能描述  : 读取FT5x06的一个寄存器的值
 输入参数  : u8 reg         -->FT5x06的寄存器地址
 输出参数  : 无
 返 回 值  : 读取的寄存器的值
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月25日
    作    者   : SiminLee
    修改内容   : 新生成函数

*****************************************************************************/
u8 FT_IIC_RegRead(u8 reg)
{
  u8 b;
  FT5x06_Start();                                  
  FT5x06_WriteByte(FT5x06_ADD);                 
  FT5x06_WriteByte(reg);                        
  FT5x06_Start();                           
  FT5x06_WriteByte(FT5x06_ADD+1);                    
  b = FT5x06_ReadByte(NO_ACK);                                                
  FT5x06_Stop();                                 
  return b;
}


/*****************************************************************************
 函 数 名  : IIC_RegWriteN
 功能描述  : 连续写入FT5x06的多个寄存器
 输入参数  : u8 reg1        -->要写入的起始的寄存器地址
             u8 N           -->要写入的寄存器个数
             u8 *array      -->写入寄存器值存储位置
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月25日
    作    者   : SiminLee
    修改内容   : 新生成函数

*****************************************************************************/
void FT5x06_RegWriteN(u8 reg1,u8 N,u8 *array)
{                              
  FT5x06_Start();                                 
  FT5x06_WriteByte(FT5x06_ADD);                      
  FT5x06_WriteByte(reg1);                     
  while (N>0)                               
  {
    FT5x06_WriteByte(*array);
    array++;
    N--;
  }
  FT5x06_Stop();                                
}


/*****************************************************************************
 函 数 名  : FT5x06_RegReadN
 功能描述  : 连续读取FT5x06的多个寄存器的值
 输入参数  : u8 reg1        -->要读起始的寄存器地址
             u8 N           -->要读起始的寄存器个数
             u8 *array      -->读取的寄存器值存储位置
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年2月25日
    作    者   : SiminLee
    修改内容   : 新生成函数

*****************************************************************************/
void FT5x06_RegReadN(u8 reg1, u8 N, u8 *array)
{
  u8 b;
  FT5x06_Start();                                  
  FT5x06_WriteByte(FT5x06_ADD);                      
  FT5x06_WriteByte(reg1);                        
  FT5x06_Start();                           
  FT5x06_WriteByte(FT5x06_ADD+1);                    
  //b = IIC_ReadByte(ACK);                        
  while (N>1)                                   
  {
    b = FT5x06_ReadByte(ACK);
    *array = b;
    array++;
    N--;
  }
  b = FT5x06_ReadByte(NO_ACK);
  *array = b;                                   
  FT5x06_Stop();                                
}
/*******************************************************************************
* Function Name  : FT5x06_identify
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
bool FT5x06_identify(void)
{
	int id,ver;
	id = FT_IIC_RegRead(FT5X0X_REG_CIPHER);
	if (id != FT5x06_CHIP_ID) {
		printf("ID %d not supported\r\n", id);
		return 0;
	}
	ver = FT_IIC_RegRead(FT5X0X_REG_FIRMID);
	if (ver < 0) {
		printf("could not read the firmware version\r\n");
		return 0;
	}

	printf("FT5x06 firmware version %d\r\n", ver);

	return 1;

}
/*******************************************************************************
* Function Name  : FT5x06_interrupt
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FT5x06_GetData(int* x, int* y)
{

	static int Xposition_H,Xposition_L,Yposition_H,Yposition_L,Xposition,Yposition;

//	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
//	if(TOUCH_PRESSING == 0)
	{
		  Xposition_H=FT_IIC_RegRead(FT5X0X_REG_TOUCH1_XH);
		  Xposition_L=FT_IIC_RegRead(FT5X0X_REG_TOUCH1_XL);
		  Xposition = (Xposition_H&0x0f)*256+Xposition_L;
		  Yposition_H=FT_IIC_RegRead(FT5X0X_REG_TOUCH1_YH);
		  Yposition_L=FT_IIC_RegRead(FT5X0X_REG_TOUCH1_YL);
		  Yposition = (Yposition_H&0x0f)*256+Yposition_L;

		  *x = Xposition;
		  *y = 480 - Yposition;

		  //printf("Xposition= [%d],Yposition = [%d]\r\n", Xposition,Yposition);
		    /* Clear the EXTI Line 4 */
//		  EXTI_ClearITPendingBit(EXTI_Line4);
  	}	
}
/*******************************************************************************
* Function Name  : FT5x06_init
* Description    : Init FT5x06
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FT5x06_init(void)
{
	FT5x06_GPIO_Config();
	printf("[FTS] ft5x0x_ts_probe, driver version is %s.\r\n", CFG_FTS_CTP_DRIVER_VERSION);
	if(!FT5x06_identify())
	{
		printf("[FTS] ==identify failed =\r\n");	
	}
	else
	{
		printf("[FTS] ==init over =\r\n");
	}
}

#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
