#include <htc.h>
#define _XTAL_FREQ 20000000
//__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF & CPD_OFF & WRT_OFF & CP_OFF);
__CONFIG(0X7F1A);

int main()
{
	TRISB = 0X00;
	TRISC = 0X00;
	
	while(1)
	{
		PORTB = 0X00;
		PORTC = 0X00;
		
		for(int i=0, j=7; i<1, j<8; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
	
		for(int i=0, j=6; i<2, j<8; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
	
		for(int i=0, j=5; i<3, j<8; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
		
		for(int i=0, j=4; i<4, j<8; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
		
		for(int i=0, j=3; i<5, j<8; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
	
		for(int i=0, j=2; i<6, j<8; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
	
		for(int i=0, j=1; i<7, j<8; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
	
		for(int i=0, j=8; i<8, j<8; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
		
		for(int i=0, j=0; i<8, j<8; i++, j++)
		{
			PORTB = 0x01<<i;
			PORTC = 0X01<<j;
			__delay_ms(10);
		}
		
		for(int i=1, j=0; i<8, j<7; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
	
		for(int i=2, j=0; i<8, j<6; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}

		for(int i=3, j=0; i<8, j<5; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
		
		for(int i=4, j=0; i<8, j<4; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
	
		for(int i=5, j=0; i<8, j<3; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
		
			for(int i=6, j=0; i<8, j<2; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTC = 0x01<<j;
			__delay_ms(10);
		}
		
		for(int i=7, j=0; i<8, j<1; i++, j++)
		{
			PORTB = 0x01<<i; 
			PORTD = 0x01<<j;
			__delay_ms(10);
		}
	
	}
	while(1);
}