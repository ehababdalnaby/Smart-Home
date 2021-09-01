/*
 * ExTinterupt.c
 *
 * Created: 8/21/2021 4:23:22 PM
 *  Author: ehab2_phjirwi
 */ 
#include "ExTinterupt.h"
#include <avr/interrupt.h>

void INT_init(u8 int_num , u8 sense_control)
{
	
	if(int_num == INT_2)
	{
		MCUCSR|=((sense_control & 0x01)<<6);
	}
	else
	{
		MCUCR|=(sense_control<<(0));
	}
	
	GICR|=(1<<int_num);
	GLOBAL_INT_EN();
}

void GLOBAL_INT_EN(void)
{
	writePins( &SREG,0x80,HIGH );
}

void GLOBAL_INT_DE(void)
{
	writePins( &SREG,0x80,LOW );
}
ISR(INT0_vect)
{
	writePin(PC2,HIGH);
	//_delay_ms(1000);
	writePin(PC2,LOW);
	//_delay_ms(1000);
}