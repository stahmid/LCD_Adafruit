/*
 * bsp.h
 *
 *  Created on: Apr 22, 2015
 *      Author: Tahmid
 */

#include <msp430.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifndef BSP_H_
#define BSP_H_

#define P3_out		P2OUT
#define P4_out		P2OUT
#define P5_out		P2OUT
#define P6_out		P2OUT
#define P7_out		P2OUT
#define P8_out		P4OUT
#define P9_out		P4OUT
#define P10_out		P4OUT
#define P11_out		P4OUT
#define P13_out		P2OUT
#define P14_out		P2OUT
#define P15_out		P3OUT
#define P16_out		P3OUT
#define P17_out		P3OUT
#define P18_out		P3OUT

#define P3_in		P2IN
#define P4_in		P2IN
#define P5_in		P2IN
#define P6_in		P2IN
#define P7_in		P2IN
#define P8_in		P4IN
#define P9_in		P4IN
#define P10_in		P4IN
#define P11_in		P4IN
#define P13_in		P2IN
#define P14_in		P2IN
#define P15_in		P3IN
#define P16_in		P3IN
#define P17_in		P3IN
#define P18_in		P3IN

#define P3_dir		P2DIR
#define P4_dir		P2DIR
#define P5_dir		P2DIR
#define P6_dir		P2DIR
#define P7_dir		P2DIR
#define P8_dir		P4DIR
#define P9_dir		P4DIR
#define P10_dir		P4DIR
#define P11_dir		P4DIR
#define P13_dir		P2DIR
#define P14_dir		P2DIR
#define P15_dir		P3DIR
#define P16_dir		P3DIR
#define P17_dir		P3DIR
#define P18_dir		P3DIR

#define P3_bit		BIT0
#define P4_bit		BIT1
#define P5_bit		BIT2
#define P6_bit		BIT3
#define P7_bit		BIT4
#define P8_bit		BIT3
#define P9_bit		BIT4
#define P10_bit		BIT5
#define P11_bit		BIT6
#define P13_bit		BIT6
#define P14_bit		BIT7
#define P15_bit		BIT2
#define P16_bit		BIT3
#define P17_bit		BIT0
#define P18_bit		BIT1

#define P3_sel		P2SEL
#define P4_sel		P2SEL
#define P5_sel		P2SEL
#define P6_sel		P2SEL
#define P7_sel		P2SEL
#define P8_sel		P4SEL
#define P9_sel		P4SEL
#define P10_sel		P4SEL
#define P11_sel		P4SEL
#define P13_sel		P2SEL
#define P14_sel		P2SEL
#define P15_sel		P3SEL
#define P16_sel		P3SEL
#define P17_sel		P3SEL
#define P18_sel		P3SEL

#define P3_sel2		P2SEL2
#define P4_sel2		P2SEL2
#define P5_sel2		P2SEL2
#define P6_sel2		P2SEL2
#define P7_sel2		P2SEL2
#define P8_sel2		P4SEL2
#define P9_sel2		P4SEL2
#define P10_sel2	P4SEL2
#define P11_sel2	P4SEL2
#define P13_sel2	P2SEL2
#define P14_sel2	P2SEL2
#define P15_sel2	P3SEL2
#define P16_sel2	P3SEL2
#define P17_sel2	P3SEL2
#define P18_sel2	P3SEL2

#define P3_ren		P2REN
#define P4_ren		P2REN
#define P5_ren		P2REN
#define P6_ren		P2REN
#define P7_ren		P2REN
#define P8_ren		P4REN
#define P9_ren		P4REN
#define P10_ren		P4REN
#define P11_ren		P4REN
#define P13_ren		P2REN
#define P14_ren		P2REN
#define P15_ren		P3REN
#define P16_ren		P3REN
#define P17_ren		P3REN
#define P18_ren		P3REN

#define P3_adc_ch	0
#define P4_adc_ch	1
#define P5_adc_ch	2
#define P6_adc_ch	3
#define P7_adc_ch	4
#define P8_adc_ch	12
#define P9_adc_ch	13
#define P10_adc_ch	14
#define P11_adc_ch	15


#define MOSI_out	P18_out
#define MOSI_in		P18_in
#define MOSI_dir	P18_dir
#define MOSI_bit	P18_bit
#define MOSI_sel	P18_sel
#define MOSI_sel2	P18_sel2

#define MISO_out	P15_out
#define MISO_in		P15_in
#define MISO_dir	P15_dir
#define MISO_bit	P15_bit
#define MISO_sel	P15_sel
#define MISO_sel2	P15_sel2

#define SCLK_out	P16_out
#define SCLK_in		P16_in
#define SCLK_dir	P16_dir
#define SCLK_bit	P16_bit
#define SCLK_sel	P16_sel
#define SCLK_sel2	P16_sel2

#define TxBufFull() (!(IFG2 & UCB0TXIFG))
#define SpiBusy()	(UCB0STAT & UCBUSY)

#endif /* BSP_H_ */
