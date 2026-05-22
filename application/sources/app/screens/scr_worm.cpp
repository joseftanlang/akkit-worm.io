#include "scr_worm.h"
#include "app.h"
#include "app_dbg.h"

static void view_scr_worm();

#define WORM_TICK_INTERVAL_MS (150)
#define HEART_SIZE (7)
#define HEART_SPACING (1)

view_dynamic_t dyn_view_item_worm = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_worm};

view_screen_t scr_worm = {
	&dyn_view_item_worm,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_worm()
{
	/* draw border (and set game_border) */
	border_settings();

	/* draw apples using bitmap_apple */
	for (uint8_t i = 0; i < MAX_APPLES; i++)
	{
		if (apples_no[i].is_active)
		{
			view_render.drawBitmap((int16_t)apples_no[i].x,
								   (int16_t)apples_no[i].y,
								   bitmap_apple,
								   APPLE_WIDTH,
								   APPLE_HEIGHT,
								   WHITE);
		}
	}

	/* draw worm head */
	view_render.fillRect((int16_t)game_worm.x,
						 (int16_t)game_worm.y,
						 (int16_t)game_worm.width,
						 (int16_t)game_worm.height,
						 WHITE);

	/* draw lives at top right */
	for (uint32_t i = 0; i < lives_get(); i++)
	{
		int16_t heart_x = (int16_t)(SCR_WIDTH - HEART_SIZE - (i * (HEART_SIZE + HEART_SPACING)));
		view_render.drawBitmap(heart_x,
							   0,
							   bitmap_heart_w,
							   HEART_SIZE,
							   HEART_SIZE,
							   WHITE);
	}
}

void game_gamer_handler(ak_msg_t *msg)
{
	switch (msg->sig)
	{
	case AC_WORM_INIT:
		task_post_pure_msg(GAME_WORM_ID, AC_WORM_INIT);
		task_post_pure_msg(GAME_LIVES_ID, AC_LIVES_INIT);
		task_post_pure_msg(GAME_APPLE_ID, AC_APPLE_INIT);
		break;

	case AC_WORM_TICK:
	{
		task_post_pure_msg(GAME_WORM_ID, AC_WORM_TICK);
		view_render_screen(&scr_worm);
	}
	break;

	default:
		break;
	}
}

void scr_worm_handle(ak_msg_t *msg)
{
	switch (msg->sig)
	{
	case SCREEN_ENTRY:
	{
		timer_remove_attr(GAME_GAMER_ID, AC_WORM_TICK);
		task_post_pure_msg(GAME_WORM_ID, AC_WORM_INIT);
		task_post_pure_msg(GAME_LIVES_ID, AC_LIVES_INIT);
		task_post_pure_msg(GAME_APPLE_ID, AC_APPLE_INIT);
		timer_set(GAME_GAMER_ID, AC_WORM_TICK, WORM_TICK_INTERVAL_MS, TIMER_PERIODIC);
	}
	break;

	default:
		break;
	}

	if (msg->sig == 12) { /* AC_DISPLAY_BUTON_UP_PRESSED */
		task_post_pure_msg(GAME_WORM_ID, AC_WORM_SET_DIR_RIGHT);
	}
    else if (msg->sig == 13) { /* AC_DISPLAY_BUTON_DOWN_PRESSED */
		task_post_pure_msg(GAME_WORM_ID, AC_WORM_SET_DIR_LEFT);
	}
	else if (msg->sig == 11) { /* AC_DISPLAY_BUTON_MODE_PRESSED */
		timer_remove_attr(GAME_GAMER_ID, AC_WORM_TICK);
		SCREEN_BACK();
	}
}