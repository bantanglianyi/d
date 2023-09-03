#include <STC32G.H>
#include "oled.h"
#include "config.h"
#include <stdio.h>
#include <USART.h>

u16 cap;											// 捕获差值
u32  cap_new;							// 当前捕获计数值
u16 cap_old;									// 上次捕获计数值
float  freq;								// 方波频率
u8 segdelay;									// 数码管延时计数
u8 capnums;		                                //捕获次数
u8 count=250;

char count_oled[50];

void pwm_init()
{
//--------------------------PWMA设置-捕获上升沿----------------------------------	
	PWMA_ENO = 0x00;						// 关闭捕获/输出通道
	PWMA_CCER1 = 0x00;					// 关闭通道
	PWMA_CCMR1 = 0x01; 					// 通道模式配置为输入
	PWMA_SMCR = 0x56;					  // 输入1，触发模式
	PWMA_CCER1 = 0x01;					// 使能捕获/比较通道1
	PWMA_CCER1 |= 0x00;					// 设置捕获/比较通道1上升沿捕获
	PWMA_CCER1 |= 0x20;					// 设置捕获/比较通道1下降沿捕获
	
	PWMA_IER = 0x02; 						// 使能捕获中断
	PWMA_CR1 = 0x01; 						// 启动PWMA定时器
	
//------------PWMB设置-PWM5(P2.0)输出一路PWM：500Hz，占空比：50%-------------------
//	PWMB_PSCRH = (u16)(PWMB_PSC >> 8);
//	PWMB_PSCRL = (u16)(PWMB_PSC);	// 预分频
//	
//	PWMB_CCER1 = 0x00;					// 关闭通道
//	PWMB_CCMR1 = 0x68; 					// 通道模式配置为输出，PWM模式1
//	PWMB_CCER1 = 0x05;					// 使能捕获/比较通道1，使能CCR预装载

//	PWMB_CCR5H = (u16)(PWMB_PERIOD_500 >> 2 >> 8);
//	PWMB_CCR5L = (u16)(PWMB_PERIOD_500 >> 2);	// 设置占空比50%
//	
//	PWMB_ARRH = (u16)(PWMB_PERIOD_500 >> 8);
//	PWMB_ARRL = (u16)(PWMB_PERIOD_500);	// 设置周期
//	
//	PWMB_ENO = 0x01;						// 使能PWM5输出
//	PWMB_BKR = 0x80;						// 使能PWMB主输出
//	PWMB_CR1 |= 0x01; 					// 使能PWMB计数器
}


void Timer0_Init(void)		//2毫秒@12.000MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x30;				//设置定时初始值
	TH0 = 0xF8;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0 = 1;				//使能定时器0中断
}

void main()
{
	EAXFR = 1; 									// 使能访问 XFR
	CKCON = 0x00; 							// 设置外部数据总线速度为最快
	WTST = 0x00; 	// 设置程序代码等待参数，赋值为 0 可将 CPU 执行程序的速度设置为最快
	
	EA=1;
	P4M0=0XFF;
	P4M1=0X00;
	
	OLED_Init();
	pwm_init();
	Timer0_Init();		//1毫秒@11.0592MHz

	while(1)
	{
		
		sprintf(count_oled,"%d\n",freq);
		OLED_ShowNum(1 ,1,freq,8,8);
		
	
	}
}
void Timer0_Isr(void) interrupt 1
{
	if(count--==0)
	{
		count=250;
		freq = (float)((MAIN_Fosc / cap)/0.5);	// 计算方波频率，此处+1是为了加上被舍弃的小数部分
	}
}
void PWM_ISR() interrupt 26
{
	if (PWMA_SR1 & 0X02)				// 当捕获中断标志置1
	{	
		PWMA_SR1 &= ~0X02;				// 清零捕获中断标志
		cap_old = cap_new;				// 更新当前捕获值
		cap_new =(PWMA_CCR1H << 8) + PWMA_CCR1L;	// 读取计数值低8位,并合并存入cap_new
		cap = cap_new - cap_old;		// 计算两次捕获差值
		capnums++;
		//if(capnums == 2) PWMA_CCER1 = 0x00;	//关闭捕获/比较通道1
	}
}


