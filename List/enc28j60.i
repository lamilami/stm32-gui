#line 1 "Source\\Net\\enc28j60.c"













 

#line 1 "Source\\Net\\enc28j60.h"



#line 1 ".\\Source\\FWLib\\cm3\\stm32f10x.h"























 



 



 
    






  


 
  


 

#line 59 ".\\Source\\FWLib\\cm3\\stm32f10x.h"


















 





#line 91 ".\\Source\\FWLib\\cm3\\stm32f10x.h"







            
#line 106 ".\\Source\\FWLib\\cm3\\stm32f10x.h"





 






 
#line 125 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 



 



 
#line 144 ".\\Source\\FWLib\\cm3\\stm32f10x.h"




 
typedef enum IRQn
{
 
  NonMaskableInt_IRQn         = -14,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVCall_IRQn                 = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      

 
  WWDG_IRQn                   = 0,       
  PVD_IRQn                    = 1,       
  TAMPER_IRQn                 = 2,       
  RTC_IRQn                    = 3,       
  FLASH_IRQn                  = 4,       
  RCC_IRQn                    = 5,       
  EXTI0_IRQn                  = 6,       
  EXTI1_IRQn                  = 7,       
  EXTI2_IRQn                  = 8,       
  EXTI3_IRQn                  = 9,       
  EXTI4_IRQn                  = 10,      
  DMA1_Channel1_IRQn          = 11,      
  DMA1_Channel2_IRQn          = 12,      
  DMA1_Channel3_IRQn          = 13,      
  DMA1_Channel4_IRQn          = 14,      
  DMA1_Channel5_IRQn          = 15,      
  DMA1_Channel6_IRQn          = 16,      
  DMA1_Channel7_IRQn          = 17,      

#line 203 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 224 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 252 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 278 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 323 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 364 ".\\Source\\FWLib\\cm3\\stm32f10x.h"


  ADC1_2_IRQn                 = 18,      
  USB_HP_CAN1_TX_IRQn         = 19,      
  USB_LP_CAN1_RX0_IRQn        = 20,      
  CAN1_RX1_IRQn               = 21,      
  CAN1_SCE_IRQn               = 22,      
  EXTI9_5_IRQn                = 23,      
  TIM1_BRK_TIM9_IRQn          = 24,      
  TIM1_UP_TIM10_IRQn          = 25,      
  TIM1_TRG_COM_TIM11_IRQn     = 26,      
  TIM1_CC_IRQn                = 27,      
  TIM2_IRQn                   = 28,      
  TIM3_IRQn                   = 29,      
  TIM4_IRQn                   = 30,      
  I2C1_EV_IRQn                = 31,      
  I2C1_ER_IRQn                = 32,      
  I2C2_EV_IRQn                = 33,      
  I2C2_ER_IRQn                = 34,      
  SPI1_IRQn                   = 35,      
  SPI2_IRQn                   = 36,      
  USART1_IRQn                 = 37,      
  USART2_IRQn                 = 38,      
  USART3_IRQn                 = 39,      
  EXTI15_10_IRQn              = 40,      
  RTCAlarm_IRQn               = 41,      
  USBWakeUp_IRQn              = 42,      
  TIM8_BRK_TIM12_IRQn         = 43,      
  TIM8_UP_TIM13_IRQn          = 44,      
  TIM8_TRG_COM_TIM14_IRQn     = 45,      
  TIM8_CC_IRQn                = 46,      
  ADC3_IRQn                   = 47,      
  FSMC_IRQn                   = 48,      
  SDIO_IRQn                   = 49,      
  TIM5_IRQn                   = 50,      
  SPI3_IRQn                   = 51,      
  UART4_IRQn                  = 52,      
  UART5_IRQn                  = 53,      
  TIM6_IRQn                   = 54,      
  TIM7_IRQn                   = 55,      
  DMA2_Channel1_IRQn          = 56,      
  DMA2_Channel2_IRQn          = 57,      
  DMA2_Channel3_IRQn          = 58,      
  DMA2_Channel4_5_IRQn        = 59       


#line 455 ".\\Source\\FWLib\\cm3\\stm32f10x.h"
} IRQn_Type;



 

#line 1 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"
 




















 























 













 




 






 

 











#line 99 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"

 


#line 120 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"

#line 1 "D:\\Keil_ARM\\ARM\\RV31\\INC\\stdint.h"
 
 





 









#line 25 "D:\\Keil_ARM\\ARM\\RV31\\INC\\stdint.h"







 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

     
typedef   signed       __int64 intmax_t;
typedef unsigned       __int64 uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 196 "D:\\Keil_ARM\\ARM\\RV31\\INC\\stdint.h"

     







     










     











#line 260 "D:\\Keil_ARM\\ARM\\RV31\\INC\\stdint.h"



 


#line 122 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"
#line 1 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cmInstr.h"
 




















 





 



 


 









 







 







 






 








 







 







 









 









 
static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 
static __inline __asm int32_t __REVSH(int32_t value)
{
  revsh r0, r0
  bx lr
}










 









 









 









 











 











 











 







 










 










 









 






#line 582 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cmInstr.h"

   

#line 123 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"
#line 1 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cmFunc.h"
 




















 





 



 


 





 
 






 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}







 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}







 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}







 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}







 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}







 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}







 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}







 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}







 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}







 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}







 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}
 







 







 








 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}







 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xff);
}
 






 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}







 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & (uint32_t)1);
}




#line 293 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cmFunc.h"


#line 605 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cmFunc.h"

 


#line 124 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"








 
#line 154 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"

 
#line 163 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"

 





 








 





 


 
typedef union
{
  struct
  {

    uint32_t _reserved0:27;               





    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       

    uint32_t _reserved0:15;               





    uint32_t T:1;                         
    uint32_t IT:2;                        
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;



 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t FPCA:1;                      
    uint32_t _reserved0:29;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 






 


 
typedef struct
{
  volatile uint32_t ISER[8];                  
       uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];                  
       uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];                  
       uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];                  
       uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];                  
       uint32_t RESERVED4[56];
  volatile uint8_t  IP[240];                  
       uint32_t RESERVED5[644];
  volatile  uint32_t STIR;                     
}  NVIC_Type;

 



 






 


 
typedef struct
{
  volatile const  uint32_t CPUID;                    
  volatile uint32_t ICSR;                     
  volatile uint32_t VTOR;                     
  volatile uint32_t AIRCR;                    
  volatile uint32_t SCR;                      
  volatile uint32_t CCR;                      
  volatile uint8_t  SHP[12];                  
  volatile uint32_t SHCSR;                    
  volatile uint32_t CFSR;                     
  volatile uint32_t HFSR;                     
  volatile uint32_t DFSR;                     
  volatile uint32_t MMFAR;                    
  volatile uint32_t BFAR;                     
  volatile uint32_t AFSR;                     
  volatile const  uint32_t PFR[2];                   
  volatile const  uint32_t DFR;                      
  volatile const  uint32_t ADR;                      
  volatile const  uint32_t MMFR[4];                  
  volatile const  uint32_t ISAR[5];                  
       uint32_t RESERVED0[5];
  volatile uint32_t CPACR;                    
} SCB_Type;

 















 






























 



 





















 









 


















 










































 









 









 















 






 


 
typedef struct
{
       uint32_t RESERVED0[1];
  volatile const  uint32_t ICTR;                     



       uint32_t RESERVED1[1];

} SCnSCB_Type;

 



 










 






 


 
typedef struct
{
  volatile uint32_t CTRL;                     
  volatile uint32_t LOAD;                     
  volatile uint32_t VAL;                      
  volatile const  uint32_t CALIB;                    
} SysTick_Type;

 












 



 



 









 






 


 
typedef struct
{
  volatile  union
  {
    volatile  uint8_t    u8;                   
    volatile  uint16_t   u16;                  
    volatile  uint32_t   u32;                  
  }  PORT [32];                           
       uint32_t RESERVED0[864];
  volatile uint32_t TER;                      
       uint32_t RESERVED1[15];
  volatile uint32_t TPR;                      
       uint32_t RESERVED2[15];
  volatile uint32_t TCR;                      
} ITM_Type;

 



 



























   







 


 
typedef struct
{
  volatile const  uint32_t TYPE;                     
  volatile uint32_t CTRL;                     
  volatile uint32_t RNR;                      
  volatile uint32_t RBAR;                     
  volatile uint32_t RASR;                     
  volatile uint32_t RBAR_A1;                  
  volatile uint32_t RASR_A1;                  
  volatile uint32_t RBAR_A2;                  
  volatile uint32_t RASR_A2;                  
  volatile uint32_t RBAR_A3;                  
  volatile uint32_t RASR_A3;                  
} MPU_Type;

 









 









 



 









 












 







 


 
typedef struct
{
  volatile uint32_t DHCSR;                    
  volatile  uint32_t DCRSR;                    
  volatile uint32_t DCRDR;                    
  volatile uint32_t DEMCR;                    
} CoreDebug_Type;

 




































 






 







































 




 

 
#line 850 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"

#line 857 "..\\..\\..\\STM32F4\\STM32F4xx_DSP_StdPeriph_Lib_V1.0.1\\Libraries\\CMSIS\\Include\\core_cm3.h"






 





 






 



 



 










 
static __inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07);                

  reg_value  =  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;                                                    
  reg_value &= ~((0xFFFFUL << 16) | (7UL << 8));              
  reg_value  =  (reg_value                                 |
                ((uint32_t)0x5FA << 16) |
                (PriorityGroupTmp << 8));                                      
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR =  reg_value;
}








 
static __inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) >> 8);    
}








 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}








 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}










 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}








 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}








 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}








 
static __inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}












 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 4)) & 0xff); }  
  else {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)] = ((priority << (8 - 4)) & 0xff);    }         
}













 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 4)));  }  
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)]           >> (8 - 4)));  }  
}















 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 4) ? 4 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 4) < 7) ? 0 : PriorityGroupTmp - 7 + 4;

  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}















 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);           
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 4) ? 4 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 4) < 7) ? 0 : PriorityGroupTmp - 7 + 4;

  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}





 
