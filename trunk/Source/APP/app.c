/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2006; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   STM3210B-EVAL Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : Brian Nagel
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
 #ifndef SDHC_TEST
#include <includes.h>

/* ----------------- APPLICATION GLOBALS ------------------ */
 OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];
__align(8) static  OS_STK AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE];
 OS_STK AppTaskKbdStk[APP_TASK_KBD_STK_SIZE];

 OS_STK AppTaskNetStk[APP_TASK_NET_SIZE];

//static  OS_EVENT       *AppUserIFMbox;

int ExTick;

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void AppTaskCreate(void);
static void AppTaskStart(void *p_arg);

static void AppTaskUserIF(void *p_arg);
static void AppTaskKbd(void *p_arg);

static void AppTaskNet(void *p_arg);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/


int  main (void)
{

    OSInit();                          

   // Create the start task 
OSTaskCreateExt(AppTaskStart,(void *)0,(OS_STK *)&AppTaskStartStk[APP_TASK_START_STK_SIZE-1],APP_TASK_START_PRIO,APP_TASK_START_PRIO,(OS_STK *)&AppTaskStartStk[0],APP_TASK_START_STK_SIZE,(void *)0,OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);

#if (OS_TASK_NAME_SIZE > 13)
    OSTaskNameSet(APP_TASK_START_PRIO, "Start Task", &err);
#endif

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II)       */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
		 int ma,i;
		 static unsigned int read_data;
  (void)p_arg;
 
   BSP_Init();  

        			                                      /* Initialize BSP functions                                 */
   #if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity                                   */
   #endif

//   AppUserIFMbox = OSMboxCreate((void *)0);                  /* Create MBOX for communication between Kbd and UserIF     */
   AppTaskCreate();                                            /* Create application tasks                                 */
    
   while(DEF_TRUE)
	 {  
	  /* Task body, always written as an infinite loop. */
	   OSTaskSuspend(OS_PRIO_SELF);

     }
}


/*
*********************************************************************************************************
*                                      CREATE APPLICATION TASKS
*
* Description:  This function creates the application tasks.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

static  void  AppTaskCreate(void)
{
  //INT8U  err;

  OSTaskCreateExt(AppTaskUserIF,(void *)0,(OS_STK *)&AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE-1],APP_TASK_USER_IF_PRIO,APP_TASK_USER_IF_PRIO,(OS_STK *)&AppTaskUserIFStk[0],
                    APP_TASK_USER_IF_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);


#if (OS_TASK_NAME_SIZE > 8)
  OSTaskNameSet(APP_TASK_USER_IF_PRIO, "User I/F", &err);
#endif


  OSTaskCreateExt(AppTaskKbd,(void *)0,(OS_STK *)&AppTaskKbdStk[APP_TASK_KBD_STK_SIZE-1],APP_TASK_KBD_PRIO,APP_TASK_KBD_PRIO,(OS_STK *)&AppTaskKbdStk[0],
                    APP_TASK_KBD_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);


  OSTaskCreateExt(AppTaskNet,(void *)0,(OS_STK *)&AppTaskNetStk[APP_TASK_NET_SIZE-1],APP_TASK_NET_PRIO,APP_TASK_NET_PRIO,(OS_STK *)&AppTaskNetStk[0],
                    APP_TASK_NET_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);

#if (OS_TASK_NAME_SIZE > 8)
  OSTaskNameSet(APP_TASK_KBD_PRIO, "Keyboard", &err)
#endif
}


/*
*********************************************************************************************************
*                                         USER INTERFACE TASK
*
* Description : This task updates the LCD screen based on messages passed to it by AppTaskKbd().
*
* Arguments   : p_arg   is the argument passed to 'AppStartUserIF()' by 'OSTaskCreate()'.
*
* Returns     : none
*********************************************************************************************************
*/
extern void  MainTask(void);
static  void  AppTaskUserIF (void *p_arg)
{
 
 (void)p_arg;
  // GUI_Init();
  while(DEF_TRUE) 
    {
	  MainTask(); 
	 // GUIDEMO_Touch();
    }
}


/*
*********************************************************************************************************
*                                    KEYBOARD RESPONSE TASK
*
* Description : This task monitors the state of the push buttons and passes messages to AppTaskUserIF()
*
* Arguments   : p_arg   is the argument passed to 'AppStartKbd()' by 'OSTaskCreate()'.
*
* Returns     : none
*********************************************************************************************************
*/

static  void  AppTaskKbd (void *p_arg)
{
   u8 tick=0;
  (void)p_arg;
   while(DEF_TRUE) 
     {
	 	tick++;
        OSTimeDlyHMSM(0,0,0,6); 
	    GUI_TOUCH_Exec(); 

		if(tick&0x10)
		{
		  //  GPIO_SetBits(GPIOF,GPIO_Pin_6);
		  //  GPIO_ResetBits(GPIOF,GPIO_Pin_10);
		}
		else
		{
		 	//GPIO_ResetBits(GPIOF,GPIO_Pin_6);
			//GPIO_SetBits(GPIOF,GPIO_Pin_10);
		}
	   ;
	
     }
}

static void AppTaskNet(void *p_arg)
{
	 
	 while(1)
	{
	OSTimeDlyHMSM(0,0,0,10);    
	}
//	 Web_Server();
}


#endif

