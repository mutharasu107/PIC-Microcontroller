#include <htc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

int main()
{
	int i=0;
	TRISB = 0X00;
	
	while(1)
	{
		for(i=0; i<8; i++)
		{
			__delay_ms(1000);
			PORTB = 0x01<<i;
			__delay_ms(1000);
		}
	}
	while(1);
}
