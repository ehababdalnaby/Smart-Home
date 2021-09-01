/*
 * GLCD.h
 *
 * Created: 8/28/2021 1:01:01 PM
 *  Author: ehab2_phjirwi
 */ 


#ifndef GLCD_H_
#define GLCD_H_

#include "includes.h"

#define FIRSTADD   0x40
#define	LASTADD    0x7F

#define FIRSTLINE   0xB8
#define LASTTLINE   0xBF


#define DISPLAYON  0x3F


#define GLCD_DATA_PORT	PORTB
#define GLCD_DATA_DDR	DDRB
#define GLCD_CTRL_PORT  PORTA
#define GLCD_CTRL_DDR	DDRA
#define CTRL_MASK		0xF0


#define CS1				PA7
#define CS2				PA6
#define RS				PA5
#define EN				PA4


void GLCD_init(void);
void GLCD_Send_CMD(u8 CMD);
void GLCD_Send_data(u8 data);
void GLCD_Latch(void);
void GLCD_GOTOXY(u8 x,u8 y);
void GLCD_Disp_Char_XY(u8 x,u8 y,u8 data);
void GLCD_Disp_image(u8 *image);
void GLCD_Disp_customsize(u8 hight,u8 width,u8 *image);
#endif /* GLCD_H_ */