/*
 * parser.h
 *
 *  Created on: May 4, 2015
 *      Author: Tahmid
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "bsp.h"
#include "spi.h"
#include "diskio.h"
#include "pff.h"

struct pkmn {
	uint8_t id;
	uint8_t type1;
	uint8_t type2;
	int16_t hp;				// int instead of uint for simplicity of death calculation
	uint16_t attack;
	uint16_t defense;
	uint16_t spattack;
	uint16_t spdefense;
	uint16_t speed;
	uint8_t attackOne;
	uint8_t attackTwo;
	uint8_t attackThree;
	uint8_t attackFour;
};

typedef struct pkmn pokemon_t;
//pokemon_t pk1;

struct attk {
	uint8_t id;
	uint8_t type;
	uint8_t power;
	uint8_t accuracy;
	uint8_t special; 		// 0 or 1 - should spattk or attk be used for damage calculation
							// 0 means regular attack, 1 means special attack
};

typedef struct attk attack_t;
attack_t ak1;

pokemon_t get_pokemon_data(char file);
char* parsedata(BYTE *buff, char *name);
void get_Name(char file_number, char* Pkname);
attack_t get_attacks(int attack_number);
char* parseCommaData(BYTE *buff, char *attacks);
void get_attack_Name(char attack_number, char* attkname);

char name[20];
char attacks[40];
volatile int start_pos;

#endif /* PARSER_H_ */
