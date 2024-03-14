#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

//function declaration

void init_i2c();

void start();
void stop();
void wait();
void  i2c_send(char data);
char  i2c_recv(char );
unsigned uart_rx(void);
void uart_print(unsigned char *s);
void uart_tx(unsigned char data);
void uart_init();

int main()
{
	int UT;
	char a,b,c;
	int val = 0x2E; //temperature value
	TRISC = 0x00;
	init_i2c();
	
	//funtion call
	uart_init();
	
	wait();
	start();
	i2c_send(0xEE); //pressure sensor device addresss now write
	i2c_send(0xF4); //presure register address
	i2c_send(val);
	stop();
	
    __delay_ms(3000);	
	start();
	i2c_send(0xEE);  //pressure sensor device address now write
	i2c_send(0xF6);  //temperature or presure data register address
	stop();
	
	start();
	i2c_send(0xEF); //pressure sensor device address now read the value from device
	a = i2c_recv(0); //wrtie value
	b = i2c_recv(0); //write value
	c = i2c_recv(1); //write value
	stop();
	
	UT = a<<8 + b;
	uart_print(UT);
	
	while(1);
}

//function definiton

void init_i2c(){
	
	TRISC3 = 0; /* enable Serial clock (SCL) */
	TRISC4 = 0; /* enable Serial data (SDA) */
	SSPCON = 0x28; /*I2C Master mode*/
	SSPSTAT = 0X80; /*Slew Rate Control bit Slew rate control disabled for standard speed mode (100 kHz and 1 MHz)*/
	SSPADD = 49; /*address register normal speed 100KHz SSPADD+1 = fosc/4*(100KHz)*/
}

void wait(){
	while(!SSPIF); //interrupt flage set
	SSPIF =0; //interrupt flage clear

}

void start(){

	SEN = 1;//Start Condition Enabled/Stretch Enabled bit
	wait();
}
void stop(){
	PEN = 1; //Stop Condition Enable bit (Master mode only)
	wait();
}

void  i2c_send(char data){
	SSPBUF=data;//Synchronous Serial Port Buffer Register
	wait();
}

char  i2c_recv(char ack){
	char ret =0;

    RCEN=1; //Receive Enable bit (Master mode only)
    wait();
    ret = SSPBUF;
    ACKDT = ack; /*acknowledge data bit(master receive mode only)*/
    ACKEN = 1;/*acknowledge sequnce enable bit (master receive mode only)*/
    while(ACKEN==1);
    return ret;
}

void uart_tx(unsigned char data)
{
	TXREG=data; /*transmitter register*/
	while(!TXIF); /*transmitter interrupt flage bit set*/
	TXIF=0; /*transmitter interrrupt flage bit clear*/
}

unsigned uart_rx(void)
{
	while(!RCIF); /*receive interrupt flage bit set*/
	RCIF=0; /*receive interrupt flage bit clear*/
	return RCREG; /*return to receiver register*/
}

void uart_init()
{

	TRISC6=0; /*UART transmitter*/
	TRISC7=1; /*UART receiver*/
	TXSTA=0X20; /*transmit enable bit*/
	RCSTA=0X90; /*serial port enable bit, continuous receive enable bit*/
	SPBRG=31; /*badu rate*/
	TXIF=0; /*transmit interrupt flage clear*/
	RCIF=0; /*receiver interrupt flage clear*/
}

void uart_print(unsigned char *s)
{
	while(*s)
	{
		uart_tx(*s++);
	}
}