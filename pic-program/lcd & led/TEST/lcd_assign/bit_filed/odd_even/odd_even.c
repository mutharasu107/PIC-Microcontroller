#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0x1f74);

int main()
{
	TRISD = 0X00;
	int a = 8;
	int b = 1;
	while(a>=0)
	{
		PORTD = 0X01 << a;
		__delay_ms(200);
		a--;
		a--;
		
	}
	while(b<=8)
	{
		PORTD = 0X01 << b;
		__delay_ms(200);
		b++;
		b++;
	}
	while(1);
}