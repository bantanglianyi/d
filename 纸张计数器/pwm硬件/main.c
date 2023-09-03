#include <STC32G.H>
#include "pwm.h"
#include "oled.h"

void main()
{
	
	//EAXFR=1;
	//CKCON=0X00;
	//WTST=0X00;
    P3M0=0XFF;P3M1=0X00;
		//pwm_Init();
	OLED_Init();
	
	while(1)
	{
		OLED_ShowChinese(0,2,0,16);
		OLED_ShowChinese(18,2,1,16);

		delay_ms(1);
		
	}
}