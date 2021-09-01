/*
* Atmega32 drivers.c
*
* Created: 8/18/2021 9:30:05 PM
* Author : Ehab & Mohamed & Mahmoud Muhammed
*/

#include "includes.h"
#include "GPS.h"


#ifndef INCLUDES_H_
#error define includes.h file
#endif

extern volatile u32 overflow;



// #include "smile.h"
 //#include "wink.h"
#include "NTI.h"

void servo_rotate(u32 angel)
{
	angel= 1000+(1000UL*angel/180UL);
	writePin(PD7,HIGH);
	timer_delay_us(angel);
	writePin(PD7,LOW);
	timer_delay_us(20000-angel);
}
int main(void)
{	
	
	Clock_APP();
	//GPS_APP();
	//SERVO_APP();
	//tempsensorAPP();
	
	
	
	
// 	u8 imageline[128];
// 	u16 i=0;
// 	u16 x=1,y=1;
// 	GLCD_init();
// 	I2C_Init();
// while(1)
// {
// 	for (x=0;x<8;x++)
// 	{
// 		I2C_EEPROM_Seq_Read((x*128),128,imageline);
// 		for(y=0;y<128;y++)
// 		{
// 			//I2C_EEPROM_Read(add,&imageline);
// 			GLCD_Disp_Char_XY(x+1,y+1,imageline[y]);
// 		}
// 	}
// }
	
	
}

