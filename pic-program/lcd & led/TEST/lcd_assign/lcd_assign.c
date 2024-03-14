#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG (0X1F74);

#define RS RC0
#define RW RC1
#define EN RC2

void lcd_cmd(unsigned )