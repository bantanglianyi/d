#include <STC32G.H>
#include "DMP.h"
#include "oled.h"
#include "MPU6050.H"
#include "pwm.h"
#include <math.h>
#include "intrins.h"
#include "stdint.h"
#include <stdio.h>
#include "UART.h"


char x_angle[50];
char y_angle[50];
char PD_main[50];



float Pitch, Roll;
float  Out,ErrPres,Pias,ErrPres_formerly,ErrPres_lastseen,pd;
float ErrPrev=0;


unsigned int PWM1_Duty;
unsigned int PWM2_Duty;
unsigned int PWM3_Duty;
unsigned int PWM4_Duty;

 
///////////////////////����ʽpid
float PIDPro(float Sample, float Position)
{
	float Kp =0.04;
	float Ki =0;
	float Kd =0.009;
	ErrPres=(Position-Sample);
	Pias+=ErrPres;//ÿ��������ֵ
	Out=((ErrPres_formerly-ErrPres)*Kp)+(Pias*Ki)+((ErrPres-2*ErrPres_formerly+	ErrPres_lastseen)*Kd);
	//���=���ϴ����-�����*p  +   ������ֵ*i   +    �����-2*�ϴ����+���ϴ���*d
	ErrPres_formerly=ErrPres;//�ϴ����
	ErrPres_lastseen=ErrPres_formerly;//���ϴ����
	if(Out>1000)Out=1000;
	if(Out<0)Out=0;
	return Out;
}

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
	
		OLED_Init();
		MPU6050_DMP_Init();
		PWMA_Init();
		UART_init(1,9600,0);
		
	while(1)
	{
	
		PWM1_Duty=(pd);
		UpdatePwm();
		Pitch = asin(-2 * Q[1] * Q[3] + 2 * Q[0]* Q[2])* 57.3;	// pitch
		Roll  = atan2(2 * Q[2] * Q[3] + 2 * Q[0] * Q[1], -2 * Q[1] * Q[1] - 2 * Q[2]* Q[2] + 1)* 57.3;	// roll
		//Yaw   = atan2(2 * (Q[1] * Q[2] + Q[0] * Q[3]), Q[0] * Q[0] + Q[1] * Q[1] - Q[2] * Q[2] - Q[3] * Q[3]) * 57.3;	//yaw
	
		MPU6050_Refresh_DMP();
		sprintf(x_angle,"%.3f",Pitch);
		OLED_ShowString(0,0,x_angle,8);
		sprintf(y_angle,"%.3f",Roll);
		OLED_ShowString(0,1,y_angle,8);
		pd=PIDPro(Roll,110-5);
		sprintf(PD_main,"%.3f\n",pd);
		OLED_ShowString(0,2,PD_main,8);
		UART_Send_string(1,PD_main);
		
		

	}
}






