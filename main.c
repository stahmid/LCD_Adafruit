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

// get image here
    get_pokemon(3, SIDE_OPPOSITION);
    get_pokemon(8, SIDE_SELF);
    draw_borders();

    draw_health(48, 75);
    draw_names("Martinez", "Rana");

    message_write("Martinez used \"Spaghetti\"", 1);
    message_write("Rana used \"Stick of Honor\"", 2);
    message_write("Martinez used \"Round Robin\"", 3);
    message_write("Rana used \"Phase Margin\"", 4);

//    setup_timer_buttons();
    updateButtons();

    get_pokemon(25, SIDE_OPPOSITION);
    get_pokemon(19, SIDE_SELF);
    draw_borders();

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
