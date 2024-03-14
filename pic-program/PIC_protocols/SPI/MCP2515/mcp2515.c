#include <htc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000
__CONFIG(0X1F7A);
#define SS RA5

void spi_init(void);
unsigned char spi_trans(unsigned char);
void delay(void);

int main()
{
	spi_init();
	SS=1;
	__delay_ms(10);
	SS = 0;
	
    spi_trans(0x03); // Read instruction 
    spi_trans(0x7f); // select 8 bit address first 
    spi_trans(0x00); // don't care bit 
    
    SS=1;
    
    while(1);
}

void spi_init()
{
		
	TRISA5  = 0;
	TRISC3  = 0;
	TRISC4  = 1; // Master in slave out 
	TRISC5  = 0; // Master out slave in
	SSPEN  = 1; // Synchronous Serial Port Enable
	SSPSTAT = 0X00;
	SSPCON  = 0X12; // Clock Polarity Select bit	
	SSPIE  = 0;
	SSPIF  = 0;
	SSPBUF = 0;
//	SSPEN  = 1; // Synchronous Serial Port Enable bit
}

unsigned char spi_trans(unsigned char data)
{
	SSPBUF = data;
	while(SSPIF == 0);
	SSPIF = 0;
}