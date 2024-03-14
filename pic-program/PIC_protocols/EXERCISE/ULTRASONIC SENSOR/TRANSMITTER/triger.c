
#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0X1F7A);

void uart_recei()
{
	TRISC6 = 0;    
	TRISC7 = 1;   
	TXSTA = 0X20; 
	RCSTA = 0X80; 
	SPBRG = 31;
	TXIF = 0;
	RCIF = 0;
}

void uart_tx(unsigned int val)
{
	TXREG = val;
	while(TXIF == 0);
	TXIF = 0;
}

int main()
{
	unsigned int Distance;
	float time,soundspeed;
	time = 0.025;
	soundspeed = 343;
	uart_recei();
	while(1)
	{
		Distance = 0.025 * 343;
		uart_tx(Distance);
		
		__delay_ms(1000);
	}
}