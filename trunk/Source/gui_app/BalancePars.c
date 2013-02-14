#include "gui_app.h"
#include "KeyBoard_Win.h"

TBalancePars tbalance_pars;
TBalanceResult tbalance_result;

void OnRadioClicked(WM_MESSAGE * pMsg)
{
	int i,j,k;
	tbalance_pars.test_mode = RADIO_GetValue(WM_GetDialogItem(pMsg->hWin,GUI_ID_RADIO_TEST_MODE));
	if(tbalance_pars.test_mode == 0)
	{
	 for(i=GUI_ID_EDIT_FIRST;i< GUI_ID_EDIT_EIGHTTH+1;i++)
	 WM_DisableWindow(WM_GetDialogItem(current_handle,i));
	}else{
	 for(i=GUI_ID_EDIT_FIRST;i< GUI_ID_EDIT_EIGHTTH+1;i++)
	 WM_EnableWindow(WM_GetDialogItem(current_handle,i));	
	}	
}

void OnButtonOK(WM_MESSAGE * pMsg)
{
	char get_value[10];

	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_CUS),tbalance_pars.tcustormer.custorm, sizeof(tbalance_pars.tcustormer.custorm));
	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_ELE_ID),tbalance_pars.tcustormer.series_no, sizeof(tbalance_pars.tcustormer.series_no));
	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_PRO),tbalance_pars.tcustormer.elevator_productor, sizeof(tbalance_pars.tcustormer.elevator_productor));
    
	tbalance_pars.base_value = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_BASE_VALUE));

	EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TOTAL_TIMES),get_value,5);
	
	tbalance_pars.test_times = atoi(get_value);
	
//	tbalance_pars.test_times = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_TOTAL_TIMES));
	
	if(tbalance_pars.test_mode == 0)
	{

	}else{
	 tbalance_pars.first_value = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_FIRST)); 
	 
	 tbalance_pars.second_value = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_SECOND));
	
	 tbalance_pars.third_value = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_THIRD));

	 tbalance_pars.forth_value = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_FOURTH));

	 tbalance_pars.fifth_value = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_FIFTH));

	 tbalance_pars.sixth_value = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_SIXTH));

	 tbalance_pars.seventh_value = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_SEVENTH));

	 tbalance_pars.eighth_value = EDIT_GetFloatValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT_EIGHTTH));				 	 
	}
	
	balance(pMsg);

}









