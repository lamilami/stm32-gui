#include "stm32f10x.h"
#include "LCD_Config.h"
#include "SSD1963.h"
//��ʱ����
void TimeDelay(u32 Time);

unsigned int  HDP=799; //Horizontal Display Period
unsigned int  HT=1000; //Horizontal Total
unsigned int  HPS=51;  //LLINE Pulse Start Position
unsigned int  LPS=3;   //	Horizontal Display Period Start Position
unsigned char HPW=8;   //	LLINE Pulse Width


unsigned int  VDP=479;	//Vertical Display Period
unsigned int  VT=530;	//Vertical Total
unsigned int  VPS=24;	//	LFRAME Pulse Start Position
unsigned int  FPS=23;	//Vertical Display Period Start Positio
unsigned char VPW=3;	// LFRAME Pulse Width


#define  ptr_LCD_ADDR_REG  ((volatile unsigned short *)(0x60000000))
#define  ptr_LCD_ADDR_RAM  ((volatile unsigned short *)(0x60080000))

void LCD_X_Init(void)
{

}

/*******************************************************************************
* Function Name  : LCD_WriteCom
* Description    : Writes to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteCom(u16 LCD_Reg)
{
	*ptr_LCD_ADDR_REG  =LCD_Reg;
}
/*******************************************************************************
* Function Name  : LCD_WriteRAM
* Description    : Writes to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM(u16 RGB_Code)					 
{
	/* Write 16-bit GRAM Reg */
  	*ptr_LCD_ADDR_RAM	 =RGB_Code;
}
/*******************************************************************************
* Function Name  : LCD_ReadRAM
* Description    : Reads the LCD RAM.
* Input          : None
* Output         : None
* Return         : LCD RAM Value.
*******************************************************************************/
u16 LCD_ReadRAM(void)
{
	u16 dummy;
  	/* Write 16-bit Index (then Read Reg) */
  	*ptr_LCD_ADDR_REG	 = 0x002e;
  	/* Read 16-bit Reg */
  	dummy  =  *ptr_LCD_ADDR_RAM;
  	return dummy;
}

void ssd1963_SetCursor(u16 x,u16 y)
{				
    LCD_WriteCom(0x002A);	
	LCD_WriteRAM(x>>8);	    
	LCD_WriteRAM(x&0x00ff);
	LCD_WriteRAM(HDP>>8);	    
	LCD_WriteRAM(HDP&0x00ff);
    LCD_WriteCom(0x002b);	
	LCD_WriteRAM(y>>8);	    
	LCD_WriteRAM(y&0x00ff);
	LCD_WriteRAM(VDP>>8);	    
	LCD_WriteRAM(VDP&0x00ff);
}

//****************************************************************************************************
// ԭ  ��: unsigned int Get_Dot_LCD(int x,int y)
// �����: tfthome.com
// ��  ��: ����һ�����ص���ɫ
// �汾��: 1.0
//****************************************************************************************************
unsigned int LCD_GetPoint(int x,int y)
{ 
  ssd1963_SetCursor(x,y);
  return (LCD_ReadRAM());
}
//****************************************************************************************************
// ԭ  ��: void Set_Dot_Addr_LCD(int x,int y)
// �����: tfthome.com
// ��  ��: �������ص�ַ
// �汾��: 1.0
//****************************************************************************************************
void Set_Dot_Addr_LCD(int x,int y)
{
	*TFT_Reg_Ptr = 0;
	*TFT_DAT_Ptr = y>>8;
	*TFT_DAT_Ptr = y;
	*TFT_Reg_Ptr = 1;
	*TFT_DAT_Ptr = x>>8;
	*TFT_DAT_Ptr = x;
	*TFT_Reg_Ptr = 2;
} 
void TimeDelay(u32 Time)
{
  	u32 Daly_Time = 0;
	do
	{
		Daly_Time ++;
	}
	while(Daly_Time < Time);
}


