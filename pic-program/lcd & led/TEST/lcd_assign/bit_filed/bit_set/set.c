#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1f74);


int main()
{
	TRISD = 0X00;
    int a = 0xFF,c;
    __delay_ms(200);
    PORTD = a & (0X01 << 3);
    
    while(1);   
}