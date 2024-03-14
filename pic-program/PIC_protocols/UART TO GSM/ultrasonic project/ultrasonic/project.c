
#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1f7a);

#define RS RC0
#define RW RC1 
#define EN RC2

#define PIR RD1

char AT[]="AT\r\n";
char phone[]="ATD6380695575;\r\n";
char set_sms[]="AT+CMGF=1\r\n";
char send_message[]="Human Detected\r\n";
char mobile_no[]="AT+CMGS=\"6380695575"\r\n";
char no_message[]="Human Not Detected";

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

void uart_print(unsigned char *s)
{
	while(*s)
	{
		uart_tx(*s++);
	}
}

void led()
{
	if(RD1==1)
	{
		RA0=1;
	}
	else
	{
		RA0=0;
	}
}

void uart_init()
{
	TRISD1=1;
	TRISA0=0;
	TRISC6=0;
	TRISC7=1;
	TXSTA=0X20;
	RCSTA=0X90;
	SPBRG=31;
	TXIF=0;
	RCIF=0;
}

void lcd_cmd(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB=cmd;
	__delay_ms(10);
	EN = 0;
}

void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB=data;
	__delay_ms(10);
	EN = 0;
}

void lcd_init()
{
	TRISB=0;
	TRISC0=0;
	TRISC1=0;
	TRISC2=0;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x38);
	lcd_cmd(0x0f);
	lcd_cmd(0x0c);
	lcd_cmd(0x06);
	lcd_cmd(0x80);
}


void lcd_print(unsigned char *str)
{
	while(*str)
	{
		lcd_data(*str++);
	}
}

void sensor(void)
{
	
	int k=0;
	int a,b,c,d,f;
	TRISD2=0;
	TRISD3=1;
	if(PIR==1)
    {
	    led();
	    T1CON = 0x10;               //Initialize Timer Module
	    
            TMR1H = 0;                //Sets the Initial Value of Timer
            TMR1L = 0;                //Sets the Initial Value of Timer

            RD2 = 1;                  //TRIGGER HIGH
            __delay_us(10);           //10uS Delay 
            RD2 = 0;                  //TRIGGER LOW
            
            while(!RD3);              //Waiting for Echo
            TMR1ON = 1;               //Timer Starts
            while(RD3);               //Waiting for Echo goes LOW
            TMR1ON = 0;               //Timer Stops

            a = (TMR1L | (TMR1H<<8)); //Reads Timer Value
            b = a/58.02;              //Converts Time to Distance
            c = b +1;                //Distance Calibration
            if(c>=0 && c<=30)        //Check whether the result is valid or not
            {
	            lcd_cmd(0x80);
                lcd_print("Distance = ");
                __delay_ms(200);
     
                lcd_cmd(0x8D);
                lcd_data(c%10 + 48);
                
                lcd_cmd(0x8C);
                d = c/10;
                lcd_data(d%10 + 48);
      
                lcd_cmd(0x8B);
                f = d/10;
                lcd_data(f%10 + 48);	

                lcd_cmd(0x8E);
                lcd_print("cm");
                __delay_ms(300);
            }
            else
            {
	            lcd_cmd(0x01);
                lcd_cmd(0x80);
                lcd_print("Out of Range");
                __delay_ms(2000);
            }
		    if(k==0)
		    {
			    uart_print(AT);
			    __delay_ms(100);
			   	
			    uart_print(phone);
			
		        lcd_cmd(0x01);
	            lcd_cmd(0x80);
	            lcd_print("Animal Detected");
	            __delay_ms(3000);
	
	            lcd_cmd(0x01);
	            lcd_cmd(0x80);
	            lcd_print("Dialing  Number");
	            lcd_cmd(0xc0);
	            lcd_print("   6380695575   ");
	            __delay_ms(3000);
	            __delay_ms(3000);
	            __delay_ms(3000);
	            __delay_ms(3000);
	            __delay_ms(3000);
	            __delay_ms(3000);
	            __delay_ms(3000);
	            __delay_ms(3000);
	            __delay_ms(3000);
	            __delay_ms(3000);
			    lcd_cmd(0x01);
		   }
	}
	else
	{
		led();
		uart_print(no_message);
		uart_tx(0x1a);
		__delay_ms(1000);
	}
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_print("School Of linux");
	lcd_cmd(0xc0);
	lcd_print("  Dharmapuri.  ");
}

int main()
{	
	lcd_init();
	uart_init();
  
	while(1)
	{
		sensor();
	}
}
