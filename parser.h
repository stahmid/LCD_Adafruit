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

#ifndef NULL
#define NULL 0
#endif

/*
 * Pokemon Type Definitions
 */
#define NORMAL 0
#define FIGHT 1
#define FLYING 2
#define POISON 3
#define GROUND 4
#define ROCK 5
#define BUG 6
#define GHOST 7
#define STEEL 8
#define FIRE 9
#define WATER 10
#define GRASS 11
#define ELECTR 12
#define PSYCHC 13
#define ICE 14
#define DRAGON 15
#define DARK 16
#define FAIRY 17

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
};

//typedef struct pkmn pokemon_t;
typedef struct pkmn pokemon_data_t;

struct pokemon {
	uint16_t id;
	uint16_t speed;
	int16_t hp_left;
	int16_t hp_max;
	int16_t attackOne;
	int16_t attackTwo;
	int16_t attackThree;
	int16_t attackFour;
};

typedef struct pokemon pokemon_team_t;

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

pokemon_data_t get_pokemon_data(char file);
pokemon_team_t get_pokemon_team(char file_number);
char* parsedata(BYTE *buff, char *name);
void get_Name(char file_number, char* Pkname);
attack_t get_attacks(int attack_number);
char* parseCommaData(BYTE *buff, char *attacks);
void get_attack_Name(char attack_number, char* attkname);

char name[20];
char attacks[40];
volatile int start_pos;

#endif /* PARSER_H_ */
