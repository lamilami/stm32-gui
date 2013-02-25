#include "stm32f10x.h"
#ifndef	__LCD_CONFIG_h__
#define	__LCD_CONFIG_h__
//	write your header here
#define LCD_X_MAX			480				//屏幕的X轴的物理宽度
#define LCD_Y_MAX			272				//屏幕的Y轴的物理宽度
			
//#define LCD_XY_Switch		0				//显示时X轴和Y由交换
//#define LCD_X_Rev			0				//显示时X轴反转
//#define LCD_Y_Rev			0				//显示时Y轴反转


//GPIOC_BASE + 16


#define		TFT_Base_Addr		0x60000000							//TFT基地址


#define	TFT_Reg_Ptr			((vu16 *)TFT_Base_Addr)
#define	TFT_DAT_Ptr			((vu16 *)(TFT_Base_Addr+(0x00080000)))
#define	TFT_Y_Ptr			
#define	TFT_X_Ptr			
#define	TFT_Sys_Ptr			
/*
#define	TFT_DAT_Read_Ptr	((vu16 *)TFT_Base_Addr)
#define	TFT_DAT_Write_Ptr	((vu16 *)(TFT_Base_Addr+(0x10<<1)))
#define	TFT_Reg0_Ptr		((vu16 *)(TFT_Base_Addr+(0x18<<1)))
#define	TFT_Reg1_Ptr		((vu16 *)(TFT_Base_Addr+(0x19<<1)))
#define	TFT_Reg2_Ptr		((vu16 *)(TFT_Base_Addr+(0x1A<<1)))
#define	TFT_Reg3_Ptr		((vu16 *)(TFT_Base_Addr+(0x1B<<1)))
#define	TFT_Reg4_Ptr		((vu16 *)(TFT_Base_Addr+(0x1C<<1)))
#define	TFT_Reg5_Ptr		((vu16 *)(TFT_Base_Addr+(0x1D<<1)))
#define	TFT_Reg6_Ptr		((vu16 *)(TFT_Base_Addr+(0x1E<<1)))
#define	TFT_Reg7_Ptr		((vu16 *)(TFT_Base_Addr+(0x1F<<1)))
*/

#define LCD_RES_Enable	  GPIO_ResetBits(GPIOD, GPIO_Pin_3);
#define LCD_RES_Disable	  GPIO_SetBits(GPIOD, GPIO_Pin_3);

#endif
void LCD_Dis_ON(void);
void LCD_Dis_OFF(void);
void LCD_Dis_Switch(u8 Dis_Num);
void LCD_Buffer_Switch(u8 Buffer_Num);
void Back_Light_SET(u8 PWM_Duty);
void Back_Light_ON_OFF(u8 ON_OFF);
void LCD_DataWrite(u16 Data);
u16 LCD_DataRead(void);
void Fill_Dot_LCD(u16 Color);
void Write_Dot_LCD(int x,int y,u16 Color);
void Clear_Dot_LCD(int x,int y);
unsigned int LCD_GetPoint(int x,int y);
void Set_Dot_Addr_LCD(int x,int y);
void LCD_Fill(u16 Data);
void LCD_Fill_s(u16 Number,u16 Color);
void Lcd_Init(void);

void ili9320_Initializtion(void);;;
void ili9320_SetCursor(u16 x,u16 y);
void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY);
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic);
void LCD_SetPoint(u16 x,u16 y,u16 point);
void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor);
void LCD_Clear(u16 dat);
void ili9320_Delay(u32 nCount);
u16 ili9320_GetCode(void);;

void ili9320_BackLight(u8 status);

u16 ili9320_BGR2RGB(u16 c);

u16 ili9320_GetPoint(u16 x,u16 y);;

u16 GUI_Color565(u32 RGB);  // RGB颜色转为16位(565)

void GUI_Text(u16 x, u16 y, u8 *str, u16 len,u16 Color, u16 bkColor);
void GUI_Line(u16 x0, u16 y0, u16 x1, u16 y1,u16 color);  // 画线
void GUI_Circle(u16 cx,u16 cy,u16 r,u16 color,u8 fill);  // 画园
void GUI_Rectangle(u16 x0, u16 y0, u16 x1, u16 y1,u16 color,u8 fill); // 画矩形
void GUI_Square(u16 x0, u16 y0, u16 with, u16 color,u8 fill);  // 画正方形

void Touch_Initializtion(void);
u16  Touch_GetPhyX(void);
u16  Touch_GetPhyY(void);
u16  Touch_MeasurementX(void);
u16  Touch_MeasurementY(void);





