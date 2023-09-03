#include <STC32G.H>
#include "oled.h"
#include <stdio.h>
#include "USART.h"
#include <intrins.h>

bit INT0_judge=0;
char count=0;
char transfer;
unsigned char array_signal[8]={0};
char i=0;
char xstart=3;
unsigned char interim;
unsigned char interim_array_signal;


void Delay2us()		//@11.0592MHz
{
		unsigned long edata g;

	_nop_();
	_nop_();
	_nop_();
	_nop_();
	g = 4UL;
	while (g) g--;
}

void delay(unsigned int ns)
{
	while(ns--);
}
void signaldisplay(unsigned char ax,unsigned char ay,unsigned char tall,unsigned char wide,unsigned char gap,unsigned int continue_time)
{
		Draw_Hline(0,ay,(ax-1),continue_time);
		Draw_Vline(ax,(ay-tall),ay,continue_time);
		Draw_Hline((ax+1),(ay-tall),(ax+wide),continue_time);
		Draw_Vline((ax+wide+1),(ay-tall),ay,continue_time);
		Draw_Hline((ax+wide+2),ay,(ax+wide+gap),continue_time);
	
		Draw_Vline((ax+wide+1+gap),(ay-tall),ay,continue_time);
		Draw_Hline((ax+wide+2+gap),(ay-tall),(ax+wide+gap+wide),continue_time);
		Draw_Vline((ax+wide+gap+wide+1),(ay-tall),ay,continue_time);
		Draw_Hline((ax+wide+gap+wide+2),ay,128,continue_time);
}
	
		

int judge(unsigned char judge_price)
{
	char judge_price1=0;
		if(judge_price==5)judge_price1=0;
	else 
		if(judge_price==10)judge_price1=15;
	else 
		if(judge_price==20)judge_price1=30;
	else 
		if(judge_price==40)judge_price1=45;
	else 
		if(judge_price==80)judge_price1=60;
	else 
		if(judge_price==160)judge_price1=75;
	else 
		if(judge_price==65)judge_price1=90;
	else 
		if(judge_price==130)judge_price1=105;
	return judge_price1;
}
void judge_1()
{

			switch(count)
			{
				case 0:
					interim_array_signal=array_signal[count];
					interim=judge(interim_array_signal);
					signaldisplay((xstart+interim),5,5,15,15,1);
				break;
				case 1:
						interim_array_signal=array_signal[count];
					interim=judge(interim_array_signal);
					signaldisplay((xstart+interim),13,5,15,15,1);
				break;
				case 2:
						interim_array_signal=array_signal[count];
					interim=judge(interim_array_signal);
					signaldisplay((xstart+interim),21,5,15,15,1);
				break;
				case 3:
						interim_array_signal=array_signal[count];
					interim=judge(interim_array_signal);
					signaldisplay((xstart+interim),29,5,15,15,1);
				break;
				case 4:
						interim_array_signal=array_signal[count];
					interim=judge(interim_array_signal);
					signaldisplay((xstart+interim),37,5,15,15,1);
				break;
				case 5:
						interim_array_signal=array_signal[count];
					interim=judge(interim_array_signal);
					signaldisplay((xstart+interim),45,5,15,15,1);
				break;
				case 6:
						interim_array_signal=array_signal[count];
					interim=judge(interim_array_signal);
					signaldisplay((xstart+interim),53,5,15,15,1);
				break;
				case 7:
						interim_array_signal=array_signal[count];
					interim=judge(interim_array_signal);
					signaldisplay((xstart+interim),61,5,15,15,1);
				break;
				
			}
}
void main()
{ 
	EAXFR=1;
	CKCON=0X00;
	WTST=0X00;
	
	IT0 = 1;      
	EX0 = 1;      //打开外部中断1
	EA=0;
	
	P4M0 = 0xff;
	P4M1 = 0x00;
	//P7M0 = 0x00; P7M1 = 0x00; 
	P6M0 = 0x00; P6M1 = 0x00; 


	OLED_Init();
	UartInit();	
	

	while(1)
	{
		if(P70==0)
		{
			delay(4000);
			while(P70==0);
			delay(4000);
			EA=1;
			while(EA==1);
			for(count=0;count<8;count++)
			{
				judge_1();
			}
		}
		if(P71==0)
		{
			delay(4000);
			while(P71==0);
			xstart++;
			for(count=0;count<8;count++)
			{
				judge_1();
			}
		}
		if(P76==0)
		{
			delay(4000);
			while(P76==0);
			xstart--;
			for(count=0;count<8;count++)
			{
				judge_1();
	
			}
		}		
	}	  
}

void INT0_Routine() interrupt 0
{
	
	Delay2us();
	array_signal[i]=P6;
	i++;
	if(i>=8)
	{
		i=0;
		EA=0;
	}
	
}

