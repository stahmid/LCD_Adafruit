/*
 * parser.c
 *
 *  Created on: May 4, 2015
 *      Author: Tahmid
 */

#include "parser.h"
#include "spi.h"
#include "diskio.h"
#include "pff.h"

char name[20];
char attacks[40];
volatile int start_pos;

pokemon_data_t get_pokemon_data(uint8_t file_number) {
	pokemon_data_t pk1;
    UINT br;
    BYTE buff[20];
	FRESULT res;

	sprintf((char*) buff, "%d.txt", file_number);
	// Open a file
    res = pf_open((char*) buff);

    res = pf_read((char*) buff, 20, (WORD*) &br);   //Read first line of text file, getting Pokemon, forget about data

    pk1.id = (uint8_t) file_number;

    res = pf_read((char*) buff, 20, (WORD*) &br);	//Read next line, Type1
    char* type1 = parsedata(buff, name);

    res = pf_read((char*) buff, 20, (WORD*) &br);	//Read next line, Type2
    char* type2 = parsedata(buff, name);

    res = pf_read((char*) buff, 20, (WORD*) &br);	//Read next line, hp
    char* hp = parsedata(buff, name);
    pk1.hp = atoi(hp);

    res = pf_read((char*) buff, 20, (WORD*) &br);	//Read next line, attack
    char* attack = parsedata(buff, name);
    pk1.attack = atoi(attack);

    res = pf_read((char*) buff, 20, (WORD*) &br);	//Read next line, defense
    char* defense = parsedata(buff, name);
    pk1.defense = atoi(defense);

    res = pf_read((char*) buff, 20, (WORD*) &br);	//Read next line, special attack
    char* sa = parsedata(buff, name);
    pk1.spattack = atoi(sa);

    res = pf_read((char*) buff, 20, (WORD*) &br);	//Read next line, special defense
    char* sd = parsedata(buff, name);
    pk1.spdefense = atoi(sd);

    res = pf_read((char*) buff, 20, (WORD*) &br);	//Read next line, speed
    char* speed = parsedata(buff, name);
    pk1.speed = atoi(speed);

    res = pf_read((char*) buff, 20, (WORD*) &br);   //1st attack
    char* att1 = parsedata(buff, name);
    //pk1.attackOne = atoi(att1);

    res = pf_read((char*) buff, 20, (WORD*) &br);   //2nd attack
    char* att2 = parsedata(buff, name);
    //pk1.attackTwo = atoi(att2);

    res = pf_read((char*) buff, 20, (WORD*) &br);   //3rd attack
    char* att3 = parsedata(buff, name);
    //pk1.attackThree = atoi(att3);

    res = pf_read((char*) buff, 20, (WORD*) &br);   //4th attack
    char* att4 = parsedata(buff, name);
    //pk1.attackFour = atoi(att4);

    return pk1;
}

pokemon_team_t get_pokemon_team(uint8_t file_number) {
	pokemon_team_t pk1;
	UINT br;
	BYTE buff[20];
	FRESULT res;

	sprintf((char*) buff, "%d.txt", file_number);
	// Open a file
	res = pf_open((char*) buff);

	res = pf_read(buff, 20, (WORD*) &br);   //Read first line of text file, getting Pokemon, forget about data

	pk1.id = (uint8_t) file_number;

	res = pf_read(buff, 20, (WORD*) &br);	//Read next line, Type1
	char* type1 = parsedata(buff, name);

	res = pf_read(buff, 20, (WORD*) &br);	//Read next line, Type2
	char* type2 = parsedata(buff, name);

	res = pf_read(buff, 20, (WORD*) &br);	//Read next line, hp
	char* hp = parsedata(buff, name);
	pk1.hp_max = atoi(hp);
	pk1.hp_left = atoi(hp);

	res = pf_read(buff, 20, (WORD*) &br);	//Read next line, attack
	char* attack = parsedata(buff, name);
	//pk1.attack = atoi(attack);

	res = pf_read(buff, 20, (WORD*) &br);	//Read next line, defense
	char* defense = parsedata(buff, name);
	//pk1.defense = atoi(defense);

	res = pf_read(buff, 20, (WORD*) &br);	//Read next line, special attack
	char* sa = parsedata(buff, name);
	//pk1.spattack = atoi(sa);

	res = pf_read(buff, 20, (WORD*) &br);	//Read next line, special defense
	char* sd = parsedata(buff, name);
	//pk1.spdefense = atoi(sd);

	res = pf_read(buff, 20, (WORD*) &br);	//Read next line, speed
	char* speed = parsedata(buff, name);
	pk1.speed = atoi(speed);

	res = pf_read(buff, 20, (WORD*) &br);   //1st attack
	char* att1 = parsedata(buff, name);
	pk1.attackOne = atoi(att1);

	res = pf_read(buff, 20, (WORD*) &br);   //2nd attack
	char* att2 = parsedata(buff, name);
	pk1.attackTwo = atoi(att2);

	res = pf_read(buff, 20, (WORD*) &br);   //3rd attack
	char* att3 = parsedata(buff, name);
	pk1.attackThree = atoi(att3);

	res = pf_read(buff, 20, (WORD*) &br);   //4th attack
	char* att4 = parsedata(buff, name);
	pk1.attackFour = atoi(att4);

	return pk1;
}

