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
#define KEYPAD_COL   4

#define FIRSTOFROW   PD4
#define LASTOFROW    PD7
#define ROWOFFSET    FIRSTOFROW

#define FIRSTOFCOL   PC3
#define LASTOFCOL    PC6
#define COLOFFSET    FIRSTOFCOL

#define ROW_PINS	0xF0
#define COL_PINS	0x78
#define COL_PORT	PORTC
#define ROW_PORT	PORTD

#define COL_DDR		DDRC
#define ROW_DDR     DDRD

#define COLPINREG   PINC


void KEYPAD_Init(void);
u8 GetKey(void);






#endif /* KEYPAD_H_ */