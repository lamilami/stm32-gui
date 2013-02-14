#include "stm32f10x.h"

//void LCD_WriteCom(u16 LCD_Reg);
void LCD_WriteRAM(u16 RGB_Code);
void TimeDelay(u32 Time);
void ili9320_Initializtion(void);;;
void ili9320_SetCursor(u16 x,u16 y);
void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY);
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic);
void ili9320_SetPoint(u16 x,u16 y,u16 point);
void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor);
void ili9320_Clear(u16 dat);
void ili9320_Delay(u32 nCount);
u16 ili9320_GetCode(void);;

void ili9320_BackLight(u8 status);

u16 ili9320_GetPoint(u16 x,u16 y);;

u16 GUI_Color565(u32 RGB);  // RGB颜色转为16位(565)

void GUI_Text(u16 x, u16 y, u8 *str, u16 len,u16 Color, u16 bkColor);
void GUI_Line(u16 x0, u16 y0, u16 x1, u16 y1,u16 color);  // 画线
void GUI_Circle(u16 cx,u16 cy,u16 r,u16 color,u8 fill);  // 画园
void GUI_Rectangle(u16 x0, u16 y0, u16 x1, u16 y1,u16 color,u8 fill); // 画矩形
void GUI_Square(u16 x0, u16 y0, u16 with, u16 color,u8 fill);  // 画正方形
void LCD_WriteCom(u16 LCD_Reg);
void LCD_WriteRAM(u16 RGB_Code);

int GUI_GetVLine(u16 x0, u16 y0,u16 y1,u16 *color);
int GUI_SetVLine(u16 x0, u16 y0,u16 y1,u16 *color);	

//void Touch_Initializtion(void);
//u16  Touch_GetPhyX(void);
//u16  Touch_GetPhyY(void);
//u16  Touch_MeasurementX(void);
//u16  Touch_MeasurementY(void);


