#include"MMA8452Q.h"
#include"xyz_acc_para.h"
#include"rtc.h"
#include"gui_app.h"

#ifndef _XYZ_H
#define _XYZ_H

#define G			980			//9.8m/s2  980cm/s2
#define G_D_DIV		0.239258		// 2G - 2(13) G - 2(12)
#define GET_ACC(n)  (G_D_DIV*n)    

#define FFT_LENTH			1024

#define FIR_BLOCK_SIZE		 32
#define FIR_TAPS			 8

#define XYZ_SCALE_X_START    20
#define XYZ_SCALE_X_SIZE     600
#define XYZ_SCALE_X_END     (XYZ_SCALE_X_START+XYZ_SCALE_X_SIZE)

#define XYZ_SCALE_Y_START    23
#define XYZ_SCALE_Y_SIZE     352
#define XYZ_SCALE_Y_END     (SCALE_Y_START +SCALE_Y_SIZE)

#define XYZ_FFT_X_SIZE	685
#define YXZ_FFT_Y_SIZE  402 - XYZ_SCALE_Y_START

#define FFT_SCALE_Y_MAX	XYZ_SCALE_Y_SIZE
#define FFT_SCALE_X_MAX 256    // 800/2  1024点FFt,采样率800Hz,频率分辨率0.78125Hz(800HZ/1024),测量最大有效频率400Hz 
#define FFT_BASE_4				4

#define  SCALE_Z_ACC_SIZE     128
#define  SCALE_Z_SPEED_SIZE   128
#define  SCALE_XY_ACC_SIZE    128

//#define SCALE_Z_ACC_MIDDLE    (SCALE_Y_START+SCALE_Z_SPEED_SIZE+SCALE_Z_ACC_SIZE/2)

//#define SCALE_XY_ACC_MIDDLE   (SCALE_Y_START+SCALE_Z_SPEED_SIZE+SCALE_Z_ACC_SIZE +SCALE_XY_ACC_SIZE /2)

#define Y_SIZE_IN	   35  // + - 35

#define ZY_ACC_SCOPE    8   //8g

#define ZY_ACC_RATE     (Y_SIZE_IN/ZY_ACC_SCOPE)

#define X_SCOPE_MIN		1

#define X_SCOPE_MS		(X_SCOPE_MIN*60*1000)

#define X_TIME_RATE		(SCALE_X_SIZE/X_SCOPE_MS)

#define GET_DATA_RATE_HZ  800

#define TOTAL_DATA		(GET_DATA_RATE_HZ*X_SCOPE_MIN*60)

// 原则问题 有多少个点
#define PICK_RATE		(TOTAL_DATA/SCALE_X_SIZE)  // 归一化处理	

#define Z_ACC_START_X0	20

#define Z_ACC_START_Y0  65

#define TIME_BASE_STEP   15 //  时基移动一次，移动的像素数

#define MMA845X_XYZ_FILTER_BUF    1024

#define TIME_BASE_STEP   5 //   时基移动一次，移动的像素数



#define STOP_START_SPEED  150

#define STOP_START_SPEED_END  STOP_START_SPEED*GET_DATA_RATE_HZ

#define STOP_CONTINUE_TIME_S  2

#define STOP_GET_TIMES     STOP_CONTINUE_TIME_S*GET_DATA_RATE_HZ


typedef enum{
ONE_AXLE,
TOW_AXLE

}EGetDataMode;


 typedef enum{

	 STOP = 0,
	 START
	 
 }XYZ_ACC_SAMPLE_STATUS;


typedef struct
{
	unsigned int acc_nums_of_one_pixel;           //多少个加速度的采样点对应一个lcd的像素
	unsigned int acc_sample_seconds;                   //加速度的采样时间
	short        Z_acc_x_pos;// = SCALE_X_START;
	short        Z_acc_y_pos;// = SCALE_Z_ACC_MIDDLE;
	XYZ_ACC_SAMPLE_STATUS    sample_status;

}Dispaly_Acc_struct;


typedef enum
{
	CHOICE_A =0,
	CHOICE_B

}TIME_BASE;

 typedef struct 
{
	int	A_pos;
	int B_pos;
	TIME_BASE choice_ab;
	unsigned short A_color_value[480];	
	unsigned short B_color_value[480];	
}TimeBase;


typedef  struct 
{
	unsigned int got_filter_acc_num;
	unsigned int used_filter_acc_num;
	signed short filter_acc_buf[MMA845X_XYZ_FILTER_BUF];
	
}TMMA845xFilterResult;

typedef enum
{
X = 0,
Y = 1,
Z = 2

}EXYZ;


// 加速度 保存成默认格式
// 速度   Q8格式 (乘除2(8))
 typedef struct{
   signed short za_max;
   signed short za_ave;
   signed short tza_ms; // z 轴加速时间 用浮点方便 统一读取
   signed short zd_mix; // z 轴最大减速度
   signed short zd_ave; // z 轴平均减速度
   signed short tzd_ms; // z 轴减速时间
   signed short za_abs; // z 轴最大绝对加速度
   signed short xa_abs; // x 轴绝对加速度
   signed short ya_abs;
   signed short balance_speed;
   signed short res1;	// 保留
   signed short res2;
   signed short res3;

   signed short za_ave_base;
   signed short xa_ave_base;
   signed short ya_ave_base;
   unsigned int ave_times_ms;

 }TXYZ_Result;


typedef struct
{
	TXYZ_Cus  xyz_customer;
	TXYZ_Pars xyz_parameter;
	TXYZ_Result    xyz_result;  
	tim            xyz_tim; 
	unsigned int   fragment_start;
}T_XYZ_FILE_struct;





extern 	 T_XYZ_FILE_struct xyz_file;

extern	 TimeBase  time_base;

void draw_scale_y(int x0, int y0,int y1);
void time_base_inital(void);

void xyz_fir(void);
void xyz_acc_to_graph(void);

//void xyz_value_dir_to_graph(MMA845X_struct acc);

void fir_init(int get_id);

//data 数据指针, loc1 loc2 位置1,2, size 大小,mode 模式
void get_data_from_sd(signed short* data ,unsigned int loc1,unsigned int loc2, unsigned int size,EGetDataMode mode);
void draw_fft_scale(void);
void view_fft(signed short* fft_buf);
void charge_button_fft_fun(void);
void xyz_sys_init(void);
void disp_titles(void);
void disp_caculate(void);

int xyz_file_init(int status);
int xyz_head_save(void);
int xyz_file_data_save(unsigned char *buf, unsigned int data_size);
void xyz_file_close(void);
void disp_mode(void);
int save_xyz(void);

void xyz_file_save_end(void);

void draw_cm_s2(int z_judge_cm_s2,int xy_judge_cm_s2);

extern XYZ_ACC_SAMPLE_STATUS    sample_status;
extern Dispaly_Acc_struct   tdisp_acc_struct;

#endif