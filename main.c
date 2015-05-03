    /*
    sprintf(buffer, "Bytes read = %d\n", (int)br);
    tft_writeString(buffer);

    sprintf(buffer, "Offset to BMP data = %d\n", (uint16_t) bmp_header.offset);
    tft_writeString(buffer);

    sprintf(buffer, "Image width = %d\n", (uint16_t) bmp_header.width);
    tft_writeString(buffer);

    sprintf(buffer, "Image height = %d\n", (uint16_t) bmp_header.height);
    tft_writeString(buffer);

    sprintf(buffer, "BPP = %d\n", (uint16_t) bmp_header.bpp);
    tft_writeString(buffer);

    sprintf(buffer, "Compression type = %d\n", (uint16_t) bmp_header.comp);
    tft_writeString(buffer);

    sprintf(buffer, "Row size = %d\n", (int16_t)bmp_header.row_size);
    tft_writeString(buffer);
     */

#include "bsp.h"
#include "setup.h"

void main(void) {

	setup_lcd_fs();
	setup_timer_buttons();

	init_touch_adc();

// get image here
    get_pokemon(24, SIDE_OPPOSITION);
    get_pokemon(18, SIDE_SELF);
    draw_borders();

    draw_health(48, 75);
    draw_names("Pidgeot", "Arbok");

    message_write("Pidgeot used \"Wing Attack\"", 1);
    message_write("Arbok used \"Wrap\"", 2);
    message_write("Pidgeot used \"Sand Attack\"", 3);
    message_write("Arbok used \"Ice Fang\"", 4);

    updateButtons();

    while(1){
    	if (getFlag(flgupdateButton)){
    		updateButtons();
    		clearFlag(flgupdateButton);
    	}
    	if (getFlag(flgButtonSelected)){
    		// do things with selected button
    		P1OUT ^= 1;
    		clearFlag(flgButtonSelected);
    	}
    }

}
