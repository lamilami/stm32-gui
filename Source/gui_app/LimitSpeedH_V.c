/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

#include "gui_app.h"
#include "LimitSpeedH_V.h"
#include "mot.h"

#define MAX_VALUE 680

//extern      TPars   pars;
//extern	    TRecord record;
//extern      S_GetData get_data;

int button_cr_state;
int disp_muit;
/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static GRAPH_DATA_Handle  _ahData[3]; /* Array of handles for the GRAPH_DATA objects */
unsigned int exist[3];
static GRAPH_SCALE_Handle _hScaleV;   /* Handle of vertical scale */
static GRAPH_SCALE_Handle _hScaleH;   /* Handle of horizontal scale */

static I16 _aValue[3];

static GUI_COLOR _aColor[] = {GUI_BLUE,GUI_RED, GUI_GREEN,GUI_CYAN};
//,GUI_MAGENTA,GUI_YELLOW,GUI_LIGHTBLUE,GUI_LIGHTGREEN,GUI_LIGHTRED,
//	GUI_LIGHTRED,GUI_DARKCYAN,GUI_DARKMAGENTA,GUI_DARKYELLOW,GUI_WHITE,GUI_LIGHTGRAY,GUI_GRAY,GUI_DARKGRAY,GUI_BLUE,GUI_RED, GUI_GREEN}; /* Array of colors for the GRAPH_DATA objects */


static int _Stop;
#if 0
void add_value_graph(int loc , signed short data )
{
	if(disp_muit)
		GRAPH_DATA_YT_AddValue(_ahData[loc], data);
	else
		GRAPH_DATA_YT_AddValue(_ahData[0], data);
}



//EventsFunctionList
void OnxxxClicked_DELET(WM_MESSAGE * pMsg)
{
#if 0
	int row;
	if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
		{
	row = LISTVIEW_GetSel(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW0));
	LISTVIEW_DeleteRow(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW0),row);
	record.test_times--;
	record.v1[row] = 0;
	record.v2[row] = 0;
	
	 }
	#endif
}
void OnxxxClicked_DATA(WM_MESSAGE * pMsg)
{
}
void OnCheckBoxClicked_MUlT(WM_MESSAGE * pMsg)
{
   
	disp_muit = CHECKBOX_GetState(WM_GetDialogItem(pMsg->hWin,GUI_ID_CHECKBOX_MULT));
	
}
void OnxxxClicked_Start(WM_MESSAGE * pMsg)
{
#if 0
	  int lenth;
	  char buf[5];
	
	  GUI_ConstString _ListBox[] = {"1", "0", "0", "Start", "","R"};

	  if(!disp_muit && !exist[0])// 如果单曲线显示
	  	{
	  	_ahData[0] = GRAPH_DATA_YT_Create(_aColor[0], 500, 0, 0);//YT
	 
     	GRAPH_AttachData(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), _ahData[0]);//attaches  data object to graph object
     	exist[0] = 1;
		GRAPH_SetUserDraw(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), _UserDraw); /* Enable user draw */

			
    GRAPH_SetGridVis(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), 6);
	GRAPH_SetVSizeY(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), 1000);
    _hScaleV = GRAPH_SCALE_Create( 35, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 10);
    GRAPH_SCALE_SetTextColor(_hScaleV, GUI_YELLOW);
    GRAPH_AttachScale(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), _hScaleV);
	  }

	  if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	  	{
	
	  lenth = LISTVIEW_GetNumRows(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW0));
	  
	  if(lenth < 20)
	  {
	  record.test_times++;
	  
	  sprintf(buf,"%d",lenth+1);
	  _ListBox[0]= buf;
	  LISTVIEW_InsertRow(WM_GetDialogItem(pMsg->hWin,GUI_ID_LISTVIEW0),0,_ListBox);
	
	  if(disp_muit)
	  	{
	  	if(!exist[lenth])
	  		{
		_ahData[lenth] = GRAPH_DATA_YT_Create(_aColor[lenth], 500, 0, 0);//YT
	 
     	GRAPH_AttachData(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), _ahData[lenth]);//attaches  data object to graph object
     	exist[lenth] = 1;
		if(lenth == 0)
			{
		GRAPH_SetUserDraw(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), _UserDraw); /* Enable user draw */	
    	GRAPH_SetGridVis(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), 6);
		GRAPH_SetVSizeY(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), 1000);
    	_hScaleV = GRAPH_SCALE_Create( 35, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 10);
    	GRAPH_SCALE_SetTextColor(_hScaleV, GUI_YELLOW);
    	GRAPH_AttachScale(WM_GetDialogItem(pMsg->hWin, GUI_ID_GRAPH0), _hScaleV);
		}
	    }
	  }
	
	  BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_CR),"正转");
	  button_cr_state = 1;

	  pars.dir = 1;
	  
	  start_test_init();
	  	}
	}

	#endif
}

