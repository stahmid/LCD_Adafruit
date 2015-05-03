/* Code rewritten from Adafruit Arduino library for the TFT
 *  by Syed Tahmid Mahbub
 * The TFT itself is Adafruit product 1480
 *
 */

#include "tft_master.h"

void tft_init_hw(void) {
	_width = ILI9340_TFTWIDTH;
	_height = ILI9340_TFTHEIGHT;

/* Initializing the module (from the MSP430 User's Guide):
	1. Set UCSWRST (BIS.B #UCSWRST,&UCxCTL1)
	2. Initialize all USCI registers with UCSWRST=1 (including UCxCTL1)
	3. Configure ports
	4. Clear UCSWRST via software (BIC.B #UCSWRST,&UCxCTL1)
	5. Enable interrupts (optional) via UCxRXIE and/or UCxTXIE
*/
//	UCB0CTL1 = UCSSEL_2 | UCSWRST;
	/* Use SMCLK
	 * Software reset enabled
	 */
//	UCB0CTL0 = UCMST | UCSYNC | UCCKPH | UCMSB;
	/* Data captured on 1st UCLK edge and changed on following edge.
	 * Inactive clock state is low.
	 * MSB first
	 * 8-bit data
	 * Master Mode
	 * 3-pin SPI : 4-pin SPI would enable radio so, we'll handle CS in software.
	 * Synchronous mode: for SPI
	 */
//	UCB0BR0 = 2;
//	UCB0BR1 = 0;
	/* Clock division factor of 2
	 * f_spi = f_BRCLK/2
	 * In UCB0CTL1, BRCLK source is selected
	 */

//	MOSI_output();
//	SCLK_output();
//	MOSI_low();
//	SCLK_low();

//	UCB0CTL1 &= ~UCSWRST;
}

void tft_spiwrite8(uint8_t c) {   // Transfer one byte c to SPI
	UCB0TXBUF = c;
	while (TxBufFull());
	while (SpiBusy());	// wait for it to end of transaction
}

void tft_spiwrite16(uint16_t c){  // Transfer two bytes "c" to SPI
	tft_spiwrite8(c >> 8);
	tft_spiwrite8(c & 0xFF);
}


void tft_writecommand(uint8_t c) {
	_dc_low();
	_cs_low();

	tft_spiwrite8(c);

	_cs_high();

}

void tft_writecommand16(uint16_t c) {
	_dc_low();
	_cs_low();

	tft_spiwrite16(c);

	_cs_high();

}


void tft_writedata(uint8_t c) {
	_dc_high();
	_cs_low();

	tft_spiwrite8(c);

	_cs_high();

}

void tft_writedata16(uint16_t c) {
	_dc_high();
	_cs_low();

	tft_spiwrite16(c);

	_cs_high();

}

// Rather than a bazillion writecommand() and writedata() calls, screen
// initialization commands and arguments are organized in these tables
// stored in PROGMEM.  The table may look bulky, but that's mostly the
// formatting -- storage-wise this is hundreds of bytes more compact
// than the equivalent code.  Companion function follows.
#define DELAY 0x80

