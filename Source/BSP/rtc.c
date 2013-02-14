/******************************************************************************

                  版权所有 (C), 2012-2022, 浙大精益

 ******************************************************************************
  文 件 名   : rtc.c
  版 本 号   : 初稿
  作    者   : ganjinming
  生成日期   : 2012年9月11日
  最近修改   :
  功能描述   : 实时时钟模块（应用层）
  函数列表   :
              Is_Leap_Year
              RTC_Get_Time
              RTC_Get_Week
              RTC_Set
  修改历史   :
  1.日    期   : 2012年9月11日
    作    者   : ganjinming
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/

#include "rtc.h"
#include "gui_app.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_bkp.h"

/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/
tim w_timer;

const unsigned char mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
unsigned char*week[]={"Sunday","Monday","Tuesday","Wednesday", "Thursday", "Friday","Saturday"};

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/


/*****************************/


unsigned char RTC_Get_Week(unsigned short year,unsigned char month,unsigned char day)//	 0=sunday
{
    year--;
	if(month>2)
	{
	    month-=2;
	}
	else
	{
	    month+=10;
		year--;
	}
	return((year+(year/4)+(13*month-1)/5+day)%7);
}

unsigned char Is_Leap_Year(unsigned short year)		  //知道返回的值是多少
{
    return((year%4==0)&&(year%100!=0)||(year%400==0));
}

unsigned char RTC_Get_Time(tim *timer)
{
    static unsigned short daycnt=0;
	unsigned int timecount=0;
	unsigned int temp=0;
	unsigned short temp1=0;
	RTC_WaitForLastTask();
	timecount=RTC->CNTH;//得到计数器中的值(秒钟数)
	timecount<<=16;
	timecount+=RTC->CNTL;
	temp=timecount/86400; //得到天数(秒钟数对应的)
	if(daycnt!=temp)//超过一天了
	{
		daycnt=temp;
		temp1=1970; //从1970年开始
		while(temp>=365)
		{
			if(Is_Leap_Year(temp1))//是闰年
			{
				if(temp>=366)temp-=366;//闰年的秒钟数
				else {temp1++;break;}
			}
			else temp-=365; //平年
			temp1++;
		}
		timer->year=temp1;//得到年份
		temp1=0;
		while(temp>=28)//超过了一个月
		{
			if(Is_Leap_Year(timer->year)&&temp1==1)//当年是不是闰年/2月份
			{
				if(temp>=29)temp-=29;//闰年的秒钟数
				else break;
			}
			else
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//平年
				else break;
			}
			temp1++;
		}
		timer->month=temp1+1;//得到月份
		timer->date=temp+1; //得到日期
	}
	temp=timecount%86400; //得到秒钟数
	timer->hour=temp/3600; //小时
	timer->min=(temp%3600)/60; //分钟
	timer->sec=(temp%3600)%60; //秒钟
	//timer->sec = 0; //秒钟
	timer->week=RTC_Get_Week(timer->year,timer->month,timer->date);//获取星期
	return 0;
}

//设置时钟
//把输入的时钟转换为秒钟
//以1970年1月1日为基准
//1970~2099年为合法年份
//返回值:0，成功;其他:错误代码.
//月份数据表
//unsigned char const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表
//平年的月份日期表
//const unsigned char mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
unsigned char RTC_Set(tim timer)
{
	unsigned short t;
	unsigned int seccount=0;
	if(timer.year<1970||timer.year>2099)return 1;
	for(t=1970;t<timer.year;t++) //把所有年份的秒钟相加
	{
		if(Is_Leap_Year(t)!=0)seccount+=31622400;//闰年的秒钟数
		else seccount+=31536000; //平年的秒钟数
	}
	timer.month-=1;
	for(t=0;t<timer.month;t++) //把前面月份的秒钟数相加
	{
		seccount+=(unsigned int)mon_table[t]*86400;//月份秒钟数相加
		if(Is_Leap_Year(timer.year)&&t==1)seccount+=86400;//闰年2月份增加一天的秒钟数
	}
	seccount+=(unsigned int)(timer.date-1)*86400;//把前面日期的秒钟数相加
	seccount+=(unsigned int)timer.hour*3600;//小时秒钟数
	seccount+=(unsigned int)timer.min*60; //分钟秒钟数
	seccount+=timer.sec;//最后的秒钟加上去

	
	//设置时钟
	RCC->APB1ENR|=1<<28;//使能电源时钟
	RCC->APB1ENR|=1<<27;//使能备份时钟
	PWR->CR|=1<<8; //取消备份区写保护
	//上面三步是必须的!
	RTC->CRL|=1<<4; //允许配置
	RTC->CNTL=seccount&0xffff;
	RTC->CNTH=seccount>>16;
	RTC->CRL&=~(1<<4);//配置更新
	while(!(RTC->CRL&(1<<5)));//等待RTC寄存器操作完成
	return 0;
}




