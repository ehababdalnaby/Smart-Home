/*
 * GPS.c
 *
 * Created: 25/08/2021 11:15:44 ص
 *  Author: Administrator
 */ 
#include "GPS.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"


void GPS_READing(u8* lati_value,u8* lati_dir,u8* longi_value,u8* longi_dir,u8* alti,u8* time)
{
	u8 value,i;
	if(UART_RX()=='$' && UART_RX()=='G'&&UART_RX()=='P'&&UART_RX()=='G'&&UART_RX()=='G'&&UART_RX()=='A')
	{
		UART_RX();
		//time
		time[0]=UART_RX();
		value=time[0];
		for(i=1;value!=',';i++)
		{
			time[i]=UART_RX();
			value=time[i];
		}
		time[i-1]=' ';
		//latitude
		lati_value[0]=UART_RX();
		value=lati_value[0];
		for(i=1;value!=',';i++)
		{
			lati_value[i]=UART_RX();
			value=lati_value[i];
		}
		lati_value[i-1]=' ';
		lati_dir=UART_RX();
		value=UART_RX();//remove next comma (,)
		//longitude
		longi_value[0]=UART_RX();
		value=longi_value[0];
		for(i=1;value!=',';i++)
		{
			longi_value[i]=UART_RX();
			value=longi_value[i];
		}
		longi_value[i-1]=' ';
		longi_dir=UART_RX();
		 //convert_time_to_UTC(time);
		 //disp_strXY(1,1,time);
		 //convert_to_degrees(lati_value);
		 strfToint(lati_value);
		 disp_strXY(1,1,lati_value);
		 disp_char(',');
		 disp_char(lati_dir);
 		 //convert_to_degrees(longi_value);
		 strfToint(longi_value);
		 disp_strXY(2,1,longi_value);
		 disp_char(',');
		 disp_char(longi_dir);
	}//if
	
}





void strfToint(u8* strf) //"12312.1234" or "1212.1234" --> "123.(121234/##)" or "12.(121234/##)"//converts from string of (degrees, minutes and fraction of minutes ) to string of(degrees and fraction of degrees)// so the important numbers are 12.1234 they have to be converted to int and making some operations(/ and *)// without using float or double then they need to be converted back to string but after this string"12."// so we will handle this number 121234{	u8 i=0;	u8 dotIndex;	u32 Num=0;	u32 Num2=0;	while (strf[i]!='.')	i++;	dotIndex=i;	Num2=atoi(&(strf[dotIndex+1]));	Num=atoi(&(strf[dotIndex-2]));	Num=(Num*10000+Num2)*100/6UL;	strf[dotIndex-2]='.';	i=dotIndex-1;	// the first 2 digits are important altough if they are zero cuz they will be printed	// as a fraction after .	if (Num/100000==0)	{		strf[dotIndex-1]='0';		strf[dotIndex]='0';		i=dotIndex+1;	}	else if (Num/1000000==0)	{		strf[dotIndex-1]='0';		i=dotIndex;	}	sprintf(&strf[i],"%lu",Num);	//disp_strXY(2,1,strf);}




void convert_to_degrees(u8 *raw)//9000.1506  as string
{
	
	double value;
	float decimal_value,minutes;
	
	u16 degrees;
	
	float position;
	value = atof(raw);  //9000.1506  as a float value  
	
	
	decimal_value = (value/100UL);  //90.001506
	degrees= (int)(decimal_value);  //90
	minutes = (decimal_value - (int)decimal_value)/0.6;  //90.001506-90=0.001506/0.6=0.00251
	position = (float)degrees + minutes;  //90+0.00251=90.00251
	
	dtostrf(position, 7,6,raw);  //convert float to string  (float value,minwidth,precision,buffer)
}























void convert_time_to_UTC(u8 *time)
{
	u16 hour, min, sec;
	u32 Time_value;
	
	Time_value = atol(time);      
	hour = (Time_value / 10000);          
	min  = (Time_value % 10000) / 100;    
	sec  = (Time_value % 10000) % 100;    

	sprintf(time, "%d:%d:%d", hour,min,sec);
	
}