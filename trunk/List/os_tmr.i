#line 1 "Source\\uCOS-II\\Source\\os_tmr.c"






















 

#line 1 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"




















 












 







 

#line 1 ".\\Source\\APP\\app_cfg.h"











 














 











 








 
















 















 







#line 45 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"
#line 1 ".\\Source\\APP\\os_cfg.h"






















 





                                        










                                        













                                        





                                        
#line 73 ".\\Source\\APP\\os_cfg.h"


                                        
#line 83 ".\\Source\\APP\\os_cfg.h"


                                        
#line 93 ".\\Source\\APP\\os_cfg.h"


                                        





                                        






                                        
#line 118 ".\\Source\\APP\\os_cfg.h"


                                        
#line 127 ".\\Source\\APP\\os_cfg.h"


                                        






                                        







	 	   	  		 			 	    		   		 		 	 	 			 	    		   	 			 	  	 		 				 		  			 		 					 	  	  		      		  	   		      		  	 		 	      		   		 		  	 		 	      		  		  		  
#line 46 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"
#line 1 ".\\Source\\uCOS-II\\Ports\\os_cpu.h"






















 
















 

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                     
typedef signed   char  INT8S;                     
typedef unsigned short INT16U;                    
typedef signed   short INT16S;                    
typedef unsigned int   INT32U;                    
typedef signed   int   INT32S;                    
typedef float          FP32;                      
typedef double         FP64;                      

typedef unsigned int   OS_STK;                    
typedef unsigned int   OS_CPU_SR;                 





















 












 









 


OS_CPU_SR  OS_CPU_SR_Save(void);
void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);


void       OSCtxSw(void);
void       OSIntCtxSw(void);
void       OSStartHighRdy(void);

void       PendSV_Handler(void);

                                                   
void       SysTick_Handler(void);
void       OS_CPU_SysTickInit(void);

                                                   
INT32U     OS_CPU_SysTickClkFreq(void);
#line 47 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"





 




























#line 88 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"









 




 
#line 111 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"







 








 
#line 134 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"


                                             





 

























 











 









 









 









 









 












 









 


#line 255 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"

#line 266 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"













#line 293 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"

#line 300 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"

#line 311 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"



#line 320 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"



#line 337 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"

 




 


typedef  INT8U    OS_PRIO;





typedef struct os_event {
    INT8U    OSEventType;                     
    void    *OSEventPtr;                      
    INT16U   OSEventCnt;                      
    OS_PRIO  OSEventGrp;                      
    OS_PRIO  OSEventTbl[((63u) / 8u + 1u)];   


    INT8U   *OSEventName;

} OS_EVENT;







 

#line 411 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"

 




 


typedef struct os_mbox_data {
    void   *OSMsg;                          
    OS_PRIO OSEventTbl[((63u) / 8u + 1u)];  
    OS_PRIO OSEventGrp;                     
} OS_MBOX_DATA;






 

#line 455 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"

 




 

#line 472 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"





 

#line 499 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"





 


typedef struct os_sem_data {
    INT16U  OSCnt;                           
    OS_PRIO OSEventTbl[((63u) / 8u + 1u)];   
    OS_PRIO OSEventGrp;                      
} OS_SEM_DATA;






 


typedef struct os_stk_data {
    INT32U  OSFree;                     
    INT32U  OSUsed;                     
} OS_STK_DATA;


 




 

typedef struct os_tcb {
    OS_STK          *OSTCBStkPtr;            


    void            *OSTCBExtPtr;            
    OS_STK          *OSTCBStkBottom;         
    INT32U           OSTCBStkSize;           
    INT16U           OSTCBOpt;               
    INT16U           OSTCBId;                


    struct os_tcb   *OSTCBNext;              
    struct os_tcb   *OSTCBPrev;              


    OS_EVENT        *OSTCBEventPtr;          







    void            *OSTCBMsg;               


#line 566 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"

    INT32U           OSTCBDly;               
    INT8U            OSTCBStat;              
    INT8U            OSTCBStatPend;          
    INT8U            OSTCBPrio;              

    INT8U            OSTCBX;                 
    INT8U            OSTCBY;                 
    OS_PRIO          OSTCBBitX;              
    OS_PRIO          OSTCBBitY;              






    INT32U           OSTCBCtxSwCtr;          
    INT32U           OSTCBCyclesTot;         
    INT32U           OSTCBCyclesStart;       
    OS_STK          *OSTCBStkBase;           
    INT32U           OSTCBStkUsed;           







    INT32U           OSTCBRegTbl[1u];

} OS_TCB;

 




 

#line 636 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"

 




 

extern  INT32U            OSCtxSwCtr;                


