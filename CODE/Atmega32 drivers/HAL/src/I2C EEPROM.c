/*
 * I2C_EEPROM.c
 *
 * Created: 8/26/2021 11:37:10 AM
 *  Author: ehab2_phjirwi
 */ 
#include "I2C EEPROM.h"





void I2C_EEPROM_Write(u16 add,u8 data)
{
	I2C_start(); //send start 
	I2C_Write(((add>>7)&0x02)|(CMD_WRITE),SCMTSLA_Ack_Code); //send control Byte
	I2C_Write(add,SCMTSLA_Ack_Code);  //send address word
	I2C_Write(data,SlaveData_Ack_code); //send data
	I2C_Stop();
	_delay_ms(10);
}
void I2C_EEPROM_Current_Add(u8 *data)
{
	
	I2C_start();
	I2C_Write((CMD_READ),SCMRSLA_Ack_Code);
	I2C_Read(data,ReceiveData_NAck_code);
	I2C_Stop();
	_delay_ms(1);
}

void I2C_EEPROM_Read(u16 add,u8 *data)
{
	I2C_start(); //send start
	I2C_Write(((add>>7)&0x02)|(CMD_WRITE),SCMRSLA_Ack_Code); //send control Byte
	I2C_Write(add,SCMRSLA_Ack_Code);  //send address word
	I2C_start();
	I2C_Write((CMD_READ),SCMRSLA_Ack_Code); //send control Byte
	I2C_Read(data,ReceiveData_NAck_code); //send data
	I2C_Stop();
	_delay_ms(1);
}


void I2C_EEPROM_Seq_Read(u16 add,u16 Numchar,u8 *data)
{
	u8 i=0;
	I2C_start(); //send start
	I2C_Write(((add>>7)&0x02)|(CMD_WRITE),SCMRSLA_Ack_Code); //send control Byte
	I2C_Write(add,SCMRSLA_Ack_Code);  //send address word
	I2C_Restart();
	I2C_Write((CMD_READ),SCMRSLA_Ack_Code); //send control Byte
	while(i<Numchar-1)
	{
		I2C_Read(&data[i],ReceiveData_Ack_code); //send data
		i++;
	}
	I2C_Read(&data[i],ReceiveData_NAck_code); //send data
	I2C_Stop();
	_delay_ms(1);
}

void I2C_EEPROM_Page_Write(u16 add,u8* data)
{
	u8 i=0;
	I2C_start(); //send start
	I2C_Write(((add>>7)&0x02)|(CMD_WRITE),SCMTSLA_Ack_Code); //send control Byte
	I2C_Write(add,SCMTSLA_Ack_Code);  //send address word
	while(*data!='\0' && i<16)
	{
		I2C_Write(*data,SlaveData_Ack_code); //send data
		data++;
		i++;
	}
	I2C_Stop();
	_delay_ms(10);
}
