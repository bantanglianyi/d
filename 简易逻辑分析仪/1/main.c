#include <STC32G.H>
#include "pwm.h"

unsigned int PWM1_Duty=100;//�ߵ�ƽ�ĳ���ʱ�䣬���ڸı�ռ�ձ�
void main()
{
	PWM_Init();
	UpdatePwm();
	while(1)
	{
		
	}
}