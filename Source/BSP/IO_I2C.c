
#include"IO_I2C.h"


/*****************************************************************************
 函 数 名  : delay_asm
 功能描述  : 汇编实现精确延时，一次循环需要6个时钟周期, 仅一次12-24不等
                系统时钟72MHz--- 0.5us	----> i = 6
 输入参数  : int i  --> 延时循环个数
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年10月5日
    作    者   : ganjinming 
    修改内容   : 新生成函数

*****************************************************************************/
__asm void  delay_asm1(int i)
{
	subs    r0, #1   
    bne     delay_asm1
    bx      lr
} 

/*****************************************************************************
 函 数 名  : IIC_Start
 功能描述  : IIC启动信号
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年10月5日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
void IIC_Start (void)
{
	IIC_SDA=HIGH;
	IIC_SCL=HIGH;
	delay_asm1(6*2);
	IIC_SDA=LOW;
	delay_asm1(6*2);
	IIC_SCL=LOW;
	delay_asm1(6);
	
}
/*****************************************************************************
 函 数 名  : IIC_Stop
 功能描述  : IIC结束信号
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年10月5日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
void IIC_Stop (void)
{
	IIC_SDA=LOW;
	IIC_SCL=LOW;
	delay_asm1(6*2);
	IIC_SCL=HIGH;
	delay_asm1(6*2);
	IIC_SDA=HIGH;
	delay_asm1(6*4);
}

/*****************************************************************************
 函 数 名  : IIC_WriteByte
 功能描述  : IIC写入一个字节
 输入参数  : u8 txByte--> 待写入的字节
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年10月5日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 IIC_WriteByte (u8 txByte)
{
    u8 mask,erro=0;
    for (mask=0x80; mask>0; mask>>=1) 
    { 
	    if ((mask & txByte) == 0) IIC_SDA=LOW;
		else IIC_SDA=HIGH;
		delay_asm1(6);
		IIC_SCL=HIGH; 
		delay_asm1(6*3);
		IIC_SCL=LOW;
		delay_asm1(6*3);
    }
    IIC_SDA=HIGH; //release SDA-line
    IIC_SCL=HIGH; //clk #9 for ack
    delay_asm1(6*3);
	if(READ_SDA==HIGH) erro=ACK_ERROR;
    IIC_SCL=LOW;
	delay_asm1(6*3);
    return erro; //return error code
}

/*****************************************************************************
 函 数 名  : IIC_ReadByte
 功能描述  : IIC读取一个字节
 输入参数  : etI2cAck ack  ACK主机响应从机 NO_ACK 主机不响应从机
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年10月5日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 IIC_ReadByte (etI2cAck ack)
{
	u8 mask,rxByte=0;
	IIC_SDA=HIGH; 
	delay_asm1(6);
	for (mask=0x80; mask>0; mask>>=1) 
	{ 
	    IIC_SCL=HIGH; //start clock on SCL-line
		delay_asm1(6*3);
		if(READ_SDA==1) rxByte=(rxByte | mask); 
		IIC_SCL=LOW;
		delay_asm1(6*3);
	}
	IIC_SDA=ack; 
	delay_asm1(6);
	IIC_SCL=HIGH; //clk #9 for ack
	delay_asm1(6*3);
	IIC_SCL=LOW;
	IIC_SDA=HIGH;
	delay_asm1(6*3);
	return rxByte; 
}

/*****************************************************************************
 函 数 名  : IIC_RegWrite
 功能描述  : 配置一个寄存器
 输入参数  : u8 device_add  -->MMA845x的地址
             u8 reg         --> MMA8445x的寄存器地址
             u8 val         --> 写入响应寄存器的值
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年10月5日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
void IIC_RegWrite(u8 reg,u8 val,u8 DEVICE_ADD)
{
  IIC_Start();                                  
  IIC_WriteByte(DEVICE_ADD);                      
  IIC_WriteByte(reg);                         
  IIC_WriteByte(val);                         
  IIC_Stop();                               
}

/*****************************************************************************
 函 数 名  : IIC_RegRead
 功能描述  : 读取的一个寄存器的值
 输入参数  : u8 reg         -->MMA8445x的寄存器地址
 输出参数  : 无
 返 回 值  : 读取的寄存器的值
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年10月5日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 IIC_RegRead(u8 reg,u8 DEVICE_ADD)
{
  u8 b;
  IIC_Start();                                  
  IIC_WriteByte(DEVICE_ADD);                 
  IIC_WriteByte(reg);                        
  IIC_Start();                           
  IIC_WriteByte(DEVICE_ADD+1);                    
  b = IIC_ReadByte(NO_ACK);                                                
  IIC_Stop();                                 
  return b;
}


/*****************************************************************************
 函 数 名  : IIC_RegWriteN
 功能描述  : 连续写入多个寄存器
 输入参数  : u8 reg1        -->要写入的起始的寄存器地址
             u8 N           -->要写入的寄存器个数
             u8 *array      -->写入寄存器值存储位置
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年10月5日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
void IIC_RegWriteN(u8 reg1,u8 N,u8 *array,u8 DEVICE_ADD)
{                              
  IIC_Start();                                 
  IIC_WriteByte(DEVICE_ADD);                      
  IIC_WriteByte(reg1);                     
  while (N>0)                               
  {
    IIC_WriteByte(*array);
    array++;
    N--;
  }
  IIC_Stop();                                
}


/*****************************************************************************
 函 数 名  : IIC_RegReadN
 功能描述  : 连续读取多个寄存器的值
 输入参数  : u8 reg1        -->要读起始的寄存器地址
             u8 N           -->要读起始的寄存器个数
             u8 *array      -->读取的寄存器值存储位置
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年10月5日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
void IIC_RegReadN(u8 reg1, u8 N, u8 *array, u8 DEVICE_ADD)
{
  u8 b;
  IIC_Start();                                  
  IIC_WriteByte(DEVICE_ADD);                      
  IIC_WriteByte(reg1);                        
  IIC_Start();                           
  IIC_WriteByte(DEVICE_ADD+1);                    
  //b = IIC_ReadByte(ACK);                        
  while (N>1)                                   
  {
    b = IIC_ReadByte(ACK);
    *array = b;
    array++;
    N--;
  }
  b = IIC_ReadByte(NO_ACK);
  *array = b;                                   
  IIC_Stop();                                
}
 	