//������ģ��ʹ�ö�ʱ��0

#ifndef _HC_SR04_H_
#define _HC_SR04_H_

#define echo P46   //Echo�˿�
#define trig P45   //TTrig�˿�

void HC_SR04_Init(void); //��ʼ��HCSR04����Ӳ��
float  HC_SR04_Loop(void); //��ȡ��ǰ����ֵ
void Timer0_Init(void);	//@12.000MHz

#endif