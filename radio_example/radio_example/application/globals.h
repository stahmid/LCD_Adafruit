#include "typedefs.h"
/******************
 * Global Variables
*******************/
extern uint16_t flagReg;

extern attack_t received_attack;
extern pokemon_data_t opp_pkmn;
extern pokemon_team_t pkmn1;

// helpful definitions
#define rfDone_bit	BIT0
#define rfDone() (flagReg & rfDone_bit)
#define gameOver_bit BIT1
#define gameOver() (flagReg & gameOver_bit)
