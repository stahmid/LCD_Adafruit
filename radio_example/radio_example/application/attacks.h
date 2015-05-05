/*
 * attacks.h
 *
 *  Created on: Apr 24, 2015
 *      Author: Manish Patel
 */
//#include "typedefs.h"
#include <stdint.h>

#ifndef ATTACKS_H_
#define ATTACKS_H_

/*
 * Type chart matrix. The attacking type is encoded in the rows and the defending type
 * is encoded in the columns. Reference: http://bulbapedia.bulbagarden.net/wiki/Type.
 * NOTE: ALL THE VALUES IN THIS MATRIX ARE DOUBLED TO SAVE MEMORY. THE DIVIDE BY 2 OCCURS
 * IN FUNCTION getEffectiveness().
 */

const uint8_t typeMatrix[18][18] =  {{2, 2, 2, 2, 2, 1, 2, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2},
							   	     {4, 2, 1, 1, 2, 4, 1, 0, 4, 2, 2, 2, 2, 1, 4, 2, 4, 1},
							   	     {2, 4, 2, 2, 2, 1, 4, 2, 1, 2, 2, 4, 1, 2, 2, 2, 2, 2},
							   	     {2, 2, 2, 1, 1, 1, 2, 1, 0, 2, 2, 4, 2, 2, 2, 2, 2, 4},
							   	     {2, 2, 0, 4, 2, 4, 1, 2, 4, 4, 2, 1, 4, 2, 2, 2, 2, 2},
							   	     {2, 1, 4, 2, 1, 2, 4, 2, 1, 4, 2, 2, 2, 2, 4, 2, 2, 2},
							   	     {2, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 4, 2, 4, 2, 2, 4, 1},
							   	     {0, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 1, 2},
							   	     {2, 2, 2, 2, 2, 4, 2, 2, 1, 1, 1, 2, 1, 2, 4, 2, 2, 4},
							   	     {2, 2, 2, 2, 2, 1, 4, 2, 4, 1, 1, 4, 2, 2, 4, 1, 2, 2},
							   	     {2, 2, 2, 2, 4, 4, 2, 2, 2, 4, 1, 1, 2, 2, 2, 1, 2, 2},
							   	     {2, 2, 1, 1, 4, 4, 1, 2, 1, 1, 4, 1, 2, 2, 2, 1, 2, 2},
							   	     {2, 2, 4, 2, 0, 2, 2, 2, 2, 2, 4, 1, 1, 2, 2, 1, 2, 2},
							   	     {2, 4, 2, 4, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 0, 2},
							   	     {2, 2, 4, 2, 4, 2, 2, 2, 1, 1, 1, 4, 2, 2, 1, 4, 2, 2},
							   	     {2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 4, 2, 0},
							   	     {2, 1, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 1, 1},
							   	     {2, 4, 2, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 4, 4, 2}};

/*
 * Define all of the attacks. Declare them as const so that they reside in ROM
 * and save RAM.
 */

// Normal Attacks
/*
const attack_t body_slam = {"Body Slam", NORMAL, 85, 100, 0};
const attack_t extreme_speed = {"Extreme Speed", NORMAL, 80, 100, 0};

// Fire Attacks
const attack_t flamethrower = {"Flamethrower", FIRE, 95, 100, 1};

// Water Attacks
const attack_t surf = {"Surf", WATER, 95, 100, 1};

// Steel Attacks
const attack_t iron_tail = {"Iron Tail", 100, 75, 0};

// Electric Attacks
const attack_t thunderbolt = {"Thunderbolt", 95, 100, 1};

// Dark Attacks
const attack_t dark_pulse = {"Dark Pulse", 80, 100, 1};

// Ground Attacks
const attack_t earthquake = {"Earthquake", 100, 100, 0};

// Fighting Attacks
const attack_t brick_break = {"Brick Break", 75, 100, 0};

// Flying Attacks
const attack_t aerial_ace = {"Aerial Ace", 60, 100, 0};

// Ice Attacks
const attack_t ice_beam = {"Ice Beam", 95, 100, 1};
*/


#endif /* ATTACKS_H_ */
