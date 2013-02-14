#if defined  SDHC_TEST
#include "bsp.h"
#include "ff.h"	
#include "stm32f10x.h"
#include "sdcard.h"
#include "diskio.h"
#define NULL 0
void sdhc_test(void)
{
    FATFS fs;
	FIL fsrc;
//	static int cnt = 0;
	unsigned int i, bw;
	unsigned char res;
	SDCard_Init();
	disk_initialize(0);
	f_mount(0, &fs);				                  //注册到文件系统0区	
	res = f_open(&fsrc, "0:77长期按时的服乳法个个.txt",FA_CREATE_ALWAYS| FA_WRITE |FA_READ) ;
	if(res)
	{
		while(1);
	}
	for(i = 0 ; i <4 ;i++)
	{
    	res = f_lseek(&fsrc, fsrc.fsize);  /* 移动文件读/写指针到文件结束处，以便添加数据 */ 
		res = f_write(&fsrc, "Q我的44444444444rrrrrrr011111111111\n", sizeof("Q我的44444444444rrrrrrr011111111111\n"), &bw);
	}
   	f_close(&fsrc);
	f_mount(0, NULL);
	while(1);
}
int main (void)
{
	BSP_Init();
	sdhc_test();
}
#endif


