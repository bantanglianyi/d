#include "ADC.h"
#include <STC32G.H>
#include "intrins.h"

void ADC_init()
{
	P1M0 = 0x00; 
	P1M1 = 0xff;		//����0000 0100
	ADCCFG = 0x00;
	ADC_CONTR = 0x80;					//ʹ��ADCģ��
}
unsigned int Get_ADC12bitResult(unsigned char channel)	//channel = 0~14
{
	unsigned int adc;
	ADC_CONTR = (ADC_CONTR & 0xe0) | channel;	 //ѡ��ͨ��
	ADC_CONTR|=0xc0;							//����ADC��Դ������ADת�� 	
	while(!(ADC_CONTR&0x20));					//�ȴ�ת�����
	ADC_CONTR&=~0x20;							//�����־λ
	adc = ADC_RES; 		 						//�洢 ADC �� 12 λ����ĸ� 8 λ
	adc <<= 8;
	adc |= ADC_RESL;  							//�洢 ADC �� 12 λ����ĵ� 4 λ
	adc = adc >> 4;								//16-4=12λ
	return adc;									//adc;
}