static __inline void NVIC_SystemReset(void)
{
  __dsb(0xF);                                                     
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = ((0x5FA << 16)      |
                 (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) |
                 (1UL << 2));                    
  __dsb(0xF);                                                      
  while(1);                                                     
}

 



 



 











 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if (ticks > (0xFFFFFFUL << 0))  return (1);             

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = (ticks & (0xFFFFFFUL << 0)) - 1;       
  NVIC_SetPriority (SysTick_IRQn, (1<<4) - 1);   
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0;                                           
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2) |
                   (1UL << 1)   |
                   (1UL << 0);                     
  return (0);                                                   
}



 



 



 

extern volatile int32_t ITM_RxBuffer;                     











 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if ((((CoreDebug_Type *) (0xE000EDF0UL))->DEMCR & (1UL << 24))  &&       
      (((ITM_Type *) (0xE0000000UL) )->TCR & (1UL << 0))                  &&       
      (((ITM_Type *) (0xE0000000UL) )->TER & (1UL << 0)        )                    )      
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000UL) )->PORT[0].u8 = (uint8_t) ch;
  }
  return (ch);
}










 
static __inline int32_t ITM_ReceiveChar (void) {
  int32_t ch = -1;                            

  if (ITM_RxBuffer != 0x5AA55AA5) {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = 0x5AA55AA5;        
  }

  return (ch);
}









 
static __inline int32_t ITM_CheckChar (void) {

  if (ITM_RxBuffer == 0x5AA55AA5) {
    return (0);                                  
  } else {
    return (1);                                  
  }
}

 





#line 462 ".\\Source\\FWLib\\cm3\\stm32f10x.h"
#line 1 ".\\Source\\FWLib\\cm3\\system_stm32f10x.h"


















 



 



   
  


 









 



 




 

extern uint32_t SystemCoreClock;           



 



 



 



 



 



 
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


 









 
  


   
 
#line 463 ".\\Source\\FWLib\\cm3\\stm32f10x.h"
#line 464 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



   

 
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;   
typedef const int16_t sc16;   
typedef const int8_t sc8;    

typedef volatile int32_t  vs32;
typedef volatile int16_t  vs16;
typedef volatile int8_t   vs8;

typedef volatile const int32_t vsc32;   
typedef volatile const int16_t vsc16;   
typedef volatile const int8_t vsc8;    

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;   
typedef const uint16_t uc16;   
typedef const uint8_t uc8;    

typedef volatile uint32_t  vu32;
typedef volatile uint16_t vu16;
typedef volatile uint8_t  vu8;

typedef volatile const uint32_t vuc32;   
typedef volatile const uint16_t vuc16;   
typedef volatile const uint8_t vuc8;    

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

 





 



    



 

typedef struct
{
  volatile uint32_t SR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
  volatile uint32_t JOFR1;
  volatile uint32_t JOFR2;
  volatile uint32_t JOFR3;
  volatile uint32_t JOFR4;
  volatile uint32_t HTR;
  volatile uint32_t LTR;
  volatile uint32_t SQR1;
  volatile uint32_t SQR2;
  volatile uint32_t SQR3;
  volatile uint32_t JSQR;
  volatile uint32_t JDR1;
  volatile uint32_t JDR2;
  volatile uint32_t JDR3;
  volatile uint32_t JDR4;
  volatile uint32_t DR;
} ADC_TypeDef;



 

typedef struct
{
  uint32_t  RESERVED0;
  volatile uint16_t DR1;
  uint16_t  RESERVED1;
  volatile uint16_t DR2;
  uint16_t  RESERVED2;
  volatile uint16_t DR3;
  uint16_t  RESERVED3;
  volatile uint16_t DR4;
  uint16_t  RESERVED4;
  volatile uint16_t DR5;
  uint16_t  RESERVED5;
  volatile uint16_t DR6;
  uint16_t  RESERVED6;
  volatile uint16_t DR7;
  uint16_t  RESERVED7;
  volatile uint16_t DR8;
  uint16_t  RESERVED8;
  volatile uint16_t DR9;
  uint16_t  RESERVED9;
  volatile uint16_t DR10;
  uint16_t  RESERVED10; 
  volatile uint16_t RTCCR;
  uint16_t  RESERVED11;
  volatile uint16_t CR;
  uint16_t  RESERVED12;
  volatile uint16_t CSR;
  uint16_t  RESERVED13[5];
  volatile uint16_t DR11;
  uint16_t  RESERVED14;
  volatile uint16_t DR12;
  uint16_t  RESERVED15;
  volatile uint16_t DR13;
  uint16_t  RESERVED16;
  volatile uint16_t DR14;
  uint16_t  RESERVED17;
  volatile uint16_t DR15;
  uint16_t  RESERVED18;
  volatile uint16_t DR16;
  uint16_t  RESERVED19;
  volatile uint16_t DR17;
  uint16_t  RESERVED20;
  volatile uint16_t DR18;
  uint16_t  RESERVED21;
  volatile uint16_t DR19;
  uint16_t  RESERVED22;
  volatile uint16_t DR20;
  uint16_t  RESERVED23;
  volatile uint16_t DR21;
  uint16_t  RESERVED24;
  volatile uint16_t DR22;
  uint16_t  RESERVED25;
  volatile uint16_t DR23;
  uint16_t  RESERVED26;
  volatile uint16_t DR24;
  uint16_t  RESERVED27;
  volatile uint16_t DR25;
  uint16_t  RESERVED28;
  volatile uint16_t DR26;
  uint16_t  RESERVED29;
  volatile uint16_t DR27;
  uint16_t  RESERVED30;
  volatile uint16_t DR28;
  uint16_t  RESERVED31;
  volatile uint16_t DR29;
  uint16_t  RESERVED32;
  volatile uint16_t DR30;
  uint16_t  RESERVED33; 
  volatile uint16_t DR31;
  uint16_t  RESERVED34;
  volatile uint16_t DR32;
  uint16_t  RESERVED35;
  volatile uint16_t DR33;
  uint16_t  RESERVED36;
  volatile uint16_t DR34;
  uint16_t  RESERVED37;
  volatile uint16_t DR35;
  uint16_t  RESERVED38;
  volatile uint16_t DR36;
  uint16_t  RESERVED39;
  volatile uint16_t DR37;
  uint16_t  RESERVED40;
  volatile uint16_t DR38;
  uint16_t  RESERVED41;
  volatile uint16_t DR39;
  uint16_t  RESERVED42;
  volatile uint16_t DR40;
  uint16_t  RESERVED43;
  volatile uint16_t DR41;
  uint16_t  RESERVED44;
  volatile uint16_t DR42;
  uint16_t  RESERVED45;    
} BKP_TypeDef;
  


 

typedef struct
{
  volatile uint32_t TIR;
  volatile uint32_t TDTR;
  volatile uint32_t TDLR;
  volatile uint32_t TDHR;
} CAN_TxMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t RIR;
  volatile uint32_t RDTR;
  volatile uint32_t RDLR;
  volatile uint32_t RDHR;
} CAN_FIFOMailBox_TypeDef;



 
  
typedef struct
{
  volatile uint32_t FR1;
  volatile uint32_t FR2;
} CAN_FilterRegister_TypeDef;



 
  
typedef struct
{
  volatile uint32_t MCR;
  volatile uint32_t MSR;
  volatile uint32_t TSR;
  volatile uint32_t RF0R;
  volatile uint32_t RF1R;
  volatile uint32_t IER;
  volatile uint32_t ESR;
  volatile uint32_t BTR;
  uint32_t  RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  uint32_t  RESERVED1[12];
  volatile uint32_t FMR;
  volatile uint32_t FM1R;
  uint32_t  RESERVED2;
  volatile uint32_t FS1R;
  uint32_t  RESERVED3;
  volatile uint32_t FFA1R;
  uint32_t  RESERVED4;
  volatile uint32_t FA1R;
  uint32_t  RESERVED5[8];

  CAN_FilterRegister_TypeDef sFilterRegister[14];



} CAN_TypeDef;



 
typedef struct
{
  volatile uint32_t CFGR;
  volatile uint32_t OAR;
  volatile uint32_t PRES;
  volatile uint32_t ESR;
  volatile uint32_t CSR;
  volatile uint32_t TXD;
  volatile uint32_t RXD;  
} CEC_TypeDef;



 

typedef struct
{
  volatile uint32_t DR;
  volatile uint8_t  IDR;
  uint8_t   RESERVED0;
  uint16_t  RESERVED1;
  volatile uint32_t CR;
} CRC_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t SWTRIGR;
  volatile uint32_t DHR12R1;
  volatile uint32_t DHR12L1;
  volatile uint32_t DHR8R1;
  volatile uint32_t DHR12R2;
  volatile uint32_t DHR12L2;
  volatile uint32_t DHR8R2;
  volatile uint32_t DHR12RD;
  volatile uint32_t DHR12LD;
  volatile uint32_t DHR8RD;
  volatile uint32_t DOR1;
  volatile uint32_t DOR2;



} DAC_TypeDef;



 

typedef struct
{
  volatile uint32_t IDCODE;
  volatile uint32_t CR;	
}DBGMCU_TypeDef;



 

typedef struct
{
  volatile uint32_t CCR;
  volatile uint32_t CNDTR;
  volatile uint32_t CPAR;
  volatile uint32_t CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t IFCR;
} DMA_TypeDef;



 

