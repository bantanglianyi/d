#include <STC32G.H>
#include <stdio.h>
#include "oled.h"
#include "USART.H"
#include "key_multi.h"
#include "ADC.H"
/*����Ƶ��Ϊ24Mhz*/
#define N 100
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
u8 Key1_nums,Key2_nums,Key3_nums,Key4_nums;		//KEY1˫��������KEY2˫��������KEY3˫��������KEY4˫������
u8 keyvalue;//��ֵ
u16 b=500;
u16 TH1_NOW,TL1_NOW;
char count_key=0;//Ƶ�ʵ�ѹ����ת��
char c,TF1_NOW=0;
float f;
char count;
int count_time4=0;
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
void Delay_ms_(int ms)		//@24.000MHz
{
	while(ms--)
	{
		unsigned long edata k;
		_nop_();
		_nop_();
		_nop_();
		k = 5998UL;
		while (k)k--;
	}
}

/*ADC�ӳٺ���*/
void Delay_ADC_100us()		
{
	unsigned long edata i;

	_nop_();
	_nop_();
	_nop_();
	i = 598UL;
	while (i) i--;
}
/*ADC���ú���
����ֵΪ�ɼ���ѹ*/
float ADC_call_1()
{
	float ADC_1,ADC_15;//ADCͨ���������
	float ADC_out_1;//ADCͨ��һ�����մ���
	ADC_15=Get_ADC12bitResult(15);
	ADC_1=Get_ADC12bitResult(1);
	ADC_out_1=(float)(1.18301*ADC_1/ADC_15);
//	printf("%.4f\n",ADC_out_filter);
	Delay_ADC_100us();
	return ADC_out_1;
}
float ADC_call_2()
{
	float ADC_2,ADC_15;//ADCͨ���������
	float ADC_out_2;//ADCͨ��һ�����մ���
	ADC_15=Get_ADC12bitResult(15);
	ADC_2=Get_ADC12bitResult(2);
	ADC_out_2=(float)(1.18301*ADC_2/ADC_15);
//	printf("%.4f\n",ADC_out_filter);
	Delay_ADC_100us();
	return ADC_out_2;
}
/*�˲�*/
float filter(float import)
{
float sum = 0;
for (count=0;count<N;count++)
{
	sum += import;
}
return (float)(sum/N);
}
/*�����ж�,
  ����ֵΪ�ɼ�Ƶ��
  ����ֵ������*/
char Frequency_judgment(float HZ,float U)
{
	char open_circuit_numbe=0;

		if(HZ>5300&&HZ<5800&&U>0.4)     //����ģʽ
		{
			open_circuit_numbe=1;
		}		
		else if(HZ>57000&&HZ<59000&&U<0.4)   //L1
		{
			open_circuit_numbe=2;
		}
		else if(HZ>12000&&HZ<13000&&U<0.4)  //L2
		{
			open_circuit_numbe=3;
		}
		else if(HZ>7300&&HZ<7500&&U<0.4)    //L3
		{
			open_circuit_numbe=4;
		}
		else if(HZ>5900&&HZ<6080&&U>0.4)    //C1
		{
			open_circuit_numbe=5;
		}
		else if(HZ>8900&&HZ<9300&&U>0.4)   //C2
		{
			open_circuit_numbe=6;
		}
		else if(HZ>7500&&HZ<9000&&U>0.4)   //C3
		{
			open_circuit_numbe=7;
		}
		else if(HZ>6080&&HZ<6300&&U>0.4)   //C4
		{
			open_circuit_numbe=8;
		}
		 else if(U>1.6 &&U<2)
		{
			open_circuit_numbe=1;
		}
		else if(U>2&&U<2.5)
		{
			open_circuit_numbe=9;
		}		
		else if(U>0.6&&U<1)
		{
			open_circuit_numbe=10;
		}
		else if(U>1.2&&U<1.6)
		{
			open_circuit_numbe=11;
		}
		else if(U<0.2&&HZ<10)
		{
			open_circuit_numbe=12;
		}
	return open_circuit_numbe;
}

