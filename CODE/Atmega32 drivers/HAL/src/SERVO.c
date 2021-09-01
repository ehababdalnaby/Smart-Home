/*
 * SERVO.c
 *
 * Created: 30/08/2021 12:49:47 
 *  Author: Administrator
 */ 
#include "SERVO.h"

Servo_Init()
{
	pinDirection(SERVO_PIN,OUTPUT);
	Timer1_Init(FPWM);
}

void servo_Angel(u8 Angel)
{
	set_dutycycleTimer1(Angel);
}
