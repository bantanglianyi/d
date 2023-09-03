#include <STC32G.H>
#include <stdio.h>
#include "oled.h"
#include "USART.H"
#include "key_multi.h"
#include "ADC.H"
/*����Ƶ��Ϊ24Mhz*/
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long	
u8 Key1_nums,Key2_nums,Key3_nums,Key4_nums;		//KEY1˫��������KEY2˫��������KEY3˫��������KEY4˫������
u8 keyvalue;//��ֵ
u16 b=500;//��������ʱ
u16 TH1_NOW,TL1_NOW;//�������ߵ�λ����
u16 TF1_NOW=0;//��������ת����
char count_key=0;//Ƶ�ʵ�ѹ����ת��
char c;//�������������
float f;//Ƶ�ʼ�������ȡֵ
float f_1;
void Timer1_Init(void)		//2����@24.000MHz  ������
{
	TMOD &= 0x0F;			//���ö�ʱ��ģʽ
	TMOD |= 0x50;			//���ö�ʱ��ģʽ
	TL1 = 0;				//���ö�ʱ��ʼֵ
	TH1 = 0;				//���ö�ʱ��ʼֵ
	TF1 = 0;				//���TF1��־
	TR1 = 1;				//��ʱ��0��ʼ��ʱ
	ET1 = 1;				//ʹ�ܶ�ʱ��1�ж�
	
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

void Timer0_Init(void)		//2����@24.000MHz
{
	AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0x80;				//���ö�ʱ��ʼֵ
	TH0 = 0x44;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0 = 1;				//ʹ�ܶ�ʱ��0�ж�
}



/*ADC�ӳٺ���*/
//void Delay_ADC_100us()		
//{
//	unsigned long edata i;

//	_nop_();
//	_nop_();
//	_nop_();
//	i = 598UL;
//	while (i) i--;
//}
///*ADC���ú���
//����ֵΪ�ɼ���ѹ*/
//float ADC_call_1()
//{
//	float ADC_1,ADC_15;//ADCͨ���������
//	float ADC_out_1;//ADCͨ��һ�����մ���
//	ADC_15=Get_ADC12bitResult(15);
//	ADC_1=Get_ADC12bitResult(1);
//	ADC_out_1=(float)(1.18301*ADC_1/ADC_15);
////	printf("%.4f\n",ADC_out_filter);
//	Delay_ADC_100us();
//	return ADC_out_1;
//}
///*�����ж�,
//  ����ֵΪ�ɼ�Ƶ��
//  ����ֵ������*/
//char Frequency_judgment(float HZ,float U)
//{
//	char open_circuit_numbe;
//	switch(count_key)
//	{
//		case 0://Ƶ��
//		if(HZ>46100&&HZ<47000)
//		{
//			open_circuit_numbe=1;
//			
//		}		
//		else if(HZ>453000&&HZ<500000)
//		{
//			open_circuit_numbe=2;
//		}
//		else if(HZ>101500&&HZ<103000)
//		{
//			open_circuit_numbe=3;
//		}
//		else if(HZ>58500&&HZ<59700)
//		{
//			open_circuit_numbe=4;
//		}
//		else if(HZ>610000)
//		{
//			open_circuit_numbe=5;
//		}
//		else if(HZ>87700&&HZ<88800)
//		{
//			open_circuit_numbe=6;
//		}
//		else if(HZ>84200&&HZ<86300)
//		{
//			open_circuit_numbe=7;
//		}
//	//	else if(HZ>58500&&HZ<58600)
//	//	{
//	//		open_circuit_numbe=8;
//	//	}
//		break;
//				
//		case 1://��ѹ
//		if(U>53070&&U<54000)
//		{
//			open_circuit_numbe=9;
//			
//		}		
//		else if(U>453000&&U<500000)
//		{
//			open_circuit_numbe=10;
//		}
//		else if(U>101500&&U<103000)
//		{
//			open_circuit_numbe=11;
//		}
//		
//		break;
//	}
//	return open_circuit_numbe;
//}

///*���ϱ���ж�*/
//void Fault_number()
//{
//	char malfunction_number;
//	malfunction_number=Frequency_judgment(f,ADC_call_1());
//	switch(malfunction_number)
//	{
//		case 1:
//			OLED_ShowChinese(32,2,16,16);//û
//			OLED_ShowChinese(48,2,17,16);//��
//			OLED_ShowChinese(64,2,12,16);//��
//			OLED_ShowChinese(80,2,13,16);//��
//		break;
//		case 2:
//			OLED_ShowString(16,2,"L1",16);
//			OLED_ShowChinese(32,2,10,16);//��
//			OLED_ShowChinese(48,2,11,16);//·
//		break;
//		case 3:
//			OLED_ShowString(16,2,"L2",16);
//			OLED_ShowChinese(32,2,10,16);//��
//			OLED_ShowChinese(48,2,11,16);//·
//		break;
//		case 4:
//			OLED_ShowString(16,2,"L3",16);
//			OLED_ShowChinese(32,2,10,16);//��
//			OLED_ShowChinese(48,2,11,16);//·
//		break;
//		case 5:
//			OLED_ShowString(16,2,"C1",16);
//			OLED_ShowChinese(32,2,10,16);//��
//			OLED_ShowChinese(48,2,11,16);//·
//		break;
//		case 6:
//			OLED_ShowString(16,2,"C2",16);
//			OLED_ShowChinese(32,2,10,16);//��
//			OLED_ShowChinese(48,2,11,16);//·
//		break;
//		case 7:
//			OLED_ShowString(16,2,"C3",16);
//			OLED_ShowChinese(32,2,10,16);//��
//			OLED_ShowChinese(48,2,11,16);//·
//		break;
//		case 8:
//			OLED_ShowString(16,2,"C4",16);
//			OLED_ShowChinese(32,2,10,16);//��
//			OLED_ShowChinese(48,2,11,16);//·	
//		break;
//		case 9:
//			OLED_ShowString(16,2,"L1",16);
//			OLED_ShowChinese(32,2,18,16);//��
//			OLED_ShowChinese(48,2,11,16);//·	
//		break;
//		case 10:
//			OLED_ShowString(16,2,"L2",16);
//			OLED_ShowChinese(32,2,18,16);//��
//			OLED_ShowChinese(48,2,11,16);//·	
//		break;
//		case 11:
//			OLED_ShowString(16,2,"L3",16);
//			OLED_ShowChinese(32,2,18,16);//��
//			OLED_ShowChinese(48,2,11,16);//·	
//		break;
//		
//	}
//}
///*�๦�ܶ�������*/
//void key_independence()
//{
//		if(keyvalue == Key1_Single_Click)//KEY1�̰�����һ��
//		{
//			OLED_Clear();
//			Fault_number();
//			
//		}
//		if(keyvalue == Key1_Long_Click)//KEY1����,
//		{
//			count_key++;				//ת����������
//			
//		}
//		if(keyvalue == Key1_Double_Click)//KEY1˫��
//		{
//			Key1_nums++;		//KEY1˫������
//			if(Key1_nums%2 == 1)		//������˫��
//			{

//			}
//			if(Key1_nums%2 == 0)		//ż����˫����Ϩ��LED1��LED2
//			{
//			
//			}
//			if(Key1_nums >= 99) Key1_nums = 0;		//��ֹKEY1˫���������������
//		}
//		
//		if(keyvalue == Key2_Single_Click) //KEY2�̰�
//		{
//		
//		}
//		if(keyvalue == Key2_Long_Click)//KEY2����
//		{
//		
//		}
//		if(keyvalue == Key2_Double_Click) //KEY3˫��
//		{
//			Key2_nums++;		//KEY2˫������
//			if(Key2_nums%2 == 1)		//������˫��
//			{
//			
//			}
//			if(Key2_nums%2 == 0)		//ż����˫��
//			{
//			
//			}
//			if(Key2_nums >= 99) Key2_nums = 0;	//��ֹKEY2˫���������������
//		}
//		
//		if(keyvalue == Key3_Single_Click)//KEY3�̰�
//		{
//		
//		}
//		if(keyvalue == Key3_Long_Click)//KEY3����
//		{
//		
//		}
//		if(keyvalue == Key3_Double_Click) //KEY3˫��
//		{
//			Key3_nums++;		//KEY3˫������
//			if(Key3_nums%2 == 1)//������˫��
//			{

//			}
//			if(Key3_nums%2 == 0)		//ż����˫��
//			{

//			}
//			if(Key3_nums >= 99) Key3_nums = 0;		//��ֹKEY3˫���������������
//		}
//		
//		if(keyvalue == Key4_Single_Click)//KEY4�̰�
//		{
//		
//		}
//		if(keyvalue == Key4_Long_Click)//KEY4����
//		{
//		
//		}
//		if(keyvalue == Key4_Double_Click)//KEY4˫��
//		{
//			Key4_nums++;		//KEY4˫������
//			if(Key4_nums%2 == 1)//������˫��	
//			{

//			}
//			if(Key4_nums%2 == 0)		//ż����˫��
//			{
//				
//			}
//			if(Key4_nums >= 99) Key4_nums = 0;		//��ֹKEY4˫���������������
//		}
//}

void main()
{
	
	EA=1;
	/*�����ڲ�����*/
	XOSCCR=0xc4;
	while(XOSCCR&1);
	CLKDIV=0X00;
	CLKSEL=0X01;
	/*ʹ�ڲ��������*/
	EAXFR=1; 
	CKCON=0X00;
	WTST=0X00;
	/*lo��ģʽ*/
	P0M0 = 0X00;P0M1 = 0X00;
	P2M0 = 0xff; P2M1 = 0x00; 
	P3M0 = 0x00; P3M1 = 0x20; 
	P4M0 = 0XFF; P4M1 = 0X00;
	/*������ʼ��*/
	OLED_Init();
	Timer0_Init();
	Timer1_Init();
	UartInit();
	while(1)
	{
		f_1=f;
		//keyvalue = key_multi();//��ȡ��ֵ
		//key_independence();
		switch(count_key)
		{
			case 0:P01=1;break;
			case 1:P01=0;break;
			case 2:count_key=0;break;
		}
		printf("%.3f\n\r",f_1);
		OLED_ShowNum(0,0,f_1,10,8);
		
	}
}
