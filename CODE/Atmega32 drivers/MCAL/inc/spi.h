#ifndef __SPI_H__
#define __SPI_H__

#include "includes.h"

#define SPI_PORT		PORTB
#define SPI_DDR			DDRB

#define SPI_SS			(PB4-PORTB_OFFSET)
#define SPI_MOSI		(PB5-PORTB_OFFSET)
#define SPI_MISO		(PB6-PORTB_OFFSET)
#define SPI_SCK			(PB7-PORTB_OFFSET)
#define SPE				6
#define SPIF			7
#define SPR0			0
#define	MSTR			4


typedef enum{
	SPI_MASTER, SPI_SLAVE
}SPI_Mode;

void SPI_Init(SPI_Mode spiMode);
u8 SPI_Transceive(u8 data);


#endif