/*
 * EXT_INT.c
 *
 * Created: 8/21/2021 6:01:45 PM
 *  Author: ehab2_phjirwi
 */ 
#include "EXT_INT.h"

void INT_init(u8 int_num , u8 sense_control)
{
	GICR|=(1<<int_num);
	switch(int_num)
	{
		case INT_2:
		MCUCSR|=((sense_control & 0x01)<<6);
		break;
		
		case INT_0:
		MCUCR|=sense_control;
		break;
		case INT_1:
		MCUCR|=(sense_control<<2);
	}
}

void GLOBAL_INT_EN(void)
{
	writePins( &SREG,0x80,HIGH );
}

void GLOBAL_INT_DE(void)
{
	writePins( &SREG,0x80,LOW );
}
