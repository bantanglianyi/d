#include <STC32G.H>
#include "pwm.h"
unsigned int PWM1_Duty;//�ߵ�ƽ�ĳ���ʱ�䣬���ڸı�ռ�ձ�
unsigned int PWM2_Duty;
unsigned int PWM3_Duty;
unsigned int PWM4_Duty;
void main()
{
	
	EAXFR = 1;				// ʹ�ܷ���XFR
	CKCON = 0x00;			// �����ⲿ��������Ϊ���
	WTST = 0;  
	
	PWM1_Duty=25;
		
	P6M0 = 0x00; 
	P6M1 = 0x00; 
	
	P6=0X05;
	
	PWMA_Init();
	UpdatePwm();
	
	IT0 = 1;      
	EX0 = 1;      //���ⲿ�ж�1
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

