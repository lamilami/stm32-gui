/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* by grqd_xp                                                            */
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/
#include <string.h>
#include "diskio.h"
//#include "sdcard.h"
#include "sd_spi_driver.h"

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */
/* Note that Tiny-FatFs supports only single drive and always            */
/* accesses drive number 0.                                              */

#define SECTOR_SIZE 512U

//u32 buff2[512/4];
/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{	
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{  /*
  //memset(buff2, 0, sizeof(buff2));
	if(count==1)
        {
          SD_ReadBlock(sector << 9 ,(u32 *)(&buff[0]),SECTOR_SIZE);
          //memcpy(buff,buff2,SECTOR_SIZE);
	}
	else
        {
          SD_ReadMultiBlocks(sector << 9 ,(u32 *)(&buff[0]),SECTOR_SIZE,count);
          //memcpy(buff,buff2,SECTOR_SIZE * count);
	}
	  
	return RES_OK; */
	u8 res;
	res=SD_ReadDisk(buff,sector,count);	 
		 /*	if(res)//STM32 SPI的bug,在sd卡操作失败的时候如果不执行下面的语句,可能导致SPI读写异常
			{
				SD_SPI_SpeedLow();
				SD_SPI_ReadWriteByte(0xff);//提供额外的8个时钟
				SD_SPI_SpeedHigh();
			}	*/
			//处理返回值，将SPI_SD_driver.c的返回值转成ff.c的返回值
    if(res==0x00)return RES_OK;	 
    else 
	{
		return RES_ERROR;
	}
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
/*
  //memset(buff2, 0, sizeof(buff2));
	if(count==1)
        {
          //memcpy(buff2,buff,SECTOR_SIZE);
          SD_WriteBlock(sector << 9 ,(u32 *)(&buff[0]),SECTOR_SIZE);
	}
	else
        {
          //memcpy(buff2,buff,SECTOR_SIZE * count);
          SD_WriteMultiBlocks(sector << 9 ,(u32 *)(&buff[0]),SECTOR_SIZE,count);
	}
        
  return RES_OK;  */
  u8 res;
	res=SD_WriteDisk((u8*)buff,sector,count);
	 //处理返回值，将SPI_SD_driver.c的返回值转成ff.c的返回值
    if(res == 0x00)return RES_OK;	 
    else 
	{
		return RES_ERROR;
	}
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{

	/*return RES_OK;  */
	u8 res;
	res = sd_init();//SD_Initialize() 
		 /*	if(res)//STM32 SPI的bug,在sd卡操作失败的时候如果不执行下面的语句,可能导致SPI读写异常
			{
				SD_SPI_SpeedLow();
				SD_SPI_ReadWriteByte(0xff);//提供额外的8个时钟
				SD_SPI_SpeedHigh();
			} */
	if(res)return  STA_NOINIT;
	else return RES_OK;
}

DWORD get_fattime(void){
	return 0;
}























