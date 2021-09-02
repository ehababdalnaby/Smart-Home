/*
 * SmartHome.h
 *
 * Created: 01/09/2021 08:53:52 م
 *  Author: Administrator
 */ 


#ifndef SMARTHOME_H_
#define SMARTHOME_H_

#include "includes.h"



void Get_Password(u8*);
void Check_Password(u8*);
void Project_Init(void);
void AnalogSensors(void);
void FireAlarm(void);
void turnOnFireAlarm(void);
void temp(void);
void IOTcharinput(u8 data);


#endif /* SMARTHOME_H_ */