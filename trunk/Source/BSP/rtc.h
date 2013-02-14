/******************************************************************************

                  ��Ȩ���� (C), 2012-2022, �����

 ******************************************************************************
  �� �� ��   : rtc.h
  �� �� ��   : ����
  ��    ��   : ganjinming
  ��������   : 2012��9��11��
  ����޸�   :
  ��������   : rtc.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��11��
    ��    ��   : ganjinming
    �޸�����   : �����ļ�

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
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/
 typedef struct
{
    
	//������������
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
 * �ⲿ����ԭ��˵��                             *
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
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
#define RTCClockSource_LSE



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __RTC_H__ */
