/*
 * game_gfx.h
 *
 *  Created on: Apr 30, 2015
 *      Author: Tahmid
 */

#ifndef GAME_GFX_H_
#define GAME_GFX_H_

#include "tft_master.h"
#include "tft_gfx.h"
#include "bsp.h"

#define MAX_MSG_LINES			4
#define MSG_CLEARANCE			5
#define MSG_HEIGHT				(textsize*8)
#define MSG_X					10

#define IMAGE_MAXHEIGHT			140
#define IMAGE_MAXWIDTH			120
#define HEALTH_BAR_LEFT_OFFSET	10
#define HEALTH_BAR_Y			165
#define HEALTH_BAR_HEIGHT		20
#define NAME_Y					150
#define	SCREEN_CENTER			ILI9340_TFTWIDTH/2
#define ME_LEFT					210

#define BORDER_HEIGHT			(HEALTH_BAR_Y+HEALTH_BAR_HEIGHT+10)

#define h_btn			25
#define w				ILI9340_TFTWIDTH
#define	w_btn			w/2
#define r_btn			10	// radius for rounding rectangle

#define	btn_clearance 	20 // clearance off the bottom of the screen
#define s_color 		ILI9340_BLACK	// background color for filling
#define s_tcolor		ILI9340_WHITE	// text color when selected
#define ns_color 		ILI9340_WHITE	// background color for filling
#define ns_tcolor		ILI9340_BLACK	// text color when not selected

typedef struct attack_button{
	uint16_t x_tc; // x coordinates of top left corner
	uint16_t y_tc; // y coordinates of top left corner
	uint8_t selected; // 1 = button currently selected, 0 = button not selected
	char* text; // text to display on button
} btnAttack_t;

btnAttack_t btn1, btn2, btn3, btn4;

volatile uint8_t activeButton;

void initButtons(void);
void drawButton(btnAttack_t* btn);
void updateButtons(void);

volatile uint8_t flgupdateButton;

struct bitmap_header{
//	uint16_t signature;
//	uint32_t bmp_size;
	/* offset should theoretically be 32 bits but we
	 * need not that much
	 */
//	uint16_t offset;
//	uint8_t header_size;
	uint16_t width;
	uint16_t height;
	uint8_t bpp;
//	uint8_t comp;
//	uint32_t size_w_padding;
	uint16_t row_size;
} bmp_header;


void get_pokemon(uint16_t pokemon_number, uint8_t side);
void draw_borders(void);
void draw_health(uint8_t health_self, uint8_t health_opponent);

#define MESSAGE_Y
void message_write(char* msg, uint8_t msg_line);

void draw_names(char* name_self, char* name_opponent);

#endif /* GAME_GFX_H_ */
