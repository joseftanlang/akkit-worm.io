#ifndef __OBJ_APPLE_H__
#define __OBJ_APPLE_H__

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
#define MAX_APPLES      (5)
#define APPLE_WIDTH     (7)
#define APPLE_HEIGHT    (7)

enum {
	AC_APPLE_INIT = AK_USER_DEFINE_SIG,
	AC_APPLE_TICK,
};

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
	uint8_t is_active;
	uint8_t life_seconds;
	uint8_t respawn_seconds;
    uint8_t apple_image;
} apple_t;

extern apple_t apples_no[MAX_APPLES];

void counting_apples(void);
void apple_init(void);

#endif //__OBJ_APPLE_H__