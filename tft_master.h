/* Code rewritten from Adafruit Arduino library for the TFT
 *  by Syed Tahmid Mahbub
 * The TFT itself is Adafruit product 1480
 */

#include "bsp.h"
#include "delays.h"

#define _dc         	P5 // this is the pin of the header, not on MSP
#define _dc_output()	{P5_dir |= P5_bit;}
#define _dc_high()  	{P5_out |= P5_bit;}
#define _dc_low()   	{P5_out &= ~P5_bit;}

#define _cs         	P6 // this is the pin of the header, not on MSP
#define _cs_output()	{P6_dir |= P6_bit;}
#define _cs_high()		{P6_out |= P6_bit;}
#define _cs_low()   	{P6_out &= ~P6_bit;}

#define _rst        	P7 // this is the pin of the header, not on MSP
#define _rst_output()	{P7_dir |= P7_bit;}
#define _rst_high() 	{P7_out |= P7_bit;}
#define _rst_low()  	{P7_out &= ~P7_bit;}

#define MISO_input()	{MISO_dir &= ~MISO_bit; MISO_sel |= MISO_bit;}
#define MOSI_output()	{MOSI_dir |= MOSI_bit; MOSI_sel |= MOSI_bit;}
#define SCLK_output()	{SCLK_dir |= SCLK_bit; SCLK_sel |= SCLK_bit;}
#define MOSI_low()		{MOSI_out &= ~MOSI_bit;}
#define SCLK_low()		{SCLK_out &= ~SCLK_bit;}


#define ILI9340_TFTWIDTH  240
#define ILI9340_TFTHEIGHT 320

#define ILI9340_NOP     0x00
#define ILI9340_SWRESET 0x01
#define ILI9340_RDDID   0x04
#define ILI9340_RDDST   0x09

#define ILI9340_SLPIN   0x10
#define ILI9340_SLPOUT  0x11
#define ILI9340_PTLON   0x12
#define ILI9340_NORON   0x13

#define ILI9340_RDMODE  0x0A
#define ILI9340_RDMADCTL  0x0B
#define ILI9340_RDPIXFMT  0x0C
#define ILI9340_RDIMGFMT  0x0A
#define ILI9340_RDSELFDIAG  0x0F

#define ILI9340_INVOFF  0x20
#define ILI9340_INVON   0x21
#define ILI9340_GAMMASET 0x26
#define ILI9340_DISPOFF 0x28
#define ILI9340_DISPON  0x29

#define ILI9340_CASET   0x2A
#define ILI9340_PASET   0x2B
#define ILI9340_RAMWR   0x2C
#define ILI9340_RAMRD   0x2E

#define ILI9340_PTLAR   0x30
#define ILI9340_MADCTL  0x36


#define ILI9340_MADCTL_MY  0x80
#define ILI9340_MADCTL_MX  0x40
#define ILI9340_MADCTL_MV  0x20
#define ILI9340_MADCTL_ML  0x10
#define ILI9340_MADCTL_RGB 0x00
#define ILI9340_MADCTL_BGR 0x08
#define ILI9340_MADCTL_MH  0x04

#define ILI9340_PIXFMT  0x3A

#define ILI9340_FRMCTR1 0xB1
#define ILI9340_FRMCTR2 0xB2
#define ILI9340_FRMCTR3 0xB3
#define ILI9340_INVCTR  0xB4
#define ILI9340_DFUNCTR 0xB6

#define ILI9340_PWCTR1  0xC0
#define ILI9340_PWCTR2  0xC1
#define ILI9340_PWCTR3  0xC2
#define ILI9340_PWCTR4  0xC3
#define ILI9340_PWCTR5  0xC4
#define ILI9340_VMCTR1  0xC5
#define ILI9340_VMCTR2  0xC7

#define ILI9340_RDID1   0xDA
#define ILI9340_RDID2   0xDB
#define ILI9340_RDID3   0xDC
#define ILI9340_RDID4   0xDD

#define ILI9340_GMCTRP1 0xE0
#define ILI9340_GMCTRN1 0xE1
/*
#define ILI9340_PWCTR6  0xFC

 */

// Color definitions
#define	ILI9340_BLACK   0x0000
#define	ILI9340_BLUE    0x001F
#define	ILI9340_RED     0xF800
#define ILI9340_ORANGE	((255 << 11) | (102 << 5)) // orange RGB = 255,102,0
#define	ILI9340_GREEN   0x07E0
#define ILI9340_CYAN    0x07FF
#define ILI9340_MAGENTA 0xF81F
#define ILI9340_YELLOW  0xFFE0
#define ILI9340_WHITE   0xFFFF

#define tabspace 4 // number of spaces for a tab

void tft_init_hw(void);
void tft_spiwrite8(uint8_t c);
void tft_spiwrite16(uint16_t c);
void tft_writecommand(uint8_t c);
void tft_writecommand16(uint16_t c);
void tft_writedata(uint8_t c);
void tft_writedata16(uint16_t c);
void tft_commandList(uint8_t *addr);
void tft_begin(void);
void tft_setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void tft_pushColor(uint16_t color);
void tft_drawPixel(int16_t x, int16_t y, uint16_t color);
void tft_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
//void tft_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void tft_fillScreen(uint16_t color);
//void tft_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
uint16_t tft_Color565(uint8_t r, uint8_t g, uint8_t b);
void tft_setRotation(uint8_t m);
uint8_t tft_spiread(void);
uint8_t tft_readdata(void);
uint8_t tft_readcommand8(uint8_t c);

uint16_t _width, _height;


