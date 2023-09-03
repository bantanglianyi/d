#include <STC32G.H>
#include "USART.H"
#include <stdio.h>

#define PWM_PERIOD  1000   //��������ֵ
#define ENO3P       0x10
#define ENO3N       0x20
#define PWM3_1      0x10	//P:P2.4  N:P2.5
unsigned int PWM3_Duty;
unsigned char cnt_H,cnt_L;
unsigned int newcount,oldcount;						//����ֵ���¼���ֵ
unsigned int number,out;										//����ܼ���ֵ
						


float PID(float Sample,float Position); //����ʽPID
void PWM_Config();
void Encoder_Check();
void Timer0_Init(void);		//100΢��@12.000MHz



void main()
{
	EAXFR = 1; 									// ʹ�ܷ��� XFR
	CKCON = 0x00;							  // �����ⲿ���������ٶ�Ϊ���
	WTST = 0x00; 								// ���ó������ȴ���������ֵΪ 0 �ɽ� CPU ִ�г�����ٶ�����Ϊ���

	P0M1 = 0x00;P0M0 = 0x00;		//����P0��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
	P1M1 = 0x00;P1M0 = 0xff;		//����P1��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
	P2M1 = 0x00;P2M0 = 0x00;		//����P2��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
	P3M1 = 0x00;P3M0 = 0x00;		//����P3��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
	P4M1 = 0x00;P4M0 = 0x00;		//����P4��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
	P5M1 = 0x00;P5M0 = 0x00;		//����P5��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
	P6M1 = 0x00;P6M0 = 0x00;		//����P6��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
	P7M1 = 0x00;P7M0 = 0x00;		//����P7��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
	
	EA=1;
	PWM_Config();
	UartInit();
//	Timer0_Init();
	PWM3_Duty=100;

	while(1)
	{		

		
			printf("%d\n",newcount);
			
	}		
}
//void Timer0_Isr(void) interrupt 1
//{
//	out=(newcount-oldcount);
//	oldcount=newcount;
//}

//void Timer0_Init(void)		//100΢��@12.000MHz
//{
//	AUXR &= 0x7F;			//��ʱ��ʱ��12Tģʽ
//	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
//	TL0 = 0xF0;				//���ö�ʱ��ʼֵ
//	TH0 = 0xD8;				//���ö�ʱ��ʼֵ
//	TF0 = 0;				//���TF0��־
//	TR0 = 1;				//��ʱ��0��ʼ��ʱ
//	ET0 = 1;				//ʹ�ܶ�ʱ��0�ж�z
//}


//float PID(float expect,float practical) //����ʽPID
//{
//	float out;
//	errir = expect - practical;
//	total_errir += errir;
//	ratio = kp * errir;	
//	integral =  total_errir * ki;
//	differential = (errir - last1_errir)*kd;
//	last1_errir = errir;
//	out = ratio + integral + differential;
//	if(integral>1000) integral = 1000;
//	if(integral<-1000) integral = -1000;
//	return out;
//}
float PID(float Sample,float Position)//λ��ʽPID
{
	float Kp =0.04;
	float Ki =0;
	float Kd =0.009;
	float ErrPres,Pias,Out,ErrPres_formerly,ErrPres_lastseen;
	ErrPres=(Position-Sample);
	Pias+=ErrPres;//ÿ��������ֵ
	Out=((ErrPres_formerly-ErrPres)*Kp)+(Pias*Ki)+((ErrPres-2*ErrPres_formerly+	ErrPres_lastseen)*Kd);
	//���=���ϴ����-�����*p  +   ������ֵ*i   +    �����-2*�ϴ����+���ϴ���*d
	ErrPres_formerly=ErrPres;//�ϴ����
	ErrPres_lastseen=ErrPres_formerly;//���ϴ����
	if(Out>1000)Out=1000;
	if(Out<0)Out=0;
	return Out;
}



void PWM_Config()
{
	PWMA_PS|=0x01	;
	PWMA_PS|=0x04	;
	PWMA_ENO = 0x00;// ���ó� TRGI �� pin ��ص� ENO ��Ӧ bit ����� input
	
	
	
	PWMA_CCER1 = 0x00;					// ����CCER���ر�ͨ��
	PWMA_CCER2 = 0x00;					//д CCMRx ǰ���������� CCxE �ر�ͨ��
	
	PWMA_CCMR1 = 0x21; 					// ͨ��ģʽ����Ϊ���룬�ӱ����� , �˲��� 4 ʱ��
	PWMA_CCMR2 = 0x21; 					// ͨ��ģʽ����Ϊ���룬�ӱ����� , �˲��� 4 ʱ��
	
//	PWMA_CCMR3 = 0x68;
//    PWMA_CCMR4 = 0x68;
//	
	PWMA_CCER1 = 0x55; 					// ����ͨ��ʹ�ܺͼ���
	PWMA_CCER2 = 0x55; 					// ����ͨ��ʹ�ܺͼ���
	
//	PWMA_SMCR = 0x01; 					// ������ģʽ 1
//	PWMA_SMCR = 0x02; 					// ������ģʽ 2	
	PWMA_SMCR = 0x03; 					// ������ģʽ 3
	

	PWMA_ARRH = (unsigned char)(PWM_PERIOD >> 8); //��������ʱ��
    PWMA_ARRL = (unsigned char)PWM_PERIOD;
	
//	PWMA_ENO |= ENO3P; //ʹ�����
//    PWMA_ENO |= ENO3N; //ʹ�����
//	  PWMA_PS = 0x00;  //�߼� PWM ͨ�������ѡ��λ	
	PWMA_IER = 0x82; 						// ʹ���ж�
	PWMA_CR1 |= 0x81; 					// ʹ��PWM������
}



//========================================================================
// ����: UpdatePwm(void)
// ����: ����PWMռ�ձ�. 
// ����: none.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================*/
//void UpdatePwm(void)//PWMx_DUTY��ֵ��Ҫ��������ֵ
//{
////    PWMA_CCR1H = (unsigned int)(PWM1_Duty >> 8); //����ռ�ձ�ʱ��
////    PWMA_CCR1L = (unsigned int)(PWM1_Duty);
////    PWMA_CCR2H = (unsigned int)(PWM2_Duty >> 8); //����ռ�ձ�ʱ��
////    PWMA_CCR2L = (unsigned int)(PWM2_Duty);
//    PWMA_CCR3H = (unsigned int)(PWM3_Duty >> 8); //����ռ�ձ�ʱ��
//    PWMA_CCR3L = (unsigned int)(PWM3_Duty);
////    PWMA_CCR4H = (u8)(PWM4_Duty >> 8); //����ռ�ձ�ʱ��
////    PWMA_CCR4L = (u8)(PWM4_Duty);
//}

void PWMA_ISR (void) interrupt 26
{
	if(PWMA_SR1 & 0X02)
	{
	
		cnt_H=PWMA_CCR1H;
		cnt_L=PWMA_CCR1L;
		PWMA_SR1 &=~0X02;
		newcount = cnt_H * 256 + cnt_L;	//��ȡ�µļ�����ֵ

	}
}


