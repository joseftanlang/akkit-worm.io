#ifndef __SCR_MENU_GAME_H__
#define __SCR_MENU_GAME_H__

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"
#include "view_render.h"

#include "buzzer.h"

#include "app_eeprom.h"
#include "screens_bitmap.h"
#include "screens.h"
#include "scr_setting.h"

#define MENU_VISIBLE_COUNT (3)
#define MENU_TITLE_Y (3)
#define MENU_DIVIDER_Y (14)
#define MENU_ITEMS_TOP_Y (20)
#define MENU_ITEM_STEP_Y (10)
#define MENU_ITEM_HEIGHT (18)

void scr_worm_menu_game_handle(ak_msg_t* msg);

#endif // __SCR_MENU_GAME_H__