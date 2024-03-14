

//ULTRASONIC SENSOR USING DISTANCE CALCULATING.

#include <htc.h>

#define _XTAL_FREQ 20000000

__CONFIG(0x1f7a);

#define RS RC0
#define RW RC1
#define EN RC2

void Lcd_Cmd(unsigned char Cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTD = Cmd;
	__delay_ms(10);
	EN = 0;
}

void lcd_print(unsigned char data )
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTD = data;
	__delay_ms(10);
	EN = 0;
}

void Lcd_Init()
{
	TRISD = 0X00;
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
  int a,b,c,d,f,g,h,i=1;
  TRISC = 0X00;
  TRISB = 0b00010000;         //RB4 as Input PIN (ECHO)
  TRISD = 0x00;               // LCD Pins as Output
  TRISA0 = 0;

  Lcd_Init();
  
  T1CON = 0x10;               //Initialize Timer Module

  while(1)
  { 
    TMR1H = 0;                //Sets the Initial Value of Timer
    TMR1L = 0;                //Sets the Initial Value of Timer

    RB0 = 1;                  //TRIGGER HIGH
    __delay_us(10);           //10uS Delay 
    RB0 = 0;                  //TRIGGER LOW

    while(!RB4);              //Waiting for Echo
    TMR1ON = 1;               //Timer Starts
    while(RB4);               //Waiting for Echo goes LOW
    TMR1ON = 0;               //Timer Stops

    a = (TMR1L | (TMR1H<<8)); //Reads Timer Value
    b = a/156.71;              //Converts Time to Distance
    c = b +1;                //Distance Calibration
    if(c>=0 && c<=30)        //Check whether the result is valid or not
    { 
      Lcd_Cmd(0x80);
      Lcd_Write("Distance = ");
     
      Lcd_Cmd(0x8D);
      lcd_print(c%10 + 48);
      RA0 = 1;

      Lcd_Cmd(0x8C);
      d = c/10;
      lcd_print(d%10 + 48);
      RA0 = d;
      
      Lcd_Cmd(0x8B);
      f = d/10;
      lcd_print(f%10 + 48);	
      RA0 = f; 

      Lcd_Cmd(0x8E);
      Lcd_Write("cm");
 
    }  
    else
    {
      Lcd_Cmd(0x01);
      Lcd_Cmd(0x80);
      Lcd_Write("Out of Range");
    }
    __delay_ms(400);
  }
}