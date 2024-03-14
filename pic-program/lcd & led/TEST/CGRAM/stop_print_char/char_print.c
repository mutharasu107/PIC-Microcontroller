#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0x1f74);

#define RS RC0
#define RW RC1
#define EN RC2

void lcd_cmd(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = cmd;
	__delay_ms(100);
	EN = 0;
}

void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
	__delay_ms(100);
	EN = 0;
}

int main()
{
	TRISB = 0;
	TRISC = 0;
	TRISD0 = 1;
	TRISB0 = 0;
	RB0 = 0;
	
	unsigned char *ptr ={"MUTHU"};
	lcd_cmd(0x38);
	lcd_cmd(0x0f);
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x06);
	lcd_cmd(0x80);
	
	while(1)
	{
		if(RD0 == 0)
	    {
		    __delay_ms(100);
		    if(RD0 == 0)
		    {
			    RB0 = 1;
			    lcd_data(*(ptr++));
			    __delay_ms(100);
		    	RD0 = 0;
		    }
		}
	}
	while(1);
}