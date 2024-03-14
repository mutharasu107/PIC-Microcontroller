#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0x1F74);

#define RS RC0
#define RW RC1
#define EN RC2

void lcd_val(unsigned char val)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = val;
	__delay_ms(50);
	EN = 1;
	__delay_ms(100);
	EN = 0;
}
void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
	__delay_ms(50);
	EN = 1;
	__delay_ms(100);
	EN = 0;
}

int main()
{
	TRISB = 0;
	TRISC = 0;
	unsigned char *str ="        linux";
	
	lcd_val(0x38);//data length,line display,5x11
	lcd_val(0x0f);//set display,cursor,blinking on cursor
	lcd_val(0x18);//cursor or display shift
	lcd_val(0x01);//clear display
//	lcd_val(0x05);//entry mode
	lcd_val(0x02);//return to home
	lcd_val(0x06);//set DDRAM 
	lcd_val(0x80);//cur++
	
	lcd_val(0x00);
	
	for(int i=0; i<1500; i++)
	    lcd_data(*(str++));
	    
	__delay_ms(20);
	lcd_val(0x80);
	__delay_ms(100);
	 lcd_data(0);
	 
	 while(1);
}
