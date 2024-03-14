#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0x1F74);

void uart_tx(unsigned char val);
void uart_init(void);

void uart_init()
{
	TRISC6 = 1; 	// High for 25 pin RC6/Tx/CK
	TRISC7 = 0; 	// LOW for 26 pin RC7/Rx/DT
	TXSTA  = 0x00; 	// TX status & control Reg(add 98H)
	RCSTA  = 0x00; 	// RC status & control Reg(add 18H)
	SPBRG  = 31; 	// Badu rate set 9600 bit for second
	TXEN   = 1;		// TX enable bit
	SPEN   = 1; 	// Serial flag bit
	TXIF   = 0;		// TX interrupt flage bit
	RCIF   = 0; 	// RC interrupt flage bit
}


void uart_tx(unsigned char val)
{
	TXREG = val; // Transmit buffer
	while(TXIF == 0); // condition checking
	TXIF = 0; // clear the flage bit
}

int main()
{
	uart_init();
	uart_tx('S');
	__delay_ms(100);
	uart_tx('L');
	__delay_ms(100);
	uart_tx(' ');
	__delay_ms(100);
	uart_tx('L');
	__delay_ms(100);
	uart_tx('I');
	__delay_ms(100);
	uart_tx('N');
	__delay_ms(100);
	uart_tx('U');
	__delay_ms(100);
	uart_tx('X');
	__delay_ms(100);
	
	while(1);
}