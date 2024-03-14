#include <htc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000
__CONFIG(0X1F7A);
#define SS RC1

void spi_init(void);
unsigned char spi_trans(unsigned char);
void delay(void);
unsigned char spi_recv();
void uart_tx(unsigned char val);
void uart_init(void);
void uart_print(unsigned char *s);
unsigned char m_str[]="School of Linux\r\n";
unsigned char p_msg[]="SPI Master Initializing\r\n";

int main()
{
	unsigned char i,j,recv,b;
	int a[3];
	uart_init();
	unsigned char buffer[50];
	__delay_ms(100);
	
	uart_print(m_str);
	uart_print(p_msg);
	
	__delay_ms(10);
	
	spi_init();
	SS=1;    
    __delay_ms(10);
    SS = 0;
    /*spi_trans(0x06);
    SS = 1;
    SS = 0;
    
    spi_trans(0x02);
    spi_trans(0x00);
    spi_trans(0x08);
    
    spi_trans('M');
    spi_trans('B');
    
    SS = 1;
    
    SS = 0;*/
    spi_trans(0x03); /*read data to memory array*/
    
    spi_trans(0x00);
    spi_trans(0x08);
    
    spi_recv();
    
    spi_recv();
    spi_recv();
    
//    uart_print(b);
    SS = 1;
    for(b=0; b<2; b++)
    {
	    a[b] = spi_recv();
	}
	
	sprintf(buffer,"%x : %x\r",a[0],a[1]);//data read eeprom %x\r",spi_recv);
	uart_print(0x08);
	
	SS = 0;
	b = spi_trans(0x03);
	SS = 1;
	SS = 0;
	uart_print(b);
//    uart_print(*spi_recv);
//    SS = 1;
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
	SSPEN  = 1; /*Synchronous Serial Port Enable bit*/
}

unsigned char spi_trans(unsigned char data)
{
	SSPBUF = data;
	while(SSPIF == 0);
	SSPIF = 0;
}

unsigned char spi_recv()
{
	SSPBUF = 0xFF;
	while(SSPIF == 0);
	SSPIF = 0;
	return SSPBUF;
}

void uart_tx(unsigned char val)
{
	TXREG = val;
	while(TXIF == 0);
	TXIF = 0;
}

void uart_init()
{
	TRISC6 = 0;
	TRISC7 = 1;
	TXSTA = 0X20;
	RCSTA = 0X80;
	SPBRG = 31;
	TXIF = 0;
	RCIF = 0;
}

void uart_print(unsigned char *s)
{
	while(*s)
	{
		uart_tx(*s);
		__delay_ms(100);
		*s++;
	}
}