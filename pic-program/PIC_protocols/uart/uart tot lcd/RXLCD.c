//Getting data from RX same data print in lcd.

#include <htc.h>
#define _XTAL_FREQ 20000000

#define RS RD5
#define RW RD6
#define EN RD7

void lcd_cmd(unsigned char cmd);
void lcd_disp(unsigned char data);

void uart_init(void);
void lcd_init();

void lcd_cmd(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB = cmd;
	__delay_ms(50);
	EN = 0;
	__delay_ms(50);
}

void lcd_disp(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
	__delay_ms(50);
	EN = 0;
	__delay_ms(50);
}

void uart_init()
{
	TRISC6 = 0;  //Low 26 pin RC7/RX/DT.
	TRISC7 = 1;  //High 25 pin RC6/TX/CK.
	TXSTA = 0X20;//b5 TXEN=1.
	RCSTA = 0X90;//b7 SPEN =1,b4 CREN =1.
	SPBRG = 31;  //Badu rate gentrate(9600).
	TXIF = 0;    //Transmitt interrupt flage.
	RCIF = 0;    //Reciver interrupt flage.
} 

void lcd_init()
{
	TRISB = 0X00;  //PORT-B used out put bit
	TRISD5 = 0;    //PORT-D pin #5 out put pin
	TRISD6 = 0;    //PORT-D pin #6 out put pin
	TRISD7 = 0;    //PORT-D pin #7 out put pin
	__delay_ms(50);
	lcd_cmd(0x38); //init 5x8,2 line ret home
	lcd_cmd(0x0f); //disp on,on-cur,en-blink
	lcd_cmd(0x0c); //disp on,en-cur,en-blink
	lcd_cmd(0x02); //ret home
	lcd_cmd(0x06); //cur++
	lcd_cmd(0x80); //set DDRAM
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
		while(RCIF == 0);//Poll if RCIF IS Empty
		RData = RCREG;
		lcd_disp(RData);//display receive data on lcd.
	}
}