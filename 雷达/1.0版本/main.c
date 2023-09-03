#include <STC32G.H>
#include "hc_sr04.h"
#include "oled.h"
#include <stdio.h>
float distance=0;
unsigned int yaxle=0;
char ultrasonic_data[50];
unsigned int j;
void Delay50ms();		//@12.000MHz
char data_transition(char ultrasonic_input);
void main()
{
	
	EAXFR = 1; 								// 使能访问 XFR
	CKCON = 0x00; 							// 设置外部数据总线速度为最快
	WTST = 0x00;
	
	P0M0 = 0x00; P0M1 = 0x00; 
    P1M0 = 0x00; P1M1 = 0x00; 
    P2M0 = 0x00; P2M1 = 0x00; 
    P3M0 = 0x00; P3M1 = 0x00; 
    P4M0 = 0x1f; P4M1 = 0x00; 
    P5M0 = 0x00; P5M1 = 0x00; 
    P6M0 = 0x00; P6M1 = 0x00; 
    P7M0 = 0x00; P7M1 = 0x00; 
	OLED_Init();
	Timer0_Init();
	while(1)
	{
		for(j=0;j<128;j++)
		{	
			distance=HC_SR04_Loop();
			yaxle=data_transition(distance);
			Setpos(j,(yaxle));
			Delay50ms();
		}
		OLED_Clear();
	
		
//		sprintf(ultrasonic_data,"%.3f",distance);
//		OLED_ShowString(0,0,ultrasonic_data,8);
	}
}

void Delay50ms()		//@12.000MHz
{
	unsigned long edata i;

	_nop_();
	_nop_();
	i = 149998UL;
	while (i) i--;
}

char data_transition(char ultrasonic_input)
{
	char Computed_return_value;
		Computed_return_value=(ultrasonic_input );
	return Computed_return_value;
}