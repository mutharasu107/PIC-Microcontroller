#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

#define RS RC0
#define RW RC1
#define EN RC2

void lcd_read(unsigned char read)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = read;
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

int main()
{
	TRISD0 = 1;
	TRISB0 = 0;
	TRISB = 0;
	TRISC = 0;
	RB0 = 0;
	int a = 1;
	int i = 1;
	
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
			__delay_ms(50);
			if(RD0==0)
			{
				RB0=1;
	            for(int i=0; i<10; i++)
	            {
		            lcd_write(i+0x30);
		            lcd_read(0x80);
		            for(int i=0; i<10; i++)
		            {
			            lcd_write(i+0x31);
		                lcd_read(0x81);
		            }
		            lcd_write(0x30+a);
		            lcd_read(0x80);
		        }
		        lcd_write(0x30+a);
		        lcd_read(0x80);
		     }
		 }
     }
}
		             
/*		        }
		        for(int i=0; i<10; i++)
		        {
			        lcd_write(i+0x30);
			        lcd_read(0x83);
			        for(int i=0; i<10; i++)
			        {
				        lcd_write(i+0x30);
				        lcd_read(0x84);
				    }
				}
				for(int i=0; i<10; i++)
				{
					lcd_write(i+0x30);
					lcd_read(0x86);
					for(int i=0; i<10; i++)
					{
						lcd_write(i+0x30);
						lcd_read(0x87);
				    }
				}
		        __delay_ms(50);
            }
        }
 //       lcd_read(1+0x30);
  //      lcd_write(0x80);
    }
}*/
    