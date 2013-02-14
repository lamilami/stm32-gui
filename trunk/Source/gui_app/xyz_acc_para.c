#include "gui_app.h"
#include "xyz_acc_para.h"
#include "arm_math.h"
#include "XYZ.h"


/*********************************************************************
*
*       static data
*
**********************************************************************
*/

//EventsFunctionList
void OnEditSetSmapleTimeClicked(WM_MESSAGE * pMsg);
void OnButtonOKClicked(WM_MESSAGE * pMsg);

TXYZ_Pars xyz_pars;
TXYZ_Cus  xyz_cus;

static int num_dilog_status = 0;


unsigned int loc_A;
unsigned int loc_B;


void OnCheckBoxClicked(WM_MESSAGE * pMsg)
{
	xyz_pars.auto_sel = CHECKBOX_GetState(WM_GetDialogItem(pMsg->hWin,GUI_ID_CHECKBOX_AUTO));
}


//FIR
void OnRadioButtonClicked(WM_MESSAGE * pMsg)
{
	int get_id;

	get_id = RADIO_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_RADIO_FILTER));

	xyz_pars.e_filter = get_id;

	xyz_pars.e_filter = get_id;
	if(get_id != FILTER_NO)
	{
	fir_init(get_id);
	}
}

/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {

	{ FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  0,  800,480,0,0},
    { TEXT_CreateIndirect,      "客户名称",              GUI_ID_TEXT1,            88, 80, 72, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_CUS,         179,75, 193,21, 0,0},
    { TEXT_CreateIndirect,      "电梯序号",              GUI_ID_TEXT2,            88, 111,72, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_ELE_ID,      179,106,193,21, 0,0},
    { TEXT_CreateIndirect,      "电梯制造商",             GUI_ID_TEXT3,            88, 142,88, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_PRO,         179,137,193,21, 0,0},
    { TEXT_CreateIndirect,      "保留",                GUI_ID_TEXT4,            95, 176,40, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_RES1,        179,171,193,21, 0,0},
    { RADIO_CreateIndirect,      NULL,               GUI_ID_RADIO_FILTER,     562,75, 175,117,0,6},

    { TEXT_CreateIndirect,      "记录方式",              GUI_ID_TEXT5,            88, 226,72, 16, 0,0},
    { TEXT_CreateIndirect,      "开始记录门限",            GUI_ID_TEXT6,            179,256,104,16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_START_R,     289,253,61, 21, 0,0},
    { TEXT_CreateIndirect,      "m2/s(Za)",          GUI_ID_TEXT12,           356,256,53, 12, 0,0},
    { TEXT_CreateIndirect,      "结束记录门限",            GUI_ID_TEXT7,            179,284,104,16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_STOP_R,      289,279,61, 21, 0,0},
    { TEXT_CreateIndirect,      "m2/s(Za)",          GUI_ID_TEXT13,           356,282,53, 12, 0,0},
    { TEXT_CreateIndirect,      "定时记录",              GUI_ID_TEXT8,            88, 352,72, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_SAMPLE_TIME_EDIT, 289,345,61, 21, 0,0},
    { TEXT_CreateIndirect,      "s",                 GUI_ID_TEXT14,           356,350,11, 12, 0,0},
    { TEXT_CreateIndirect,      "记录时间",              GUI_ID_TEXT9,            211,350,72, 16, 0,0},
    { CHECKBOX_CreateIndirect,  "自动",                GUI_ID_CHECKBOX_AUTO,             95, 255,59, 20, 0,0},
    { TEXT_CreateIndirect,      "滤波方式",              GUI_ID_TEXT10,            562,43, 72, 16, 0,0},
    { TEXT_CreateIndirect,      "用户信息",              GUI_ID_TEXT11,            88, 43, 72, 16, 0,0},
    { BUTTON_CreateIndirect,    "OK",                GUI_ID_RETURN_BUTTON,    619,399,165,54, 0,0}

};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

