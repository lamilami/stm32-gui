#line 1 "Source\\uCOS-II\\Source\\os_task.c"





















 

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






	 	   	  		 			 	    		   		 		 	 	 			 	    		   	 			 	  	 		 				 		  			 		 					 	  	  		      		  	   		      		  	 		 	      		   		 		  	 		 	      		  		  		  
#line 26 "Source\\uCOS-II\\Source\\os_task.c"


 



















 


INT8U  OSTaskChangePrio (INT8U  oldprio,
                         INT8U  newprio)
{

    OS_EVENT  *pevent;




    OS_TCB    *ptcb;
    INT8U      y_new;
    INT8U      x_new;
    INT8U      y_old;
    OS_PRIO    bity_new;
    OS_PRIO    bitx_new;
    OS_PRIO    bity_old;
    OS_PRIO    bitx_old;

    OS_CPU_SR  cpu_sr = 0u;                                  



 

    if (oldprio >= 63u) {
        if (oldprio != 0xFFu) {
            return (42u);
        }
    }
    if (newprio >= 63u) {
        return (42u);
    }

    {cpu_sr = OS_CPU_SR_Save();};
    if (OSTCBPrioTbl[newprio] != (OS_TCB *)0) {              
        {OS_CPU_SR_Restore(cpu_sr);};
        return (40u);
    }
    if (oldprio == 0xFFu) {                           
        oldprio = OSTCBCur->OSTCBPrio;                       
    }
    ptcb = OSTCBPrioTbl[oldprio];
    if (ptcb == (OS_TCB *)0) {                               
        {OS_CPU_SR_Restore(cpu_sr);};                                  
        return (41u);
    }
    if (ptcb == ((OS_TCB *)1)) {                           
        {OS_CPU_SR_Restore(cpu_sr);};                                  
        return (67u);
    }

    y_new                 = (INT8U)(newprio >> 3u);          
    x_new                 = (INT8U)(newprio & 0x07u);




    bity_new              = (OS_PRIO)(1uL << y_new);
    bitx_new              = (OS_PRIO)(1uL << x_new);

    OSTCBPrioTbl[oldprio] = (OS_TCB *)0;                     
    OSTCBPrioTbl[newprio] =  ptcb;                           
    y_old                 =  ptcb->OSTCBY;
    bity_old              =  ptcb->OSTCBBitY;
    bitx_old              =  ptcb->OSTCBBitX;
    if ((OSRdyTbl[y_old] &   bitx_old) != 0u) {              
         OSRdyTbl[y_old] &= (OS_PRIO)~bitx_old;
         if (OSRdyTbl[y_old] == 0u) {
             OSRdyGrp &= (OS_PRIO)~bity_old;
         }
         OSRdyGrp        |= bity_new;                        
         OSRdyTbl[y_new] |= bitx_new;
    }


    pevent = ptcb->OSTCBEventPtr;
    if (pevent != (OS_EVENT *)0) {
        pevent->OSEventTbl[y_old] &= (OS_PRIO)~bitx_old;     
        if (pevent->OSEventTbl[y_old] == 0u) {
            pevent->OSEventGrp    &= (OS_PRIO)~bity_old;
        }
        pevent->OSEventGrp        |= bity_new;               
        pevent->OSEventTbl[y_new] |= bitx_new;
    }
#line 152 "Source\\uCOS-II\\Source\\os_task.c"

    ptcb->OSTCBPrio = newprio;                               
    ptcb->OSTCBY    = y_new;
    ptcb->OSTCBX    = x_new;
    ptcb->OSTCBBitY = bity_new;
    ptcb->OSTCBBitX = bitx_new;
    {OS_CPU_SR_Restore(cpu_sr);};
    if (OSRunning == 1u) {
        OS_Sched();                                          
    }
    return (0u);
}

 






































 

#line 257 "Source\\uCOS-II\\Source\\os_task.c"
 




































































 
 

