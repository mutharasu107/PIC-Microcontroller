#include <htc.h>
#define _XTAL_FREQ 20000000
 __CONFIG(0X1F7A);

int main()
{
	TRISC = 0x00;
	TRISD = 0x00;
	int i,j;
	
	while(1)
	{
		for(i=0; i<1; i++)
		{
			PORTC = 0X01<<i;
			for(int j=4; j<8; j++)
			{
				PORTD = 0X01<<j;
			}
		}
		for(i=1;i<2;i++)
		{
			PORTB = 0X01<<i;
			for(j=5;j<7;j++)
			{
				PORTC = 0X01<<j;
			}
		}for(i=2;i<3;i++)
		{
			PORTC = 0X01<<i;
			for(j=5;j<=7;j++)
			{
				PORTC = 0X01<<j;
			}
		}
		for(i=3;i<4;i++)
		{
			PORTB =0X01<<i;
			for(j=
		}
	}
	while(1);	
}