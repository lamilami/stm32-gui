/******************************************************************************

                  ��Ȩ���� (C), 2012-2022, �����

 ******************************************************************************
  �� �� ��   : sd_spi_driver.c
  �� �� ��   : ����
  ��    ��   : ganjinming
  ��������   : 2012��12��22��
  ����޸�   :
  ��������   : SD����spiģʽ�µ������ļ�
  �����б�   :
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

  
 
  �޸���ʷ   :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ļ�

******************************************************************************/
/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include "sd_spi_driver.h"
 /*----------------------------------------------*
 * �궨��                                       *
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

// SD�����Ͷ���  
#define SD_TYPE_ERR     0x00
#define SD_TYPE_MMC     0x01
#define SD_TYPE_V1      0x02
#define SD_TYPE_V2      0x04
#define SD_TYPE_V2HC    0x06	   
// SD��ָ���  	   
#define CMD0    0       //����λ
#define CMD1    1
#define CMD8    8       //����8 ��SEND_IF_COND
#define CMD9    9       //����9 ����CSD����
#define CMD10   10      //����10����CID����
#define CMD12   12      //����12��ֹͣ���ݴ���
#define CMD16   16      //����16������SectorSize Ӧ����0x00
#define CMD17   17      //����17����sector
#define CMD18   18      //����18����Multi sector
#define CMD23   23      //����23�����ö�sectorд��ǰԤ�Ȳ���N��block
#define CMD24   24      //����24��дsector
#define CMD25   25      //����25��дMulti sector
#define CMD41   41      //����41��Ӧ����0x00
#define CMD55   55      //����55��Ӧ����0x01
#define CMD58   58      //����58����OCR��Ϣ
#define CMD59   59      //����59��ʹ��/��ֹCRC��Ӧ����0x00
//����д���Ӧ������
#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF
//SD����Ӧ�����
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF

#define	SD_CS                      PCout(11)          //SD��Ƭѡ�ź�

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/
	
/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
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
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/
    
/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/
    static u8  SD_Type=0;//��ȡSD��������
/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*****************************************************************************
 �� �� ��  : SD_ReadDisk
 ��������  : ��SD��������
 �������  : u8*buf     ��ȡ���ݵĻ�����   
             u32 sector ��ȡ��������ʼ���   
             u8 cnt     ��ȡ��������Ŀ 
 �������  : ��
 �� �� ֵ  :  0--ok;  ����--ʧ��.
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
u8 SD_ReadDisk(u8*buf,u32 sector,u8 cnt)
{
	u8 r1;
	if(SD_Type!=SD_TYPE_V2HC)
    {
        sector <<= 9;//ת��Ϊ�ֽڵ�ַ
    }
	if(cnt==1)
	{
		r1=SD_SendCmd(CMD17,sector,0X01);//������
		if(r1==0)//ָ��ͳɹ�
		{
			r1=SD_RecvData(buf,512);//����512���ֽ�	   
		}
	}
    else
	{
		r1=SD_SendCmd(CMD18,sector,0X01);//����������
		do
		{
			r1=SD_RecvData(buf,512);//����512���ֽ�	 
			buf+=512;  
		}while(--cnt && r1==0); 	
		SD_SendCmd(CMD12,0,0X01);	//����ֹͣ����
	}   
	SD_DisSelect();//ȡ��Ƭѡ
	return r1;
}

/*****************************************************************************
 �� �� ��  : SD_WriteDisk
 ��������  : дSD��������
 �������  : u8*buf      Ҫд������ݻ�����
             u32 sector  Ҫд�����ݵ���ʼ����
             u8 cnt      Ҫд���������Ŀ
 �������  : ��
 �� �� ֵ  : 0--ok;  ����--ʧ��.
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
u8 SD_WriteDisk(u8*buf,u32 sector,u8 cnt)
{
	u8 r1;
	if(SD_Type!=SD_TYPE_V2HC)
    {
        sector *= 512;//ת��Ϊ�ֽڵ�ַ
    }
	if(cnt==1)
	{
		r1=SD_SendCmd(CMD24,sector,0X01);//������
		if(r1==0)//ָ��ͳɹ�
		{
			r1=SD_SendBlock(buf,0xFE);//д512���ֽ�	   
		}
	}
    else
	{
		if(SD_Type!=SD_TYPE_MMC)
		{
			SD_SendCmd(CMD55,0,0X01);	
			SD_SendCmd(CMD23,cnt,0X01);//����ָ��	
		}
 		r1=SD_SendCmd(CMD25,sector,0X01);//����������
		if(r1==0)
		{
			do
			{
				r1=SD_SendBlock(buf,0xFC);//����512���ֽ�	 
				buf+=512;  
			}while(--cnt && r1==0);
			r1=SD_SendBlock(0,0xFD);//����512���ֽ� 
		}
	}   
	SD_DisSelect();//ȡ��Ƭѡ
	return r1;//
}


/*****************************************************************************
 �� �� ��  : sd_init
 ��������  : ��ʼ��SD��
 �������  : void  
 �������  : ��
 �� �� ֵ  : 0-OK ����--ʧ��
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
u8 sd_init(void)
{
    u8 r1;      // ���SD���ķ���ֵ
    u16 retry;  // �������г�ʱ����
    u8 buf[4];  
	u16 i;

	sd_low_level_Init();		             //��ʼ��IO
 	sd_spi_speed(SD_SPI_SPEED_LOW); //���õ�����ģʽ 
 	for(i=0; i<10; i++)
    {
        SD_SPI_ReadWriteByte(0xFF);//��������74������
    }
	retry=20;
	do
	{
		r1 = SD_SendCmd(CMD0,0,0x95);//����IDLE״̬
	}while((r1!=0x01) && retry--);
    
 	SD_Type=0;//Ĭ���޿�
 	
	if(r1==0x01)
	{
		if(SD_SendCmd(CMD8,0x1AA,0x87)==1)//SD V2.0
		{
			for(i=0;i<4;i++)
            {
                buf[i]=SD_SPI_ReadWriteByte(0xFF);  //Get trailing return value of R7 resp
            }
			if(buf[2]==0x01&&buf[3]==0xAA)//���Ƿ�֧��2.7~3.6V
			{
				retry=0xFFFE;
				do
				{
					SD_SendCmd(CMD55,0,0X01);	          //����CMD55
					r1=SD_SendCmd(CMD41,0x40000000,0X01);//����CMD41
				}while(r1&&retry--);
                
				if(retry&&SD_SendCmd(CMD58,0,0x01)==0)//����SD2.0���汾��ʼ
				{
					for(i=0; i<4; i++)
                    {
                        buf[i]=SD_SPI_ReadWriteByte(0xFF);//�õ�OCRֵ
                    }
					if(buf[0]&0x40)
                    {
                        SD_Type=SD_TYPE_V2HC;    //���CCS
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
			SD_SendCmd(CMD55,0,0X01);		//����CMD55
			r1=SD_SendCmd(CMD41,0,0X01);	//����CMD41
			if(r1<=1)
			{		
				SD_Type=SD_TYPE_V1;
				retry=0XFFFE;
				do //�ȴ��˳�IDLEģʽ
				{
					SD_SendCmd(CMD55,0,0X01);	//����CMD55
					r1=SD_SendCmd(CMD41,0,0X01);//����CMD41
				}while(r1&&retry--);
			}
            else
			{
				SD_Type=SD_TYPE_MMC;//MMC V3
				retry=0XFFFE;
				do //�ȴ��˳�IDLEģʽ
				{											    
					r1=SD_SendCmd(CMD1,0,0X01);//����CMD1
				}while(r1&&retry--);  
			}
			if(retry==0||SD_SendCmd(CMD16,512,0X01)!=0)
            {
                SD_Type=SD_TYPE_ERR;//����Ŀ�
            }
		}
	}
	SD_DisSelect();//ȡ��Ƭѡ
	sd_spi_speed(SD_SPI_SPEED_HIGH);//����
	if(SD_Type)
    {
        return 0;
    }
	else if(r1)
    {
        return r1; 
    }
	return 0xaa; //��������
}
/*****************************************************************************
 �� �� ��  : sd_low_level_Init
 ��������  : SD���ײ����ż�SPI����(��ʼ��)
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

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
 �� �� ��  : sd_spi_speed
 ��������  : ����SD��spi���ٶ�
 �������  : u8 SPI_BaudRate  
              ��ѡ��ֵΪ:
               SPI_BaudRatePrescaler_x(����x = 2,4,8,16,32,64,128,256)   

 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
void sd_spi_speed(u8 SPI_BaudRate)
 {
    SD_SPI->CR1&=0XFFC7;
	SD_SPI->CR1|=SPI_BaudRate;	
	SPI_Cmd(SD_SPI,ENABLE); 
 }

/*****************************************************************************
 �� �� ��  : SD_SPI_ReadWriteByte
 ��������  : ��spi�ж�дһ���ֽ�
 �������  : u8 TxData  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
u8 SD_SPI_ReadWriteByte(u8 TxData)
{					 	
	while (SPI_I2S_GetFlagStatus(SD_SPI, SPI_I2S_FLAG_TXE) == RESET); 		  
	SPI_I2S_SendData(SD_SPI, TxData); 
	while (SPI_I2S_GetFlagStatus(SD_SPI, SPI_I2S_FLAG_RXNE) == RESET);					    
	return SPI_I2S_ReceiveData(SD_SPI); 				    
}

/*****************************************************************************
 �� �� ��  : SD_DisSelect
 ��������  : SD��Ƭѡ����
 �������  : void  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
void SD_DisSelect(void)
{
	SD_CS=1;
 	SD_SPI_ReadWriteByte(0xff);//�ṩ�����8��ʱ��
}

/*****************************************************************************
 �� �� ��  : SD_Select
 ��������  : SD��Ƭѡʹ��
 �������  : void  
 �������  : ��
 �� �� ֵ  : 0 - Ƭѡ�ɹ�  1-Ƭѡʧ��
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

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
 �� �� ��  : SD_WaitReady
 ��������  : ��ѯSD���Ƿ�׼����
 �������  : void  
 �������  : ��
 �� �� ֵ  : 0--׼������; ����--�������
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

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
 �� �� ��  : SD_GetResponse
 ��������  : �ȴ�SD����Ӧ
 �������  : u8 Response  :Ҫ�õ��Ļ�Ӧֵ
 �������  : ��
 �� �� ֵ  : 0-�ɹ��õ��˸û�Ӧֵ
             ����-�õ���Ӧֵʧ��
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
u8 SD_GetResponse(u8 Response)
{
	u16 Count=0xFFFF;   						  
	while ((SD_SPI_ReadWriteByte(0xFF)!=Response)&&Count)
    {
        Count--;//�ȴ��õ�׼ȷ�Ļ�Ӧ  
    }
	if (Count==0)
    {
        return MSD_RESPONSE_FAILURE;//�õ���Ӧʧ��
    }
	else
    {
        return MSD_RESPONSE_NO_ERROR;//��ȷ��Ӧ
    }
}
	
/*****************************************************************************
 �� �� ��  : SD_RecvData
 ��������  : ��sd����ȡһ�����ݰ�������
 �������  : u8*buf   ��ȡ���ݵĻ�����
             u16 len  ��ȡ���ݳ���
 �������  : ��
 �� �� ֵ  : 0--�ɹ�;  ����--ʧ��;	
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
u8 SD_RecvData(u8 *buf,u16 len)
{			  	  
	if(SD_GetResponse(0xFE))
    {
        return 1;//�ȴ�SD������������ʼ����0xFE
    }
    while(len--)//��ʼ��������
    {
        *buf=SD_SPI_ReadWriteByte(0xFF);
        buf++;
    }
    //������2��αCRC��dummy CRC��
    SD_SPI_ReadWriteByte(0xFF);
    SD_SPI_ReadWriteByte(0xFF);									  					    
    return 0;//��ȡ�ɹ�
}
/*****************************************************************************
 �� �� ��  : SD_SendBlock
 ��������  : ��sd��д��һ�����ݰ������� 512�ֽ�
 �������  : u8*buf  д�����ݻ�����
             u8 cmd  д��ָ�� 
 �������  : ��
 �� �� ֵ  : 0--�ɹ�;  ����--ʧ��;
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
u8 SD_SendBlock(u8*buf,u8 cmd)
{	
	u16 t;		  	  
	if(SD_WaitReady())
    {
        return 1;//�ȴ�׼��ʧЧ
    }
	SD_SPI_ReadWriteByte(cmd);
	if(cmd!=0xFD)//���ǽ���ָ��
	{
		for(t=0; t<512; t++)
        {
            SD_SPI_ReadWriteByte(buf[t]);
         }
	    SD_SPI_ReadWriteByte(0xFF);  //����crc
	    SD_SPI_ReadWriteByte(0xFF);
		t=SD_SPI_ReadWriteByte(0xFF);//������Ӧ
		if((t&0x1F)!=0x05)return 2;  //��Ӧ����									  					    
	}						 									  					    
    return 0;//д��ɹ�
}
														  
/*****************************************************************************
 �� �� ��  : SD_SendCmd
 ��������  : ��SD������һ������
 �������  : u8 cmd   ���� 
             u32 arg  �������
             u8 crc   crcУ��ֵ	
 �������  : ��
 �� �� ֵ  : SD�����ص���Ӧ	
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��12��22��
    ��    ��   : ganjinming
    �޸�����   : �����ɺ���

*****************************************************************************/
u8 SD_SendCmd(u8 cmd, u32 arg, u8 crc)
{
    u8 r1;	
	u8 Retry=0; 
	SD_DisSelect();//ȡ���ϴ�Ƭѡ
	if(SD_Select())
    {
        return 0xFF;//ƬѡʧЧ
    }
	//����
    SD_SPI_ReadWriteByte(cmd | 0x40);//�ֱ�д������
    SD_SPI_ReadWriteByte(arg >> 24);
    SD_SPI_ReadWriteByte(arg >> 16);
    SD_SPI_ReadWriteByte(arg >> 8);
    SD_SPI_ReadWriteByte(arg);	  
    SD_SPI_ReadWriteByte(crc); 
	if(cmd==CMD12)
    {
        SD_SPI_ReadWriteByte(0xff);//Skip a stuff byte when stop reading
    }
    //�ȴ���Ӧ����ʱ�˳�
	Retry=0x1F;
	do
	{
		r1=SD_SPI_ReadWriteByte(0xFF);
	}while((r1&0x80) && Retry--);	 
	//����״ֵ̬
    return r1;
}




