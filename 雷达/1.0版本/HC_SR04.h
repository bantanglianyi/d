//超声波模块使用定时器0

#ifndef _HC_SR04_H_
#define _HC_SR04_H_

#define echo P46   //Echo端口
#define trig P45   //TTrig端口

void HC_SR04_Init(void); //初始化HCSR04所需硬件
float  HC_SR04_Loop(void); //获取当前距离值
void Timer0_Init(void);	//@12.000MHz

#endif