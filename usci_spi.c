/**
 * File: usci_spi.c - msp430 USCI SPI implementation
 *
 */
#include <stdint.h>
#include "spi.h"

#ifndef __MSP430_HAS_USCI__
#error "Error! This MCU doesn't have a USCI peripheral"
#endif

/**
 * USCI flags for various the SPI MODEs
 *
 * Note: The msp430 UCCKPL tracks the CPOL value. However,
 * the UCCKPH flag is inverted when compared to the CPHA
 * value described in Motorola documentation.
 */

#define SPI_MODE_0 (UCMSB | UCMST | UCSYNC | UCCKPH)			/* CPOL=0 CPHA=0 */
#define SPI_MODE_1 (UCMSB | UCMST | UCSYNC)         			/* CPOL=0 CPHA=1 */
#define SPI_MODE_2 (UCMSB | UCMST | UCSYNC | UCCKPL | UCCKPH)	/* CPOL=1 CPHA=0 */
#define SPI_MODE_3 (UCMSB | UCMST | UCSYNC | UCCKPL)			/* CPOL=1 CPHA=1 */

/**
 * utility macros for extracting hi/lo byte data from a word value
 */
#ifndef LOBYTE
#define LOBYTE(w) ((w)&0xFF)
#define HIBYTE(w) ((w)>>8)
#endif

/**
 * spi_initialize() - Configure USCI UCB0 for SPI mode
 *
 * P4.5 - CS (active low)
 * P3.3 - SCLK
 * P3.2 - SIMO/MOSI
 * P3.1 - SOMI/MISO
 */
void spi_initialize(void) {
    UCB0CTL1 = UCSWRST | UCSSEL_2; // Put USCI in reset mode, source USCI clock from SMCLK
    UCB0CTL0 = SPI_MODE_0; // Use SPI MODE 0 - CPOL=0 CPHA=0

    P3SEL |= BIT3 | BIT2 | BIT1;

    UCB0BR0 = LOBYTE(SPI_400kHz); // set initial speed to 400kHz (16MHz/400000)
    UCB0BR1 = HIBYTE(SPI_400kHz);

    P8_out |= P8_bit; // CS start out disabled
    P8_dir |= P8_bit; // CS configured as output

    UCB0CTL1 &= ~UCSWRST; // release USCI for operation
}

/**
 * spi_send() - send a byte and recv response
 */
uint8_t spi_send(const uint8_t c) {
    while (!(IFG2 & UCB0TXIFG))
        ; // wait for previous tx to complete

    UCB0TXBUF = c; // setting TXBUF clears the TXIFG flag

    while (!(IFG2 & UCB0RXIFG))
        ; // wait for an rx character?

    return UCB0RXBUF; // reading clears RXIFG flag
}

/**
 * spi_receive() - send dummy btye then recv response
 */

uint8_t spi_receive(void) {

    while (!(IFG2 & UCB0TXIFG))
        ; // wait for any previous xmits to complete

    UCB0TXBUF = 0xFF; // Send dummy packet to get data back.

    while (!(IFG2 & UCB0RXIFG))
        ; // wait to recv a character?

    return UCB0RXBUF; // reading clears RXIFG flag
}

/**
 * spi_set_divisor() - set new clock divider for USCI
 *
 * USCI speed is based on the SMCLK divided by BR0 and BR1
 * initially we start slow (400kHz) to conform to SDCard
 * specifications then we speed up once initialized (SPI_DEFAULT_SPEED)
 *
 * returns the previous setting
 */

uint16_t spi_set_divisor(const uint16_t clkdiv) {
    uint16_t prev_clkdiv = UCB0BR1 << 8 | UCB0BR0;

    UCB0CTL1 |= UCSWRST; // go into reset state
    UCB0BR0 = LOBYTE(clkdiv);
    UCB0BR1 = HIBYTE(clkdiv);
    UCB0CTL1 &= ~UCSWRST; // release for operation

    return prev_clkdiv;
}
