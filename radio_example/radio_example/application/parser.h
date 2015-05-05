/*
 * parser.h
 *
 *  Created on: May 4, 2015
 *      Author: Tahmid
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "spi.h"
#include "diskio.h"
#include "pff.h"
#include "typedefs.h"

#include <stdio.h>
#include <stdlib.h>

pokemon_data_t get_pokemon_data(uint8_t file);
pokemon_team_t get_pokemon_team(uint8_t file);
char* parsedata(BYTE *buff, char *name);
void get_Name(char file_number, char* Pkname);
attack_t get_attacks(int attack_number);
char* parseCommaData(BYTE *buff, char *attacks);
void get_attack_Name(char attack_number, char* attkname);

extern char name[20];
extern char attacks[40];
extern volatile int start_pos;

#endif /* PARSER_H_ */
