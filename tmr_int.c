/*
 * tmr_int.c
 *
 *  Created on: May 2, 2015
 *      Author: Tahmid
 */

#include "tmr_int.h"
#include "game_gfx.h"
#include "flags.h"

void init_systimer(void){
	TBCTL = TBCLR|		// clear timer b settings
			TBSSEL_2| 	// clock source: SMCLK (16 MHz)
			MC_1|		// count up
			ID_3;		// divide by 8

	TBR = 0;

	ms_time = 0;
	TBCCR0 = 1999;		// 1ms/(8/16MHz)=2000
	TBCCTL0 = CCIE;
}

#pragma vector= TIMERB0_VECTOR
__interrupt void ms_timer_handler (void)
{
	++ms_time;

	if (ms_time > time_btn_enable){
		time_btn_enable = 0; time_btn_enable--; // Make sure this block of code doesn't run unless
												// ISR makes it
		if (!(P1IN & button_pin)){				// Button still pushed
			P1IES = 0;							// Rising edge
		} else {
			P1IES = button_pin;					// Falling edge
		}

		P1IE = button_pin;						// Enable button interrupt
	}

	TBCCTL0 &=	~ CCIFG;						// Clear interrupt flag
}

void init_button(void){
	time_btn_enable = 0; time_btn_enable--;
	time_push = time_btn_enable;
	clearFlag(flgupdateButton);
	P1DIR &= ~button_pin;						// Button input
	P1REN 	= button_pin;						// Enable pull up/down for button
	P1OUT  |= button_pin;						// Enable pull-up for button
	P1IE 	= button_pin;						// Enable button pin interrupt
	P1IES	= button_pin;						// Falling edge
	P1IFG	= 0;
}

#pragma vector= PORT1_VECTOR
__interrupt void button_handler (void)
{
	if (P1IFG & button_pin){
		P1IE 	= 	0;								// Disable all port interrupts
		time_btn_enable = ms_time + DEBOUNCE_PERIOD;
		if (P1IES & button_pin){					// Falling edge
			time_push = ms_time;
		} else { // Rising edge
			if ((ms_time - time_push) > PRESS_TIME){	// long press
				selectedButton = activeButton;
				setFlag(flgButtonSelected);
			} else {	// short press
				if (++activeButton == 5) activeButton = 1;
				setFlag(flgupdateButton);
			}
		}
		P1IFG 	= 	0;								// Clear all port interrupt flags
	}
}