extern  OS_EVENT         *OSEventFreeList;           
extern  OS_EVENT          OSEventTbl[10u]; 








extern  INT8U             OSCPUUsage;                
extern  INT32U            OSIdleCtrMax;              
extern  INT32U            OSIdleCtrRun;              
extern  BOOLEAN           OSStatRdy;                 
extern  OS_STK            OSTaskStatStk[128u];       


extern  INT8U             OSIntNesting;              

extern  INT8U             OSLockNesting;             

extern  INT8U             OSPrioCur;                 
extern  INT8U             OSPrioHighRdy;             

extern  OS_PRIO           OSRdyGrp;                         
extern  OS_PRIO           OSRdyTbl[((63u) / 8u + 1u)];        

extern  BOOLEAN           OSRunning;                        

extern  INT8U             OSTaskCtr;                        

extern  volatile  INT32U  OSIdleCtr;                                  





extern  OS_STK            OSTaskIdleStk[128u];       


extern  OS_TCB           *OSTCBCur;                         
extern  OS_TCB           *OSTCBFreeList;                    
extern  OS_TCB           *OSTCBHighRdy;                     
extern  OS_TCB           *OSTCBList;                        
extern  OS_TCB           *OSTCBPrioTbl[63u + 1u];     
extern  OS_TCB            OSTCBTbl[20u + 2u];    


extern  INT8U             OSTickStepState;           













extern  volatile  INT32U  OSTime;                    


#line 726 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"

extern  INT8U   const     OSUnMapTbl[256];           

 





 





 




INT8U         OSEventNameGet          (OS_EVENT        *pevent,
                                       INT8U          **pname,
                                       INT8U           *perr);

void          OSEventNameSet          (OS_EVENT        *pevent,
                                       INT8U           *pname,
                                       INT8U           *perr);


#line 762 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"







 

#line 816 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"





 




void         *OSMboxAccept            (OS_EVENT        *pevent);


OS_EVENT     *OSMboxCreate            (void            *pmsg);







void         *OSMboxPend              (OS_EVENT        *pevent,
                                       INT32U           timeout,
                                       INT8U           *perr);


INT8U         OSMboxPendAbort         (OS_EVENT        *pevent,
                                       INT8U            opt,
                                       INT8U           *perr);



INT8U         OSMboxPost              (OS_EVENT        *pevent,
                                       void            *pmsg);



INT8U         OSMboxPostOpt           (OS_EVENT        *pevent,
                                       void            *pmsg,
                                       INT8U            opt);












 

#line 897 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"





 

#line 932 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"

 




 

#line 992 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"

 




 



INT16U        OSSemAccept             (OS_EVENT        *pevent);


OS_EVENT     *OSSemCreate             (INT16U           cnt);







void          OSSemPend               (OS_EVENT        *pevent,
                                       INT32U           timeout,
                                       INT8U           *perr);


INT8U         OSSemPendAbort          (OS_EVENT        *pevent,
                                       INT8U            opt,
                                       INT8U           *perr);


INT8U         OSSemPost               (OS_EVENT        *pevent);







void          OSSemSet                (OS_EVENT        *pevent,
                                       INT16U           cnt,
                                       INT8U           *perr);




 




 

INT8U         OSTaskChangePrio        (INT8U            oldprio,
                                       INT8U            newprio);


#line 1055 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"


INT8U         OSTaskCreateExt         (void           (*task)(void *p_arg),
                                       void            *p_arg,
                                       OS_STK          *ptos,
                                       INT8U            prio,
                                       INT16U           id,
                                       OS_STK          *pbos,
                                       INT32U           stk_size,
                                       void            *pext,
                                       INT16U           opt);







#line 1082 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"


INT8U         OSTaskResume            (INT8U            prio);
INT8U         OSTaskSuspend           (INT8U            prio);



INT8U         OSTaskStkChk            (INT8U            prio,
                                       OS_STK_DATA     *p_stk_data);










INT32U        OSTaskRegGet            (INT8U            prio,
                                       INT8U            id,
                                       INT8U           *perr);

void          OSTaskRegSet            (INT8U            prio,
                                       INT8U            id,
                                       INT32U           value,
                                       INT8U           *perr);


 




 

void          OSTimeDly               (INT32U           ticks);


INT8U         OSTimeDlyHMSM           (INT8U            hours,
                                       INT8U            minutes,
                                       INT8U            seconds,
                                       INT16U           ms);



INT8U         OSTimeDlyResume         (INT8U            prio);



INT32U        OSTimeGet               (void);
void          OSTimeSet               (INT32U           ticks);


void          OSTimeTick              (void);





 

#line 1177 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"





 

void          OSInit                  (void);

