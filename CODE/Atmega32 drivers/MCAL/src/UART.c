/*
 * UART.c
 *
 * Created: 8/21/2021 10:16:09 PM
 *  Author: ehab2_phjirwi
 */ 
#include "includes.h"
#define  F_CPU 8000000UL





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


BOOL	Uart_ReceiveByte_unblock(u8* pData)
{
	BOOL result = FALSE;
	if ( UCSRA & (1<<RXC) ){
		(*pData) = UDR;
		result =  TRUE;
	}
	else{
		result = FALSE;
	}
	return result;
}

void	Uart_SendStr(u8* str){
	u32 ind = 0;
	while(str[ind] != 0){
		UART_TX(str[ind]);
		ind++;
	}
}