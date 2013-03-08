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
#include "KeyBoard_Win.h"
#include "mot.h"


TTPars ttpars;


//EndofEventsFunctionList
/*********************************************************************
*
*       static data
*
**********************************************************************
*/
#define GUI_ID_EDIT_TENCR   GUI_ID_USER+1
#define GUI_ID_EDIT_TENCN  GUI_ID_USER+2
#define GUI_ID_EDIT_TR   GUI_ID_USER+3
#define GUI_ID_EDIT_Tr   GUI_ID_USER+4
#define GUI_ID_EDIT_TRES3   GUI_ID_USER+5

#define GUI_ID_EDIT_TVE   GUI_ID_USER+6
#define GUI_ID_EDIT_TV0   GUI_ID_USER+7
#define GUI_ID_EDIT_TT0   GUI_ID_USER+8

#define GUI_ID_EDIT_TV1   GUI_ID_USER+9
#define GUI_ID_EDIT_TV2   GUI_ID_USER+10

//     GUI_ID_USER+11 有bug

#define GUI_ID_EDIT_TA1   GUI_ID_USER+12
#define GUI_ID_EDIT_TA2   GUI_ID_USER+13
#define GUI_ID_EDIT_TA3   GUI_ID_USER+14
#define GUI_ID_EDIT_TRES0   GUI_ID_USER+15


#define GUI_ID_EDIT_TT1   GUI_ID_USER+16
#define GUI_ID_EDIT_TT2   GUI_ID_USER+17
#define GUI_ID_EDIT_TT3   GUI_ID_USER+18
#define GUI_ID_EDIT_TDV   GUI_ID_USER+19
#define GUI_ID_EDIT_TRES1   GUI_ID_USER+20
#define GUI_ID_EDIT_TRES2   GUI_ID_USER+21

#define GUI_ID_EDIT_TT   GUI_ID_USER+22
#define GUI_ID_EDIT_TVP   GUI_ID_USER+23

#define GUI_ID_EDIT_TRES4   GUI_ID_USER+24

#define GUI_ID_TEXT_TENCR   GUI_ID_USER+25
#define GUI_ID_TEXT_TENCN   GUI_ID_USER+26
#define GUI_ID_TEXT_Tr   GUI_ID_USER+28

#define GUI_ID_TEXT_TVE   GUI_ID_USER+29
#define GUI_ID_TEXT_TR   GUI_ID_USER+30
#define GUI_ID_TEXT_TV0   GUI_ID_USER+31
#define GUI_ID_TEXT_TT0   GUI_ID_USER+32

#define GUI_ID_TEXT_TV1   GUI_ID_USER+33
#define GUI_ID_TEXT_TV2   GUI_ID_USER+34
#define GUI_ID_TEXT_TA1   GUI_ID_USER+35
#define GUI_ID_TEXT_TA2   GUI_ID_USER+36
#define GUI_ID_TEXT_TA3   GUI_ID_USER+37
#define GUI_ID_TEXT_TRES0   GUI_ID_USER+38

#define GUI_ID_TEXT_TT1   GUI_ID_USER+39
#define GUI_ID_TEXT_TT2   GUI_ID_USER+40
#define GUI_ID_TEXT_TT3   GUI_ID_USER+41
#define GUI_ID_TEXT_TDV   GUI_ID_USER+42
#define GUI_ID_TEXT_TRES1   GUI_ID_USER+43
#define GUI_ID_TEXT_TRES2   GUI_ID_USER+44

#define GUI_ID_TEXT_TT   GUI_ID_USER+45
#define GUI_ID_TEXT_TVP   GUI_ID_USER+46
#define GUI_ID_TEXT_TRES3   GUI_ID_USER+47
#define GUI_ID_TEXT_TRES4   GUI_ID_USER+48

#define GUI_ID_CHECK_BOX_MUL GUI_ID_USER+49

#define GUI_ID_TEXT_EN   GUI_ID_USER+50
#define GUI_ID_CHECKBOX_TMULT   GUI_ID_USER+51
#define GUI_ID_BUTTON_OK   GUI_ID_USER+52

