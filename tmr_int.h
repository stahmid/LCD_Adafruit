/*
 * tmr_int.h
 *
 *  Created on: May 2, 2015
 *      Author: Tahmid
 */

#ifndef TMR_INT_H_
#define TMR_INT_H_

#include "bsp.h"

#define button_pin	BIT2

volatile uint8_t selectedButton;

void init_systimer(void);
volatile uint32_t ms_time;

void init_button(void);

#define DEBOUNCE_PERIOD	30 	// debounce period in ms
#define PRESS_TIME 250 // how long to hold down button to register as long push
volatile uint32_t time_btn_enable;
volatile uint32_t time_push;

#endif /* TMR_INT_H_ */
