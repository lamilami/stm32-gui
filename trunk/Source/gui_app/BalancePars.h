#ifndef __BALANCE_H
#define __BALANCE_H

/*********************************************************************
*
*       static data
*
**********************************************************************
*/
#define GUI_ID_EDIT_CUS   GUI_ID_USER+1

#define GUI_ID_EDIT_PRO   GUI_ID_USER+2
#define GUI_ID_EDIT_RES1   GUI_ID_USER+3

#define GUI_ID_EDIT_TOTAL_TIMES   GUI_ID_USER+4
#define GUI_ID_EDIT_ELE_ID_B   GUI_ID_USER+5

#define GUI_ID_EDIT_FIRST   GUI_ID_USER+6
#define GUI_ID_EDIT_SECOND   GUI_ID_USER+7
#define GUI_ID_EDIT_THIRD   GUI_ID_USER+8
#define GUI_ID_EDIT_FOURTH   GUI_ID_USER+9
#define GUI_ID_EDIT_FIFTH   GUI_ID_USER+10
#define GUI_ID_EDIT_SIXTH   GUI_ID_USER+11
#define GUI_ID_EDIT_SEVENTH   GUI_ID_USER+12
#define GUI_ID_EDIT_EIGHTTH   GUI_ID_USER+13

#define GUI_ID_EDIT_BASE_VALUE   GUI_ID_USER+14

#define GUI_ID_RADIO_TEST_MODE   GUI_ID_USER+15
#define GUI_ID_RETURN_BUTTON   GUI_ID_USER+16

#define  GUI_ID_TEXT_CUS	   GUI_ID_USER+17
#define  GUI_ID_TEXT_ELE_ID	   GUI_ID_USER+18
#define  GUI_ID_TEXT_PRO	   GUI_ID_USER+19

#define  GUI_ID_TEXT_RES1	   GUI_ID_USER+20
#define  GUI_ID_TEXT_TIME	   GUI_ID_USER+21
#define  GUI_ID_TEXT_CUS_IF	   GUI_ID_USER+22
#define  GUI_ID_TEXT_TEXT_MT	   GUI_ID_USER+23
#define  GUI_ID_TEXT_STAND	   GUI_ID_USER+24
#define  GUI_ID_TEXT_BASE_VALUE	   GUI_ID_USER+25
#define  GUI_ID_TEXT_TIME_NUM	   GUI_ID_USER+26
#define  GUI_ID_TEXT_GE	   GUI_ID_USER+27


typedef enum
{
	AUTO = 0,
	CUS  = 1

}ETEST_MODE;


typedef struct
{
  TCustormer tcustormer;
  float base_value;// 额定载荷
  int test_mode ;// 测试方式 0 - auto 1 - cus
  char test_times; // 测试次数
  float first_value;
  float second_value;
  float third_value;
  float forth_value;
  float fifth_value;
  float sixth_value;
  float seventh_value;
  float eighth_value;
  char dir;

}TBalancePars;


typedef struct
{
   tim  ymdt;

   float get_value[30];
   float get_percent;
   int times;
   float res1;
   float res2;
   

}TBalanceResult;


extern TBalancePars tbalance_pars ;
extern TBalanceResult tbalance_result;



#endif