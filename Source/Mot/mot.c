#include "SimSwitch.h"
#include "mot.h"
#include "math.h"
#include "gui_app.h"
#include"LimitDraw.h"


#ifndef WIN_SIM
#include "stm32f10x.h"
#endif

/* Private typedef -----------------------------------------------------------*/
// 不用float 的方法 速度单位 mm/s unsigned int 
///                 频率     hz   unsigned int
//                  电流     mA   unsigned int
//           
/* Private define ------------------------------------------------------------*/
extern  TPars   pars;
extern	TRecord record;
extern  S_GetData get_data;

extern TTPars ttpars;

TSpeed_buf tspeed_buf;

TMot_t_Cal 	mot_t_cal;

unsigned long last_cap_value;

float last_speed;

char enable_sin;

unsigned long bt_data;
float current_frequence;
unsigned int get_freq;
unsigned long current_cap_value;
unsigned int time_up;
unsigned short ADCConvertedValue;

unsigned long last_get_time;

unsigned char sw1_already_oper;
unsigned char sw2_already_oper;
unsigned char init_sw1_state;
unsigned char init_sw2_state;

char judge_res;

float* sin_buf;


#ifndef WIN_SIM
EXTI_InitTypeDef  EXTI_InitStructure_A;
#endif



void start_test_init()
{

#ifndef WIN_SIM
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
 // TIM_Cmd(TIM4, ENABLE);
#endif

	last_get_time =0;
	last_cap_value = 0;
    time_up =0;

	get_data.acce =0;
	get_data.current =0;
	get_data.frequence=0;
	get_data.speed =0;
	get_data.sw1_speed=0;
	get_data.sw2_speed=0;

	get_data.times = 0;
	
	sw1_already_oper = 0;
	sw2_already_oper = 0;

	enable_sin = 0;

	get_data.e_work_state = START_TEST;

	tspeed_buf.in_loc = 0;
	tspeed_buf.out_loc = 0;
	tspeed_buf.in_data_size = 0;

	if(!intit_sw_state())
	{

	list_view_color(3,0,GUI_LIGHTCYAN);

	}
 
	if((!mot_t_cal.cal_flag)&&(current_interface == PORTABLE_LIMIT_SPEED_T))
	{

	//mot_t_get_speed_line(mot_t_cal);

	}
	
	if(current_interface == PORTABLE_LIMIT_SPEED_T)
	{

	set_speed(ttpars.start_speed);
	if(etest_mode == TEST_MODE_SIN)
	{
#ifndef WIN_SIM
	  TIM_Cmd(TIM5, ENABLE);
#endif

	}	
	
	}else{

	pars.pwm_acc = pars.start_speed*PWM_PER_SPEED(pars.R_mm);
	set_speed(pars.pwm_acc);

	}

#ifndef WIN_SIM
  	EXTI_InitStructure_A.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure_A);
#endif

}


void motor_int(void)
{
#ifndef WIN_SIM

    NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  	TIM_OCInitTypeDef  TIM_OCInitStructure;	
    ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;

	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//配置ADC时钟= PCLK2/4
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM5|RCC_APB1Periph_TIM7,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC| RCC_APB2Periph_AFIO,ENABLE);
	 /* GPIOA and GPIOB clock enable */
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);     

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;		 //
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	 
  	GPIO_Init(GPIOD, &GPIO_InitStructure);	 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;		 //SW3_IN SW1_IN SW2_IN
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		 //TIM3_CH1
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	 
//  GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;		 //TIM2_CH1
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	 
    GPIO_Init(GPIOA, &GPIO_InitStructure);

//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;		 //
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;	 
//  	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;		 //ADC_IN0_MOTO
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	 
  	GPIO_Init(GPIOC, &GPIO_InitStructure);		
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6;		 //SW3_IN SW1_IN SW2_IN
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	 
  	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;		 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 
  	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource5|GPIO_PinSource6);// 修改
  	EXTI_InitStructure_A.EXTI_Line = EXTI_Line5|EXTI_Line6; 
  	EXTI_InitStructure_A.EXTI_Mode = EXTI_Mode_Interrupt;
  	EXTI_InitStructure_A.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  	EXTI_InitStructure_A.EXTI_LineCmd = DISABLE;
  	EXTI_Init(&EXTI_InitStructure_A);

