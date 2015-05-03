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

#include <msp430.h> 

#include "bsp.h"
#include "tft_master.h"
#include "tft_gfx.h"
#include "game_gfx.h"

#include "spi.h"
#include "diskio.h"
#include "pff.h"

#include "tmr_int.h"
#include "flags.h"

const unsigned long SMCLK_FREQ = 16000000;

void main(void) {

    FATFS fs; /* File system object */
    char buffer[30];
	FRESULT pres;
	DRESULT dres;

	_disable_interrupts();

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	BCSCTL1 = CALBC1_16MHZ;        /* Set DCO for 16 MHz */
	DCOCTL  = CALDCO_16MHZ;

	delay_ms(100);

	// Initialize SD card:
	spi_initialize();
	dres = disk_initialize();

	tft_init_hw();
    tft_begin();

    tft_fillScreen(ILI9340_WHITE);
    tft_setCursor(0, 1);
    tft_setTextColor(ILI9340_BLACK);
    tft_setTextSize(1);

	if (dres){
		sprintf(buffer, "Disk error = %d\n", (int) dres);
		tft_writeString(buffer);
		while (1);
	}

    pres = pf_mount(&fs);
    if (pres){
    	sprintf(buffer, "PFF error 1 = %d\n", (int) pres);
		tft_writeString(buffer);
		while (1);
    }

    tft_fillScreen(ILI9340_WHITE);

    P1DIR |= 3;

// get image here
    get_pokemon(3, 1);
    get_pokemon(8, 0);
    draw_borders();

    draw_health(48, 75);
    draw_names("Martinez", "Rana");

    message_write("Martinez used \"Spaghetti\"", 1);
    message_write("Rana used \"Stick of Honor\"", 2);
    message_write("Martinez used \"Round Robin\"", 3);
    message_write("Rana used \"Phase Margin\"", 4);

    init_button();
    init_systimer();
    initButtons();
    updateButtons();

    _enable_interrupts();


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
