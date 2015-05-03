
#include "game_gfx.h"
#include "pff.h"

// different shades for the different lines: (black, dark gray, light gray, white)
const uint16_t MSG_COLOR[] = {0x0000, 0x3186, 0x632C, 0x94B2};

void initButtons(void){
	btn1.selected = 1;
	btn2.selected = 0;
	btn3.selected = 0;
	btn4.selected = 0;

	btn1.x_tc = 0;
	btn2.x_tc = ILI9340_TFTWIDTH/2;
	btn3.x_tc = 0;
	btn4.x_tc = ILI9340_TFTWIDTH/2;

	btn1.y_tc = ILI9340_TFTHEIGHT-2*h_btn-btn_clearance;
	btn2.y_tc = ILI9340_TFTHEIGHT-2*h_btn-btn_clearance;
	btn3.y_tc = ILI9340_TFTHEIGHT-h_btn-btn_clearance;
	btn4.y_tc = ILI9340_TFTHEIGHT-h_btn-btn_clearance;

	btn1.text = "Tackle";
	btn2.text = "Ember";
	btn3.text = "Scratch";
	btn4.text = "Growl";

	activeButton = 1;
}

void drawButton(btnAttack_t* btn){
	uint16_t fill_color, text_color;
	uint16_t text_length = 0;
	char* init_pointer = btn->text;

	if (btn->selected){
		fill_color = s_color;
		text_color = s_tcolor;
	}
	else{
		fill_color = ns_color;
		text_color = ns_tcolor;
	}

	// fill rounded rectangle
	tft_fillRoundRect(btn->x_tc, btn->y_tc, w_btn, h_btn, r_btn, fill_color);

	// draw edge around it
	tft_drawRoundRect(btn->x_tc, btn->y_tc, w_btn, h_btn, r_btn, ILI9340_BLACK);

	// setup text for drawing
	tft_setTextColor(text_color);
	tft_setTextSize(1);

	// center text
	while (*(btn->text)){
		text_length++;
		btn->text++;
	}
	text_length *= 5; // 7x5 blocks

	// reset pointer
	btn->text = init_pointer;

	tft_setCursor(btn->x_tc+w_btn/2-text_length/2, btn->y_tc+h_btn/2);

	// draw text
	tft_writeString(btn->text);

}

void updateButtons(void){
	btn1.selected = 0;
	btn2.selected = 0;
	btn3.selected = 0;
	btn4.selected = 0;

	if (activeButton == 1){
//		drawButton(&btn4);
		btn1.selected = 1;
	}
	else if (activeButton == 2){
//		drawButton(&btn1);
		btn2.selected = 1;
	}
	else if (activeButton == 3){
//		drawButton(&btn2);
		btn3.selected = 1;
	}
	else if (activeButton == 4){
//		drawButton(&btn3);
		btn4.selected = 1;
	}

	drawButton(&btn1);
	drawButton(&btn2);
	drawButton(&btn3);
	drawButton(&btn4);

}

void get_pokemon(uint16_t pokemon_number, uint8_t side){
	/*
	 * pokemon_number: assigned number of pokemon that identies it
	 * side: 	which side - opposition or player
	 * 			0	=	player
	 * 			1	=	oppostion
	 */

	FRESULT fat_result;

	WORD br;

	uint16_t rd_block = 60;
	uint16_t rd_size;
	/* This tells how many bytes to read at one time
	 * A small number is used to minimize RAM usage.
	 * 3 bytes are needed to get information about one
	 * pixel.
	 * To read the entire BMP header, 60 bytes are allocated
	 * since that is 54 bytes long.
	 */
	uint8_t buffer[60];

	/* row_count is used to keep track of where in the row we are.
	 * If this goes beyond the row size, go to next line.
	 */
	uint16_t row_count = 0;

	char fname [12];
	sprintf(fname, "%d.bmp\0", pokemon_number);

	// Open the image file
	fat_result = pf_open(fname);
	if (fat_result){
		sprintf((char*) buffer, "PFF error 2 = %d\n", (int) fat_result);
		tft_writeString((char*) buffer);
	}

	//Read data to the memory
	fat_result = pf_read(buffer, 54, &br);
	if (fat_result){
		sprintf((char*) buffer, "PFF error 3 = %d\n", (int) fat_result);
		tft_writeString((char*) buffer);
	}

	// http://en.wikipedia.org/wiki/BMP_file_format
//	bmp_header.bmp_size = ((uint32_t)buffer[5]<<24)+((uint32_t)buffer[4]<<16)+((uint32_t)buffer[3]<<8)+((uint32_t)buffer[2]);
	bmp_header.bpp = buffer[28];
//	bmp_header.comp = buffer[30];
//	bmp_header.header_size = buffer[14];
	bmp_header.height = ((uint16_t)buffer[23]<<8)+(uint16_t)buffer[22];
//	bmp_header.offset = ((uint16_t)buffer[11]<<8)+(uint16_t)buffer[10];
//	bmp_header.signature = ((uint16_t)buffer[1]<<8)+(uint16_t)buffer[0];
//	bmp_header.size_w_padding =((uint32_t)buffer[37]<<24)+((uint32_t)buffer[36]<<16)+((uint32_t)buffer[35]<<8)+((uint32_t)buffer[34]);
	bmp_header.width = ((uint16_t)buffer[19]<<8)+(uint16_t)buffer[18];

	// row size calculation
	bmp_header.row_size = ((uint32_t)bmp_header.bpp * (uint32_t)bmp_header.width + (uint32_t)31) >> 3; // *4/32 = >>3

	uint32_t mod_rs = bmp_header.row_size % 4;
	if (mod_rs != 0){
		bmp_header.row_size -= mod_rs;
	}

// Bitmap file opened and info retrieved - now get data from the pixel array


	uint16_t y = bmp_header.height + 1;
	uint16_t p = 0;
	uint16_t x = 0;
	uint16_t z = 0;
	uint16_t l = 0;

	P1OUT &= ~BIT0;
	if (side == 0){
		y = bmp_header.height+1;
		l = ILI9340_TFTWIDTH-2-bmp_header.width;
	}
	else {
		y = bmp_header.height+1;
		l = 1;
	}

	if (y > IMAGE_MAXHEIGHT){
		y = IMAGE_MAXHEIGHT;
	}

	rd_size = rd_block;

	for (p = 0; p < bmp_header.height; p++){
		y--;
		if (y <= 0){
			break;
		}
		z = 0;
		row_count = 0;
		tft_setAddrWindow(l, y, l+bmp_header.width-1, y);

		do{
			row_count += rd_block;
			if (row_count < bmp_header.row_size){
				rd_size = rd_block;
			}
			else{
				rd_size = (bmp_header.row_size + rd_block) - row_count;
			}
			pf_read(buffer, rd_size, &br);
			// rely on division to floor value
			z = 0;
			for (x = 0; x < rd_size/3; x++){
				tft_pushColor(tft_Color565(buffer[z+2],buffer[z+1],buffer[z]));
				z += 3;
			}
		} while (row_count < bmp_header.row_size);
	}

}

