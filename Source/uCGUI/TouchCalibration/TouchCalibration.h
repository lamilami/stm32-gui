

#include "GUI.h"
#include "LCD_ConfDefaults.h"      /* valid LCD configuration */

#include "BUTTON.h"
#include "EDIT.h"

#ifndef WIN_SIM
#include "touch.h"
#endif

#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))

typedef struct{
	   int a;
	   int b;
	   int c;

}TFact;


static int _Log2Phys(int l, I32 l0, I32 l1, I32 p0, I32 p1);
static void _Calibrate(int Coord, int Log0, int Log1, int Phys0, int Phys1, int *p0, int *p1);
void _ExecCalibration(void);
int get_calibration(void);
int run_cal(void);

void myAD2XY( int *adx , int *ady );
void GUI_myTOUCH_Calibrate(int *Logx, int *Logy, int *xPhys, int *yPhys);
void Calibration(void);




