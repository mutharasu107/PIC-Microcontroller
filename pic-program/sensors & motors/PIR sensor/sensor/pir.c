

//ULTRASONIC SENSOR USING DISTANCE CALCULATING.

#include <htc.h>

#define _XTAL_FREQ 20000000

__CONFIG(0x1f7a);

#define RS RC0
#define RW RC1
#define EN RC2

#define PIR RD0

void Lcd_Cmd(unsigned char Cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = Cmd;
	EN = 0;
}

void lcd_print(unsigned char data )
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
	EN = 0;
}

void Lcd_Init()
{
	TRISB = 0X00;
	Lcd_Cmd(0X38);
	Lcd_Cmd(0X01);
	Lcd_Cmd(0X0F);
	Lcd_Cmd(0X0C);
	Lcd_Cmd(0X02);
	Lcd_Cmd(0X06);
	Lcd_Cmd(0X80);
}

void Lcd_Write(unsigned char *s)
{
	while(*s)
	{
		lcd_print(*s++);
	}
}

int main()
{ 
  TRISC = 0X00;
  TRISD0 = 1;         //RD0 as OUT PUT PIN (PIR);          
  TRISA0 = 0;

  Lcd_Init();
  Lcd_Cmd(0x80);
  while(1)
  {                  
    if(RD0==1)        
    {
	    RA0=1;
        Lcd_Cmd(0x80);
        Lcd_Write("motion detected");
        __delay_ms(1000);
    }  
    else
    {
      Lcd_Cmd(0x01);
      Lcd_Cmd(0x80);
      Lcd_Write("motion not detected");
    }
    __delay_ms(400);
  }
}