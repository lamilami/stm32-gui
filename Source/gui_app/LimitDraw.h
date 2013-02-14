
#include"gui_app.h"
#include "GUI.h"
#include "DIALOG.h"
#include "DROPDOWN.h"

#include "Draw.h"
#include "mot.h"

#ifndef  LIMIT_DRAW_H
#define  LIMIT_DRAW_H

#define GUI_BUTTON_RUN  1
#define GUI_BUTTON_STOP 2
#define GUI_BUTTON_DIR  3
#define GUI_BUTTON_DELECT 4
#define GUI_BUTTON_SAVE  5
#define GUI_BUTTON_PRINT 6
#define GUI_BUTTON_PAR  7
#define GUI_BUTTON_MODE 8
#define GUI_BUTTON_RES  9

#define  BUTTON_LENTH 9

#define LIST_VIEW 10
#define CHECK_BOX 11




extern      S_GetData get_data;
extern      TPars   pars;
extern	    TRecord record;


void limit_draw_init(WM_MESSAGE * pMsg);
void limit_draw_run(WM_MESSAGE * pMsg);
void on_start(void);
void on_stop(void);
void on_dir(void);
void on_list_delect(void);
void on_save(void);
void on_print(void);
void on_par(void);
void on_mode(void);
void on_home(void);
void Set_Color_cell(unsigned Column, unsigned Row,GUI_COLOR Color);
void save_to_ram(void);
void refresh(void);
void value_to_graph(float value);
void release_source(void);

void hide_wig(void);
void show_wig(void);

void task_run(void);


#endif