void tft_begin(void) {

	_rst_output();
	_rst_low();
	_dc_output();
	_cs_output();

	_dc_low();
	_cs_high();

	_rst_high();
	delay_ms(5);
	_rst_low();
	delay_ms(20);
	_rst_high();
	delay_ms(150);

	tft_writecommand(0xEF);
	tft_writedata(0x03);
	tft_writedata(0x80);
	tft_writedata(0x02);

	tft_writecommand(0xCF);
	tft_writedata(0x00);
	tft_writedata(0xC1);
	tft_writedata(0x30);

	tft_writecommand(0xED);
	tft_writedata(0x64);
	tft_writedata(0x03);
	tft_writedata(0x12);
	tft_writedata(0x81);

	tft_writecommand(0xE8);
	tft_writedata(0x85);
	tft_writedata(0x00);
	tft_writedata(0x78);

	tft_writecommand(0xCB);
	tft_writedata(0x39);
	tft_writedata(0x2C);
	tft_writedata(0x00);
	tft_writedata(0x34);
	tft_writedata(0x02);

	tft_writecommand(0xF7);
	tft_writedata(0x20);

	tft_writecommand(0xEA);
	tft_writedata(0x00);
	tft_writedata(0x00);

	tft_writecommand(ILI9340_PWCTR1);    //Power control
	tft_writedata(0x23);   //VRH[5:0]

	tft_writecommand(ILI9340_PWCTR2);    //Power control
	tft_writedata(0x10);   //SAP[2:0];BT[3:0]

	tft_writecommand(ILI9340_VMCTR1);    //VCM control
	tft_writedata(0x3e);
	tft_writedata(0x28);

	tft_writecommand(ILI9340_VMCTR2);    //VCM control2
	tft_writedata(0x86);

	tft_writecommand(ILI9340_MADCTL);    // Memory Access Control
	tft_writedata(ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);

	tft_writecommand(ILI9340_PIXFMT);
	tft_writedata(0x55);

	tft_writecommand(ILI9340_FRMCTR1);
	tft_writedata(0x00);
	tft_writedata(0x18);

	tft_writecommand(ILI9340_DFUNCTR);    // Display Function Control
	tft_writedata(0x08);
	tft_writedata(0x82);
	tft_writedata(0x27);

	tft_writecommand(0xF2);    // 3Gamma Function Disable
	tft_writedata(0x00);

	tft_writecommand(ILI9340_GAMMASET);    //Gamma curve selected
	tft_writedata(0x01);

	tft_writecommand(ILI9340_GMCTRP1);    //Set Gamma
	tft_writedata(0x0F);
	tft_writedata(0x31);
	tft_writedata(0x2B);
	tft_writedata(0x0C);
	tft_writedata(0x0E);
	tft_writedata(0x08);
	tft_writedata(0x4E);
	tft_writedata(0xF1);
	tft_writedata(0x37);
	tft_writedata(0x07);
	tft_writedata(0x10);
	tft_writedata(0x03);
	tft_writedata(0x0E);
	tft_writedata(0x09);
	tft_writedata(0x00);

	tft_writecommand(ILI9340_GMCTRN1);    //Set Gamma
	tft_writedata(0x00);
	tft_writedata(0x0E);
	tft_writedata(0x14);
	tft_writedata(0x03);
	tft_writedata(0x11);
	tft_writedata(0x07);
	tft_writedata(0x31);
	tft_writedata(0xC1);
	tft_writedata(0x48);
	tft_writedata(0x08);
	tft_writedata(0x0F);
	tft_writedata(0x0C);
	tft_writedata(0x31);
	tft_writedata(0x36);
	tft_writedata(0x0F);

	tft_writecommand(ILI9340_SLPOUT);    //Exit Sleep
	delay_ms(120);
	tft_writecommand(ILI9340_DISPON);    //Display on


}


void tft_setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {

	tft_writecommand(ILI9340_CASET); // Column addr set
	tft_writedata16(x0);
	tft_writedata16(x1);

	tft_writecommand(ILI9340_PASET); // Row addr set
	tft_writedata16(y0);
	tft_writedata16(y1);

	tft_writecommand(ILI9340_RAMWR); // write to RAM
}


void tft_pushColor(uint16_t color) {
	_dc_high();
	_cs_low();

	tft_spiwrite16(color);

	_cs_high();
}

void tft_drawPixel(int16_t x, int16_t y, uint16_t color) {
	/* Draw a pixel at location (x,y) with given color
	 * Parameters:
	 *      x:  x-coordinate of pixel to draw; top left of screen is x=0
	 *              and x increases to the right
	 *      y:  y-coordinate of pixel to draw; top left of screen is y=0
	 *              and y increases to the bottom
	 *      color:  16-bit color value
	 * Returns:     Nothing
	 */

	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) return;

	tft_setAddrWindow(x,y,x+1,y+1);

	_dc_high();
	_cs_low();

	tft_spiwrite16(color);

	_cs_high();
}


void tft_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	/* Draw a vertical line at location from (x,y) to (x,y+h-1) with color
	 * Parameters:
	 *      x:  x-coordinate line to draw; top left of screen is x=0
	 *              and x increases to the right
	 *      y:  y-coordinate of starting point of line; top left of screen is y=0
	 *              and y increases to the bottom
	 *      h:  height of line to draw
	 *      color:  16-bit color value
	 * Returns:     Nothing
	 */

	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) return;

	if((y+h-1) >= _height)
		h = _height-y;

	tft_setAddrWindow(x, y, x, y+h-1);

	_dc_high();
	_cs_low();

	while (h--) {
		tft_spiwrite16(color);
	}

	_cs_high();
}


