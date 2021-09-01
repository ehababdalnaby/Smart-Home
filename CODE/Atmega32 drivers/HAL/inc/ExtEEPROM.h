/*
 * ExtEEPROM.h
 *
 * Created: 8/22/2021 6:17:30 PM
 *  Author: Mohamed
 */ 


#ifndef EXTEEPROM_H_
#define EXTEEPROM_H_
#include "includes.h"



#define EROM_COM_WRITE			0x02
#define EROM_COM_READ			0x03

void writeEEPROM(u16 location,u8 data);
u8 readEEPROM(u16 location);
void WRITE_DI(void);
void WRITE_EN(void);
void writePageEEPROM(u16 location,u8* str);
void ReadEEPROMSTR(u16 location,u8 CharNum,u8 * ReadStr);
void write_EEPROM_auto(u8* str);
void CLR_EEPROM(void);


#endif /* EXTEEPROM_H_ */