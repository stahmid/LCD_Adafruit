/*
 * flags.h
 *
 *  Created on: May 2, 2015
 *      Author: Tahmid
 */

#ifndef FLAGS_H_
#define FLAGS_H_

#include "bsp.h"

uint16_t flagReg;

#define flgButtonSelected	BIT2
#define flgupdateButton		BIT3

#define setFlag(flag)	 	{flagReg |= (flag);}
#define clearFlag(flag)		{flagReg &= ~(flag);}
#define getFlag(flag)		(flagReg & (flag))

#endif /* FLAGS_H_ */
