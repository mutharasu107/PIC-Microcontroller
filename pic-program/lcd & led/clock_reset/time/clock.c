#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

#define RS RC0
#define RW RC1
#define EN RC2

int a,y,b=0x80;

void lcd_cmd(unsigned int cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = cmd;
	__delay_ms(50);
	EN = 0;
}
void lcd_data(unsigned int data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
	__delay_ms(50);
	EN = 0;
}

int main()
{
	TRISB = 0X00;
	TRISC = 0X00;
	TRISB0 = 0;
	TRISD0 = 1;
	RB0 = 0;
	
	int i,j,k,a,b,c;
	i,j,k,a,b,c = 0;
	lcd_cmd(0x38);//data length,number of line 2,5x8 line
	lcd_cmd(0x0c);//set display
	lcd_cmd(0x01);//clear display
	lcd_cmd(0x02);//return from home
	lcd_cmd(0x06);//cursor++
	lcd_cmd(0x80);//set DDRAM address
    
    lcd_cmd(0x86);
	while(1)
	{
		if(RD0 == 0)
		{
			__delay_ms(50);
			if(RD0 == 0)
			{
				RB0 = 1;
                for(a=0; a<6; a++)
                {
	                lcd_cmd(0x86);
	                lcd_data(a+0x30);
	                for(i=0; i<10; i++)
                    {
	                    lcd_cmd(0x87);
	                    lcd_data(i+0x30);
	                    __delay_ms(50);
	                }
	            }
	            for(c=0; c<6; c++)
                {
	                lcd_cmd(0x83);
	                lcd_data(c+0x30);
	                for(j=0; j<10; j++)
                    {
	                    lcd_cmd(0x84);
	                    lcd_data(j+0x30);
	                    __delay_ms(50);
	                }
	           }
	           for(b=0; b<2; b++)
               {
	               lcd_cmd(0x80);
	               lcd_data(b+0x30);
	               for(k=0; k<3; k++)
                   {
	                   lcd_cmd(0x81);
	                   lcd_data(k+0x30);
	                   __delay_ms(50);
	               }
	           }
	        }
	     }
	 }
//	 while(1);
}