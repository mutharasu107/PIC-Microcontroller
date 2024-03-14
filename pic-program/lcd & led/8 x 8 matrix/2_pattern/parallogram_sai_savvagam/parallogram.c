#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0X7F1A);

int main()
{
	TRISB = 0X00;
	TRISC = 0X00;
	
	while(1)
	{
		for(int i=3; i<4; i++)
		{
			PORTB = 0X01<<i;
			for(int j=2; j<8; j++)
			{
				PORTC = 0X01<<j;
				__delay_ms(50);
			}
		}
		
		for(int i=2; i<3; i++)
		{
			PORTB = 0X01<<i;
			for(int j=0; j<8; j++)
			{
				if(j==1||j==2==j==3||j==4||j==5||j==6)
				{
					PORTC = 0X01<<j;
					__delay_ms(1);
				}
			}
		}
		
		for(int i=2; i<3; i++)
		{
			PORTB = 0X01<<i;
			for(int j=0; j<6; j++)
			{
				PORTC = 0X01<<j;
					__delay_ms(1);
			}
		}
		
		while(1);
	}
}