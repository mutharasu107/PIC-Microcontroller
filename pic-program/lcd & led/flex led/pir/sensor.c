


/*****************************************************/
/*  NAME      : R.Mutharasu.                         */
/*  DATE      : 28-08-2022.                          */
/*  PROJECT   : Smart Agriculture System.            */
/*****************************************************/


#include <htc.h> 
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

#define RS RC0
#define RW RC1
#define EN RC2

#define PIR RD1

void uart_tx(unsigned char val);
unsigned uart_rx(void);
void uart_print(unsigned char *s);
void uart_init();
void led();
void lcd_cmd(unsigned char data);
void lcd_data(unsigned char val);
void lcd_print(unsigned char *str);
void lcd_init();
void pir_sensor();


char AT[]="AT\r\n";
char phone[]="ATD6380695575;\r\n";
char set_sms[]="AT+CMGF=1\r\n";
char send_message[]="Human Detected\r\n";
char mobile_no[]="AT+CMGS= 6380695575\r\n";
char no_message[]="Human Not Detected\r\n";

void uart_tx(unsigned char val)
{
	TXREG = val;
	while(!TXIF);
	TXIF = 0;
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

void uart_init()
{
	TRISC6 = 0;
	TRISC7 = 1;
	TRISD1 = 1;
	TRISD0 = 0;
	TRISD2 = 0;
	TRISD3 = 0;
	TRISD4 = 0;
	TXSTA = 0X20;
	RCSTA = 0X90;
	SPBRG = 31;
	TXIF = 0;
	RCIF = 0;
}

void led()
{
	if(RD1==1)
	{
		RD0 = 1;
		RD2 = 1;
		RD3 = 1;
		RD4 = 1;
	}
	else
	{
		RD0 = 0;
		RD2 = 0;
		RD3 = 0;
		RD4 = 0;
	}
}

void lcd_cmd(unsigned char data)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = data;
	__delay_ms(10);
	EN = 0;
}

void lcd_data(unsigned char val) 
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = val;
	__delay_ms(10);
	EN = 0;
	
}

void lcd_print(unsigned char *str)
{
	while(*str)
	{
		lcd_data(*str++);
	}
}

void lcd_init()
{
	TRISB = 0;
	TRISC0 = 0;
	TRISC1 = 0;
	TRISC2 = 0;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x38);
	lcd_cmd(0x0f);
	lcd_cmd(0x0c);
	lcd_cmd(0x06);
	lcd_cmd(0x80);
	__delay_ms(2);
}

void pir_sensor()
{
	lcd_cmd(0x01);
	int i=0;
	if(PIR==1)
	{
		led();
		if(i==0)
		{
			uart_print(AT);
			__delay_ms(300);
			
			uart_print(phone);
		
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_print("Animal Detected");
//			__delay_ms(3000);
			
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_print("   Dialling   ");
			lcd_cmd(0xc0);
			lcd_print("  6380695575   ");
			__delay_ms(3000);
			__delay_ms(3000);
			__delay_ms(3000);
//			__delay_ms(3000);
//			__delay_ms(3000);	
//		    __delay_ms(3000);	
//		    __delay_ms(3000);	
//		    __delay_ms(3000);
		    lcd_cmd(0x01);	
		}
	}
	else
	{
		led();
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_print("School Of Linux ");
		lcd_cmd(0xc0);
		lcd_print("   Dharmapuri   ");
		uart_print(no_message);
		uart_tx(0x18);
		__delay_ms(1000);
	}
}

int main()
{
	uart_init();
	lcd_init();
	while(1)
	{
		pir_sensor();
	}
}
/************************* END *******************************************/