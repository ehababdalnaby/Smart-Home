/*
 * SmartHome.c
 *
 * Created: 01/09/2021 08:49:50 م
 *  Author: Administrator
 */ 
#include "SmartHome.h"
#include "Proj_Cof.h"

static u8 oldpassword[]="1234";
static u8 trials=0;

void Project_Init(void)
{
	pinDirection(DOOR_LED,OUTPUT);
	pinDirection(BUZZER,OUTPUT);
}


void Get_Password(u8* password)
{
	disp_strXY(1,1,"    ");
	u8 keyPressed=0, counter=0;
	while (counter<4)
	{
		keyPressed=GetKey();
	
		if (keyPressed!=0)
		{
			password[counter]=keyPressed;
			disp_charXY(1,counter+1,keyPressed);
			keyPressed=0;
			counter++;
		}
	}
	Check_Password(password);
}
void Check_Password(u8* password)
{
	
	if (strcmp(oldpassword,password)==0)
		{
			writePin(DOOR_LED,HIGH);//open door
			_delay_ms(3000);
			writePin(DOOR_LED,LOW);//close door
			trials=0;
			return;
		}
		disp_intXY(2,1,trials);
		if (trials>3)
		{
			writePin(BUZZER,HIGH); // 	turn on alarm
			_delay_ms(3000);
			writePin(BUZZER,LOW);// 	turn off alarm
			trials=0;
			return;
		}
			trials++;
			disp_intXY(2,6,trials);
			Get_Password(password);
		
			
			
	
}