void          OSIntEnter              (void);
void          OSIntExit               (void);






void          OSSchedLock             (void);
void          OSSchedUnlock           (void);


void          OSStart                 (void);

void          OSStatInit              (void);

INT16U        OSVersion               (void);

 





 






INT8U         OS_EventTaskRdy         (OS_EVENT        *pevent,
                                       void            *pmsg,
                                       INT8U            msk,
                                       INT8U            pend_stat);

void          OS_EventTaskWait        (OS_EVENT        *pevent);

void          OS_EventTaskRemove      (OS_TCB          *ptcb,
                                       OS_EVENT        *pevent);

#line 1233 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"

void          OS_EventWaitListInit    (OS_EVENT        *pevent);







void          OS_MemClr               (INT8U           *pdest,
                                       INT16U           size);

void          OS_MemCopy              (INT8U           *pdest,
                                       INT8U           *psrc,
                                       INT16U           size);









void          OS_Sched                (void);


INT8U         OS_StrLen               (INT8U           *psrc);


void          OS_TaskIdle             (void            *p_arg);

void          OS_TaskReturn           (void);


void          OS_TaskStat             (void            *p_arg);



void          OS_TaskStkClr           (OS_STK          *pbos,
                                       INT32U           size,
                                       INT16U           opt);



void          OS_TaskStatStkChk       (void);


INT8U         OS_TCBInit              (INT8U            prio,
                                       OS_STK          *ptos,
                                       OS_STK          *pbos,
                                       INT16U           id,
                                       INT32U           stk_size,
                                       void            *pext,
                                       INT16U           opt);





 





 





void          OSInitHookBegin         (void);
void          OSInitHookEnd           (void);

void          OSTaskCreateHook        (OS_TCB          *ptcb);
void          OSTaskDelHook           (OS_TCB          *ptcb);

void          OSTaskIdleHook          (void);

void          OSTaskReturnHook        (OS_TCB          *ptcb);

void          OSTaskStatHook          (void);
OS_STK       *OSTaskStkInit           (void           (*task)(void *p_arg),
                                       void            *p_arg,
                                       OS_STK          *ptos,
                                       INT16U           opt);


void          OSTaskSwHook            (void);


void          OSTCBInitHook           (OS_TCB          *ptcb);


void          OSTimeTickHook          (void);


 





 

#line 1358 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"







 







 










 





 

#line 1402 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"






























 

#line 1440 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"


























 

#line 1478 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"














 

#line 1500 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"














 

#line 1526 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"






































 

#line 1572 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"






















 

#line 1602 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"























































#line 1664 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"





 





















 

#line 1737 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"






 


























#line 1777 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"



































 

#line 1889 ".\\Source\\uCOS-II\\Source\\ucos_ii.h"






	 	   	  		 			 	    		   		 		 	 	 			 	    		   	 			 	  	 		 				 		  			 		 					 	  	  		      		  	   		      		  	 		 	      		   		 		  	 		 	      		  		  		  
#line 26 "Source\\uCOS-II\\Source\\os_tmr.c"












 





 








 

#line 63 "Source\\uCOS-II\\Source\\os_tmr.c"

 








































 

#line 177 "Source\\uCOS-II\\Source\\os_tmr.c"

 



















 

#line 252 "Source\\uCOS-II\\Source\\os_tmr.c"

 





















 

#line 332 "Source\\uCOS-II\\Source\\os_tmr.c"

 




















 

#line 429 "Source\\uCOS-II\\Source\\os_tmr.c"

 























 

#line 501 "Source\\uCOS-II\\Source\\os_tmr.c"

 



















 

#line 576 "Source\\uCOS-II\\Source\\os_tmr.c"

 


































 

#line 695 "Source\\uCOS-II\\Source\\os_tmr.c"

 

















 

#line 726 "Source\\uCOS-II\\Source\\os_tmr.c"

 










 

#line 758 "Source\\uCOS-II\\Source\\os_tmr.c"












 

#line 793 "Source\\uCOS-II\\Source\\os_tmr.c"

 











 

#line 856 "Source\\uCOS-II\\Source\\os_tmr.c"

 









 

#line 918 "Source\\uCOS-II\\Source\\os_tmr.c"

 















 

#line 973 "Source\\uCOS-II\\Source\\os_tmr.c"

 










 

#line 1019 "Source\\uCOS-II\\Source\\os_tmr.c"

 










 

#line 1073 "Source\\uCOS-II\\Source\\os_tmr.c"
	 	   	  		 			 	    		   		 		 	 	 			 	    		   	 			 	  	 		 				 		  			 		 					 	  	  		      		  	   		      		  	 		 	      		   		 		  	 		 	      		  		  		  
