/******************** (C) COPYRIGHT 2011 ����Ƕ��ʽ���������� ********************
 * �ļ���  ��spi.c
 * ����    ��ENC28J60(��̫��оƬ) SPI�ӿ�Ӧ�ú�����
 *          
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ� ------------------------------------
 *           |PB13         ��ENC28J60-INT (û�õ�)|
 *           |PA6-SPI1-MISO��ENC28J60-SO          |
 *           |PA7-SPI1-MOSI��ENC28J60-SI          |
 *           |PA5-SPI1-SCK ��ENC28J60-SCK         |
 *           |PA4-SPI1-NSS ��ENC28J60-CS          |
 *           |PE1          ��ENC28J60-RST (û��)  |
 *            ------------------------------------
 * ��汾  ��ST3.0.0
 * ����    ��fire  QQ: 313303034
 * ����    ��firestm32.blog.chinaunix.net 
**********************************************************************************/
#include "spi_enc28j60.h"

/*
 * ��������SPI1_Init
 * ����  ��ENC28J60 SPI �ӿڳ�ʼ��
 * ����  ���� 
 * ���  ����
 * ����  ����
 */																						  
void SPI_Enc28j60_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;	
	
	/* ʹ�� SPI1 ʱ�� */                         
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 , ENABLE);

	/* ---------enc28j60 ͨ��I/O��ʼ��----------------
	 * PA5-SPI1-SCK :ENC28J60_SCK
	 * PA6-SPI1-MISO:ENC28J60_SO
	 * PA7-SPI1-MOSI:ENC28J60_SI	 
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		   // �������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* ---------enc28j60 ����I/O��ʼ��----------------*/
	/* PA4-SPI1-NSS:ENC28J60_CS */ 											 // Ƭѡ
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   // �������
  GPIO_Init(GPIOB, &GPIO_InitStructure);						  
  GPIO_SetBits(GPIOB, GPIO_Pin_12);										 // �Ȱ�Ƭѡ���ߣ������õ�ʱ��������

	/* PB13:ENC28J60_INT */						// �ж�����û�õ�

	/* PE1:ENC28J60_RST*/				      // ��λ�ƺ�����Ҳ����
 

	/* SPI1 ���� */ 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);
	
	/* ʹ�� SPI1  */
	SPI_Cmd(SPI2, ENABLE); 
}

/*
 * ��������SPI2_ReadWrite
 * ����  ��SPI1��дһ�ֽ�����
 * ����  �� 
 * ���  ��
 * ����  ��
 */
unsigned char	SPI2_ReadWrite(unsigned char writedat)
{
	/* Loop while DR register in not emplty */
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET);
	
	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI2, writedat);
	
	/* Wait to receive a byte */
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	
	/* Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI2);
}

