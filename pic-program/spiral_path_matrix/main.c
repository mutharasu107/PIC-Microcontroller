#include <htc.h>
#define _XTAL_FREQ 20000000


#define TIMER1_HIGH 0x9E
#define TIMER1_LOW 0x00


void timer1_config(void);
void interrupt_config(void);
void port_config(void);
void enable_modules(void);
void interrupt Interrupt_ser_routine(void);
void init (void);

unsigned int INT_COUNTER = 0;

void main(void)
{

	init();
	
	while(1)
	{
		//do some work
	}
}

void init(void)
{
	timer1_config();
	port_config();
	interrupt_config();
	enable_modules();
}

void timer1_config(void)
{
	//OFF TIMER
	TMR1ON = 0;
	
	//clear timer flag
	TMR1IF = 0;
	
	//internal clock is selected as timer1 input clock
	TMR1CS = 0;
	
	//prescalar is selected for 1:1 ratio
	T1CKPS1 = 0;
	T1CKPS0 = 0;
	
	//donot sync with external clock
	T1SYNC = 1;
	
	
	//0 -> FFFFh
	//Input clock FOSC 20MHz ===> time taken for 1 cycle 50ns
	//FOSC/4 = 5MHz ===> time taken for 1 cycle 200ns
	
	TMR1H = TIMER1_HIGH;
	TMR1L = TIMER1_LOW;
}

void interrupt_config(void)
{
	//disable all interrupts and clear all interrupt flags
	INTCON = 0;
	PIE1 = 0;
	PIE2 = 0;
	PIR1 = 0;
	PIR2 = 0;
	
	//enable required interrupts
	
	//enable TIMER1 interrupt
	TMR1IE = 1;
	
	
	//Enable peripheral interrupt
	PEIE = 1;
	
	//Enable global interrupt
	GIE = 1;
}

void port_config(void)
{
	//PORTC configured as output
	TRISC = 0;
}

void enable_modules(void)
{
	//ON TIMER
	TMR1ON = 1;
}

void interrupt Interrupt_ser_routine(void)
{
	//Disable global interrupt
	GIE = 0;
	INT_COUNTER++;
	if(TMR1IF == 1){
		TMR1ON = 0;
		TMR1IF = 0;
			
		TMR1H = TIMER1_HIGH;
		TMR1L = TIMER1_LOW;
		
		//required logic while timer interrup happens
		PORTC = ~PORTC;
		TMR1ON = 1;
	}	

	//enable global interrupt
	GIE = 1;
}