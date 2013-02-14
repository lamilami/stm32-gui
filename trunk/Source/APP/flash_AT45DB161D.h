
#ifndef __AT45DB161D_H
#define __AT45DB161D_H

#include "stm32f10x.h"
//#include "stm32f10x_spi.h" 
#define SPI_FLASH_SPIX  SPI3
/*******************************/
#define COMM_BUFFER1_WRITE	   0X84
#define COMM_BUFFER2_WRITE	   0X87

#define DUMMY_BYTE   0u

#if DUMMY_BYTE == 0u
	#define COMM_BUFFER1_READ	   0XD1	//0xd1--No Dummy Byte     
	#define COMM_BUFFER2_READ	   0XD3 //0xd3--No Dummy Byte     
#elif DUMMY_BYTE == 1u
	#define COMM_BUFFER1_READ	   0XD4	//1 Dummy Byte    
	#define COMM_BUFFER2_READ	   0XD6 //1 Dummy Byte  
#endif
/***************************************/

/*************************************/
//#define MMemPageRead         0xD2	 //Main Memory Page Read 
//	#define ConArrayRead         0xE8	 //Continuous Array Read(Legacy Command)
//	#define ConArrayRead         0x03	 //ContinuousArrayRead(Low Frequency)
//	#define ConArrayRead         0x0B	 //ContinuousArrayRead(High Frequency)


#define BUF1TOMEM_WITH_ERASE       0x83  //  Buffer 1 to Main Memory Page Program with Built-in Error 83H
#define BUF2TOMEM_WITH_ERASE       0x86  //		 Buffer 2 to Main Memory Page Program with Built-in Error 86H
#define BUF1TOMEM_WITHOUT_ERASE    0x88	 //	Buffer 1 to Main Memory Page Program without Built-in Error 88H
#define BUF2TOMEM_WITHOUT_ERASE    0x89	 //	 Buffer 2 to Main Memory Page Program without Built-in Error 89H

#define PAGE_ERASE       0X81
#define BLOCK_ERASE      0X50
#define SECTOR_ERASE     0X7C
#define CHIP_ERASEBYTE0  0XC7
#define CHIP_ERASEBYTE1	 0X94
#define CHIP_ERASEBYTE2	 0X80
#define CHIP_ERASEBYTE3	 0X9A

#define MAX_PAGE          4096u
#define MAX_BLOCK		  512u
#define MAX_SECTOR        
#define MAX_BYTE_PAGE     528u


#define MEMTOBUFF1       0x53
#define MEMTOBUFF2       0x55	
#define BYTES_PER_PAGE   512
typedef struct {
	uint16_t  pageaddr;
	uint16_t  byteaddr;
}PageByteaddr;

typedef enum Error_status
{
    OP_OK = 0,
	PageOver ,
	ByteOver ,
	ReadByteOver
} Error_status;

void spi_at45db161d_initial(void);
void BUFFER_Write(SPI_TypeDef *SPIx ,uint8_t buf_num, uint16_t addr,uint8_t *spi_data, uint16_t spi_data_num);
void BUFFER_Read (SPI_TypeDef *SPIx ,uint8_t buf_num, uint16_t addr,uint8_t *spi_data, uint16_t spi_data_num);
Error_status BufToMainMemPage(SPI_TypeDef *SPIx,uint8_t buf_Erase, uint16_t page_addr);
Error_status MMemPageRead(SPI_TypeDef *SPIx,uint16_t Pageaddr, uint16_t Byteaddr ,uint8_t *data_buf, uint16_t data_num);
Error_status MemPageToBUFF(SPI_TypeDef *SPIx,uint8_t buffer_num,uint16_t Pageaddr);
void FlashWaitBusy(SPI_TypeDef *SPIx);

//void LCD_ReadFlashBytes(u32 addr,u8* buf,u8 Bytes);
#endif

