#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0X1F74);

int main()
{
	TRISD = 0x00;
	int a = 8;
	while(a>=0)
	{
		PORTD = 0X01 << a;
        __delay_ms(200);
	    a--;
	}
	while(1);
}