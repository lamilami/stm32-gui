/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUIDEMO_Touch
Purpose     : Touch demo
---------------------------END-OF-HEADER------------------------------
*/

#include"TouchCalibration.h"

#define CAL_READY	0xE1E1

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
int admy;
int admx;
int admk[10];
TFact Factors[10][10];


static int _Log2Phys(int l, I32 l0, I32 l1, I32 p0, I32 p1) {
  return p0 + ((p1 - p0) * (l - l0)) / (l1 - l0);
}

static void _Calibrate(int Coord, int Log0, int Log1, int Phys0, int Phys1, int *p0, int *p1) {
  int l0 = 0;
  int l1 = (Coord == GUI_COORD_X) ? LCD_XSIZE - 1 : LCD_YSIZE - 1;
  *p0 = _Log2Phys(l0, Log0, Log1, Phys0, Phys1);
  *p1 = _Log2Phys(l1, Log0, Log1, Phys0, Phys1);
}

/*********************************************************************
*
*       _ExecCalibration
*
**********************************************************************
*/

void _ExecCalibration(void) {
  int x,y;
  uint16_t data[6];
  uint16_t get_data[6];
  int ax_Phys[2],ay_Phys[2];
/* calculate log. Positions */
  int ax[2] = { 15, LCD_XSIZE -1-15};
//  const int ay[2] = { 15, LCD_YSIZE-1-15};
  int ay[2] = { LCD_YSIZE-1-15, 15};
  GUI_TOUCH_SetDefaultCalibration();
/* _Calibrate upper left */
  GUI_SetBkColor(GUI_RED);  
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);  GUI_FillCircle(ax[0], ay[0], 10);
  GUI_SetColor(GUI_RED);    GUI_FillCircle(ax[0], ay[0], 5);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringAt("Press here", ax[0]+20, ay[0]);
  do {

#if 0
    GUI_PID_STATE State;
    GUI_TOUCH_GetState(&State);
	 if (State.Pressed) {
#endif

#if 1
  x = TPReadX();
  y = TPReadY();
  if ((x>=3700)&&(y>=3400)&&(x<3800)&&(y<3600)) {

#endif
      ax_Phys[0] = GUI_TOUCH_GetxPhys();
      ay_Phys[0] = GUI_TOUCH_GetyPhys();
      break;
    }
    GUI_Delay (3000);
  } while (1);
/* Tell user to release */
  GUI_Clear();
  GUI_DispStringAt("OK", ax[0]+20, ay[0]);
  do {
    GUI_PID_STATE State;
    GUI_TOUCH_GetState(&State);
    if (State.Pressed == 0) {
      break;
    }
    GUI_Delay (100);
  } while (1);
/* _Calibrate lower right */
  GUI_SetBkColor(GUI_RED);  
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);  GUI_FillCircle(ax[1], ay[1], 10);
  GUI_SetColor(GUI_RED);    GUI_FillCircle(ax[1], ay[1], 5);
  GUI_SetColor(GUI_WHITE);
  GUI_SetTextAlign(GUI_TA_RIGHT);
  GUI_DispStringAt("Press here", ax[1]-20, ay[1]);
  do {

#if 1
  x = TPReadX();
  y = TPReadY();
  if ((y>450)&&(y<620)&&(x>350)&&(x<450)) {
#endif

#if 0
	GUI_PID_STATE State;
  	GUI_TOUCH_GetState(&State);
	if (State.Pressed) {
#endif

      ax_Phys[1] = GUI_TOUCH_GetxPhys();
      ay_Phys[1] = GUI_TOUCH_GetyPhys();
      break;
    }
    GUI_Delay (3000);
  } while (1);
  GUI_TOUCH_Calibrate(GUI_COORD_X, ax[0], ax[1], ax_Phys[0], ax_Phys[1]);
  GUI_TOUCH_Calibrate(GUI_COORD_Y, ay[0], ay[1], ay_Phys[0], ay_Phys[1]);
  { /* calculate and display values for configuration file */
    int x0, x1;
    int y0, y1;
    GUI_Clear();
    _Calibrate(GUI_COORD_X, ax[0], ax[1], ax_Phys[0], ax_Phys[1], &x0, &x1);
    _Calibrate(GUI_COORD_Y, ay[0], ay[1], ay_Phys[0], ay_Phys[1], &y0, &y1);
    GUI_DispStringAt("x0: ", 0, 0); GUI_DispDec(x0, 4); GUI_DispNextLine();
    GUI_DispString  ("x1: ");       GUI_DispDec(x1, 4); GUI_DispNextLine();
    GUI_DispString  ("y0: ");       GUI_DispDec(y0, 4); GUI_DispNextLine();
    GUI_DispString  ("y1: ");       GUI_DispDec(y1, 4); GUI_DispNextLine();
    GUI_DispString  ("Please touch display to continue...");
    GUI_Delay(1000);

	data[0]=  CAL_READY;
	data[1]= ax_Phys[0];
	data[2]= ay_Phys[0];
	data[3]= ax_Phys[1];
	data[4]= ay_Phys[1];

	#if 1
	save_calibrate_to_flash(data);
	get_calibrate_data(get_data);

	GUI_DispStringAt("x0: ", 100, 0); GUI_DispDec(get_data[1], 4); GUI_DispNextLine();
    GUI_DispString  ("x1: ");       GUI_DispDec(get_data[2], 4); GUI_DispNextLine();
    GUI_DispString  ("y0: ");       GUI_DispDec(get_data[3], 4); GUI_DispNextLine();
    GUI_DispString  ("y1: ");       GUI_DispDec(get_data[4], 4); GUI_DispNextLine();
	GUI_DispString  ("state: ");       GUI_DispDec(get_data[0], 4); GUI_DispNextLine();
	#endif

    do {
      GUI_PID_STATE State;
      GUI_TOUCH_GetState(&State);
      if (State.Pressed)
      break;
      GUI_Delay (10);
    } while (1);
  }
}



