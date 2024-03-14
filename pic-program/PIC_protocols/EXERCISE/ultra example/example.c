#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0X1F7A);

#define RS RD1
#define RW RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

void uart_tx(unsigned char val)
{
	TXREG = val;
	while(TXIF == 0);
	TXIF =0;
}

unsigned char uart_rx(void)
{
	while(RCIF==0);
	RCIF=0;
	return RCREG;
}

void uart_tmp(unsigned char *s)
{
	while(*s)
	{
		uart_tx(*s++);
	}
}

void lcd_cmd(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTD = cmd;
	EN = 0;
}
void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTD = data;
	EN = 0;
}

void lcd_init()
{
	TRISD = 0X00;
	lcd_cmd(0x38);
	lcd_cmd(0x0f);
	lcd_cmd(0x0c);
	lcd_cmd(0x02);
	lcd_cmd(0x06);
	lcd_cmd(0x08);
	lcd_cmd(0x01);
}

void main()
{ 
  int a;

  TRISB = 0b00010000;         //RB4 as Input PIN (ECHO)
  TRISD = 0x00;               // LCD Pins as Output

  lcd_init();

  __delay_ms(200);
  lcd_cmd(0x01);

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
    a = a/58.82;              //Converts Time to Distance
    a = a + 1;                //Distance Calibration
    if(a>=2 && a<=400)        //Check whether the result is valid or not
    { 
      lcd_cmd(0x01);
      lcd_cmd(0x80);
      uart_tmp("Distance = ");

      lcd_cmd(0x8D);
      lcd_data(a%10 + 48);

      a = a/10;
      lcd_cmd(0x8C);
      lcd_data(a%10 + 48);

      a = a/10;
      lcd_cmd(0x8B);
      lcd_data(a%10 + 48);

      lcd_cmd(0x8E);
      uart_tmp("cm");
    }  
    else
    {
      lcd_cmd(0x01);
      lcd_cmd(0x80);
      uart_tmp("Out of Range");
    }
    __delay_ms(400);
  }
}