typedef struct
{
  volatile uint32_t MACCR;
  volatile uint32_t MACFFR;
  volatile uint32_t MACHTHR;
  volatile uint32_t MACHTLR;
  volatile uint32_t MACMIIAR;
  volatile uint32_t MACMIIDR;
  volatile uint32_t MACFCR;
  volatile uint32_t MACVLANTR;              
       uint32_t RESERVED0[2];
  volatile uint32_t MACRWUFFR;              
  volatile uint32_t MACPMTCSR;
       uint32_t RESERVED1[2];
  volatile uint32_t MACSR;                  
  volatile uint32_t MACIMR;
  volatile uint32_t MACA0HR;
  volatile uint32_t MACA0LR;
  volatile uint32_t MACA1HR;
  volatile uint32_t MACA1LR;
  volatile uint32_t MACA2HR;
  volatile uint32_t MACA2LR;
  volatile uint32_t MACA3HR;
  volatile uint32_t MACA3LR;                
       uint32_t RESERVED2[40];
  volatile uint32_t MMCCR;                  
  volatile uint32_t MMCRIR;
  volatile uint32_t MMCTIR;
  volatile uint32_t MMCRIMR;
  volatile uint32_t MMCTIMR;                
       uint32_t RESERVED3[14];
  volatile uint32_t MMCTGFSCCR;             
  volatile uint32_t MMCTGFMSCCR;
       uint32_t RESERVED4[5];
  volatile uint32_t MMCTGFCR;
       uint32_t RESERVED5[10];
  volatile uint32_t MMCRFCECR;
  volatile uint32_t MMCRFAECR;
       uint32_t RESERVED6[10];
  volatile uint32_t MMCRGUFCR;
       uint32_t RESERVED7[334];
  volatile uint32_t PTPTSCR;
  volatile uint32_t PTPSSIR;
  volatile uint32_t PTPTSHR;
  volatile uint32_t PTPTSLR;
  volatile uint32_t PTPTSHUR;
  volatile uint32_t PTPTSLUR;
  volatile uint32_t PTPTSAR;
  volatile uint32_t PTPTTHR;
  volatile uint32_t PTPTTLR;
       uint32_t RESERVED8[567];
  volatile uint32_t DMABMR;
  volatile uint32_t DMATPDR;
  volatile uint32_t DMARPDR;
  volatile uint32_t DMARDLAR;
  volatile uint32_t DMATDLAR;
  volatile uint32_t DMASR;
  volatile uint32_t DMAOMR;
  volatile uint32_t DMAIER;
  volatile uint32_t DMAMFBOCR;
       uint32_t RESERVED9[9];
  volatile uint32_t DMACHTDR;
  volatile uint32_t DMACHRDR;
  volatile uint32_t DMACHTBAR;
  volatile uint32_t DMACHRBAR;
} ETH_TypeDef;



 

typedef struct
{
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
} EXTI_TypeDef;



 

typedef struct
{
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t AR;
  volatile uint32_t RESERVED;
  volatile uint32_t OBR;
  volatile uint32_t WRPR;

  uint32_t RESERVED1[8]; 
  volatile uint32_t KEYR2;
  uint32_t RESERVED2;   
  volatile uint32_t SR2;
  volatile uint32_t CR2;
  volatile uint32_t AR2; 

} FLASH_TypeDef;



 
  
typedef struct
{
  volatile uint16_t RDP;
  volatile uint16_t USER;
  volatile uint16_t Data0;
  volatile uint16_t Data1;
  volatile uint16_t WRP0;
  volatile uint16_t WRP1;
  volatile uint16_t WRP2;
  volatile uint16_t WRP3;
} OB_TypeDef;



 

typedef struct
{
  volatile uint32_t BTCR[8];   
} FSMC_Bank1_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t BWTR[7];
} FSMC_Bank1E_TypeDef;



 
  
typedef struct
{
  volatile uint32_t PCR2;
  volatile uint32_t SR2;
  volatile uint32_t PMEM2;
  volatile uint32_t PATT2;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR2; 
} FSMC_Bank2_TypeDef;  



 
  
typedef struct
{
  volatile uint32_t PCR3;
  volatile uint32_t SR3;
  volatile uint32_t PMEM3;
  volatile uint32_t PATT3;
  uint32_t  RESERVED0;   
  volatile uint32_t ECCR3; 
} FSMC_Bank3_TypeDef; 



 
  
typedef struct
{
  volatile uint32_t PCR4;
  volatile uint32_t SR4;
  volatile uint32_t PMEM4;
  volatile uint32_t PATT4;
  volatile uint32_t PIO4; 
} FSMC_Bank4_TypeDef; 



 

typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;



 

typedef struct
{
  volatile uint32_t EVCR;
  volatile uint32_t MAPR;
  volatile uint32_t EXTICR[4];
  uint32_t RESERVED0;
  volatile uint32_t MAPR2;  
} AFIO_TypeDef;


 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t OAR1;
  uint16_t  RESERVED2;
  volatile uint16_t OAR2;
  uint16_t  RESERVED3;
  volatile uint16_t DR;
  uint16_t  RESERVED4;
  volatile uint16_t SR1;
  uint16_t  RESERVED5;
  volatile uint16_t SR2;
  uint16_t  RESERVED6;
  volatile uint16_t CCR;
  uint16_t  RESERVED7;
  volatile uint16_t TRISE;
  uint16_t  RESERVED8;
} I2C_TypeDef;



 

typedef struct
{
  volatile uint32_t KR;
  volatile uint32_t PR;
  volatile uint32_t RLR;
  volatile uint32_t SR;
} IWDG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CSR;
} PWR_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;










} RCC_TypeDef;



 

typedef struct
{
  volatile uint16_t CRH;
  uint16_t  RESERVED0;
  volatile uint16_t CRL;
  uint16_t  RESERVED1;
  volatile uint16_t PRLH;
  uint16_t  RESERVED2;
  volatile uint16_t PRLL;
  uint16_t  RESERVED3;
  volatile uint16_t DIVH;
  uint16_t  RESERVED4;
  volatile uint16_t DIVL;
  uint16_t  RESERVED5;
  volatile uint16_t CNTH;
  uint16_t  RESERVED6;
  volatile uint16_t CNTL;
  uint16_t  RESERVED7;
  volatile uint16_t ALRH;
  uint16_t  RESERVED8;
  volatile uint16_t ALRL;
  uint16_t  RESERVED9;
} RTC_TypeDef;



 

typedef struct
{
  volatile uint32_t POWER;
  volatile uint32_t CLKCR;
  volatile uint32_t ARG;
  volatile uint32_t CMD;
  volatile const uint32_t RESPCMD;
  volatile const uint32_t RESP1;
  volatile const uint32_t RESP2;
  volatile const uint32_t RESP3;
  volatile const uint32_t RESP4;
  volatile uint32_t DTIMER;
  volatile uint32_t DLEN;
  volatile uint32_t DCTRL;
  volatile const uint32_t DCOUNT;
  volatile const uint32_t STA;
  volatile uint32_t ICR;
  volatile uint32_t MASK;
  uint32_t  RESERVED0[2];
  volatile const uint32_t FIFOCNT;
  uint32_t  RESERVED1[13];
  volatile uint32_t FIFO;
} SDIO_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SR;
  uint16_t  RESERVED2;
  volatile uint16_t DR;
  uint16_t  RESERVED3;
  volatile uint16_t CRCPR;
  uint16_t  RESERVED4;
  volatile uint16_t RXCRCR;
  uint16_t  RESERVED5;
  volatile uint16_t TXCRCR;
  uint16_t  RESERVED6;
  volatile uint16_t I2SCFGR;
  uint16_t  RESERVED7;
  volatile uint16_t I2SPR;
  uint16_t  RESERVED8;  
} SPI_TypeDef;



 

typedef struct
{
  volatile uint16_t CR1;
  uint16_t  RESERVED0;
  volatile uint16_t CR2;
  uint16_t  RESERVED1;
  volatile uint16_t SMCR;
  uint16_t  RESERVED2;
  volatile uint16_t DIER;
  uint16_t  RESERVED3;
  volatile uint16_t SR;
  uint16_t  RESERVED4;
  volatile uint16_t EGR;
  uint16_t  RESERVED5;
  volatile uint16_t CCMR1;
  uint16_t  RESERVED6;
  volatile uint16_t CCMR2;
  uint16_t  RESERVED7;
  volatile uint16_t CCER;
  uint16_t  RESERVED8;
  volatile uint16_t CNT;
  uint16_t  RESERVED9;
  volatile uint16_t PSC;
  uint16_t  RESERVED10;
  volatile uint16_t ARR;
  uint16_t  RESERVED11;
  volatile uint16_t RCR;
  uint16_t  RESERVED12;
  volatile uint16_t CCR1;
  uint16_t  RESERVED13;
  volatile uint16_t CCR2;
  uint16_t  RESERVED14;
  volatile uint16_t CCR3;
  uint16_t  RESERVED15;
  volatile uint16_t CCR4;
  uint16_t  RESERVED16;
  volatile uint16_t BDTR;
  uint16_t  RESERVED17;
  volatile uint16_t DCR;
  uint16_t  RESERVED18;
  volatile uint16_t DMAR;
  uint16_t  RESERVED19;
} TIM_TypeDef;



 
 
typedef struct
{
  volatile uint16_t SR;
  uint16_t  RESERVED0;
  volatile uint16_t DR;
  uint16_t  RESERVED1;
  volatile uint16_t BRR;
  uint16_t  RESERVED2;
  volatile uint16_t CR1;
  uint16_t  RESERVED3;
  volatile uint16_t CR2;
  uint16_t  RESERVED4;
  volatile uint16_t CR3;
  uint16_t  RESERVED5;
  volatile uint16_t GTPR;
  uint16_t  RESERVED6;
} USART_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFR;
  volatile uint32_t SR;
} WWDG_TypeDef;



 
  


 











 




#line 1295 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 1318 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



#line 1337 ".\\Source\\FWLib\\cm3\\stm32f10x.h"




















 
  


   

#line 1437 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 



 
  
  

 
    
 
 
 

 
 
 
 
 

 



 



 


 
 
 
 
 

 











 
#line 1498 ".\\Source\\FWLib\\cm3\\stm32f10x.h"




 





 
 
 
 
 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 





 



 






 
 
 
 
 

 
#line 1674 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 1681 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 








 








 






#line 1717 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 











 











 













 






#line 1833 ".\\Source\\FWLib\\cm3\\stm32f10x.h"




#line 1853 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





#line 1866 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 1885 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 1894 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 1902 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



















#line 1927 ".\\Source\\FWLib\\cm3\\stm32f10x.h"












 













#line 1959 ".\\Source\\FWLib\\cm3\\stm32f10x.h"





#line 1973 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 1980 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 1990 ".\\Source\\FWLib\\cm3\\stm32f10x.h"











 


















#line 2026 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2034 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



















#line 2059 ".\\Source\\FWLib\\cm3\\stm32f10x.h"












 













#line 2091 ".\\Source\\FWLib\\cm3\\stm32f10x.h"





