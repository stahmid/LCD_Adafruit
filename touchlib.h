/*
 * File:   touchlib.h
 * Author: Syed Tahmid Mahbub
 *
 * Created on November 16, 2014
 */

#ifndef TOUCHLIB_H
#define	TOUCHLIB_H

#include "bsp.h"
#include "tft_master.h"

#define pressureThreshold   50

typedef struct point{
    uint16_t tp_x;
    uint16_t tp_y;
    uint16_t tp_z;
} touchpoint_t;

uint16_t ts_readY(void);
uint16_t ts_readX(void);
void ts_getPoint(touchpoint_t* tp);

uint16_t analogRead_touch(uint8_t ch);

int16_t comp (const void * elem1, const void * elem2);
uint16_t findmedian(uint16_t* x);

/* xp and yp must be connected to analog inputs
 * xm and ym don't need to be
 * Analog reads are only done with xp and yp
 */
#define _xp_ADC_CH		P10_adc_ch
#define _yp_ADC_CH		P11_adc_ch

// P11
#define _yp_INPUT() 	{P11_dir &= ~P11_bit;}
#define _yp_OUTPUT() 	{P11_dir |= P11_bit;}
#define _yp_ANALOG()	{P11_sel |= P11_bit; ADC10AE1 |= BIT7;}
#define _yp_DIGITAL() 	{P11_sel &= ~P11_bit; ADC10AE1 &= ~BIT7;}
#define _yp_PD() 		{P11_ren |= P11_bit; P11_out |= P11_bit;}
#define _yp_noPD() 		{P11_ren &= ~P11_bit;}
#define _yp_HIGH() 		{P11_out |= P11_bit;}
#define _yp_LOW() 		{P11_out &= ~P11_bit;}

// P10
#define _xp_INPUT() 	{P10_dir &= ~P10_bit;}
#define _xp_OUTPUT()	{P10_dir |= P10_bit;}
#define _xp_ANALOG() 	{P10_sel |= P10_bit; ADC10AE1 |= BIT6;}
#define _xp_DIGITAL() 	{P10_sel &= ~P10_bit; ADC10AE1 &= ~BIT6;}
#define _xp_PD() 		{P10_ren |= P10_bit; P10_out |= P10_bit;}
#define _xp_noPD() 		{P10_ren &= ~P10_bit;}
#define _xp_HIGH() 		{P10_out |= P10_bit;}
#define _xp_LOW() 		{P10_out &= ~P10_bit;}

// P13
#define _ym_INPUT() 	{P13_dir &= ~P13_bit;}
#define _ym_OUTPUT() 	{P13_dir |= P13_bit;}
#define _ym_DIGITAL()	{P13_sel &= ~P13_bit;}
#define _ym_PD() 		{P13_ren |= P13_bit; P13_out |= P13_bit;}
#define _ym_noPD() 		{P13_ren &= ~P13_bit;}
#define _ym_HIGH() 		{P13_out |= P13_bit;}
#define _ym_LOW() 		{P13_out &= ~P13_bit;}

// P14
#define _xm_INPUT() 	{P14_dir &= ~P14_bit;}
#define _xm_OUTPUT() 	{P14_dir |= P14_bit;}
#define _xm_DIGITAL()	{P14_sel &= ~P14_bit;}
#define _xm_PD() 		{P14_ren |= P14_bit; P14_out |= P14_bit;}
#define _xm_noPD() 		{P14_ren &= ~P14_bit;}
#define _xm_HIGH() 		{P14_out |= P14_bit;}
#define _xm_LOW() 		{P14_out &= ~P14_bit;}

#endif	/* TOUCHLIB_H */

