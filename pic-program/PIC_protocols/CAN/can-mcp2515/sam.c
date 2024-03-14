 #include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(FOSC_HS & WDTE_OFF & PWRTE_OFF & BOREN_ON & LVP_OFF & CPD_OFF & WRT_OFF & CP_OFF);
#define SS RD0

//	MCP2515_SPI INSTRUCTION SET
#define RESET 	0xC0
#define READ	0x03
#define WRITE	0x02
#define Read_Status	0xA0
#define RX_Status	0xB0
#define Bit_Modify	0x50

//	Message Request-To-Send
#define RTS_TXB0	0x81			//	Request-to-send for TXB0 
#define RTS_TXB1	0x82			//	Request-to-send for TXB1
#define RTS_TXB2	0x84			//	Request-to-send for TXB2

// BIT TIMING 
#define CNF1 0x2A					// 	CONFIGURATION 1 (ADDRESS: 2Ah)
#define CNF2 0x29					// 	CONFIGURATION 1 (ADDRESS: 29h)
#define CNF3 0x28					// 	CONFIGURATION 1 (ADDRESS: 28h)

//	Loopback Mode
#define CANCTRL 	0x0F			// 	CAN CONTROL REGISTER
#define CANSTAT 	0x0E			//	CAN STATUS REGISTER

//	Load Transmit Buffers
#define TX_TXB0SIDH	0x40			// TX buffer 0, Start at TXB0SIDH	0x31
#define TX_TXB0D0	0x41			// TX buffer 0, Start at TXB0D0		0x36
#define TX_TXB1SIDH	0x42			// TX buffer 1, Start at TXB1SIDH	0x41
#define TX_TXB1D0	0x43			// TX buffer 1, Start at TXB1D0		0x46
#define TX_TXB2SIDH	0x44			// TX buffer 2, Start at TXB2SIDH	0x51
#define TX_TXB2D0	0x45			// TX buffer 2, Start at TXB2D0		0x56

//Read Receive Buffers
#define RX_RXB0SIDH	 0x90			//	Receive Buffer 0,Start at RXB0SIDH	0x61
#define RX_RXB0D0	 0x92			//	Receive Buffer 0,Start at RXB0D0	0x66
#define RX_RXB1SIDH	 0x94			//	Receive Buffer 1,Start at RXB1SIDH	0x71
#define RX_RXB1D0	 0x96			//	Receive Buffer 1,Start at RXB1D0	0x76

//	Transmit control and status register
#define TXRTSCTRL 	0xD0			//	TXnRTS PIN CONTROL AND STATUS REGISTER

//	Transmit Buffer TXB0
#define TXB0CTRL	0x30			//	TRANSMIT BUFFER 0 CONTROL REGISTER
#define TXB0SIDH 	0x31			//	TRANSMIT BUFFER 0 STANDARD IDENTIFIER HIGH
#define TXB0SIDL 	0x32			//	TRANSMIT BUFFER 0 STANDARD IDENTIFIER LOW
#define TXB0EID8 	0x33			//	TRANSMIT BUFFER 0 EXTENDED IDENTIFIER HIGH
#define TXB0EID0 	0x34			//	TRANSMIT BUFFER 0 EXTENDED IDENTIFIER LOW
#define TXB0DLC 	0x35			//	TRANSMIT BUFFER 0 DATA LENGTH CODE

//	Transmit Buffer TXB1
#define TXB1CTRL	0x40			//	TRANSMIT BUFFER 1 CONTROL REGISTER
#define TXB1SIDH 	0x41			//	TRANSMIT BUFFER 1 STANDARD IDENTIFIER HIGH
#define TXB1SIDL 	0x42			//	TRANSMIT BUFFER 1 STANDARD IDENTIFIER LOW
#define TXB1EID8 	0x43			//	TRANSMIT BUFFER 1 EXTENDED IDENTIFIER HIGH
#define TXB1EID0 	0x44			//	TRANSMIT BUFFER 1 EXTENDED IDENTIFIER LOW
#define TXB1DLC 	0x45			//	TRANSMIT BUFFER 1 DATA LENGTH CODE

//	Transmit Buffer TXB2
#define TXB2CTRL	0x50			//	TRANSMIT BUFFER 2 CONTROL REGISTER
#define TXB2SIDH 	0x51			//	TRANSMIT BUFFER 2 STANDARD IDENTIFIER HIGH
#define TXB2SIDL 	0x52			//	TRANSMIT BUFFER 2 STANDARD IDENTIFIER LOW
#define TXB2EID8 	0x53			//	TRANSMIT BUFFER 2 EXTENDED IDENTIFIER HIGH
#define TXB2EID0 	0x54			//	TRANSMIT BUFFER 2 EXTENDED IDENTIFIER LOW
#define TXB2DLC 	0x55			//	TRANSMIT BUFFER 2 DATA LENGTH CODE

