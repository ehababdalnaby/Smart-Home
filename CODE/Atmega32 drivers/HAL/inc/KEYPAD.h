/*
 * KEYPAD.h
 *
 * Created: 8/20/2021 6:03:43 PM
 *  Author: ehab2_phjirwi
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "includes.h"

#define KEYPAD_ROW   4
#define KEYPAD_COL   3

#define FIRSTOFROW   PB0
#define LASTOFROW    PB3
#define ROWOFFSET    FIRSTOFROW

#define FIRSTOFCOL   PB4
#define LASTOFCOL    PB6
#define COLOFFSET    FIRSTOFCOL

#define ROW_PINS	0x0F
#define COL_PINS	0x70
#define COL_PORT	PORTB
#define ROW_PORT	PORTB

#define COL_DDR		DDRB
#define ROW_DDR     DDRB

#define COLPINREG   PINB


void KEYPAD_Init(void);
u8 GetKey(void);






#endif /* KEYPAD_H_ */