#line 2105 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2112 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2122 ".\\Source\\FWLib\\cm3\\stm32f10x.h"











 








 








   
#line 2161 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2256 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2283 ".\\Source\\FWLib\\cm3\\stm32f10x.h"
 
 
 
 
 
 

 




































































 




































































 
#line 2445 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2463 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2481 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2498 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2516 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2535 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 

 






 
#line 2562 ".\\Source\\FWLib\\cm3\\stm32f10x.h"






 








 









 








 








 









 










 




#line 2637 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 










#line 2668 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





 
#line 2683 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2692 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

   
#line 2701 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2710 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





 
#line 2725 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2734 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

   
#line 2743 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2752 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





 
#line 2767 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2776 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

   
#line 2785 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2794 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





 
#line 2809 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2818 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

   
#line 2827 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2836 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2845 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 2854 ".\\Source\\FWLib\\cm3\\stm32f10x.h"


 
#line 2864 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 
 
 
 

 





 


 


 




 
 
 
 
 

 
#line 2928 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2963 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 2998 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3033 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3068 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





 





 





 





 





 





 





 





 






 
#line 3135 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 



 









 
#line 3159 ".\\Source\\FWLib\\cm3\\stm32f10x.h"




 




 
#line 3175 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 





 
#line 3197 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 





 
#line 3212 ".\\Source\\FWLib\\cm3\\stm32f10x.h"
 
#line 3219 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 




 






 


 


 


 
 
 
 
 

 
#line 3268 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3290 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3312 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3334 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3356 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3378 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 
 
 
 

 
#line 3414 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3444 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3454 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 
#line 3478 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 
#line 3502 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 
#line 3526 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 
#line 3550 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 
#line 3574 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 
#line 3598 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















 


 


 


 


 


 


 


 


 


 



 


 


 



 


 


 


 



 


 


 


 


 
 
 
 
 

 






 
#line 3699 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3708 ".\\Source\\FWLib\\cm3\\stm32f10x.h"















  
 
#line 3731 ".\\Source\\FWLib\\cm3\\stm32f10x.h"


















 








































 


















































 


 


 


 


 


 


 
#line 3866 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3873 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3880 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3887 ".\\Source\\FWLib\\cm3\\stm32f10x.h"







 
#line 3901 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3908 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3915 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3922 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3929 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3936 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3944 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3951 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3958 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3965 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3972 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3979 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 3987 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 3994 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 4001 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 4008 ".\\Source\\FWLib\\cm3\\stm32f10x.h"





 


 


 


 


 



 
 
 
 
 

 









































 



 


 


 


 


 


 


 



 



 



 


 


 



 
 
 
 
 
 





 






 


 
#line 4150 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 4160 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 
 
 
 
 

 
















 









#line 4208 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 

























 
#line 4251 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 4265 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 4275 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 




























 





















 




























 





















 
#line 4394 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
#line 4429 ".\\Source\\FWLib\\cm3\\stm32f10x.h"





#line 4440 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 4448 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 4455 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 
 
 
 
 

 




 
#line 4477 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
 
 
 
 

 


 





 


 



 
 
 
 
 

 
#line 4539 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 
#line 4551 ".\\Source\\FWLib\\cm3\\stm32f10x.h"







 


 
 
 
 
 

 











#line 4589 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 











#line 4612 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 











#line 4635 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 











#line 4658 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 








































 








































 








































 








































 


































 


































 


































 


































 



























 



























 



























 
#line 5055 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5064 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5073 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5084 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5094 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5104 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5114 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5125 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5135 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5145 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5155 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5166 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5176 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5186 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5196 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5207 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5217 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5227 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5237 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5248 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5258 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5268 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5278 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5289 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5299 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5309 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5319 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5330 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5340 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5350 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

#line 5360 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 
 
 
 
 

 




 












 


 






#line 5408 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 


 


 


 


 


 


 
















 


 
#line 5478 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5493 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5519 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 
 
 
 
 

 
 























 























 























 























 























 























 























 























 
 
#line 5740 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 5752 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 






 
#line 5769 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



     


 
 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 


 

 


 


 


 


 


 


 


 


 

 


#line 5913 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5925 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5937 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5949 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5961 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5973 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5985 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 5997 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 

 


#line 6011 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6023 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6035 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6047 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6059 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6071 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6083 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6095 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6107 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6119 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6131 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6143 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6155 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6167 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6179 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 


#line 6191 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 
 
 
 
 

 
 
#line 6211 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6222 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6240 ".\\Source\\FWLib\\cm3\\stm32f10x.h"











 





 





 
#line 6278 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 












 
#line 6299 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 






 




 





 





 






 




 





 





 






   




 





 





 





 




 





 





 





 




 





 





 
 


 
#line 6439 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6456 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6473 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6490 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6524 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6558 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6592 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6626 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6660 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6694 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6728 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6762 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6796 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6830 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6864 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6898 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6932 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 6966 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7000 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7034 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7068 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7102 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7136 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7170 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7204 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7238 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7272 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7306 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7340 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7374 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7408 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7442 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 
 
 
 

 









#line 7469 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7477 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7487 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 


 


 


 





















 




 
 
 
 
 

 
#line 7548 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7557 ".\\Source\\FWLib\\cm3\\stm32f10x.h"







 



#line 7578 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 



 


 
#line 7603 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7613 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 




 


 
 
 
 
 

 
#line 7639 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 



 
#line 7663 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7672 ".\\Source\\FWLib\\cm3\\stm32f10x.h"







 
#line 7692 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
#line 7703 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 
 
 
 
 

 


#line 7732 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 









#line 7766 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 
 
 
 
 

 









 


 


 





 
#line 7806 ".\\Source\\FWLib\\cm3\\stm32f10x.h"

 


 









 


 

 



 



 



 



 



 



 



 



#line 8270 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 

 

  

#line 1 ".\\Source\\APP\\stm32f10x_conf.h"



















  

 



 
 
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"



















  

 







 
#line 1 ".\\Source\\FWLib\\cm3\\stm32f10x.h"























 



 



 
    
#line 8310 ".\\Source\\FWLib\\cm3\\stm32f10x.h"



 

  

 

 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"



 



 



 



 

typedef struct
{
  uint32_t ADC_Mode;                      

 

  FunctionalState ADC_ScanConvMode;       

 

  FunctionalState ADC_ContinuousConvMode; 

 

  uint32_t ADC_ExternalTrigConv;          

 

  uint32_t ADC_DataAlign;                 
 

  uint8_t ADC_NbrOfChannel;               

 
}ADC_InitTypeDef;


 



 










 

#line 103 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"

#line 114 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 

#line 128 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"




#line 138 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"

#line 153 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 







 



 

#line 191 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"




#line 204 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 

#line 228 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 

















#line 265 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 

#line 281 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 

#line 296 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"

#line 304 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 











 



 

#line 337 ".\\Source\\FWLib\\inc\\stm32f10x_adc.h"


 



 





 



 





 



 





 



 





  




 




 



 





 



 





 



 



 



 



 

void ADC_DeInit(ADC_TypeDef* ADCx);
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState);
void ADC_ResetCalibration(ADC_TypeDef* ADCx);
FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_StartCalibration(ADC_TypeDef* ADCx);
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef* ADCx);
void ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx);
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number);
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_ExternalTrigConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx);
uint32_t ADC_GetDualModeConversionValue(void);
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv);
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_SoftwareStartInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx);
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t Length);
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset);
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel);
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog);
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold, uint16_t LowThreshold);
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel);
void ADC_TempSensorVrefintCmd(FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT);









 



 



 

 
#line 29 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_bkp.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_bkp.h"



 



 



 



 



 



 







 



 

#line 77 ".\\Source\\FWLib\\inc\\stm32f10x_bkp.h"


 



 

#line 127 ".\\Source\\FWLib\\inc\\stm32f10x_bkp.h"

#line 142 ".\\Source\\FWLib\\inc\\stm32f10x_bkp.h"




 



 



 



 



 

void BKP_DeInit(void);
void BKP_TamperPinLevelConfig(uint16_t BKP_TamperPinLevel);
void BKP_TamperPinCmd(FunctionalState NewState);
void BKP_ITConfig(FunctionalState NewState);
void BKP_RTCOutputConfig(uint16_t BKP_RTCOutputSource);
void BKP_SetRTCCalibrationValue(uint8_t CalibrationValue);
void BKP_WriteBackupRegister(uint16_t BKP_DR, uint16_t Data);
uint16_t BKP_ReadBackupRegister(uint16_t BKP_DR);
FlagStatus BKP_GetFlagStatus(void);
void BKP_ClearFlag(void);
ITStatus BKP_GetITStatus(void);
void BKP_ClearITPendingBit(void);








 



 



 

 
#line 30 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"



 



 



 






 

typedef struct
{
  uint16_t CAN_Prescaler;    
  
  uint8_t CAN_Mode;         
 

  uint8_t CAN_SJW;          

 

  uint8_t CAN_BS1;          
 

  uint8_t CAN_BS2;          
 
  
  FunctionalState CAN_TTCM; 
 
  
  FunctionalState CAN_ABOM;  
 

  FunctionalState CAN_AWUM;  
 

  FunctionalState CAN_NART;  
 

  FunctionalState CAN_RFLM;  
 

  FunctionalState CAN_TXFP;  
 
} CAN_InitTypeDef;



 

typedef struct
{
  uint16_t CAN_FilterIdHigh;             

 

  uint16_t CAN_FilterIdLow;              

 

  uint16_t CAN_FilterMaskIdHigh;         


 

  uint16_t CAN_FilterMaskIdLow;          


 

  uint16_t CAN_FilterFIFOAssignment;     
 
  
  uint8_t CAN_FilterNumber;               

  uint8_t CAN_FilterMode;                
 

  uint8_t CAN_FilterScale;               
 

  FunctionalState CAN_FilterActivation;  
 
} CAN_FilterInitTypeDef;



 

typedef struct
{
  uint32_t StdId;  
 

  uint32_t ExtId;  
 

  uint8_t IDE;     
 

  uint8_t RTR;     
 

  uint8_t DLC;     
 

  uint8_t Data[8];  
} CanTxMsg;



 

