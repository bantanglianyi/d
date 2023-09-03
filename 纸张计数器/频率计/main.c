#include <STC32G.H>
#include <stdio.h>
#include "pwm.h"
#include "oled.h"
#include "bmp.h"
float c;
unsigned char dis_buf[50] = {0};
bit ssy = 0;
float TL0_NUM = 0,TH0_NUM = 0,TIME_NUM = 0;
void Timer0_Isr(void) interrupt 1
{	
//	c=(((TH1<<8)|TL1)/0.002);
//	c = TH1;
//	TH1=0;
//	TL1=0;
	

}

void Timer0_Init(void)		//2����@11.0592MHz
{
	AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0x9A;				//���ö�ʱ��ʼֵ
	TH0 = 0xA9;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0 = 1;				//ʹ�ܶ�ʱ��0�ж�
}

void ding1_Init()
{
	TMOD|=0X0F;
	TMOD&=0X50;
	TL1=0;
	TH1=0;
	TR1=1;
}

void INT0_() interrupt 0
{
	if( ssy == 0)
	{
		TR0 = 1;
		ssy = 1;
	}
	else if(  ssy == 1)
	{
		ssy = 0;
		TH0_NUM = TH0;
		TL0_NUM = TL0;
		TR0 = 0;
		TH0 = 0;
		TL0 = 0;
	}
	

}



void main()
{

	EAXFR=1;
	CKCON=0X00;
	WTST=0X00;
    P2M0=0XFF;P2M1=0X00;
    P3M0 &= ~0x04; P3M1 |= 0x04; 
	P4M0 = 0XFF; P4
	
	
	M1 = 0X00;
	IT0 = 1;
	EX0 = 1;
	//pwm_Init();
	OLED_Init();
	OLED_ColorTurn(0);
	OLED_DisplayTurn(0);

	EA=1;
	Timer0_Init();	
	ding1_Init();
	while(1)
	{
		
		c = (float)1/(((TH0_NUM*256 +TL0_NUM)*0.375/12.50785014145031)*0.000001);
		sprintf(dis_buf,"F:%.3f",c);
		OLED_ShowString(0,1,dis_buf,8);
//		OLED_ShowNum(0,4,c,16,16);

	}
}

