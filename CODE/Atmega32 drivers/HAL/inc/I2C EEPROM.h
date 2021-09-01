/*
 * I2C_EEPROM.h
 *
 * Created: 8/26/2021 11:36:50 AM
 *  Author: ehab2_phjirwi
 */ 


#ifndef I2C_EEPROM_H_
#define I2C_EEPROM_H_

#include "includes.h"




#define CMD_READ  0xA1   //1010 0001
#define CMD_WRITE 0xA0


void I2C_EEPROM_Write(u16 add,u8 data);
void I2C_EEPROM_Current_Add(u8 *data);
void I2C_EEPROM_Read(u16 add,u8 *data);
void I2C_EEPROM_Seq_Read(u16 add,u16 Numchar,u8 *data);
void I2C_EEPROM_Page_Write(u16 add,u8* data);
#endif /* I2C EEPROM_H_ */