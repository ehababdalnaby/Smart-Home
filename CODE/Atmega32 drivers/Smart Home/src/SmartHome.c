/*
* SmartHome.c
*
* Created: 01/09/2021 08:49:50 م
*  Author: Administrator
*/
#include "SmartHome.h"


static u8 oldpassword[]="1234";
static u8 trials=0;

void Project_Init(void)
{
	KEYPAD_Init();
	LCD_init();
	ADC_init();
	
	
	pinDirection(DOOR_LED,OUTPUT);
	pinDirection(BUZZER,OUTPUT);
	pinDirection(SOIL_PUMP,OUTPUT);
	pinDirection(OUTERLIGHT,OUTPUT);
}


void Get_Password(u8* password)
{
	LCD_CLEAR();
	disp_strXY(2,1,"Enter password :");
	u8 keyPressed=0, counter=0;
	while (counter<4)
	{
		keyPressed=GetKey();
		
		if (keyPressed!=0)
		{
			password[counter]=keyPressed;
			disp_charXY(3,counter+1,keyPressed);
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
		LCD_CLEAR();
		writePin(DOOR_LED,HIGH);//open door
		disp_strXY(2,1,"Pass accepted");
		_delay_ms(3000);
		writePin(DOOR_LED,LOW);//close door
		trials=0;
		return;
	}
	disp_intXY(2,1,trials);
	if (trials>=2)
	{
		writePin(BUZZER,HIGH); // 	turn on alarm
		_delay_ms(3000);
		writePin(BUZZER,LOW);// 	turn off alarm
		trials=0;
		return;
	}
	LCD_CLEAR();
	disp_strXY(2,1,"Wrong Pass");
	_delay_ms(500);
	trials++;
	disp_intXY(2,6,trials);
	Get_Password(password);
	
	
	
	
}

void AnalogSensors(void)
{
	LCD_CLEAR();
	u16 LDR=0;
	u16 soil=0;
	soil=read_analog(SOILSENSOR);
	LDR=read_analog(LDRSENSOR);
	soil=(100-(soil*100UL)/1019UL);
	LDR=((LDR*100UL)/407UL);
	disp_strXY(1,1,"soil water=");
	disp_int(soil);
	disp_char('%');
	disp_strXY(2,1,"Light = ");
	disp_int(LDR);
	disp_char('%');
	if (soil<=30)//turn on pump
	{
		writePin(SOIL_PUMP,HIGH);
	}
	else
	{
		writePin(SOIL_PUMP,LOW);
	}
	
	if (LDR<30)//turn on lights
	{
		writePin(OUTERLIGHT,HIGH);
	}
	else
	{
		writePin(OUTERLIGHT,LOW);
	}
	_delay_ms(100);
}