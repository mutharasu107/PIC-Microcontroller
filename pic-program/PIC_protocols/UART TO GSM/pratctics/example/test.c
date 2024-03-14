#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1f7a);

#define RS RC0
#define RW RC1 
#define EN RC2

#define PIR RD1

char AT[]="AT\r\n";
char phone[]="ATD9487855450;\r\n";
char set_sms[]="AT+CMGF=1\r\n";
char send_message[]="Human Detected\r\n";
char mobile_no[]="AT+CMGS=\9487855450\r\n";
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
		RD0=1;
	}
	else
	{
		RD0=0;
	}
}

void uart_init()
{
	TRISD1=1;
	TRISD0=0;
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
		__delay_ms(50);
	}
}

void sensor(void)
{
	
	int i,j,k=0;
	if(PIR==1)
	{   
		led();
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
	    lcd_print("Calling   Number");
	    lcd_cmd(0xc0);
	    lcd_print("   9487855450   ");
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