/*
 * I2C.h
 *
 * Created: 8/25/2021 5:55:12 PM
 *  Author: Mahmoud-PC
 */ 


#ifndef I2C_H_
#define I2C_H_
#include  "includes.h"

#define I2C_SDAPin		PC0
#define I2C_SClPin		PC1

		/*  */
#define TWINT			7
#define TWEN			2
#define TWEA			6
#define TWSTO			4
#define TWSTA			5

		/*  */

#define TWCR		SELECTOR(0x56)  //control register
#define TWBR		SELECTOR(0x20)	//bit 8 register (clock prescaler)
#define TWSR		SELECTOR(0x21)   //status register
#define TWAR		SELECTOR(0x22)
#define TWDR		SELECTOR(0x23)

		/*	General	status codes */

#define Start_Code					0x08
#define Restart_Code				0x10

		/* status codes for master transmit */
		

#define SCMTSLA_Ack_Code			0x18
#define SCMTSLA_NAck_Code			0x20
#define SlaveData_Ack_code			0x28
#define SlaveData_NAck_code			0x30

		/* status codes for master recieve */
		
#define SCMRSLA_Ack_Code			0x40
#define SCMRSLA_NAck_Code			0x48
#define ReceiveData_Ack_code		0x50
#define ReceiveData_NAck_code		0x58


		/*  */
typedef enum{PRE_S1,PRE_S4,PRE_S16,PRE_S64}TWI_CLK_PRESCALLER;





void I2C_Init(void);
BOOL I2C_start(void);
BOOL I2C_Restart(void);
void I2C_Stop(void);
BOOL I2C_Check_status(u8 status_code);
BOOL I2C_Write(u8 _8_Bit,u8 status_code);
BOOL I2C_Read(u8* _8_Bit,u8 status_code);


#endif /* I2C_H_ */