//	Transmit TXBnDm – TRANSMIT BUFFER n DATA BYTE m
#define TXB0D0		0x36			//	TRANSMIT BUFFER n DATA BYTE m	36h - 3Dh
#define TXB1D0		0x46			//	TRANSMIT BUFFER n DATA BYTE m	46h - 4Dh
#define TXB2D0		0x56			//	TRANSMIT BUFFER n DATA BYTE m	56h - 5Dh

//	RECEIVE MESSAGE BUFFERING 
#define RXB0CTRL 	0x60			//  RECEIVE BUFFER 0 CONTROL
#define RXB1CTRL 	0x70			//	RECEIVE BUFFER 1 CONTROL
#define BFPCTRL 	0xC0			//	RXnBF PIN CONTROL AND STATUS
#define RXB0SIDH 	0x61			//	RECEIVE BUFFER 0 STANDARD IDENTIFIER HIGH
#define RXB0SIDL 	0x62			//	RECEIVE BUFFER 0 STANDARD IDENTIFIER LOW
#define RXB0EID8 	0x63			//	RECEIVE BUFFER 0 EXTENDED IDENTIFIER HIGH
#define RXB0EID0 	0x64			//	RECEIVE BUFFER 0 EXTENDED IDENTIFIER LOW
#define RXB0DLC 	0x65			//	RECEIVE BUFFER 0 DATA LENGHT CODE
#define RXB0D7 		0x66 			//	RECEIVE BUFFER 0 DATA BYTE 7
#define RXB1SIDH 	0x71			//	RECEIVE BUFFER 1 STANDARD IDENTIFIER HIGH
#define RXB1SIDL 	0x72			//	RECEIVE BUFFER 1 STANDARD IDENTIFIER LOW
#define RXB1EID8 	0x73			//	RECEIVE BUFFER 1 EXTENDED IDENTIFIER HIGH
#define RXB1EID0 	0x74			//	RECEIVE BUFFER 1 EXTENDED IDENTIFIER LOW
#define RXB1DLC 	0x75			//	RECEIVE BUFFER 1 DATA LENGHT CODE
#define RXB1D8 		0x76 			//	RECEIVE BUFFER 1 DATA BYTE 8

//	Message Acceptance Filters and Masks
#define RXF0SIDH  	0x00			// 	FILTER 0 STANDARD IDENTIFIER HIGH
#define RXF1SIDH  	0x04			// 	FILTER 1 STANDARD IDENTIFIER HIGH
#define RXF2SIDH  	0x08			// 	FILTER 2 STANDARD IDENTIFIER HIGH
#define RXF3SIDH  	0x10			// 	FILTER 3 STANDARD IDENTIFIER HIGH
#define RXF4SIDH  	0x14			// 	FILTER 4 STANDARD IDENTIFIER HIGH
#define RXF5SIDH  	0x18			// 	FILTER 5 STANDARD IDENTIFIER HIGH
#define RXF0SIDL 	0x01			// 	FILTER 0 STANDARD IDENTIFIER LOW
#define RXF1SIDL 	0x05			// 	FILTER 1 STANDARD IDENTIFIER LOW
#define RXF2SIDL 	0x09			// 	FILTER 2 STANDARD IDENTIFIER LOW
#define RXF3SIDL 	0x11			// 	FILTER 3 STANDARD IDENTIFIER LOW
#define RXF4SIDL 	0x15			// 	FILTER 4 STANDARD IDENTIFIER LOW
#define RXF5SIDL 	0x19			// 	FILTER 5 STANDARD IDENTIFIER LOW
#define RXF0EID8 	0x02			// 	FILTER 0 EXTENDED IDENTIFIER HIGH
#define RXF1EID8 	0x06			// 	FILTER 1 EXTENDED IDENTIFIER HIGH
#define RXF2EID8 	0xA0			// 	FILTER 2 EXTENDED IDENTIFIER HIGH
#define RXF3EID8 	0x12			// 	FILTER 3 EXTENDED IDENTIFIER HIGH
#define RXF4EID8 	0x16			// 	FILTER 4 EXTENDED IDENTIFIER HIGH
#define RXF5EID8 	0x1A			// 	FILTER 5 EXTENDED IDENTIFIER HIGH
#define RXF0EID0 	0x03			// 	FILTER 0 EXTENDED IDENTIFIER LOW
#define RXF1EID0 	0x07			// 	FILTER 1 EXTENDED IDENTIFIER LOW
#define RXF2EID0 	0x0B			// 	FILTER 2 EXTENDED IDENTIFIER LOW
#define RXF3EID0 	0x13			// 	FILTER 3 EXTENDED IDENTIFIER LOW
#define RXF4EID0 	0x17			// 	FILTER 4 EXTENDED IDENTIFIER LOW
#define RXF5EID0 	0x1B			// 	FILTER 5 EXTENDED IDENTIFIER LOW
#define RXM0SIDH 	0x20			//	MASK 0 STANDARD IDENTIFIER HIGH
#define RXM1SIDH 	0x24			//	MASK 1 STANDARD IDENTIFIER HIGH
#define RXM0SIDL 	0x21			//	MASK 0 STANDARD IDENTIFIER LOW
#define RXM1SIDL 	0x25			//	MASK 1 STANDARD IDENTIFIER LOW
#define RXM0EID8 	0x22			//	MASK 0 EXTENDED IDENTIFIER HIGH
#define RXM1EID8 	0x26			//	MASK 1 EXTENDED IDENTIFIER HIGH
#define RXM0EID0 	0x23			//	MASK 0 EXTENDED IDENTIFIER LOW
#define RXM1EID0 	0x27			//	MASK 1 EXTENDED IDENTIFIER LOW

