#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0x1F74);

#define RS RC0
#define RW RC1
#define EN RC2

void lcd_cmd(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = cmd;
	__delay_ms(25);
	EN = 0;
	__delay_ms(20);
}

void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
	__delay_ms(25);
	EN = 1;
	__delay_ms(20);
    EN = 0;
}

int main()
{
	TRISB = 0;
	TRISC = 0;
	
	unsigned char arr[22] ={0x00,0x00,0x04,0x00,0x1f,0x00,0x04,0x00,0x00,0x00,0x00,
	                        0x1f,0x10,0x08,0x04,0x08,0x10,0x1f,0x00,0x00,0x00,0x00};

	lcd_cmd(0x3c);//set data length,n 2 line,5x11
	lcd_cmd(0x0f);//display on off
	lcd_cmd(0x01);//clear display
	lcd_cmd(0x02);//return home
	lcd_cmd(0x60);//cur++
	
    lcd_cmd(0x40);//set CGRAM
	for(int i=0; i<22; i++)
	   lcd_data(arr[i]);
	
	__delay_ms(10);	
	lcd_cmd(0x80);
	__delay_ms(20);
	lcd_data(0);
	
	__delay_ms(10);	
	lcd_cmd(0x81);
	__delay_ms(20);
	lcd_data(1);
	while(1);
}
