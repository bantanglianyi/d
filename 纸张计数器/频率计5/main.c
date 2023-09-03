#include <STC32G.H>
#include "oled.h"
#include <stdio.h>
#include "STC32G_PWM.h"
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
#define N 10000
#define key P7^0

u8 zp[50];
u16 b=500;
float f,f_1;
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
			f=(float)((((TH1_NOW<<8)+TL1_NOW)+(TF1_NOW*65535))*1.00145621805);
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


float filter3()
{
	float sum = 0;
	int count;
	for ( count=0;count<N;count++)
	{
		sum = sum+ f;
	}
	return (sum/N);
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
	PWM_init();
	while(1)
	{
		f_1=filter3();
		sprintf(zp,"%.3f",f_1);
		OLED_ShowString(2,2,zp,8);
		delay_ms(1000);
		
	}
}
