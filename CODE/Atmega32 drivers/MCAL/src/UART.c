/*
 * UART.c
 *
 * Created: 8/21/2021 10:16:09 PM
 *  Author: ehab2_phjirwi
 */ 
#include "includes.h"
#include <avr/interrupt.h>
#define  F_CPU 16000000UL


u8 gps[100];
u8 i=0;
u8 CHECK[]="$GPGGA";
ISR(USART_RXC_vect)
{
	gps[i]=UDR;
	i++;
	if (i==5)
	{
		gps[6]='\0';
		cli();
	}
}


void UART_INIT(u16 BaudRate)
{
	u16 BAUD_TEMP=0;
	BAUD_TEMP=((F_CPU/(16UL*BaudRate))-1);	
	UBRRH=(BAUD_TEMP>>8);
	UBRRL=BAUD_TEMP;
	SETBit(UCSRB,TXEN);
	SETBit(UCSRB,RXEN);
	//SETBit(UCSRB,RXCIE);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	GLOBAL_INT_EN();
}

void UART_TX(u8 data)
{
	UDR=data;
	while(GETBit(UCSRA,UDRE)!=1);	
		
}

u8 UART_RX(void)
{
	while(!GETBit(UCSRA,RXC));
	return UDR;	
}