/*
 * typedefs_.h
 *
 *  Created on: May 3, 2015
 *      Author: Manish Patel
 */

#ifndef TYPEDEFS__H_
#define TYPEDEFS__H_

#include <msp430.h>
#include <stdint.h>

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

/*
 * Useful Structs below
 */

struct attk {
	uint8_t id;
	uint8_t type;
	uint8_t power;
	uint8_t accuracy;
	uint8_t special; 		// 0 or 1 - should spattk or attk be used for damage calculation
							// 0 means regular attack, 1 means special attack
};

typedef struct attk attack_t;


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
//	uint8_t attackOne;
//	uint8_t attackTwo;
//	uint8_t attackThree;
//	uint8_t attackFour;
};

typedef struct pkmn pokemon_data_t;

struct pokemon {
	uint8_t id;
	uint16_t speed;
	int16_t hp_left;
	int16_t hp_max;
	uint8_t attackOne;
	uint8_t attackTwo;
	uint8_t attackThree;
	uint8_t attackFour;
};

typedef struct pokemon pokemon_team_t;


#endif /* TYPEDEFS__H_ */
