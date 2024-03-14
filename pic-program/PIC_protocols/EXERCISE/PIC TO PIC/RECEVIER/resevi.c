//Send the data from controller
#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0X1F7A);

void uart_recei()
{
	TRISC6 = 0;   //TX 
	TRISC7 = 1;   //RX
	TXSTA = 0X20; //Transmit Enable Bit = 1.
	RCSTA = 0X80; 
	SPBRG = 31;
	TXIF = 0;
	RCIF = 0;
}

void uart_tx(unsigned char val)
{
	TXREG = val;
	while(TXIF == 0);
	TXIF = 0;
}

int main()
{
	uart_recei();
	while(1)
	{
		uart_tx('R');
	    __delay_ms(1000);
	    uart_tx('Y');
	    __delay_ms(1000);
	    uart_tx('G');
	    __delay_ms(1000);
	    uart_tx(' ');
	    __delay_ms(1000);
	}
}