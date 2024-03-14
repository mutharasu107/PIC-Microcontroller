#include<htc.h>
#define __XTAL__FREQ 2000000
__CONFIG (FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF & WRT_OFF);

//function inicliation 
void uart_tx(unsigned char val);
void uart_rx();
void uart_config();
void uart_print(unsigned char *str);

int main()
{
	//function declaraction 
	TRISC = 0;
	uart_config();
	uart_print("school of linux ");
	while(1);
}
//function expression
void uart_config( )
{
	TRISC6 = 0;        //output of the transmitt pin
	TRISC7 = 1;        //input of the recevier pin
	TXSTA = 0X20; //transmitt value load
	RCSTA = 0X90; //recevier value load
	SPBRG = 31;      //baud rate generator
}
void uart_tx(unsigned char val)
{
	TXIF=0; //transimitt flage will set
	while(TXIF==0);//condition checking
     	TXREG = val; //value load in to txreg register
}
void uart_rx()
{
	RCIF = 0;//rceiver interrupt flage bit
	while(RCIF==0);//flage bit cheking for condititon 
}
void uart_print(unsigned char *str)
{
	while(*str)//while string is cheking complete or not
	{
		uart_tx(*str++);//print the given the in put
	}
}