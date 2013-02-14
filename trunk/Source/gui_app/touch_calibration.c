/******************************************************************************

                  版权所有 (C), 2012-2022, 浙大精益

 ******************************************************************************
  文 件 名   : touch_calibration.c
  版 本 号   : 初稿
  作    者   : ganjinming
  生成日期   : 2012年9月10日
  最近修改   :
  功能描述   : 触摸屏校准模块
  函数列表   :
              _Calibrate
              _ExecCalibration
              _Log2Phys
  修改历史   :
  1.日    期   : 2012年9月10日
    作    者   : ganjinming
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
    #include "gui_app.h"
    #include "GUI.h"
    #include "LCD_ConfDefaults.h"      /* valid LCD configuration */
    #include "WM.h"
/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/


static int _Log2Phys(int l, I32 l0, I32 l1, I32 p0, I32 p1) 
{
    return p0 + ((p1 - p0) * (l - l0)) / (l1 - l0);
}

static void _Calibrate(int Coord, int Log0, int Log1, int Phys0, int Phys1, int *p0, int *p1) 
{
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

void ExecCalibration(WM_MESSAGE *pMsg) 
{
    int ax_Phys[2],ay_Phys[2];
    /* calculate log. Positions */
    int ax[2] = { 15, LCD_XSIZE -1-15};
    //  const int ay[2] = { 15, LCD_YSIZE-1-15};
    int ay[2] = { LCD_YSIZE-1-15, 15};
  //  WM_DeleteWindow(pMsg->hWin);
  	display_time_flag = 0;
    GUI_TOUCH_SetDefaultCalibration();
    /* _Calibrate upper left */
    GUI_Delay (100);
    GUI_SetBkColor(GUI_RED);  
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);  GUI_FillCircle(ax[0], ay[0], 10);
    GUI_SetColor(GUI_RED);    GUI_FillCircle(ax[0], ay[0], 5);
    GUI_SetColor(GUI_WHITE);
    
    GUI_DispStringAt("Press here", ax[0]+20, ay[0]);
    do 
    {
        GUI_PID_STATE State;
        GUI_TOUCH_GetState(&State);
        if (State.Pressed) 
        {
            ax_Phys[0] = GUI_TOUCH_GetxPhys();
            ay_Phys[0] = GUI_TOUCH_GetyPhys();
            break;
         }
         GUI_Delay (100);
    }while (1);
    /* Tell user to release */
    GUI_Clear();
    GUI_DispStringAt("OK", ax[0]+20, ay[0]);
    do 
    {
        GUI_PID_STATE State;
        GUI_TOUCH_GetState(&State);
        if (State.Pressed == 0) 
        {
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
    do 
    {
        GUI_PID_STATE State;
        GUI_TOUCH_GetState(&State);
        if (State.Pressed) 
        {
            ax_Phys[1] = GUI_TOUCH_GetxPhys();
            ay_Phys[1] = GUI_TOUCH_GetyPhys();
            break;
        }
        GUI_Delay (100);
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
        do 
        {
            GUI_PID_STATE State;
            GUI_TOUCH_GetState(&State);
            if (State.Pressed)
            {
                home((WM_MESSAGE *)0);
                break;
            }
            GUI_Delay (10);
        }while (1);
    }
}