// PWM set
//  	
//	TIM_TimeBaseStructure.TIM_Period = 9999;//1999 72k,3999 36k, 5999 18k, 7999 9K	9999 4.5K 11999 2.25k	   
//  TIM_TimeBaseStructure.TIM_Prescaler = 14238;//1M
	
	TIM_TimeBaseStructure.TIM_Period = 7999;//1999 72k,3999 36k, 5999 18k, 7999 9K	9999 4.5K 11999 2.25k	   
    TIM_TimeBaseStructure.TIM_Prescaler = 0;//  		 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;	  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);               //
	
  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//exp ----
  	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_CtrlPWMOutputs(TIM4, ENABLE);

  	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

	TIM_OC1Init(TIM4,&TIM_OCInitStructure);  // 修改
  	TIM_Cmd(TIM4, DISABLE);
  	
//Input capture  没有外部脉冲情况是否也进入中断--- 可以进入中断 因为
//要不断的计数
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;//1999 36k,3999 18k, 5999 9k, 7999 4.5K	9999 2.25K	   
    TIM_TimeBaseStructure.TIM_Prescaler = TIME_CLK_DIV;//TIMxCLK / (Prescaler +1)		 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;	  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0;

    TIM_ICInit(TIM2, &TIM_ICInitStructure);
  	TIM_Cmd(TIM2, ENABLE);

    /* Enable the CC1 Interrupt Request */
    TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);

	#ifdef TEST_MODE_1
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	#endif 

#if 0	
  	DMA_DeInit(DMA1_Channel1);
  	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
  	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  	DMA_InitStructure.DMA_BufferSize = 1;
  	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

  /* Enable DMA1 channel1 */
  	DMA_Cmd(DMA1_Channel1, ENABLE);
  
  /* ADC1 configuration ------------------------------------------------------*/
  	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  	ADC_InitStructure.ADC_NbrOfChannel = 1;
  	ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel14 configuration */ 
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_55Cycles5);

  /* Enable ADC1 DMA */
    ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
    ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
    while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
    ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
    while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
