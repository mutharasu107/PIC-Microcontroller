/*#include <htc.h>
#define __XTAL__FREQ 20000000
__CONFIG (0X1F74);
void uart_tx(unsigned char data);
unsigned uart_rx(void);
void uart_config();
void uart_print(unsigned char *str);

int main()
{
	TRISC = 0;
	uart_config();
	uart_print("SOL");
	while(1);
}
void uart_config()
{
	TRISC6 = 0;
	TRISC7 = 1;
	TXSTA = 0X20;
	RCSTA = 0X90;
	SPBRG = 31;
	TXIF = 0;
	RCIF = 0;	
}
void uart_tx(unsigned char data)
{
	TXREG = data;
	while(!TXIF);
	TXIF = 0;
}
unsigned uart_rx(void)
{
	while(!RCIF);
	RCIF = 0;
	return RCREG;
}
void uart_print(unsigned char *str)
{
	while(*str)
	{
		 uart_tx(*str++);
	}
}*/

#include <htc.h>
#define _XTAL_FREQ 2000000
__CONFIG (0X1F7A);

//unsigned char uart_rx(void);
void uart_init(void);

void uart_init()
{
	TRISC6 = 1;//High for 25 pin RC6/TX/CK
	TRISC7 = 0;//lOW FOR 26 PIN RC7/RX/DT
	TXSTA = 0X00;//TX Status & Control Reg (add 98h)
	RCSTA = 0X00;//RC Status & Control Reg (add 18h)
	SPBRG = 31;//Badu rate set 9600 bit for second
	TXEN = 1;//TX enable bit 
	SPEN = 1;//Serial Port Enable Bit
	TXIF = 0;//TX Interrupt Flage Bit
	RCIF = 0;//RC Interrupt Flage Bit	
}
void uart_tx(unsigned char val)
{
	TXREG = val;//Transmit buffer
	while(TXIF == 0);//condition checking
	TXIF = 0;
}
void main()
{
	uart_init();
	uart_tx('S');
	__delay_ms(100);
	uart_tx('L');
	__delay_ms(100);
	uart_tx(' ');
	__delay_ms(100);
	uart_tx('m');
	__delay_ms(100);
	uart_tx('u');
	__delay_ms(100);
	uart_tx('t');
	__delay_ms(100);
	uart_tx('h');
	__delay_ms(100);
	uart_tx('u');
	__delay_ms(100);
	
	while(1);
}