int run_cal(void)
{
  if(get_calibrate_state()== CAL_READY)
  {
  	get_calibration();
  }else{
	#if 1
  	 _ExecCalibration();
	#endif	

	#if 0
	Calibration();
	#endif
  }
}

int get_calibration(void)
{
  uint16_t cal_data[5];
  int ax_Phys[2],ay_Phys[2];
  int ax[2] = { 15, LCD_XSIZE -1-15};
  int ay[2] = { LCD_YSIZE-1-15, 15};

  get_calibrate_data(cal_data);

  ax_Phys[0] = cal_data[1];
  ay_Phys[0] = cal_data[2];
  
  ax_Phys[1] = cal_data[3];
  ay_Phys[1] = cal_data[4];
  
  GUI_TOUCH_Calibrate(GUI_COORD_X, ax[0], ax[1], ax_Phys[0], ax_Phys[1]);
  GUI_TOUCH_Calibrate(GUI_COORD_Y, ay[0], ay[1], ay_Phys[0], ay_Phys[1]);
}


#if 0			

void myAD2XY( int *adx , int *ady ){
 float f_dat;
 int dat1;

 f_dat = (float)(*ady - admy)/(float)(*adx - admx);
 if(f_dat>0){
  if( *adx>admx && admk[2] >=f_dat) dat1 = 1;
  else if( *adx>admx && admk[2] < f_dat ) dat1 =2;//2
  else if( *adx<admx && admk[0] >=f_dat ) dat1 =0;
  else if( *adx<admx && admk[0] < f_dat ) dat1 =3;//0
  else{ dat1 =0; }//*adx =0;*ady =0; }
 }else{
  if( *adx>admx && admk[1] >=f_dat) dat1 = 0;
  else if( *adx>admx && admk[1] < f_dat ) dat1 =1;//1
  else if( *adx<admx && admk[3] >=f_dat ) dat1 =3;
  else if( *adx<admx && admk[3] < f_dat ) dat1 =2;//3
  else{ dat1 =0; }//*adx =0;*ady =0; }
 }
 *adx = (int)(Factors[dat1][0].a*(*adx)+Factors[dat1][0].b*(*ady)+Factors[dat1][0].c); 
 *ady = (int)(Factors[dat1][1].a*(*adx)+Factors[dat1][1].b*(*ady)+Factors[dat1][1].c);
}