#endif

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
  /* Enable the TIM3 global Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
	
  //base timers 
  //1999 72k,3999 36k, 5999 18k, 7999 9K	9999 4.5K 	
  //1k - 1ms -  
    TIM_TimeBaseStructure.TIM_Period = 9999;// 222us 222000us 222.0ms
    TIM_TimeBaseStructure.TIM_Prescaler = 999;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM7, DISABLE);

	//TIM1 counter clock = TIMxCLK / (Prescaler +1) 
	//                   = 72M/144 = 500K
	//TIMx ARR Register = 10000 => TIMx Frequency = TIMxcounter clock/(9999 + 1)= 500K/10000 = 50HZ 
	//2k hz 1M - 1us 1k - 1ms 2k - 0.5ms


	// 与 DIV_TIM  DIV_TIMS_MS
	// 1k -- 1ms   2k -- 0.5ms
	// 
    TIM_TimeBaseStructure.TIM_Period = 199;// 2K
    TIM_TimeBaseStructure.TIM_Prescaler = 359; //TIMxCLK / (Prescaler +1)  72/360 = 0.2M = 200K
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM5, DISABLE);

#endif		
}


// 0 - stop
// 1 - c
// 2 - rc
void motor_dir(int dir)
{
#ifndef WIN_SIM

	if(dir == 0)
	{
	 GPIO_ResetBits(GPIOE, GPIO_Pin_0);
	 GPIO_ResetBits(GPIOA, GPIO_Pin_15);
	 motor_speed(0);
	}else if(dir == 1){
	 GPIO_SetBits(GPIOE, GPIO_Pin_0);
	 GPIO_ResetBits(GPIOA, GPIO_Pin_15);	
	}else if(dir == 2){
	 GPIO_ResetBits(GPIOE, GPIO_Pin_0);
	 GPIO_SetBits(GPIOA, GPIO_Pin_15);	
	}
#endif
}


// 0 - 100 
// 100 -- ?
// 0 -- ?
void motor_speed(int pwm_speed)
{
#ifndef WIN_SIM
	TIM4->CCR1 = 8000 - pwm_speed*8;
#endif

  //TIM3->CCR2 = 10000 - pwm_speed*100;
}


#ifndef WIN_SIM
//自有捕获法

//首先，不要配置从模式控制器在捕获成功时复位计数器，这样就不会在收到捕获中断的同时出现溢出中断。
//其次，你需要把ARR参数配置为其最大值0xFFFF，这样可以得到最少的溢出中断。
//这样配置后，如果在中断程序中发现捕获中断与溢出中断同时出现，则可能有下述两种情况：
//1）捕获中断先于溢出中断出现：此时读出的捕获数值CCR应该是一个接近0xFFFF的数值，这样测量的周期就是(溢出中断累计次数*0x10000+CCR)。
//2）捕获中断晚于溢出中断出现：此时读出的捕获数值CCR应该是一个接近于0的数值，这样测量的周期就是((溢出中断累计次数+1)*0x10000+CCR)。
// 出现问题 会偶尔出现数据乱跳 到很高
// 对此用 标准信号源测试 不会出现乱跳
// 怀疑	1
// 波形在示波器上看 会移动？为何？
// 怀疑 2
// 脉冲有 杂波 1 降低捕捉频率 试验，2 查看 实际  bt_data 3 基础滤波	 4 次数显示法 5 浮点数表示的问题
// 问题的解决 结合 次数显示法+基础滤波
void TIM2_Interrupt(void)
{	
unsigned int i;

#ifdef TEST_MODE_1

  if((TIM_GetITStatus(TIM2, TIM_IT_CC1) == SET)&&(TIM_GetITStatus(TIM2, TIM_IT_Update) != SET)) 
  {
  	for(i=0;i<1500;i++)	 // 3 基础滤波
	{
	  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)!=0)
	   {
	   TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
	   return;
	   }
	}

	 if(last_cap_value == 0)
	{
	  last_cap_value = time_up*0x10000+TIM_GetCapture1(TIM2);
	  last_speed = 0;

	}else{
	  current_cap_value = time_up*0x10000+ TIM_GetCapture1(TIM2);
	  if(current_cap_value > last_cap_value)
	  {
	   bt_data = current_cap_value - last_cap_value;
	  
	  }else{
	  	   
	   bt_data = ((0xFFFFFFFF  - last_cap_value) + current_cap_value); 
	   
	  }						  
	  
	  fresh_data();
	  //if(judge()<= ONE_STOP)
	  {
		adjust_pwm_speed();
	  }
	  //judge_result();
	}

	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);

  }else if((TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)&&(TIM_GetITStatus(TIM2, TIM_IT_CC1) != SET))
  {
	time_up++;
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

  }else if((TIM_GetITStatus(TIM2, TIM_IT_CC1) == SET)&&(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET))
  {
	 if(current_cap_value > 0xfff0)
	 {
	 current_cap_value = time_up*0x10000 + TIM_GetCapture1(TIM2);
	 }else{
	 current_cap_value = (time_up+1)*0x10000 + TIM_GetCapture1(TIM2);
	 }
	 if(last_cap_value == 0)
	{
	  last_cap_value = time_up*0x10000+TIM_GetCapture1(TIM2);

	}else{
	  current_cap_value = time_up*0x10000+ TIM_GetCapture1(TIM2);
	  if(current_cap_value > last_cap_value)
	  {

	   bt_data = current_cap_value - last_cap_value;
	  
	  }else{
	  
	   bt_data = ((0xFFFFFFFF - last_cap_value) + current_cap_value); 
	   
	  }
	  fresh_data();
	  //if(judge()<= ONE_STOP)
	  {
		adjust_pwm_speed();
	  }
	  //judge_result();
	} 
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);  
  }
 #endif
}


void TIM7_Interrupt(void)
{
	
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);

	if(get_data.sw1_speed > tspeed_buf.speed_buf[tspeed_buf.in_loc&(BUF_SIZE-1)])
	{

	one_stop();

	}else{
	
	}
	
#if 0	
	if(( CURRENT(ADCConvertedValue)!=0)&&(last_speed == get_data.speed)&&(get_data.speed!=0))
	{
	#if 0
		motor_dir(0);
		record_result(HAND_OFF);	
	#endif
	}
#endif

}
#endif


//启动时给个初速度，启动无负载默认 PWM 脉宽和速度成正比
void set_speed(float speed)
{
  float  set_current;
   //motor_speed(speed*PWM_PER_SPEED(pars.R_mm));
  if(current_interface == PORTABLE_LIMIT_SPEED_T)
  {
   set_current = speed*mot_t_cal.k_R_r/1000;
#ifndef WIN_SIM
   set_data(set_current);
#endif
  }else{

   motor_speed(speed);
   }
}



void fresh_data(void)
{
#ifndef WIN_SIM
float cir; 

    current_frequence  = ((GET_SYS_CLK_HZ)*100)/(bt_data);
	current_frequence  =  current_frequence/100;
   
	if(current_interface == PORTABLE_LIMIT_SPEED_T)
	{
	get_data.speed = mot_t_cal.encode_mm_per_plus/(1000*bt_data);
	
	}else{
	cir = (CACU_BASE(pars.R_mm)*GET_SYS_CLK_HZ)/(bt_data); //m/s 转为保留3位小数	
	get_data.speed = cir/1000;
	}

    get_data.frequence = current_frequence;
	last_speed = get_data.speed;
	last_cap_value = current_cap_value;
	
	get_data.bt_time_s = 0.5*bt_data/1000000;
	get_data.time_us = get_data.time_us + 0.5*bt_data;// 2M - 0.5us

	tspeed_buf.speed_buf[tspeed_buf.in_loc&(BUF_SIZE-1)] = get_data.speed;
	tspeed_buf.in_loc++;
	tspeed_buf.in_data_size++;

#endif
}


void adjust_pwm_speed()
{
	float u1,racc,u0,speed;

 if(current_interface == PORTABLE_LIMIT_SPEED_T)
 {
 	 if(etest_mode == TEST_MODE_T)// 跳变测试
	 {
	 	if((get_data.time_us >= (ttpars.t0+ttpars.t1)*1000)&&(get_data.time_us < (ttpars.t0+ttpars.t1+ttpars.t2)*1000))
		{
			motor_speed(ttpars.start_speed+ttpars.dV);
		}else{
			motor_speed(ttpars.start_speed);
		}
	 }else if(etest_mode == TEST_MODE_COM){
	 	if(get_data.time_us >= (ttpars.t0)*1000)
		{
			u0 = get_data.speed;
			if(record.test_times == 0)
			{
			if(u0<ttpars.V1)
				speed = u0+ get_data.bt_time_s*ttpars.a1;
			else if(u0>ttpars.V1)
				speed = u0+ get_data.bt_time_s*ttpars.a2;
				
			}else{
			if(u0<ttpars.V1)
				speed = u0+ get_data.bt_time_s*ttpars.a1;
			else if((u0>ttpars.V1) &&(u0<ttpars.V2))
				speed = u0+ get_data.bt_time_s*ttpars.a2;
			else 
				speed = u0+ get_data.bt_time_s*ttpars.a3;

			motor_speed(speed);
			}
		}else{
			motor_speed(ttpars.start_speed);
		}
	 }else if(etest_mode == TEST_MODE_SIN){
	 			
			
	 }
 }else{
		u0 = get_data.speed;
		if(record.test_times == 0)
		{
			if(u0<pars.v1)
				racc =pars.ak1;
			else if(u0 > pars.v1)
				racc = pars.ak2;
			
		}else if(record.test_times > 0)
			{
			if(u0<pars.v1)
				racc =pars.ak1;
			else if((u0 >pars.v1)&&(u0 < pars.v2))
				racc = pars.ak2;
			else if(u0 > pars.v2)
				racc = pars.ak3;
		}
	 pars.pwm_acc = pars.pwm_acc + racc;
	 if(pars.pwm_acc > LIMIT_PWM_ACC)
	 return;
	 else
	 	motor_speed(pars.pwm_acc);
	}

// Ut(2) - U0*Ut - a*cir = 0	
//	u1 = quadratic_equation(1,-u0,-racc*CACU_BASE(pars.R_mm));
//	motor_speed(PWM_PER_SPEED(pars.R_mm)*u1);
}


void test_stop()
{
	int max;
#ifndef WIN_SIM
   EXTI_InitStructure_A.EXTI_LineCmd = DISABLE;
   EXTI_Init(&EXTI_InitStructure_A);

   TIM_Cmd(TIM2, DISABLE);
   TIM_Cmd(TIM4, DISABLE);
   TIM_Cmd(TIM5, DISABLE);
   TIM_Cmd(TIM7, DISABLE);

   set_speed(0);
   motor_dir(0);

   	if(current_interface == PORTABLE_LIMIT_SPEED_T)
   {
	max = GUI_ID_BUTTON_TMAIN;
   }else{
    max = GUI_ID_BUTTON_DELET;
   }
	all_button(1,max);

#endif
}


int one_stop()
{
	int max;
#ifndef WIN_SIM	
	  motor_dir(0);
	  get_data.sw2_speed = get_data.speed;
	  record.e_work_state[record.test_times] = ONE_STOP;
	  get_data.e_work_state = ONE_STOP;
	  record.v1[record.test_times]= get_data.sw1_speed;

	  if(SW1!=init_sw1_state && SW2!= init_sw2_state)
	  	{
	  record.v2[record.test_times]= get_data.sw2_speed;
	  	}else {
	  record.v2[record.test_times]= 0;
	  get_data.speed = 0;
		}

	  record.dir[record.test_times]= pars.dir;
	  test_stop();
	  judge_result();


	if(current_interface == PORTABLE_LIMIT_SPEED_T)
   {
	max = GUI_ID_BUTTON_TMAIN;
   }else{
    max = GUI_ID_BUTTON_DELET;
   }
	all_button(1,max);
#endif
	  return ONE_STOP;
}

void judge_result()
{
 unsigned int i;
 unsigned int col;
 float pass_limit,pass_max;
 pass_limit =  PASS_LIMIT(pars.ve);
 pass_max =   PASS_MAX(pars.ve);

 col = GUI_LIGHTRED;

 if(record.v2[record.test_times]!= 0)
 {
 	if(record.v1[record.test_times] >= pass_limit && record.v1[record.test_times] <= pass_max||
 	record.v2[record.test_times] >= pass_limit && record.v2[record.test_times] <= pass_max)
 	{
	record.result[record.test_times] = 1;
    }else{
	record.result[record.test_times] = 0;
	
	list_view_color(0, 0,col); 
    }

 }else{

 	if(record.v1[record.test_times] >= pass_limit && record.v1[record.test_times] <= pass_max)
 	{
	record.result[record.test_times] = 1;
    }else{
	record.result[record.test_times] = 0;
	list_view_color(0, 0,col); 
    }
 }
}



char intit_sw_state()
{
 	unsigned char sw1_st1,sw2_st2;
#ifndef WIN_SIM
	 if(record.test_times == 1)
		{
		init_sw1_state = SW1;
		init_sw2_state = SW2;
		return 1;
		}else{
		sw1_st1 = SW1;
		sw2_st2 = SW2;
		if((sw1_st1 != init_sw1_state)||(sw2_st2!= init_sw2_state))
			{
		get_data.e_work_state = SWI_ERR;
		
		return 0;
			}else{
		get_data.e_work_state = START_TEST;
		return 1;
			}
		}
#endif

}


#ifndef WIN_SIM
void EXIT9_5()
{
   int i;
   if(EXTI_GetITStatus(EXTI_Line5) != RESET)// 默认为1	SW1
  {
  	EXTI_ClearITPendingBit(EXTI_Line5);
	  	if((SW1 != init_sw1_state)&&(!sw1_already_oper))
	{
		for(i=0;i<1000;i++)
		{
		if(SW1 == init_sw1_state )
		{
		 
		return;

		}
		}
	  sw1_already_oper = 1;
	  
	  if(sw2_already_oper)
	  {
	  one_stop();

	  }else{
	   get_data.sw1_speed = get_data.speed;
	   record.e_work_state[record.test_times] = GET_V1;
	   get_data.e_work_state = GET_V1;
	   TIM_Cmd(TIM7, ENABLE);
	  }
	}

  }else if(EXTI_GetITStatus(EXTI_Line6) != RESET)//默认为2
  {
    EXTI_ClearITPendingBit(EXTI_Line6);
  	if((SW2 != init_sw2_state)&&(!sw2_already_oper))
	{
		for(i=0;i<1000;i++)
		{
		if(SW2 == init_sw2_state )
		{
		return;
		}
		}
	  sw2_already_oper = 1;
	  
	  if(sw1_already_oper)
	  {
	  one_stop();
	  }else{
	   get_data.sw1_speed = get_data.speed;
	   record.e_work_state[record.test_times] = GET_V1;
	   get_data.e_work_state = GET_V1;
	   TIM_Cmd(TIM7, ENABLE);
	  }
	}
  }
}

#endif

#if 0

unsigned int get_current(void)
{
 return ADCConvertedValue;
}

// ax(2)+bx+c = 0
// -b/2+sqr(b*b-4ac)/2
// ax(2)+bx+c = 0
float quadratic_equation(float a,float b,float c)
{
	float mid0,mid1,mid2;
	mid0 = sqrt(b*b - 4*a*c);
	mid1 = (mid0 - b)/2;
	return mid1;
}
#endif

void err_back(EWorkState work_state)
{
	test_stop();
	delect_now_row();
}


// 求取k值	k值对应 电流和速度的关系

void mot_t_get_speed_line(TMot_t_Cal  mot_t_cal)
{
	unsigned int start_ma, first_ma, second_ma,size;
	float get_speed_x0_ma, get_speed_x1_ma,k;

	for(start_ma=1;start_ma<10;start_ma++)
	{
#ifndef WIN_SIM
   	 set_data(start_ma);// 

	 OSTimeDlyHMSM(0,0,2,0);
#endif
	 if(get_data.speed !=0)
	 {
	 break;
	 }
	}
	first_ma = start_ma;
	get_speed_x0_ma = get_data.speed;

	second_ma = first_ma + 2;
#ifndef WIN_SIM
    OSTimeDlyHMSM(0,0,2,0);
#endif

	get_speed_x1_ma = get_data.speed;

	mot_t_cal.k = 2000/(get_speed_x1_ma - get_speed_x0_ma);// 2ma 乘以1000 倍  电流/速度

	mot_t_cal.cal_flag = 1;

	mot_t_cal.max_speed_m_per_s = (get_speed_x1_ma - get_speed_x0_ma)*10;// 20ma 对应的速度
	
	mot_t_cal.R_r = ttpars.R_mm/ttpars.r_mm;

	mot_t_cal.k_R_r =  mot_t_cal.k*mot_t_cal.R_r;

	mot_t_cal.r_R = ttpars.r_mm/ttpars.R_mm;
	
	mot_t_cal.encode_mm_per_plus = 2*3.1415926*ttpars.enc_r/ttpars.enc_n;

	//	1000/ttpars.HZ  -- ms				
	size = 	1000/(ttpars.HZ*DIV_TIMS_MS);								//		
	
	mot_t_cal.k_sin = ttpars.Vp;
	
	mot_t_cal.div_times = size;

	sin_buf =  sin_1_4(size);
}


float* sin_1_4(int size)
{
	float* sin_stand_buf;
	int i,end_size;
	sin_stand_buf = (float *)malloc(sizeof(float)*size);

	for(i=0;i<size;i++)
	{
	  sin_stand_buf[i] = mot_t_cal.k_sin*sin((2*3.14159)/i);
	}
	return sin_stand_buf;
}

void TIM5_Interrupt(void)
{
	float speed;


	if(enable_sin)
	{
	speed = ttpars.start_speed+sin_buf[mot_t_cal.counter&(mot_t_cal.div_times -1)];
	set_speed(speed);
	mot_t_cal.counter++;
	}

	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	
#if 0
	 if(etest_mode == TEST_MODE_COM){

	 	if(get_data.time_us >= (ttpars.t0)*1000)
		{
			u0 = get_data.speed;
			if(record.test_times == 0)
			{
			if(u0<ttpars.V1)
				speed = u0+ dt*ttpars.a1;
			else if(u0>ttpars.V1)
				speed = u0+ dt*ttpars.a2;
				
			}else{
			if(u0<ttpars.V1)
				speed = u0+ dt*ttpars.a1;
			else if((u0>ttpars.V1) &&(u0<ttpars.V2))
				speed = u0+ dt*ttpars.a2;
			else 
				speed = u0+ dt*ttpars.a3;
			motor_speed(speed);
			}
#endif

}