typedef struct
{
  uint32_t StdId;  
 

  uint32_t ExtId;  
 

  uint8_t IDE;     
 

  uint8_t RTR;     
 

  uint8_t DLC;     
 

  uint8_t Data[8];  

  uint8_t FMI;     
 
} CanRxMsg;



 



 



 






 



 










 



 










 



 

#line 247 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"




 



 

#line 265 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"





 



 





 



 







 



 








 



 









 



 








 



 



 



 








 



 







 



 







 



 








 



 








 



 






 



 






 



 

 
 

 




 
#line 446 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"

 



 

 





#line 467 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"








 

  


 


  


 
#line 493 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"

 



 






 





#line 518 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"

#line 525 ".\\Source\\FWLib\\inc\\stm32f10x_can.h"



 



 



 



 



 

void CAN_DeInit(CAN_TypeDef* CANx);
uint8_t CAN_Init(CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct);
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct);
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct);
void CAN_SlaveStartBank(uint8_t CAN_BankNumber); 
void CAN_ITConfig(CAN_TypeDef* CANx, uint32_t CAN_IT, FunctionalState NewState);
uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage);
uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox);
void CAN_CancelTransmit(CAN_TypeDef* CANx, uint8_t Mailbox);
void CAN_FIFORelease(CAN_TypeDef* CANx, uint8_t FIFONumber);
uint8_t CAN_MessagePending(CAN_TypeDef* CANx, uint8_t FIFONumber);
void CAN_Receive(CAN_TypeDef* CANx, uint8_t FIFONumber, CanRxMsg* RxMessage);
void CAN_DBGFreeze(CAN_TypeDef* CANx, FunctionalState NewState);
uint8_t CAN_Sleep(CAN_TypeDef* CANx);
uint8_t CAN_WakeUp(CAN_TypeDef* CANx);
FlagStatus CAN_GetFlagStatus(CAN_TypeDef* CANx, uint32_t CAN_FLAG);
void CAN_ClearFlag(CAN_TypeDef* CANx, uint32_t CAN_FLAG);
ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT);
void CAN_ClearITPendingBit(CAN_TypeDef* CANx, uint32_t CAN_IT);








 



 



 

 
#line 31 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_cec.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_cec.h"



 



 
  



 
   


  
typedef struct
{
  uint16_t CEC_BitTimingMode; 
 
  uint16_t CEC_BitPeriodMode; 
 
}CEC_InitTypeDef;



 



  
  


  







 



  







  




  
#line 99 ".\\Source\\FWLib\\inc\\stm32f10x_cec.h"


  




  



  



  




 



 
   


  
#line 135 ".\\Source\\FWLib\\inc\\stm32f10x_cec.h"



  
#line 146 ".\\Source\\FWLib\\inc\\stm32f10x_cec.h"


                               
#line 156 ".\\Source\\FWLib\\inc\\stm32f10x_cec.h"



  



  



 
 


 



  
void CEC_DeInit(void);
void CEC_Init(CEC_InitTypeDef* CEC_InitStruct);
void CEC_Cmd(FunctionalState NewState);
void CEC_ITConfig(FunctionalState NewState);
void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress);
void CEC_SetPrescaler(uint16_t CEC_Prescaler);
void CEC_SendDataByte(uint8_t Data);
uint8_t CEC_ReceiveDataByte(void);
void CEC_StartOfMessage(void);
void CEC_EndOfMessageCmd(FunctionalState NewState);
FlagStatus CEC_GetFlagStatus(uint32_t CEC_FLAG);
void CEC_ClearFlag(uint32_t CEC_FLAG);
ITStatus CEC_GetITStatus(uint8_t CEC_IT);
void CEC_ClearITPendingBit(uint16_t CEC_IT);









  



  



  

 
#line 32 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_crc.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_crc.h"



 



 



 



 



 



 



 



 



 

void CRC_ResetDR(void);
uint32_t CRC_CalcCRC(uint32_t Data);
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength);
uint32_t CRC_GetCRC(void);
void CRC_SetIDRegister(uint8_t IDValue);
uint8_t CRC_GetIDRegister(void);








 



 



 

 
#line 33 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"



 



 



 



 

typedef struct
{
  uint32_t DAC_Trigger;                      
 

  uint32_t DAC_WaveGeneration;               

 

  uint32_t DAC_LFSRUnmask_TriangleAmplitude; 

 

  uint32_t DAC_OutputBuffer;                 
 
}DAC_InitTypeDef;



 



 



 

#line 93 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"

#line 103 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"



 



 

#line 118 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"


 



 

#line 150 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"

#line 175 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"


 



 







 



 







 



 

#line 213 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"


 



 







 



 




 
#line 260 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"



 



 



 



 

void DAC_DeInit(void);
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct);
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct);
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState);



void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState);
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState);
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState);
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data);
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1);
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel);
#line 298 ".\\Source\\FWLib\\inc\\stm32f10x_dac.h"








 



 



 

 
#line 34 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_dbgmcu.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_dbgmcu.h"



 



 



 



 



 

#line 79 ".\\Source\\FWLib\\inc\\stm32f10x_dbgmcu.h"
                                              



  



 



 



 

uint32_t DBGMCU_GetREVID(void);
uint32_t DBGMCU_GetDEVID(void);
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);








 



 



 

 
#line 35 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"



 



 



 



 

typedef struct
{
  uint32_t DMA_PeripheralBaseAddr;  

  uint32_t DMA_MemoryBaseAddr;      

  uint32_t DMA_DIR;                
 

  uint32_t DMA_BufferSize;         

 

  uint32_t DMA_PeripheralInc;      
 

  uint32_t DMA_MemoryInc;          
 

  uint32_t DMA_PeripheralDataSize; 
 

  uint32_t DMA_MemoryDataSize;     
 

  uint32_t DMA_Mode;               


 

  uint32_t DMA_Priority;           
 

  uint32_t DMA_M2M;                
 
}DMA_InitTypeDef;



 



 

#line 106 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"



 







 



 







 



 







 



 

#line 153 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"


 



 

#line 167 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"


 



 






 



 

#line 194 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"


 



 







 



 






#line 247 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"

#line 268 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"



#line 295 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"



 



 
#line 331 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"

#line 352 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"



#line 379 ".\\Source\\FWLib\\inc\\stm32f10x_dma.h"


 



 





 



 



 



 



 

void DMA_DeInit(DMA_Channel_TypeDef* DMAy_Channelx);
void DMA_Init(DMA_Channel_TypeDef* DMAy_Channelx, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_Channel_TypeDef* DMAy_Channelx, FunctionalState NewState);
void DMA_ITConfig(DMA_Channel_TypeDef* DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx, uint16_t DataNumber); 
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef* DMAy_Channelx);
FlagStatus DMA_GetFlagStatus(uint32_t DMA_FLAG);
void DMA_ClearFlag(uint32_t DMA_FLAG);
ITStatus DMA_GetITStatus(uint32_t DMA_IT);
void DMA_ClearITPendingBit(uint32_t DMA_IT);








 



 



 

 
#line 36 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_exti.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_exti.h"



 



 



 



 

typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;





 

typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;






 

typedef struct
{
  uint32_t EXTI_Line;               
 
   
  EXTIMode_TypeDef EXTI_Mode;       
 

  EXTITrigger_TypeDef EXTI_Trigger; 
 

  FunctionalState EXTI_LineCmd;     
  
}EXTI_InitTypeDef;



 



 



 

#line 123 ".\\Source\\FWLib\\inc\\stm32f10x_exti.h"
                                          
#line 135 ".\\Source\\FWLib\\inc\\stm32f10x_exti.h"

                    


 



 



 



 



 

void EXTI_DeInit(void);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line);
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line);
void EXTI_ClearFlag(uint32_t EXTI_Line);
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClearITPendingBit(uint32_t EXTI_Line);








 



 



 

 
#line 37 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"



 



 



 



 

typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;



 



 



 

#line 76 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"


 



 







 



 







 



 

 
#line 117 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"

 
#line 143 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"

 
#line 210 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"











 



 







 



 







 



 








 


 
#line 269 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"


 


 







#line 293 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"



 



 
















 
#line 345 ".\\Source\\FWLib\\inc\\stm32f10x_flash.h"



 



 



 



 



 

 
void FLASH_SetLatency(uint32_t FLASH_Latency);
void FLASH_HalfCycleAccessCmd(uint32_t FLASH_HalfCycleAccess);
void FLASH_PrefetchBufferCmd(uint32_t FLASH_PrefetchBuffer);
void FLASH_Unlock(void);
void FLASH_Lock(void);
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);
FLASH_Status FLASH_EraseAllPages(void);
FLASH_Status FLASH_EraseOptionBytes(void);
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data);
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages);
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState);
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY);
uint32_t FLASH_GetUserOptionByte(void);
uint32_t FLASH_GetWriteProtectionOptionByte(void);
FlagStatus FLASH_GetReadOutProtectionStatus(void);
FlagStatus FLASH_GetPrefetchBufferStatus(void);
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_Status FLASH_GetStatus(void);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);

 
void FLASH_UnlockBank1(void);
void FLASH_LockBank1(void);
FLASH_Status FLASH_EraseAllBank1Pages(void);
FLASH_Status FLASH_GetBank1Status(void);
FLASH_Status FLASH_WaitForLastBank1Operation(uint32_t Timeout);


 
void FLASH_UnlockBank2(void);
void FLASH_LockBank2(void);
FLASH_Status FLASH_EraseAllBank2Pages(void);
FLASH_Status FLASH_GetBank2Status(void);
FLASH_Status FLASH_WaitForLastBank2Operation(uint32_t Timeout);
FLASH_Status FLASH_BootConfig(uint16_t FLASH_BOOT);









 



 



 

 
#line 38 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"



 



 



 



 

