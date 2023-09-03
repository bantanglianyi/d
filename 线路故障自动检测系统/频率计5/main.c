#include <STC32G.H>
#include "oled.h"
#include <stdio.h>
#include "ADC.h"
#include "key_multi.h"
#include "USART.h"
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
char a=0;
u16 b=500;
double f=0;
u16 TH1_NOW,TL1_NOW;
char c,TF1_NOW=0;
float ADC_1,ADC_15;
float ADC_out_1;
u8 Key1_nums,Key2_nums,Key3_nums,Key4_nums;		//KEY1双击次数，KEY2双击次数，KEY3双击次数，KEY4双击次数
u8 keyvalue;		//键值
char count_mode=1;
double f_1=0;
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
	PT1H=1;
	PT1=1;
}
void Delay100us()		//@11.0592MHz
{
	unsigned long edata d;

	_nop_();
	d = 275UL;
	while (d) d--;
}
void display_autograph()
{
		OLED_ShowChinese(0,0,0,16);
		OLED_ShowChinese(16,0,1,16);
		OLED_ShowChinese(32,0,2,16);
		OLED_ShowChinese(48,0,3,16);
		OLED_ShowChinese(64,0,4,16);
		OLED_ShowChinese(80,0,5,16);
		OLED_ShowChinese(96,0,6,16);
		OLED_ShowChinese(112,0,7,16);
		OLED_ShowChinese(0,2,8,16);
		OLED_ShowChinese(16,2,9,16);
}
void ADC_AD637()
{
		ADC_15=Get_ADC12bitResult(15);
		ADC_1=Get_ADC12bitResult(1);
		ADC_out_1=(float)(1.18301*ADC_1/ADC_15);
		Delay100us();
}
void display_judge()
{	
					ADC_AD637();
					printf("%f\r\n",ADC_out_1);
					f_1=f;
					OLED_ShowChinese(0,0,12,16);//故
					OLED_ShowChinese(16,0,13,16);//障
					OLED_ShowChinese(32,0,6,16);//检
					OLED_ShowChinese(48,0,7,16);//测
					if(P24 == 0)
					{
						
						delay_ms(20);
						while(P24 == 0);
						delay_ms(20);
					OLED_Clear();						
					if(f_1>53070&&f_1<54000)
					{
						a=1;
						
					}		
					else if(f_1>453000&&f_1<500000)
					{
						a=2;
					}
					else if(f_1>101500&&f_1<103000)
					{
						a =3;
					}
					else if(f_1>58500&&f_1<59700)
					{
						a=4;
					}
					else if(f_1>610000)
					{
						a=5;
					}
					else if(f_1>87700&&f_1<88800)
					{
						a=6;
					}
					else if(f_1>84200&&f_1<86300)
					{
						a=7;
					}
//					else if(f_1>58500&&f_1<58600)
//					{
//						a=8;
//					}
					
				}
					switch(a)
					{
						case 1:
							OLED_ShowChinese(32,2,16,16);//没
							OLED_ShowChinese(48,2,17,16);//有
							OLED_ShowChinese(64,2,12,16);//故
							OLED_ShowChinese(80,2,13,16);//障
						break;
						case 2:
							OLED_ShowString(16,2,"L1",16);
							OLED_ShowChinese(32,2,10,16);//开
							OLED_ShowChinese(48,2,11,16);//路
						break;
						case 3:
							OLED_ShowString(16,2,"L2",16);
							OLED_ShowChinese(32,2,10,16);//开
							OLED_ShowChinese(48,2,11,16);//路
						break;
						case 4:
							OLED_ShowString(16,2,"L3",16);
							OLED_ShowChinese(32,2,10,16);//开
							OLED_ShowChinese(48,2,11,16);//路
						break;
						case 5:
							OLED_ShowString(16,2,"C1",16);
							OLED_ShowChinese(32,2,10,16);//开
							OLED_ShowChinese(48,2,11,16);//路
						break;
						case 6:
							OLED_ShowString(16,2,"C2",16);
							OLED_ShowChinese(32,2,10,16);//开
							OLED_ShowChinese(48,2,11,16);//路
						break;
						case 7:
							OLED_ShowString(16,2,"C3",16);
							OLED_ShowChinese(32,2,10,16);//开
							OLED_ShowChinese(48,2,11,16);//路
						break;
						case 8:
							OLED_ShowString(16,2,"C4",16);
							OLED_ShowChinese(32,2,10,16);//开
							OLED_ShowChinese(48,2,11,16);//路	
						break;
						
					}
			
					
//		sprintf(zp,"%.3f",f_1);
 		
		//OLED_ShowString(2,2,zp,8);
		//delay_ms(1000);	
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

	P3M0 = 0x00; P3M1 = 0x20; 
	P2M0 = 0xff; P2M1 = 0x00; 
	P4M0 = 0XFF; P4M1 = 0X00;
	OLED_Init();
	Timer0_Init();
	Timer1_Init();
	UartInit();
	ADC_init();
	while(1)
	{
		switch(count_mode)
		{
			case 0:display_autograph();break;
			case 1:display_judge();break;
		}
		if(P23 == 0)
		{
            delay_ms(20); 
			while(P23 == 0)
			delay_ms(20);	
			count_mode++;
			OLED_Clear();
			if(count_mode>=2)
			{
				count_mode=0;
			}
		}				
	}
}