void GUI_myTOUCH_Calibrate(int *Logx, int *Logy, int *xPhys, int *yPhys){

 int move , mnext;
 int dat1;
 int dat2;
 int dat3;
 int f_dat;

 admx = xPhys[4];
 admy = yPhys[4];
 
 for( move =0 ; move<4; move++ ){
  if( move == 3 ) mnext =0;
  else mnext = move +1;

  dat2 = yPhys[move] - yPhys[4];
  dat1 = xPhys[move] - xPhys[4];
  admk[move] = ((float)dat2/(float)dat1);
//  mk = admk[move] = (yPhys[move] - yPhys[4])/(xPhys[move] - xPhys[4]);
  
/*  dat = ((xPhys[move]-xPhys[4])*(yPhys[mnext]-yPhys[4]))-((xPhys[mnext]-xPhys[4])*(yPhys[move]-yPhys[4]));
 */ 
   dat1 =  xPhys[move]-xPhys[4];
  dat2 = yPhys[mnext]-yPhys[4];
  dat1 = dat1*dat2;
  dat3 = xPhys[mnext]-xPhys[4];
  dat2 = yPhys[move]-yPhys[4];
  dat3 = dat3*dat2;
  f_dat = (float)dat1-(float)dat3;
  
/* mk = Factors[move][0].a  = /
   (((Logx[move]-Logx[4])*(yPhys[mnext]-yPhys[4]))-((Logx[mnext]-Logx[4])*(yPhys[move]-yPhys[4])))/dat; 
*/  dat1 = Logx[move]-Logx[4];
  dat2 = yPhys[mnext]-yPhys[4];
  dat1 = dat1*dat2;
  dat3 = Logx[mnext]-Logx[4];
  dat2 = yPhys[move]-yPhys[4];
  dat3 = dat2*dat3;
  dat1 = dat1-dat3;
  Factors[move][0].a = (float)dat1/f_dat;
 
/* mk = Factors[move][0].b = /
   ((Logx[mnext]-Logx[4])*(xPhys[move]-xPhys[4])-(Logx[move]-Logx[4])*(xPhys[mnext]-xPhys[4]))/dat;
*/  dat1 = Logx[mnext]-Logx[4];
  dat2 = xPhys[move]-xPhys[4];
  dat1 = dat1*dat2;
  dat3 = Logx[move]-Logx[4];
  dat2 = xPhys[mnext]-xPhys[4];
  dat3 = dat2*dat3;
  dat1 = dat1-dat3;
  Factors[move][0].b = (float)dat1/f_dat;
 
/* mk = Factors[move][0].c = (Logx[move]*(xPhys[mnext]*yPhys[4]-xPhys[4]*yPhys[mnext])/
        +Logx[mnext]*(xPhys[move]*yPhys[4]-xPhys[4]*yPhys[move])/
        +Logx[4]*(xPhys[move]*yPhys[mnext]-xPhys[mnext]*yPhys[move]))/dat;
*/  dat1 = xPhys[mnext]*yPhys[4]-xPhys[4]*yPhys[mnext];
  dat1 = Logx[move]*dat1;
  dat2 = xPhys[move]*yPhys[4]-xPhys[4]*yPhys[move];
  dat2 = dat2*Logx[mnext];
  dat3 = xPhys[move]*yPhys[mnext]-xPhys[mnext]*yPhys[move];
  dat3 = dat3*Logx[4];
  dat1 = dat1-dat2+dat3;
  Factors[move][0].c = (float)dat1/f_dat;
 
/* mk = Factors[move][1].a  = /
   ((Logy[move]-Logy[4])*(yPhys[mnext]-yPhys[4])-(Logy[mnext]-Logy[4])*(yPhys[move]-yPhys[4]))/dat;
*/  dat1 = Logy[move]-Logy[4];
  dat2 = yPhys[mnext]-yPhys[4];
  dat1 = dat1*dat2;
  dat3 = Logy[mnext]-Logy[4];
  dat2 = yPhys[move]-yPhys[4];
  dat3 = dat2*dat3;
  dat1 = dat1-dat3;
  Factors[move][1].a = (float)dat1/f_dat;
 
/* mk = Factors[move][1].b = /
  ((xPhys[move]-xPhys[4])*(Logy[mnext]-Logy[4])-(xPhys[mnext]-xPhys[4])*(Logy[move]-Logy[4]))/dat;
*/  dat1 = xPhys[move]-xPhys[4];
  dat2 = Logy[mnext]-Logy[4];
  dat1 = dat1*dat2;
  dat3 = xPhys[mnext]-xPhys[4];
  dat2 = Logy[move]-Logy[4];
  dat3 = dat3*dat2;
  dat1 = dat1-dat3;
  Factors[move][1].b = (float)dat1/f_dat;
 
/* mk = Factors[move][1].c  = (Logy[move]*(xPhys[mnext]*yPhys[4]-xPhys[4]*yPhys[mnext])/
     +Logy[mnext]*(xPhys[move]*yPhys[4]-xPhys[4]*yPhys[move])/
     +Logy[4]*(xPhys[move]*yPhys[mnext]-xPhys[mnext]*yPhys[move]))/dat;
*/  dat1 = xPhys[mnext]*yPhys[4]-xPhys[4]*yPhys[mnext];
  dat1 = Logy[move]*dat1;
  dat2 = xPhys[move]*yPhys[4]-xPhys[4]*yPhys[move];
  dat2 = Logy[mnext]*dat2;
  dat3 = xPhys[move]*yPhys[mnext]-xPhys[mnext]*yPhys[move];
  dat3 = Logy[4]*dat3;
  dat1 = dat1-dat2+dat3;
  Factors[move][1].c = (float)dat1/f_dat;  
 
 }
}


