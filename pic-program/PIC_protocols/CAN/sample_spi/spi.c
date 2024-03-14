#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF & CPD_OFF & WRT_OFF & CP_OFF);
#define SS RC1

void spi_init(void);
unsigned char spi_trans(unsigned char);
void delay(void);
unsigned char a,b,c; 
unsigned uart_rx(void);
void uart_tx(unsigned char data);
void uart_init();
void uart_print2(unsigned char s);

int main()
{
    uart_init();
	spi_init();
	SS=1;
	__delay_ms(10000);
	SS = 0;
	
    a = spi_trans(0x03); // Read instruction 
    b = spi_trans(0x0E); // select 8 bit address first 
    c = spi_trans(0x00); // don't care bit 
    
    uart_print2(a);
    uart_print2(b);
    uart_print2(c);
    
    SS=1;
    
    while(1);
}

void spi_init()
{
		
	TRISC1  = 0;
    TRISC0 = 0;
	TRISC3  = 0;
	TRISC4  = 1; // Master in slave out 
	TRISC5  = 0; // Master out slave in
    SSPEN  = 1; // Synchronous Serial Port Enable
	SSPSTAT = 0X00;
	SSPCON  |= 0X12; // Clock Polarity Select bit	
	SSPIE  = 0;
	SSPIF  = 0;
    RC0 = 1;
	SSPEN  = 1; // Synchronous Serial Port Enable bit
}

unsigned char spi_trans(unsigned char data)
{
	SSPBUF = data;
	while(SSPIF == 0);
	SSPIF = 0;
    return SSPBUF;
}
void uart_tx(unsigned char data)
{
	 TXREG=data;
	 while(!TXIF);
	 TXIF=0;
}

unsigned uart_rx(void)
{
	while(!RCIF);
	RCIF=0;
	return RCREG;
}

void uart_init()
{
	TRISD1=1;
	TRISD0=0;
	TRISC6=0;
	TRISC7=1;
	TXSTA=0X20;
	RCSTA=0X90;
	SPBRG=31;
	TXIF=0;
	RCIF=0;
}

void uart_print2(unsigned char s)
{
	for(int i=0; i<8; i++)
	{
		if(s<<i==1)
		{
		 	uart_tx('1');
		 }
		 else
		 {
		 	uart_tx('0');
		 }
	}
}