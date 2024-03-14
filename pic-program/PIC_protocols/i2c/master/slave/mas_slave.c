

#include <htc.h>
#include <stdio.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);/*FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF*/

void print_uart(unsigned char *str);
void uart_init();
void uart_tx(unsigned char data);
void delay();
void i2c_init(void);
void i2c_start(void);
void i2c_wait(void);
void i2c_write(unsigned char val);
unsigned short i2c_read(unsigned short ack);
void i2c_stop(void);

unsigned char string[] = "school of linux\r";

int main()
{
	int a[8],i=0,b,c;
	unsigned char buffer[50];
	
	uart_init();
	i2c_init();
	
	print_uart(string);
	
	i2c_wait();
	i2c_start();
	i2c_write(0xEE); // sending device address with write 0xd0 
	i2c_write(0XF4); // sending ram address 0x00 
	i2c_write(0x2E); // load value 
	i2c_stop();
	
	i2c_wait();
	i2c_start();
	i2c_write(0xEE); // sending device address with write 0xd0 
	i2c_write(0xF6); // sending ram address 0x00 
	i2c_read(0);
	i2c_stop();
	
	i2c_wait();
	i2c_write(0xEF); // sending device address with write 0xd0 
	b = i2c_read(0);
	c = i2c_read(1);
	for(i=0 ; i<8; i++)
	{
		a[i] = i2c_read(1);
	}
	
	i2c_stop();
	sprintf(buffer,"%x %x : %x\r %x\r %x : %x : %x\r",a[2],a[1],a[0],a[3],a[4],a[5],a[6]);
	
	print_uart(buffer);
	delay();
    while(1);
	
}

void print_uart(unsigned char *str)
{
	while(*str)
	{
		uart_tx(*str);
		*str++;
	}
}

void uart_tx(unsigned char data)
{
	TXREG = data;
    while(TXIF==0);
    TXIF = 0;
}

void i2c_init()
{
	TRISC3 = 0;
	TRISC4 = 0;
	SSPCON = 0X28;
	SSPCON2 = 0X00;
	SSPSTAT = 0X00;
	SSPADD = 0X31;
}


void i2c_wait()
{
	while(SSPCON2 & 0X1F || SSPSTAT & 0X04);
}

void i2c_start()
{
	i2c_wait();
	SEN = 1;
}

void i2c_write(unsigned char val)
{
	i2c_wait();
	SSPBUF = val;
}

unsigned short i2c_read(unsigned short ack)
{
	unsigned short recv;
	i2c_wait();
	RCEN = 1;
	
	i2c_wait();
	recv = SSPBUF;
	
	i2c_wait();
	ACKDT = (ack)?0:1;
	ACKEN = 1;
	return recv;
}

void i2c_stop()
{
	i2c_wait();
	PEN = 1;
}

void delay()
{
	TMR1CS = 0;
	T1CKPS0 = 1;
	T1CKPS1 = 1;
	TMR1H = 0X0B;
	TMR1L = 0XDB;
	TMR1ON = 1;
	while(!TMR1IF);
	TMR1IF = 0;
	TMR1ON = 0;
}

void uart_init()
{
	TRISC6 = 0;
	TRISC7 = 1;
	TXSTA = 0X20;
	RCSTA = 0X80;
	SPBRG = 0X31;
	TXIF = 0;
	RCIF = 0;
}