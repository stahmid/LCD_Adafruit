/*
 * function_prototypes.h
 *
 *  Created on: May 3, 2015
 *      Author: Manish Patel
 */

#ifndef FUNCTION_PROTOTYPES_H_
#define FUNCTION_PROTOTYPES_H_

#include <stdint.h>
#include "typedefs.h"

// main.c
void process_game(void);
void init_uart(void);
void uart_putc(char c);
void uart_puts(char *str);
void uart_clear_screen(void);


// radio.c
void sendMsg(char* msg, uint8_t* dest_address, uint8_t* src_address);
void sleep(unsigned int count);
void receiveInit(uint8_t* address);
void sendID(uint8_t id, uint8_t* dest, uint8_t* source);
void sendAttack(uint8_t attackID, uint8_t* dest, uint8_t* source);
void sendGraphicsUpdate(int16_t hp_max, int16_t hp_left, uint8_t pkmnID, uint8_t* dest, uint8_t* source);
void sendGameOver(uint8_t* dest, uint8_t* source);


#endif /* FUNCTION_PROTOTYPES_H_ */
