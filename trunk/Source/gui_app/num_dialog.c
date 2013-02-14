#include "gui_app.h"
extern EDIT_Handle hwin_tick_A_edit;

//EventsFunctionList
void OnEditNumberClicked(WM_MESSAGE * pMsg);
//EndofEventsFunctionList


/*********************************************************************
*
*       static data
*
**********************************************************************
*/

/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  0,  160,240,0,0},
    { BUTTON_CreateIndirect,    "7",                 GUI_ID_BUTTON7,          6,  36, 40, 40, 0,0},
    { BUTTON_CreateIndirect,    "4",                 GUI_ID_BUTTON4,          6,  86, 40, 40, 0,0},
    { BUTTON_CreateIndirect,    "5",                 GUI_ID_BUTTON5,          56, 86, 40, 40, 0,0},
    { BUTTON_CreateIndirect,    "3",                 GUI_ID_BUTTON3,          6,  136,40, 40, 0,0},
    { BUTTON_CreateIndirect,    "6",                 GUI_ID_BUTTON6,          106,86, 40, 40, 0,0},
    { BUTTON_CreateIndirect,    "2",                 GUI_ID_BUTTON2,          56, 136,40, 40, 0,0},
    { BUTTON_CreateIndirect,    "0",                 GUI_ID_BUTTON0,          6,  186,40, 40, 0,0},
    { BUTTON_CreateIndirect,    "1",                 GUI_ID_BUTTON1,          106,136,40, 40, 0,0},
    { BUTTON_CreateIndirect,    "取消",                GUI_ID_CANCEL,           56, 186,40, 40, 0,0},
    { BUTTON_CreateIndirect,    "确定",                GUI_ID_OK,               106,186,40, 40, 0,0},
    { BUTTON_CreateIndirect,    "8",                 GUI_ID_BUTTON8,          56, 36, 40, 40, 0,0},
    { BUTTON_CreateIndirect,    "9",                 GUI_ID_BUTTON9,          106,36, 40, 40, 0,0},
    { EDIT_CreateIndirect,      "20",                GUI_ID_EDIT0,            6,  6,  140,24, 0,0}
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
    GUI_SetColor(0xe35400);
    GUI_FillRect(0,0,159,2);
    GUI_SetColor(0xff953d);
    GUI_FillRect(0,0,2,239);
    GUI_SetColor(0xff953d);
    GUI_FillRect(0,231,159,239);
    GUI_SetColor(0xe35400);
    GUI_FillRect(151,0,159,239);
}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

static void InitDialog(WM_MESSAGE * pMsg)
{
   WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetTitleVis(hWin,0);
    //
    //GUI_ID_BUTTON7
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON7),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON4
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON4),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON5
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON5),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON3
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON3),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON6
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON6),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON2
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON0
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON1
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_CANCEL
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_CANCEL),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_OK
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_OK),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON8
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON8),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_BUTTON9
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON9),&GUI_FontHZ_SongTi_16);
    //
    //GUI_ID_EDIT0
    //
    EDIT_SetFont(WM_GetDialogItem(hWin,GUI_ID_EDIT0),&GUI_FontHZ_SongTi_16);
    EDIT_SetDecMode(WM_GetDialogItem(hWin,GUI_ID_EDIT0),0,0,999999999,0,0);

}

/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
	static int num_backup = 0;
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
					{
                        GUI_EndDialog(hWin, EDIT_GetValue(WM_GetDialogItem(hWin,GUI_ID_EDIT0)));
						num_backup = 0;
					}
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_CLICKED)
					{
						num_backup = 0;
						EDIT_SetValue(WM_GetDialogItem(hWin,GUI_ID_EDIT0),num_backup); 
                       // GUI_EndDialog(hWin, 0);
					}
                    break;
                case GUI_ID_EDIT0:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_CLICKED:
                            OnEditNumberClicked(pMsg);
                            break;
                    }
                    break;
				case GUI_ID_BUTTON0:
				case GUI_ID_BUTTON1:
				case GUI_ID_BUTTON2:
				case GUI_ID_BUTTON3:
				case GUI_ID_BUTTON4:
				case GUI_ID_BUTTON5:
				case GUI_ID_BUTTON6:
				case GUI_ID_BUTTON7:
				case GUI_ID_BUTTON8:
				case GUI_ID_BUTTON9:
					 if(NCode==WM_NOTIFICATION_CLICKED)
					 {
						if(num_backup < 999999999)
						{
							num_backup = num_backup *10 +(Id - GUI_ID_BUTTON0);
						}
						if(num_backup > 999999999)
						{
							num_backup = 999999999;
						}
						EDIT_SetValue(WM_GetDialogItem(hWin,GUI_ID_EDIT0),num_backup);
					 }
					 break;
            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}

int num_dialog(WM_HWIN hWin)
{
	int set_num;
	set_num = GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, hWin, 320, 80);//	GUI_ExecDialogBox
	return set_num;
}

void OnEditNumberClicked(WM_MESSAGE * pMsg)
{

}