void OnListViewScrollChanged(WM_MESSAGE * pMsg)
{
}

void OnListViewSelChanged(WM_MESSAGE * pMsg)
{


}
void OnxxxClicked_STOP(WM_MESSAGE * pMsg)
{
	motor_dir(0);
}

void OnxxxClicked_CR(WM_MESSAGE * pMsg)
{
#if 0
	if((get_data.e_work_state != START_TEST)&&(get_data.e_work_state != GET_V1))
	 {

    if(button_cr_state)
	{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_CR),"反转");
	button_cr_state = 0;
	}else{
	BUTTON_SetText(WM_GetDialogItem(pMsg->hWin,GUI_ID_BUTTON_CR),"正转");
	button_cr_state = 1;	
	}
	}
#endif	 
}

void OnxxxClicked_SAVE(WM_MESSAGE * pMsg)
{
}
void OnxxxClicked_PRINT(WM_MESSAGE * pMsg)
{
}
void OnButtonClicked_PARM_SET(WM_MESSAGE * pMsg)
{
}

#endif


//EventsFunctionList
void OnButtonClicked_Home_Graph(WM_MESSAGE * pMsg);
void OnButtonClicked_FullScreen_speed(WM_MESSAGE * pMsg);
//EndofEventsFunctionList


/*********************************************************************
*
*       GRAPH_AttachData
*/
#if 0
void GRAPH_DetachData(GRAPH_Handle hObj, GRAPH_DATA_Handle hData) {
  if (hObj) {
    GRAPH_OBJ * pObj;
    GRAPH_DATA_OBJ * pDataObj;
    WM_LOCK();
  //  pObj = GRAPH_H2P(hObj);
  //  pDataObj = (GRAPH_DATA_OBJ *)GUI_ALLOC_h2p(hDataObj);
  //  pDataObj->PaintObj.hGraph = hObj;

	pDataYtObj = (GRAPH_DATA_YT_OBJ *)GUI_ALLOC_h2p(hDataObj);
	if (pDataYtObj->hData) {
    GUI_ALLOC_Free(pDataYtObj->hData);

	GUI_ARRAY_Delete(&hObj->GraphArray);
   // GUI_ARRAY_AddItem(&pObj->GraphArray, &hData, sizeof(GRAPH_DATA_Handle));
    WM_InvalidateWindow(hObj);
    WM_UNLOCK();
  }
}
/*
GRAPH_DATA_YT_OBJ * pDataYtObj;
  pDataYtObj = (GRAPH_DATA_YT_OBJ *)GUI_ALLOC_h2p(hDataObj);
  if (pDataYtObj->hData) {
    GUI_ALLOC_Free(pDataYtObj->hData);
  }*/
#endif
/*********************************************************************
*
*       static data
*
**********************************************************************
*/
#if 0
static const char * _lvTable_00[1] ={"01" };
static const char * _lvTable_01[1] ={"02" };
static const char * _lvTable_02[1] ={"03" };
static const char * _lvTable_03[1] ={"04" };
static const char * _lvTable_04[1] ={"05" };
static const char * _lvTable_05[1] ={"06" };
static const char * _lvTable_06[1] ={"07" };
static const char * _lvTable_07[1] ={"08" };
static const char * _lvTable_08[1] ={"09" };
static const char * _lvTable_09[1] ={"10" };
static const char * _lvTable_010[1] ={"11" };
static const char * _lvTable_011[1] ={"12" };
static const char * _lvTable_012[1] ={"13" };
static const char * _lvTable_013[1] ={"14" };
static const char * _lvTable_014[1] ={"15" };
static const char * _lvTable_015[1] ={"16" };
static const char * _lvTable_016[1] ={"17" };
static const char * _lvTable_017[1] ={"18" };
static const char * _lvTable_018[1] ={"19" };
static const char * _lvTable_019[1] ={"20" };
#endif

/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "LIMIT_SPEED_H",     0,                       0,  0,  800,480,0,0},
	{ GRAPH_CreateIndirect,     0,                   GUI_ID_GRAPH0    ,   5,  37, 370, 335,0 },
    { CHECKBOX_CreateIndirect,  "多曲线显示",             GUI_ID_CHECKBOX_MULT,           13, 10, 108,24, 0,0},
    { BUTTON_CreateIndirect,    "开始",                GUI_ID_BUTTON_START,          490,388,57, 25, 0,0},
    { BUTTON_CreateIndirect,    "停止",                GUI_ID_BUTTON_STOP,          490,420,57, 25, 0,0},
    { BUTTON_CreateIndirect,    "正转/反转",             GUI_ID_BUTTON_CR,          379,389,89, 57, 0,0},
    { BUTTON_CreateIndirect,    "删除",                GUI_ID_BUTTON_DELET,          559,388,57, 25, 0,0},
    { BUTTON_CreateIndirect,    "参数设置",              GUI_ID_BUTTON_PARM_SET,          697,388,83, 25, 0,0},
    { BUTTON_CreateIndirect,    "保存",                GUI_ID_BUTTON_SAVE,          628,388,57, 25, 0,0},
    { BUTTON_CreateIndirect,    "打印",                GUI_ID_BUTTON_PRINT,          628,420,57, 25, 0,0},
    { BUTTON_CreateIndirect,    "数据",                GUI_ID_BUTTON_DATA,          559,420,57, 25, 0,0},
    { BUTTON_CreateIndirect,    "主界面",               GUI_ID_BUTTON8,          697,420,83, 25, 0,0},
    { LISTVIEW_CreateIndirect,   NULL,               GUI_ID_LISTVIEW0,        379,37, 401,335,0,0},
    { PROGBAR_CreateIndirect,    NULL,               GUI_ID_PROGBAR0,         577,6,  100,16, 0,0},
    { TEXT_CreateIndirect,      "Data",              GUI_ID_TEXT0,            683,10, 29, 12, 0,0},
    { TEXT_CreateIndirect,      "Time",              GUI_ID_TEXT1,            718,10, 29, 12, 0,0},
    { SLIDER_CreateIndirect,     NULL,               GUI_ID_SLIDER0,          81, 396,90, 24, 0,0},
    { SLIDER_CreateIndirect,     NULL,               GUI_ID_SLIDER1,          81, 426,90, 23, 0,0},
    { TEXT_CreateIndirect,      "栅格间距X:",            GUI_ID_TEXT2,            -2, 397,88, 20, 0,0},
    { TEXT_CreateIndirect,      "栅格间距Y:",            GUI_ID_TEXT3,            -2, 433,88, 20, 0,0},
    { CHECKBOX_CreateIndirect,  "水平滚动条",             GUI_ID_CHECK1,           200,397,108,24, 0,0},
    { CHECKBOX_CreateIndirect,  "垂直滚动条",             GUI_ID_CHECK2,           200,433,108,24, 0,0},
	{ BUTTON_CreateIndirect,    "全屏",                GUI_ID_BUTTON9,          160,6,  54, 24, 0,0},
};






