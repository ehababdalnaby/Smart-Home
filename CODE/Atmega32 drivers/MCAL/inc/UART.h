
/*
 * UART.h
 *
 * Created: 8/21/2021 10:15:55 PM
 *  Author: ehab2_phjirwi
 */ 


#ifndef UART_H_
#define UART_H_

#include "includes.h"

enum {Asynchronous,synchronous}UART_MODE;
enum {Disabled,Even=2,Odd}PARITY_MODE;
enum {_1_bit,_2_bit}STOP_BIT;
enum {_5_bit,_6_bit,_7_bit,_8_bit}DATA_BIT;
enum {NORMAL_MODE,DOUBLE_SPEED}OPERATING_MODE;
	
#define MODE		Asynchronous
#define PARITY		Disabled
#define STOP_NUM	_1_bit
#define DATA_SIZE	_8_bit
#define UART_MODE	NORMAL_MODE
#define UDRE   5
#define TXEN   3
#define RXEN   4
#define RXC    7
#define UCSZ1   2
#define UCSZ0   1
#define URSEL   7
#define RXCIE   7

void UART_INIT(u16 BaudRate);
void UART_TX(u8 data);
u8 UART_RX(void);
#endif /* UART_H_ */

