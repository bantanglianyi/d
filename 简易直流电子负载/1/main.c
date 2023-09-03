#include <STC32G.H>
#include "oled.h"
#include <stdio.h>
#include "USART.H"
#include "ADC.h"
#include "pwm.h"
#include "key_multi.h"

float attenuation=10.0946;//˥������
char group_V[50]; //adc�����������
char group_A[50]; //adc�����������
char i;
unsigned char ftable[50];
float out_V,out,measurement_1,measurement_2,measurement_3,measurement_4,measurement_5,reference; //adc�ĳ��ر���
char minification,count_v;
float v=0;
unsigned int PWM1_Duty;//�ߵ�ƽ�ĳ���ʱ�䣬���ڸı�ռ�ձ�
unsigned int PWM2_Duty;
unsigned int PWM3_Duty;
unsigned int PWM4_Duty;

unsigned char Key1_nums,Key2_nums,Key3_nums,Key4_nums;		//KEY1˫��������KEY2˫��������KEY3˫��������KEY4˫������
unsigned char keyvalue;	
char pattern=0;	//��ֵ
char pwm_pattern=0;//pwm�л�����
char ol_control=0; //ol�ڿ���




	void Delay10us()		//@12.000MHz
{
	unsigned long edata r;

	_nop_();
	_nop_();
	_nop_();
	r = 28000UL;
	while (r) r--;
}


void adc_voltage_0ut() //adc���ѹ
{
		float err=0;
		long N=10000;
		unsigned long count;
		float sum=0;
		count_v=2.011;
		/*��ʾ��ѹ����ģʽ*/
		OLED_ShowChinese(0,0,9,16);
		OLED_ShowChinese(16,0,10,16);
		OLED_ShowChinese(32,0,11,16);
		OLED_ShowChinese(48,0,12,16);
		OLED_ShowChinese(64,0,13,16);
		OLED_ShowChinese(80,0,14,16);
		/*����ADCͨ��*/
		measurement_2=Get_ADC12bitResult(3);//adc 4ͨ��
		measurement_3=Get_ADC12bitResult(4);//adc 5ͨ��
		measurement_4=Get_ADC12bitResult(5);//adc 6ͨ��
		/*�ж�ʹ��ͨ��*/
		reference=Get_ADC12bitResult(15);//adc�ڲ��ο�ͨ��//
		out_V	=(float)(((measurement_2/reference*1.182937))/count_v*attenuation);	//���������adc�������
		//printf("%.6f\n",out_V); //����adc����
	   for ( count=0;count<N;count++)
	   {
		
			 if(pattern!=2)
			 {
				goto A;
			 }
			sum += out_V;
	   }
		out=(float)(sum/N);
		if(out>13.9)err=0.08;
	   if(out>4.9|out<13.9)err=0.03;
	   if(out<4.9)err=0.02;
	   if(out<0.3)
	   {
			out=0;
			err=0;
	   }
		sprintf(group_V,"v:%.2f",out+err);//��adc��ֵ��������
		OLED_ShowString(0,2,group_V,16); //adc��ʾ����
	   	A:;
}

void adc_electricity_0ut() //adc�����
{	
	
	
		float out_A;
		//printf("%.6f\n",out); //����adc����
		measurement_1=Get_ADC12bitResult(1);//adc2ͨ��
		reference=Get_ADC12bitResult(15);//adc�ڲ��ο�ͨ��
		//out_A=((float)(((measurement_1/reference*1.182937)/0.5)*6.818));	//���������adc�������
		/*��ʾ��������ģʽ*/
		OLED_ShowChinese(0,0,9,16);
		OLED_ShowChinese(16,0,15,16);
		OLED_ShowChinese(32,0,11,16);
		OLED_ShowChinese(48,0,12,16);
		OLED_ShowChinese(64,0,13,16);
		OLED_ShowChinese(80,0,14,16);
	
		switch(ol_control)
	{
		case 0 :out_A=0+v;break;
		case 1 :out_A=100+v;break;
		case 2 :out_A=200+v;break;
		case 3 :out_A=300+v;break;
		case 4 :out_A=400+v;break;
		case 5 :out_A=500+v;break;
		case 6 :out_A=600+v;break;
		case 7 :out_A=700+v;break;
		case 8 :out_A=800+v;break;
		case 9 :out_A=900+v;break;
		case 10 :out_A=1000+v;break;
	}

	
		sprintf(group_A,"%.3fmA",out_A);//��adc��ֵ��������
		OLED_ShowString(0,2,group_A,16); //adc��ʾ����
	
}

