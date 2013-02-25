
#include"gui_app.h"

#include <stdlib.h> 
#include <stdio.h> 

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"
#include "DROPDOWN.h"

#include "BUTTON_Private.h"
#include "Draw.h"
#include "math.h"// 
#include "arm_math.h"
#include "MMA8452Q.h"

#define GUI_ID_PARS	 1



BUTTON_Handle hButton;
TScale *rem_tscale;

signed short Coeffs_25hz[]=
{20,66,170,255,255,170,66,20};
//{18,49,125,203,235,203,125,49,18};

void scale_set(TScale *tscale)
{
	char buf[8];
	float rate_x,rate_y;

	rem_tscale = tscale;
	rate_x = (tscale->x_data_max/tscale->x_pix_size)*PIX_PER_DIV;
	rate_y = (tscale->y_data_max/tscale->y_pix_size)*PIX_PER_DIV;
	
	GUI_DispStringAt(tscale->unit_x,tscale->disp_text_p0.x - XYC_OFF_SET,tscale->disp_text_p0.y);
	sprintf(buf,"%.3f",rate_x);
	GUI_DispStringAt(buf,tscale->disp_text_p0.x,tscale->disp_text_p0.y);
	
	GUI_DispStringAt(tscale->unit_y,tscale->disp_text_p1.x - XYC_OFF_SET,tscale->disp_text_p1.y);
	sprintf(buf,"%.3f",rate_y);
	GUI_DispStringAt(buf,tscale->disp_text_p1.x,tscale->disp_text_p1.y);
}



// text_scale = small_degree*text_scale
void draw_scale(TSEPoint sepoint,int color,unsigned int off_set)
{
	unsigned int dis,i,j,k,s_dis_p_p,x0,y0,x1,y1;
	unsigned int draw_dir;
	unsigned long total_ms;
	unsigned int rate;
	unsigned int mirr;
	
	x0 = sepoint.start_point.x;
	y0 = sepoint.start_point.y;

	x1 = sepoint.end_point.x;
	y1 = sepoint.end_point.y;

	draw_dir = (x1 == x0)?1:0;// 1 y_dir, 0 x_dir 
	
	if(draw_dir)
	{
		dis = (y0 - y1);
	}else{
		dis = x1 - x0;
	}
	s_dis_p_p = dis/5;
	
	GUI_SetColor(color);
	GUI_DrawLine(x0,y0,x1,y1);

	for(i=1;i < s_dis_p_p ;i++)
	{
		if((i >= 5)&&(i%5 == 0))
		{
		j=5;
			
		if(draw_dir)
			{
			mirr = y0-i*5;
			GUI_DispDecAt(i+off_set,x0-10,y0-i*5,3);
			
			}else{

			GUI_DispDecAt(i+off_set,x0+i*5,y0+10,3);
			}
			
		}else{
		
		j=0;
		
		}
		
	if(draw_dir){
	
	GUI_DrawLine(x0,y0-i*5, x1+5+j,y0-i*5);
	
		}else{

	GUI_DrawLine(x0+i*5,y0, x0+i*5,y1+5+j);
		}
	}
}


void view_int(WM_MESSAGE * pMsg)
{
	TSEPoint tsepoint;
	if(pMsg)
	{
		WM_DeleteWindow(pMsg->hWin);
	}

	WM_Paint(WM_GetDesktopWindow());
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	
	GUI_DispStringAt("worke_state", 0,0);
	GUI_DispStringAt("battery", 80,0);
	
	hButton = BUTTON_Create(720, 0, 80, 25, GUI_ID_PARS, WM_CF_SHOW);
	BUTTON_SetText(hButton, "BasePars...");

	tsepoint.start_point.x = 20;
	tsepoint.start_point.y = 376;
	tsepoint.end_point.x = tsepoint.start_point.x + SCALE_X_SIZE;
	tsepoint.end_point.y = 376;
	draw_scale(tsepoint,0xffff,0);		//X

	tsepoint.start_point.x = 20;
	tsepoint.start_point.y = 376;
	tsepoint.end_point.x = 20;
	tsepoint.end_point.y = tsepoint.start_point.y - SCALE_Y_SIZE;
	draw_scale(tsepoint,0xffff,0);		//Y

	GUI_SetColor(GUI_BLUE);
	GUI_DrawHLine(65,20,SCALE_X_SIZE);
}

