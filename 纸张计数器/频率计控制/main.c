#include <STC32G.H>
#include "oled.h"
#include <stdio.h>
#include "pwm.h"
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
#define key P7^0
	u8 a=0;
u8 zp[50];
u16 b=500;
float f;
u16 TH1_NOW,TL1_NOW;
char c,TF1_NOW=0;
void Timer1_Init(void)		//2毫秒@24.000MHz  计数器
{
	TMOD &= 0x0F;			//设置定时器模式
	TMOD |= 0x50;			//设置定时器模式
	TL1 = 0;				//设置定时初始值
	TH1 = 0;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器0开始计时
	ET1 = 1;				//使能定时器1中断
	
}
void Timer0_Isr(void) interrupt 1
{
		if(b--==0)
		{
			TF1_NOW=c;
			c=0;
			b=500;
			TH1_NOW=TH1;
			TL1_NOW=TL1;
			TH1=0;
			TL1=0;	
			f=(float)((((TH1_NOW<<8)+TL1_NOW)+(TF1_NOW*65535))/0.99873);
		}
		
		
}
void Timer1_Isr(void) interrupt 3
{
	c++;
}
void Timer0_Init(void)		//2毫秒@24.000MHz
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x80;				//设置定时初始值
	TH0 = 0x44;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
}

float PIDPro(float Sample, float Position)
{
	ErrPres=Position-Sample; 
	PPro=Kp*ErrPres;
	total_Pias+=ErrPres;
	Pias=total_Pias*Ki;
	PDif=Kd*(ErrPrev-ErrPres);
	ErrPrev=ErrPres;
	VolOut=VolOut+PPro+PDif+Pias;
//	if(VolOut>5000)VolOut=5000;
//	if(VolOut<-5000)VolOut=-5000;
	return VolOut;
}

void main()
{
	EA=1;

	XOSCCR=0xc4;
	while(XOSCCR&1);
	CLKDIV=0X00;
	CLKSEL=0X01;
	
	EAXFR=1;
	CKCON=0X00;
	WTST=0X00;

	P3M0 &= ~0xdf; P3M1 &= ~0xdf; 
	P2M0 = 0xff; P2M1 = 0x00; 
	P4M0 = 0XFF; P4M1 = 0X00;
	OLED_Init();
	Timer0_Init();
	Timer1_Init();
	PWMA_Init();
	while(1)
	{

		sprintf(zp,"%.3f",f);
		OLED_ShowString(2,2,zp,8);
		delay_ms(1000);
		
	}
}
