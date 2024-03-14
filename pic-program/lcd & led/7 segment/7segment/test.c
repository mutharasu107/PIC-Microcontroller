#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

int main()
{
	TRISC = 0X00;
	while(1){
	PORTC = 0XB7;
	__delay_ms(1000);
	
	PORTC = 0X06;
	__delay_ms(1000);
	
	PORTC = 0X73;
	__delay_ms(1000);
	
	PORTC = 0X57;
	__delay_ms(1000);
	
	PORTC = 0XC6;
	__delay_ms(1000);
	
	PORTC = 0XD5;
	__delay_ms(1000);
	
	PORTC = 0XF4;
	__delay_ms(1000);
	
	PORTC = 0X07;
	__delay_ms(1000);
	
	PORTC = 0XF7;
	__delay_ms(1000);
	
	PORTC = 0XC7;
	__delay_ms(1000);
	}	
	while(1);
}