void draw_borders(void){
	tft_drawRoundRect(0,0,SCREEN_CENTER,BORDER_HEIGHT,r_btn,ILI9340_BLACK);
	tft_drawRoundRect(SCREEN_CENTER,0,SCREEN_CENTER,BORDER_HEIGHT,r_btn,ILI9340_BLACK);
}

void draw_names(char* name_self, char* name_opponent){
	char* pokemon_name;

	tft_setTextColor(ILI9340_BLACK);
	tft_setTextSize(1);

	tft_setCursor(HEALTH_BAR_LEFT_OFFSET, NAME_Y);
	pokemon_name = (char*) name_opponent;
	tft_writeString(pokemon_name);

	tft_setCursor(SCREEN_CENTER+HEALTH_BAR_LEFT_OFFSET, NAME_Y);
	pokemon_name = (char*) name_self;
	tft_writeString(pokemon_name);
}

void draw_health(uint8_t health_self, uint8_t health_opponent){
	uint16_t fill_color;

	if (health_opponent < 20) fill_color = ILI9340_RED;
	else if (health_opponent < 50) fill_color = ILI9340_ORANGE;
	else fill_color = ILI9340_GREEN;

	tft_fillRect(HEALTH_BAR_LEFT_OFFSET, HEALTH_BAR_Y, 100, HEALTH_BAR_HEIGHT, ILI9340_WHITE);
	tft_fillRect(HEALTH_BAR_LEFT_OFFSET, HEALTH_BAR_Y, health_opponent, HEALTH_BAR_HEIGHT, fill_color);
	tft_drawRect(HEALTH_BAR_LEFT_OFFSET, HEALTH_BAR_Y, 100, HEALTH_BAR_HEIGHT, ILI9340_BLACK);

	if (health_self < 20) fill_color = ILI9340_RED;
	else if (health_self < 50) fill_color = ILI9340_ORANGE;
	else fill_color = ILI9340_GREEN;

	tft_fillRect(SCREEN_CENTER+HEALTH_BAR_LEFT_OFFSET, HEALTH_BAR_Y, 100, HEALTH_BAR_HEIGHT, ILI9340_WHITE);
	tft_fillRect(SCREEN_CENTER+HEALTH_BAR_LEFT_OFFSET, HEALTH_BAR_Y, health_self, HEALTH_BAR_HEIGHT, fill_color);
	tft_drawRect(SCREEN_CENTER+HEALTH_BAR_LEFT_OFFSET, HEALTH_BAR_Y, 100, HEALTH_BAR_HEIGHT, ILI9340_BLACK);

	tft_fillCircle(ILI9340_TFTWIDTH-HEALTH_BAR_LEFT_OFFSET,NAME_Y,r_btn/2,ILI9340_BLACK);
//	tft_drawCircle(ILI9340_TFTWIDTH-HEALTH_BAR_LEFT_OFFSET,NAME_Y,r_btn/2, ILI9340_BLACK);
//	tft_fillCircle(SCREEN_CENTER-HEALTH_BAR_LEFT_OFFSET,NAME_Y,r_btn/2,ILI9340_RED);
	tft_drawCircle(SCREEN_CENTER-HEALTH_BAR_LEFT_OFFSET,NAME_Y,r_btn/2, ILI9340_BLACK);
}

void message_write(char* msg, uint8_t msg_line){
	if (msg == NULL || msg_line > MAX_MSG_LINES)
		return;

	uint8_t msg_y = BORDER_HEIGHT+MSG_CLEARANCE+MSG_HEIGHT*msg_line;

	// clear text area
	tft_fillRect(0, msg_y,ILI9340_TFTWIDTH,MSG_HEIGHT,ILI9340_WHITE);

	tft_setCursor(MSG_X, msg_y);

	uint16_t text_color = MSG_COLOR[msg_line-1];

	tft_setTextColor(text_color);
	tft_setTextSize(1);
	tft_writeString(msg);

}
