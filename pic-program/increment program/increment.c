#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

#define RS RC0
#define RW RC1
#define EN RC2
int a = 48;
int b = 0;

void lcd_read(unsigned char read)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = read;
	__delay_ms(100);
	EN = 0;
}

void lcd_write(unsigned char write)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = write;
	__delay_ms(100);
	EN = 0;
}

int main()
{
	TRISD0 = 1;
	TRISB0 = 0;
	TRISB = 0;
	TRISC = 0;
	RB0 = 0;
	
	lcd_read(0x38);
	lcd_read(0x0c);
	lcd_read(0x01);
	lcd_read(0x02);
	lcd_read(0x06);
	lcd_read(0x80);
	
	while(1)
	{
		if(RD0==0)
		{
			__delay_ms(100);
			if(RD0==0)
			{
				RB0=1;
	                        for(int i=0; i<10; i++)
	            		{
		            		lcd_write(i+0x30);
		            		lcd_read(0x80);
		            		lcd_read(0x81);
		        	}
                	__delay_ms(100);
            		}
            		while(1);
        	}
    	}
}
