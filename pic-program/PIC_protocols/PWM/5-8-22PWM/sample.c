#include <htc.h>
#include <pic16f877a.h>
#define _XTAL_FREAQ 20000000
__CONFIG(0x1F7A);

void delay();

void delay()
{
	T1CON = 0X30;     //timer1 precelar value 1:8
	TMR1H = 0X0B;     //timer1 high value
	TMR1L = 0XDC;     //timer1 low value
	TMR1ON=1;         //timer on
	while(TMR1IF==0); //wait for timer1 interrupt flage bit set
	TMR1IF = 0;       //timer off
}

int main()
{
	unsigned char i = 0;
	TRISC2 = 0;
	CCP1CON = 0X0F; //0B0000 1111selct the PWM mode.
	PR2 = 0XFF;//Period reg./set the cycle time in to 255 for varying the duty cycle from 0xff.
	CCPR1L = 0X10;//0b0001 0000 by default set the dutycycle to 10
	T2CON = 0X07;//0B0000 0111 tmr2on t2ckps1:t2ps0:timer2 clock prescale select bits
	delay();
	
	for(i=0;i<16;i++)
	{
		CCPR1L=CCPR1L+0X10;
	    delay();
	    delay();
	    delay();
	    delay();
	    delay();
	    delay();
	    delay();
	    delay();
	    delay();
	    delay();
	}
}