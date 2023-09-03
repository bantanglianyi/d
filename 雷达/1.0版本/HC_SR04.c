#include <STC32G.H>
#include "hc_sr04.h"
#define MAIN_Fosc 12000000UL		//������Ƶ12MHz�������ʵ��ʹ��Ƶ���޸ģ�����delay��������Ӧ��Ƶ��

typedef unsigned char u8;				//unsigned char			 	���ͣ���u8��ʾ
typedef unsigned int u16;				//unsigned int 				���ͣ���u16��ʾ
typedef unsigned long int u32;	//unsigned long int 	���ͣ���u32��ʾ

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
// ����: HC_SR04_Init()
// ����: ��ʼ��HC_SR04����Ӳ����
// ����: 
// ����: none.
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
// ����: HC_SR04_Start()
// ����: ��ʼ����������
// ����: 
// ����: none.
//========================================================================
void HC_SR04_Start()
{
	trig = 0;
	Delay20us();
	trig = 1;
}
//========================================================================
// ����: int HC_SR04_Loop()
// ����: ���ؾ��롣
// ����:  
// ����: distance:���루��λ�����ף�.
//========================================================================
float HC_SR04_Loop()
{
	 float distance;//distance|����
	 HC_SR04_Start();
	 while(!echo);		//Wait when RX is zero|��RXΪ��ʱ�ȴ�
	 TR0 = 1;			    //Opening count|��������
	 while(echo);			//When RX counts to 1 and waits|��RXΪ1�������ȴ�
	 TR0 = 0;				  //Closing count|�رռ���
	 time = TH0*256+TL0;
	 TH0 = 0;
	 TL0 = 0;
	 distance =(float)(time*1.7)/100;     //�������CM
	if(flag == 1)		    //��������
	{
		flag = 0;
		distance = 0;
	}
	return distance;
}

void Timer0_Isr(void) interrupt 1      //T0�ж��������������,������෶Χ
{
	flag = 1;							 //�ж������־
}