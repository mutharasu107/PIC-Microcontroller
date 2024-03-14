#include<htc.h>
 
#define _XTAL_FREQ 20000000
__CONFIG(0X1F7A);
 
 
void ser_int();
void tx(unsigned char);
unsigned char rx();
void tx_str(unsigned char *);
 
void call(unsigned char *num2);
void gsm_delay();
 
char AT[]="AT\r\n";   // To initialize mode
char noecho[]="ATE0\r\n";   // To stop echo
char mode_text[]="AT+CMGF=1\r\n";   // to set text mode
char char_mode[]="AT+CSCS=\"GSM\"\r\n";   // to set character mode
char param[]="AT+CSMP=17,167,0,0\r\n";   // set the parameter of character
char mobile_no[]="AT+CMGS=\"9632279895\"\r\n";   //use to set receinpent number and mesg
char terminator[]="CTRL+Z";     // chartacter form of control + z terminator character
char mesg[]="GSM MISSION ACCOMPLISHED";   // mesg we want to send
char ph[]="ATD9632279895;\r\n";// to make call
char stop[]="ATH";// HANG OFF
 
int main()
{
        ser_int();		//initialize UART
		
		tx_str(AT);		
		__delay_ms(100);

		
		tx_str(ph);
		__delay_ms(1000);

		
		tx_str(AT);
		__delay_ms(100);

				
        tx_str(noecho);
		__delay_ms(100);

		
		tx_str(mode_text);
		__delay_ms(100);

		tx_str(char_mode);
		__delay_ms(100);
	
		
		tx_str(param);
		__delay_ms(100);
	
	
		tx_str(mobile_no);
		__delay_ms(100);
		
		
		tx_str(mesg);
		tx(0X1A);
		__delay_ms(1000);
		
		while(1);
}
 
void ser_int()
{
	TRISC6=0;//tx pin enable
	TRISC7=1;//rx pin enable
	TXSTA=0x20; //BRGH=0, TXEN = 1, Asynchronous Mode, 8-bit mode
	RCSTA=0x90; //Serial Port enabled,8-bit reception
	SPBRG=31; //9600 baudrate for 11.0592Mhz
	TXIF=RCIF=0;
}
 
void tx(unsigned char a)
{
	TXREG=a;
	while(!TXIF);
	TXIF = 0;
}
 
unsigned char rx()
{
	while(!RCIF);
	RCIF=0;
	return RCREG;		
}
 
void tx_str(unsigned char *s)
{
	while(*s) 
	{
		tx(*s++);
	}
}