#include <htc.h>
#define _XTAL_FREQ 20000000 
__CONFIG(0x1F7A);

#define RS RC0
#define RW RC1
#define EN RC2

#define PIR RB0
#define Buzzer RA0

void lcd_cmd(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTD = cmd;
	__delay_ms(10);
	EN = 0;
}

void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTD = data;
	__delay_ms(10);
	EN = 0;
}

void lcd_init()
{
	lcd_cmd(0x01);
	lcd_cmd(0x38);
	lcd_cmd(0x0f);
	lcd_cmd(0x0c);
	lcd_cmd(0x02);
	lcd_cmd(0x06);
	lcd_cmd(0x80);
}


void lcd_print(unsigned char *s)
{
	while(*s)
	{
		lcd_data(*s++);
	}
}

int main() 
{
    TRISA0 = 0;
    TRISC0  = 0;
    TRISC1  = 0;
    TRISC2  = 0;
    TRISB0 = 1;
    TRISD = 0;
    lcd_init();
    lcd_cmd(0x80);
    lcd_print("WELCOME");
    while(1)
    {
	    if(PIR ==1)
		{
			RA0=1;
			lcd_cmd(0xC0);
			lcd_print("motion detectd");
            __delay_ms(1000);
            lcd_cmd(0x01);
               
        }
        else
	    {
		    RA0=0;
		    lcd_cmd(0xC0);
		    lcd_print("motion not detectd");
		    __delay_ms(1000);
		    lcd_cmd(0x01);
        }
    }
}

