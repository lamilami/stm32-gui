#include "flash_AT45DB161D.h"
#define SPIcs_Reset() do{GPIO_ResetBits(GPIOE, GPIO_Pin_3);} while(0);
#define SPIcs_Set()   do{GPIO_SetBits  (GPIOE, GPIO_Pin_3);	}while(0);
/********************************
*初始化SPI配置;
*无形参，无返回值
****************************/
void spi_at45db161d_initial(void)//bsp.c中定义		使用spi3
{
	#if 0
    GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 , ENABLE);


    /* Configure SPI1 pins: SCK, MISO and MOSI */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |  GPIO_Pin_7|GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//MISO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure); */
	/*SPI1 pin: NSS*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


	#if 0
      /* SPI_SLAVE_	Tx_DMA_Channel configuration ---------------------------------------------*/
	{
		DMA_InitTypeDef  DMA_InitStructure;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		DMA_DeInit(DMA1_Channel3); //SPI_TX  / /通道选择
	  	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)(&SPI1->DR);//外设地址
//	  	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPI1_Buffer_Tx; //数据地址
	  	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	//数据方向
//	  	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;//数据量
	  	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   //外设地址变化
	  	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;			 // 存储器地址变化
	  	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	// 外设传输数据宽度
	  	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;		//存储器数据宽度
	  	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //是否是循环模式
	  	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;	//通道优先级
	  	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //是否启动存储器到存储器模式
	  	DMA_Init(DMA1_Channel3, &DMA_InitStructure);

		//SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
	}
   #endif
	SPI_Cmd(SPI1, DISABLE);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
  	SPI_InitStructure.SPI_Direction =SPI_Direction_2Lines_FullDuplex; // SPI_Direction_1Line_Tx ;//
  	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	//初始化为第一个上升沿开始发送	  //模式还可以设置为   SPI_CPOL_High /Low
  	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;				                  //模式还可以设置为    SPI_CPHA_2Edge/1Edge
  	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  	SPI_InitStructure.SPI_CRCPolynomial = 7;
  	SPI_Init(SPI1, &SPI_InitStructure);
	//SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
  	/* Enable SPIy */
  	SPI_Cmd(SPI1, ENABLE);
	  /* Enable DMA1 Channel5 */
   // DMA_Cmd(DMA1_Channel3, ENABLE);

 #endif
}
/******************************
* spi读写一个字节
*  SPIx     :选择spi通道(SPI1 SPI2 SPI3)
*  spi_send :spi要发送的数据
*  返回值   :接收的spi数据 
*/
uint8_t SPI_WrRd_byte(SPI_TypeDef *SPIx,uint8_t spi_send)
{
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPIx,spi_send);
//	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
	return((uint8_t)SPI_I2S_ReceiveData(SPIx));
}
/**************************************
*  写AT45DB161B的buffer1 或者buffer2
*  buf_num : 选择buffer1 ,buffer2
*  addr：    指定buffer的地址(低10位为有效地址，因为buffer = 528byte,笔者芯片如此)
*  spi_data：要写入的数据地址
*  spi_data_num：要传入	buffer的数据个数<=528
*  无返回值
*/
void BUFFER_Write(SPI_TypeDef *SPIx ,uint8_t buf_num, uint16_t addr, uint8_t *spi_data, uint16_t spi_data_num)
{
    uint16_t i;
	SPIcs_Reset();
	SPI_WrRd_byte(SPIx, buf_num);
	SPI_WrRd_byte(SPIx, 0x00);
	SPI_WrRd_byte(SPIx, (uint8_t)(addr>>8));
	SPI_WrRd_byte(SPIx, (uint8_t)addr);
	for(i = 0; i < spi_data_num; i++)
	{
		SPI_WrRd_byte(SPIx, *spi_data++);	
	}
    SPIcs_Set();
}

