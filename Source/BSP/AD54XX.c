
#include"gui_app.h"

#define AD54XX_LATCH   	 	GPIO_SetBits(GPIOC, GPIO_Pin_5)
#define AD54XX_UNLATCH 	 	GPIO_ResetBits(GPIOC, GPIO_Pin_5)
  

// spi 配置被外部使用
void AD54XX_init(void)
{
	ESR_CLK sr_clk;
	ESR_STEP sr_step;
	sr_clk = SR_198410;
	sr_step = AD5410_SR_STEP_1_8_AD5420_2;
   	set_contol(sr_clk,sr_step);
}


// exp 
void set_contol(ESR_CLK sr_clk,ESR_STEP sr_step)
{
	int i,j;
	unsigned char out;
	unsigned short control;
	control = 0;
	
	control = (RXEN<<13)|(OUTEN<<12)|(sr_clk<<8)|(sr_step<<5)|(SREN<<4)|(DCEN<<3)|OUT_MA;
	
	SPI_I2S_SendData(SPI3,ADDR_CONTROL_REG);
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE)==0) {}
	out = (control>>8);
	SPI_I2S_SendData(SPI3,out);
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE)==0) {}
	out = (control&0x00FF);
	SPI_I2S_SendData(SPI3,out);
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE)==0) {}

	AD54XX_UNLATCH;
	for(j=0;j<50;j++);
	AD54XX_LATCH;
}

void set_data(float ma)
{
    unsigned char out;
    unsigned int ad54xx;
	int i,lenth,j;
	unsigned short data;

	if(OUT_MA == R1R2R3_4_20MA)
	data = ((1<<AD54XX)/16)*(ma - 4);
	else if(OUT_MA ==  OUT_PUT_0_20MA)
	data = ((1<<AD54XX)/20)*ma ;
	else
	data = ((1<<AD54XX)/24)*ma ;

	data = data<<(16 - AD54XX);

	SPI_I2S_SendData(SPI3,ADDR_DATA);
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE)==0) {}
	out = 	(data>>8);
	SPI_I2S_SendData(SPI3,out);
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE)==0) {}
	out = (data&0x00ff);
	SPI_I2S_SendData(SPI3,out);
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE)==0) {}

	AD54XX_UNLATCH;
	for(j=0;j<50;j++);
	AD54XX_LATCH;
}

void reset(void)
{
	int j;
	
	SPI_I2S_SendData(SPI3,READ_ADD_DEC_CONTROL_REG);
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE)==0) {}
	AD54XX_UNLATCH;
	for(j=0;j<50;j++);
	AD54XX_LATCH;
}

unsigned int read(EREAD_KIND read_kind)
{
    unsigned int read_back,j,i;

	SPI_I2S_SendData(SPI3,ADDR_READ_BACK_REG);
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE)==0) {}
	AD54XX_UNLATCH;
	for(j=0;j<50;j++);
	AD54XX_LATCH;
	SPI_I2S_ReceiveData(SPI3);                     // To clear OVR
	SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE); // To clear OVR
	SPI_I2S_SendData(SPI3,0x00);
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE)==0) {}
	read_back = SPI_I2S_ReceiveData(SPI3)<<16;
	SPI_I2S_SendData(SPI3,0x00);
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE)==0) {}
	read_back = read_back|(SPI_I2S_ReceiveData(SPI3)<<8);
	SPI_I2S_SendData(SPI3,0x00);
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE)==0) {}
	read_back = read_back|SPI_I2S_ReceiveData(SPI3);

	AD54XX_UNLATCH;
	for(j=0;j<50;j++);
	AD54XX_LATCH;

	return read_back;
}