static void _UserDraw(WM_HWIN hWin, int Stage) {
  if (Stage == GRAPH_DRAW_LAST) {
    char acText[] = "speed";
    GUI_RECT Rect, RectInvalid;
    int FontSizeY;
    GUI_SetFont(&GUI_Font13_ASCII);
    FontSizeY = GUI_GetFontSizeY();
    WM_GetInsideRect(&Rect);
    WM_GetInvalidRect(hWin, &RectInvalid);
    Rect.x1 = Rect.x0 + FontSizeY;
    GUI_SetColor(GUI_YELLOW);
    GUI_DispStringInRectEx(acText, &Rect, GUI_TA_HCENTER, strlen(acText), GUI_ROTATE_CCW);
  }
}


static void _ForEach(WM_HWIN hWin, void * pData) {
  int Id, FullScreenMode;
  FullScreenMode = *(int *)pData;
  Id = WM_GetId(hWin);
  if ((Id == GUI_ID_GRAPH0) || (Id == GUI_ID_BUTTON9) || (Id == GUI_ID_VSCROLL) || (Id == GUI_ID_HSCROLL)) {
    return;
  }
  if (FullScreenMode) {
    WM_HideWindow(hWin);
  } else {
    WM_ShowWindow(hWin);
  }
}


static void _ToggleFullScreenMode(WM_HWIN hDlg) {
  static int FullScreenMode;
  static GUI_RECT Rect;
  static unsigned ScalePos;
  WM_HWIN hGraph, hButton;
  hGraph  = WM_GetDialogItem(hDlg, GUI_ID_GRAPH0);
  hButton = WM_GetDialogItem(hDlg, GUI_ID_BUTTON9);
  FullScreenMode ^= 1;
  if (FullScreenMode) {
    /* Enter the full screen mode */
    WM_HWIN hClient;
    GUI_RECT RectInside;
    hClient = WM_GetClientWindow(hDlg);
    BUTTON_SetText(hButton, "退出");
    //WM_MoveWindow(hButton, 0, 11);
	WM_MoveTo(hButton, 740, 10);
    FRAMEWIN_SetTitleVis(hDlg, 0);
    WM_GetInsideRectEx(hClient, &RectInside);
    WM_GetWindowRectEx(hGraph, &Rect);
    WM_ForEachDesc(hClient, _ForEach, &FullScreenMode); /* Hide all descendants */
    WM_SetWindowPos(hGraph, WM_GetWindowOrgX(hClient), WM_GetWindowOrgX(hClient), RectInside.x1, RectInside.y1);
    ScalePos = GRAPH_SCALE_SetPos(_hScaleH, RectInside.y1 -20);
  } else {
    /* Return to normal mode */
    BUTTON_SetText(hButton, "全屏");
    //WM_MoveWindow(hButton, 0, -11);

	WM_MoveTo(hButton, 160, 6);
    WM_ForEachDesc(WM_GetClientWindow(hDlg), _ForEach, &FullScreenMode); /* Show all descendants */
    WM_SetWindowPos(hGraph, Rect.x0, Rect.y0, Rect.x1 - Rect.x0 + 1, Rect.y1 - Rect.y0 + 1);
    FRAMEWIN_SetTitleVis(hDlg, 1);

    GRAPH_SCALE_SetPos(_hScaleH, ScalePos);
  }
}

