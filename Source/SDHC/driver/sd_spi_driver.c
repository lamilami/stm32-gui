/******************************************************************************

                  版权所有 (C), 2012-2022, 浙大精益

 ******************************************************************************
  文 件 名   : sd_spi_driver.c
  版 本 号   : 初稿
  作    者   : ganjinming
  生成日期   : 2012年12月22日
  最近修改   :
  功能描述   : SD卡在spi模式下的驱动文件
  函数列表   :
              SD_DisSelect
              SD_GetResponse
              sd_init
              sd_low_level_Init
              SD_ReadDisk
              SD_RecvData
              SD_Select
              SD_SendBlock
              SD_SendCmd
              SD_SPI_ReadWriteByte
              sd_spi_speed
              SD_WaitReady
              SD_WriteDisk

  
 
  修改历史   :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 创建文件

******************************************************************************/
/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "sd_spi_driver.h"
 /*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/	
#define SD_SPI                           SPI3
#define SD_SPI_CLK                       RCC_APB1Periph_SPI3
#define SD_SPI_SCK_PIN                   GPIO_Pin_3                  /* PA.05 */
#define SD_SPI_SCK_GPIO_PORT             GPIOB                       /* GPIOA */
#define SD_SPI_SCK_GPIO_CLK              RCC_APB2Periph_GPIOB
#define SD_SPI_MISO_PIN                  GPIO_Pin_4                  /* PA.06 */
#define SD_SPI_MISO_GPIO_PORT            GPIOB                       /* GPIOA */
#define SD_SPI_MISO_GPIO_CLK             RCC_APB2Periph_GPIOB
#define SD_SPI_MOSI_PIN                  GPIO_Pin_5                  /* PA.07 */
#define SD_SPI_MOSI_GPIO_PORT            GPIOB                       /* GPIOA */
#define SD_SPI_MOSI_GPIO_CLK             RCC_APB2Periph_GPIOB
#define SD_CS_PIN                        GPIO_Pin_11                 /* PC.5 */
#define SD_CS_GPIO_PORT                  GPIOC                       /* GPIOC */
#define SD_CS_GPIO_CLK                   RCC_APB2Periph_GPIOC

#define SD_SPI_SPEED_LOW                 SPI_BaudRatePrescaler_256
#define SD_SPI_SPEED_HIGH                SPI_BaudRatePrescaler_4

// SD卡类型定义  
#define SD_TYPE_ERR     0x00
#define SD_TYPE_MMC     0x01
#define SD_TYPE_V1      0x02
#define SD_TYPE_V2      0x04
#define SD_TYPE_V2HC    0x06	   
// SD卡指令表  	   
#define CMD0    0       //卡复位
#define CMD1    1
#define CMD8    8       //命令8 ，SEND_IF_COND
#define CMD9    9       //命令9 ，读CSD数据
#define CMD10   10      //命令10，读CID数据
#define CMD12   12      //命令12，停止数据传输
#define CMD16   16      //命令16，设置SectorSize 应返回0x00
#define CMD17   17      //命令17，读sector
#define CMD18   18      //命令18，读Multi sector
#define CMD23   23      //命令23，设置多sector写入前预先擦除N个block
#define CMD24   24      //命令24，写sector
#define CMD25   25      //命令25，写Multi sector
#define CMD41   41      //命令41，应返回0x00
#define CMD55   55      //命令55，应返回0x01
#define CMD58   58      //命令58，读OCR信息
#define CMD59   59      //命令59，使能/禁止CRC，应返回0x00
//数据写入回应字意义
#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF
//SD卡回应标记字
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF

#define	SD_CS                      PCout(11)          //SD卡片选信号

/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/
	
/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/
	void sd_low_level_Init(void);
	void sd_spi_speed(u8 SPI_BaudRate);
	u8 SD_SPI_ReadWriteByte(u8 TxData);
    void SD_DisSelect(void);
    u8 SD_Select(void);
    u8 SD_WaitReady(void);
    u8 SD_GetResponse(u8 Response);
	u8 SD_RecvData(u8 *buf,u16 len);
	u8 SD_SendBlock(u8*buf,u8 cmd);	
    u8 SD_SendCmd(u8 cmd, u32 arg, u8 crc);
/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/
    
/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/
    static u8  SD_Type=0;//获取SD卡的类型
