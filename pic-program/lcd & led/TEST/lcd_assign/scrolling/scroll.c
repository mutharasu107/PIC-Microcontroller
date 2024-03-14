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
	 EN = 0;
}

void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
	__delay_ms(50);
	
	EN	= 0;
}

int main()
{
	TRISB = 0;
	TRISC = 0;
	
	unsigned char *ptr =" school of linux ";
	lcd_val(0x38);
	lcd_val(0x0f);
	lcd_val(0x1c);
	lcd_val(0x01);
	lcd_val(0x02);
	lcd_val(0x06);
	lcd_val(0x80);
	
	lcd_val(0x00);
	
	for(int i=0; i<16 ; i++)
	  lcd_data(*(ptr++));
	  
	  
    __delay_ms(10);
    lcd_val(0x80);
    
    lcd_val(0x11);
	  
    __delay_ms(10);
    lcd_data(0); 
         
    while(1);
}