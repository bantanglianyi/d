#include "TIME.H"	 
u16 ds_w=0,ds=0,wb=0,wb_w=0,js=0;		   //,js_w=0,TH_1=0,TL_1=0
u8 TL_0=0,TH_0=0;
f32 zhou =0.0;
extern bit qie;
void init()  //��ʼ������
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD = 0X51;//TMOD=0x51 5T1 16λ������ 1T0 16��ʱ��
	TH0  = 0;	//��6.5535ms*152=996.132ms
	TL0  = 0;	//��
	TH1  = 0;
	TL1  = 0;
	TR1  = 1;  	//��ʱ��1 ����
	TR0  = 1;	//��ʱ��0 ����
	ET0  = 1;	//����T0 �ж�
	ET1  = 1;	//����T1 �ж�
	IT0  = 1;	//�ⲿ�ж�0�½����ж�
	EX0  = 1;	//�ⲿ�ж�0����
	EA   = 1;	//���������ж�	 	 
}

void time_0()interrupt 1 //T0 ��ʱ��  152
{	
	ds++;
//	if(ds==337&&qie==1)
//	{
//		zhou=(js*65535)+TH1*256+TL1;
//		TH1=TL1=0; 
//		js=0;
//	}
//		ds=0;
//		wb=0;				
}
void int_0()interrupt 0	//�ⲿ�ж�
{
	wb++;
	if(ds>=100)
	{
		TL_0=TL0;
		TL0=0;
		TH_0=TH0;
		TH0=0;
		ds_w=ds;
		ds=0;
		wb_w=wb;
		wb=0;
	}		
}
void time_1()interrupt 3 //T1 ������ 
{
	js++;	
}  

