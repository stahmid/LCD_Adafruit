/*
 * setup.c
 *
 *  Created on: May 3, 2015
 *      Author: Tahmid
 */

#include "setup.h"

const unsigned long SMCLK_FREQ = 16000000;

void setup_lcd_fs(void){

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

    P1DIR |= BIT0 | BIT1;
    P1OUT &= ~ (BIT0 | BIT1);

}

void setup_timer_buttons(void){
    init_button();
    init_systimer();
    initButtons();

    _enable_interrupts();
}
