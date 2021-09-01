/*
* RTC.c
*
* Created: 8/26/2021 5:56:22 PM
*  Author: Mahmoud-PC
*/

#include "RTC.h"

u8 days[][4]={" ","Sun","Mon","Tus","Wed","Thr","Fri","Sat"};





void Write_RTC(u8 Seconds,u8 Minutes,u8 Hours,u8 Day,u8 Date,u8 Month,u8 Year)
{
	
	I2C_start();
	I2C_Write(RTC_WRITE_ADDRESS,SCMTSLA_Ack_Code);	//send address of RTC and write command
	I2C_Write(RTC_SECONDS_ADDRESS,SCMTSLA_Ack_Code);	//move the pointer register to the first address (0x00)
	I2C_start();
	I2C_Write(RTC_WRITE_ADDRESS,SCMTSLA_Ack_Code);	//send address of RTC and read command
	I2C_Write(Seconds,SlaveData_Ack_code);			//write seconds
	I2C_Write(Minutes,SlaveData_Ack_code);			//write minutes
	I2C_Write(Hours,SlaveData_Ack_code);			//write hours
	I2C_Write(Day,SlaveData_Ack_code);				//write day
	I2C_Write(Date,SlaveData_Ack_code);				//write date
	I2C_Write(Month,SlaveData_Ack_code);			//write month
	I2C_Write(Year,SlaveData_NAck_code);			//write year
	I2C_Stop();
}

void Read_RTC(u8* Time,u8* Calen)
{
	u8 Seconds, Minutes, Hours, Day, Date, Month, Year;
	I2C_start();
	I2C_Write(RTC_WRITE_ADDRESS,SCMTSLA_Ack_Code);  //send address of RTC and write command
	I2C_Write(RTC_SECONDS_ADDRESS,SCMTSLA_Ack_Code);  //move the pointer register to the first address (0x00)
	I2C_Stop();

	I2C_start();
	I2C_Write(RTC_READ_ADDRESS,SCMTSLA_Ack_Code);   //send address of RTC and read command
	I2C_Read(&Seconds,ReceiveData_Ack_code);		//read seconds
	I2C_Read(&Minutes,ReceiveData_Ack_code);		//read minutes
	I2C_Read(&Hours,ReceiveData_Ack_code);			//read hours
	I2C_Read(&Day,ReceiveData_Ack_code);			//read day
	I2C_Read(&Date,ReceiveData_Ack_code);			//read date
	I2C_Read(&Month,ReceiveData_Ack_code);			//read month
	I2C_Read(&Year,ReceiveData_NAck_code);			//read year   
	I2C_Stop();
	sprintf(Time,"%d%d:%d%d:%d%d",((Hours&0xf0)>>4),Hours&0x0f,((Minutes&0xf0)>>4),Minutes&0x0f,((Seconds&0xf0)>>4),Seconds&0x0f);
	sprintf(Calen,"%d%d/%d%d/20%d%d %s",((Date&0xf0)>>4),Date&0x0f,((Month&0xf0)>>4),Month&0x0f,((Year&0xf0)>>4),Year&0x0f,&days[Day]);
}