/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_tpar[] = {

    { FRAMEWIN_CreateIndirect,  "TParameters",       0,                       0,  0,  443,480,0,0},

    { TEXT_CreateIndirect,      "初速度V0:",            GUI_ID_TEXT_TV0,         123,51, 80, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TV0,         128,67, 70, 21, 0,0},

    { BUTTON_CreateIndirect,    "OK",                GUI_ID_BUTTON_OK,               239,415,88, 42, 0,0},
    { BUTTON_CreateIndirect,    "Cancel",            GUI_ID_BUTTON0,          341,415,88, 42, 0,0},

    { TEXT_CreateIndirect,      "初始时间t0:",           GUI_ID_TEXT_TT0,         226,51, 96, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TT0,         233,67, 70, 21, 0,0},

    { TEXT_CreateIndirect,      "ms",                GUI_ID_TEXT1,            186,233,17, 12, 0,0},
    { TEXT_CreateIndirect,      "上升时间t1:",           GUI_ID_TEXT_TT1,         5,  233,96, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TT1,         107,227,70, 21, 0,0},

    { TEXT_CreateIndirect,      "ms",                GUI_ID_TEXT1,            186,273,17, 12, 0,0},
    { TEXT_CreateIndirect,      "持续时间t2:",           GUI_ID_TEXT_TT2,         208,232,96, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TT2,         310,228,70, 21, 0,0},

    { TEXT_CreateIndirect,      "m/s",               GUI_ID_TEXT1,            386,352,23, 12, 0,0},
    { TEXT_CreateIndirect,      "振动频率Hz:",            GUI_ID_TEXT_TT,          11, 346,88, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TT,          107,343,70, 21, 0,0},

    { TEXT_CreateIndirect,      "振动幅度Vp:",           GUI_ID_TEXT_TVP,         213,348,96, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TVP,         310,347,70, 21, 0,0},
    { TEXT_CreateIndirect,      "额定速度Ve:",           GUI_ID_TEXT_TVE,         11, 51, 96, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TVE,         16, 67, 70, 21, 0,0},
    { TEXT_CreateIndirect,      "m/s",               GUI_ID_TEXT1,            203,73, 23, 12, 0,0},
    { TEXT_CreateIndirect,      "节经r:",              GUI_ID_TEXT_Tr,          350,7,  56, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TRES3,       341,64, 70, 21, 0,0},
    { TEXT_CreateIndirect,      "mm",                GUI_ID_TEXT1,            417,29, 17, 12, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TR,          234,26, 70, 21, 0,0},
    { TEXT_CreateIndirect,      "保留3:",              GUI_ID_TEXT_TRES3,        350,48, 56, 16, 0,0},
    { TEXT_CreateIndirect,      "外径R:",              GUI_ID_TEXT_TR,          238,7,  56, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_Tr,          341,24, 70, 21, 0,0},
    { CHECKBOX_CreateIndirect,  "多曲线显示",             GUI_ID_CHECK_BOX_MUL,             19, 415,107,20, 0,0},
    { TEXT_CreateIndirect,      "ms",                GUI_ID_TEXT1,            310,70, 17, 12, 0,0},
    { TEXT_CreateIndirect,      "下降时间t3:",           GUI_ID_TEXT_TT3,         6,  269,96, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TT3,         107,268,70, 21, 0,0},
    { TEXT_CreateIndirect,      "ms",                GUI_ID_TEXT1,            389,233,17, 12, 0,0},
    { TEXT_CreateIndirect,      "m/s",               GUI_ID_TEXT1,            386,273,23, 12, 0,0},
    { TEXT_CreateIndirect,      "跳变量dV:",            GUI_ID_TEXT_TDV,         221,269,80, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TDV,         310,268,70, 21, 0,0},
    { TEXT_CreateIndirect,      "保留2:",              GUI_ID_TEXT_TRES2,       233,305,56, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TRES2,       310,304,70, 21, 0,0},
    { TEXT_CreateIndirect,      "xx",                GUI_ID_TEXT1,            389,309,17, 12, 0,0},
    { TEXT_CreateIndirect,      "xx",                GUI_ID_TEXT1,            417,70, 17, 12, 0,0},
    { TEXT_CreateIndirect,      "ms",                GUI_ID_TEXT1,            186,352,17, 12, 0,0},
    { TEXT_CreateIndirect,      "mm",                GUI_ID_TEXT1,            90, 29, 17, 12, 0,0},
    { TEXT_CreateIndirect,      "速度V1:",             GUI_ID_TEXT_TV1,         21, 114,64, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TV1,         107,111,70, 21, 0,0},
    { TEXT_CreateIndirect,      "速度V2:",             GUI_ID_TEXT_TV2,         229,110,64, 16, 0,0},
    { TEXT_CreateIndirect,      "m/s",               GUI_ID_TEXT1,            183,114,23, 12, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TV2,         310,109,70, 21, 0,0},
    { TEXT_CreateIndirect,      "m/s",               GUI_ID_TEXT1,            386,114,23, 12, 0,0},

	{ TEXT_CreateIndirect,      "加速度a1:",            GUI_ID_TEXT_TA1,         13, 154,80, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TA1,         107,150,70, 21, 0,0},
    { TEXT_CreateIndirect,      "m2/s",              GUI_ID_TEXT1,            180,154,29, 12, 0,0},

    { TEXT_CreateIndirect,      "加速度a2:",            GUI_ID_TEXT_TA2,         221,150,80, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TA2,         310,149,70, 21, 0,0},
    { TEXT_CreateIndirect,      "m2/s",              GUI_ID_TEXT1,            383,154,29, 12, 0,0},

    { TEXT_CreateIndirect,      "加速度a3:",            GUI_ID_TEXT_TA3,         13, 194,80, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TA3,         107,189,70, 21, 0,0},
    { TEXT_CreateIndirect,      "m2/s",              GUI_ID_TEXT1,            180,194,29, 12, 0,0},
    { TEXT_CreateIndirect,      "保留0:",              GUI_ID_TEXT_TRES0,       233,190,56, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TRES0,       310,189,70, 21, 0,0},
    { TEXT_CreateIndirect,      "xx",                GUI_ID_TEXT1,            389,194,17, 12, 0,0},
    { TEXT_CreateIndirect,      "保留1:",              GUI_ID_TEXT_TRES1,       25, 309,56, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TRES1,       107,301,70, 21, 0,0},
    { TEXT_CreateIndirect,      "xx",                GUI_ID_TEXT1,            186,309,17, 12, 0,0},
    { TEXT_CreateIndirect,      "编码器R:",             GUI_ID_TEXT_TENCR,       14, 7,  72, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TENCR,       16, 26, 70, 21, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TENCN,       128,26, 70, 21, 0,0},
    { TEXT_CreateIndirect,      "编码器线N:",            GUI_ID_TEXT_TENCN,       123,7,  88, 16, 0,0},
    { TEXT_CreateIndirect,      "n",                 GUI_ID_TEXT1,            203,33, 11, 12, 0,0},
    { TEXT_CreateIndirect,      "mm",                GUI_ID_TEXT1,            310,33, 17, 12, 0,0},
    { TEXT_CreateIndirect,      "m/s",               GUI_ID_TEXT1,            90, 73, 23, 12, 0,0}

};



