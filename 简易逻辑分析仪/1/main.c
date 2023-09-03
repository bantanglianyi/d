#include <STC32G.H>
#include "pwm.h"

unsigned int PWM1_Duty=100;//高点平的持续时间，用于改变占空比
void main()
{
	PWM_Init();
	UpdatePwm();
	while(1)
	{
		
	}
}