typedef struct
{
  uint32_t FSMC_AddressSetupTime;       


 

  uint32_t FSMC_AddressHoldTime;        


 

  uint32_t FSMC_DataSetupTime;          


 

  uint32_t FSMC_BusTurnAroundDuration;  


 

  uint32_t FSMC_CLKDivision;            

 

  uint32_t FSMC_DataLatency;            





 

  uint32_t FSMC_AccessMode;             
 
}FSMC_NORSRAMTimingInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_Bank;                
 

  uint32_t FSMC_DataAddressMux;      

 

  uint32_t FSMC_MemoryType;          

 

  uint32_t FSMC_MemoryDataWidth;     
 

  uint32_t FSMC_BurstAccessMode;     

 
                                       
  uint32_t FSMC_AsynchronousWait;     

 

  uint32_t FSMC_WaitSignalPolarity;  

 

  uint32_t FSMC_WrapMode;            

 

  uint32_t FSMC_WaitSignalActive;    


 

  uint32_t FSMC_WriteOperation;      
 

  uint32_t FSMC_WaitSignal;          

 

  uint32_t FSMC_ExtendedMode;        
 

  uint32_t FSMC_WriteBurst;          
  

  FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct;    

  FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct;            
}FSMC_NORSRAMInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_SetupTime;      



 

  uint32_t FSMC_WaitSetupTime;  



 

  uint32_t FSMC_HoldSetupTime;  




 

  uint32_t FSMC_HiZSetupTime;   



 
}FSMC_NAND_PCCARDTimingInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_Bank;              
 

  uint32_t FSMC_Waitfeature;      
 

  uint32_t FSMC_MemoryDataWidth;  
 

  uint32_t FSMC_ECC;              
 

  uint32_t FSMC_ECCPageSize;      
 

  uint32_t FSMC_TCLRSetupTime;    

 

  uint32_t FSMC_TARSetupTime;     

  

  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;     

  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;  
}FSMC_NANDInitTypeDef;



 

typedef struct
{
  uint32_t FSMC_Waitfeature;    
 

  uint32_t FSMC_TCLRSetupTime;  

 

  uint32_t FSMC_TARSetupTime;   

  

  
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;  

  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;    
  
  FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_IOSpaceTimingStruct;    
}FSMC_PCCARDInitTypeDef;



 



 



 






 



   




 



     



 



















 



 








 



 

#line 316 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"



 



 








 



 







 
  


 







 
  


 








 



 








 



 








 



 





                              


 



 







 



 









 



 







 



 





 



 





 



 





 



 





 



 





 



 





 



 

#line 520 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"



 



 
  


 



 








 




 








 



 

#line 576 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"



 



 





 



 





 



 





 



 





 



 





 



 





 



 

#line 652 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"


 



 

#line 668 ".\\Source\\FWLib\\inc\\stm32f10x_fsmc.h"





 



 



 



 



 



 

void FSMC_NORSRAMDeInit(uint32_t FSMC_Bank);
void FSMC_NANDDeInit(uint32_t FSMC_Bank);
void FSMC_PCCARDDeInit(void);
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct);
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct);
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct);
void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState);
void FSMC_NANDCmd(uint32_t FSMC_Bank, FunctionalState NewState);
void FSMC_PCCARDCmd(FunctionalState NewState);
void FSMC_NANDECCCmd(uint32_t FSMC_Bank, FunctionalState NewState);
uint32_t FSMC_GetECC(uint32_t FSMC_Bank);
void FSMC_ITConfig(uint32_t FSMC_Bank, uint32_t FSMC_IT, FunctionalState NewState);
FlagStatus FSMC_GetFlagStatus(uint32_t FSMC_Bank, uint32_t FSMC_FLAG);
void FSMC_ClearFlag(uint32_t FSMC_Bank, uint32_t FSMC_FLAG);
ITStatus FSMC_GetITStatus(uint32_t FSMC_Bank, uint32_t FSMC_IT);
void FSMC_ClearITPendingBit(uint32_t FSMC_Bank, uint32_t FSMC_IT);








 



 



  

 
#line 39 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"



 



 



 

#line 52 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"
                                     


 

typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;





 

typedef enum
{ GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDef;








 

typedef struct
{
  uint16_t GPIO_Pin;             
 

  GPIOSpeed_TypeDef GPIO_Speed;  
 

  GPIOMode_TypeDef GPIO_Mode;    
 
}GPIO_InitTypeDef;




 

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;





 



 



 

#line 143 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"



#line 162 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"



 



 

#line 203 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"







#line 216 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"






#line 244 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"
                              


  



 

#line 265 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"

#line 273 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"



 



 

#line 298 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"

#line 315 ".\\Source\\FWLib\\inc\\stm32f10x_gpio.h"



 



  








                                                 


 



 



 



 

void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_EventOutputCmd(FunctionalState NewState);
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);
void GPIO_ETH_MediaInterfaceConfig(uint32_t GPIO_ETH_MediaInterface);








 



 



 

 
#line 40 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"



 



 



 



 

typedef struct
{
  uint32_t I2C_ClockSpeed;          
 

  uint16_t I2C_Mode;                
 

  uint16_t I2C_DutyCycle;           
 

  uint16_t I2C_OwnAddress1;         
 

  uint16_t I2C_Ack;                 
 

  uint16_t I2C_AcknowledgedAddress; 
 
}I2C_InitTypeDef;



  




 





 

#line 91 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"


 



 







  



 







 



 







 



 







  



 

#line 165 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"


 



 







 



 







  



 







  



 

#line 223 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"



#line 233 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"


 



 



 

#line 252 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"



 

#line 271 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"



#line 285 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"


 



 




 







 
 

























 

 


 





























 

  
 


 
 

 






 
























 

    
 



 



 



























 

  
 

 


 
 


 


 

#line 483 ".\\Source\\FWLib\\inc\\stm32f10x_i2c.h"


 



 




 



 




 



 



 



 



 

void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address);
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState);
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction);
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register);
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, uint16_t I2C_SMBusAlert);
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_PECPosition);
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx);
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, uint16_t I2C_DutyCycle);













































































 





 
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);




 
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx);




 
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);



 

void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT);
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT);








  



  



  

 
#line 41 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_iwdg.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_iwdg.h"



 



 



 



 



 



 







 



 

#line 83 ".\\Source\\FWLib\\inc\\stm32f10x_iwdg.h"


 



 







 



 



 



 



 

void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);
void IWDG_SetReload(uint16_t Reload);
void IWDG_ReloadCounter(void);
void IWDG_Enable(void);
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);








 



 



 

 
#line 42 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_pwr.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_pwr.h"



 



  



  



  



  



  

#line 69 ".\\Source\\FWLib\\inc\\stm32f10x_pwr.h"


 



 







 



 




 


 



 










 



 



 



 



 

void PWR_DeInit(void);
void PWR_BackupAccessCmd(FunctionalState NewState);
void PWR_PVDCmd(FunctionalState NewState);
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
void PWR_WakeUpPinCmd(FunctionalState NewState);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);








 



 



 

 
#line 43 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"



 



 



 

typedef struct
{
  uint32_t SYSCLK_Frequency;   
  uint32_t HCLK_Frequency;     
  uint32_t PCLK1_Frequency;    
  uint32_t PCLK2_Frequency;    
  uint32_t ADCCLK_Frequency;   
}RCC_ClocksTypeDef;



 



 



 









  



 



#line 93 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"



  



 
#line 125 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"

#line 140 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 



 
#line 174 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 




 
#line 195 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 

#line 282 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"




 

#line 294 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 



 

#line 316 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


  



 

#line 332 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 



 

#line 346 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"

#line 363 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"




 




 








 
#line 395 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


#line 422 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"
  



 

#line 434 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 



 








 



 

#line 461 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 



 







#line 488 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"


 



 

#line 517 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"




  



 

#line 552 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"
 




 



 







#line 585 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"



 



 

#line 605 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"

#line 624 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"




 



 



 



 



 

void RCC_DeInit(void);
void RCC_HSEConfig(uint32_t RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);





#line 665 ".\\Source\\FWLib\\inc\\stm32f10x_rcc.h"

void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
uint8_t RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);
void RCC_PCLK1Config(uint32_t RCC_HCLK);
void RCC_PCLK2Config(uint32_t RCC_HCLK);
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);


 void RCC_USBCLKConfig(uint32_t RCC_USBCLKSource);




void RCC_ADCCLKConfig(uint32_t RCC_PCLK2);






void RCC_LSEConfig(uint8_t RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
void RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);





void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(uint8_t RCC_MCO);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(uint8_t RCC_IT);
void RCC_ClearITPendingBit(uint8_t RCC_IT);








 



 



  

 
#line 44 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_rtc.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_rtc.h"



 



  



  



  



 



 

#line 63 ".\\Source\\FWLib\\inc\\stm32f10x_rtc.h"


  



 

#line 81 ".\\Source\\FWLib\\inc\\stm32f10x_rtc.h"



 



 



 



 



 

void RTC_ITConfig(uint16_t RTC_IT, FunctionalState NewState);
void RTC_EnterConfigMode(void);
void RTC_ExitConfigMode(void);
uint32_t  RTC_GetCounter(void);
void RTC_SetCounter(uint32_t CounterValue);
void RTC_SetPrescaler(uint32_t PrescalerValue);
void RTC_SetAlarm(uint32_t AlarmValue);
uint32_t  RTC_GetDivider(void);
void RTC_WaitForLastTask(void);
void RTC_WaitForSynchro(void);
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG);
void RTC_ClearFlag(uint16_t RTC_FLAG);
ITStatus RTC_GetITStatus(uint16_t RTC_IT);
void RTC_ClearITPendingBit(uint16_t RTC_IT);








 



 



 

 
#line 45 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"



 



 



 

typedef struct
{
  uint32_t SDIO_ClockEdge;            
 

  uint32_t SDIO_ClockBypass;          

 

  uint32_t SDIO_ClockPowerSave;       

 

  uint32_t SDIO_BusWide;              
 

  uint32_t SDIO_HardwareFlowControl;  
 

  uint8_t SDIO_ClockDiv;              
 
                                           
} SDIO_InitTypeDef;

typedef struct
{
  uint32_t SDIO_Argument;  


 

  uint32_t SDIO_CmdIndex;   

  uint32_t SDIO_Response;  
 

  uint32_t SDIO_Wait;      
 

  uint32_t SDIO_CPSM;      

 
} SDIO_CmdInitTypeDef;

