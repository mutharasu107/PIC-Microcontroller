#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1f7a);
unsigned int arr[8]  = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
unsigned int arr1[8] = {0X80, 0XC0, 0XE0, 0XF0, 0XF8, 0XFC, 0XFE, 0XFF};
unsigned int arr2[6] = {0x02, 0x06, 0x0E, 0x1E, 0x3E, 0x7E};
unsigned int arr3[6] = {0X40, 0X60, 0X70, 0X78, 0X7C, 0X7E};
unsigned int arr4[4] = {0x04, 0x0C, 0x1C, 0x3C};
unsigned int arr5[3] = {0x08, 0x18, 0x28};
unsigned int arr6[3] = {0X10, 0X18, 0X1C};

unsigned int timer_1(void);

int main()
{
	timer_1();
	TRISB = 0X00;
	TRISD = 0X00;
	while(1)
	{
		PORTD = 0X01<<0;		// line1
		for(int j=0; j<8; j++)
		{
			PORTB = arr[j];
			timer_1();
		}
		PORTB = 0X01<<7;		// line2
		for(int j=0; j<8; j++)
		{
			PORTD = arr[j];
			timer_1();
		}
		PORTD = 0X01<<7;		//line3
		for(int j=0; j<8; j++)
		{
			PORTB = arr1[j];
			timer_1();
		}
		PORTB = 0X01<<0;		//line4
		for(int j=0; j<7; j++)
		{
			PORTD = arr1[j];
			timer_1();
		}
		PORTD = 0X01<<1;		// line5
		for(int j=1; j<7; j++)
		{
			PORTB = arr[j];
			timer_1();
		}
		PORTB = 0X01<<6;		// line6
		for(int j=3; j<6; j++)
		{
			PORTD = arr2[j];
			timer_1();
		}
		PORTD = 0X01<<6;		//line7
		for(int j=2; j<7; j++)
		{
			PORTB = arr3[j];
			timer_1();
		}
		PORTB = 0X01<<1;		//line8
		for(int j=0; j<5; j++)
		{
			PORTD = arr3[j];
			timer_1();
		}
		PORTD = 0X01<<2;		// line9
		for(int j=0; j<4; j++)
		{
			PORTB = arr4[j];
			timer_1();
		}
		PORTB = 0X01<<5;		// line10
		for(int j=0; j<3; j++)
		{
			PORTD = arr5[j];
			timer_1();
		}
		PORTD = 0X01<<5;		// line11
		for(int j=0; j<3; j++)
		{
			PORTB = arr6[j];
			timer_1();
		}
		PORTB = 0X01<<2;		//line12
		for(int j=0; j<2; j++)
		{
			PORTD = arr6[j];
			timer_1();
		}
		PORTD = 0X01<<3;		// line13
		for(int j=0; j<2; j++)
		{
			PORTB = arr5[j];
			timer_1();
		}
		PORTD = 0X01<<4;		// line14
		PORTB = 0x10;
		timer_1();

		PORTD = 0x01<<4;		// line14
		PORTB = 0x08;
		timer_1();
	}
	while(1);
}

//delay 16ms timer calculation
unsigned int timer_1(void)
{
	T1CON = 0X30;     //timer1 precelar value 1:8
	TMR1H = 0X27;     //timer1 high value
	TMR1L = 0X10;     //timer1 low value
	TMR1ON=1;         //timer on
	while(TMR1IF==0); //wait for timer1 interrupt flage bit set
	TMR1IF = 0;       //timer off
}