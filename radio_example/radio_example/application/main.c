#include <msp430.h>

#include "globals.h"

#include "function_prototypes.h"
#include "attacks.h"
#include <stdlib.h>

// radio includes
#include "bsp.h"
#include "mrfi.h"
#include "radios/family1/mrfi_spi.h"
#include <string.h>

#include "parser.h"

uint16_t flagReg;

attack_t received_attack;
pokemon_data_t opp_pkmn;
pokemon_team_t pkmn1;

/*
 * main.c
 */

// radio definitons and variables
uint8_t dest[] = {0x12,0x34,0xab,0xcd};
uint8_t source[] = {0x02,0x00,0x01,0x02};

void main(void) {

	//init_uart();
	//uart_clear_screen();
	//uart_puts("The UART works woohoo");

	//WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	/* Perform board-specific initialization */

	BSP_Init();

	/* Initialize minimal RF interface, wake up radio */
	MRFI_Init();
	MRFI_WakeUp();
	receiveInit(source);

	P1DIR = 0x03;

	__bis_SR_register(GIE);

	/*
	while(1) {
		P1OUT = 0x01;
		__delay_cycles(1000000UL);
		while(rfDone() == 0);
		P1OUT = 0x02;
		__delay_cycles(1000000UL);
		flagReg ^= rfDone_bit;
		sendID(1, dest, source);
	}
	 */
	/*
	while(1) {
		sendID(2, dest, source);
		P1OUT = 0x01;
		__delay_cycles(1000000UL);
		while(rfDone() == 0);
		P1OUT = 0x02;
		__delay_cycles(1000000UL);
		flagReg ^= rfDone_bit;
	}
	 */

	// Initialize SD card:
	BCSCTL1 = CALBC1_16MHZ;        /* Set DCO for 16 MHz */
		DCOCTL  = CALDCO_16MHZ;
		spi_initialize();
		disk_initialize();
		FATFS fs;
		pf_mount(&fs);

	pkmn1 = get_pokemon_team(5);
	char buffer[40];
	sprintf(buffer, "My pokemon is %d", pkmn1.id);
	uart_puts(buffer);
	//pkmn1 = get_pokemon_team(25);
	process_game();

	while(1);
}

/*
 * Returns the effectiveness multiplier of an attack of type 1 against a pokemon
 * of types 2 and 3.
 */
float getEffectiveness(uint16_t type1, uint16_t type2, uint16_t type3) {
	float temp1 = (float)(typeMatrix[type1-1][type2-1]) / 2.0;
	float temp2 = (type3 != NULL) ? ( (float)(typeMatrix[type1-1][type3-1]) / 2.0 ) : (1.0);
	return temp1 * temp2;
}

/*
 * Damage calculated using the formula from this website:
 * http://bulbapedia.bulbagarden.net/wiki/Damage#Damage_formula. Level is set
 * to 50 for all pokemon. Critical hits and randomness modifier omitted for
 * simplicity.
 */
uint16_t calculateDamage(uint8_t attackerID, uint8_t attackID) {

	/*
	 * REMEMBER TO ACCOUNT FOR SPECIAL ATTACK AND SPECIAL DEFENSE
	 */
	float temp1 = ((2.0 * 50.0 + 10.0) / 250.0);

	attack_t attack = get_attacks(attackID);
	pokemon_data_t attacker = get_pokemon_data(attackerID);
	pokemon_data_t defender = get_pokemon_data(pkmn1.id);

	float temp2 = ((float)(attacker.attack))/((float)(defender.defense));
	float temp3 = getEffectiveness(attack.type, defender.type1, defender.type2);
	if(attacker.type1 == attack.type || attacker.type2 == attack.type) {
		temp3 *= 1.5;
	}

	return (uint16_t)( (temp1*temp2*(float)(attack.power) + 2.0) * temp3);
}

