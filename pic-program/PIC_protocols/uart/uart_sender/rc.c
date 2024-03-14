#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0x1F74);

#define RS RD5
#define RW RD6
#define EN RD7

void lcd_cmd(unsigned char cmd);
void lcd_dis(unsigned char data);
void lcd_init(void);
void uart_init(void);

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

void lcd_dis(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTB = data;
	__delay_ms(50);
	EN = 0;
	__delay_ms(50);
}	

void lcd_init()
{
	TRISB  = 0x00; 	// PORTB used out put bit
	TRISD5 = 0; 	// PORTD pin #5 out put pin
	TRISD6 = 0; 	// PORTD pin #6 out put pin
	TRISD7 = 0; 	// PORTD pin #7 out put pin
	__delay_ms(50);
	lcd_cmd(0x38);	// init 5x8, 2 line ret home
	lcd_cmd(0x0f);  // disp on, on_cur, en_blink
	lcd_cmd(0x0c);	// disp_on, en_cur, en_blink
	lcd_cmd(0x02);	// ret home
	lcd_cmd(0x06); 	// cur++
	lcd_cmd(0x80);	// set DDRAM address
	__delay_ms(50);
	lcd_cmd(0x01);	// clear display
}

void uart_init()
{
	TRISC6 = 0; 	// High for 25 pin RC6/Tx/CK
	TRISC7 = 1; 	// LOW for 26 pin RC7/Rx/DT
	TXSTA  = 0x20; 	// TX status & control Reg(add 98H)
	RCSTA  = 0x90; 	// RC status & control Reg(add 18H)
	SPBRG  = 31; 	// Badu rate set 9600 bit for second
	TXIF   = 0;		// TX interrupt flage bit
	RCIF   = 0; 	// RC interrupt flage bit
}

int main()
{
	unsigned char RData;
	lcd_init();
	uart_init();
	
	while(1)
	{
		while(RCIF == 0); 	// poll if RCIF is empty
		RData = RCREG;
		lcd_dis(RData); // display receive data on lcd 
	}
	while(1);	
}