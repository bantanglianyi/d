#include <STC32G.H>
#include "MPU6050.H"
#include "DMP.h"
#include "stdint.h"
#include <stdio.h>
#include "intrins.h"
#include <math.h>
#include "usart.h"
#include "oled.h"
float Pitch, Roll, Yaw;
char x_angle[50];
void main()
{	
	P4M0 = 0xff; P4M1 = 0x00; 
	P2M0 = 0x00; P2M1 = 0x00;
	
	OLED_Init();
	MPU6050_DMP_Init();
	UartInit();
	
	while(1)
	{
		
		EAXFR = 1;				// ʹ�ܷ���XFR
		CKCON = 0x00;			// �����ⲿ��������Ϊ���
		WTST = 0; 
		
		
		Pitch = asin(-2 * Q[1] * Q[3] + 2 * Q[0]* Q[2])* 57.3;	// pitch
		//Roll  = atan2(2 * Q[2] * Q[3] + 2 * Q[0] * Q[1], -2 * Q[1] * Q[1] - 2 * Q[2]* Q[2] + 1)* 57.3;	// roll
		//Yaw   = atan2(2 * (Q[1] * Q[2] + Q[0] * Q[3]), Q[0] * Q[0] + Q[1] * Q[1] - Q[2] * Q[2] - Q[3] * Q[3]) * 57.3;	//yaw
		MPU6050_Refresh_DMP();
		sprintf(x_angle,"%.3f",Pitch);
		OLED_ShowString(0,0,x_angle,8);
		
		
		
	}
}