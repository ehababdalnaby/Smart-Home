/*
* Atmega32 drivers.c
*
* Created: 8/18/2021 9:30:05 PM
* Author : Ehab & Mohamed & Mahmoud & Muhammed
*/

#include "includes.h"
#include <avr/interrupt.h>
#include <string.h>

extern	void (*ptrINT)(void);
#ifndef INCLUDES_H_
#error define includes.h file
#endif


u8 mqttPkt[150]			= {0}; // 1 -> type, 2-> RL, ....RL
u8 mqttPktInd			= 0;
u8 remLen				= 0;
u8 pktRecState			= 0; // 0 no packets, 1 publish type, 2 remLen

u8 temp2  = 1;
u8 tempstr[10]={0};
u8 data = 0;
int main()
{
	
	
	u8 TV_state=0;
	UART_INIT(9600);
	MQTT_Connect("1111");
	_delay_ms(3000);
	MQTT_Subscribe("G/devices");
	Project_Init();
	sei();
	u8 password[5]={0};
	turnOnFireAlarm();
	AnalogSensors();
	Get_Password(password);
	while(1)
	{
		
		AnalogSensors();
		IOTcharinput(data);
		// 		MQTT_Publish("G/Temp",tempstr,strlen(tempstr));
		// 		_delay_ms(1000);
		// 		if(Uart_ReceiveByte_unblock(&data))
		// 		{
		// 			if (pktRecState == 0 && data == 0x30)
		// 			{
		// 				mqttPktInd = 0;
		// 				mqttPkt[mqttPktInd++] = data;
		// 				pktRecState = 1; // we received the pub type
		// 			}
		// 			else if(pktRecState == 1){
		// 				mqttPkt[mqttPktInd++] = data;
		// 				pktRecState = 2;
		// 				remLen = data;
		// 			}
		// 			else if(pktRecState == 2){
		// 				mqttPkt[mqttPktInd++] = data;
		// 				if(mqttPktInd == remLen + 2){
		// 					pktRecState = 0;
		// 				}
		// 			}
		// 		}
		// 		if(mqttPkt[0] == 0x30){
		// 			if(mqttPkt[remLen + 1] == '1'){
		// 				TV_state=1;
		// 				}else if(mqttPkt[remLen + 1] == '0'){
		// 				TV_state=0;
		// 			}
		// 		}
		// 		if (TV_state==1)
		// 		{
		// 			SETBit(PORTD,7);
		// 		}
		// 		else
		// 		{
		// 			CLRBit(PORTD,7);
		// 		}
		
		
		
	}
}


ISR(INT0_vect)
{
	ptrINT();
}

ISR(USART_RXC_vect)
{
	
	data=UDR;
	if (pktRecState == 0 && data == 0x30)
	{
		mqttPktInd = 0;
		mqttPkt[mqttPktInd++] = data;
		pktRecState = 1; // we received the pub type
	}
	else if(pktRecState == 1)
	{
		mqttPkt[mqttPktInd++] = data;
		pktRecState = 2;
		remLen = data;
	}
	else if(pktRecState == 2)
	{
		mqttPkt[mqttPktInd++] = data;
		if(mqttPktInd == remLen + 2)
		{
			pktRecState = 0;
		}
	}

	if(mqttPkt[0] == 0x30)
	{
		data=mqttPkt[remLen + 1];
		
	}
	
}