char* parsedata(BYTE *buff, char *name) {
    volatile int i = 0; volatile int j = 0;
    //char *name;
    while(buff[i] != '.') {
    	i++;
    }
    //name = (char*)malloc(k * sizeof(char));
    for (j=0; j<i; j++) {
    	name[j] = buff[j];
    }
    name[j] = '\0';

    return name;
}

void get_Name(char file_number, char* Pkname) {
	UINT br;
	BYTE buff[20];
	FRESULT res;

	sprintf((char*) buff, "%d.txt", file_number);
	// Open a file
    res = pf_open((char*) buff);

    res = pf_read((char*) buff, 20, (WORD*) &br);   //Read first line of text file, getting Pokemon, forget about data
    char* pkname = parsedata(buff, name);

    int counter = 0;
    while (*pkname){
    	Pkname[counter++] = *pkname++;
    }
    Pkname[counter] = '\0';
}

attack_t get_attacks(int attack_number) {
	attack_t attk;
	UINT br;
	BYTE buff[40];
	FRESULT res;
	int p;

	// Open a file
    res = pf_open("attacks.txt");

    for (p=0; p<attack_number; p++) {
    	res = pf_read((char*) buff, 40, (WORD*) &br);   //Read first line of text file, getting Pokemon, forget about data
    }//buff will have the relevant comma separated line

    start_pos = 0;
    char* id = parseCommaData(buff, attacks);
    attk.id = atoi(id);

    char* attk_name = parseCommaData(buff, attacks);
    char* type = parseCommaData(buff, attacks);


    char* power = parseCommaData(buff, attacks);
    attk.power = atoi(power);

    char* accuracy = parseCommaData(buff, attacks);
    attk.accuracy = atoi(accuracy);

    char* special = parseCommaData(buff, attacks);
    attk.special = atoi(special);

    return attk;
}

char* parseCommaData(BYTE *buff, char *attacks) {
    volatile int i = start_pos; volatile int j = 0;
    //char *name;
    while(buff[i] != ',') {
    	i++;
    }
    //name = (char*)malloc(k * sizeof(char));
    for (j=0; j<(i-start_pos); j++) {
    	name[j] = buff[start_pos + j];
    }
    start_pos = i+1;
    name[j] = '\0';

    return name;
}

void get_attack_Name(char attack_number, char* Attkname) {
	UINT br;
	BYTE buff[40];
	FRESULT res;

	if (attack_number == 0){
		Attkname[0] = '\0';
		return;
	}

	// Open a file
    res = pf_open("attacks.txt");
    int p;
    for (p=0; p<attack_number; p++) {
    	res = pf_read(buff, 40, (WORD*) &br);   //Read first line of text file, getting Pokemon, forget about data
    }//buff will have the relevant comma separated line

    start_pos = 0;
    char* tmp = parseCommaData(buff, attacks);
    char* attkname = parseCommaData(buff, attacks);

    int counter = 0;
    while (*attkname){
    	Attkname[counter++] = *attkname++;
    }
    Attkname[counter] = '\0';

}