/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*****************************************************************************
 函 数 名  : SD_ReadDisk
 功能描述  : 读SD卡的扇区
 输入参数  : u8*buf     读取数据的缓冲区   
             u32 sector 读取扇区的起始编号   
             u8 cnt     读取扇区的数目 
 输出参数  : 无
 返 回 值  :  0--ok;  其他--失败.
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 SD_ReadDisk(u8*buf,u32 sector,u8 cnt)
{
	u8 r1;
	if(SD_Type!=SD_TYPE_V2HC)
    {
        sector <<= 9;//转换为字节地址
    }
	if(cnt==1)
	{
		r1=SD_SendCmd(CMD17,sector,0X01);//读命令
		if(r1==0)//指令发送成功
		{
			r1=SD_RecvData(buf,512);//接收512个字节	   
		}
	}
    else
	{
		r1=SD_SendCmd(CMD18,sector,0X01);//连续读命令
		do
		{
			r1=SD_RecvData(buf,512);//接收512个字节	 
			buf+=512;  
		}while(--cnt && r1==0); 	
		SD_SendCmd(CMD12,0,0X01);	//发送停止命令
	}   
	SD_DisSelect();//取消片选
	return r1;
}

/*****************************************************************************
 函 数 名  : SD_WriteDisk
 功能描述  : 写SD卡的扇区
 输入参数  : u8*buf      要写入的数据缓冲区
             u32 sector  要写入数据的起始扇区
             u8 cnt      要写入的扇区数目
 输出参数  : 无
 返 回 值  : 0--ok;  其他--失败.
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 SD_WriteDisk(u8*buf,u32 sector,u8 cnt)
{
	u8 r1;
	if(SD_Type!=SD_TYPE_V2HC)
    {
        sector *= 512;//转换为字节地址
    }
	if(cnt==1)
	{
		r1=SD_SendCmd(CMD24,sector,0X01);//读命令
		if(r1==0)//指令发送成功
		{
			r1=SD_SendBlock(buf,0xFE);//写512个字节	   
		}
	}
    else
	{
		if(SD_Type!=SD_TYPE_MMC)
		{
			SD_SendCmd(CMD55,0,0X01);	
			SD_SendCmd(CMD23,cnt,0X01);//发送指令	
		}
 		r1=SD_SendCmd(CMD25,sector,0X01);//连续读命令
		if(r1==0)
		{
			do
			{
				r1=SD_SendBlock(buf,0xFC);//接收512个字节	 
				buf+=512;  
			}while(--cnt && r1==0);
			r1=SD_SendBlock(0,0xFD);//接收512个字节 
		}
	}   
	SD_DisSelect();//取消片选
	return r1;//
}


/*****************************************************************************
 函 数 名  : sd_init
 功能描述  : 初始化SD卡
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 0-OK 其他--失败
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 sd_init(void)
{
    u8 r1;      // 存放SD卡的返回值
    u16 retry;  // 用来进行超时计数
    u8 buf[4];  
	u16 i;

	sd_low_level_Init();		             //初始化IO
 	sd_spi_speed(SD_SPI_SPEED_LOW); //设置到低速模式 
 	for(i=0; i<10; i++)
    {
        SD_SPI_ReadWriteByte(0xFF);//发送最少74个脉冲
    }
	retry=20;
	do
	{
		r1 = SD_SendCmd(CMD0,0,0x95);//进入IDLE状态
	}while((r1!=0x01) && retry--);
    
 	SD_Type=0;//默认无卡
 	
	if(r1==0x01)
	{
		if(SD_SendCmd(CMD8,0x1AA,0x87)==1)//SD V2.0
		{
			for(i=0;i<4;i++)
            {
                buf[i]=SD_SPI_ReadWriteByte(0xFF);  //Get trailing return value of R7 resp
            }
			if(buf[2]==0x01&&buf[3]==0xAA)//卡是否支持2.7~3.6V
			{
				retry=0xFFFE;
				do
				{
					SD_SendCmd(CMD55,0,0X01);	          //发送CMD55
					r1=SD_SendCmd(CMD41,0x40000000,0X01);//发送CMD41
				}while(r1&&retry--);
                
				if(retry&&SD_SendCmd(CMD58,0,0x01)==0)//鉴别SD2.0卡版本开始
				{
					for(i=0; i<4; i++)
                    {
                        buf[i]=SD_SPI_ReadWriteByte(0xFF);//得到OCR值
                    }
					if(buf[0]&0x40)
                    {
                        SD_Type=SD_TYPE_V2HC;    //检查CCS
                    }
					else 
                    {
                        SD_Type=SD_TYPE_V2;
                    }
				}
			}
		}
        else//SD V1.x/ MMC	V3
		{
			SD_SendCmd(CMD55,0,0X01);		//发送CMD55
			r1=SD_SendCmd(CMD41,0,0X01);	//发送CMD41
			if(r1<=1)
			{		
				SD_Type=SD_TYPE_V1;
				retry=0XFFFE;
				do //等待退出IDLE模式
				{
					SD_SendCmd(CMD55,0,0X01);	//发送CMD55
					r1=SD_SendCmd(CMD41,0,0X01);//发送CMD41
				}while(r1&&retry--);
			}
            else
			{
				SD_Type=SD_TYPE_MMC;//MMC V3
				retry=0XFFFE;
				do //等待退出IDLE模式
				{											    
					r1=SD_SendCmd(CMD1,0,0X01);//发送CMD1
				}while(r1&&retry--);  
			}
			if(retry==0||SD_SendCmd(CMD16,512,0X01)!=0)
            {
                SD_Type=SD_TYPE_ERR;//错误的卡
            }
		}
	}
	SD_DisSelect();//取消片选
	sd_spi_speed(SD_SPI_SPEED_HIGH);//高速
	if(SD_Type)
    {
        return 0;
    }
	else if(r1)
    {
        return r1; 
    }
	return 0xaa; //其他错误
}
/*****************************************************************************
 函 数 名  : sd_low_level_Init
 功能描述  : SD卡底层引脚及SPI配置(初始化)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
void sd_low_level_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    SPI_InitTypeDef   SPI_InitStructure;

    SPI_I2S_DeInit(SD_SPI); 

    RCC_APB2PeriphClockCmd(SD_CS_GPIO_CLK | SD_SPI_MOSI_GPIO_CLK | SD_SPI_MISO_GPIO_CLK |SD_SPI_SCK_GPIO_CLK , ENABLE);
    
    RCC_APB1PeriphClockCmd(SD_SPI_CLK, ENABLE); 

    GPIO_InitStructure.GPIO_Pin = SD_SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SD_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SD_SPI_MOSI_PIN;
    GPIO_Init(SD_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SD_SPI_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
    GPIO_Init(SD_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SD_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(SD_CS_GPIO_PORT, &GPIO_InitStructure);
    GPIO_SetBits(SD_CS_GPIO_PORT,SD_CS_PIN);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SD_SPI, &SPI_InitStructure);
  
    SPI_Cmd(SD_SPI, ENABLE); 
    
    SPI_I2S_ReceiveData(SD_SPI);
    while (SPI_I2S_GetFlagStatus(SD_SPI, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_ReceiveData(SD_SPI);

    SD_CS=1;
    
}
/*****************************************************************************
 函 数 名  : sd_spi_speed
 功能描述  : 设置SD卡spi的速度
 输入参数  : u8 SPI_BaudRate  
              可选数值为:
               SPI_BaudRatePrescaler_x(其中x = 2,4,8,16,32,64,128,256)   

 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
void sd_spi_speed(u8 SPI_BaudRate)
 {
    SD_SPI->CR1&=0XFFC7;
	SD_SPI->CR1|=SPI_BaudRate;	
	SPI_Cmd(SD_SPI,ENABLE); 
 }

/*****************************************************************************
 函 数 名  : SD_SPI_ReadWriteByte
 功能描述  : 从spi中读写一个字节
 输入参数  : u8 TxData  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 SD_SPI_ReadWriteByte(u8 TxData)
{					 	
	while (SPI_I2S_GetFlagStatus(SD_SPI, SPI_I2S_FLAG_TXE) == RESET); 		  
	SPI_I2S_SendData(SD_SPI, TxData); 
	while (SPI_I2S_GetFlagStatus(SD_SPI, SPI_I2S_FLAG_RXNE) == RESET);					    
	return SPI_I2S_ReceiveData(SD_SPI); 				    
}

/*****************************************************************************
 函 数 名  : SD_DisSelect
 功能描述  : SD卡片选除能
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
void SD_DisSelect(void)
{
	SD_CS=1;
 	SD_SPI_ReadWriteByte(0xff);//提供额外的8个时钟
}

/*****************************************************************************
 函 数 名  : SD_Select
 功能描述  : SD卡片选使能
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 0 - 片选成功  1-片选失败
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 SD_Select(void)
{
	SD_CS=0;
	if(SD_WaitReady()==0)
    {
        return 0;
    }
	SD_DisSelect();
	return 1;
}

/*****************************************************************************
 函 数 名  : SD_WaitReady
 功能描述  : 查询SD卡是否准备好
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 0--准备好了; 其他--错误代码
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 SD_WaitReady(void)
{
	u32 t=0;
	do
	{
		if(SD_SPI_ReadWriteByte(0xFF)==0xFF)
        {
            return 0;
        }
		t++;		  	
	}while(t<0xFFFFFF);
	return 1;
}
/*****************************************************************************
 函 数 名  : SD_GetResponse
 功能描述  : 等待SD卡回应
 输入参数  : u8 Response  :要得到的回应值
 输出参数  : 无
 返 回 值  : 0-成功得到了该回应值
             其他-得到回应值失败
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 SD_GetResponse(u8 Response)
{
	u16 Count=0xFFFF;   						  
	while ((SD_SPI_ReadWriteByte(0xFF)!=Response)&&Count)
    {
        Count--;//等待得到准确的回应  
    }
	if (Count==0)
    {
        return MSD_RESPONSE_FAILURE;//得到回应失败
    }
	else
    {
        return MSD_RESPONSE_NO_ERROR;//正确回应
    }
}
	
/*****************************************************************************
 函 数 名  : SD_RecvData
 功能描述  : 从sd卡读取一个数据包的内容
 输入参数  : u8*buf   读取数据的缓冲区
             u16 len  读取数据长度
 输出参数  : 无
 返 回 值  : 0--成功;  其他--失败;	
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 SD_RecvData(u8 *buf,u16 len)
{			  	  
	if(SD_GetResponse(0xFE))
    {
        return 1;//等待SD卡发回数据起始令牌0xFE
    }
    while(len--)//开始接收数据
    {
        *buf=SD_SPI_ReadWriteByte(0xFF);
        buf++;
    }
    //下面是2个伪CRC（dummy CRC）
    SD_SPI_ReadWriteByte(0xFF);
    SD_SPI_ReadWriteByte(0xFF);									  					    
    return 0;//读取成功
}
/*****************************************************************************
 函 数 名  : SD_SendBlock
 功能描述  : 向sd卡写入一个数据包的内容 512字节
 输入参数  : u8*buf  写入数据缓冲区
             u8 cmd  写入指令 
 输出参数  : 无
 返 回 值  : 0--成功;  其他--失败;
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 SD_SendBlock(u8*buf,u8 cmd)
{	
	u16 t;		  	  
	if(SD_WaitReady())
    {
        return 1;//等待准备失效
    }
	SD_SPI_ReadWriteByte(cmd);
	if(cmd!=0xFD)//不是结束指令
	{
		for(t=0; t<512; t++)
        {
            SD_SPI_ReadWriteByte(buf[t]);
         }
	    SD_SPI_ReadWriteByte(0xFF);  //忽略crc
	    SD_SPI_ReadWriteByte(0xFF);
		t=SD_SPI_ReadWriteByte(0xFF);//接收响应
		if((t&0x1F)!=0x05)return 2;  //响应错误									  					    
	}						 									  					    
    return 0;//写入成功
}
														  
/*****************************************************************************
 函 数 名  : SD_SendCmd
 功能描述  : 向SD卡发送一个命令
 输入参数  : u8 cmd   命令 
             u32 arg  命令参数
             u8 crc   crc校验值	
 输出参数  : 无
 返 回 值  : SD卡返回的响应	
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2012年12月22日
    作    者   : ganjinming
    修改内容   : 新生成函数

*****************************************************************************/
u8 SD_SendCmd(u8 cmd, u32 arg, u8 crc)
{
    u8 r1;	
	u8 Retry=0; 
	SD_DisSelect();//取消上次片选
	if(SD_Select())
    {
        return 0xFF;//片选失效
    }
	//发送
    SD_SPI_ReadWriteByte(cmd | 0x40);//分别写入命令
    SD_SPI_ReadWriteByte(arg >> 24);
    SD_SPI_ReadWriteByte(arg >> 16);
    SD_SPI_ReadWriteByte(arg >> 8);
    SD_SPI_ReadWriteByte(arg);	  
    SD_SPI_ReadWriteByte(crc); 
	if(cmd==CMD12)
    {
        SD_SPI_ReadWriteByte(0xff);//Skip a stuff byte when stop reading
    }
    //等待响应，或超时退出
	Retry=0x1F;
	do
	{
		r1=SD_SPI_ReadWriteByte(0xFF);
	}while((r1&0x80) && Retry--);	 
	//返回状态值
    return r1;
}




