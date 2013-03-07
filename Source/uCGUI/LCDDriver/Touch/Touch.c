/**************************************************************
** 	开发板
**	功能介绍： 触摸屏驱动代码
**  版本：V1.0  
**	论坛：www.openmcu.com
**	淘宝：http://shop36995246.taobao.com/   
**  技术支持群：121939788 
***************************************************************/ 
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Touch.h"
#include "SSD1963.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
Pen_Holder Pen_Point;	/* 定义笔实体 */ 
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
EXTI_InitTypeDef  EXTI_InitStructure;

TTOUCH_P g_tTP;

#if defined TOUCH_SPI_SIM
void Delay1(unsigned int x)
{
	unsigned int y = 0;
	for(;x>0;x--)
	for(y = 0;y<10;y++);
}
//SPI写数据
//向7843写入1byte数据   
void ADS_Write_Byte(u8 num)    
{  
	u8 count=0;   
	for(count=0;count<8;count++)  
	{ 	  
		if(num&0x80)TDIN=1;  
		else TDIN=0;   
		num<<=1;    
		TCLK=0;//上升沿有效	   	 
		TCLK=1;      
	} 			    
} 		 
//SPI读数据 
//从7846/7843/XPT2046/UH7843/UH7846读取adc值	   
u16 ADS_Read_AD(u8 CMD)	  
{ 	 
	u8 i;
	u8 count=0; 	  
	u16 Num=0; 
	TCLK=0;//先拉低时钟 	 
	TCS=0; //选中ADS7843	 
	ADS_Write_Byte(CMD);//发送命令字
	for(i=100;i>0;i--);
//	Delay1_us(6);//ADS7846的转换时间最长为6us
	TCLK=1;//给1个时钟，清除BUSY   	    
	TCLK=0; 	 
	for(count=0;count<16;count++)  
	{ 				  
		Num<<=1; 	 
		TCLK=0;//下降沿有效  	    	   
		TCLK=1;
		if(DOUT)Num++; 		 
	}  	
	Num>>=4;   //只有高12位有效.
	TCS=1;//释放ADS7843	 
	return(Num);   
}
//读取一个坐标值
//连续读取READ_TIMES次数据,对这些数据升序排列,
//然后去掉最低和最高LOST_VAL个数,取平均值 
#define READ_TIMES 15 //读取次数
#define LOST_VAL 5	  //丢弃值
u16 ADS_Read_XY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)
	{				 
		buf[i]=ADS_Read_AD(xy);	    
	}				    
	for(i=0;i<READ_TIMES-1; i++)//排序
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//升序排列
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 
//带滤波的坐标读取
//最小值不能少于100.
u8 Read_ADS(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=ADS_Read_XY(CMD_RDY);
	ytemp=ADS_Read_XY(CMD_RDX);	  				
	*x=xtemp;
	*y=ytemp;
	return 1;//读数成功
}
//2次读取ADS7846,连续读取2次有效的AD值,且这两次的偏差不能超过
//50,满足条件,则认为读数正确,否则读数错误.	   
//该函数能大大提高准确度
#define ERR_RANGE 50 //误差范围 
u8 Read_ADS2(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=Read_ADS(&x1,&y1);   
    if(flag==0)return(0);
    flag=Read_ADS(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-50内
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;	  
} 
//读取一次坐标值	
//仅仅读取一次,知道PEN松开才返回!					   
u8 Read_TP_Once(void)
{
	unsigned  char t = 0;  
	Pen_Int_Set(0);//关闭中断
	Pen_Point.Key_Sta=Key_Up;		  
		Read_ADS2(&Pen_Point.X,&Pen_Point.Y);
		Pen_Point.X = 0,Pen_Point.Y = 0;
	while((Pen_Point.X == 1730) || (Pen_Point.Y == 2428) || (Pen_Point.Y == 0) ||(Pen_Point.Y == 1730))
	{											  
		Delay1(8);
		Read_ADS2(&Pen_Point.X,&Pen_Point.Y); 
	}
	while(PEN==0&&t<=250)
	{
		t++;
		Delay1(3);
	};
	Pen_Int_Set(1);//开启中断		 
	if(t>=250)return 0;//按下2.5s 认为无效	x = 1730 ,y = 2428
	else return 1;	
}

#endif
/*****************************************************************************
** 函数名称: Touch_Configuration
** 功能描述: 触摸屏IO配置
** 作  　者: Dream
** 日　  期: 2010年12月06日
*****************************************************************************/

void Touch_Configuration()	//bsp.c中配置
{	
 #if 0
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOG | RCC_APB2Periph_AFIO
							, ENABLE );  //重要！！

	//下面是SPI相关GPIO初始化	sck mosi
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //通用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	//下面是SPI相关GPIO初始化	miso
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	//Configure PB12 pin: TP_CS pin 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//通用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB,&GPIO_InitStructure);
//sd_cs
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//通用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOG,&GPIO_InitStructure);

//flash_cs 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//通用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOG,&GPIO_InitStructure);

	GPIO_SetBits(GPIOG,GPIO_Pin_15);     //不选中SD卡
    GPIO_SetBits(GPIOG,GPIO_Pin_11);     //不选中FLASH卡

	//Configure PG7 pin: TP_INT pin 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	//上拉输入
	GPIO_Init(GPIOG,&GPIO_InitStructure);


	/*********gan**********/
	{
		SPI_InitTypeDef   SPI_InitStructure; 
   		//SPI2 Periph clock enable 
  		RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE );

		// SPI2 Config  
  		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
	  	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
	  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
	  	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 
	  	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; 
	  	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   
	  	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; 
	  	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
	  	SPI_InitStructure.SPI_CRCPolynomial = 7; 
	  	SPI_Init(SPI2,&SPI_InitStructure); 

  		// SPI2 enable  
  		SPI_Cmd(SPI2,ENABLE);
	}
	#endif
}
/*****************************************************************************
** 函数名称: Pen_Int_Set
** 功能描述: PEN中断设置
				EN=1：开启中断
					EN=0: 关闭中断
** 作  　者: Dream
** 日　  期: 2010年12月06日
*****************************************************************************/	 
void Pen_Int_Set(u8 en)
{
	if(en)EXTI->IMR|=1<<7;   //开启line13上的中断	  	
	else EXTI->IMR&=~(1<<7); //关闭line13上的中断	   
}
/*****************************************************************************
** 函数名称: EXTI15_10_IRQHandler
** 功能描述: 中断处理函数
				中断,检测到PEN脚的一个下降沿.
					置位Pen_Point.Key_Sta为按下状态
						中断线4线上的中断检测
** 作  　者: Dream
** 日　  期: 2010年12月06日
*****************************************************************************/
/*void EXTI15_10_IRQHandler()
{
	u16 i;
  	if(NVIC_GetIRQChannelPendingBitStatus(EXTI_IMR_MR13) != RESET)
	{
    	NVIC_ClearIRQChannelPendingBit(EXTI_IMR_MR13);	 //清楚中断挂起位
		for(i=1000;i>0;i--); 			//延时去抖动
		Pen_Point.Key_Sta=Key_Down;//按键按下 		 		  				 
	}
}*/
#ifdef ADJ_SAVE_ENABLE
#define SAVE_ADDR_BASE 40
/*****************************************************************************
** 函数名称: Save_Adjdata
** 功能描述: 保存校准参数到EEPROAM中的 地址40
				此部分涉及到使用外部EEPROM,如果没有外部EEPROM,屏蔽此部分即可
				保存在EEPROM里面的地址区间基址,占用13个字节(RANGE:SAVE_ADDR_BASE~SAVE_ADDR_BASE+12)
** 作  　者: Dream
** 日　  期: 2010年12月06日
*****************************************************************************/
void Save_Adjdata(void)
{
	u8 temp[4];
	//保存校正结果!		   							  
	temp[0]=(u32)(Pen_Point.xfac*100000000)&0xff;	//保存x校正因素    
	temp[1]=(u32)(Pen_Point.xfac*100000000)>>8&0xff;//保存x校正因素    
	temp[2]=(u32)(Pen_Point.xfac*100000000)>>16&0xff;//保存x校正因素        
	temp[3]=(u32)(Pen_Point.xfac*100000000)>>24&0xff;//保存x校正因素        
   	I2C_Write(&temp[0],SAVE_ADDR_BASE,4);

	temp[0]=(u32)(Pen_Point.yfac*100000000)&0xff;//保存x校正因素    
	temp[1]=(u32)(Pen_Point.yfac*100000000)>>8&0xff;//保存x校正因素    
	temp[2]=(u32)(Pen_Point.yfac*100000000)>>16&0xff;//保存x校正因素        
	temp[3]=(u32)(Pen_Point.yfac*100000000)>>24&0xff;//保存x校正因素 

   	I2C_Write(&temp[0],SAVE_ADDR_BASE+4,4);
	temp[0]=(u32)(Pen_Point.xoff*100000000)&0xff;//保存x校正因素    
	temp[1]=(u32)(Pen_Point.xoff*100000000)>>8&0xff;//保存x校正因素    
   	I2C_Write(&temp[0],SAVE_ADDR_BASE+8,2);
	//保存x偏移量
	//保存y偏移量
	temp[0]=(u32)(Pen_Point.yoff*100000000)&0xff;//保存x校正因素    
	temp[1]=(u32)(Pen_Point.yoff*100000000)>>8&0xff;//保存x校正因素    
   	I2C_Write(&temp[0],SAVE_ADDR_BASE+10,2);
	I2C_Read(&temp[0],SAVE_ADDR_BASE+12,1);
	temp[0]&=0XF0;
	temp[0]|=0X0A;//标记校准过了
	I2C_Write(&temp[0],SAVE_ADDR_BASE+12,1);			 
}
/*****************************************************************************
** 函数名称: Get_Adjdata
** 功能描述: 得到保存在EEPROM里面的校准值
				返回值：1，成功获取数据
						 0，获取失败，要重新校准
** 作  　者: Dream
** 日　  期: 2010年12月06日
*****************************************************************************/       
u8 Get_Adjdata(void)
{	
	u8 temp[4];
	u32 tempfac=0;
	I2C_Read(&temp[0],52,1); //第五十二字节的第四位用来标记是否校准过！ 		 
	if((temp[0]&0X0F)==0X0A)		//触摸屏已经校准过了			   
	{   
		I2C_Read(&temp[0],40,4);
		tempfac = temp[0]|(temp[1]<<8)|(temp[2]<<16)|(temp[3]<<24);	   
		Pen_Point.xfac=(float)tempfac/100000000;//得到x校准参数
		I2C_Read(&temp[0],44,4);
		tempfac = temp[0]|(temp[1]<<8)|(temp[2]<<16)|(temp[3]<<24);	   
			          
		Pen_Point.yfac=(float)tempfac/100000000;//得到y校准参数
	    //得到x偏移量
		I2C_Read(&temp[0],48,2);		
		tempfac = temp[0]|(temp[1]<<8);	   		   	  
		Pen_Point.xoff=tempfac;					 
	    //得到y偏移量
		I2C_Read(&temp[0],50,2);
		tempfac = temp[0]|(temp[1]<<8);	   
						 	  
		Pen_Point.yoff=tempfac;					 
		return 1;	 
	}
	return 0;
}
#endif

