#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0X1F7A);

#define RS RD5
#define RW RD6
#define EN RD7

void lcd_tx(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = cmd;
	__delay_ms(100);
	EN = 0;	
}

void lcd_rx(unsigned char val)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = val;
	__delay_ms(100);
	EN = 0;	
}

void lcd_init()
{
	TRISB = 0X00;
	TRISD = 0X00;
	__delay_ms(100);
	lcd_tx(0x38);
	lcd_tx(0x0f);
	lcd_tx(0x0c);
	lcd_tx(0x02);
	lcd_tx(0x06);
	lcd_tx(0x80);
	__delay_ms(100);
	lcd_tx(0x01);
}
void uart_init()
{ 
	TRISA0 = 0;
	TRISA1 = 0;
	TRISA2 = 0;
	TRISC6 = 0;
	TRISC7 = 1;
	TXSTA = 0X20;   //Transmit Enable Bit
	RCSTA = 0X90;   //Serial port enable bit = 1,Continus recevi enable bit = 1.
	SPBRG = 31;
	TXIF = 0;
	RCIF = 0;
}

int main()
{
	unsigned char R,Y,G;
	unsigned char data;
	lcd_init();
	uart_init();
	while(1)
	{
		while(RCIF == 0);
		RA1 = 0;
	    data = RCREG;
	    lcd_rx(data);
	    RA1 = 1;
	    __delay_ms(500);
	    
	    while(RCIF == 0);
		RA2 = 0;
	    data = RCREG;
	    lcd_rx(data);
	    RA2 = 1;
	    __delay_ms(500);
	    
	    while(RCIF == 0);
		RA0 = 0;
	    data = RCREG;
	    lcd_rx(data);
	    RA0 = 1;
	    __delay_ms(500);
	    
	    while(RCIF == 0);
	    data = RCREG;
	    lcd_rx(data);
	    __delay_ms(500);
	}
}
