#include <htc.h>
#define _XTAL_ 20000000
__CONFIG(0x1F7A);

#define MAX_UART_BYTES 40

/*
#define SPEED_9600 0
#define SPEED_19200 1
#define SPEED_28800 2
#define SPEED_33600 3
#define SPEED_57600 4
*/

enum UART_SPEED{
	SPEED_9600,
	SPEED_19200,
	SPEED_28800,
	SPEED_33600,
	SPEED_57600
};


void interrupt_config(void);
void port_config(void);
void interrupt ISR(void);
void uart_tx(unsigned char val);
void uart_rx(void);
void uart_init(unsigned char speed);
void uart_print(unsigned char *str);
void init(void);

unsigned char is_recv;
unsigned char is_tx;
unsigned char uart_rdata;
unsigned char uart_byte_count;
unsigned char UART_RX_BUFF[MAX_UART_BYTES + 1];
unsigned char UART_TX_BUFF[MAX_UART_BYTES + 1];
const unsigned char UART_SPEED[5] = {31, /* 9600 */
									 15, /* 19200 */
									 9, /* 28800 */
									 8, /* 33600 */
									 4 /* 57600 */};


void main()
{
	init();
	uart_print((unsigned char*)"uart_initialized\r\n");
	while(1)
	{
	}
}

void init(void)
{
	port_config();
	uart_init(SPEED_19200);
	interrupt_config();
}

void interrupt_config(void)
{
	// Disable all interrupt flag and Clear all interrupt flage
	INTCON 	= 0;
	PIE1 	= 0;
	PIE2 	= 0;
	PIR1 	= 0;
	PIR2 	= 0;
	
	// USART Receive Interrupt Enable bit
	RCIE = 1;
	
	// Peripheral Interrupt Enable bit
	PEIE = 1;
	
	// Global Interrupt Enable bit
	GIE = 1; 
}

void port_config(void)
{
	// Portconfigure as a output
	TRISC = 0;
}

void interrupt ISR(void)
{
	
	// Global Interrupt Disable bit
	GIE = 0;
	if(RCIF) {
		// Clear the interrupt flag bit
		RCIF = 0;
		uart_rdata = RCREG;
		//required logic while uart interrut happens
		is_recv = 1;
	}
	
	if(TXIF) {
		static	unsigned int temp = 0;
		// Clear the interrupt flag bit
		TXIF = 0;
		if(is_tx) {
			if(temp < uart_byte_count) {
				TXREG = UART_TX_BUFF[temp++];
			} else {
				is_tx = 0;
				temp = 0;
				TXIE = 0;
			}
			
		}
	}
	// Global Interrupt Enable bit
	GIE = 1;
}

void uart_init(unsigned char speed)
{
	TRISC6 = 1;//High for 25 pin RC6/TX/CK
	TRISC7 = 0;//lOW FOR 26 PIN RC7/RX/DT
	TXSTA = 0X00;//TX Status & Control Reg (add 98h)
	RCSTA = 0X00;//RC Status & Control Reg (add 18h)
	SPBRG = UART_SPEED[speed];//Badu rate set 9600 bit for second
	TXEN = 1;//TX enable bit 
	SPEN = 1;//Serial Port Enable Bit	
}

void uart_tx(unsigned char val)
{
	TXREG = val;//Transmit buffer
	while(TXIF == 0);//condition checking
	TXIF = 0;
}

void uart_print(unsigned char *str)
{
	unsigned char loop1=0;
	//load the first char
	TXREG = str[0];	//transmission started
	str++;
	uart_byte_count=0;
	for(loop1=0; loop1<MAX_UART_BYTES; loop1++,str++)
	{
		if(*str){
			UART_TX_BUFF[loop1] = *str;
			uart_byte_count++;
		} else {
			break;
		}
	}
	UART_TX_BUFF[loop1] = '\0';
	is_tx = 1;
	TXIE = 1;
}