/****************************************************************************
* ��    �ƣ�void ili9320_Clear(u16 dat)
* ��    �ܣ�����Ļ����ָ������ɫ��������������� 0xffff
* ��ڲ�����dat      ���ֵ
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_Clear(0xffff);
****************************************************************************/
void LCD_Clear(u16 c)
{
    unsigned int l=800,w;

	LCD_WriteCom(0x002A);	
	LCD_WriteRAM(0);	    
	LCD_WriteRAM(0);
	LCD_WriteRAM(HDP>>8);	    
	LCD_WriteRAM(HDP&0x00ff);
    LCD_WriteCom(0x002b);	
	LCD_WriteRAM(0);	    
	LCD_WriteRAM(0);
	LCD_WriteRAM(VDP>>8);	    
	LCD_WriteRAM(VDP&0x00ff);
	LCD_WriteCom(0x002c);
	
	
	while(l--)
	{
	    for(w=0;w<480;w++)
		{    
          	LCD_WriteRAM(0xf800);
		}
	}
}
/****************************************************************************
* ��    �ƣ�void ili9320_SetPoint(u16 x,u16 y,u16 point)
* ��    �ܣ���ָ�����껭��
* ��ڲ�����x      ������
*           y      ������
*           point  �����ɫ
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_SetPoint(10,10,0x0fe0);
****************************************************************************/
void LCD_SetPoint(u16 x,u16 y,u16 c)
{
    LCD_WriteCom(0x002A);	
	LCD_WriteRAM(x>>8);	    
	LCD_WriteRAM(x&0x00ff);
	LCD_WriteRAM(HDP>>8);	    
	LCD_WriteRAM(HDP&0x00ff);
    LCD_WriteCom(0x002b);	
	LCD_WriteRAM(y>>8);	    
	LCD_WriteRAM(y&0x00ff);
	LCD_WriteRAM(VDP>>8);	    
	LCD_WriteRAM(VDP&0x00ff);
	LCD_WriteCom(0x002c);
  
 	LCD_WriteRAM(c);
}
/****************************************************************************
* ��    �ƣ�void LCD_Init()
* ��    �ܣ���ʼ�� ILI9320 ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷�����ili9320_Initializtion();
****************************************************************************/
void Lcd_Init(void)
{
  	LCD_X_Init();
	LCD_WriteCom(0x00E2);	
	LCD_WriteRAM(0x0023);
	// Set PLL with OSC = 10MHz (hardware)
    // Multiplier N = 35, VCO (>250MHz)= OSC*(N+1), VCO = 360MHz	   
	LCD_WriteRAM(0x0002);
	// Divider M = 2, PLL = 360/(M+1) = 120MHz
	LCD_WriteRAM(0x0004);
	// Validate M and N values

	LCD_WriteCom(0x00E0);  // PLL enable
	LCD_WriteRAM(0x0001);
	TimeDelay(10);
	LCD_WriteCom(0x00E0);
	LCD_WriteRAM(0x0003);
	TimeDelay(50);
	LCD_WriteCom(0x0001);  // software reset
	TimeDelay(50);
	LCD_WriteCom(0x00E6);
	LCD_WriteRAM(0x0004);
	LCD_WriteRAM(0x0093);
	LCD_WriteRAM(0x00e0);

	LCD_WriteCom(0x00B0);	//LCD SPECIFICATION
	LCD_WriteRAM(0x0000);
	LCD_WriteRAM(0x0000);
	LCD_WriteRAM((HDP>>8)&0X00FF);  //Set HDP
	LCD_WriteRAM(HDP&0X00FF);
    LCD_WriteRAM((VDP>>8)&0X00FF);  //Set VDP
	LCD_WriteRAM(VDP&0X00FF);
    LCD_WriteRAM(0x0000);

	LCD_WriteCom(0x00B4);	//HSYNC
	LCD_WriteRAM((HT>>8)&0X00FF);  //Set HT
	LCD_WriteRAM(HT&0X00FF);
	LCD_WriteRAM((HPS>>8)&0X00FF);  //Set HPS
	LCD_WriteRAM(HPS&0X00FF);
	LCD_WriteRAM(HPW);			   //Set HPW
	LCD_WriteRAM((LPS>>8)&0X00FF);  //Set HPS
	LCD_WriteRAM(LPS&0X00FF);
	LCD_WriteRAM(0x0000);

	LCD_WriteCom(0x00B6);	//VSYNC
	LCD_WriteRAM((VT>>8)&0X00FF);   //Set VT
	LCD_WriteRAM(VT&0X00FF);
	LCD_WriteRAM((VPS>>8)&0X00FF);  //Set VPS
	LCD_WriteRAM(VPS&0X00FF);
	LCD_WriteRAM(VPW);			   //Set VPW
	LCD_WriteRAM((FPS>>8)&0X00FF);  //Set FPS
	LCD_WriteRAM(FPS&0X00FF);

	LCD_WriteCom(0x00BA);
	LCD_WriteRAM(0x0005);//0x000F);    //GPIO[3:0] out 1

	LCD_WriteCom(0x00B8);
	LCD_WriteRAM(0x0007);    //GPIO3=input, GPIO[2:0]=output
	LCD_WriteRAM(0x0001);    //GPIO0 normal

	LCD_WriteCom(0x0036); //rotation
	LCD_WriteRAM(0x0008);

	LCD_WriteCom(0x00F0); //pixel data interface
	LCD_WriteRAM(0x0003);


	TimeDelay(50);
	LCD_WriteCom(0x0029); //display on

	LCD_WriteCom(0x00BE); //set PWM for B/L
	LCD_WriteRAM(0x0006);
	LCD_WriteRAM(0x0080);
	
	LCD_WriteRAM(0x0001);
	LCD_WriteRAM(0x00f0);
	LCD_WriteRAM(0x0000);
	LCD_WriteRAM(0x0000);

	LCD_WriteCom(0x00d0);//���ö�̬����������� 
	LCD_WriteRAM(0x000d);
}

