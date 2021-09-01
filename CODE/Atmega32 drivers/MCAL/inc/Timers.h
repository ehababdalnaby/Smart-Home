/*
 * Timers.h
 *
 * Created: 8/21/2021 7:35:31 PM
 *  Author: Mohamed
 */ 

#ifndef TIMERS_H_
#define TIMERS_H_

#include "includes.h"
typedef enum{NORMAL,Phase_PWM,CTC,FPWM}timer_modes;
typedef enum{STOP,NO_PRESC,_8_PRESC,_16_PRESC,_64_PRESC,_256_PRESC,_1024_PRESC}Prescaler;	
/*this bits define the prescaler*/	
#define CS00 0
#define CS01 1
#define CS02 2	
/*this bits define compare output mode*/
#define COM00 4
#define COM01 5	

/*this bits define compare output mode*/
#define WGM00	6
#define WGM01	3

	
	
#define TOIE0	0



/*Timer 1*/

/*this bits define the mode for the timer*/
#define WGM10   0	//located at TCCR1A
#define WGM11	1
#define WGM12	3	//located at TCCR1B
#define WGM13	4

#define COM1A1	7	//located at TCCR1A
#define COM1A0	6
#define COM1B1	5
#define COM1B0	4


/*this bits define the prescaler*/
#define CS10	0	//located at TCCR1B
#define CS11	1
#define CS12	2



/*Timer0 function*/
void Timer0_Init(timer_modes Tmode);
void Timer0_start(void);
void Timer0_Stop(void);
void set_dutycycle(u8 duty);
void ResetTimer(void);
void timer_delay_us(u32 delay);



/*Timer1 function*/
void Timer1_Init(timer_modes Tmode);
void set_dutycycleTimer1(u16 duty);



//void servo_rotate(u32 angel);
#endif




