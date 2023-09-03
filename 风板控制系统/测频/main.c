#include <STC32G.H>
#include "oled.h"
#include "config.h"
#include <stdio.h>
#include <USART.h>

u16 cap;											// �����ֵ
u32  cap_new;							// ��ǰ�������ֵ
u16 cap_old;									// �ϴβ������ֵ
float  freq;								// ����Ƶ��
u8 segdelay;									// �������ʱ����
u8 capnums;		                                //�������
u8 count=250;

char count_oled[50];

void pwm_init()
{
//--------------------------PWMA����-����������----------------------------------	
	PWMA_ENO = 0x00;						// �رղ���/���ͨ��
	PWMA_CCER1 = 0x00;					// �ر�ͨ��
	PWMA_CCMR1 = 0x01; 					// ͨ��ģʽ����Ϊ����
	PWMA_SMCR = 0x56;					  // ����1������ģʽ
	PWMA_CCER1 = 0x01;					// ʹ�ܲ���/�Ƚ�ͨ��1
	PWMA_CCER1 |= 0x00;					// ���ò���/�Ƚ�ͨ��1�����ز���
	PWMA_CCER1 |= 0x20;					// ���ò���/�Ƚ�ͨ��1�½��ز���
	
	PWMA_IER = 0x02; 						// ʹ�ܲ����ж�
	PWMA_CR1 = 0x01; 						// ����PWMA��ʱ��
	
//------------PWMB����-PWM5(P2.0)���һ·PWM��500Hz��ռ�ձȣ�50%-------------------
//	PWMB_PSCRH = (u16)(PWMB_PSC >> 8);
//	PWMB_PSCRL = (u16)(PWMB_PSC);	// Ԥ��Ƶ
//	
//	PWMB_CCER1 = 0x00;					// �ر�ͨ��
//	PWMB_CCMR1 = 0x68; 					// ͨ��ģʽ����Ϊ�����PWMģʽ1
//	PWMB_CCER1 = 0x05;					// ʹ�ܲ���/�Ƚ�ͨ��1��ʹ��CCRԤװ��

//	PWMB_CCR5H = (u16)(PWMB_PERIOD_500 >> 2 >> 8);
//	PWMB_CCR5L = (u16)(PWMB_PERIOD_500 >> 2);	// ����ռ�ձ�50%
//	
//	PWMB_ARRH = (u16)(PWMB_PERIOD_500 >> 8);
//	PWMB_ARRL = (u16)(PWMB_PERIOD_500);	// ��������
//	
//	PWMB_ENO = 0x01;						// ʹ��PWM5���
//	PWMB_BKR = 0x80;						// ʹ��PWMB�����
//	PWMB_CR1 |= 0x01; 					// ʹ��PWMB������
}


void Timer0_Init(void)		//2����@12.000MHz
{
	AUXR &= 0x7F;			//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0x30;				//���ö�ʱ��ʼֵ
	TH0 = 0xF8;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0 = 1;				//ʹ�ܶ�ʱ��0�ж�
}

void main()
{
	EAXFR = 1; 									// ʹ�ܷ��� XFR
	CKCON = 0x00; 							// �����ⲿ���������ٶ�Ϊ���
	WTST = 0x00; 	// ���ó������ȴ���������ֵΪ 0 �ɽ� CPU ִ�г�����ٶ�����Ϊ���
	
	EA=1;
	P4M0=0XFF;
	P4M1=0X00;
	
	OLED_Init();
	pwm_init();
	Timer0_Init();		//1����@11.0592MHz

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
		freq = (float)((MAIN_Fosc / cap)/0.5);	// ���㷽��Ƶ�ʣ��˴�+1��Ϊ�˼��ϱ�������С������
	}
}
void PWM_ISR() interrupt 26
{
	if (PWMA_SR1 & 0X02)				// �������жϱ�־��1
	{	
		PWMA_SR1 &= ~0X02;				// ���㲶���жϱ�־
		cap_old = cap_new;				// ���µ�ǰ����ֵ
		cap_new =(PWMA_CCR1H << 8) + PWMA_CCR1L;	// ��ȡ����ֵ��8λ,���ϲ�����cap_new
		cap = cap_new - cap_old;		// �������β����ֵ
		capnums++;
		//if(capnums == 2) PWMA_CCER1 = 0x00;	//�رղ���/�Ƚ�ͨ��1
	}
}