static void PaintDialog(WM_MESSAGE * pMsg)
{
	WM_HWIN hWin = pMsg->hWin;
}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/
static void InitDialog(WM_MESSAGE * pMsg)
{
	int i;

	char buf[10] ;

    WM_HWIN hWin = pMsg->hWin;
	
	WM_DisableWindow(WM_GetDialogItem(hWin,GUI_ID_EDIT_RES1));
    //
    //GUI_ID_SAMPLE_TIME_EDIT
    //
    //EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_SAMPLE_TIME_EDIT),&GUI_FontHZ_SongTi_16);
    //EDIT_SetDecMode(WM_GetDialogItem(hWin,GUI_ID_SAMPLE_TIME_EDIT),xyz_pars.record_s,1,99999,0,0);
	
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_START_R),xyz_pars.auto_start_za,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_STOP_R),xyz_pars.auto_stop_za,0,99999,3,2);
    //
    
	for(i=GUI_ID_TEXT1;i<GUI_ID_TEXT11+1;i++)
	{
    TEXT_SetFont(WM_GetDialogItem(hWin,i),&GUI_FontHZ_SongTi_16);
	}

	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_CUS),50);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_ELE_ID),50);
	EDIT_SetMaxLen(WM_GetDialogItem(hWin,GUI_ID_EDIT_PRO),50);
	
	//
    //GUI_ID_RADIO0
    //
    RADIO_SetGroupId(WM_GetDialogItem(hWin,GUI_ID_RADIO_FILTER),0);
    RADIO_SetText(WM_GetDialogItem(hWin,GUI_ID_RADIO_FILTER),"No Filter",0);
    RADIO_SetText(WM_GetDialogItem(hWin,GUI_ID_RADIO_FILTER),"20Hz Low",1);
    RADIO_SetText(WM_GetDialogItem(hWin,GUI_ID_RADIO_FILTER),"30Hz Low",2);
    RADIO_SetText(WM_GetDialogItem(hWin,GUI_ID_RADIO_FILTER),"50Hz Low",3);
    RADIO_SetText(WM_GetDialogItem(hWin,GUI_ID_RADIO_FILTER),"100Hz Low",4);
    RADIO_SetText(WM_GetDialogItem(hWin,GUI_ID_RADIO_FILTER),"200Hz Low",5);

	//
    //GUI_ID_CHECKBOX_AUTO
    //
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECKBOX_AUTO),"自动");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECKBOX_AUTO),&GUI_FontHZ_SongTi_16);

	if(xyz_pars.auto_sel)
	{
	CHECKBOX_Check(WM_GetDialogItem(hWin,GUI_ID_CHECKBOX_AUTO));
	}

	EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT_CUS),&GUI_FontHZ_SongTi_16);
	EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT_PRO),&GUI_FontHZ_SongTi_16);

	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_CUS),xyz_cus.custorm);
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_ELE_ID),xyz_cus.series_no);
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_PRO),xyz_cus.elevator_productor);

	sprintf(buf,"%d",xyz_pars.record_s);
	
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_SAMPLE_TIME_EDIT),buf);

	RADIO_SetValue(WM_GetDialogItem(hWin,GUI_ID_RADIO_FILTER),xyz_pars.e_filter);

}


/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
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
                case GUI_ID_RETURN_BUTTON:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnButtonOKClicked(pMsg);
                            break;
                    }
                    break;

				case GUI_ID_EDIT_START_R:
				case GUI_ID_EDIT_STOP_R:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            UseKeyBoard(pMsg,2,GUI_ID_EDIT_START_R,Id,SFLOAT);
                            break;
                    }
                    break;


				case GUI_ID_EDIT_ELE_ID:
				case GUI_ID_SAMPLE_TIME_EDIT:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            UseKeyBoard(pMsg,2,GUI_ID_EDIT_ELE_ID,Id,ENGLISH_B);
                            break;
                    }
                    break;


				case GUI_ID_EDIT_CUS:
				case GUI_ID_EDIT_PRO:
					switch(NCode)
					{
					case WM_NOTIFICATION_RELEASED:
						UseKeyBoard(pMsg,2,GUI_ID_EDIT_CUS,Id,CHINESE);
						break;
					}
					break;

			   case GUI_ID_RADIO_FILTER:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnRadioButtonClicked(pMsg);
                            break;
                    }
                    break;

			   case GUI_ID_CHECKBOX_AUTO:
				   switch(NCode)
				   {
					   case WM_NOTIFICATION_CLICKED:
						OnCheckBoxClicked(pMsg);
						break;
				   }

            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}



void xyz_acc_parameter(WM_MESSAGE *pMsg)
{
	static int flag;
	int ret_get;
	
	current_interface = XYZ_ACC_PARAMETER;
	if(pMsg)
	{
		WM_DeleteWindow(pMsg->hWin);
	}

	if(flag == 0)
	{
	 ret_get = xyz_file_init(1);
	 if(ret_get >0)
	 {
	 
	 }
	 flag = 1;
	}

	current_handle = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
}




static void _ForEach(WM_HWIN hWin, void * pData) 
{
	ELock_Unlock win_status;
	win_status = (ELock_Unlock)pData;
	if (win_status == LOCK) 
	{
		WM_DisableWindow(hWin);
	} 
	else 
	{
		WM_EnableWindow(hWin);
	}
}

void dialog_lock(WM_HWIN hwin,void *pData)
{		 
    ELock_Unlock win_status;
	win_status = (ELock_Unlock)pData;

	WM_ForEachDesc(hwin, _ForEach, pData);
	if (win_status == LOCK) 
	{
		WM_DisableWindow(hwin);
	} 
	else 
	{
		WM_EnableWindow(hwin);
	}
}

void OnButtonOKClicked(WM_MESSAGE * pMsg)
{
	char buf[10];
	
	
	if(xyz_pars.auto_sel)
	{
	 xyz_pars.auto_start_za =  EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_START_R));
	 xyz_pars.auto_stop_za = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_STOP_R));
	}else{
	
	//xyz_pars.record_s = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_SAMPLE_TIME_EDIT));

	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_SAMPLE_TIME_EDIT),buf, 9);
	xyz_pars.record_s = atoi(buf);
	tdisp_acc_struct.acc_sample_seconds = xyz_pars.record_s;
	
	tdisp_acc_struct.acc_nums_of_one_pixel = (800*xyz_pars.record_s)/XYZ_SCALE_X_SIZE;

	}
	
	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_CUS),xyz_cus.custorm, sizeof(xyz_cus.custorm));
	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_ELE_ID),xyz_cus.series_no, sizeof(xyz_cus.series_no));
	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_PRO),xyz_cus.elevator_productor, sizeof(xyz_cus.elevator_productor));
	
	xyz_acc_home(pMsg);
}


void xyz_pars_save()
{
  int bw,res;

#ifndef WIN_SIM
  res = f_lseek(&fsrc, fsrc.fsize);
  res = f_write(&fsrc,&xyz_file,sizeof(xyz_file),&bw); //存储数据
#endif

}

