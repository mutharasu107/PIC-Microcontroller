#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0X7F1A);

int main()
{
	TRISB = 0x00;
	TRISC = 0x00;
	
	while(1)
	{	
		for(int i=7, j=3; i<7, j<8; i++, j++)
		{
			PORTB = 0X01<<i;
			PORTC = 0X01<<j;
			__delay_ms(1);
		}
		
		for(int i=6; i<7; i++)
		{
			PORTB = 0x01<<i;
			for(int j=2; j<5; j++, j++)
			{
				PORTC = 0x01<<j;
				__delay_ms(1);
			}
		}
		
		for(int i=5; i<6; i++)
		{
			PORTB = 0x01<<i;
			for(int j=1; j<6; j++)
			{
				if(j == 1 || j==5)
				{
					PORTC = 0x01<<j;
					__delay_ms(1);
				}
			}
		}
	
		for(int i=4; i<5; i++)
		{
			PORTB = 0x01<<i;
			for(int j=0; j<7; j++)
			{
				if(j == 0 || j==6)
				{
					PORTC = 0x01<<j;
					__delay_ms(1);
				}
			}
		}
	
		for(int i=3; i<4; i++)
		{
			PORTB = 0x01<<i;
			for(int j=0; j<8; j++)
			{
				if(j == 0 || j==7)
				{
					PORTC = 0x01<<j;
					__delay_ms(1);
				}
			}
		}
		
		for(int i=2; i<3; i++)
		{
			PORTB = 0x01<<i;
			for(int j=0; j<8; j++)
			{
				if(j == 0 || j==3 || j==7)
				{
					PORTC = 0x01<<j;
					__delay_ms(1);
				}
			}
		}
		
		for(int i=1; i<2; i++)
		{
			PORTB = 0x01<<i;
			for(int j=0; j<8; j++)
			{
				if(j == 1 || j==2 || j==4 || j==5 || j==6)
				{
					PORTC = 0x01<<j;
					__delay_ms(1);
				}
			}
		}
	}
	while(1);
}	
