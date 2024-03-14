
 /*************************************************/
 /* NAME        :   PERUMAL.R                     */               
 /* DESCRIPTION :  GSM INTERFACE WITH PIR SENSOR  */                                                                              
 /* DATE        :   ..........                    */ 
 /*                                               */
 /*************************************************/

#include<htc.h>
#define _XTAL_FREQ 20000000
__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_OFF & CP_OFF & BOREN_ON & LVP_OFF & CPD_OFF & WRT_OFF & DEBUG_OFF);

//#define NUMBER 7867040324    //Here insert your number where you want to send message

#define Rs RC0
#define Rw RC1
#define En RC2

// this declare to PIR sensor 
#define PIR RD1
void PIR_SENSOR(void);

//uart protocols & Function
void uart_tx(unsigned char  val);
unsigned char uart_rx(void);
void uart_tmp(unsigned char *);
void uart_init(void);

//Lcd function
void Lcd_cmd(unsigned char cmd);
void Lcd_data(unsigned char data);
void Lcd_tmp(unsigned char *);
void Lcd_init(void);
void Lcd_clrscr();

void port_config(void);
void  LED(void);

unsigned char AT[]="AT\r\n"; //TRANSMIT MODE 
unsigned char noecho[]="ATE0\r\n"; //STOP THE ECHO
unsigned char text_msg[]="AT+CMGF=1\r\n"; //sending a massage mode
unsigned char check[]="AT+CSCS=\"GSM\"\r\n";
unsigned char service[]="AT+CSMP=17,167,0,0\r\n";
unsigned char number[]="AT+CMGS=\"9566781406\"\r\n";
//unsigned char terminal[]= "CTRL+Z\r\n";
unsigned char msg[]=" ";
unsigned char ph[]="ATD9566781406;\r\n"; // TO MAKE A CALL
unsigned char stop[]="ATH"; //HANG OFF 
	

int main(){
	
    port_config(); //PORT-initilazation
	uart_init();   //UART-initilazation		
	LED();		   // Led -initilazation
	Lcd_init();    //Lcd-initilazation
	Lcd_clrscr();  //lcd_clear function

	while(1){

			PIR_SENSOR();  //pir_sensor function

	}
	
}
//PORT CONFIGURATION
void port_config(void){
	
	PORTB 	=   0;
	TRISB	=	0;
	TRISC0 	= TRISC1 = TRISC2 = 0;
	PORTD	=	0;
	TRISD0	=	0;
	TRISD1 	=	1;
	TRISD2	= 	1;
	TRISD3	= 	0;
	TRISC3	=	1;
	
}
//LED FUNCTION
void LED(void){
	
	if(RD1==1){ //It WILL CHECK CONNDTION IT TRUE 0R FALS
		RD0	=	1;  //ON THE LED
	}
	else{
		RD0	=	0; //OFF THE LED

	}

} 
//UART-INITIALIZATION
void uart_init(void){  //I INITILAZIED UART CONFIGURATION AND PORT

	TRISC6	= 	0;
	TRISC7	=	1;
	SPBRG	=	31; 
	SPEN	=	1;
	TXSTA	=	0x20;
	RCSTA	=	0x90;
	TXIF=RCIF =	0;
}
//UART-TRANSMITER CONFIGURATION
void uart_tx(unsigned char val){
		TXREG	=	val;                
	while(!TXIF);                       
		TXIF	=	0;	
}
//UART-RECIVER CONFIGURATION
unsigned char uart_rx(void){

	while(RCIF==0);
		RCIF	=	0;
	return RCREG;
	
}
//UART-PRINTING A STRINGS OR CHARACTERIZE 
void  uart_tmp(unsigned char *var){

	while(*var){
		uart_tx(*var++);

	}
}
//PIR -SENSOR CONFIGURATION & GSM CONFIGURATION
void PIR_SENSOR(void){
	int j=0,k=0,a;

		if(PIR==1)
		{
			LED();	
   			if(j==0);
			{
				
				uart_tmp(AT);
				__delay_ms(10);
		
				uart_tmp(ph);
				uart_tmp("PIR=>HUMAN DECTCION\r\n");
				__delay_ms(100);
			
				uart_tmp(text_msg);
				__delay_ms(10);
				
				uart_tmp(number);
				__delay_ms(10);
			
				uart_tmp("=>HUMAN IS DECTICION\n");
				__delay_ms(10);
				
				uart_tmp(msg);
	   			uart_tx(0x1A);
				__delay_ms(100);

				Lcd_tmp("PIR=>HUMAN DECTCION\r\n");
				Lcd_clrscr();
				j++;
				k=0;
			}
		
		}
		else
		{ 
			k++;
			if(k==1)
			{
				LED();
				Lcd_tmp("PIR=>NOT DECTCION\r\n");
				Lcd_clrscr();
				j=0;
			}
		}
}

//LCD-PORT CONFIGURATION
void Lcd_cmd(unsigned char cmd){
	
	Rs	=	0;
	Rw	=	0;
	En	=	1;
	PORTB=cmd;
	__delay_ms(5);
	En	=	0;
	
}
//LCD-INITIALIZATION
void Lcd_init(void){
	
	Lcd_cmd(0x38);
	Lcd_cmd(0x0c);
	Lcd_cmd(0x06);
	Lcd_cmd(0x80);
}

//LCD-CLEAR FUNCTION
void Lcd_clrscr(void){
		
	Lcd_cmd(0x38);
	Lcd_cmd(0x0c);
	Lcd_cmd(0x06);
	Lcd_cmd(0x80);
}
//LCD-DATA TRANSFER FUNCTION
void Lcd_data(unsigned char data){
	
	Rs	=	1;
	Rw 	=	0;
	En 	=	1;
	PORTB=data;
	__delay_ms(5);
	En 	=	0;
}
//LCD-PRINT & COMMANDS
void Lcd_tmp(unsigned char *s){

	while(*s){
		Lcd_data(*s++);
		__delay_ms(2);
	}
}
/*----------------------------GSM & PIR-SENSOR MODULES--------------------------*/ 