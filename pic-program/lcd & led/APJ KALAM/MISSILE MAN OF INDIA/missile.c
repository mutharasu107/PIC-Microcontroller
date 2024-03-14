

#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0X1F7A);

#define RS RC0
#define RW RC1
#define EN RC2

void lcd_cmd(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = cmd;
	__delay_ms(10);
	EN = 0;
}

void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
	__delay_ms(10);
	EN = 0;
}

void lcd_init()
{
	lcd_cmd(0x01);   //lcd clear.
	lcd_cmd(0x02);   //return home
	lcd_cmd(0x38);   //16x2 line,data length.
	lcd_cmd(0x0f);
	lcd_cmd(0x0c);
	lcd_cmd(0x06);
	lcd_cmd(0x80);
}

void lcd_print(unsigned char *s)
{
	while(*s)
	{
		lcd_data(*s++);
		__delay_ms(50);
	}
}

int main()
{
	int i,j,k,l;
	TRISC0 = 0;
	TRISC1 = 0;
	TRISC2 = 0;
	TRISB = 0;
	
	lcd_init();
	
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_print("Missile Man of");
	__delay_ms(500);
	lcd_cmd(0xC0);
	lcd_print("India  Dr.APJ");
	__delay_ms(1000);
	
	lcd_cmd(0x01);
	lcd_print(" End is not the ");
	__delay_ms(1000);
	lcd_cmd(0xC0);
	lcd_print("      end ,     ");
	__delay_ms(1500);
	
	lcd_cmd(0x01);
	lcd_print(" if fact E.N.D. ");
	__delay_ms(1000);
	lcd_cmd(0xC0);
	lcd_print("      means    ");
	__delay_ms(1500);
	
		lcd_cmd(0x01);
	lcd_print("  Effort Never   ");
	__delay_ms(1000);
	lcd_cmd(0xC0);
	lcd_print("  Dies Dr. APJ ");
	__delay_ms(1500);
	
	lcd_cmd(0x01);
	lcd_print("Remembering the");
	__delay_ms(500);
	lcd_cmd(0xC0);
	lcd_print("Missile Man");
	__delay_ms(2000);
	
	lcd_cmd(0x01);
	lcd_print("School of Linux");
	__delay_ms(1000);
	lcd_cmd(0xC0);
	lcd_print("   Dharmapuri  ");
	__delay_ms(2000);
	
	lcd_cmd(0x01);
	lcd_print(" Programmed by ");
	__delay_ms(1000);
	lcd_cmd(0xC0);
	lcd_print("  R.Mutharasu.  ");
	__delay_ms(1500);
	
	while(1);
}