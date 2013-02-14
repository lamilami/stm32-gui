
#include"IO_I2C.h"


/*****************************************************************************
 �� �� ��  : delay_asm
 ��������  : ���ʵ�־�ȷ��ʱ��һ��ѭ����Ҫ6��ʱ������, ��һ��12-24����
                ϵͳʱ��72MHz--- 0.5us	----> i = 6
 �������  : int i  --> ��ʱѭ������
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming 
    �޸�����   : �����ɺ���

*****************************************************************************/
__asm void  delay_asm1(int i)
{
	subs    r0, #1   
    bne     delay_asm1
    bx      lr
} 

/*****************************************************************************
 �� �� ��  : IIC_Start
 ��������  : IIC�����ź�
 �������  : void  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

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
 �� �� ��  : IIC_Stop
 ��������  : IIC�����ź�
 �������  : void  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

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
 �� �� ��  : IIC_WriteByte
 ��������  : IICд��һ���ֽ�
 �������  : u8 txByte--> ��д����ֽ�
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

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
 �� �� ��  : IIC_ReadByte
 ��������  : IIC��ȡһ���ֽ�
 �������  : etI2cAck ack  ACK������Ӧ�ӻ� NO_ACK ��������Ӧ�ӻ�
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

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
 �� �� ��  : IIC_RegWrite
 ��������  : ����һ���Ĵ���
 �������  : u8 device_add  -->MMA845x�ĵ�ַ
             u8 reg         --> MMA8445x�ļĴ�����ַ
             u8 val         --> д����Ӧ�Ĵ�����ֵ
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

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
 �� �� ��  : IIC_RegRead
 ��������  : ��ȡ��һ���Ĵ�����ֵ
 �������  : u8 reg         -->MMA8445x�ļĴ�����ַ
 �������  : ��
 �� �� ֵ  : ��ȡ�ļĴ�����ֵ
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

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
 �� �� ��  : IIC_RegWriteN
 ��������  : ����д�����Ĵ���
 �������  : u8 reg1        -->Ҫд�����ʼ�ļĴ�����ַ
             u8 N           -->Ҫд��ļĴ�������
             u8 *array      -->д��Ĵ���ֵ�洢λ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

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
 �� �� ��  : IIC_RegReadN
 ��������  : ������ȡ����Ĵ�����ֵ
 �������  : u8 reg1        -->Ҫ����ʼ�ļĴ�����ַ
             u8 N           -->Ҫ����ʼ�ļĴ�������
             u8 *array      -->��ȡ�ļĴ���ֵ�洢λ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��10��5��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

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
 	