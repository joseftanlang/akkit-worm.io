#ifndef __OBJ_WORM_H__
#define __OBJ_WORM_H__

//includes
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

#include <math.h>
#include <vector>

#include "screens_bitmap.h"
#include "scr_worm.h"

//codes
#define WORM_START_POSITION_X  (50)
#define WORM_START_POSITION_Y  (35)
#define WORM_START_WIDTH       (20)
#define WORM_START_HEIGHT      (5)
#define INCREMENT_WORM_SIZE    (5) //increment only the width of the worm when it eats an apple

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    uint8_t worm_image;
    uint8_t dir; /* worm_dir_t value */
} worm_t;

typedef enum {
    WORM_DIR_RIGHT = 0,
    WORM_DIR_DOWN,
    WORM_DIR_LEFT,
    WORM_DIR_UP,
} worm_dir_t;

extern worm_t game_worm;

/* Object-only (movement and input handled by screen code) */
void worm_init(void);
void worm_set_direction(worm_dir_t d);
worm_dir_t worm_get_direction(void);
void worm_advance(void);
void worm_grow(void);

/* message signals for `game_worm_handler` */
enum {
    AC_WORM_INIT = AK_USER_DEFINE_SIG,
    AC_WORM_TICK,
    AC_WORM_SET_DIR_RIGHT,
    AC_WORM_SET_DIR_DOWN,
    AC_WORM_SET_DIR_LEFT,
    AC_WORM_SET_DIR_UP,
    AC_WORM_GROW,
};


#endif //__OBJ_WORM_H__