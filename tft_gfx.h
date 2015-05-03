#include "bsp.h"

#define swap(a, b) { int16_t t = a; a = b; b = t; }

uint16_t cursor_y, cursor_x, textsize, textcolor, textbgcolor, wrap, rotation;

void tft_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void tft_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void tft_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void tft_drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
      uint16_t color);
void tft_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void tft_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
      int16_t delta, uint16_t color);
void tft_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color);
void tft_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color);
void tft_drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
      int16_t radius, uint16_t color);
void tft_fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
void tft_drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
void tft_drawChar(int16_t x, int16_t y, uint8_t c, uint16_t color, uint16_t bg, uint8_t size);
void tft_setCursor(int16_t x, int16_t y);
void tft_setTextColor(uint16_t c);
void tft_setTextColor2(uint16_t c, uint16_t bg);
void tft_setTextSize(uint8_t s);
void tft_setTextWrap(char w);
void tft_gfx_setRotation(uint8_t r);
void tft_write(uint8_t c);
void tft_writeString(char* str);    // This is the function to use to write a string
