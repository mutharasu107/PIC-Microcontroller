#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1f74);

int main()
{
	TRISD0 = 1;//SWITCH	
    TRISB0 = 0;//LED
    RB0 = 0;//FIRST LED OFF
 	while(1)
	{
		if(RD0 == 0)
		{
		//	__delay_ms(100);
			if(RD0 == 0)
			{
				RB0 = 1;//LED ON 
				__delay_ms(100);//DELAY GIVE INPUT IN PORTB    
				RD0 = 0;//5 VOLTAGE GIVE IN PUT
			}
		}
	}
}