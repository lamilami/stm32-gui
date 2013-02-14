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



/****************************************************************************
* ��    �ƣ�GUI_CmpColor()
* ��    �ܣ��ж���ɫֵ�Ƿ�һ�¡�
* ��ڲ�����color1		��ɫֵ1
*		        color2		��ɫֵ2
* ���ڲ���������1��ʾ��ͬ������0��ʾ����ͬ��
* ˵    ����
****************************************************************************/
#define  GUI_CmpColor(color1, color2)	( (color1&0x01) == (color2&0x01) )


/****************************************************************************
* ��    �ƣ�u16 GUI_Color565(u32 RGB)
* ��    �ܣ���RGB��ɫת��Ϊ16λ��ɫ��
* ��ڲ�����RGB  ��ɫֵ
* ���ڲ���������16λRGB��ɫֵ��
* ˵    ����
* ���÷�����i=GUI_Color565(0xafafaf);
****************************************************************************/
u16 GUI_Color565(u32 RGB)
{
  u8  r, g, b;

  b = ( RGB >> (0+3) ) & 0x1f;		// ȡBɫ�ĸ�5λ
  g = ( RGB >> (8+2) ) & 0x3f;		// ȡGɫ�ĸ�6λ
  r = ( RGB >> (16+3)) & 0x1f;		// ȡRɫ�ĸ�5λ
   
  return( (r<<11) + (g<<5) + (b<<0) );		
}

/****************************************************************************
* ��    �ƣ�void GUI_Text(u16 x, u16 y, u8 *str, u16 len,u16 Color, u16 bkColor)
* ��    �ܣ���ָ��������ʾ�ַ���
* ��ڲ�����x      ������
*           y      ������
*           *str   �ַ���
*           len    �ַ�������
*           Color  �ַ���ɫ
*           bkColor�ַ�������ɫ
* ���ڲ�������
* ˵    ����
* ���÷�����GUI_Text(0,0,"0123456789",10,0x0000,0xffff);
****************************************************************************/
void GUI_Text(u16 x, u16 y, u8 *str, u16 len,u16 Color, u16 bkColor)
{
  u8 i;
  
  for (i=0;i<len;i++)
  {
 //   ili9320_PutChar((x+8*i),y,*str++,Color,bkColor);
  }
}

