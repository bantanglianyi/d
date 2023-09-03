#include <STC32G.H>
#include "pwm.h"
#define u8 unsigned char
#define u16 unsigned int
unsigned int PWM1_Duty=25;//高点平的持续时间，用于改变占空比
unsigned int PWM2_Duty;
unsigned int PWM3_Duty;
unsigned int PWM4_Duty;
//bit sine_flag = 0;
//u8 sine_time = 0;
//u16 sine_receive = 0;
//u8 sine_wave[100]={ 0x7F,0x87,0x8F,0x97,0x9F,0xA6,0xAE,0xB5,0xBC,0xC3,0xCA,0xD0,0xD6,0xDC,0xE1,0xE6
//,0xEB,0xEF,0xF2,0xF6,0xF8,0xFA,0xFC,0xFD,0xFE,0xFE,0xFE,0xFD,0xFC,0xFA,0xF8,0xF6
//,0xF2,0xEF,0xEB,0xE6,0xE1,0xDC,0xD6,0xD0,0xCA,0xC3,0xBC,0xB5,0xAE,0xA6,0x9F,0x97
//,0x8F,0x87,0x7F,0x77,0x6F,0x67,0x5F,0x58,0x50,0x49,0x42,0x3B,0x34,0x2E,0x28,0x22
//,0x1D,0x18,0x13,0x0F,0x0C,0x08,0x06,0x04,0x02,0x01,0x00,0x00,0x00,0x01,0x02,0x04
//,0x06,0x08,0x0C,0x0F,0x13,0x18,0x1D,0x22,0x28,0x2E,0x34,0x3B,0x42,0x49,0x50,0x58
//,0x5F,0x67,0x6F,0x77};

//u16 i = 0;
//void Timer0_Isr() interrupt 1
//{
//	for(i=0;i<99;i++)
//	{
//		P6 = sine_wave[i];
//	}
//}
  
//void Timer0_Init(void)		
//{
//	AUXR |= 0x80;			//定时器时钟1T模式
//	TMOD &= 0xF0;			//设置定时器模式
//	TL0 = 0xFA;				//设置定时初始值
//	TH0 = 0xFF;				//设置定时初始值
//	TF0 = 0;				//清除TF0标志
//	TR0 = 1;				//定时器0开始计时
//	ET0 = 1;				//使能定时器0中断
//	EA = 1;
//}

//void IO()
//{
//	P6M0 = 0XFF;
//	P6M1 = 0X00;
//}
	
void main()
{
	EAXFR = 1;
	CKCON = 0X00;
	WTST = 0X00;
	
//	IO();
//	Timer0_Init();
	P0M0 = 0X00;
	P0M1 = 0X00;
	PWMA_Init();
	UpdatePwm();
	while(1)
	{
		if(P07==0)
		{
				PWMA_BKR=0x80;
		}
		else
		{
				PWMA_BKR=0x00;
		}
	}
}