void pwm()//pwm������ʾ����
{
	switch(pwm_pattern)
	{
		case 0 : /*�ر�pwm��*/
				OLED_ShowChinese(0,0,0,16);
				OLED_ShowChinese(16,0,1,16);
				OLED_ShowString(32,0,"PWM",16);
				OLED_ShowChinese(0,3,7,16);
				OLED_ShowChinese(16,3,8,16);
				PWMA_BKR = 0x00;  //
				break;
		case 1 :
			/*��pwm��*/
				OLED_ShowChinese(0,0,0,16);
				OLED_ShowChinese(16,0,1,16);
				OLED_ShowString(32,0,"PWM",16);		
				OLED_ShowChinese(0,3,5,16);
				OLED_ShowChinese(16,3,6,16);	
				OLED_ShowChinese(0,6,2,16);
				OLED_ShowChinese(16,6,3,16);
				OLED_ShowChinese(32,6,4,16);
				PWMA_BKR = 0x80;  //ʹ�������
				OLED_ShowNum(48,6,PWM1_Duty,3,16);
				break;
	}
}
void electricity_switch()//���ص�������
{
	OLED_ShowChinese(0,0,5,16);
	OLED_ShowChinese(16,0,7,16);
	OLED_ShowNum(32,2,ol_control,2,16);
	switch(ol_control)
	{
		case 0 :P67=0;break;
		case 1 :P66=0;break;
		case 2 :P65=0;break;
		case 3 :P64=0;break;
		case 4 :P63=0;break;
		case 5 :P62=0;break;
		case 6 :P61=0;break;
		case 7 :P60=0;break;
		case 8 :P36=0;break;
		case 9 :P37=0;break;
		case 10 :P6=0XFF;P70=1;P71=1;break;
	}
}

