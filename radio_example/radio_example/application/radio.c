/*------------------------------------------------------------
 * Example radio "send" application
 *   Sends packets with a data payload in an infinite loop
 *----------------------------------------------------------*/

#include "bsp.h"
#include "mrfi.h"
#include "radios/family1/mrfi_spi.h"
#include "globals.h"
#include "function_prototypes.h"
#include <string.h>

#include "parser.h"

/* Useful #defines */
#define RED_SEND_LED 		0x01

/* Main function for transmit application */
//void main(void) {
//
//	/* Perform board-specific initialization */
//	BSP_Init();
//
//	/* Initialize minimal RF interface, wake up radio */
//	MRFI_Init();
//	MRFI_WakeUp();
//
//	/* Set red LED to output */
//	P1DIR = RED_SEND_LED;
//	P1OUT = RED_SEND_LED;
//
//	__bis_SR_register(GIE);
//
//	/* Main (infinite) transmit loop */
//	while(1){
//		/* Construct a packet to send over the radio.
//		 *
//		 *  Packet frame structure:
//		 *  ---------------------------------------------------
//		 *  | Length (1B) | Dest (4B) | Source (4B) | Payload |
//		 *  ---------------------------------------------------
//		 */
//		mrfiPacket_t 	packet;
//		//char msg[] = "ECE3140 rocks!\r\n";
//		uint8_t address[] = {0x12,0x34,0xab,0xcd};
//		uint8_t source[] = {0x02,0x00,0x01,0x02};
//		sendMsg("ECE3140 rocks!\r\n",address, source);
//	}
//}

/* Function to execute upon receiving a packet
 *   Called by the driver when new packet arrives */
void MRFI_RxCompleteISR(void) {
	/* Read the received data packet */

	mrfiPacket_t	packet;
	MRFI_Receive(&packet);

	uint8_t type[4] = {packet.frame[9], packet.frame[10], packet.frame[11], packet.frame[12]};
	if(type[0]=='0' & type[1]=='0' & type[2]=='0' & type[3]=='0') {
		// this is the opponent's id. Set the opp_pkmn struct as appropriate.
		opp_pkmn = get_pokemon_data(packet.frame[13]);
	}
	else if(type[0]=='0' & type[1]=='0' & type[2]=='0' & type[3]=='1') {
		received_attack = get_attacks(packet.frame[13]);
	}
	else if(type[0]=='0' & type[1]=='0' & type[2]=='1' & type[3]=='0') {
		// graphics update
	}
	else if(type[0]=='0' & type[1]=='0' & type[2]=='1' & type[3]=='1') {
		// game over signal
		flagReg ^= gameOver_bit;
	}

	// set the rfDone_bit high so that it no longer blocks
	flagReg ^= rfDone_bit;

}

void receiveInit(uint8_t* address){
	/* Set a filter address for packets received by the radio
	 *   This should match the "destination" address of
	 *   the packets sent by the transmitter. */
	//uint8_t address[] = {0x12,0x34,0xab,0xcd};

	/* Filter setup return value: success or failure */
	unsigned char status;

	/* Perform board-specific initialization */
	BSP_Init();

	/* Initialize minimal RF interface, wake up radio */
	MRFI_Init();
	MRFI_WakeUp();

	/* Attempt to turn on address filtering
	 *   If unsuccessful, turn on both LEDs and wait forever */
	status = MRFI_SetRxAddrFilter(address);
	MRFI_EnableRxAddrFilter();

	/* Turn on the radio receiver */
	MRFI_RxOn();

	/* Main loop just toggles the green LED with some delay */
	__bis_SR_register(GIE);
}

void sendMsg(char* msg, uint8_t* dest_address, uint8_t* src_address) {
	/* Construct a packet to send over the radio.
	 *
	 *  Packet frame structure:
	 *  ---------------------------------------------------
	 *  | Length (1B) | Dest (4B) | Source (4B) | Payload |
	 *  ---------------------------------------------------
	 */
	mrfiPacket_t 	packet;
	/* First byte of packet frame holds message length in bytes */
	packet.frame[0] = strlen(msg) + 8;	/* Includes 8-byte address header */

	/* Next 8 bytes are addresses, 4 each for source and dest. */
	packet.frame[1] = dest_address[0];		/* Destination */
	packet.frame[2] = dest_address[1];
	packet.frame[3] = dest_address[2];
	packet.frame[4] = dest_address[3];

	packet.frame[5] = src_address[0]; 		/* Source */
	packet.frame[6] = src_address[1];
	packet.frame[7] = src_address[2];
	packet.frame[8] = src_address[3];

	/* Remaining bytes are the message/data payload */
	strcpy( (char *) &packet.frame[9] , msg );


	/* Transmit the packet over the radio */
	MRFI_Transmit(&packet , MRFI_TX_TYPE_FORCED);

	/* Toggle red LED after transmitting, then wait a while */
	//P1OUT ^= RED_SEND_LED;
	//sleep(60000);

}

/*
 * Message type is "0000"
 */
void sendID(uint8_t id, uint8_t* dest, uint8_t* source) {
	char msg[] = {'0', '0', '0', '0', id, 0};
	sendMsg(msg, dest, source);
}

/*
 * Message type is "0001"
 */
void sendAttack(uint8_t attackID, uint8_t* dest, uint8_t* source) {
	char msg[] = {'0', '0', '0', '1', attackID, 0};
	sendMsg(msg, dest, source);
}

/*
 * Message type is "0010"
 */
void sendGraphicsUpdate(int16_t hp_max, int16_t hp_left, uint8_t pkmnID, uint8_t* dest, uint8_t* source) {
	char msg[] = {'0', '0', '1', '1', (hp_max << 8), (hp_max & 0x00FF),
			       (hp_left << 8), (hp_left & 0x00FF), pkmnID};
	sendMsg(msg, dest, source);
}

/*
 * Message type is "0011"
 */
void sendGameOver(uint8_t* dest, uint8_t* source) {
	char msg[] = {'0', '0', '1', '1'};
	sendMsg(msg, dest, source);
}

/* Parameterized "sleep" helper function */
void sleep(unsigned int count) {
	int i;
	for (i = 0; i < 10; i++) {
		while(count > 0) {
			count--;
			__no_operation();
		}
	}
}
