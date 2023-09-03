#include <STC32G.H>
#include <stdio.h>
#include "oled.h"
#include "bmp.h"
//#include "STC32G_PWM.h"

unsigned char c[50];
float a=0;
void Timer0_Isr(void) interrupt 1
{
	a=(float)(((TL1*256)+TH1)/0.65535);
	TL1 = 0;				//设置定时初始值
	TH1 = 0;				//设置定时初始值
	TR1 = 1;
}

void Timer0_Init(void)		
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0;				//设置定时初始值
	TH0 = 0;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
}
void Timer1_Init(void)		
{
	
	TMOD &= 0x0F;			//设置定时器模式
	TMOD |= 0xD0;			//设置定时器模式
	TL1 = 0;				//设置定时初始值
	TH1 = 0;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
					//定时器1开始计时
}

	
void main()
{
	EA=1;
	P3M0 &= ~0xdf; P3M1 &= ~0xdf; 
	P2M0 = 0xff; P2M1 = 0x00; 
	P4M0 = 0XFF; P4M1 = 0X00;
	///////////////////////////
	XOSCCR=0XC8;
	while(XOSCCR&1);
	CLKDIV=0X00;
	CLKSEL=0X01;
	//////////////////////////
	EAXFR=1;
	CKCON=0X00;	
	WTST=0X00;
	/////////////////////////
	OLED_Init();
	Timer0_Init();
	Timer1_Init();
	
	//PWM_init();
    /////////////////////////	
	
//    P3M0 &= ~0x20; P3M1 |= 0x20; 
	
//	P0M0 = 0x00; P0M1 = 0x00; 
//    P1M0 = 0x00; P1M1 = 0x00; 
//    P2M0 = 0x00; P2M1 = 0x00; 
//    P5M0 = 0x00; P5M1 = 0x00; 
//    P6M0 = 0x00; P6M1 = 0x00; 
//	P7M0 = 0x00; P7M1 = 0x00; 
	///////////////////////////

	while(1)
	{
		sprintf(bug,"%.3f",a);
		OLED_ShowString(2,2,c,8);
		//delay_ms(1000);

	}
}