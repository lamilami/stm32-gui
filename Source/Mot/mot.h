#ifndef __MOT_H
#define __MOT_H
#include"gui_app.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)

#define TEST_MODE_1		1 // 
//#define TEST_MODE_2   2 // CAP only count plus
#define FILTER_FREQ	   500
#define FILTER_BETWEEN  20
#define R_MO		   270
#define TIME_CLK_DIV   35
#define SYS_CLK_MHZ    72
//#define GET_SYS_CLK_MHZ (SYS_CLK_MHZ/(TIME_CLK_DIV+1))
#define GET_SYS_CLK_HZ 2000000
#define FULL_PWM       1000
#define BASE_SPEED     300
#define FULL_RUN_CIR    5// 综合参数 与 转轮半径，减速器半径，故有最大转速（圈/s)
#define CACU_BASE(R_MM) (2*3.14159*R_MM)
#define FULL_RUN_SPEED(R_MM) (((2*3.141592*R_MM)*FULL_RUN_CIR)/1000)
#define PWM_PER_SPEED(R_MM)  (FULL_PWM/FULL_RUN_SPEED(R_MM))
#define GET_SECOND(SYS_FREQ,DT)  (DT/(SYS_FREQ*1000000))														   
#define CURRENT(ADC_DATA)  ((R_MO*ADC_DATA*825)>>10) //#define CURRENT(ADC_DATA,R_mO)  R_mO*ADC_DATA*3300/4096

#define GET_TIME_US(SPEED,R_MM)  ((CACU_BASE(R_MM)*1000)/SPEED)
#define TIM4_BASE_222_US   222

#define LIMIT_PWM_ACC     1000


#define PASS_LIMIT(Ve)  (1.15*Ve)

#define PASS_MAX(Ve)   (1.15*Ve+ 0.25/Ve)


#ifndef SIM_WIN
#define SW1  GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)
#define SW2  GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6)
#define SW3  GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
#else 
#define SW1
#define SW2
#define SW3
#endif

#define HAND_CONTROL SW3

#define DIV_TIMS_US    0.5

#define BUF_SIZE      512


typedef struct Mot_t_Cal
{
  char cal_flag;
  float max_speed_m_per_s;
  float k;//rate_speed_current;
  float R_r;
  float k_R_r; // 从内径速度转换到外径速度
  float r_R;

  float encode_mm_per_plus;

  unsigned int div_times;
  unsigned int counter;
  float k_sin;

}TMot_t_Cal;


typedef struct Get_data
{
  EMotWorkState e_work_state;
  float  current;
  float  frequence;
  float acce;
  float speed;
  float sw1_speed;
  float sw2_speed;

  unsigned int times;// 次数
  unsigned long time_us;//
  float bt_time_s;

}S_GetData;

typedef struct{
  
	 unsigned int in_loc;
	 unsigned int out_loc;
	 unsigned int in_data_size;
	 float speed_buf[BUF_SIZE];

}TSpeed_buf;




extern TMot_t_Cal 	mot_t_cal;

extern TSpeed_buf tspeed_buf;

void motor_int(void);

void motor_dir(int dir);

void motor_speed( int pwm_speed);

void TIM2_Interrupt(void);

void fresh_data(void);


void start_test_init(void);

void set_speed(float speed);


void judge_result(void);

int one_stop(void);

void adjust_pwm_speed(void);

float quadratic_equation(float a,float b,float c);

char intit_sw_state(void);

void test_stop(void);

void err_back(EWorkState work_state);

void mot_t_get_speed_line(TMot_t_Cal  mot_pars);
float* sin_1_4(int size);



#if 0
unsigned int  test_get_current(void);
#endif


#endif

