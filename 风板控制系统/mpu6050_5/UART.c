#include "UART.h"


void UART_init(int pin,unsigned long btl,int isr)
{
	if(pin==1)		//����1
	{
      P_SW1 |= 0x00;   //����1�����л��� P30.P31
		  SCON = 0x50;    //����1����ģʽΪ0��8λ����ģʽ
		  AUXR &= 0xFE;   //����1ѡ��ʱ��1��Ϊ�����ʷ�����
		  TMOD |= 0x00;    
			TL1 = (65536 - MAIN_Fosc / btl / 4); //��ʱ��2װ��ֵ
			TH1 = (65536 - MAIN_Fosc / btl / 4) >> 8; 
			TR1 = 1;																 //������ʱ��1
			AUXR |= 0x40;                            //��ʱ��1��1Tģʽ
			if(isr==1)
			{ES = 1;}                                  //ʹ�ܴ���1�ж�
	}
	if(pin ==2) 
	{
			P_SW2 |= 0x01;   //����2�����л��� P40.P42
		  S2CON = 0x10;    //����2ѡ��ʱ��2��Ϊ�����ʷ�����
			T2L = (65536 - MAIN_Fosc / btl / 4); //��ʱ��2װ��ֵ
			T2H = (65536 - MAIN_Fosc / btl / 4) >> 8; 
			AUXR |= 0x14;																 //������ʱ��2��1Tģʽ
			if(isr==1)
			{IE2 |= ES2;}                                  //ʹ�ܴ���2�ж�
	}
	if(pin ==3) 
	{
			P_SW2 |= 0x02;   //����3�����л��� P50.P51
		  S3CON = 0x50;    //����3ѡ��ʱ��3��Ϊ�����ʷ�����
			T3L = (65536 - MAIN_Fosc / btl / 4); //��ʱ��3װ��ֵ
			T3H = (65536 - MAIN_Fosc / btl / 4) >> 8; 
			T4T3M |= 0x0a;																 //������ʱ��3��1Tģʽ
			if(isr==1)
			{IE2 |= ES3;}                                  //ʹ�ܴ���3�ж�
	}
	if(pin ==4) 
	{
			P_SW2 |= 0x04;   //����4�����л��� P52.P53
		  S4CON = 0x50;    //����4ѡ��ʱ��4��Ϊ�����ʷ�����
			T4L = (65536 - MAIN_Fosc / btl / 4); //��ʱ��4װ��ֵ
			T4H = (65536 - MAIN_Fosc / btl / 4) >> 8; 
			T4T3M |= 0xa0;																 //������ʱ��4��1Tģʽ
			if(isr==1)
			{IE2 |= ES4;}                                  //ʹ�ܴ���4�ж�
	}
	EA=1;            //���������ж�
}

void UART_Send_byte(int pin,unsigned char c)  //���ô���ģ�鷢�͵����ַ�
{
	if(pin==1)
	{
		TI=0;
    SBUF = c;	
		while(!TI);
	}
	if(pin==2)
	{
		S2CON &= ~0x02;
		S2BUF = c;
		while(!(S2CON & 0x02));		
	}
	if(pin==3)
	{
		S3CON &= ~0x02; 
		S3BUF = c;
		while(!(S3CON & 0x02));
	}
	if(pin==4)
	{
		S4CON &= ~0x02;
		S4BUF = c;
		while(!(S4CON & 0x02) );
	}
}

void UART_Send_string(int pin,unsigned char *pt) //���ô���ģ�鷢���ַ���
{
	while(*pt != '\0')
	{
		UART_Send_byte(pin,*pt++);
	}
}