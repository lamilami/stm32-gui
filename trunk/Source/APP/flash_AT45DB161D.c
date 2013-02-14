#include "flash_AT45DB161D.h"
#define SPIcs_Reset() do{GPIO_ResetBits(GPIOE, GPIO_Pin_3);} while(0);
#define SPIcs_Set()   do{GPIO_SetBits  (GPIOE, GPIO_Pin_3);	}while(0);
/********************************
*��ʼ��SPI����;
*���βΣ��޷���ֵ
****************************/
void spi_at45db161d_initial(void)//bsp.c�ж���		ʹ��spi3
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
		DMA_DeInit(DMA1_Channel3); //SPI_TX  / /ͨ��ѡ��
	  	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t)(&SPI1->DR);//�����ַ
//	  	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SPI1_Buffer_Tx; //���ݵ�ַ
	  	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	//���ݷ���
//	  	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;//������
	  	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   //�����ַ�仯
	  	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;			 // �洢����ַ�仯
	  	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	// ���贫�����ݿ��
	  	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;		//�洢�����ݿ��
	  	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //�Ƿ���ѭ��ģʽ
	  	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;	//ͨ�����ȼ�
	  	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //�Ƿ������洢�����洢��ģʽ
	  	DMA_Init(DMA1_Channel3, &DMA_InitStructure);

		//SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
	}
   #endif
	SPI_Cmd(SPI1, DISABLE);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
  	SPI_InitStructure.SPI_Direction =SPI_Direction_2Lines_FullDuplex; // SPI_Direction_1Line_Tx ;//
  	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	//��ʼ��Ϊ��һ�������ؿ�ʼ����	  //ģʽ����������Ϊ   SPI_CPOL_High /Low
  	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;				                  //ģʽ����������Ϊ    SPI_CPHA_2Edge/1Edge
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
* spi��дһ���ֽ�
*  SPIx     :ѡ��spiͨ��(SPI1 SPI2 SPI3)
*  spi_send :spiҪ���͵�����
*  ����ֵ   :���յ�spi���� 
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
*  дAT45DB161B��buffer1 ����buffer2
*  buf_num : ѡ��buffer1 ,buffer2
*  addr��    ָ��buffer�ĵ�ַ(��10λΪ��Ч��ַ����Ϊbuffer = 528byte,����оƬ���)
*  spi_data��Ҫд������ݵ�ַ
*  spi_data_num��Ҫ����	buffer�����ݸ���<=528
*  �޷���ֵ
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
*  ��AT45DB161B��buffer1 ����buffer2
*  buf_num : ѡ��buffer1 ,buffer2
*  addr��    ָ��buffer�ĵ�ַ(��10λΪ��Ч��ַ����Ϊbuffer = 528byte,����оƬ���)
*  spi_data����Ŷ������ݵ��׵�ַ
*  spi_data_num������buffer�����ݸ���<=528
*  �޷���ֵ
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
*ͨ��buffer�����洢��ҳд����
*buf_Erase   :buffer1/2, whith/without Built-in Erase ��ָͬ��
*page_addr   :�洢����ҳ��ַ ���ܹ�4096ҳ 12λ��ַ��ʾ;
*                              ��ַ��Խ�����ֽڣ�xxpppppp ppppppxx xxxxxxxx
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
	temp = (uint8_t)(Pageaddr >> 6); //��6λ(page_addr�����4λ����)
	SPI_WrRd_byte(SPIx, temp);
	temp = (uint8_t)(Pageaddr << 2); //��6λ(page_addr�����4λ����)
	SPI_WrRd_byte(SPIx, temp);

	SPI_WrRd_byte(SPIx, 0x00);        //����λ
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
	temp = (uint8_t)(page_addr >> 6); //��6λ(page_addr�����4λ����)
	SPI_WrRd_byte(SPIx, temp);
	temp = (uint8_t)(page_addr << 2); //��6λ(page_addr�����4λ����)
	SPI_WrRd_byte(SPIx, temp);
	SPI_WrRd_byte(SPIx, 0x00);        //����λ
	SPIcs_Set();
}	*/
/*******************
* �Ӵ洢����ĳһҳ�о����ֱַ�Ӷ�ȡ���� MainMemory Page Read
*  *SPIx            :ѡ��SPI��ͨ��SPI1��SPI2 SPI3
* Pageaddr 	        :�洢����ҳ��ַ(��Чλ 12bit)
* Byteaddr          : �洢��ҳ�ڵ�ַ����Чλ10bit�����ܹ�22λ��ַ��Խ�����ֽڣ�XXPPPPPP PPPPPPAA AAAAAAAA
* databuf           ���洢��AT45����������	
*data_num           : Ҫ���AT45���������ݸ���	<=528
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
	SPI_WrRd_byte(SPIx, (uint8_t)(Pageaddr>>6));	 //��6λ(page_addr�����2λ����)
	SPI_WrRd_byte(SPIx, (uint8_t)((Pageaddr << 2)|(Byteaddr >> 8)&0x3)); //��6λageaddr ��2λbyteaddr
	SPI_WrRd_byte(SPIx, (uint8_t)Byteaddr);	//��8λbyteaddr

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
	SPI_WrRd_byte(SPIx, (uint8_t)(Pageaddr >>6));	 //��6λ(page_addr�����2λ����)
	SPI_WrRd_byte(SPIx, (uint8_t)(Pageaddr << 2));    //��6λageaddr 
	SPI_WrRd_byte(SPIx, 0x00);        //1 dummy bytes
	SPIcs_Set();
	FlashWaitBusy(SPIx);
	return OP_OK;	
}
/*
Main Memory Page to Buffer 1 Transfer 53H
Main Memory Page to Buffer 2 Transfer 55H	*/

/****************
*��� �洢���Ƿ���æ��״̬��д��������Ƿ���ȷ��page�Ƿ񱣻���  page��512/528 bytes
���յ������� bit7:0--æ��1--����
             bit6:1--���һ��bufferд��memory page������һ����ͬ(���д���)��0--��ȷ	 
			           The result of the most recent Main Memory Page to Buffer Compare operation
			 bit1:1--page���ڱ�����0--δ����
			 bit0:1--page 512bytes, 0--528bytes	(����Ϊ512bytes/page ��power of 2�� is OTP������ )
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
	//|2���޹�λ|------------12λҳ��ַ-------------|----10���޹�λ-----|
	SPIcs_Set();
	return OP_OK;
}

/*
*************************
*	������   ��ȡָ����ַ�µĺ�����������
*	������   addr-flash�е�ƫ�Ƶ�ַ 
*		     *buf-��ȡ���������ݴ洢
*		     bytes-Ҫ��ȡ���ֽ���
*   ����ֵ�� ��
************************
*/
/*
void LCD_ReadFlashBytes(u32 addr, u8 *buf, u8 bytes)
{

	MMemPageRead(SPIX,addr/BYTES_PER_PAGE, addr % BYTES_PER_PAGE ,buf, bytes);	
}
   */

