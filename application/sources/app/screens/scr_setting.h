#ifndef __SCR_GAME_SETTING_H__
#define __SCR_GAME_SETTING_H__

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

#include "eeprom.h"
#include "app_eeprom.h"

#include "screens.h"
#include "screens_bitmap.h"

#define SETTING_ANIM_INTERVAL_MS (85)
#define SETTING_ANIM_TICK_SIG (AK_USER_DEFINE_SIG + 183)
#define SETTING_ROW_COUNT (4)
#define SETTING_ROW_TOP_Y (18)
#define SETTING_ROW_STEP_Y (10)
#define SETTING_ROW_HEIGHT (9)

#define SETTING_WORM_SPEED_MIN (1)
#define SETTING_WORM_SPEED_MAX (5)
#define SETTING_APPLE_COUNT_MIN (1)
#define SETTING_APPLE_COUNT_MAX (8)
#define SETTING_SONG_COUNT (5)

#define SELECTED_DEFAULT_ITEM              (0)
#define SETTING_ITEM_SPEED                 (0)
#define SETTING_ITEM_APPLE                 (1)
#define SETTING_ITEM_SONG                  (2)
#define SETTING_ITEM_BUZZER                (3)

typedef struct{
    uint32_t magic;
    uint8_t worm_speed;
    uint8_t apple_count;
    uint8_t song_index;
    uint8_t buzzer_enabled;
} setting_persist_t;

typedef struct{
    int16_t x;
    uint8_t y;
    uint8_t speed;
} setting_star_t;

extern view_screen_t scr_game_setting;
extern view_dynamic_t dyn_view_item_game_setting;
extern void scr_game_setting_handle(ak_msg_t* msg);
extern uint16_t scr_game_setting_get_worm_tick_interval_ms(void);
extern uint8_t scr_game_setting_get_apple_count(void);
extern buzzer_sound_t scr_game_setting_get_song(void);
extern uint8_t scr_game_setting_is_buzzer_enabled(void);

#endif // __SCR_GAME_SETTING_H__