void get_za_data(signed short *data, unsigned int lenth)
{  
	int i;
	long si;
	float freq;
	float fs=1024;//采样频率
	float pick;
    
	for(i=0;i<lenth;i++)
	{
	 pick = i/fs;
	 data[i] = 1024*sin(pick*2*3.14159*80) + 5*sin(pick*2*3.14159*5)+2*sin(pick*2*3.14159*256);
	}	
}


// 由系统 定时时间长度 和采集时间 点数 来确定 比例
// 采集量与 pick_rate 成比例
void zip_data(int* in_data, int* out_data,int in_size,int pick_rate)
{
	int i,j,k;
	int first,mid;

	for(i=0,j=0;i<in_size;i=i+pick_rate,j++)
	{
		mid = in_data[i];
	   for(k=1;k<pick_rate;k++)
	   {
		  if(abs(mid) > abs(in_data[i+k]))
		  {
		  
		  }else{
			mid = in_data[i+k];
		  }
	   }
		out_data[j] = mid;//out_data[j] = mid%35;
	}
}

void draw_open(TDraw* draw)
{
	draw->buf = malloc(sizeof(unsigned int)*draw->buf_size);
}

void draw_close(TDraw* draw)
{
	free(draw->buf);
}

void draw(TDraw* draw)
{
	int i;
	GUI_COLOR color;
	color = GUI_GetColor();
    
	if(color != draw->draw_color)
	{
	 GUI_SetColor(draw->draw_color);
	}

	if(draw->data_size <= draw->buf_size)
	{
	//draw->buf[draw->data_size] = (draw->px.y - draw->p0.y);// 以p0.y为基准偏移的！！
	//GUI_DrawGraph(draw->buf, draw->data_size,draw->p0.x, draw->p0.y);
		draw->buf[draw->data_size] = (draw->px.y);
		if(draw->data_size >= 1)
		{
		GUI_DrawLine(draw->p0.x+draw->data_size-1,draw->buf[draw->data_size-1],draw->p0.x+draw->data_size,draw->px.y);
		}
		draw->data_size++;	

	}else{

#if 1
		draw_clear(draw);
		data_zip(draw->buf,draw->buf_size,draw->buf_size/2,MOVE_HALF);
		draw->data_size = draw->buf_size/2;
		
		for(i=1;i<draw->data_size;i++)
		{
		GUI_DrawLine(draw->p0.x+i-1,draw->buf[i-1],draw->p0.x+i,draw->buf[i]);
		}
#endif


#if 0
		GUI_ClearRect(draw->p_rec_lu.x,draw->p_rec_lu.y,draw->p_rec_rd.x,draw->p_rec_rd.y);
		draw->data_size = 0;
	}
	if(color != draw->draw_color)
	{
	 GUI_SetColor(color);
	}
#endif
}
}



void draw_clear(TDraw* draw)
{
	unsigned int i,color;
	unsigned int bk_color;

	color = GUI_GetColor();

	bk_color = GUI_GetBkColor();

	GUI_SetColor(bk_color);

	for(i=1;i<draw->data_size;i++)
	{
	GUI_DrawLine(draw->p0.x+i-1,draw->buf[i-1],draw->p0.x+i,draw->buf[i]);
	}
	GUI_SetColor(color);
}


unsigned int data_zip(int* data,unsigned int in_size,int out_size,EZip ezip)
{
	int rate,i;
	rate = in_size/out_size;
	
  if(ezip == ZIP_BEFORE)
  {
	for(i=0;i<in_size;i=i+rate)
	{
		data[i] = data[i+rate-1];
	}
  }
  
  if(ezip == MOVE_HALF)
  {
	for(i=0;i<in_size/2;i++)
	{
		data[i]=data[in_size/2+i];
	}
  }
	return i;
}




