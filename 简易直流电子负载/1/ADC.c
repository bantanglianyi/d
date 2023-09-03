#include "ADC.h"
#include <STC32G.H>
#include "intrins.h"

void ADC_init()
{
	P1M0 = 0x00; 
	P1M1 = 0xff;		//高阻0000 0100
	ADCCFG = 0x00;
	ADC_CONTR = 0x80;					//使能ADC模块
}
unsigned int Get_ADC12bitResult(unsigned char channel)	//channel = 0~14
{
	unsigned int adc;
	ADC_CONTR = (ADC_CONTR & 0xe0) | channel;	 //选择通道
	ADC_CONTR|=0xc0;							//开启ADC电源，启动AD转换 	
	while(!(ADC_CONTR&0x20));					//等待转换完成
	ADC_CONTR&=~0x20;							//清除标志位
	adc = ADC_RES; 		 						//存储 ADC 的 12 位结果的高 8 位
	adc <<= 8;
	adc |= ADC_RESL;  							//存储 ADC 的 12 位结果的低 4 位
	adc = adc >> 4;								//16-4=12位
	return adc;									//adc;
}