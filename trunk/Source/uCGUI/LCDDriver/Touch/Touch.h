#ifndef __TOUCH_H
#define __TOUCH_H	

#include "touchc.h"
#include "bsp.h"

#define ADC_READ_TIME			8
#define DISCARD_No				2
#define ADC_ERR_RANGE			12

#define ADC_CH_X				1
#define ADC_CH_Y				2

/* ADS7843/7846/UH7843/7846/XPT2046/TSC2046 指令集 */\
#define CMD_RDX	0XD0  //0B11010000即用差分方式读X坐标 
#define CMD_RDY 0X90  //0B10010000即用差分方式读Y坐标 
/* 使能24LC02 */
//#define ADJ_SAVE_ENABLE	    
 
/*触摸屏芯片连接引脚配置	*/   
#define PEN  PGin(7)   //PG7  INT
#define DOUT PBin(14)   //PB14  MISO
#define TDIN PBout(15)  //PB15  MOSI
#define TCLK PBout(13)  //PB13  SCLK
#define TCS  PBout(12)  //PB12  CS    

/* 按键状态	*/ 
#define Key_Down 0x01
#define Key_Up   0x00 
/*
typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;*/

#define CAL_STATE_ADDR BANK511_WRITE_START_ADDR
#define CAL_DATA_ADDR  BANK511_WRITE_START_ADDR+2
#define CAL_STATE_ADJ_READY 0x01
#define CAL_STATE_NOT_ADJ   0x00

typedef struct{

	uint16_t usAdcNowX;
	uint16_t usAdcNowY;

}TTOUCH_P;

/* 笔杆结构体 */
typedef struct 
{
	u16 X0;//原始坐标
	u16 Y0;
	u16 X; //最终/暂存坐标
	u16 Y;						   	    
	u8  Key_Sta;//笔的状态			  
	//触摸屏校准参数
	float xfac;
	float yfac;
	short xoff;
	short yoff;
}Pen_Holder;




extern Pen_Holder Pen_Point; 
extern TTOUCH_P g_tTP;

void Touch_Init(void);
void Pen_Int_Set(u8 en); 
void Touch_Configuration(void);
void ADS_Write_Byte(u8 num);
u16 ADS_Read_AD(u8 CMD);
u16 ADS_Read_XY(u8 xy);
u8 Read_TP_Once(void);
u8 Read_ADS2(u16 *x,u16 *y);
u8 Read_ADS(u16 *x,u16 *y);
void Drow_Touch_Point(u16 x,u16 y);
u8 Get_Adjdata(void);
void Refreshes_Screen(void);
void Convert_Pos(void);
void Draw_Big_Point(u16 x,u16 y);
void Touch_Adjust(void);


void get_calibrate_data(uint16_t* cal_data);
FLASH_Status  save_calibrate_to_flash(uint16_t* data);
unsigned int get_calibrate_state(void);


uint16_t TOUCH_DataFilter(uint8_t xy);
uint8_t TOUCH_ReadAdcXY(uint16_t *_usX, uint16_t *_usY);
void TOUCH_Scan(void);

#endif