void draw_exp(TDraw* draw)
{
	int i;
	draw_clear(draw);
#if 1
		data_zip(draw->buf,draw->buf_size,draw->buf_size/2,0);
		draw->data_size = draw->buf_size/2;

		for(i=1;i<draw->data_size;i++)
		{
		GUI_DrawLine(draw->p0.x+i-1,draw->buf[i-1],draw->p0.x+i,draw->buf[i]);
		}
#endif

}


void Draw(WM_MESSAGE * pMsg)
{
	int i,j,k;
	signed short data_in[5000],data_out[5000];
	unsigned int lenth = 2048;
	unsigned int count,pick;
	short base_buf[63],in_buf[64];
	unsigned int disp_size;
	int get_return;
	q15_t  State[FIR_BLOCK_SIZE+FIR_TAPS-1];
	arm_fir_instance_q15 S;

	arm_cfft_radix4_instance_q15  fft_S;
	uint16_t fftLen;
	uint8_t ifftFlag;
	uint8_t bitReverseFlag;

	fftLen = 1024;
	ifftFlag = 0;
	bitReverseFlag = 1;
	lenth = 1024*3;
	disp_size =1024;

	for(j=0;j<64;j++)
		in_buf[j]=j;

	for(i=0;i<63;i++)
		base_buf[i]=i;
	
	put_head(in_buf, base_buf);
	
	view_int(pMsg);
	
	get_za_data(data_in,lenth);
	
	get_return = arm_fir_init_q15(&S,FIR_TAPS,&Coeffs_25hz[0],&State[0],FIR_BLOCK_SIZE);
	
	//arm_cfft_radix4_init_q15(&fft_S,fftLen,ifftFlag,bitReverseFlag);
	
	//arm_cfft_radix4_q15(&fft_S, data_in); 

	for(i=0;i<disp_size;i++)
	{
		data_out[i] = (data_out[i]/1024);
	}

	for(i=0;i< disp_size/FIR_BLOCK_SIZE;i++)
	{
		arm_fir_q15(&S,data_in+FIR_BLOCK_SIZE*i,data_out+FIR_BLOCK_SIZE*i,FIR_BLOCK_SIZE);
	}

	for(i=0;i<disp_size;i++)
	{
		data_in[i] = 0-(data_in[i]/35); //有个倍数关系 why? 衰减了29倍 1024/35
		data_out[i] = 0-data_out[i];
	}
	
	GUI_DrawGraph(data_in,512,Z_ACC_START_X0,Z_ACC_START_Y0);
	GUI_DrawGraph(data_out,512,Z_ACC_START_X0,Z_ACC_START_Y0+200);
	


	
#if 0
	if(pMsg)
	{
		WM_DeleteWindow(pMsg->hWin);
	}

	WM_Paint(WM_GetDesktopWindow());
	GUI_SetBkColor(GUI_RED);
	GUI_Clear();
    GUI_DispStringHCenterAt("WIDGET_SimpleButton - Sample", 160, 5);

	while(1)
	{

	GUI_Exec();
	}
#endif    
	
	
while(1)
 {
	if(GUI_GetKey() == GUI_ID_PARS)
	{
	 GUI_DispStringHCenterAt("Gui id  - Pars", 160, 5);
	}
	GUI_Exec();
 }

}



void draw_line_at(TPoint ps,TPoint pe,unsigned char line_style)
{
	unsigned char get_line_style;
	get_line_style = GUI_GetLineStyle();
	GUI_SetLineStyle(GUI_LS_DASH);

	GUI_DrawLine(ps.x,ps.y,pe.x,pe.y);
	GUI_SetLineStyle(get_line_style);
}


void get_loc(int *y,int scale_mid,float CM_S,char zero_up_down)
{
	float rate ,g,get,half_scale;
	g = 9.8*1000;
	half_scale = SCALE_Y_SIZE/4;
	rate = half_scale/g;
	get = rate*CM_S;
	if(zero_up_down > 0)
	{
		*y = scale_mid - get;
	}else{
		*y = scale_mid + get;
	}
}