/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_balance_pars[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  0,  800,480,0,0},
    { TEXT_CreateIndirect,      "客户名称",              GUI_ID_TEXT_CUS,            56, 82, 72, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_CUS,         147,77, 193,21, 0,0},
    { TEXT_CreateIndirect,      "电梯序号",              GUI_ID_TEXT_ELE_ID,            56, 113,72, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_ELE_ID_B,      147,108,193,21, 0,0},
    { TEXT_CreateIndirect,      "电梯制造商",             GUI_ID_TEXT_PRO,            56, 144,88, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_PRO,         147,139,193,21, 0,0},
    { TEXT_CreateIndirect,      "保留",                GUI_ID_TEXT_RES1,            63, 173,40, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_RES1,        147,168,193,21, 0,0},
    { RADIO_CreateIndirect,      NULL,               GUI_ID_RADIO_TEST_MODE,  56, 327,81, 38, 0,2},
    { TEXT_CreateIndirect,      "次",                 GUI_ID_TEXT_TIME,            425,327,24, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_TOTAL_TIMES, 358,322,61, 21, 0,0},
    { TEXT_CreateIndirect,      "测试方式",              GUI_ID_TEXT_TEXT_MT,            56, 303,72, 16, 0,0},
    { TEXT_CreateIndirect,      "用户信息",              GUI_ID_TEXT_CUS_IF,            56, 45, 72, 16, 0,0},
    { BUTTON_CreateIndirect,    "OK",                GUI_ID_RETURN_BUTTON,    616,355,165,92, 0,0},
    { TEXT_CreateIndirect,      "按标准测试测试次数",         GUI_ID_TEXT_STAND,            200,327,152,16, 0,0},
    { TEXT_CreateIndirect,      "额定载荷",              GUI_ID_TEXT_GE,            56, 238,72, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_BASE_VALUE,  147,233,61, 21, 0,0},
    { TEXT_CreateIndirect,      "kg",                GUI_ID_TEXT0,            214,238,24, 16, 0,0},
    { TEXT_CreateIndirect,      "升降次序",            GUI_ID_TEXT_TIME_NUM,           502,41, 56, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_FIRST,       562,60, 61, 21, 0,0},
    { TEXT_CreateIndirect,      "对重重量",          GUI_ID_TEXT_BASE_VALUE,            562,41, 72, 16, 0,0},
    { TEXT_CreateIndirect,      "kg",                GUI_ID_TEXT0,            642,41, 24, 16, 0,0},
    { TEXT_CreateIndirect,      "1",                 GUI_ID_TEXT0,            515,65, 16, 16, 0,0},
    { TEXT_CreateIndirect,      "2",                 GUI_ID_TEXT0,            515,99, 16, 16, 0,0},
    { TEXT_CreateIndirect,      "3",                 GUI_ID_TEXT0,            515,133,16, 16, 0,0},
    { TEXT_CreateIndirect,      "4",                 GUI_ID_TEXT0,            515,167,16, 16, 0,0},
    { TEXT_CreateIndirect,      "5",                 GUI_ID_TEXT0,            515,201,16, 16, 0,0},
    { TEXT_CreateIndirect,      "6",                 GUI_ID_TEXT0,            515,235,16, 16, 0,0},
    { TEXT_CreateIndirect,      "7",                 GUI_ID_TEXT0,            515,269,16, 16, 0,0},
    { TEXT_CreateIndirect,      "8",                 GUI_ID_TEXT0,            515,303,16, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_SECOND,      562,94, 61, 21, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_THIRD,       562,128,61, 21, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_FOURTH,      562,162,61, 21, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_FIFTH,       562,196,61, 21, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_SIXTH,       562,230,61, 21, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_SEVENTH,     562,264,61, 21, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT_EIGHTTH,     562,301,61, 21, 0,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog_balance_pars(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog_balance_pars(WM_MESSAGE * pMsg)
{
    int i;
    WM_HWIN hWin = pMsg->hWin;
 
    //
	for(i = GUI_ID_TEXT_CUS; i< GUI_ID_TEXT_GE+1;i++)
	{ 
    TEXT_SetFont(WM_GetDialogItem(hWin,i),&GUI_FontHZ_SongTi_16);
	}
    //
    
    RADIO_SetGroupId(WM_GetDialogItem(hWin,GUI_ID_RADIO_TEST_MODE),0);
	//RADIO_SetFont(WM_GetDialogItem(hWin,GUI_ID_RADIO_TEST_MODE),&GUI_FontHZ_SongTi_16);
    RADIO_SetText(WM_GetDialogItem(hWin,GUI_ID_RADIO_TEST_MODE),"Stand Test",0);
    RADIO_SetText(WM_GetDialogItem(hWin,GUI_ID_RADIO_TEST_MODE),"Self Test",1);

	RADIO_SetValue(WM_GetDialogItem(hWin,GUI_ID_RADIO_TEST_MODE),tbalance_pars.test_mode);
	
//	EDIT_SetDecMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_TOTAL_TIMES),30,0,1000,0,0);
	
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_BASE_VALUE),tbalance_pars.base_value,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_BASE_VALUE),tbalance_pars.first_value,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_BASE_VALUE),tbalance_pars.second_value,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_BASE_VALUE),tbalance_pars.third_value,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_BASE_VALUE),tbalance_pars.forth_value,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_BASE_VALUE),tbalance_pars.fifth_value,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_BASE_VALUE),tbalance_pars.sixth_value,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_BASE_VALUE),tbalance_pars.seventh_value,0,99999,3,2);
	EDIT_SetFloatMode(WM_GetDialogItem(hWin,GUI_ID_EDIT_BASE_VALUE),tbalance_pars.eighth_value,0,99999,3,2);

	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_CUS),tbalance_pars.tcustormer.custorm);
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_ELE_ID_B),tbalance_pars.tcustormer.series_no);
	EDIT_SetText(WM_GetDialogItem(hWin,GUI_ID_EDIT_PRO),tbalance_pars.tcustormer.elevator_productor);


	if(tbalance_pars.test_mode == 0)
	{
	 for(i=GUI_ID_EDIT_FIRST;i< GUI_ID_EDIT_EIGHTTH+1;i++)
	 WM_DisableWindow(WM_GetDialogItem(current_handle,i));
	}

}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback_balance_pars(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog_balance_pars(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog_balance_pars(pMsg);
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


                case GUI_ID_EDIT_CUS:
                case GUI_ID_EDIT_PRO:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                           
							UseKeyBoard(pMsg,2 ,GUI_ID_EDIT_CUS,Id,CHINESE);
                            break;
                    }
                    break;

                case GUI_ID_EDIT_RES1:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            
                            break;
                    }
                    break;

                case GUI_ID_EDIT_TOTAL_TIMES:
		        case GUI_ID_EDIT_ELE_ID_B:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            UseKeyBoard(pMsg,2 ,GUI_ID_EDIT_TOTAL_TIMES,Id,ENGLISH_S);
                            break;
                    }
                    break;

                case GUI_ID_EDIT_FIRST:
          
                case GUI_ID_EDIT_SECOND:
            
                case GUI_ID_EDIT_THIRD:
         
                case GUI_ID_EDIT_FOURTH:
         
                case GUI_ID_EDIT_FIFTH:
         
                case GUI_ID_EDIT_SIXTH:
          
                case GUI_ID_EDIT_SEVENTH:
      
                case GUI_ID_EDIT_EIGHTTH:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            UseKeyBoard(pMsg,GUI_ID_EDIT_EIGHTTH - GUI_ID_EDIT_FIRST+1  ,GUI_ID_EDIT_FIRST,Id,SFLOAT);
                            break;
                    }
                    break;

				case GUI_ID_EDIT_BASE_VALUE:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            UseKeyBoard(pMsg,1,GUI_ID_EDIT_BASE_VALUE,Id,SFLOAT);
                            break;
                    }
                    break;




		        case GUI_ID_RADIO_TEST_MODE:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnRadioClicked(pMsg);
                            break;
                    }
                    break;

				case GUI_ID_RETURN_BUTTON:
					 switch(NCode)
					 {
					 	 case WM_NOTIFICATION_CLICKED:
					 	   OnButtonOK(pMsg);
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
void balance_pars(WM_MESSAGE *pMsg)
{ 
	current_interface = BALANCE_PAR;

	if(pMsg)
	{
		WM_DeleteWindow(pMsg->hWin);
	}

    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */

    current_handle = GUI_CreateDialogBox(_aDialogCreate_balance_pars, GUI_COUNTOF(_aDialogCreate_balance_pars), &_cbCallback_balance_pars, 0, 0, 0);
}

