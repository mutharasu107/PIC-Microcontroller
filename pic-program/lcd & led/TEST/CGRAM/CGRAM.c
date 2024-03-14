//character generator RAM.(CGRAM)

#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0X1F74);

#define RS RC0
#define RW RC1
#define EN RC2

void lcd_val(unsigned char val)
{
	RS = 0;
	RW = 0; 
	EN = 1;
	PORTB = val;
	__delay_ms(50);
	EN = 0;
	__delay_ms(20);
}

void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	PORTB = data;
	EN = 1;
	__delay_ms(50);
	EN = 0;
	__delay_ms(20);
}

int main()

{
	int a = 0;
	TRISB = 0;
	TRISC = 0;
	
	unsigned char pattern[64] ={0x0f,0x10,0x10,0x1e,0x01,0x01,0x1e,0x00,
	                             0x0f,0x10,0x10,0x10,0x10,0x10,0x0f,0x00,
	                             0x11,0x11,0x11,0x1f,0x11,0x11,0x11,0x00,
	                             0x0e,0x11,0x11,0x11,0x11,0x11,0x0e,0x00,
	                             0x0e,0x11,0x11,0x11,0x11,0x11,0x0e,0x00,
	                             0x10,0x10,0x10,0x10,0x10,0x10,0x1f,0x00,
	                             0x0e,0x11,0x11,0x11,0x11,0x11,0x1e,0x00,
	                             0x1f,0x10,0x10,0x1f,0x10,0x10,0x10,0x00};
	                              
    unsigned char arr[40]      ={0x10,0x10,0x10,0x10,0x10,0x10,0x1f,0x00,
	                             0x1f,0x04,0x04,0x04,0x04,0x04,0x1f,0x00,
	                             0x11,0x11,0x19,0x05,0x11,0x11,0x11,0x00,
	                             0x11,0x11,0x11,0x11,0x11,0x11,0x0e,0x00,
	                             0x11,0x11,0x0a,0x04,0x0a,0x11,0x11,0x00};	
	
	lcd_val(0x38);//data length,cursor,N 2 line and 5x8 diots
	lcd_val(0x0f);//display on off control
	lcd_val(0x01);//clear display.
	lcd_val(0x02);//return home
	lcd_val(0x06);//cur++                    
    
    lcd_val(0x40);//set CGRDM 
	
	for(int i=0; i<64; i++)
	    lcd_data(pattern[i]);
 
     __delay_ms(10);
    lcd_val(0x80 + a++);
    __delay_ms(10);
    lcd_data(0 + a++);
        
    __delay_ms(10);
    lcd_val(0x81);
    __delay_ms(10);
    lcd_data(1);
    
    __delay_ms(10);
    lcd_val(0x82);
    __delay_ms(10);
    lcd_data(2);
    
    
    __delay_ms(10);
    lcd_val(0x83);
    __delay_ms(10);
    lcd_data(3);
    
    __delay_ms(10);
    lcd_val(0x84);
    __delay_ms(10);
    lcd_data(4);
    
    
    __delay_ms(10);
    lcd_val(0x85);
    __delay_ms(10);
    lcd_data(5);
    
    __delay_ms(10);
    lcd_val(0x86);
    __delay_ms(10);
    lcd_data(6);
    
    
    __delay_ms(10);
    lcd_val(0x87);
    __delay_ms(10);
    lcd_data(7);

     while(1);
}