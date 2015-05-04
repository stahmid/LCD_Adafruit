/*
 * setup.h
 *
 *  Created on: May 3, 2015
 *      Author: Tahmid
 */

#ifndef SETUP_H_
#define SETUP_H_

#include "bsp.h"

#include "tft_master.h"
#include "tft_gfx.h"
#include "game_gfx.h"

#include "tmr_int.h"
#include "flags.h"

#include "spi.h"
#include "diskio.h"
#include "pff.h"

//#include "touchlib.h"
#include "parser.h"

pokemon_team_t pkmnt1;
pokemon_data_t pkmnd1;

FATFS fs; /* File system object */
char buffer[30];
FRESULT pres;
DRESULT dres;

void setup_lcd_fs(void);
void setup_timer_buttons(void);
void init_touch_adc(void);

#endif /* SETUP_H_ */