/**************************************
*  读AT45DB161B的buffer1 或者buffer2
*  buf_num : 选择buffer1 ,buffer2
*  addr：    指定buffer的地址(低10位为有效地址，因为buffer = 528byte,笔者芯片如此)
*  spi_data：存放读出数据的首地址
*  spi_data_num：读出buffer的数据个数<=528
*  无返回值
*/
void BUFFER_Read(SPI_TypeDef *SPIx ,uint8_t buf_num, uint16_t addr,uint8_t *spi_data, uint16_t spi_data_num)
{
    uint16_t i;
	SPIcs_Reset();
	SPI_WrRd_byte(SPIx, buf_num );
	SPI_WrRd_byte(SPIx,  0x00 );
	SPI_WrRd_byte(SPIx,  (uint8_t)(addr>>8) );
	SPI_WrRd_byte(SPIx,  (uint8_t)(addr) );
#if DUMMY_BYTE == 1
	SPI_WrRd_byte(SPIx,  0x00 );
#endif
	for(i = 0; i < spi_data_num; i++)
	{
		*spi_data++ = SPI_WrRd_byte(SPIx, 0x00);	
	}
    SPIcs_Set();
}

/**************************
*通过buffer向主存储器页写数据
*buf_Erase   :buffer1/2, whith/without Built-in Erase 不同指令
*page_addr   :存储器的页地址 ，总共4096页 12位地址标示;
*                              地址跨越三个字节：xxpppppp ppppppxx xxxxxxxx
*/
Error_status BufToMainMemPage(SPI_TypeDef *SPIx,uint8_t buf_Erase, uint16_t Pageaddr)
{
    uint8_t temp;
    if(Pageaddr >= MAX_PAGE)   
	{
		return PageOver;
	}
	FlashWaitBusy(SPIx);
	SPIcs_Reset();
	SPI_WrRd_byte(SPIx, buf_Erase);
	temp = (uint8_t)(Pageaddr >> 6); //高6位(page_addr的最高4位不用)
	SPI_WrRd_byte(SPIx, temp);
	temp = (uint8_t)(Pageaddr << 2); //低6位(page_addr的最高4位不用)
	SPI_WrRd_byte(SPIx, temp);

	SPI_WrRd_byte(SPIx, 0x00);        //无用位
	SPIcs_Set();
	FlashWaitBusy(SPIx);
	return OP_OK;
}

/*************

void BufToMainMemPage(SPI_TypeDef *SPIx,uint8_t buf_Error, uint16_t page_addr)
{
    uint8_t temp;
	SPIcs_Reset();
	SPI_WrRd_byte(SPIx, buf_Error);
	temp = (uint8_t)(page_addr >> 6); //高6位(page_addr的最高4位不用)
	SPI_WrRd_byte(SPIx, temp);
	temp = (uint8_t)(page_addr << 2); //低6位(page_addr的最高4位不用)
	SPI_WrRd_byte(SPIx, temp);
	SPI_WrRd_byte(SPIx, 0x00);        //无用位
	SPIcs_Set();
}	*/
/*******************
* 从存储器的某一页中具体地址直接读取数据 MainMemory Page Read
*  *SPIx            :选择SPI的通道SPI1，SPI2 SPI3
* Pageaddr 	        :存储器的页地址(有效位 12bit)
* Byteaddr          : 存储器页内地址（有效位10bit），总共22位地址跨越三个字节：XXPPPPPP PPPPPPAA AAAAAAAA
* databuf           ：存储从AT45读出的数据	
*data_num           : 要求从AT45读出的数据个数	<=528
*/	

Error_status MMemPageRead(SPI_TypeDef *SPIx,uint16_t Pageaddr, uint16_t Byteaddr ,uint8_t *data_buf, uint16_t data_num)//pdf p7 p28
{
	uint16_t i;
	if(Pageaddr >= MAX_PAGE)         
	{
		return PageOver;
	}
	if(Byteaddr >= MAX_BYTE_PAGE)	 
	{
		return ByteOver;
	}
	if(data_num >  MAX_BYTE_PAGE)	 
	{
		return  ReadByteOver;
	}
	FlashWaitBusy(SPIx);
	SPIcs_Reset();
	SPI_WrRd_byte(SPIx, 0xd2);	 //opcode
	SPI_WrRd_byte(SPIx, (uint8_t)(Pageaddr>>6));	 //高6位(page_addr的最高2位不用)
	SPI_WrRd_byte(SPIx, (uint8_t)((Pageaddr << 2)|(Byteaddr >> 8)&0x3)); //低6位ageaddr 高2位byteaddr
	SPI_WrRd_byte(SPIx, (uint8_t)Byteaddr);	//低8位byteaddr

	for(i =0 ;i < 4;i++)
	{
		SPI_WrRd_byte(SPIx, 0x00);        //4 dummy bytes
	}
	for(i = 0; i<data_num; i++)
	{
		*data_buf++ = SPI_WrRd_byte(SPIx, 0x00);
	}
	SPIcs_Set();
	FlashWaitBusy(SPIx);
	return OP_OK;	
}

