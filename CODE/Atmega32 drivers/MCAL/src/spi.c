#include "SPI.h"
void SPI_Init(SPI_Mode spiMode){
	switch(spiMode){
	case SPI_MASTER:
	SETBit(SPI_DDR,SPI_SS);
	SETBit(SPI_DDR,SPI_SCK);
	SETBit(SPI_DDR,SPI_MOSI);
	CLRBit(SPI_DDR,SPI_MISO);
	
		SETBit(SPCR,SPR0);
		SETBit(SPCR,MSTR);
		SETBit(SPCR,SPE);
	    writePin(PB4,HIGH);

	break;
	case SPI_SLAVE:
	CLRBit(SPI_DDR,SPI_SS);
	CLRBit(SPI_DDR,SPI_SCK);
	CLRBit(SPI_DDR,SPI_MOSI);
	SETBit(SPI_DDR,SPI_MISO);
	
		CLRBit(SPCR,MSTR);
		SETBit(SPCR,SPE);

	break;
	}
}
u8 SPI_Transceive(u8 data){
		SPDR = data;
		while(!(SPSR & (1<<SPIF)));
		_delay_ms(1);
		return SPDR;
}
