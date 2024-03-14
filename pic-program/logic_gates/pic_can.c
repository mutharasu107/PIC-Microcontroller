#include<htc.h>	
#define _XTAL_FREQ 2000000
__CONFIG(0x1F7A);
#define SS RC1

void usart_print(unsigned char data);

void uart_init()
{
	TRISC6 = 0;
	TXSTA = 0X20;
	RCSTA = 0X80;
	SPBRG = 31;
	TXIF = 0;
}
void uart_tx(unsigned char msg)
{
	TXREG = msg;
	while(TXIF == 0);
	TXIF = 0;
}
void uart_data(unsigned char *data)
{
	while(*data)
		uart_tx(*data++);
}
void spi_init(void)
{	
	TRISC1  = 0; 	// Slave selection pin
	TRISC3  = 0; 	// SCK -> Output
	TRISC4  = 1;	// Serial Data In
	TRISC5  = 0;	// Serial Data Out

	SSPSTAT = 0x00; // Input data sampled at end of data output time
	SSPCON  = 0x12; // SPI Master mode, clock = FOSC/64,Clock Polarity  Idle state for clock is a high level
	SSPIE   = 0;
	SSPIF   = 0;
	SSPBUF  = 0;;
	SSPEN   = 1;
	SS      = 1;
	__delay_ms(1000);	
}
unsigned char spi_tx(unsigned char data)
{	
	SSPBUF = data;
	while(SSPIF==0); //  Check to Buffer Full detect bit
	SSPIF = 0;
	while(!BF);
	BF = 0;
	return (SSPBUF);
}

unsigned char spi_read(void)
{
	unsigned char data;
	SS = 0;
	SSPBUF = 0x10;
	while(!(SSPSTAT & 1));
	data = SSPBUF;
	SS = 1;
	return (data);
}

unsigned char cmd (unsigned char cmd)
{
	__delay_ms(500);
	SS = 0;		
	SSPBUF = cmd;
	while(SSPIF==0); //  Check to Buffer Full detect bit
	while(BF != 1);
	SSPIF = 0;
	BF = 0;
	SS = 1;
	__delay_ms(300);
	return (SSPBUF);
}
int main()
{
	unsigned char spi_data = 0;
	uart_init();
	spi_init();
	uart_data("UART TESTING\n\r");

	cmd(0xC0);
	__delay_ms(300);
	usart_print(spi_data);
//	cmd(0x03);
//	usart_print(spi_data);
//	cmd(0X0E);
//	usart_print(spi_data);
//	spi_data = cmd(0x81);
//	usart_print(spi_data);
	while(1);
}
void usart_print(unsigned char data)
{
	for(int i=7;i>=0;i--)
	{
		if(data & 1<<i)
			uart_tx('1');
		else
			uart_tx('0');
	}
	uart_data("\n\r");
}