/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void static PaintDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void static InitDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin= pMsg->hWin;
	WM_HWIN hDlg= pMsg->hWin;
	WM_HWIN hItem;
	int i;

    //
    //FRAMEWIN
    //
    FRAMEWIN_SetTextAlign(hWin,GUI_TA_VCENTER|GUI_TA_CENTER);
    //FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
   // FRAMEWIN_AddMaxButton(hWin, FRAMEWIN_BUTTON_RIGHT, 1);
   // FRAMEWIN_AddMinButton(hWin, FRAMEWIN_BUTTON_RIGHT, 2);
    //
    //GUI_ID_CHECK0
    //
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK0),"多曲线显示");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK0),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON1
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON2
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON0
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON3
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON3),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON7
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON7),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON5
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON5),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON6
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON6),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON4
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON4),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON8
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON8),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_LISTVIEW0
    //
   // LISTBOX_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),0,0xcfe8cc);
    //
    //GUI_ID_PROGBAR0
    //
    PROGBAR_SetValue(WM_GetDialogItem(hWin,GUI_ID_PROGBAR0),50);
    //
    //GUI_ID_SLIDER0
    //
    SLIDER_SetNumTicks(WM_GetDialogItem(hWin,GUI_ID_SLIDER0),5);
    //
    //GUI_ID_SLIDER1
    //
    SLIDER_SetNumTicks(WM_GetDialogItem(hWin,GUI_ID_SLIDER1),5);
    //
    //GUI_ID_TEXT2
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT2),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_TEXT3
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT3),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_CHECK1
    //
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK1),"水平滚动条");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK1),&GUI_FontHZ_SongTi_16);
    CHECKBOX_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_CHECK1),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_CHECK2
    //
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK2),"垂直滚动条");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK2),&GUI_FontHZ_SongTi_16);
    CHECKBOX_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_CHECK2),GUI_TA_VCENTER|GUI_TA_CENTER);
	//
    //GUI_ID_BUTTON9
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON9),&GUI_FontHZ_SongTi_16);//全屏
	 BUTTON_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON9),BUTTON_CI_UNPRESSED,0x0000ff);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_BUTTON9);
    WM_SetStayOnTop(hItem, 1);

	//gtaph图形
	hItem = WM_GetDialogItem(hWin, GUI_ID_GRAPH0);
    /* Add graphs */
    for (i = 0; i < GUI_COUNTOF(_aColor); i++) {
      _aValue[i] = rand() % 180;
      _ahData[i] = GRAPH_DATA_YT_Create(_aColor[i], 1000, 0, 0);
      GRAPH_AttachData(hItem, _ahData[i]);
    }
	/* Set graph attributes */
    GRAPH_SetGridDistY(hItem, 25);
    GRAPH_SetGridVis(hItem, 1);