INT8U  OSTaskCreateExt (void   (*task)(void *p_arg),
                        void    *p_arg,
                        OS_STK  *ptos,
                        INT8U    prio,
                        INT16U   id,
                        OS_STK  *pbos,
                        INT32U   stk_size,
                        void    *pext,
                        INT16U   opt)
{
    OS_STK    *psp;
    INT8U      err;

    OS_CPU_SR  cpu_sr = 0u;











    if (prio > 63u) {              
        return (42u);
    }

    {cpu_sr = OS_CPU_SR_Save();};
    if (OSIntNesting > 0u) {                  
        {OS_CPU_SR_Restore(cpu_sr);};
        return (60u);
    }
    if (OSTCBPrioTbl[prio] == (OS_TCB *)0) {  
        OSTCBPrioTbl[prio] = ((OS_TCB *)1); 
                                              
        {OS_CPU_SR_Restore(cpu_sr);};


        OS_TaskStkClr(pbos, stk_size, opt);                     


        psp = OSTaskStkInit(task, p_arg, ptos, opt);            
        err = OS_TCBInit(prio, psp, pbos, id, stk_size, pext, opt);
        if (err == 0u) {
            if (OSRunning == 1u) {                         
                OS_Sched();
            }
        } else {
            {cpu_sr = OS_CPU_SR_Save();};
            OSTCBPrioTbl[prio] = (OS_TCB *)0;                   
            {OS_CPU_SR_Restore(cpu_sr);};
        }
        return (err);
    }
    {OS_CPU_SR_Restore(cpu_sr);};
    return (40u);
}

 


































 

#line 525 "Source\\uCOS-II\\Source\\os_task.c"
 












































 
 
#line 614 "Source\\uCOS-II\\Source\\os_task.c"
 






















 

#line 696 "Source\\uCOS-II\\Source\\os_task.c"

 





















 
#line 774 "Source\\uCOS-II\\Source\\os_task.c"

 
















 


INT8U  OSTaskResume (INT8U prio)
{
    OS_TCB    *ptcb;

    OS_CPU_SR  cpu_sr = 0u;





    if (prio >= 63u) {                              
        return (42u);
    }

    {cpu_sr = OS_CPU_SR_Save();};
    ptcb = OSTCBPrioTbl[prio];
    if (ptcb == (OS_TCB *)0) {                                 
        {OS_CPU_SR_Restore(cpu_sr);};
        return (70u);
    }
    if (ptcb == ((OS_TCB *)1)) {                             
        {OS_CPU_SR_Restore(cpu_sr);};
        return (67u);
    }
    if ((ptcb->OSTCBStat & 0x08u) != 0x00u) {  
        ptcb->OSTCBStat &= (INT8U)~(INT8U)0x08u;     
        if (ptcb->OSTCBStat == 0x00u) {                  
            if (ptcb->OSTCBDly == 0u) {
                OSRdyGrp               |= ptcb->OSTCBBitY;     
                OSRdyTbl[ptcb->OSTCBY] |= ptcb->OSTCBBitX;
                {OS_CPU_SR_Restore(cpu_sr);};
                if (OSRunning == 1u) {
                    OS_Sched();                                
                }
            } else {
                {OS_CPU_SR_Restore(cpu_sr);};
            }
        } else {                                               
            {OS_CPU_SR_Restore(cpu_sr);};
        }
        return (0u);
    }
    {OS_CPU_SR_Restore(cpu_sr);};
    return (68u);
}

 


















 

INT8U  OSTaskStkChk (INT8U         prio,
                     OS_STK_DATA  *p_stk_data)
{
    OS_TCB    *ptcb;
    OS_STK    *pchk;
    INT32U     nfree;
    INT32U     size;

    OS_CPU_SR  cpu_sr = 0u;





    if (prio > 63u) {                        
        if (prio != 0xFFu) {
            return (42u);
        }
    }
    if (p_stk_data == (OS_STK_DATA *)0) {               
        return (9u);
    }

    p_stk_data->OSFree = 0u;                            
    p_stk_data->OSUsed = 0u;
    {cpu_sr = OS_CPU_SR_Save();};
    if (prio == 0xFFu) {                         
        prio = OSTCBCur->OSTCBPrio;
    }
    ptcb = OSTCBPrioTbl[prio];
    if (ptcb == (OS_TCB *)0) {                          
        {OS_CPU_SR_Restore(cpu_sr);};
        return (67u);
    }
    if (ptcb == ((OS_TCB *)1)) {
        {OS_CPU_SR_Restore(cpu_sr);};
        return (67u);
    }
    if ((ptcb->OSTCBOpt & 0x0001u) == 0u) {  
        {OS_CPU_SR_Restore(cpu_sr);};
        return (69u);
    }
    nfree = 0u;
    size  = ptcb->OSTCBStkSize;
    pchk  = ptcb->OSTCBStkBottom;
    {OS_CPU_SR_Restore(cpu_sr);};

    while (*pchk++ == (OS_STK)0) {                     
        nfree++;
    }





    p_stk_data->OSFree = nfree * sizeof(OS_STK);           
    p_stk_data->OSUsed = (size - nfree) * sizeof(OS_STK);  
    return (0u);
}

 





















 


