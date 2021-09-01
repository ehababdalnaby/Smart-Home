/*
 * Timers.c
 *
 * Created: 8/21/2021 7:35:54 PM
 *  Author: Mohamed
 */

 
#include "Timers.h"
#include <avr/interrupt.h>
#include "DIO.h"
volatile static  u32 overflow=0;


ISR(TIMER0_OVF_vect)
{
	overflow++;	
}






void Timer0_Init(timer_modes Tmode)
{
	switch(Tmode)
	{
		case NORMAL:
		CLRBit(TCCR0,WGM01);
		CLRBit(TCCR0,WGM00);
		
		Timer0_Stop();
		
		SETBit(TIMSK,TOIE0);
		sei();
		break;
		case CTC:
		
		break;	
		case FPWM:
		SETBit(TCCR0,WGM01);
		SETBit(TCCR0,WGM00);
		
		SETBit(TCCR0,COM01);
		CLRBit(TCCR0,COM00);
		
		SETBit(TCCR0,CS00);
		CLRBit(TCCR0,CS01);
		SETBit(TCCR0,CS02);
		break;
	}
}

void Timer1_Init(timer_modes Tmode)
{
	/*fast PWM*/
	CLRBit(TCCR1A,WGM10);
	SETBit(TCCR1A,WGM11);
	CLRBit(TCCR1B,WGM12);
	SETBit(TCCR1B,WGM13);
	/*non inverting mode & Clear OC1A on compare match*/
	 CLRBit(TCCR1A,COM1A0);
	 SETBit(TCCR1A,COM1A1); 
	 
	 /*set the prescaler*/
	 SETBit(TCCR1B,CS10); //prescaler 64
	 SETBit(TCCR1B,CS11);
	 CLRBit(TCCR1B,CS12);
     TCNT1=0x00;
	 ICR1=4999;    // fOCPWM=50Hz   fclk=16MHz   N=64           //fOCPWM=fclk/(N(1 + TOP))                          
}


void Timer0_Start(void)
{
	CLRBit(TCCR0,CS00);
	SETBit(TCCR0,CS01);
	CLRBit(TCCR0,CS02);
}
void Timer0_Stop(void)
{
	CLRBit(TCCR0,CS00);
	CLRBit(TCCR0,CS01);
	CLRBit(TCCR0,CS02);
}

void ResetTimer(void)
{
	TCNT0=0x00;
	overflow=0;
}
void timer_delay_us(u32 delay)
{
	ResetTimer();
	Timer0_Start();
	while(delay > ((TCNT0+1+overflow*256UL)/2UL));	
	Timer0_Stop();
}
void set_dutycycle(u8 duty)
{
	OCR0=(duty*255UL)/100;
}


void set_dutycycleTimer1(u16 duty)       //1->2         overal time 20->4999
{                                                          //        0->125
	OCR1A=125+(125*duty)/180;                              //        180->250
}														//       90->188