typedef struct
{
  uint32_t SDIO_DataTimeOut;     

  uint32_t SDIO_DataLength;      
 
  uint32_t SDIO_DataBlockSize;  
 
 
  uint32_t SDIO_TransferDir;    

 
 
  uint32_t SDIO_TransferMode;   
 
 
  uint32_t SDIO_DPSM;           

 
} SDIO_DataInitTypeDef;



  



 



 







 



 







  



 







 



 









 



 







 



 






  




 

#line 221 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"


  



 




 



 

#line 244 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"


 



 








 



 






  



 

#line 282 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"


 



 




 



 

#line 329 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"


 



 







 



 







 



 






 



 

#line 420 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"



#line 447 ".\\Source\\FWLib\\inc\\stm32f10x_sdio.h"





 



 







 



 



 



 



 

void SDIO_DeInit(void);
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_ClockCmd(FunctionalState NewState);
void SDIO_SetPowerState(uint32_t SDIO_PowerState);
uint32_t SDIO_GetPowerState(void);
void SDIO_ITConfig(uint32_t SDIO_IT, FunctionalState NewState);
void SDIO_DMACmd(FunctionalState NewState);
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct);
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct);
uint8_t SDIO_GetCommandResponse(void);
uint32_t SDIO_GetResponse(uint32_t SDIO_RESP);
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
uint32_t SDIO_GetDataCounter(void);
uint32_t SDIO_ReadData(void);
void SDIO_WriteData(uint32_t Data);
uint32_t SDIO_GetFIFOCount(void);
void SDIO_StartSDIOReadWait(FunctionalState NewState);
void SDIO_StopSDIOReadWait(FunctionalState NewState);
void SDIO_SetSDIOReadWaitMode(uint32_t SDIO_ReadWaitMode);
void SDIO_SetSDIOOperation(FunctionalState NewState);
void SDIO_SendSDIOSuspendCmd(FunctionalState NewState);
void SDIO_CommandCompletionCmd(FunctionalState NewState);
void SDIO_CEATAITCmd(FunctionalState NewState);
void SDIO_SendCEATACmd(FunctionalState NewState);
FlagStatus SDIO_GetFlagStatus(uint32_t SDIO_FLAG);
void SDIO_ClearFlag(uint32_t SDIO_FLAG);
ITStatus SDIO_GetITStatus(uint32_t SDIO_IT);
void SDIO_ClearITPendingBit(uint32_t SDIO_IT);








 



 



 

 
#line 46 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"



 



  



 



 

typedef struct
{
  uint16_t SPI_Direction;           
 

  uint16_t SPI_Mode;                
 

  uint16_t SPI_DataSize;            
 

  uint16_t SPI_CPOL;                
 

  uint16_t SPI_CPHA;                
 

  uint16_t SPI_NSS;                 

 
 
  uint16_t SPI_BaudRatePrescaler;   



 

  uint16_t SPI_FirstBit;            
 

  uint16_t SPI_CRCPolynomial;        
}SPI_InitTypeDef;



 

typedef struct
{

  uint16_t I2S_Mode;         
 

  uint16_t I2S_Standard;     
 

  uint16_t I2S_DataFormat;   
 

  uint16_t I2S_MCLKOutput;   
 

  uint32_t I2S_AudioFreq;    
 

  uint16_t I2S_CPOL;         
 
}I2S_InitTypeDef;



 



 










 
  
#line 135 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


 



 







 



 







  



 







 



 







 



 







  



 

#line 219 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


  



 







 



 

#line 247 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


 



 

#line 265 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


 



 

#line 281 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


  



 







 



 

#line 311 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"






  



 







 



 






 



 







 



 






 



 







 



 

#line 395 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


 



 

#line 416 ".\\Source\\FWLib\\inc\\stm32f10x_spi.h"


 



 




 



 



 



 



 

void SPI_I2S_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);
void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_TransmitCRC(SPI_TypeDef* SPIx);
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);








 



 



 

 
#line 47 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"



 



  



  




 

typedef struct
{
  uint16_t TIM_Prescaler;         
 

  uint16_t TIM_CounterMode;       
 

  uint16_t TIM_Period;            

  

  uint16_t TIM_ClockDivision;     
 

  uint8_t TIM_RepetitionCounter;  






 
} TIM_TimeBaseInitTypeDef;       



 

typedef struct
{
  uint16_t TIM_OCMode;        
 

  uint16_t TIM_OutputState;   
 

  uint16_t TIM_OutputNState;  

 

  uint16_t TIM_Pulse;         
 

  uint16_t TIM_OCPolarity;    
 

  uint16_t TIM_OCNPolarity;   

 

  uint16_t TIM_OCIdleState;   

 

  uint16_t TIM_OCNIdleState;  

 
} TIM_OCInitTypeDef;



 

typedef struct
{

  uint16_t TIM_Channel;      
 

  uint16_t TIM_ICPolarity;   
 

  uint16_t TIM_ICSelection;  
 

  uint16_t TIM_ICPrescaler;  
 

  uint16_t TIM_ICFilter;     
 
} TIM_ICInitTypeDef;




 

typedef struct
{

  uint16_t TIM_OSSRState;        
 

  uint16_t TIM_OSSIState;        
 

  uint16_t TIM_LOCKLevel;        
  

  uint16_t TIM_DeadTime;         

 

  uint16_t TIM_Break;            
 

  uint16_t TIM_BreakPolarity;    
 

  uint16_t TIM_AutomaticOutput;  
 
} TIM_BDTRInitTypeDef;



 

#line 185 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

 



 






 
#line 204 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"
									                                 
 
#line 215 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

                                             
#line 224 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

 
#line 235 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

 
#line 248 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

                                         
#line 265 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

 
#line 278 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"
                                                                                                                                                                                                                          


  



 

#line 307 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


 



 







  



 

#line 340 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 354 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


 



 

#line 372 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 







 



 
  






 



 







  



 







  



 







  



 







  



 







  



 







  



 







  



 

#line 496 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 







 



 







  



 







  



 







  



 

#line 560 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 576 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 592 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 609 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"

#line 618 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 664 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 708 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 724 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"



  



 

#line 741 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 769 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 783 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



  






 



 







  



 







  



 

#line 832 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  




 

#line 850 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"



  



 

#line 865 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 







  



 





                                     


  



 







  



 

#line 926 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 

#line 942 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"


  



 







  



 

#line 986 ".\\Source\\FWLib\\inc\\stm32f10x_tim.h"
                               
                               



  



 




  



 




  



 



 



  



 

void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource);
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState);
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter);
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, 
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode);
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint16_t Autoreload);
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD);
uint16_t TIM_GetCapture1(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture2(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture3(TIM_TypeDef* TIMx);
uint16_t TIM_GetCapture4(TIM_TypeDef* TIMx);
uint16_t TIM_GetCounter(TIM_TypeDef* TIMx);
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT);








  



  



 

 
#line 48 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"



 



  



  



  
  
typedef struct
{
  uint32_t USART_BaudRate;            


 

  uint16_t USART_WordLength;          
 

  uint16_t USART_StopBits;            
 

  uint16_t USART_Parity;              




 
 
  uint16_t USART_Mode;                
 

  uint16_t USART_HardwareFlowControl; 

 
} USART_InitTypeDef;



  
  
typedef struct
{

  uint16_t USART_Clock;   
 

  uint16_t USART_CPOL;    
 

  uint16_t USART_CPHA;    
 

  uint16_t USART_LastBit; 

 
} USART_ClockInitTypeDef;



  



  
  
















  
  


                                    




  



  
  
#line 145 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"


  



  
  
#line 159 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"


  



  
  





  



  
#line 186 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"


  



  






  



 
  






  



 







 



 







  



 
  
#line 263 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"


 



 







  



 







 



 
  







 



 







  



 

#line 335 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"
                              
#line 343 ".\\Source\\FWLib\\inc\\stm32f10x_usart.h"



  



  



  



  



 

void USART_DeInit(USART_TypeDef* USARTx);
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct);
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState);
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address);
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp);
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength);
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data);
uint16_t USART_ReceiveData(USART_TypeDef* USARTx);
void USART_SendBreak(USART_TypeDef* USARTx);
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime);
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler);
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState);
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode);
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState);
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG);
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT);
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);








  



  



  

 
#line 49 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\stm32f10x_wwdg.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\stm32f10x_wwdg.h"



 



  



  
  


  



  
  


  
  
#line 67 ".\\Source\\FWLib\\inc\\stm32f10x_wwdg.h"



  



  



  


  



  
  
void WWDG_DeInit(void);
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void WWDG_SetWindowValue(uint8_t WindowValue);
void WWDG_EnableIT(void);
void WWDG_SetCounter(uint8_t Counter);
void WWDG_Enable(uint8_t Counter);
FlagStatus WWDG_GetFlagStatus(void);
void WWDG_ClearFlag(void);









  



  



  

 
#line 50 ".\\Source\\APP\\stm32f10x_conf.h"
#line 1 ".\\Source\\FWLib\\inc\\misc.h"



















  

 







 
#line 32 ".\\Source\\FWLib\\inc\\misc.h"



 



 



 



 

typedef struct
{
  uint8_t NVIC_IRQChannel;                    


 

  uint8_t NVIC_IRQChannelPreemptionPriority;  

 

  uint8_t NVIC_IRQChannelSubPriority;         

 

  FunctionalState NVIC_IRQChannelCmd;         

    
} NVIC_InitTypeDef;
 


 



 
























 



 



 



 







 



 

#line 132 ".\\Source\\FWLib\\inc\\misc.h"


 



 

#line 150 ".\\Source\\FWLib\\inc\\misc.h"















 



 







 



 



 



 



 

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);









 



 



 

 
#line 51 ".\\Source\\APP\\stm32f10x_conf.h"

 
 

 
 

 
#line 73 ".\\Source\\APP\\stm32f10x_conf.h"



 
#line 8281 ".\\Source\\FWLib\\cm3\\stm32f10x.h"




 

















 









 

  

 

 
#line 5 "Source\\Net\\enc28j60.h"


















#line 35 "Source\\Net\\enc28j60.h"




#line 51 "Source\\Net\\enc28j60.h"

#line 76 "Source\\Net\\enc28j60.h"

#line 96 "Source\\Net\\enc28j60.h"

#line 113 "Source\\Net\\enc28j60.h"

#line 123 "Source\\Net\\enc28j60.h"


