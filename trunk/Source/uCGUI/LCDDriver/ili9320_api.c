#include "stm32f10x.h"
#include "LCD_Config.h"


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