//    GRAPH_SetGridFixedX(hItem, 1);
    GRAPH_SetUserDraw(hItem, _UserDraw);

#if 1
    /* Create and add vertical scale */
    _hScaleV = GRAPH_SCALE_Create( 35, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 50);
    GRAPH_SCALE_SetTextColor(_hScaleV, GUI_YELLOW);
    GRAPH_AttachScale(hItem, _hScaleV);
    /* Create and add horizontal scale */
    _hScaleH = GRAPH_SCALE_Create(310, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 50);
    GRAPH_SCALE_SetTextColor(_hScaleH, GUI_DARKGREEN);
    GRAPH_AttachScale(hItem, _hScaleH);
#endif
	 /* Init slider widgets */
    hItem = WM_GetDialogItem(hDlg, GUI_ID_SLIDER0);
    SLIDER_SetRange(hItem, 0, 10);
    SLIDER_SetValue(hItem, 5);
    SLIDER_SetNumTicks(hItem, 6);
    hItem = WM_GetDialogItem(hDlg, GUI_ID_SLIDER1);
    SLIDER_SetRange(hItem, 0, 20);
    SLIDER_SetValue(hItem, 5);
    SLIDER_SetNumTicks(hItem, 6);


	//ListVeiw列表
	//
    //GUI_ID_LISTVIEW0
    //
    //LISTBOX_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),0,0xcfe8cc);
	LISTVIEW_SetFont(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),&GUI_FontHZ_SongTi_16);
//    LISTVIEW_SetAutoScrollH(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),1);
    LISTVIEW_SetAutoScrollV(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),1);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),100,"Order",GUI_TA_VCENTER|GUI_TA_CENTER);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),100,"Time",GUI_TA_VCENTER|GUI_TA_CENTER);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),100,"V1(m/s)",GUI_TA_VCENTER|GUI_TA_CENTER);
    LISTVIEW_AddColumn(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),100,"V2(m/s)",GUI_TA_VCENTER|GUI_TA_CENTER);
#if 0
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_00);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_01);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_02);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_03);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_04);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_05);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_06);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_07);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_08);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_09);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_010);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_011);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_012);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_013);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_014);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_015);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_016);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_017);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_018);
    LISTVIEW_AddRow(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),_lvTable_019);
#endif
	LISTVIEW_SetGridVis(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),1);
	LISTVIEW_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),0,GUI_TA_VCENTER|GUI_TA_CENTER);
	LISTVIEW_SetTextColor(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0), 3,GUI_RED);
	//HEADER_SetTextColor(hHeader, GUI_BLUE);
#if 0
	{
		 HEADER_Handle hHeader;
		 hHeader = LISTVIEW_GetHeader(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0));
		 HEADER_SetTextColor(hHeader, GUI_BLUE);
		 HEADER_SetHeight(hHeader,20);
		 LISTVIEW_SetItemTextColor(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),1,2,LISTVIEW_CI_UNSEL,GUI_RED);
		 LISTVIEW_SetItemText(WM_GetDialogItem(hWin,GUI_ID_LISTVIEW0),2,8,"测试");
	}