/******gan*********/

#define TP_CS()  GPIO_ResetBits(GPIOC,GPIO_Pin_3)
#define TP_DCS() GPIO_SetBits(GPIOC,GPIO_Pin_3)

unsigned char SPI_WriteByte(unsigned char data) 
{ 
 unsigned char Data01 = 0; 

   //Wait until the transmit buffer is empty 
  while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET); 
  // Send the byte  
  SPI_I2S_ReceiveData(SPI1);
  SPI_I2S_SendData(SPI1,data); 

   //Wait until a data is received 
  while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET); 
  // Get the received data 
  Data01 = SPI_I2S_ReceiveData(SPI1); 

  // Return the shifted data 
  return Data01; 
}  


void SpiDelay(unsigned int DelayCnt)
{
 unsigned int i;
 for(i=0;i<DelayCnt;i++);
}

u16 TPReadX(void)
{ 
   u16 x=0;
   TP_CS();
   SpiDelay(10);
   SPI_WriteByte(0xd0);
   SpiDelay(10);
   x=SPI_WriteByte(0x00);
   x<<=8;
   x+=SPI_WriteByte(0x00);
   SpiDelay(20);
   TP_DCS();
   //x = 3671 - x; 
   x = x>>3;

  GUI_DispDecAt(x, 300, 300, 5);
  return (x);
}

