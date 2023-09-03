#include <STC32G.H>
#include "pwm.h"
#include <math.h>
#include "intrins.h"
#include "stdint.h"
#include <stdio.h>

bit B_1ms;          //1ms��־

unsigned int PWM1_Duty;
unsigned int PWM2_Duty;
unsigned int PWM3_Duty;
unsigned int PWM4_Duty;

 bit PWM1_Flag;
 bit PWM2_Flag;
 bit PWM3_Flag;
 bit PWM4_Flag;
 


////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////
void main()
{	
	
		EAXFR = 1;				// ʹ�ܷ���XFR
		CKCON = 0x00;			// �����ⲿ��������Ϊ���
		WTST = 0;  
	
		P1M0 = 0xff; P1M1 = 0x00;
	    P4M0 = 0xff; P4M1 = 0x00; 
	    P2M0 = 0x00; P2M1 = 0x00;
		P3M0 &= ~0xdf; P3M1 &= ~0xdf; 
	
		PWMA_Init();
		
	while(1)
	{
	
		PWM1_Duty=1;

		if(!PWM1_Flag)
		{
			PWM1_Duty++;
 			if(PWM1_Duty > PWM_PERIOD) PWM1_Flag = 1;
		}
		else
		{
			PWM1_Duty--;
			if(PWM1_Duty <= 0) PWM1_Flag = 0;
		}
		  UpdatePwm(); 
		

	}
}





