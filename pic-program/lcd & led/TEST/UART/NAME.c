#include <htc.h>
#define __XTAL__FREQ 20000000
__CONFIG (0X1F74);
void uart_tx(unsigned char data);
void uart_rx();
void uart_config();
void uart_print(unsigned char *str);

int main()
{
	TRISC = 0;
	uart_config();
	uart_print("SHACHUDHANANDHAN M");
	while(1);
}
void uart_config()
{
	TRISC6 = 0;
	TRISC7 = 1;
	TXSTA = 0X20;
	RCSTA = 0X90;
	SPBRG = 31;
}
void uart_tx(unsigned char data)
{
	TXIF = 0;
	while(TXIF == 0);
	TXREG = data;
}
void uart_rx()
{
	RCIF = 0;
	while(RCIF == 0);
}
void uart_print(unsigned char *str)
{
	while(*str)
	{
		 uart_tx(*str++);
	}
}