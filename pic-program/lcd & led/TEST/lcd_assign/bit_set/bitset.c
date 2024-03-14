#include <htc.h>
#define _XTAL_FREQ 20000000
 __CONFIG(0X1F7A);

#define RS RC0
#define RW RC1
#define EN RC2

void lcd_cmd(int cmd)
{
	RS = 0; //register signal 
	RW = 0; //read or write
	EN = 1; //enable bit on
	PORTB = cmd;
	__delay_ms(100);
	EN = 1;//enable bit off
	__delay_ms(20);
	EN = 0;
}

void lcd_data(int data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
	__delay_ms(100);
	EN = 1;
	__delay_ms(20);
	EN = 0;
}

int main()
{
	TRISC = 0;
	TRISB = 0;
     
    int a =255,b;
	
	lcd_cmd(0x38); //function set,5x8 line,N line 2
	lcd_cmd(0x0f); //display on,rn_cur
	lcd_cmd(0x01); //clear display
    lcd_cmd(0x02); //return home
	lcd_cmd(0x00); //set DDRM
	
	lcd_cmd(0x00);//set cursor first line
	
    b = a &(0x01<<6);
 
	    lcd_data (b);
	  
   __delay_ms(20);
    while(1);
   
}