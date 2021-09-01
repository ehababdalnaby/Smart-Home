/*
 * GLCD.c
 *
 * Created: 8/28/2021 1:01:22 PM
 *  Author: ehab2_phjirwi
 */ 

#include "GLCD.h"




void GLCD_init(void)
{
	pinsDirection(&GLCD_DATA_DDR,0xFF,OUTPUT);
	pinsDirection(&GLCD_CTRL_DDR,CTRL_MASK,OUTPUT);
	GLCD_Send_CMD(DISPLAYON);
}
void GLCD_Send_CMD(u8 CMD)
{
	GLCD_DATA_PORT=CMD;
	writePin(RS,LOW);
	GLCD_Latch();
	_delay_us(1);
}
void GLCD_Send_data(u8 data)
{
	GLCD_DATA_PORT=data;
	writePin(RS,HIGH);
	GLCD_Latch();
	_delay_us(1);
}
void GLCD_Latch(void)
{
	writePin(EN,HIGH);
	writePin(EN,LOW);
}
void GLCD_GOTOXY(u8 x,u8 y)
{
	
	if (y>64)
	{
		writePin(CS1,LOW);
		writePin(CS2,HIGH);
		y=y-64;
	}
	else
	{
		writePin(CS1,HIGH);
		writePin(CS2,LOW);
	}
	GLCD_Send_CMD(FIRSTLINE+(x-1));
	GLCD_Send_CMD(FIRSTADD+(y-1));
}
void GLCD_Disp_Char_XY(u8 x,u8 y,u8 data)
{
	GLCD_GOTOXY(x,y);
	GLCD_Send_data(data);
}

void GLCD_Disp_image(u8 *image)
{
	u8 i=0,j=0;
	for (i=0;i<8;i++)
	{
		for (j=0;j<128;j++)
		{
			GLCD_Disp_Char_XY(i+1,j+1,image[(j+(i*128))]);
		}
	}
}


void GLCD_Disp_customsize(u8 hight,u8 width,u8 *image)
{
	//GLCD_GOTOXY(1,1);
	u8 i=0,j=0;
	for (i=0;i<(hight/8);i++)
	{
		for (j=0;j<width;j++)
		{
			GLCD_GOTOXY(1,j+1);
			GLCD_Disp_Char_XY(i+1,j+1,image[(j+(i*width))]);
		}
	}
}