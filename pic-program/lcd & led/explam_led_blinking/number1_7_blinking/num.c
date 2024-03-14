#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

int main()
{
	TRISB = 0x00;
	while(1)
	{
		PORTB = 0XFF;
        
        __delay_ms(300);

		
		PORTB = 0X00;
		__delay_ms(300);
		
	}
	while(1);
}