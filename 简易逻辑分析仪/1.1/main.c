#include <STC32G.H>
#include "pwm.h"
unsigned int PWM1_Duty;//高点平的持续时间，用于改变占空比
unsigned int PWM2_Duty;
unsigned int PWM3_Duty;
unsigned int PWM4_Duty;
void main()
{
	
	EAXFR = 1;				// 使能访问XFR
	CKCON = 0x00;			// 设置外部数据总线为最快
	WTST = 0;  
	
	PWM1_Duty=25;
		
	P6M0 = 0x00; 
	P6M1 = 0x00; 
	
	P6=0X05;
	
	PWMA_Init();
	UpdatePwm();
	
	IT0 = 1;      
	EX0 = 1;      //打开外部中断1
	EA=1;
	
	
	//UpdatePwm();
	while(1)
	{
		
		
	}
}

void INT0_Routine() interrupt 0
{
		P6=_cror_(P6,1);
}

