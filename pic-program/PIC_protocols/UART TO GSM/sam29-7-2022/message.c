#include<htc.h>
#define _XTAL_FREQ 20000000 
__CONFIG(0x1F7A);

#define PIR RD1

void Uart_tx(unsigned char data);
unsigned char Uart_rx(void);
unsigned char uart_init();

char atcall[]="ATA\r\n";//Atten incoming call
char AT[]="AT\r\n";   // To initialize mode
char noecho[]="ATE0\r\n";   // To stop echo
char mode_text[]="AT+CMGF=1\r\n";   // to set text mode
char char_mode[]="AT+CSCS=\"GSM\"\r\n";   // to set character mode
char param[]="AT+CSMP=17,167,0,0\r\n";   // set the parameter of character
char mobile_no[]="AT+CMGS=\"9487855450\"\r\n";   //use to set receinpent number and mesg
char terminator[]="CTRL+Z";     // chartacter form of control + z terminator character
char mesg[]="Human Detected";   // mesg we want to send
char nomesg[]="Human not Detected";
char ph[]="ATD9487855450;\r\n";// to make call
char stop[]="ATH";// HANG OFF


void Uart_tx(unsigned char data)
{
	TXREG=data;
    while(!TXIF);
    TXIF = 0;
}

unsigned char Uart_rx(void)
{
	while(!RCIF);
	RCIF=0;
    return RCREG;
}

void LED(void)
{
	if(RD1==1) //It WILL CHECK CONNDTION IT TRUE 0R FALS
	{
		RD0	=	1;  //ON THE LED
	}
	else
	{
		RD0	=	0; //OFF THE LED
	}
} 

void uart_print(unsigned char *str)
{
	while(*str)
	{
		Uart_tx(*str++);	
	}
}
unsigned char uart_init()
{
	TRISD1 = 1;
	TRISD0 = 0;
	TRISC6 = 0;                             // Set Tx pin Output
	TRISC7 = 1;                             // Set RX pin input
	TXSTA = 0X20;                           // Transmit Enabled Bit 
	RCSTA = 0X90;                           // Serial Port Enable Bit   
    SPBRG=31;                               // BaudRate = 9600
    TXIF = 0;
    RCIF = 0;	                     
}
                     
void pir_sensor(void)
{
    int j=0;
	if(PIR==1)
    {
	    LED();
	    if(j==0);
		{
			uart_print(AT);
	        __delay_ms(100);
	
	        uart_print(ph);
	        __delay_ms(3000);
	
	        uart_print(mode_text);
	        __delay_ms(100);
	
	        uart_print(char_mode);
	        __delay_ms(100);
	
	        uart_print(param);
	        __delay_ms(100);
	
	        uart_print(mobile_no);
	        __delay_ms(100);
	
	        uart_print(mesg);
	        Uart_tx(0x1a);
	        __delay_ms(1000);
	    }
	}
	else
	{
		LED();
		uart_print(nomesg);
	    Uart_tx(0x1a);
	    __delay_ms(1000);
   }
	   
}

int main()
{
	uart_init();
	while(1)
	{
		pir_sensor();	
	}
}