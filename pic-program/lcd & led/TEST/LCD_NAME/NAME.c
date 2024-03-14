#include <htc.h>
#define _XTAL_FREQ 20000000
 __CONFIG(0X1F7A);

#define RS RC0
#define RW RC1
#define EN RC2

void lcd_cmd(unsigned char cmd)
{
	RS = 0; //register signal 
	RW = 0; //read or write
	EN = 1; //enable bit on
	PORTB = cmd;
	__delay_ms(25);
	EN = 0;//enable bit off
}

void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
	__delay_ms(25);
	EN = 0;
}

int main()
{
	char *str ="SHACHUDHANANDHAN";
	TRISC = 0;
	TRISB = 0;
	lcd_cmd(0x38); //function set,5x8 line,N line 2
	lcd_cmd(0x0f); //display on,rn_cur
	lcd_cmd(0x01); //clear display
      lcd_cmd(0x02); //return home
	lcd_cmd(0x00); //set DDRM
	lcd_cmd(0x80); //cur++
	 
	 lcd_cmd(0x80);//set cursor first line
	
	for(int i=0; i<16; i++)
	  lcd_data(*(str++));
       __delay_ms(200);
       while(1);
   
       lcd_cmd(0xC0); //set cursor second line
   
   	 for(int i=0; i<16; i++)
	    lcd_data(*(ptr++));
	 while(1);
}