/****************************************************************************
* ��    �ƣ�void GUI_Line(u16 x0, u16 y0, u16 x1, u16 y1,u16 color)
* ��    �ܣ���ָ�����껭ֱ��
* ��ڲ�����x0     A��������
*           y0     A��������
*           x1     B��������
*           y1     B��������
*           color  ����ɫ
* ���ڲ�������
* ˵    ����
* ���÷�����GUI_Line(0,0,240,320,0x0000);
****************************************************************************/
void GUI_Line(u16 x0, u16 y0, u16 x1, u16 y1,u16 color)
{
 	unsigned int length,i;
	u16 x,y;
 	u16 dx;// = abs(x1 - x0);
 	u16 dy;// = abs(y1 - y0);

	if(y0==y1)
	{
		  LCD_WriteCom(0x002A);	
  		  LCD_WriteRAM(x0>>8);	    
	      LCD_WriteRAM(x0&0x00ff);
	      LCD_WriteRAM(x1>>8);	    
	      LCD_WriteRAM(x1&0x00ff);
          LCD_WriteCom(0x002b);	
	
	      LCD_WriteRAM(y0>>8);	    
	      LCD_WriteRAM(y0&0x00ff);
	      LCD_WriteRAM(y1>>8);	    
	      LCD_WriteRAM(y1&0x00ff);
	      LCD_WriteCom(0x002c);
  		  
		  length=x1-x0+1;  
  		
 		  for(i=0;i<length;i++)      //��ʼ����д��
 	      LCD_WriteRAM(color);

  		return;
	}
	else if(y0>y1)
	{
		dy=y0-y1;
	}
	else
	{
		dy=y1-y0;
	}
 
 	if(x0==x1)
	{
		  LCD_WriteCom(0x002A);	
  		  LCD_WriteRAM(x0>>8);	    
	      LCD_WriteRAM(x0&0x00ff);
	      LCD_WriteRAM(x1>>8);	    
	      LCD_WriteRAM(x1&0x00ff);
          LCD_WriteCom(0x002b);	
	
	      LCD_WriteRAM(y0>>8);	    
	      LCD_WriteRAM(y0&0x00ff);
	      LCD_WriteRAM(y1>>8);	    
	      LCD_WriteRAM(y1&0x00ff);
	      LCD_WriteCom(0x002c);
  		  
		  length=y1-y0+1;  
  		
 		  for(i=0;i<length;i++)      //��ʼ����д��
 	      LCD_WriteRAM(color);

  		return;
	}
	else if(x0 > x1)
 	{
		dx=x0-x1;
  		x = x1;
  		x1 = x0;
  		y = y1;
  		y1 = y0;
 	}
 	else
 	{
		dx=x1-x0;
  		x = x0;
  		y = y0;
 	}

 	if(dx == dy)
 	{
  		while(x <= x1)
  		{

   			x++;
			if(y>y1)
			{
				y--;
			}
			else
			{
   				y++;
			}
   			LCD_SetPoint(x,y,color);
  		}
 	}
 	else
 	{
 		LCD_SetPoint(x, y, color);
  		if(y < y1)
  		{
   			if(dx > dy)
   			{
    			s16 p = dy * 2 - dx;
    			s16 twoDy = 2 * dy;
    			s16 twoDyMinusDx = 2 * (dy - dx);
    			while(x < x1)
    			{
     				x++;
     				if(p < 0)
     				{
      					p += twoDy;
     				}
     				else
     				{
      					y++;
      					p += twoDyMinusDx;
     				}
     				LCD_SetPoint(x, y,color);
    			}
   			}
   			else
   			{
    			s16 p = dx * 2 - dy;
    			s16 twoDx = 2 * dx;
    			s16 twoDxMinusDy = 2 * (dx - dy);
    			while(y < y1)
    			{
     				y++;
     				if(p < 0)
     				{
      					p += twoDx;
     				}
     				else
     				{
      					x++;
      					p+= twoDxMinusDy;
     				}
     				LCD_SetPoint(x, y, color);
    			}
   			}
  		}
  		else
  		{
   			if(dx > dy)
   			{
    			s16 p = dy * 2 - dx;
    			s16 twoDy = 2 * dy;
	    		s16 twoDyMinusDx = 2 * (dy - dx);
    			while(x < x1)
    			{
     				x++;
     				if(p < 0)
	     			{
    	  				p += twoDy;
     				}
     				else
     				{
      					y--;
	      				p += twoDyMinusDx;
    	 			}
     				LCD_SetPoint(x, y,color);
    			}
   			}
	   		else
   			{
    			s16 p = dx * 2 - dy;
    			s16 twoDx = 2 * dx;
	    		s16 twoDxMinusDy = 2 * (dx - dy);
    			while(y1 < y)
    			{
     				y--;
     				if(p < 0)
	     			{
    	  				p += twoDx;
     				}
     				else
     				{
      					x++;
	      				p+= twoDxMinusDy;
    	 			}
     				LCD_SetPoint(x, y,color);
    			}
   			}
  		}
 	}
}

/****************************************************************************
* ��    �ƣ�void GUI_Circle(u16 cx,u16 cy,u16 r,u16 color,u8 fill)
* ��    �ܣ���ָ�����껭Բ�������
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
****************************************************************************/
void GUI_Circle(u16 cx,u16 cy,u16 r,u16 color,u8 fill)
{
	u16 x,y;
	s16 delta,tmp;
	x=0;
	y=r;
	delta=3-(r<<1);

	while(y>x)
	{
		if(fill)
		{
			GUI_Line(cx+x,cy+y,cx-x,cy+y,color);
			GUI_Line(cx+x,cy-y,cx-x,cy-y,color);
			GUI_Line(cx+y,cy+x,cx-y,cy+x,color);
			GUI_Line(cx+y,cy-x,cx-y,cy-x,color);
		}
		else
		{
			LCD_SetPoint(cx+x,cy+y,color);
			LCD_SetPoint(cx-x,cy+y,color);
			LCD_SetPoint(cx+x,cy-y,color);
			LCD_SetPoint(cx-x,cy-y,color);
			LCD_SetPoint(cx+y,cy+x,color);
			LCD_SetPoint(cx-y,cy+x,color);
			LCD_SetPoint(cx+y,cy-x,color);
			LCD_SetPoint(cx-y,cy-x,color);
		}
		x++;
		if(delta>=0)
		{
			y--;
			tmp=(x<<2);
			tmp-=(y<<2);
			delta+=(tmp+10);
		}
		else
		{
			delta+=((x<<2)+6);
		}
	}
}

