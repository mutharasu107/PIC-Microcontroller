#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0X1F7A);
int main()
{
	int i,j;
	TRISC=0;
	TRISB=0;

	PORTC=0Xff;
	PORTB=0X01;
	__delay_ms(200);
	
	PORTC=0Xff;	
	PORTB=0X02;
	__delay_ms(200);
	
	PORTC=0Xff;
	PORTB=0X04;
	__delay_ms(200);
	
	PORTC=0Xff;
	PORTB=0X08;	
	__delay_ms(200);
	
	PORTC=0Xff;
	PORTB=0X10;	
	__delay_ms(200);
	
	PORTC=0Xff;
	PORTB=0X20;	
	__delay_ms(200);
	
	PORTC=0Xff;
	PORTB=0X40;	
	__delay_ms(200);
	
	PORTC=0Xff;
	PORTB=0X80;	
	__delay_ms(200); 
}