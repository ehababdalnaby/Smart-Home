/*
* Atmega32 drivers.c
*
* Created: 8/18/2021 9:30:05 PM
* Author : Ehab & Mohamed & Mahmoud & Muhammed
*/

#include "includes.h"
#include <avr/interrupt.h>


extern	void (*ptrINT)(void);
#ifndef INCLUDES_H_
#error define includes.h file
#endif

int main(){
	
	UART_INIT(9600);
	MQTT_Connect("1111");
	_delay_ms(1000);
	MQTT_Subscribe("NTI/Control");
	Project_Init();
	sei();
	u8 password[5]={0};
	turnOnFireAlarm();	
	while(1)
	{
		//Get_Password(password);
		AnalogSensors();
	}
}


ISR(INT0_vect)
{
	ptrINT();
}

