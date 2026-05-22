#ifndef __OBJ_SCORE_H__
#define __OBJ_SCORE_H__

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

#define START_SCORE     (10)
#define INCREMENT_SCORE (5)

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t score;
} score_display_t;

void score_display_t 

#endif //__OBJ_SCORE_H__