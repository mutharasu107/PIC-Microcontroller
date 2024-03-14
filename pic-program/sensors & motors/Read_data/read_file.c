#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0x1f7A);

#define RS RC0
#define RW RC1
#define EN RC2

void lcd_cmd(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = cmd;
	__delay_ms(50);
	EN = 0;
}

void lcd_write(unsigned char write)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = write;
	__delay_ms(50);
	EN = 0;
}

void lcd_read(unsigned char read)
{
	RS = 0;
	RW = 1;
	EN = 1;
	PORTB= read;
	__delay_ms(50);
	EN = 0;
}
int main()
{
	TRISB = 0;
	TRISC = 0;
	
	unsigned char *ptr[]={"SCHOOL OF LINUX"};
	unsigned char *str;
	
	lcd_read(0x38);//data length,line 2,5x8 display font types
	lcd_read(0x0F);//display,set cursor,cursor blinking
	lcd_read(0x01);//clear diplay
	lcd_read(0x02);//return home
	lcd_read(0x06);//cursor moving direction
	lcd_read(0x80);//set DDRAM address
	
//	lcd_cmd(0x80);
	
	for(int i=0; i<15; i++)
	{
        lcd_cmd(0x80+i);
	    lcd_read(*(ptr[i]));
	}
//.	for(int a=0; a<15; a++)
//	{
//	    lcd_write(0xc0+a);
//	}
	    
	while(1);
}