void tft_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
	/* Draw a horizontal line at location from (x,y) to (x+w-1,y) with color
	 * Parameters:
	 *      x:  x-coordinate starting point of line; top left of screen is x=0
	 *              and x increases to the right
	 *      y:  y-coordinate of starting point of line; top left of screen is y=0
	 *              and y increases to the bottom
	 *      w:  width of line to draw
	 *      color:  16-bit color value
	 * Returns:     Nothing
	 */

	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) return;
	if((x+w-1) >= _width)  w = _width-x;
	tft_setAddrWindow(x, y, x+w-1, y);

	_dc_high();
	_cs_low();

	while (w--) {
		tft_spiwrite16(color);
	}

	_cs_high();
}

void tft_fillScreen(uint16_t color) {
	/* Fill entire screen with given color
	 * Parameters:
	 *      color: 16-bit color value
	 * Returs:  Nothing
	 */
	tft_fillRect(0, 0,  _width, _height, color);
}

// fill a rectangle
void tft_fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
		uint16_t color) {
	/* Draw a filled rectangle with starting top-left vertex (x,y),
	 *  width w and height h with given color
	 * Parameters:
	 *      x:  x-coordinate of top-left vertex; top left of screen is x=0
	 *              and x increases to the right
	 *      y:  y-coordinate of top-left vertex; top left of screen is y=0
	 *              and y increases to the bottom
	 *      w:  width of rectangle
	 *      h:  height of rectangle
	 *      color:  16-bit color value
	 * Returns:     Nothing
	 */

	// rudimentary clipping (drawChar w/big text requires this)
	if((x >= _width) || (y >= _height)) return;
	if((x + w - 1) >= _width)  w = _width  - x;
	if((y + h - 1) >= _height) h = _height - y;

	tft_setAddrWindow(x, y, x+w-1, y+h-1);

	_dc_high();
	_cs_low();

	for(y=h; y>0; y--) {
		for(x=w; x>0; x--) {
			tft_spiwrite16(color);
		}
	}

	_cs_high();
}

inline uint16_t tft_Color565(uint8_t r, uint8_t g, uint8_t b) {
	/* Pass 8-bit (each) R,G,B, get back 16-bit packed color
	 * Parameters:
	 *      r:  8-bit R/red value from RGB
	 *      g:  8-bit g/green value from RGB
	 *      b:  8-bit b/blue value from RGB
	 * Returns:
	 *      16-bit packed color value for color info
	 */
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


void tft_setRotation(uint8_t m) {
	uint8_t rotation;
	tft_writecommand(ILI9340_MADCTL);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) {
	case 0:
		tft_writedata(ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);
		_width  = ILI9340_TFTWIDTH;
		_height = ILI9340_TFTHEIGHT;
		break;
	case 1:
		tft_writedata(ILI9340_MADCTL_MV | ILI9340_MADCTL_BGR);
		_width  = ILI9340_TFTHEIGHT;
		_height = ILI9340_TFTWIDTH;
		break;
	case 2:
		tft_writedata(ILI9340_MADCTL_MY | ILI9340_MADCTL_BGR);
		_width  = ILI9340_TFTWIDTH;
		_height = ILI9340_TFTHEIGHT;
		break;
	case 3:
		tft_writedata(ILI9340_MADCTL_MV | ILI9340_MADCTL_MY | ILI9340_MADCTL_MX | ILI9340_MADCTL_BGR);
		_width  = ILI9340_TFTHEIGHT;
		_height = ILI9340_TFTWIDTH;
		break;
	}
}

void delay_ms(uint16_t i){
	uint16_t j;
	for (j=0; j<i; j++){
		__delay_cycles(16000); // 1ms
	}
}

void delay_us(uint16_t i){
	uint16_t j;
	for (j=0; j<(i<<2); j++){ // (i>>2)*16 = i<<2
		_nop();
	}
}
