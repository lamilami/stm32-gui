/******************************************************************************

                  版权所有 (C), 2012-2022, 浙大精益

 ******************************************************************************
  文 件 名   : rtc.h
  版 本 号   : 初稿
  作    者   : ganjinming
  生成日期   : 2012年9月11日
  最近修改   :
  功能描述   : rtc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月11日
    作    者   : ganjinming
    修改内容   : 创建文件

******************************************************************************/
#include"SimSwitch.h"


#ifndef __RTC_H__
#define __RTC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/
 typedef struct
{
    
	//公历日月年周
	unsigned short year;
	unsigned char  month;
	unsigned char  date;

	unsigned char week;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
}tim;

    extern tim w_timer;
    extern const unsigned char SecStatus;
    extern unsigned char *week[];
/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/
    extern unsigned char RTC_Get_Week(unsigned short year,unsigned char month,unsigned char day);
    extern unsigned char Is_Leap_Year(unsigned short year);
    extern unsigned char RTC_Get_Time(tim *timer);
    extern unsigned char RTC_Set(tim timer);


    extern char RTC_Check(tim timer);


	extern RTC_time_to_string(char *buf ,tim timer);
	extern void get_hour_min(char *buf ,tim timer);
	extern void RTC_Configuration(void);
	extern void RTC_Config_Init(void);
/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#define RTCClockSource_LSE



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __RTC_H__ */
