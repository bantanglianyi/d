#include <STC32G.H>
#include "hc_sr04.h"
#define MAIN_Fosc 12000000UL		//定义主频12MHz，请根据实际使用频率修改（用于delay函数自适应主频）

typedef unsigned char u8;				//unsigned char			 	类型，用u8表示
typedef unsigned int u16;				//unsigned int 				类型，用u16表示
typedef unsigned long int u32;	//unsigned long int 	类型，用u32表示

u16  time = 0;
bit  flag = 0;

void Delay20us()		//@12.000MHz
{
	unsigned long i;
	_nop_();
	_nop_();
	_nop_();
	i = 58UL;
	while (i) i--;
}

//========================================================================
// 函数: HC_SR04_Init()
// 描述: 初始化HC_SR04所需硬件。
// 参数: 
// 返回: none.
//========================================================================
void Timer0_Init(void)	//@12.000MHz
{			
	TMOD = 0x01;		
	TL0 = 0;				
	TH0 = 0;				
	TF0 = 0;				
	TR0 = 0;						
  EA = 1;	
}
//========================================================================
// 函数: HC_SR04_Start()
// 描述: 开始发送声波。
// 参数: 
// 返回: none.
//========================================================================
void HC_SR04_Start()
{
	trig = 0;
	Delay20us();
	trig = 1;
}
//========================================================================
// 函数: int HC_SR04_Loop()
// 描述: 返回距离。
// 参数:  
// 返回: distance:距离（单位：厘米）.
//========================================================================
float HC_SR04_Loop()
{
	 float distance;//distance|距离
	 HC_SR04_Start();
	 while(!echo);		//Wait when RX is zero|当RX为零时等待
	 TR0 = 1;			    //Opening count|开启计数
	 while(echo);			//When RX counts to 1 and waits|当RX为1计数并等待
	 TR0 = 0;				  //Closing count|关闭计数
	 time = TH0*256+TL0;
	 TH0 = 0;
	 TL0 = 0;
	 distance =(float)(time*1.7)/100;     //算出来是CM
	if(flag == 1)		    //超出测量
	{
		flag = 0;
		distance = 0;
	}
	return distance;
}

void Timer0_Isr(void) interrupt 1      //T0中断用来计数器溢出,超过测距范围
{
	flag = 1;							 //中断溢出标志
}