#line 133 "Source\\Net\\enc28j60.h"

#line 142 "Source\\Net\\enc28j60.h"

#line 150 "Source\\Net\\enc28j60.h"












#line 170 "Source\\Net\\enc28j60.h"







#line 183 "Source\\Net\\enc28j60.h"

#line 192 "Source\\Net\\enc28j60.h"






























#line 229 "Source\\Net\\enc28j60.h"




























unsigned char enc28j60ReadOp(unsigned char op, unsigned char address);
void 	enc28j60WriteOp(unsigned char op, unsigned char address, unsigned char data);
void 	enc28j60ReadBuffer(unsigned int len, unsigned char* data);
void 	enc28j60WriteBuffer(unsigned int len, unsigned char* data);
void 	enc28j60SetBank(unsigned char address);
unsigned char enc28j60Read(unsigned char address);
void 	enc28j60Write(unsigned char address, unsigned char data);
void 	enc28j60PhyWrite(unsigned char address, unsigned int data);
void 	enc28j60clkout(unsigned char clk);
void 	enc28j60Init(unsigned char* macaddr);
unsigned char enc28j60getrev(void);
void 	enc28j60PacketSend(unsigned int len, unsigned char* packet);
unsigned int enc28j60PacketReceive(unsigned int maxlen, unsigned char* packet);

#line 17 "Source\\Net\\enc28j60.c"
#line 1 "Source\\Net\\spi_enc28j60.h"



#line 5 "Source\\Net\\spi_enc28j60.h"


void SPI_Enc28j60_Init(void);
unsigned char	SPI2_ReadWrite(unsigned char writedat);

#line 18 "Source\\Net\\enc28j60.c"

static unsigned char Enc28j60Bank;
static unsigned int NextPacketPtr;


unsigned char enc28j60ReadOp(unsigned char op, unsigned char address)
{
    unsigned char dat = 0;
    
    ((GPIO_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x0C00))->BRR = ((uint16_t)0x1000);;
    
    dat = op | (address & 0x1F);
    SPI2_ReadWrite(dat);
    dat = SPI2_ReadWrite(0xFF);
    
    if(address & 0x80)
    {
        dat = SPI2_ReadWrite(0xFF);
    }
    
    ((GPIO_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x0C00))->BSRR = ((uint16_t)0x1000);;
    return dat;
}

void enc28j60WriteOp(unsigned char op, unsigned char address, unsigned char data)
{
    unsigned char dat = 0;
    
    ((GPIO_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x0C00))->BRR = ((uint16_t)0x1000);;
    
    dat = op | (address & 0x1F);
    SPI2_ReadWrite(dat);
    
    dat = data;
    SPI2_ReadWrite(dat);
    ((GPIO_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x0C00))->BSRR = ((uint16_t)0x1000);;
}

void enc28j60ReadBuffer(unsigned int len, unsigned char* data)
{
    ((GPIO_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x0C00))->BRR = ((uint16_t)0x1000);;
    
    SPI2_ReadWrite(0x3A);
    while(len)
    {
        len--;
        
        *data = (unsigned char)SPI2_ReadWrite(0);
        data++;
    }
    *data='\0';
    ((GPIO_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x0C00))->BSRR = ((uint16_t)0x1000);;
}

void enc28j60WriteBuffer(unsigned int len, unsigned char* data)
{
    ((GPIO_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x0C00))->BRR = ((uint16_t)0x1000);;
    
    SPI2_ReadWrite(0x7A);
    
    while(len)
    {
        len--;
        SPI2_ReadWrite(*data);
        data++;
    }
    ((GPIO_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x0C00))->BSRR = ((uint16_t)0x1000);;
}

void enc28j60SetBank(unsigned char address)
{
    
    if((address & 0x60) != Enc28j60Bank)
    {
        
        enc28j60WriteOp(0xA0, 0x1F, (0x02|0x01));
        enc28j60WriteOp(0x80, 0x1F, (address & 0x60)>>5);
        Enc28j60Bank = (address & 0x60);
    }
}

unsigned char enc28j60Read(unsigned char address)
{
    
    enc28j60SetBank(address);
    
    return enc28j60ReadOp(0x00, address);
}

void enc28j60Write(unsigned char address, unsigned char data)
{
    
    enc28j60SetBank(address);
    
    enc28j60WriteOp(0x40, address, data);
}

void enc28j60PhyWrite(unsigned char address, unsigned int data)
{
    
    enc28j60Write((0x14|0x40|0x80), address);
    
    enc28j60Write((0x16|0x40|0x80), data);
    enc28j60Write((0x17|0x40|0x80), data>>8);
    
    while(enc28j60Read((0x0A|0x60|0x80)) & 0x01)
    {
        
        
    }
}

void enc28j60clkout(unsigned char clk)
{
    
    enc28j60Write((0x15|0x60), clk & 0x7);
}

void enc28j60Init(unsigned char* macaddr)
{   
    ((GPIO_TypeDef *) ((((uint32_t)0x40000000) + 0x10000) + 0x0C00))->BSRR = ((uint16_t)0x1000);;	      

    
    enc28j60WriteOp(0xFF, 0, 0xFF);
   
    
    
    
    
    
    
    
    NextPacketPtr = 0x0;
    
    enc28j60Write((0x08|0x00), 0x0&0xFF);	 
    enc28j60Write((0x09|0x00), 0x0>>8);
    
    enc28j60Write((0x0C|0x00), 0x0&0xFF);
    enc28j60Write((0x0D|0x00), 0x0>>8);
    
    enc28j60Write((0x0A|0x00), (0x1FFF-0x0600-1)&0xFF);
    enc28j60Write((0x0B|0x00), (0x1FFF-0x0600-1)>>8);
    
    enc28j60Write((0x04|0x00), (0x1FFF-0x0600)&0xFF);
    enc28j60Write((0x05|0x00), (0x1FFF-0x0600)>>8);
    
    enc28j60Write((0x06|0x00), 0x1FFF&0xFF);
    enc28j60Write((0x07|0x00), 0x1FFF>>8);
    
    
    
    
    
    
    
    
    
    
    
    enc28j60Write((0x18|0x20), 0x80|0x20|0x10);
    enc28j60Write((0x08|0x20), 0x3f);
    enc28j60Write((0x09|0x20), 0x30);
    enc28j60Write((0x10|0x20), 0xf9);
    enc28j60Write((0x11|0x20), 0xf7);    
    enc28j60Write((0x00|0x40|0x80), 0x01|0x08|0x04);
    
    enc28j60Write((0x01|0x40|0x80), 0x00);
    
    enc28j60WriteOp(0x80, (0x02|0x40|0x80), 0x20|0x10|0x02|0x01);
    

    enc28j60Write((0x06|0x40|0x80), 0x12);
    enc28j60Write((0x07|0x40|0x80), 0x0C);
    

    enc28j60Write((0x04|0x40|0x80), 0x15);
    
    
  
    enc28j60Write((0x0A|0x40|0x80), 1500&0xFF);	
    enc28j60Write((0x0B|0x40|0x80), 1500>>8);
    
    
    
    enc28j60Write((0x04|0x60|0x80), macaddr[0]);	
    enc28j60Write((0x05|0x60|0x80), macaddr[1]);
    enc28j60Write((0x02|0x60|0x80), macaddr[2]);
    enc28j60Write((0x03|0x60|0x80), macaddr[3]);
    enc28j60Write((0x00|0x60|0x80), macaddr[4]);
    enc28j60Write((0x01|0x60|0x80), macaddr[5]);

    
    enc28j60PhyWrite(0x00, 0x0100);    
    
    
    enc28j60PhyWrite(0x10, 0x0100);

    
    enc28j60SetBank(0x1F);

    
    enc28j60WriteOp(0x80, 0x1B, 0x80|0x40);

    
    enc28j60WriteOp(0x80, 0x1F, 0x04);
}


unsigned char enc28j60getrev(void)
{
    
    
    
    return(enc28j60Read((0x12|0x60)));
}

void enc28j60PacketSend(unsigned int len, unsigned char* packet)
{
    
    enc28j60Write((0x02|0x00), (0x1FFF-0x0600)&0xFF);
    enc28j60Write((0x03|0x00), (0x1FFF-0x0600)>>8);
    
    
    enc28j60Write((0x06|0x00), ((0x1FFF-0x0600)+len)&0xFF);
    enc28j60Write((0x07|0x00), ((0x1FFF-0x0600)+len)>>8);
    
    
    enc28j60WriteOp(0x7A, 0, 0x00);
    
    
    enc28j60WriteBuffer(len, packet);
    
    
    enc28j60WriteOp(0x80, 0x1F, 0x08);
    
    
    if( (enc28j60Read(0x1C) & 0x02) )
    {
        enc28j60WriteOp(0xA0, 0x1F, 0x08);
    }
}






unsigned int enc28j60PacketReceive(unsigned int maxlen, unsigned char* packet)
{
    unsigned int rxstat;
    unsigned int len;
    
    
    
    
    if( enc28j60Read((0x19|0x20)) ==0 )  
    {
        return(0);
    }
    
    
    enc28j60Write((0x00|0x00), (NextPacketPtr));
    enc28j60Write((0x01|0x00), (NextPacketPtr)>>8);
    
    
    NextPacketPtr  = enc28j60ReadOp(0x3A, 0);
    NextPacketPtr |= enc28j60ReadOp(0x3A, 0)<<8;
    
    
    len  = enc28j60ReadOp(0x3A, 0);
    len |= enc28j60ReadOp(0x3A, 0)<<8;
    
    len-=4; 
    
    rxstat  = enc28j60ReadOp(0x3A, 0);
    rxstat |= enc28j60ReadOp(0x3A, 0)<<8;
    
    if (len>maxlen-1)
    {
        len=maxlen-1;
    }
    
    
    
    
    if ((rxstat & 0x80)==0)
    {
        
        len=0;
    }
    else
    {
        
        enc28j60ReadBuffer(len, packet);
    }
    
    
    enc28j60Write((0x0C|0x00), (NextPacketPtr));
    enc28j60Write((0x0D|0x00), (NextPacketPtr)>>8);
    
    
    enc28j60WriteOp(0x80, 0x1E, 0x40);
    return(len);
}



