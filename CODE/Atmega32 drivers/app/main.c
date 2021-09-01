/*
* Atmega32 drivers.c
*
* Created: 8/18/2021 9:30:05 PM
* Author : Ehab & Mohamed & Mahmoud & Muhammed
*/

#include "includes.h"

#ifndef INCLUDES_H_
#error define includes.h file
#endif

int main(){
	KEYPAD_Init();
	LCD_init();
	u8 keyPressed, password[5],counter;
	while(1)
	{
	
		while(counter<4)
		{
			keyPressed=GetKey();

			while(keyPressed!=0)
			{
				password[counter]=keyPressed;
				disp_charXY(1,counter+1,keyPressed);
				keyPressed=0;
				counter++;
			}	
		}
	
	}
	return 0;
	
	
	
	
	
	
	
	
}




