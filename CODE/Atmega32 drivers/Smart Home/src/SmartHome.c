/*
* SmartHome.c
*
* Created: 01/09/2021 08:49:50 
*  Author: Administrator
*/
#include "SmartHome.h"
#include "MQTT.h"

static u8 oldpassword[]="1234";
static u8 trials=0;

extern	void (*ptrINT)(void);
extern u8 temp2;
extern	u8 tempstr[10];
static u8 flag=0;


void turnOnFireAlarm(void)
{
	Callback(FireAlarm);
}

void Project_Init(void)
{
	KEYPAD_Init();
	LCD_init();
	ADC_init();
	INT_init(INT_0,any_level);
	
	pinDirection(DOOR_LED,OUTPUT);
	pinDirection(BUZZER,OUTPUT);
	pinDirection(SOIL_PUMP,OUTPUT);
	pinDirection(OUTERLIGHT,OUTPUT);
	pinDirection(FIREPUMP,OUTPUT);
	pinDirection(TV_PIN,OUTPUT);
	pinDirection(FAN,OUTPUT);
	pinDirection(INNERLIGHT,OUTPUT);
	
	pinDirection(FLAME_SENSOR,INPUT);
}


void Get_Password(u8* password)
{
	
	while(flag!=1)
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
		flag=1;
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
	u8 tempstr[4]={0};
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
	//controlling planets irrigation 
	if (soil<=30)//turn on pump
	{
		writePin(SOIL_PUMP,HIGH);
	}
	else
	{
		writePin(SOIL_PUMP,LOW);
	}
	//controlling outer lights
	if (LDR<30)//turn on lights
	{
		writePin(OUTERLIGHT,HIGH);
	}
	else
	{
		writePin(OUTERLIGHT,LOW);
	}
	 	
	temp();
// 		itoa(LDR,tempstr,10);
// 	 	MQTT_Publish("G/light",tempstr,strlen(tempstr));
// 	 	_delay_ms(1000);
// 	
}

void temp(void)
{
	u8 temp[60];
	u8 hum[60];
	disp_strXY(3,1,"Humid=     %RH");
	disp_strXY(4,1,"temp=      Deg.c");
	DHT_Represent(hum,temp);
	disp_strXY(3,7,hum);
	disp_strXY(4,6,temp);
	
	MQTT_Publish("G/DHT",temp,strlen(temp));
	_delay_ms(1000);
	MQTT_Publish("G/hum",hum,strlen(hum));
	_delay_ms(1000);
}


void FireAlarm(void)
{
	u8 msg[]="home on fire";
	TGLBit(PORTD,3);
	TGLBit(PORTB,7);
	MQTT_Publish("G/fire",msg,strlen(msg));
	_delay_ms(1000);	
}

void IOTcharinput(u8 data)
{
	switch(data)
	{
		case '0':
		writePin(TV_PIN,LOW);
		break;
		case '1':
		writePin(TV_PIN,HIGH);
		break;
		case '2':
		writePin(INNERLIGHT,HIGH);
		break;
		case '3':
		writePin(INNERLIGHT,LOW);
		break;
		case '4':
		writePin(FAN,HIGH);
		break;
		case '5':
		writePin(FAN,LOW);
		break;
		case '6':
		writePin(OUTERLIGHT,HIGH);
		break;
		case '7':
		writePin(OUTERLIGHT,LOW);
		break;
	}
}