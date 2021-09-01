/*
 * RTC.h
 *
 * Created: 8/26/2021 5:56:04 PM
 *  Author: Mahmoud-PC
 */ 


#ifndef RTC_H_
#define RTC_H_

#include "includes.h"

#define RTC_READ_ADDRESS     0xD1
#define RTC_WRITE_ADDRESS    0xD0

#define RTC_SECONDS_ADDRESS	 0x00
#define RTC_MINUTES_ADDRESS  0X01
#define RTC_HOURS_ADDRESS	 0X02
#define RTC_DAY_ADDRESS		 0X03
#define RTC_DATE_ADDRESS	 0X04
#define RTC_MONTH_ADDRESS	 0X05	
#define RTC_YEAR_ADDRESS	 0X06

typedef enum{Sun=1,Mon,Tus,Wed,Thr,Fri,Sat}DAYS_NAMES;


void Write_RTC(u8 Seconds,u8 Minutes,u8 Hours,u8 Day,u8 Date,u8 Month,u8 Year);
void Read_RTC(u8* Time,u8* Calen);

#endif /* RTC_H_ */