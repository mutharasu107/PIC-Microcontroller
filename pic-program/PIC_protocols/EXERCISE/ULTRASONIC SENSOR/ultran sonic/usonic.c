// LCD module connections
#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0X1F7A);

#define RS RC0
#define RW RC1
#define EN RC2

void Lcd_Cmd(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTD = cmd;
//	__delay_ms(2);
	EN = 0;
}
void Lcd_Out(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTD = data;
//	__delay_ms(2);
	EN = 0;
}
void Lcd_Data(unsigned int val)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTD = val;
//	 __delay_ms(2);
    EN = 0;
}
void Lcd_Init()
{
	TRISC = 0X00;
//	TRISD = 0X00;
	Lcd_Cmd(0x38);
	Lcd_Cmd(0x0f);
	Lcd_Cmd(0x0c);
	Lcd_Cmd(0x02);
	Lcd_Cmd(0x06);
	Lcd_Cmd(0x80);
}
/* variables to store pulse duration and to display string on LCD 8 */
int time_taken;
char txt[7];
/* Main code to take distance measurement and initializations */
void main() 
{
//  PORTB=0X00;
  TRISB=0X00;
  TRISD=0x00;  /* initialize PORTD as digital ouput pin for LCD */
  Lcd_Init();   /* initialize LCD library functions */
  Lcd_Cmd(0x01); /* Clear whatever is written on LCD */
  
  /* display "HC-SR04" on LCD */
  Lcd_Out("HC-SR04");
  
//  __delay_ms(2000); /* wait for one second */
  Lcd_Cmd(0x01);  /* Clear text from LCD */
  
  T1CON = 0x10; /* Set timer1 prescaler value to 1:2 prscale and disable timer1 */
  
  while(1)
  {
     /* Initialize Timer1 register to zero */
     TMR1H = 0;
     TMR1L = 0;
     
     /* send 10us puls to triger pin of HC-SR04 from RB0 pin */
     TRISB0= 1;
//     __delay_us(10);
     TRISB0= 0;
     
     while(TRISB4== 1);   /* wait till echo output signal goes high */
     T1CON= 1;    /* enable the Timer1 */
//     while(TRISB4== 0);  /* wait till echo output signal goes low */
     T1CON= 0; /*disable timer1 */

     time_taken= (TMR1L | (TMR1H<<8)); /*read the content of Timer1 registers */
     time_taken= (TMR1L | (TMR1H<<8))/58.82; /* convert duration into distance */
     
     /* This code block displays the measured distance value on LCD */
     if(time_taken>=0 && time_taken<=400)
     {
       Lcd_Data(time_taken);
       Lcd_Data(txt);
       Lcd_Cmd(0X01);
       Lcd_Out("Distance = ");
       Lcd_Data(txt);
       Lcd_Out("cm");
     }
    else
     {
       Lcd_Cmd(0X01);
       Lcd_Out("Out of Range");
     }
//     __delay_ms(500);
  }
}