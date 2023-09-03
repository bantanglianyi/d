#ifndef __ADC_H
#define __ADC_H		

void ADC_init();
unsigned int Get_ADC12bitResult(unsigned char channel);	//channel = 0~14

#endif