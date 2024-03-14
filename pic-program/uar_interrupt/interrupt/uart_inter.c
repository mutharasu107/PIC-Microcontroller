#include <htc.h>
#define _XTAL_ 20000000
__CONFIG(0x1F7A);

void interrupt_config(void);
void port_config(void);
void interrupt ISR(void);
void uart_tx(unsigned char val);
void uart_rx(void);
void uart_init();
void uart_print(unsigned char *str);
void init(void);

void main()
{
	init();
	
	while(1)
	{
	}
}

void init(void)
{
	port_config();
	uart_init();
	interrupt_config();
}

void interrupt_config(void)
{
	// Disable all interrupt flag and Clear all interrupt flage
	INTCON 	= 0;
	PIE1 	= 0;
	PIE2 	= 0;
	PIR1 	= 0;
	PIR2 	= 0;
	
	// USART Receive Interrupt Enable bit
	RCIE = 1;
	
	// Peripheral Interrupt Enable bit
	PEIE = 1;
	
	// Global Interrupt Enable bit
	GIE = 1; 
}

void port_config(void)
{
	// Portconfigure as a output
	TRISC = 0;
}

void interrupt ISR(void)
{
	// Global Interrupt Disable bit
	GIE = 0;
	if(RCIF == 1)
	{
		// Clear the interrupt flag bit
		RCIF = 0;
		unsigned char data = RCREG;
		//required logic while uart interrut happens
		uart_print(data);
		
	}
	// Global Interrupt Enable bit
	GIE = 1;
}

void uart_init()
{
	TRISC6 = 0;//High for 25 pin RC6/TX/CK
	TRISC7 = 1;//lOW FOR 26 PIN RC7/RX/DT
	TXSTA = 0X00;//TX Status & Control Reg (add 98h)
	RCSTA = 0X00;//RC Status & Control Reg (add 18h)
	SPBRG = 31;//Badu rate set 9600 bit for second
	TXEN = 1;//TX enable bit 
	SPEN = 1;//Serial Port Enable Bit	
}

void uart_tx(unsigned char val)
{
	TXREG = val;//Transmit buffer
	while(TXIF == 0);//condition checking
	TXIF = 0;
}

void uart_print(unsigned char *str)
{
	while(*str)
	{
		 uart_tx(*str++);
	}
}