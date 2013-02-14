
#include"CTPM.h"
#include"math.h"

void IIC_CTPM_Start (void)
{
	IIC_CTPM_SDA=HIGH;
	IIC_CTPM_SCL=HIGH;
	delay_asm1(6*2);
	IIC_CTPM_SDA=LOW;
	delay_asm1(6*2);
	IIC_CTPM_SCL=LOW;
	delay_asm1(6);
}


void IIC_CTPM_Stop(void){

  	IIC_CTPM_SDA=LOW;
	IIC_CTPM_SCL=LOW;
	delay_asm1(6*2);
	IIC_CTPM_SCL=HIGH;
	delay_asm1(6*2);
	IIC_CTPM_SDA=HIGH;
	delay_asm1(6*4);

}


u8 IIC_CTPM_WriteByte (u8 txByte){

	    u8 mask,erro=0;
    for (mask=0x80; mask>0; mask>>=1) 
    { 
	    if ((mask & txByte) == 0) IIC_CTPM_SDA=LOW;
		else IIC_CTPM_SDA=HIGH;
		delay_asm1(6);
		IIC_CTPM_SCL=HIGH; 
		delay_asm1(6*3);
		IIC_CTPM_SCL=LOW;
		delay_asm1(6*3);
    }
    IIC_CTPM_SDA=HIGH; //release SDA-line
    IIC_CTPM_SCL=HIGH; //clk #9 for ack
    delay_asm1(6*3);
	if(READ_CTPM_SDA==HIGH) erro=ACK_ERROR;
    IIC_CTPM_SCL=LOW;
	delay_asm1(6*3);
    return erro; //return error code
}


u8 IIC_CTPM_ReadByte (etI2cAck ack){

   	u8 mask,rxByte=0;
	IIC_CTPM_SDA=HIGH; 
	delay_asm1(6);
	for (mask=0x80; mask>0; mask>>=1) 
	{ 
	    IIC_CTPM_SCL=HIGH; //start clock on SCL-line
		delay_asm1(6*3);
		if(READ_CTPM_SDA==1) rxByte=(rxByte | mask); 
		IIC_CTPM_SCL=LOW;
		delay_asm1(6*3);
	}
	IIC_CTPM_SDA=ack; 
	delay_asm1(6);
	IIC_CTPM_SCL=HIGH; //clk #9 for ack
	delay_asm1(6*3);
	IIC_CTPM_SCL=LOW;
	IIC_CTPM_SDA=HIGH;
	delay_asm1(6*3);
	return rxByte; 
}

void IIC_CTPM_RegWrite(u8 reg,u8 val)
{
  IIC_CTPM_Start();                                  
  IIC_CTPM_WriteByte(DEVICE_ADD);                      
  IIC_CTPM_WriteByte(reg);                         
  IIC_CTPM_WriteByte(val);                         
  IIC_CTPM_Stop(); 
}


u8 IIC_CTPM_RegRead(u8 reg){

  u8 b;
  IIC_CTPM_Start();                                  
  IIC_CTPM_WriteByte(DEVICE_ADD);                 
  IIC_CTPM_WriteByte(reg);                        
  IIC_CTPM_Start();                                               
  b = IIC_CTPM_ReadByte(NO_ACK);                                                
  IIC_CTPM_Stop();                                 
  return b;

}


