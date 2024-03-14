#include <htc.h>
#define _XTAL_FREQ 20000000
 __CONFIG(0X1F7A);
 
int main()
{
	TRISB = 0x00;
	TRISD = 0x00;
	while(1)
	{
		PORTB = 0x2E;
		PORTD = 0x02;
//		__delay_ms(50);
		
		PORTB = 0X02;
		PORTD = 0X04;
//		__delay_ms(50); 
		
		PORTB = 0X0E;
		PORTD = 0X08;
//		__delay_ms(50);
		
		PORTB = 0X08;
		PORTD = 0X10;  
//		__delay_ms(50);
		
		PORTB = 0X0E;
		PORTD = 0X20;
//		__delay_ms(50);
	}
}