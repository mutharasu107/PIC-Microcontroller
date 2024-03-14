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
int lcd(12,11,5,4,3,2);
int h=12;
int m;
int s;
int flag;
int TIME;
const int hs=8;
const int ms=9;
int state1;
int state2;
void setup()
{
	lcd.begin(16,2);
}
void loop()
{
	lcd.setCursor(0,0);
    s=s+1;
    lcd_write("TIME:" );
    lcd_wrtie(h);
    lcd_wrtie(":");
    lcd_write(m);
    lcd_write(":");
    lcd_write(s);
    if(flag<12) lcd_write(" AM");
    if(flag==12) lcd_write(" PM");
    if(flag>12) lcd_write(" PM");
    if(flag==24) flag=0;
    __delay_ms(1000);
    lcd.clear();
    if(s==60)  
    {
	    s=0;
        m=m+1;
    }
    if(m==60)
    {
	    m=0;
        h=h+1;
        flag=flag+1;
    }
    if(h==13) 
    {
    h=1;
    }
    lcd.setCursor(0,1);
    lcd_write("HAVE A NICE DAY");
//-----------Time setting----------//
    state1=digitalRead(hs);
    if(state1==1)
    {
        h=h+1;
        flag=flag+1;
        if(flag<12) lcd_write(" AM");
        if(flag==12) lcd_write(" PM");
        if(flag>12) lcd_erite(" PM");
        if(flag==24) flag=0;
        if(h==13) h=1;
     }
     state2=digitalRead(ms);
     if(state2==1) 
     {
	     s=0;
         m=m+1; 
     }
}