#endif
}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
{
  //  int NCode, Id;
	int i, NCode, Id, Value;
	WM_HWIN hDlg, hItem;
    WM_HWIN hWin = pMsg->hWin;
	hDlg = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog(pMsg);
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;   
			switch (NCode) 
			{
			   case WM_NOTIFICATION_CLICKED:
				switch (Id) 
				{
					case GUI_ID_OK:
						if(NCode==WM_NOTIFICATION_RELEASED)
							GUI_EndDialog(hWin, 0);
						break;
					case GUI_ID_CANCEL:
						if(NCode==WM_NOTIFICATION_RELEASED)
							GUI_EndDialog(hWin, 0);
						break;
					case GUI_ID_BUTTON8:
						switch(NCode)
						{
							case WM_NOTIFICATION_CLICKED:
								OnButtonClicked_Home_Graph(pMsg);
                            break;
						}
						break;
					case GUI_ID_BUTTON9:
						_ToggleFullScreenMode(hDlg);
						break;



				   #if 0

					 case GUI_ID_BUTTON_PARM_SET:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonClicked_PARM_SET(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_PRINT:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_PRINT(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_SAVE:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_SAVE(pMsg);
                            break;
                    }
                    break;
            
                case GUI_ID_BUTTON_CR:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_CR(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_STOP:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_STOP(pMsg);
                            break;
                    }
                    break;
         
                    break;
                case GUI_ID_BUTTON_START:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_Start(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_CHECKBOX_MULT:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnCheckBoxClicked_MUlT(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_DATA:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_DATA(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON_DELET:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnxxxClicked_DELET(pMsg);
                            break;
                    }
                    break;
				 #endif
				    

				}
				break;

			case WM_NOTIFICATION_VALUE_CHANGED:
				switch (Id) 
				{
					case GUI_ID_SLIDER0:
						/* Set horizontal grid spacing */
						hItem = WM_GetDialogItem(hWin, GUI_ID_GRAPH0);
						Value = SLIDER_GetValue(pMsg->hWinSrc) * 10;
						GRAPH_SetGridDistX(hItem, Value);
						GRAPH_SCALE_SetTickDist(_hScaleH, Value);
						break;

					case GUI_ID_SLIDER1:
						/* Set vertical grid spacing */
						hItem = WM_GetDialogItem(hWin, GUI_ID_GRAPH0);
						Value = SLIDER_GetValue(pMsg->hWinSrc) * 10;
						GRAPH_SetGridDistY(hItem, Value);
						GRAPH_SCALE_SetTickDist(_hScaleV, Value);
						break;
					case GUI_ID_CHECK1:
						/* Toggle horizontal scroll bar */
						hItem = WM_GetDialogItem(hWin, GUI_ID_GRAPH0);
						if (CHECKBOX_IsChecked(WM_GetDialogItem(hDlg, GUI_ID_CHECK1))) {
						  GRAPH_SetVSizeX(hItem, 1000);
						} else {
						  GRAPH_SetVSizeX(hItem, 0);
						}
						break;
				   case GUI_ID_CHECK2:
						/* Toggle vertical scroll bar */
						hItem = WM_GetDialogItem(hDlg, GUI_ID_GRAPH0);
						if (CHECKBOX_IsChecked(WM_GetDialogItem(hDlg, GUI_ID_CHECK2))) {
						  GRAPH_SetVSizeY(hItem, 1000);
						} else {
						  GRAPH_SetVSizeY(hItem, 0);
						}
						break;
				}
				break;
			}
			break;
       default:
            WM_DefaultProc(pMsg);
    }
}

/*********************************************************************
*
*       MainTask
*
**********************************************************************
*/
void limit_speed(WM_MESSAGE *pMsg) 
{ 
	WM_HWIN hWin,hGraph = 0;
	current_interface = PORTABLE_LIMIT_SPEED;
	WM_DeleteWindow(pMsg->hWin);
	//WM_DeleteWindow(0);
    //GUI_Init();
    WM_SetDesktopColor(GUI_BLACK);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    //CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
    //DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
    //SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
    //SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    //HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
    //RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
    current_handle = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
}


void OnButtonClicked_Home_Graph(WM_MESSAGE * pMsg)
{   
	//GRAPH_DetachData()
	//GUI_ALLOC_Init();
	//GUI_Init();
	//if(pMsg)
	//GUI_EndDialog(pMsg->hWin, 1);//删除上一个窗口
	home(pMsg);
}

void OnButtonClicked_FullScreen_speed(WM_MESSAGE * pMsg)
{
}