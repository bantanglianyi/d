#include <STC32G.H>
#include "oled.H"
#include "ADC.h"
#include <stdio.h>
#include "USART.h"
#define N 100
float ADC_1,ADC_15;
float ADC_out_1;
float ADC_out_filter;
unsigned int value_buf[N];

void Delay10us();
void Delay100us();		//@11.0592MHz
float filter3();

void main()
{
//	P4M0 = 0xff; 
//	P4M1 = 0x00; 
	OLED_Init();
	ADC_init();
	UartInit();
	while(1)
	{
		ADC_15=Get_ADC12bitResult(15);
		ADC_1=Get_ADC12bitResult(1);
		ADC_out_1=(float)(1.18301*ADC_1/ADC_15);
		ADC_out_filter=filter3();
		printf("%.4f\n",ADC_out_filter);
		Delay100us();
		
	}
}
void Delay100us()		//@11.0592MHz
{
	unsigned long edata d;

	_nop_();
	d = 275UL;
	while (d) d--;
}
void Delay10us()		//@11.0592MHz
{
	unsigned long edata c;

	_nop_();
	_nop_();
	c = 26UL;
	while (c) c--;
}
float filter3()
{
	float sum = 0;
	int count,a;
	for ( count=0;count<N;count++)
	{
		sum = sum+ ADC_out_1;
		a++;
		if(a==255) a=0;
	}
	return (sum/N);
}
 