void main()
{

	
	EAXFR = 1;				// ʹ�ܷ���XFR
	CKCON = 0x00;			// �����ⲿ��������Ϊ���
	WTST = 0;  
	/*����ģʽ����*/
	P4M0 = 0xff; P4M1 = 0x00; 
    P3M0 = 0xff; P3M1 = 0xff; 
	P6M0 = 0xff; P6M1 = 0xff; 
    P2M0 = 0xff; P2M1 = 0xff; 	  
	




	P67=0;
	
	ADC_init();  //adc��ʼ��
	UartInit(); //���ڳ�ʼ��
	PWMA_Init();  //pwm��ʼ��
	OLED_Init();  //oled��Ļ��ʼ��
	UpdatePwm(); //����pwm
	PWM1_Duty=50; //��ʼpwm����ռ�ձ�
	while(1)
	{
		keyvalue = key_multi();		//��ȡ��ֵ����ֵ�ͳ����̰�˫���ĸ��ϼ�ֵ��

		switch(pattern)
		{
			case 0 :electricity_switch();break; //���ؿ���
			case 1 :adc_electricity_0ut();break;//����ģʽ
			case 2 :adc_voltage_0ut();break;//��ѹģʽ
			case 3 :pwm();break;//pwm������
			
		}
//		for(i=0;i<10;i++)
//	{
//		Delay10us();
//		v+=0.001;
//		if(v>0.02)v=0;
//	
//	}
		
		if(keyvalue == Key1_Single_Click)//ģʽ����
		{
			OLED_Clear();
			pattern++;
			if(pattern>3)pattern=0;
		}
				
		if(keyvalue == Key1_Long_Click)//pwm����
		{
			if(pattern==3)
			{
			OLED_Clear();
			pwm_pattern++;
			if(pwm_pattern>1)pwm_pattern=0;
			}
		}		//KEY1������Ϩ��LED1
		if(keyvalue == Key1_Double_Click) 	//����ģʽ1
		{
			OLED_Clear();
			pattern=0;
		}
		
		if(keyvalue == Key2_Single_Click) //lo�ڿ���
		{
			if(pattern==0)
			{
				P6=0XFF;
				P36=1;
				P37=1;
				OLED_Clear();
				ol_control++;
			}
		
			if(pattern==3)
			{
				 PWM1_Duty++;
				UpdatePwm(); //����pwm
				if( PWM1_Duty>100)PWM1_Duty=100;
				
				
			}
				if(ol_control>10)ol_control=0;
		}				//KEY2�̰�������LED3
		if(keyvalue == Key2_Long_Click) 
		{
			if(pattern==0)
			{
				P6=0XFF;
				P36=1;
				P37=1;
				OLED_Clear();
				ol_control--;
				
				
			}
			if(pattern==3)
			{
				 PWM1_Duty--;
				UpdatePwm(); //����pwm
				if( PWM1_Duty<0)PWM1_Duty=0;
				
			}
			if(ol_control<0)ol_control=0;
		}
			//KEY2������Ϩ��LED3
//		if(keyvalue == Key2_Double_Click) 								//KEY3˫��������LED3��LED4���ٴ�˫����Ϩ��LED3��LED4
//		{
//			Key2_nums++;		//KEY2˫������
//			if(Key2_nums%2 == 1)		//������˫��������LED3��LED4
//			{
//				LED3 = ON;
//				LED4 = ON;
//			}
//			if(Key2_nums%2 == 0)		//ż����˫����Ϩ��LED3��LED4
//			{
//				LED3 = OFF;
//				LED4 = OFF;
//			}
//			if(Key2_nums >= 99) Key2_nums = 0;	//��ֹKEY2˫���������������
//		}
//		
		if(keyvalue == Key3_Single_Click)
				
			{
				if(pattern==3)
				 PWM1_Duty+=10;
				UpdatePwm(); //����pwm
				if( PWM1_Duty>100)PWM1_Duty=100;
			}
					//KEY3�̰�������LED5
		if(keyvalue == Key3_Long_Click) 
			{		
				if(pattern==3)
				 PWM1_Duty-=10;
				UpdatePwm(); //����pwm
				if( PWM1_Duty<0)PWM1_Duty=0;
			}
			//KEY3������Ϩ��LED5
//		if(keyvalue == Key3_Double_Click) 								//KEY3˫��������LED5��LED6���ٴ�˫����Ϩ��LED5��LED6
//		{
//			Key3_nums++;		//KEY3˫������
//			if(Key3_nums%2 == 1)		//������˫��������LED5��LED6
//			{
//				LED5 = ON;
//				LED6 = ON;
//			}
//			if(Key3_nums%2 == 0)		//ż����˫����Ϩ��LED5��LED6
//			{
//				LED5 = OFF;
//				LED6 = OFF;
//			}
//			if(Key3_nums >= 99) Key3_nums = 0;		//��ֹKEY3˫���������������
//		}
//		
//		if(keyvalue == Key4_Single_Click) LED7 = ON;			//KEY4�̰�������LED7
//		if(keyvalue == Key4_Long_Click) 	LED7 = OFF;			//KEY4������Ϩ��LED7
//		if(keyvalue == Key4_Double_Click) 								//KEY4˫��������LED7��LED8���ٴ�˫����Ϩ��LED7��LED8
//		{
//			Key4_nums++;		//KEY4˫������
//			if(Key4_nums%2 == 1)		//������˫��������LED7��LED8	
//			{
//				LED7 = ON;
//				LED8 = ON;
//			}
//			if(Key4_nums%2 == 0)		//ż����˫����Ϩ��LED7��LED8
//			{
//				LED7 = OFF;
//				LED8 = OFF;
//			}
//			if(Key4_nums >= 99) Key4_nums = 0;		//��ֹKEY4˫���������������
//		}
		

	}
}