void Calibration(void) 
{
  int ax_Phys[5],ay_Phys[5];
  int move;
/* calculate log. Positions */
  int ax[5] = { 50, LCD_XSIZE-50, LCD_XSIZE-50, 50, (LCD_XSIZE/2)-10};
  int ay[5] = { 50, 50, LCD_YSIZE-50, LCD_YSIZE-50, (LCD_YSIZE/2)-10};

//  GUI_TOUCH_SetDefaultCalibration();
/* _Calibrate upper left */
 for( move =0 ; move<5; move++){
  GUI_SetBkColor(GUI_RED);  
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_FillCircle(ax[move], ay[move], 10);
  GUI_SetColor(GUI_RED);    
  GUI_FillCircle(ax[move], ay[move], 5);
  GUI_SetColor(GUI_WHITE);

  do {
   GUI_PID_STATE State;
   GUI_TOUCH_GetState(&State);
   if (State.Pressed) {
   ax_Phys[move] = State.x;//GUI_TOUCH_GetxPhys();
   ay_Phys[move] = State.y;//GUI_TOUCH_GetyPhys();
   break;
   }
      GUI_Delay (100);
    } while (1); 
  GUI_Delay (4000);
/*  release */
  GUI_TOUCH_StoreState(-1,-1); 
 }

 	GUI_myTOUCH_Calibrate(ax,ay,ax_Phys,ay_Phys);
    GUI_Delay(500);
    GUI_DispStringAt  ("Please touch display to continue...",50,20);
    GUI_TOUCH_StoreState(-1,-1); 

    do {
      GUI_PID_STATE State;
      GUI_TOUCH_GetState(&State);
      if (State.Pressed)
        break;
      GUI_Delay (10);
    } while (1);
}

#endif 







