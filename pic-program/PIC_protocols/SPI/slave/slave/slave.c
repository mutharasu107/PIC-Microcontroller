
#include<htc.h>
#include<stdio.h>
#define XTAL_FREQ 20000000
#define SS RC1
__CONFIG(0x2FCF);

void delay();
void spi_init(void);
unsigned char spi_transfer(unsigned char data);
void print_uart(unsigned char *str);
void uart_tx(unsigned char val);
unsigned char uart_rc(void);
void uart_init(void);
unsigned char m_str[]	= "PIC initialized\n";
unsigned char p_msg[]   = "Initializing device\n";

int main()
{
	unsigned char i,j, recv,var='M';
	char arr[30];
	uart_init();
	delay();
	print_uart(m_str);
	print_uart(p_msg);
	spi_init();
	delay();
	for (j=0;j<5;j++)
	{
		SS	  = 0;//chip select 0
		recv  = spi_transfer(var);
		SS	  = 1;
		
		sprintf(arr,"Data from slave %x\r",recv);
		arr[29]=0;
		print_uart(arr);
		for (i=0;i<100;i++)
		{
			delay();
		}
		var++;
	}
	while(1);
}

void spi_init(void)
{
	unsigned char temp;
	TRISC3	= 1;
	TRISC4	= 0;
	TRISC5	= 0;
	TRISC1	= 0;
	SSPSTAT	= 0x00;
	SSPCON	= 0x14;  /*Synchronous Serial Port Enable bit*//*Synchronous Serial Port Enable bit*/
	SSPIE   = 0;
	SSPIF	= 0;
	SSPBUF	= 0;
	SSPEN	= 1;
	delay();	
	SSPBUF	= 0;
	while(SSPIF == 0);
	SSPIF	= 0;
	temp    = SSPBUF;
	SSPSTAT	= 0x00;
}

unsigned char spi_transfer(unsigned char data)
{
	SSPBUF	= data;
	while(SSPIF == 0);
	SSPIF	= 0;
	return SSPBUF;
}

void print_uart(unsigned char *str)
{
	
	while(*str)
	{
		uart_tx(*str);
		delay();
		str++;
	}
}

void delay()
{
		TMR1CS  = 0;	
		T1CKPS0 = 1;
		T1CKPS1 = 1;
		TMR1H   = 0X0B;
		TMR1L   = 0XDB;
		TMR1ON  = 1;
		while(!TMR1IF);
		TMR1IF  = 0;
		TMR1ON  = 0;
}

void uart_tx(unsigned char val)
{

	TXREG = val;
	while(TXIF==0);
	TXIF  = 0;
}

void uart_init(void)
{
	TRISC6 = 0; //making TX as output
	TRISC7 = 1; //making RX as input
	TXSTA  = 0x00; //Asynchronous mode, 8bit, low speed
	RCSTA  = 0x00; //Enable UART to use RC7 and RC6 as UART module pins
	SPBRG  = 31; //to generate 9600 baudrate
	TXEN   = 1;
	SPEN   = 1;
	TXIF   = 0;
	RCIF   = 0;
}