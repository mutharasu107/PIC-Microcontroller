#include <htc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000
__CONFIG(0X1F7A);
#define SS RC1

void spi_init(void);
unsigned char spi_trans(unsigned char);
void delay(void);

int main()
{
	spi_init();
	SS=1;
	__delay_ms(10);
	SS=0;
	spi_trans(0x06); /*Set the write enable latch*/
    SS = 1;
    SS = 0;
    spi_trans(0x02); /*Write data to memory array beginning at selected address*/
    spi_trans(0x00); /*select 16 bit address first */
    spi_trans(0x08); /*select 16 bit address second*/
    spi_trans('M');  /*write value first*/
    spi_trans('B');  /*write value second*/
    SS=1;
    
    while(1);
}

void spi_init()
{
	TRISC3  = 0;
	TRISC4  = 1; /*SS must have TRISC<4> bit set*/
	TRISC5  = 0;
	TRISC1  = 0;
	SSPSTAT = 0X00;
	SSPCON  = 0X10; /*Clock Polarity Select bit*/	
	SSPIE  = 0;
	SSPIF  = 0;
	SSPBUF = 0;
	SSPEN  = 1; /**Synchronous Serial Port Enable bit*/
}

unsigned char spi_trans(unsigned char data)
{
	SSPBUF = data;
	while(SSPIF == 0);
	SSPIF = 0;
}