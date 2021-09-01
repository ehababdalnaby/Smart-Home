/*
 * HDT.h
 *
 * Created: 8/24/2021 10:25:37 AM
 *  Author: Mahmoud-PC
 */ 



#ifndef DHT_H_
#define DHT_H_

#include "includes.h"


#define DHT_PORT	PORTD
#define DHT_DDR		DDRD
#define DHT_PIN		PD7


void DHT_start(void);
u8 DHT_read(void);
void DHT_Response(void);
BOOL DHT_Represent(u8* hum,u8* temp);
void intTostring(u16 hum_1,u16 temp_1,u8* temp,u8* hum);


#endif /* HDT_H_ */