void spi_init(void);
unsigned char spi_read(void);
unsigned char spi_trans(unsigned char);
unsigned char spi_reciv(unsigned char);
void delay(void);
unsigned char a,b,c;
void uart_tx(unsigned char data);
unsigned uart_rx(void);
void uart_print2(unsigned char s);
void uart_print(unsigned char *str);
void uart_init(); 

int main()
{
    uart_init();
	spi_init();
	__delay_ms(1000);

	uart_print("\n\r");
	uart_print(" SOL"); 

	uart_print("\n\r");
   
    spi_trans(0xC0);
    a = spi_read();
    uart_print2(a);
    uart_print("\n\r");
	__delay_ms(200);
    spi_trans(0x03);
     a = spi_read();
    uart_print2(a);
    uart_print("\n\r");
    spi_trans(0xE);
    a = spi_read();
    uart_print("\n\r");
    uart_print2(a);
   
/*    spi_trans(READ);
    a=spi_trans(CANSTAT);
    uart_print("\n\r"); 
    uart_print2(a);
    
    spi_trans(WRITE);
    spi_trans(CNF1);
    spi_trans(0x82);
    spi_trans(CNF2);
    spi_trans(0xFF);
    spi_trans(CNF3);
    spi_trans(0x02);
    
 
    spi_reciv(RXB0SIDH);    
    SS=1;  */
    
    while(1);
}

void spi_init()
{
	TRISD0 		= 0;		
	TRISC1  	= 0;
    TRISC0 		= 0;
	TRISC3  	= 0;
	TRISC4  	= 1; // Master in slave out 
	TRISC5  	= 0; // Master out slave in
    SSPEN  		= 1; // Synchronous Serial Port Enable
	SSPSTAT 	= 0X00;
	SSPCON  	|= 0X12; // Clock Polarity Select bit	
	SSPIE  		= 0;
	SSPIF  		= 0;
    RC0 		= 1;
	SSPEN  		= 1; // Synchronous Serial Port Enable bit
	RD0 		= 1;
}

unsigned char spi_trans(unsigned char data)
{
	RD0 		= 0;
	SSPBUF = data;
	while(SSPIF == 0);
	SSPIF = 0;
	RD0 		= 1;
    return SSPBUF;
}

unsigned char spi_reciv(unsigned char incoming)
{
//	SS = 0;
	spi_trans(0x03);
	c=spi_trans(CANSTAT);
//	while(!(SSPSTAT & 1));
//	c=SSPBUF;
//	SS = 1;
	uart_print("\n\r");
	uart_print2(c);
}

void uart_tx(unsigned char data)
{
	 TXREG=data;
	 while(!TXIF);
	 TXIF=0;
}

unsigned uart_rx(void)
{
	while(!RCIF);
	RCIF=0;
	return RCREG;
}
void uart_print(unsigned char *str)
{
	while(*str)
	{
		uart_tx(*str++);
	}
}
void uart_init()
{
	TRISC6=0;
	TRISC7=1;
	TXSTA=0X20;
	RCSTA=0X90;
	SPBRG=31;
	TXIF=0;
	RCIF=0;
}

void uart_print2(unsigned char s)
{
	for(int i=7; i>=0; i--)
	{
			if(s & (1<<i))
		 		uart_tx('1');
		 else
		 	uart_tx('0');
	}
}

unsigned char spi_read(void)
{
	RD0 		= 0;
	SSPBUF = 0x11;		// dummy data
	while(SSPIF == 0);
	SSPIF = 0;
	RD0 		= 1;
	while(!(SSPSTAT & (1<<0)));
    return SSPBUF;
}