void process_game(void) {
	while(1) {
		sendID(pkmn1.id, dest, source);
		// wait until opponent's id is received via RF
		while(rfDone() == 0);
		flagReg ^= rfDone_bit;			// toggle rfDone bit back to low. Make sure to set rfDone_bit to zero in RF ISR
		//send active pokemon's id to opponent via RF


		if(opp_pkmn.speed > pkmn1.speed) {
			while(rfDone() == 0);
			flagReg ^= rfDone_bit;

			// calculate damage done, update hp
			pkmn1.hp_left = pkmn1.hp_left - calculateDamage(opp_pkmn.id, received_attack.id);
			char buffer[40];
			sprintf(buffer, "My remaining health: %d", pkmn1.hp_left);
			uart_puts(buffer);
			if(pkmn1.hp_left < 0) {
				// send termination signal via RF
				sendGameOver(dest, source);
				P1OUT = 0x01;		// red LED to indicate loss
				// update graphics to display loss
			}
			else {
				sendGraphicsUpdate(pkmn1.hp_max, pkmn1.hp_left, pkmn1.id, dest, source);
				// wait for user to select attack
				sendAttack(2, dest, source);

				// block for graphics update / victory signal
				while(rfDone()==0);
				flagReg ^= rfDone_bit;

				if(gameOver()) {
					P1OUT = 0x02;
					break;
				}
				else {
					// update opponent graphics
				}
			}
		}
		else if(opp_pkmn.speed < pkmn1.speed){
			// wait for user to select attack
			// send attack via RF
			sendAttack(1, dest, source);
			// block until RF signal for graphics update / victory signal
			while(rfDone()==0);
			flagReg ^= rfDone_bit;

			if(gameOver()) {
				P1OUT = 0x02;
				break;
			}
			else {
				// update opponent graphics
			}

			// block until opponent attack is sent
			while(rfDone() == 0);
			flagReg ^= rfDone_bit;

			// calculate damage done, update hp
			pkmn1.hp_left = pkmn1.hp_left - calculateDamage(opp_pkmn.id, received_attack.id);
			char buffer[40];
			sprintf(buffer, "My remaining health: %d", pkmn1.hp_left);
			uart_puts(buffer);
			if(pkmn1.hp_left < 0) {
				// send termination signal via RF
				sendGameOver(dest, source);
				P1OUT = 0x01;		// red LED to indicate loss
				// update graphics to display loss
			}
			else {
				sendGraphicsUpdate(pkmn1.hp_max, pkmn1.hp_left, pkmn1.id, dest, source);
			}
		}
	}
}


uint8_t parseType(char* type) {
	if(strcmp(type, "Normal"))
		return NORMAL;
	else if(strcmp(type, "Fight"))
		return FIGHT;
	else if(strcmp(type, "Flying"))
		return FLYING;
	else if(strcmp(type, "Poison"))
		return GROUND;
	else if(strcmp(type, "Rock"))
		return ROCK;
	else if(strcmp(type, "Bug"))
		return BUG;
	else if(strcmp(type, "Ghost"))
		return GHOST;
	else if(strcmp(type, "Steel"))
		return STEEL;
	else if(strcmp(type, "Fire"))
		return FIRE;
	else if(strcmp(type, "Water"))
		return WATER;
	else if(strcmp(type, "Grass"))
		return GRASS;
	else if(strcmp(type, "Electr"))
		return ELECTR;
	else if(strcmp(type, "Psychc"))
		return PSYCHC;
	else if(strcmp(type, "Ice"))
		return ICE;
	else if(strcmp(type, "Dragon"))
		return DRAGON;
	else if(strcmp(type, "Dark"))
		return DARK;
	else if(strcmp(type, "Fairy"))
		return FAIRY;
	else
		return 0;
}

/* Initialize the UART for TX (9600, 8N1) */
/* Settings taken from TI UART demo */
void init_uart(void) {
	BCSCTL1 = CALBC1_1MHZ;        /* Set DCO for 1 MHz */
	DCOCTL  = CALDCO_1MHZ;
	P3SEL = 0x30;                 /* P3.4,5 = USCI_A0 TXD/RXD */
	UCA0CTL1 |= UCSSEL_2;         /* SMCLK */
	UCA0BR0 = 104;                /* 1MHz 9600 */
	UCA0BR1 = 0;                  /* 1MHz 9600 */
	UCA0MCTL = UCBRS0;            /* Modulation UCBRSx = 1 */
	UCA0CTL1 &= ~UCSWRST;         /* Initialize USCI state machine */
}

/* Transmit a single character over UART interface */
void uart_putc(char c) {
	while(!(IFG2 & UCA0TXIFG)); /* Wait for TX buffer to empty */
	UCA0TXBUF = c;				/* Transmit character */
}

/* Transmit a nul-terminated string over UART interface */
void uart_puts(char *str) {
	while (*str) {
		/* Replace newlines with \r\n carriage return */
		if(*str == '\n') { uart_putc('\r'); }
		uart_putc(*str++);
	}
}

/* Clear terminal screen using VT100 commands */
/* http://braun-home.net/michael/info/misc/VT100_commands.htm */
void uart_clear_screen(void) {
	uart_putc(0x1B);		/* Escape character */
	uart_puts("[2J");		/* Clear screen */
	uart_putc(0x1B);		/* Escape character */
	uart_puts("[0;0H");		/* Move cursor to 0,0 */
}
