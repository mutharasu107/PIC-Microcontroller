
//stepper motor works.

#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

char motor_steps[]={0x07,0x03,0x0b,0x09,0x0d,0x0c,0x0e,0x06};
int main()
{
	int i=0,j=0;
    TRISB = 0X00;
    TRISA = 0X00;
	while(1){
	for(i=0; i<13; i++)
	{
		RA0 = 1;
		for(j=0;j<8;j++)
		{
		    PORTB = motor_steps[j];
		    __delay_ms(20);
		}
			
	}
	__delay_ms(1000);
	
	for(i=0; i<13; i++)
	{
		RA0 = 1;
		for(j=7;j>=0;j--)
		{
		    PORTB = motor_steps[j];
		    __delay_ms(5);
		}
			
	}
	
	__delay_ms(1000);
	
	for(i=0; i<50; i++)
	{
		RA0 = 1;
		for(j=0;j<8;j++)
		{
		    PORTB = motor_steps[j];
		    __delay_ms(5);
		}
			
	}
	__delay_ms(1000);
	
	for(i=0; i<25; i++)
	{
		RA1 = 1;
		for(j=0;j<8;j++)
		{
		    PORTB = motor_steps[j];
		    __delay_ms(5);
		}
			
	}
	__delay_ms(1000);
	
		
	for(i=0; i<25; i++)
	{
		RA1 = 1;
		for(j=8;j>=0;j--)
		{
		    PORTB = motor_steps[j];
		    __delay_ms(5);
		}
			
	}
	__delay_ms(1000);
	
		
	for(i=0; i<50; i++)
	{
		RA1 = 1;
		for(j=0;j<8;j++)
		{
		    PORTB = motor_steps[j];
		    __delay_ms(5);
		}
			
	}
	
	__delay_ms(1000);
	
	for(i=0; i<37; i++)
	{
		RA2 = 1;
		for(j=0;j<8;j++)
		{
		    PORTB = motor_steps[j];
		    __delay_ms(5);
		}
			
	}
	__delay_ms(1000);
	
	for(i=0; i<37; i++)
	{
		RA2 = 1;
		for(j=7;j>=0;j--)
		{
		    PORTB = motor_steps[j];
		    __delay_ms(5);
		}
			
	}
	
	__delay_ms(1000);
	
	for(i=0; i<50; i++)
	{
		RA2 = 1;
		for(j=0;j<8;j++)
		{
		    PORTB = motor_steps[j];
		    __delay_ms(5);
		}
			
	}
	__delay_ms(1000);
	
	for(i=0; i<50; i++)
	{
		RA3 = 1;
		for(j=7;j>=0;j--)
		{
		    PORTB = motor_steps[j];
		    __delay_ms(5);
		}
			
	}
	
	__delay_ms(1000);
	
		
	for(i=0; i<50; i++)
	{
		RA3 = 1;
		for(j=0;j<8;j++)
		{
		    PORTB = motor_steps[j];
		    __delay_ms(5);
		}
			
	}
	__delay_ms(1000);
	PORTB = 0XFF;
	__delay_ms(1000);
	}
	while(1);
}