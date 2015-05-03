/*
 * delays.c
 *
 *  Created on: May 3, 2015
 *      Author: Tahmid
 */

#include "delays.h"

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