u16 TPReadY(void)
{
 u16 y=0;
  TP_CS();
  SpiDelay(10);
  SPI_WriteByte(0x90);
  SpiDelay(10);
  y=SPI_WriteByte(0x00);
  y<<=8;
  y+=SPI_WriteByte(0x00);
  SpiDelay(20);
  TP_DCS();
  //y = 3601 - y;
  y = y>>3;
   
  GUI_DispDecAt(y, 350, 300, 5);

  return (y);
}


unsigned int get_calibrate_state(void)
{
   return  (*(__IO uint16_t*)CAL_STATE_ADDR); 

}

void get_calibrate_data(uint16_t* cal_data)
{
	int i;
	for(i=0;i<5;i++)
	{
	cal_data[i]= (*(__IO uint16_t*)(BANK511_WRITE_START_ADDR+i*2)); 
    } 
}

FLASH_Status  save_calibrate_to_flash(uint16_t* data)
{

    return flash_pro(CAL_STATE_ADDR, data,5);
}



//
//xy 1-- x, 2-- y
//
uint16_t TOUCH_DataFilter(uint8_t xy)
{
	uint16_t i, j;
    uint16_t buf[ADC_READ_TIME];
    uint16_t usSum;
    uint16_t usTemp;
	usSum = 0;
	
    for(i=0; i < ADC_READ_TIME; i++)
    {
     	if(xy == 1)
		{
        buf[i] = TPReadX();
		}else{
		buf[i] = TPReadY();
		}
    }
                        
    for(i = 0; i < ADC_READ_TIME - 1; i++)
    {
        for(j = i + 1; j < ADC_READ_TIME; j++)
        {
            if(buf[i] > buf[j])
            {
                usTemp = buf[i];
                buf[i] = buf[j];
                buf[j] = usTemp;
            }
        }
    }     
    
 
    for(i = DISCARD_No; i < ADC_READ_TIME - DISCARD_No; i++)
    {
        usSum += buf[i];
    }
   
    usTemp = usSum / (ADC_READ_TIME - 2 * DISCARD_No);

    return usTemp; 
}

 
uint8_t TOUCH_ReadAdcXY(uint16_t *_usX, uint16_t *_usY) 
{
    uint16_t iX1, iY1;
    uint16_t iX2, iY2;
    uint16_t iX, iY;

    iY1 = TOUCH_DataFilter(ADC_CH_Y);
    iX1 = TOUCH_DataFilter(ADC_CH_X);
    iY2 = TOUCH_DataFilter(ADC_CH_Y);
    iX2 = TOUCH_DataFilter(ADC_CH_X);

    iX = abs(iX1 - iX2);
    iY = abs(iY1 - iY2); 

    /* 前后两次采样在+-ADC_ERR_RANGE内 */  
    if ((iX <= ADC_ERR_RANGE) && (iY <= ADC_ERR_RANGE))
    {       
        *_usX = (iX1 + iX2) / 2;
        *_usY = (iY1 + iY2) / 2;

        return 1;
    }
    else 
    {
        return 0;
    }      
} 



void TOUCH_Scan(void)
{

    uint8_t s_invalid_count = 0;
	uint8_t flag;
	
   
    if (TOUCH_PRESSING == 0)
    {   
	              
        while(!TOUCH_ReadAdcXY(&g_tTP.usAdcNowX, &g_tTP.usAdcNowY)&&(s_invalid_count<5));
        {
            s_invalid_count++;
        }
        
        if(s_invalid_count >= 5)
        {
            g_tTP.usAdcNowX = 0;
            g_tTP.usAdcNowY = 0;    
        }
    }
    else
    {
        g_tTP.usAdcNowX = 0;
        g_tTP.usAdcNowY = 0;
    }
	GUI_DispDecAt( g_tTP.usAdcNowX, 400, 400, 5);
	GUI_DispDecAt( g_tTP.usAdcNowY, 450, 450, 5);
}




/*********************************************************************************************************
** End of File
*********************************************************************************************************/
