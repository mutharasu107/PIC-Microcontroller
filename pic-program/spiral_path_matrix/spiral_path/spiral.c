
#include<htc.h>	
#define _XTAL_FREQ 2000000
__CONFIG(0x1F7A);

int main()
{
	TRISB = 0X00;
	TRISD = 0X00;
	while(1)
	{
		// 1 line
		for(int i=0; i<1; i++)
		{
			PORTB = 0x01<<i;
			for(int j=0; j<4; j++)
			{
				PORTD = 0X01<<j | PORTD;
				__delay_ms(200);
			}
		}
		// 2 line
/*		for(int i=7; i<8; i++)
		{
			PORTD = 0x01<<i;
			for(int j=0; j<8; j++)
			{
				PORTB = 0x01<<j;
//				__delay_ms(100);
			}
		}
		// 3 line
		for(int i=7; i<8; i++)
		{
			PORTB = 0x01<<i;
			for(int j=7; j>=0; j--)
			{
				PORTD = 0x01<<j;
//				__delay_ms(100);
			}
		}
		// 4 line
		for(int i=0; i<1; i++)
		{
			PORTD = 0x01<<i;
			for(int j=6; j>=1; j--)
			{
				PORTB = 0x01<<j;
//				__delay_ms(100);
			}
		}
//		__delay_ms(3000);
		
		// 5 line
		for(int i=1; i<2; i++, i++)
		{
			PORTB = 0x01<<i;
			for(int j=1; j<7; j++)
			{
				PORTD = 0x01<<j;
//				__delay_ms(100);
			}
		}
		// 6 line
		for(int i=6; i<7; i++)
		{
			PORTD = 0x01<<i;
			for(int j=1; j<7; j++)
			{
				PORTB = 0x01<<j;
//				__delay_ms(100);
			}
		}
		// 7 line
		for(int i=6; i<7; i++)
		{
			PORTB = 0x01<<i;
			for(int j=6; j>=1; j--)
			{
				PORTD = 0x01<<j;
//				__delay_ms(100);
			}
		}
		// 8 line
		for(int i=1; i<2; i++)
		{
			PORTD = 0x01<<i;
			for(int j=5; j>=2; j--)
			{
				PORTB = 0x01<<j;
//				__delay_ms(100);
			}
		}
//		__delay_ms(3000);
		
		// 9 line
		for(int i=2; i<3; i++)
		{
			PORTB = 0x01<<i;
			for(int j=2; j<6; j++)
			{
				PORTD = 0x01<<j;
//				__delay_ms(100);
			}
		}
		// 10 line
		for(int i=5; i<6; i++)
		{
			PORTD = 0x01<<i;
			for(int j=2; j<6; j++)
			{
				PORTB = 0x01<<j;
//				__delay_ms(1);
			}
		}
		// 11 line
		for(int i=5; i<6; i++)
		{
			PORTB = 0x01<<i;
			for(int j=5; j>=2; j--)
			{
				PORTD = 0x01<<j;
//				__delay_ms(100);
			}
		}
		// 12 line
		for(int i=2; i<3; i++)
		{
			PORTD = 0x01<<i;
			for(int j=4; j>=3; j--)
			{
				PORTB = 0x01<<j;
//				__delay_ms(100);
			}
		}
//		__delay_ms(3000);
		
		// 13 line
		for(int i=3; i<4; i++)
		{
			PORTB = 0x01<<i;
			for(int j=3; j<5; j++)
			{
				PORTD = 0x01<<j;
//				__delay_ms(100);
			}
		}
		// 14 line
		for(int i=4; i<5; i++)
		{
			PORTD = 0x01<<i;
			for(int j=3; j<5; j++)
			{
				PORTB = 0x01<<j;
//				__delay_ms(100);
			}
		}
		// 15 line
		for(int i=4; i<5; i++)
		{
			PORTB = 0x01<<i;
			for(int j=4; j>=3; j--)
			{
				PORTD = 0x01<<j;
//				__delay_ms(100);
			}
		}
		__delay_ms(5000);*/
	}
	while(1);
}
