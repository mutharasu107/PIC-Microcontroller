#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0x1F74);

void uart_init(void);
void uart_rx(void);
void uart_tx(unsigned char val);
void uart_print(unsigned char *str);

void uart_init()
{
	TRISC6 = 0; 	// High for 25 pin RC6/Tx/CK
	TRISC7 = 1; 	// LOW for 26 pin RC7/Rx/DT
	TXSTA  = 0x20; 	// TX status & control Reg(add 98H)
	RCSTA  = 0x90; 	// RC status & control Reg(add 18H)
	SPBRG  = 31; 	// Badu rate set 9600 bit for second
	TXIF   = 0;		// TX interrupt flage bit
	RCIF   = 0; 	// RC interrupt flage bit
}


void uart_tx(unsigned char val)
{
	TXREG = val; // Transmit buffer
	while(TXIF == 0); // condition checking
	TXIF = 0; // clear the flage bit
}

void uart_rx()
{
	RCIF = 0; 	// reciver interrupt flage bit
	while(RCIF == 0);	// flage bit checking condition 
}

void uart_print(unsigned char *str)
{
	while(*str)
	{
		uart_tx(*str++);
	}
}

int main()
{
	TRISC = 0;
	uart_init();
	uart_print("school of ");
	uart_print("Dharmapuri");
	while(1);	
}