void OnButtonClicked_TPars(WM_MESSAGE * pMsg)
{
	ttpars.enc_r = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TENCR));
	ttpars.enc_n = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TENCN));
	
	ttpars.r_mm = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_Tr));
	ttpars.Ve = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TVE));
	ttpars.R_mm = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TR));
	ttpars.start_speed = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TV0));
	
	ttpars.V1 = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TV1));
	ttpars.V2 = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TV2));

	ttpars.a1 = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TA1));
	ttpars.a2 = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TA2));
	ttpars.a3 = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TA3));

	ttpars.t0 = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TT0));
	ttpars.t1 = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TT1));
	ttpars.t2 = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TT2));
	ttpars.t3 = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TT3));
	ttpars.dV = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TDV));
	ttpars.HZ = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TT));
	ttpars.Vp = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TVP));

//	mot_t_get_speed_line(mot_t_cal);
	caculate_pars(&mot_t_cal);
	LimitSpeedT(pMsg);
}

void OnCheckBoxMULT_TPars(WM_MESSAGE * pMsg)
{
	disp_mult = CHECKBOX_GetState(WM_GetDialogItem(pMsg->hWin,GUI_ID_CHECK_BOX_MUL));
}



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog_tpar(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}

/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog_tpar(WM_MESSAGE * pMsg)
{
	int i;
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    //
    //
	for(i= GUI_ID_TEXT_TENCR;i<  GUI_ID_TEXT_TRES4+1;i++)
    TEXT_SetFont(WM_GetDialogItem(hWin,i),&GUI_FontHZ_SongTi_16);


    //
	CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK_BOX_MUL),&GUI_FontHZ_SongTi_16);
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK_BOX_MUL),"多曲线显示");
    //
 

	for(i= GUI_ID_EDIT_TENCR ;i< GUI_ID_EDIT_TRES4+1;i++)
	{ 
	//EDIT_SetMaxLen(WM_GetDialogItem(hWin,i),6);
	}

	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TENCR),ttpars.enc_r,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TENCN),ttpars.enc_n,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_Tr),ttpars.r_mm,0,99999,3,2);

	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TR),ttpars.R_mm,0,99999,3,2);

	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TVE),ttpars.Ve,0,99999,3,2);

	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TV0),ttpars.start_speed,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TT0),ttpars.t0,0,99999,3,2);
	
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TV1),ttpars.V1,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TV2),ttpars.V2,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TA1),ttpars.a1,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TA2),ttpars.a2,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TA3),ttpars.a3,0,99999,3,2);
	
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TT1),ttpars.t1,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TT2),ttpars.t2,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TT3),ttpars.t3,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TDV),ttpars.dV,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TT),ttpars.HZ,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TVP),ttpars.Vp,0,99999,3,2);
	
	WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT_TRES0));
	WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT_TRES1));
	WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT_TRES2));
	WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT_TRES3));
	WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT_TRES4));
}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback_tpar(WM_MESSAGE * pMsg)
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog_tpar(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog_tpar(pMsg);
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
				
				case GUI_ID_EDIT_TENCR:
				case GUI_ID_EDIT_TENCN:
				case GUI_ID_EDIT_Tr:
				case GUI_ID_EDIT_TV1:
				case GUI_ID_EDIT_TV2:

					if(NCode==WM_NOTIFICATION_RELEASED)
					{
					UseKeyBoard(pMsg,GUI_ID_EDIT_TENCR -GUI_ID_EDIT_TV2+1 ,GUI_ID_EDIT_TENCR,Id,SFLOAT);
					break;
					}
					break;


				case GUI_ID_EDIT_TA1:
				case GUI_ID_EDIT_TA2:
				case GUI_ID_EDIT_TA3:
			    case GUI_ID_EDIT_TV0:
				case GUI_ID_EDIT_TT0:
				case GUI_ID_EDIT_TT1:
				case GUI_ID_EDIT_TT2:
				case GUI_ID_EDIT_TT:
				case GUI_ID_EDIT_TVP:
				case GUI_ID_EDIT_TVE:
				case GUI_ID_EDIT_TR:
				case GUI_ID_EDIT_TT3:
				case GUI_ID_EDIT_TDV:

						if(NCode==WM_NOTIFICATION_RELEASED)
					{
					UseKeyBoard(pMsg,GUI_ID_EDIT_TA1 -GUI_ID_EDIT_TDV+1 ,GUI_ID_EDIT_TA1,Id,SFLOAT);
					break;
					}
					break;

			   
			   	case GUI_ID_BUTTON_OK:
					switch(NCode)
					{
						case WM_NOTIFICATION_CLICKED:
							OnButtonClicked_TPars(pMsg);
							break;
					}
					break;

				 case GUI_ID_CHECK_BOX_MUL:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnCheckBoxMULT_TPars(pMsg);
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
void tparameter(WM_MESSAGE * pMsg)
{ 
  //  GUI_Init();
	current_interface = PORTABLE_LIMIT_TPARS;

	if(pMsg)
	{
		WM_DeleteWindow(pMsg->hWin);
	}

    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */

    current_handle = GUI_CreateDialogBox(_aDialogCreate_tpar, GUI_COUNTOF(_aDialogCreate_tpar), &_cbCallback_tpar, 0, 0, 0);
}



void save_tparameters(void)
{
	


}



void read_tparameters(void)
{



}


