#include <htc.h>
#define __XTAL__FREQ 20000000

void uart_tx(unsigned char val);
void uart_rx();
void uart_config();
void uart_print(unsigned char *str);

int main()
{
	TRISC = 0;//TRISC OUT PUT
	uart_config();//CONFIGURE THE OUT OR INPUT FILE
	uart_print("school of linux");//PRINT THE STRING
	while(1);//INFINITI LOOP
}
void uart_config()
{
	TRISC6 =   0;//OUT PUT OF TRANSMITT
	TRISC7 =   1;//INPUT OF RECEVIER
	TXSTA = 0X20;//TRANSMITT STATUS VALUE LOAD
	RCSTA = 0X90;//RECEVIER STATUS VALUE LOAD
	SPBRG = 0X31;//BADU RATE GENTRATOR
}
void uart_tx(unsigned char val)
{
	TXIF = 0;//TRANSMITT INTERRUPT FLAGE EQUAL TO ZERO
	while(TXIF==0);//CONDITIATION
	TXREG = val; 
}
void uart_rx()
{
	RCIF = 0;//RECEVIER INTERRUPT FLAGE BIT EQUAL TO ZERO
	while(RCIF==0);//CONDITIATION CHECKING
}
void uart_print(unsigned char *str)
{
	while(*str)
	{
		uart_tx(*str++);
	}
}