/******************

*/
Error_status MemPageToBUFF(SPI_TypeDef *SPIx,uint8_t buffer_num,uint16_t Pageaddr)//pdf p19 p37
{
	if(Pageaddr >= MAX_PAGE)         
	{
		return PageOver;
	}
	FlashWaitBusy(SPIx);
	SPIcs_Reset();
	SPI_WrRd_byte(SPIx, buffer_num);	 //opcode
	SPI_WrRd_byte(SPIx, (uint8_t)(Pageaddr >>6));	 //高6位(page_addr的最高2位不用)
	SPI_WrRd_byte(SPIx, (uint8_t)(Pageaddr << 2));    //低6位ageaddr 
	SPI_WrRd_byte(SPIx, 0x00);        //1 dummy bytes
	SPIcs_Set();
	FlashWaitBusy(SPIx);
	return OP_OK;	
}
/*
Main Memory Page to Buffer 1 Transfer 53H
Main Memory Page to Buffer 2 Transfer 55H	*/

/****************
*检测 存储器是否处于忙的状态，写入的数据是否正确，page是否保护，  page是512/528 bytes
接收到的数据 bit7:0--忙，1--空闲
             bit6:1--最近一次buffer写入memory page至少有一个不同(即有错误)，0--正确	 
			           The result of the most recent Main Memory Page to Buffer Compare operation
			 bit1:1--page处于保护，0--未保护
			 bit0:1--page 512bytes, 0--528bytes	(设置为512bytes/page ”power of 2“ is OTP，慎用 )
*/
void FlashWaitBusy(SPI_TypeDef *SPIx)
{
	unsigned char state_reg=0x00;
	SPIcs_Reset();
	SPI_WrRd_byte(SPIx, 0xD7);
	while((state_reg&0x80) == 0)
	{		
		state_reg = SPI_WrRd_byte(SPIx,0x00);// SPI_Flash_ReadByte();
	//	state_reg = SPI_WrRd_byte(SPIx,0x00);
	}
	SPIcs_Set();
	
}


/**************************
*
*/
Error_status page_erase(SPI_TypeDef *SPIx, uint16_t pageaddr)
{
    if(pageaddr >= MAX_PAGE) return PageOver;
	FlashWaitBusy(SPIx);
	SPIcs_Reset();
	SPI_WrRd_byte(SPIx,PAGE_ERASE);
	SPI_WrRd_byte(SPIx,(u8)(pageaddr >> 6));
	SPI_WrRd_byte(SPIx,(u8)(pageaddr << 2));
	SPI_WrRd_byte(SPIx,0x00);	//Dummy byte
	//|-23-|-22-|21|20|19|18|17|16|15|14|13|12|11|10|9|8|7|6|5|4|3|2|1|0|
	//|2个无关位|------------12位页地址-------------|----10个无关位-----|
	SPIcs_Set();
	return OP_OK;
}

/*
*************************
*	描述：   获取指定地址下的汉字内码数据
*	参数：   addr-flash中的偏移地址 
*		     *buf-读取的内码数据存储
*		     bytes-要读取的字节数
*   返回值： 无
************************
*/
/*
void LCD_ReadFlashBytes(u32 addr, u8 *buf, u8 bytes)
{

	MMemPageRead(SPIX,addr/BYTES_PER_PAGE, addr % BYTES_PER_PAGE ,buf, bytes);	
}
   */

