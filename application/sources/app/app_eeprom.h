#ifndef __APP_EEPROM_H__
#define __APP_EEPROM_H__

#include <stdint.h>
#include "app.h"

/**
  *****************************************************************************
  * EEPROM define address.
  *
  *****************************************************************************
  */
#define EEPROM_START_ADDR								(0X0000)
#define EEPROM_END_ADDR									(0X1000)

#define EEPROM_WORM_SCORE_MAGIC_ADDR                 (EEPROM_START_ADDR + 0x0000)
#define EEPROM_WORM_SCORE_TOP3_ADDR                  (EEPROM_START_ADDR + 0x0004)
#define EEPROM_WORM_SCORE_MAGIC                      (0x57524D31UL)

#define EEPROM_WORM_SETTING_MAGIC_ADDR               (EEPROM_START_ADDR + 0x0010)
#define EEPROM_WORM_SETTING_DATA_ADDR                (EEPROM_START_ADDR + 0x0014)
#define EEPROM_WORM_SETTING_MAGIC                    (0x57525354UL)

#endif //__APP_EEPROM_H__