/****************************************************************************
* ��    �ƣ�void GUI_Rectangle(u16 x0, u16 y0, u16 x1, u16 y1,u16 color,u8 fill)
* ��    �ܣ���ָ�����򻭾��Σ��������ɫ
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
****************************************************************************/
void GUI_Rectangle(u16 x0, u16 y0, u16 x1, u16 y1,u16 color,u8 fill)
{
	if(fill)
	{
		u16 i;
		if(x0>x1)
		{
			i=x1;
			x1=x0;
		}
		else
		{
			i=x0;
		}
		for(;i<=x1;i++)
		{
			GUI_Line(i,y0,i,y1,color);
		}
		return;
	}
	GUI_Line(x0,y0,x0,y1,color);
	GUI_Line(x0,y1,x1,y1,color);
	GUI_Line(x1,y1,x1,y0,color);
	GUI_Line(x1,y0,x0,y0,color);
}

/****************************************************************************
* ��    �ƣ�void  GUI_Square(u16 x0, u16 y0, u16 with, u16 color,u8 fill)
* ��    �ܣ���ָ�����������Σ��������ɫ
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
****************************************************************************/
void  GUI_Square(u16 x0, u16 y0, u16 with, u16 color,u8 fill)
{
	GUI_Rectangle(x0, y0, x0+with, y0+with, color,fill);
}


/*****************************************************************************
 �� �� ��  : GUI_GetVLine
 ��������  : ��ȡlcd��һ����ֱ�ߵ���ɫ
 �������  : u16 x0 ��ʼ��x����
		   : u16 y0 ��ʼ��y����
		   : u16 y1 ������y����
		   ��u16 *buf ��ȡ����ɫֵ���λ��
 �������  : ��
 �� �� ֵ  : ��ȡ�����ݳ��� (<=480)
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��11��28��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
int GUI_GetVLine(u16 x0, u16 y0,u16 y1,u16 *color)
{
 	int length,i;
	
	LCD_WriteCom(0x002A);	
  	LCD_WriteRAM(x0>>8);	    
	LCD_WriteRAM(x0&0x00ff);
	LCD_WriteRAM(x0>>8);	    
	LCD_WriteRAM(x0&0x00ff);
    LCD_WriteCom(0x002b);	
	
	LCD_WriteRAM(y0>>8);	    
	LCD_WriteRAM(y0&0x00ff);
	LCD_WriteRAM(y1>>8);	    
	LCD_WriteRAM(y1&0x00ff);
	//LCD_WriteCom(0x002c); 
	LCD_WriteCom(0x002e); //������
  		  
	length=y1-y0+1;  
  		
 	for(i=0;i<length;i++)      //��ʼ������ȡ
	color[i]  =  *ptr_LCD_ADDR_RAM;
 	//LCD_WriteRAM(color);
	return length;
	
}

/*****************************************************************************
 �� �� ��  : GUI_SetVLine
 ��������  : д��lcd��һ����ֱ�ߵ���ɫ
 �������  : u16 x0 ��ʼ��x����
		   : u16 y0 ��ʼ��y����
		   : u16 y1 ������y����
		   ��u16 *buf ��ɫֵ���λ��
 �������  : ��
 �� �� ֵ  : д������ݳ���
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��11��28��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
int GUI_SetVLine(u16 x0, u16 y0,u16 y1,u16 *color)
{
 	int length,i;

	LCD_WriteCom(0x002A);	
  	LCD_WriteRAM(x0>>8);	    
	LCD_WriteRAM(x0&0x00ff);
	LCD_WriteRAM(x0>>8);	    
	LCD_WriteRAM(x0&0x00ff);
    LCD_WriteCom(0x002b);	
	
	LCD_WriteRAM(y0>>8);	    
	LCD_WriteRAM(y0&0x00ff);
	LCD_WriteRAM(y1>>8);	    
	LCD_WriteRAM(y1&0x00ff);
	LCD_WriteCom(0x002c); 
		  
	length=y1-y0+1;  
  		
 	for(i=0;i<length;i++)      
 	LCD_WriteRAM(color[i]);
	return length;
}

