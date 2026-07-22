#include "scr_startup.h"

static void view_scr_startup();
static uint8_t startup_anim_index = 0;

view_dynamic_t dyn_view_startup = {{.item_type = ITEM_TYPE_DYNAMIC,},view_scr_startup};

view_screen_t scr_startup = {&dyn_view_startup,ITEM_NULL,ITEM_NULL,.focus_item = 0,};

void view_scr_startup(){
	view_render.clear();
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);

	// Drawing the 2 penguins
	view_render.drawBitmap(0, 15, image_WarningDolphin_1_bits, 45, 42, WHITE);
	view_render.drawBitmap(80, 15, image_WarningDolphinFlip_bits, 45, 42, WHITE);

	// Title text
	view_render.setTextSize(2);
	view_render.setCursor(10, 0);
	view_render.print("WORM GAME");
}

void scr_startup_handle(ak_msg_t *msg){
	switch (msg->sig){
	case SCREEN_ENTRY:
		APP_DBG_SIG("AC_DISPLAY_INITIAL\n");
		view_render.initialize();
		view_render_display_on();
		view_render_screen(&scr_startup);
		timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_STARTUP_ANIM_TICK, AC_DISPLAY_STARTUP_ANIM_TICK_INTERVAL, TIMER_PERIODIC);
		timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_LOGO, AC_DISPLAY_STARTUP_INTERVAL, TIMER_ONE_SHOT);
	break;

	case AC_DISPLAY_BUTON_MODE_PRESSED:
	case AC_DISPLAY_BUTON_UP_PRESSED:
	case AC_DISPLAY_BUTON_DOWN_PRESSED:
		APP_DBG_SIG("AC_DISPLAY_MENU_SCREEN\n");
		timer_remove_attr(AC_TASK_DISPLAY_ID, AC_DISPLAY_STARTUP_ANIM_TICK);
		SCREEN_TRAN(scr_worm_menu_game_handle, &scr_menu_game);
	break;

	case AC_DISPLAY_STARTUP_ANIM_TICK:
		startup_anim_index++;
		view_render_screen(&scr_startup);
	break;

	case AC_DISPLAY_SHOW_LOGO:
		APP_DBG_SIG("AC_DISPLAY_MENU_SCREEN\n");
		timer_remove_attr(AC_TASK_DISPLAY_ID, AC_DISPLAY_STARTUP_ANIM_TICK);
		SCREEN_TRAN(scr_worm_menu_game_handle, &scr_menu_game);
	break;

	case AC_DISPLAY_SHOW_IDLE:
		APP_DBG_SIG("AC_DISPLAY_SHOW_IDLE\n");
		SCREEN_TRAN(scr_idle_handle, &scr_idle);
	break;

	default:
		break;
	}
}
