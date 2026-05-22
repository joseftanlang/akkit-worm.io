#include "obj_worm.h"
#include "obj_border.h"

/* worm object: owns the head rectangle and provides simple helpers.
 * Higher-level movement, rendering and input are handled by the screen code.
 */

worm_t game_worm = {0};

/* movement step aligns with growth so the worm stays grid-consistent */
#ifndef WORM_MOVE_STEP
#define WORM_MOVE_STEP INCREMENT_WORM_SIZE
#endif

void worm_init(void) {
	game_worm.x = WORM_START_POSITION_X;
	game_worm.y = WORM_START_POSITION_Y;
	game_worm.width = WORM_START_WIDTH;
	game_worm.height = WORM_START_HEIGHT;
	game_worm.worm_image = 0;
	game_worm.dir = (uint8_t)WORM_DIR_RIGHT;
}

void worm_set_direction(worm_dir_t d) {
	game_worm.dir = (uint8_t)d;
}

worm_dir_t worm_get_direction(void) {
	return (worm_dir_t)game_worm.dir;
}

void worm_advance(void) {
	switch (worm_get_direction()) {
	case WORM_DIR_RIGHT:
		game_worm.x += WORM_MOVE_STEP;
		break;
	case WORM_DIR_LEFT:
		game_worm.x = (game_worm.x > WORM_MOVE_STEP) ? (game_worm.x - WORM_MOVE_STEP) : 0;
		break;
	case WORM_DIR_DOWN:
		game_worm.y += WORM_MOVE_STEP;
		break;
	case WORM_DIR_UP:
		game_worm.y = (game_worm.y > WORM_MOVE_STEP) ? (game_worm.y - WORM_MOVE_STEP) : 0;
		break;
	}

	/* wrap around inside the game border (or screen if border not set) */
	uint32_t bx = (game_border.width != 0) ? game_border.x : 0;
	uint32_t by = (game_border.height != 0) ? game_border.y : 0;
	uint32_t bw = (game_border.width != 0) ? game_border.width : SCR_WIDTH;
	uint32_t bh = (game_border.height != 0) ? game_border.height : SCR_HEIGHT;

	if (game_worm.x + game_worm.width > bx + bw) {
		game_worm.x = bx;
	} else if (game_worm.x < bx) {
		game_worm.x = bx + bw - game_worm.width;
	}

	if (game_worm.y + game_worm.height > by + bh) {
		game_worm.y = by;
	} else if (game_worm.y < by) {
		game_worm.y = by + bh - game_worm.height;
	}
}

void worm_grow(void) {
	game_worm.width += INCREMENT_WORM_SIZE;
}

void game_worm_handler(ak_msg_t* msg) {
	switch (msg->sig) {
	case AC_WORM_INIT:
		worm_init();
		break;

	case AC_WORM_TICK:
		worm_advance();
		break;

	case AC_WORM_SET_DIR_RIGHT:
		worm_set_direction(WORM_DIR_RIGHT);
		break;

	case AC_WORM_SET_DIR_DOWN:
		worm_set_direction(WORM_DIR_DOWN);
		break;

	case AC_WORM_SET_DIR_LEFT:
		worm_set_direction(WORM_DIR_LEFT);
		break;

	case AC_WORM_SET_DIR_UP:
		worm_set_direction(WORM_DIR_UP);
		break;

	case AC_WORM_GROW:
		worm_grow();
		break;

	default:
		break;
	}
}