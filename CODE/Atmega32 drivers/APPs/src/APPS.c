/*
 * APPS.c
 *
 * Created: 8/20/2021 6:36:16 PM
 *  Author: ehab2_phjirwi
 */ 
#include "APPS.h"

extern u8 autoAddress;
void counterAPP(void)
{
	INT_init(INT_0,falling_edge);
	GLOBAL_INT_EN();
	pinDirection(PC2,OUTPUT);
	
	LCD_init();
	
	/* Replace with your application code */
	pinDirection(PB0,INPUT);
	
	u32 count=0,i=0;
	u32 delay =1000,row=1;
	disp_strXY(1,1,(u8 *)"counter = ");
	//disp_intXY(2,3,2021);
	while (1)
	{
		delay =1000;
		if (readPin(PB0))
		{
			row++;
			delay=delay/(row*0.5);
			if (delay<100)
			{
				delay=100;
			}
			disp_strXY(1,11,(u8 *)"    ");
			disp_intXY(1,11,count++);
			for (i=0;i<=delay;i++)
			{
				_delay_ms(1);
			}
			
		}
		else
		{
			row=1;
			delay =1000;
			disp_strXY(1,11,(u8 *)"    ");
			disp_intXY(1,11,count++);
			for (i=0;i<=delay;i++)
			{
				_delay_ms(1);
			}
			
		}
	
	}
}



void KeyPadAPP(void)
{
	LCD_init();
	KEYPAD_Init();
	disp_charXY(1,1,'x');
	u8 key=0;
	while(1)
	{
		key=GetKey();
		if (key!=0)
		{
			disp_charXY(1,1,key);
			key=0;
		}	
	}
}



void CLockAPP(void)
{
	LCD_init();
	disp_strXY(1,1,__TIME__);
}




void ADCAPP(void)
{
	ADC_init();
	LCD_init();
	while(1)
	{
		u16 aDCvalue=read_analog(ADC0);
		disp_strXY(1,1,(u8 *)"    ");
		disp_intXY(1,1,aDCvalue);
		s16 aDCvalue1=read_analog(ADC1);
		disp_strXY(2,1,(u8 *)"    ");
		disp_intXY(2,1,aDCvalue1);
		u16 aDCvalue2=read_analog(ADC2);
		disp_strXY(2,8,(u8 *)"    ");
		disp_intXY(2,8,aDCvalue2);
		_delay_ms(100);
	}
}
// void SPI_app(void)
// {
// 	u8 data='A';
// 	u8 receive;
// 	u8 col=1;
// 	while(1)
// 	{
// 	SPI_Transceive(data);
// 	_delay_ms(1000);
// 	disp_charXY(1,col,data);
// 	disp_charXY(2,col,receive);
// 	data++;
// 	col++;
// 	}
// }

void EEPROM_25aa040(void)
{
	
	SPI_Init(SPI_MASTER);
	LCD_init();
	CLR_EEPROM();
	u8 name[]="NTI Group -- External EEPROM Task With Automated Filling -- Thank you Dr mahmoud for you efforts ";
	write_EEPROM_auto(name);
	u8 name_modified[16];
	u8 i=0;
	u8 up,down;
	while(1)
	{
		i=0;
		while((i+31)!=autoAddress)
		{
			up=i;
			down=i+16;
			ReadEEPROMSTR(up++,16,name_modified);
			disp_strXY(1,1,name_modified);
			ReadEEPROMSTR(down++,16,name_modified);
			disp_strXY(2,1,name_modified);
			_delay_ms(200);
			i++;i++;
		}
	}
}

void tempsensorAPP(void){
	LCD_init();
	u8 temp[60];
	u8 hum[60];
	while(1)
	{
		disp_strXY(1,1,"Humid=     %RH");
		disp_strXY(2,1,"temp=      Deg.c");
		DHT_Represent(hum,temp);
		disp_strXY(1,7,hum);
		disp_strXY(2,6,temp);
		_delay_ms(500);
	}
}


void GPS_APP(void)
{
	u8 value,i,lati_value[20]={0},lati_dir, longi_value[20]={0}, longi_dir, alti[5],time[20] ;
	LCD_init();
	UART_INIT(9600);
	disp_strXY(1,5,"LOADING");
	disp_strXY(2,1,"<<");
	disp_strXY(2,15,">>");
	for (i=3;i<15;i++)
	{
		disp_charXY(2,i,'*');
		_delay_ms(900);
	}
	LCD_CLEAR();
	
	while(1)
	{
		
		GPS_READing(lati_value,&lati_dir,longi_value,&longi_dir,alti,time);
	}//while
}

void I2C_EEPROM_APP(void)
{
	
	I2C_Init();
	LCD_init();
	u8 data1[]="NTI Group";
	u8 data2[15];
	u8 data='x';
	I2C_EEPROM_Page_Write(0x00,data1);
	I2C_EEPROM_Seq_Read(0x00,9,data2);
	disp_strXY(1,1,data2);
}


void Clock_APP(void)
{
	u8 Time[20];
	u8 Calen[20];
	I2C_Init();
	LCD_init();
	//Write_RTC(0x00,0x00,0x00,Thr,0x20,0x05,0x95);
	while (1)
	{
		Read_RTC(Time,Calen);
		disp_strXY(1,1,Time);
		disp_strXY(2,1,Calen);
		_delay_ms(500);
	}
}


void SERVO_APP(void)
{
	Servo_Init();
	u32 angel=0;
	LCD_init();
	ADC_init();
	
	while(1)
	{
		angel= read_analog(ADC0);
		angel=(angel*180)/1023UL;
		disp_strXY(1,1,"angel = ");
		disp_str("    ");
		disp_intXY(1,9,angel);
		servo_Angel(angel);
		disp_intXY(2,9,angel);
	}
}