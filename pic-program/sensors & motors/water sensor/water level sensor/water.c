#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0X1F7A);

#define WATER RA4

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
	__delay_ms(50);
}

void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
	__delay_ms(50);
	EN = 0;
	__delay_ms(50);
}

void lcd_init()
{
	TRISB = 0;  //PORT-B used out put bit
	TRISC = 0;    //PORT-C pin #0 out put pin	
	__delay_ms(50);
	lcd_cmd(0x38); //init 5x8,2 line ret home
	lcd_cmd(0x0f); //disp on,on-cur,en-blink
	lcd_cmd(0x0c); //disp on,en-cur,en-blink
	lcd_cmd(0x02); //ret home
	lcd_cmd(0x06); //cur++
	lcd_cmd(0x80); //set DDRAM
	__delay_ms(50);
	lcd_cmd(0x01); //clear display
}

void lcd_print(unsigned char *s)
{
	while(*s)
	{
		lcd_data(*s++);
		__delay_ms(10);
	}
}

int main()
{
	TRISA4 = 1;
	lcd_init();
 
	while(1)
	{
		if(WATER > 0 && WATER <= 150)
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_print("WATER LOW");
			__delay_ms(1000);
		}
		else if(WATER > 150 && WATER <= 400)
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_print("WATER MEDIUM");
			__delay_ms(1000);
		}
		else if(WATER > 400 && WATER <= 520)
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_print("WATER HIGH");
			__delay_ms(1000);
		}
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_print("SCHOOL OF LINUX");
		lcd_cmd(0xc0);
		lcd_print("   DHARMAPURI ");
		__delay_ms(3000);
	}
}