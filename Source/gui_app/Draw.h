#ifndef  _DRAW_H
#define  _DRAW_H

#define SCALE_PIXEL      40

#define SCALE_Y_START    23
#define SCALE_Y_SIZE     128*2
#define SCALE_Y_END     (SCALE_Y_START +SCALE_Y_SIZE)

#define SCALE_X_START    20
#define SCALE_X_SIZE     600
#define SCALE_X_END      (SCALE_X_START+SCALE_X_SIZE)

#define SCALE_Z_ACC_MIDDLE    (SCALE_Y_START+SCALE_Z_ACC_SIZE/2)

#define SCALE_X_ACC_MIDDLE	  (SCALE_Y_START+SCALE_Z_SPEED_SIZE+SCALE_Z_ACC_SIZE/2)

#define SCALE_Y_ACC_MIDDLE	  (SCALE_Y_START+SCALE_Z_SPEED_SIZE+SCALE_Z_ACC_SIZE/2)
//(SCALE_Y_START+SCALE_Z_SPEED_SIZE+SCALE_Z_ACC_SIZE +SCALE_XY_ACC_SIZE /2)

#define SCALE_PIXEL    40

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

#define PIX_PER_DIV		5

#define XYC_OFF_SET     70





typedef struct{
int x;
int y;
}TPoint;

typedef struct{
TPoint start_point;
TPoint end_point;
}TSEPoint;

//
//disp_kind 0 移动画线 1压缩画线
//
//p0  --- scale disp start point 
//
//p_rec_lu 	 --- left up point
//p_rec_rd	 --- right down point

typedef struct{

unsigned int* buf;
unsigned int buf_size;
unsigned int data_size;
char disp_kind;

TPoint p0;

TPoint px;

TPoint p_rec_lu;
TPoint p_rec_rd;

unsigned int draw_color;

}TDraw;

//
// disp_text_p0	--
// disp_text_p1	--
//
typedef struct{
	
	unsigned  int x_pix_size;
	unsigned  int y_pix_size;
	
	float x_data_max;
	float y_data_max;

	TPoint disp_text_p0;
	TPoint disp_text_p1;

	char* unit_x;
	char* unit_y;
	
}TScale;


typedef enum{
	ZIP_BEFORE = 0,
	MOVE_HALF =1,
}EZip;

void Draw(WM_MESSAGE * pMsg);
void eMainTask(void);


void draw_scale(TSEPoint sepoint,int color,unsigned int off_set);

void zip_data(int* in_data, int* out_data,int in_size,int out_size);

void get_za_data(short *data, unsigned int lenth);

void draw_open(TDraw* draw);
void draw(TDraw* draw);
void draw_close(TDraw* draw);

void draw_exp(TDraw* draw);
void draw_clear(TDraw* draw);

unsigned int data_zip(int* data,unsigned int in_size,int out_size,EZip ezip);

void draw_line_at(TPoint ps,TPoint pe,unsigned char line_style);

void get_loc(int *y,int scale_mid,float CM_S,char zero_up_down);


#endif