char RTC_Check(tim timer)
{
   if(Is_Leap_Year(timer.year))
    {
        if((timer.month == 2) && (timer.date >mon_table[timer.month-1]))
         {
           return ERROR;
           // GUI_MessageBox("请输入正确的日期","error!!",0); 
         }
        else
        {
            if(timer.date > mon_table[timer.month-1])
            {
                return ERROR;
              ///  GUI_MessageBox("请输入正确的日期","error!!",0); 
            }
        }   
     }
   else
    {
        if(timer.date > mon_table[timer.month-1])
         {
            return ERROR;
           // GUI_MessageBox("请输入正确的日期","error!!",0); 
         }
        
    }
   return SUCCESS;
   
}


RTC_time_to_string(char *buf ,tim timer)
{
	buf[0] = timer.year/1000 +'0';
    buf[1] = timer.year%1000/100 +'0';
    buf[2] = timer.year%100/10 +'0';
    buf[3] = timer.year%10 +'0';
                
    buf[4] = '-';
                
    buf[5] = timer.month/10  +'0';
    buf[6] = timer.month%10 +'0';

    buf[7] = '-';
                
    buf[8] = timer.date/10 +'0';
    buf[9] = timer.date%10 +'0';
                
    buf[10] = ' ';
                
    buf[11] = timer.hour/10  +'0';
    buf[12] = timer.hour%10 +'0';

    buf[13] = ':';
                
    buf[14] = timer.min/10 +'0';
    buf[15] = timer.min%10 +'0';

	buf[16] = ':';
	
	buf[17] = timer.sec/10 +'0';
    buf[18] = timer.sec%10 +'0';
    buf[19] = '\0';
	
}


void get_hour_min(char *buf ,tim timer)
{
	buf[0] = timer.hour/10  +'0';
    buf[1] = timer.hour%10 +'0';

    buf[2] = ':';
                
    buf[3] = timer.min/10 +'0';
    buf[4] = timer.min%10 +'0';
	buf[5] = '\0';

}

void RTC_Configuration(void)
{
	/* Enable PWR and BKP clocks */
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  	/* Allow access to BKP Domain */
  	PWR_BackupAccessCmd(ENABLE);

  	/* Reset Backup Domain */
  	BKP_DeInit();

#ifdef RTCClockSource_LSI
  /* Enable LSI */ 
  RCC_LSICmd(ENABLE);
  /* Wait till LSI is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {
  }

  /* Select LSI as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);  
#elif defined	RTCClockSource_LSE
  	/* Enable LSE */
  	RCC_LSEConfig(RCC_LSE_ON);
  	/* Wait till LSE is ready */
  	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  	{}

  	/* Select LSE as RTC Clock Source */
  	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
#endif
  	/* Enable RTC Clock */
  	RCC_RTCCLKCmd(ENABLE);

  	/* Wait for RTC registers synchronization */
  	RTC_WaitForSynchro();

  	/* Wait until last write operation on RTC registers has finished */
  	RTC_WaitForLastTask();

  	/* Enable the RTC Second */
  	RTC_ITConfig(RTC_IT_SEC, ENABLE);

  	/* Wait until last write operation on RTC registers has finished */
  	RTC_WaitForLastTask();

  	/* Set RTC prescaler: set RTC period to 1sec */
      /* Set RTC prescaler: set RTC period to 1sec */
#ifdef RTCClockSource_LSI
  		RTC_SetPrescaler(31999); /* RTC period = RTCCLK/RTC_PR = (32.000 KHz)/(31999+1) */
#elif defined	RTCClockSource_LSE
  		RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
#endif

  //	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  	/* Wait until last write operation on RTC registers has finished */
  	RTC_WaitForLastTask();
}
void RTC_Config_Init(void)
{
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A1 )
	{
	    RTC_Configuration(); 
		RTC_WaitForLastTask();
	//	RTC_SetCounter(Time_Regulate());		   	 	 
	   // RTC_Set(2010,11,14,15,38,30);

		RTC_WaitForLastTask(); 

		BKP_WriteBackupRegister(BKP_DR1, 0xA5A1);
	}
	else
	{
		RTC_WaitForSynchro();        				
													
	 	RTC_WaitForLastTask();       				
																									 
     	RTC_ITConfig(RTC_IT_SEC, ENABLE);   		
													
     	RTC_WaitForLastTask();
	} 
}
