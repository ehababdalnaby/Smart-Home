/*
 * MQTT.c
 *
 * Created: 8/29/2021 1:10:59 PM
 *  Author: MahmoudH
 */ 
#include "MQTT.h"

u16 PID = 1;
u8 proName[] = "MQTT";
void sendUTFStr(u8* str){
	UART_TX(0x00); // MSB = 0 because packet len < 256
	UART_TX(strlen(str));
	UART_TX(str);
}
void MQTT_Connect(u8* id){
	u8 RL = (2 + strlen(proName)) + 1 + 1 + 2 + ( 2 + strlen(id));
	UART_TX(0x10);
	UART_TX(RL);
	sendUTFStr(proName);
	UART_TX(0x04);
	UART_TX(0x02);
	UART_TX(0xFF);
	UART_TX(0xFF);
	sendUTFStr(id);
}
void MQTT_Publish(u8* topic, u8* msgPtr, u8 msgLen){
	u8 RL = (2 + strlen(topic)) + msgLen;
	u8 ind = 0;
	UART_TX(0x30);
	UART_TX(RL);
	sendUTFStr(topic);
	for (ind = 0; ind < msgLen; ind++)
	{
		UART_TX(msgPtr[ind]);
	}
}
void MQTT_Subscribe(u8* topic){
	u8 RL = 2 + (2 + strlen(topic)) + 1;
	UART_TX(0x82);
	UART_TX(RL);
	
	UART_TX((u8)(PID>>8)); // MSB
	UART_TX((u8)(PID));
	PID++;
	
	sendUTFStr(topic);	
	UART_TX(0x00);
}