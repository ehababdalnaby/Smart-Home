/*
 * I2C.c
 *
 * Created: 8/25/2021 5:55:26 PM
 *  Author: Mahmoud-PC
 */ 
#include "I2C.h"

void I2C_Init(void)
{				
	TWBR=32;				//set clk prescaler 100Khz
	SETBit(TWCR,TWEN);		//TWI enable 
}

BOOL I2C_start(void)
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWSTA); //enable the i2c , set the flag and send start 
	while(!GETBit(TWCR,TWINT));    //wait to execute the process
	return(I2C_Check_status(Start_Code));
}

BOOL I2C_Restart(void)
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWSTA); //enable the i2c , set the flag and send Restart
	while(!GETBit(TWCR,TWINT));    //wait to execute the process
	return(I2C_Check_status(Restart_Code));
}

void I2C_Stop(void)
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWSTO); //enable the i2c , set the flag and send stop
}


BOOL I2C_Check_status(u8 status_code)
{
	return(TWSR & 0xF8==status_code);
}


BOOL I2C_Write(u8 _8_Bit,u8 status_code)
{
	TWDR=_8_Bit;
	TWCR=(1<<TWEN)|(1<<TWINT);
	while(!GETBit(TWCR,TWINT));    //wait to execute the process
	return(I2C_Check_status(status_code));
}


BOOL I2C_Read(u8* _8_Bit,u8 status_code)
{
	TWCR=(1<<TWEN)|(1<<TWINT);
	if (status_code==ReceiveData_Ack_code)
	{
		SETBit(TWCR,TWEA);
	}
	while(!GETBit(TWCR,TWINT));    //wait to execute the process
	
	if (I2C_Check_status(status_code))
	{
		*_8_Bit=TWDR;
		return TRUE;
	}
	*_8_Bit=TWDR;
	return FALSE;
}



