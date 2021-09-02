/*
 * EXT_INT.h
 *
 * Created: 8/21/2021 6:03:16 PM
 *  Author: ehab2_phjirwi
 */ 


#ifndef EXT_INT_H_
#define EXT_INT_H_

#include "includes.h"

enum {INT_2=5,INT_0,INT_1}INT_NUM;
enum {low_level,any_level,falling_edge,rising_edge }sense_control;

#define INT0_ISC_MSK	0x03
#define INT0_ISC_POS	0


void INT_init(u8 int_num , u8 sense_control);
void GLOBAL_INT_EN(void);		//global interrupt enable
void GLOBAL_INT_DE(void);		//global interrupt disable
void Callback(void (*ptrfun)(void));


#endif /* EXT_INT_H_ */