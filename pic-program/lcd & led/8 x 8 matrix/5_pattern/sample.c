#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1f7a);

int main()
{
	int a=8;
	TRISB = 0X00;
	TRISC = 0X00;
	while(1)
	{
		for(int i=0; i<8; i++, i++)
		{
			PORTB = 0x01<<i;
			for(int j=0; j<8; j++, j++)
			{
				PORTC = 0x01<<j;
				__delay_ms(1);
			}
			__delay_ms(1);
		}
//		__delay_ms(1);
		for(int i=1; i<8; i++, i++)
		{
			PORTB = 0x01<<i;
			for(int j=1; j<8; j++, j++)
			{
				PORTC = 0x01<<j;
				__delay_ms(1);
			}
			__delay_ms(1);
		}
	}
	while(1);
}