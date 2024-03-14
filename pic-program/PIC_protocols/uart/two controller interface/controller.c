#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0X1F7A);

#define RS RD5
#define RW RD6
#define EN RD7

void lcd_init();
void uart_init();

void lcd_cmd(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = cmd;
//	__delay_ms(50);
	EN = 0;	
}

void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
//	__delay_ms(50);
	EN = 0;	
}
void uart_init()
{
	TRISC6 = 0; //TX
	TRISC7 = 1; //RX
	TXSTA = 0X20;
	RCSTA = 0X90;
	SPBRG = 31;
	TXIF = 0;
	RCIF = 0;
}
/*void uart_transmit()
{
	TRISC6 = 0;   //RC6/TX/CK
	TXSTA = 0X20;  //Transmit enable bit set = 1.
	SPBRG = 31;    //Badu rate gentrate 
	TXIF = 0;      //Transmit interrupt flage
}

void uart_recive()
{
	TRISC7 = 1;
	RCSTA = 0X90;
	SPBRG = 31;
	RCIF = 0;
}*/

void lcd_init()
{
	TRISB = 0X00;   
	TRISD = 0X00;
	__delay_ms(50);
	lcd_cmd(0x38); //data lingth,2 line
	lcd_cmd(0x0f); //display on,cur on,en blink
	lcd_cmd(0x0c); //display on,cur on,en blink
	lcd_cmd(0x02); //ret home
	lcd_cmd(0x06); //cur++
	lcd_cmd(0x80); //set DDRAM address
	__delay_ms(50);
	lcd_cmd(0x01); //clear display
}

int main()
{
	unsigned char RData;
	lcd_init();
	uart_init();
	while(1)
	{
		while(RCIF == 0);//		RData = RCREG;
        RData = RCREG;
		lcd_data(RData);
	}
}
/*	lcd_init();
	uart_recive();
	while(1)
	{
		while(RCIF == 0);
		RData = RCREG;
		lcd_data(RData);
	}*/