INT8U  OSTaskSuspend (INT8U prio)
{
    BOOLEAN    self;
    OS_TCB    *ptcb;
    INT8U      y;

    OS_CPU_SR  cpu_sr = 0u;





    if (prio == (63u)) {                             
        return (71u);
    }
    if (prio >= 63u) {                                
        if (prio != 0xFFu) {
            return (42u);
        }
    }

    {cpu_sr = OS_CPU_SR_Save();};
    if (prio == 0xFFu) {                                  
        prio = OSTCBCur->OSTCBPrio;
        self = 1u;
    } else if (prio == OSTCBCur->OSTCBPrio) {                    
        self = 1u;
    } else {
        self = 0u;                                         
    }
    ptcb = OSTCBPrioTbl[prio];
    if (ptcb == (OS_TCB *)0) {                                   
        {OS_CPU_SR_Restore(cpu_sr);};
        return (72u);
    }
    if (ptcb == ((OS_TCB *)1)) {                               
        {OS_CPU_SR_Restore(cpu_sr);};
        return (67u);
    }
    y            = ptcb->OSTCBY;
    OSRdyTbl[y] &= (OS_PRIO)~ptcb->OSTCBBitX;                    
    if (OSRdyTbl[y] == 0u) {
        OSRdyGrp &= (OS_PRIO)~ptcb->OSTCBBitY;
    }
    ptcb->OSTCBStat |= 0x08u;                          
    {OS_CPU_SR_Restore(cpu_sr);};
    if (self == 1u) {                                       
        OS_Sched();                                              
    }
    return (0u);
}

 

















 

#line 1059 "Source\\uCOS-II\\Source\\os_task.c"
 
























 


INT32U  OSTaskRegGet (INT8U   prio,
                      INT8U   id,
                      INT8U  *perr)
{

    OS_CPU_SR  cpu_sr = 0u;

    INT32U     value;
    OS_TCB    *ptcb;



    if (prio >= 63u) {
        if (prio != 0xFFu) {
            *perr = 42u;
            return (0u);
        }
    }
    if (id >= 1u) {
        *perr = 8u;
        return (0u);
    }

    {cpu_sr = OS_CPU_SR_Save();};
    if (prio == 0xFFu) {                   
        ptcb = OSTCBCur;
    } else {
        ptcb = OSTCBPrioTbl[prio];
    }
    value = ptcb->OSTCBRegTbl[id];
    {OS_CPU_SR_Restore(cpu_sr);};
    *perr = 0u;
    return (value);
}


 


























 


void  OSTaskRegSet (INT8U    prio,
                    INT8U    id,
                    INT32U   value,
                    INT8U   *perr)
{

    OS_CPU_SR  cpu_sr = 0u;

    OS_TCB    *ptcb;



    if (prio >= 63u) {
        if (prio != 0xFFu) {
            *perr = 42u;
            return;
        }
    }
    if (id >= 1u) {
        *perr = 8u;
        return;
    }

    {cpu_sr = OS_CPU_SR_Save();};
    if (prio == 0xFFu) {                   
        ptcb = OSTCBCur;
    } else {
        ptcb = OSTCBPrioTbl[prio];
    }
    ptcb->OSTCBRegTbl[id] = value;
    {OS_CPU_SR_Restore(cpu_sr);};
    *perr                 = 0u;
}


 













 

void  OS_TaskReturn (void)
{
    OSTaskReturnHook(OSTCBCur);                    




    for (;;) {
        OSTimeDly(1000u);
    }

}

 





















 

void  OS_TaskStkClr (OS_STK  *pbos,
                     INT32U   size,
                     INT16U   opt)
{
    if ((opt & 0x0001u) != 0x0000u) {       
        if ((opt & 0x0002u) != 0x0000u) {   

            while (size > 0u) {                         
                size--;
                *pbos++ = (OS_STK)0;                    
            }
#line 1258 "Source\\uCOS-II\\Source\\os_task.c"
        }
    }
}


	 	   	  		 			 	    		   		 		 	 	 			 	    		   	 			 	  	 		 				 		  			 		 					 	  	  		      		  	   		      		  	 		 	      		   		 		  	 		 	      		  		  		  
