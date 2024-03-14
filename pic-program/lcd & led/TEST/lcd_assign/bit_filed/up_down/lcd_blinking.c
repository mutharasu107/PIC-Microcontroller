#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0X1F74);

int main()
{
	TRISD = 0X00;
	int a = 8;
	int b = 0;
	while(a>=0)
	{
		PORTD = 0X01 << a;
		__delay_ms(200);
		a--;
	}
	
	while(b<=8)
	{
		 PORTD = 0X01 << b;
		 __delay_ms(500);
		 b++;
	 } 	
	 while(1);
}