/*���ϱ���ж�*/
void Fault_number()
{	
	char malfunction_number=0;
	malfunction_number=Frequency_judgment(filter(f),ADC_call_1());
	switch(malfunction_number)
	{
		case 0:
			
			OLED_ShowChinese(16,2,19,16);//��
			OLED_ShowChinese(32,2,20,16);//ʼ
			OLED_ShowChinese(48,2,6,16);//��
			OLED_ShowChinese(64,2,7,16);//��
		break;
		case 1:
			
			OLED_ShowChinese(16,2,16,16);//û
			OLED_ShowChinese(32,2,17,16);//��
			OLED_ShowChinese(48,2,12,16);//��
			OLED_ShowChinese(64,2,13,16);//��
		break;
		case 2:
			OLED_ShowString(16,2,"L1",16);
			OLED_ShowChinese(32,2,10,16);//��
			OLED_ShowChinese(48,2,11,16);//·
			OLED_ShowString(64,2,"  ",16);
		break;
		case 3:
			OLED_ShowString(16,2,"L2",16);
			OLED_ShowChinese(32,2,10,16);//��
			OLED_ShowChinese(48,2,11,16);//·
			OLED_ShowString(64,2,"  ",16);
		break;
		case 4:
			OLED_ShowString(16,2,"L3",16);
			OLED_ShowChinese(32,2,10,16);//��
			OLED_ShowChinese(48,2,11,16);//·
			OLED_ShowString(64,2,"  ",16);
		break;
		case 5:
			OLED_ShowString(16,2,"C1",16);
			OLED_ShowChinese(32,2,10,16);//��
			OLED_ShowChinese(48,2,11,16);//·
			OLED_ShowString(64,2,"  ",16);
		break;
		case 6:
			OLED_ShowString(16,2,"C2",16);
			OLED_ShowChinese(32,2,10,16);//��
			OLED_ShowChinese(48,2,11,16);//·
			OLED_ShowString(64,2,"  ",16);
		break;
		case 7:
			OLED_ShowString(16,2,"C3",16);
			OLED_ShowChinese(32,2,10,16);//��
			OLED_ShowChinese(48,2,11,16);//·
			OLED_ShowString(64,2,"  ",16);
		break;
		case 8:
			OLED_ShowString(16,2,"C4",16);
			OLED_ShowChinese(32,2,10,16);//��
			OLED_ShowChinese(48,2,11,16);//·
			OLED_ShowString(64,2,"  ",16);		
		break;
		case 9:
			OLED_ShowString(16,2,"L1",16);
			OLED_ShowChinese(32,2,18,16);//��
			OLED_ShowChinese(48,2,11,16);//·
			OLED_ShowString(64,2,"  ",16);		
		break;
		case 10:
			OLED_ShowString(16,2,"L2",16);
			OLED_ShowChinese(32,2,18,16);//��
			OLED_ShowChinese(48,2,11,16);//·
			OLED_ShowString(64,2,"  ",16);
		break;
		case 11:
			OLED_ShowString(16,2,"L3",16);
			OLED_ShowChinese(32,2,18,16);//��
			OLED_ShowChinese(48,2,11,16);//·
			OLED_ShowString(64,2,"  ",16);		
		break;
		case 12:
			OLED_ShowString(16,2,"C3",16);
			OLED_ShowChinese(32,2,18,16);//��
			OLED_ShowChinese(48,2,11,16);//·
			OLED_ShowString(64,2,"  ",16);		
		break;
		
	}
}
/*�๦�ܶ�������*/
void key_independence()
{
	
		if(keyvalue == Key1_Single_Click)//KEY1�̰�����һ��
		{
			count_time4+=1;
		}
		if(keyvalue == Key1_Long_Click)//KEY1����,
		{
			
		}
		if(keyvalue == Key1_Double_Click)//KEY1˫��
		{
			Key1_nums++;		//KEY1˫������
			if(Key1_nums%2 == 1)		//������˫��
			{

			}
			if(Key1_nums%2 == 0)		//ż����˫����Ϩ��LED1��LED2
			{
			
			}
			if(Key1_nums >= 99) Key1_nums = 0;		//��ֹKEY1˫���������������
		}
		
		if(keyvalue == Key2_Single_Click) //KEY2�̰�
		{
		
		}
		if(keyvalue == Key2_Long_Click)//KEY2����
		{
		
		}
		if(keyvalue == Key2_Double_Click) //KEY3˫��
		{
			Key2_nums++;		//KEY2˫������
			if(Key2_nums%2 == 1)		//������˫��
			{
			
			}
			if(Key2_nums%2 == 0)		//ż����˫��
			{
			
			}
			if(Key2_nums >= 99) Key2_nums = 0;	//��ֹKEY2˫���������������
		}
		
		if(keyvalue == Key3_Single_Click)//KEY3�̰�
		{
		
		}
		if(keyvalue == Key3_Long_Click)//KEY3����
		{
		
		}
		if(keyvalue == Key3_Double_Click) //KEY3˫��
		{
			Key3_nums++;		//KEY3˫������
			if(Key3_nums%2 == 1)//������˫��
			{

			}
			if(Key3_nums%2 == 0)		//ż����˫��
			{

			}
			if(Key3_nums >= 99) Key3_nums = 0;		//��ֹKEY3˫���������������
		}
		
		if(keyvalue == Key4_Single_Click)//KEY4�̰�
		{
		
		}
		if(keyvalue == Key4_Long_Click)//KEY4����
		{
		
		}
		if(keyvalue == Key4_Double_Click)//KEY4˫��
		{
			Key4_nums++;		//KEY4˫������
			if(Key4_nums%2 == 1)//������˫��	
			{

			}
			if(Key4_nums%2 == 0)		//ż����˫��
			{
				
			}
			if(Key4_nums >= 99) Key4_nums = 0;		//��ֹKEY4˫���������������
		}
}



void main()
{
	
	EA=1;
	XOSCCR=0xc4;
	while(XOSCCR&1);
	CLKDIV=0X00;
	CLKSEL=0X01;
	
	EAXFR=1;
	CKCON=0X00;
	WTST=0X00;
	P0M0 = 0x00; P0M1 = 0x00; 
	P3M0 &= ~0xdf; P3M1 &= ~0xdf; 
	P2M0 = 0xff; P2M1 = 0x00; 
	P4M0 = 0XFF; P4M1 = 0X00;
	OLED_Init();
	Timer0_Init();
	Timer1_Init();
	UartInit();
	ADC_init();

	while(1)
	{
		keyvalue = key_multi();//��ȡ��ֵ
		key_independence();
		
		switch(count_time4)
		{
			case 1:
			Delay_ms_(10000);
			P01=0;
			Delay_ms_(1000);
			if(Frequency_judgment(filter(f),ADC_call_1())<9)
			{
				P01=1;
				Delay_ms_(4000);
				Fault_number();
			}
			else 
			{
				Delay_ms_(3000);
				Fault_number();	
			}
			break;
		}

	}
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
			printf("%.3f %.3f\n\r",ADC_call_1(),filter(f));
		}
		
		
}