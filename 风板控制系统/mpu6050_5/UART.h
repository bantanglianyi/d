
#include <STC32G.H>
#define MAIN_Fosc 11059200
extern void UART_init(int pin,unsigned long btl,int isr); //UARTģ���ʼ������
/*
ȡֵ��p:Ҫ��ʼ��ͨ��       ����1 Ϊ ����ģ��ͨ��1	����ΪRXD=P3.0��TXD=P3.1
														   2 Ϊ ����ģ��ͨ��2 ����ΪRXD=P4.0��TXD=P4.2
															 3 Ϊ ����ģ��ͨ��3	����ΪRXD=P5.0��TXD=P5.1
														   4 Ϊ ����ģ��ͨ��4 ����ΪRXD=P5.2��TXD=P5.3
ȡֵ��btl:UARTͨ�Ų�����   ����  ȡֵ��Χ��2400,4800.9600.19200.38400.115200
													 ע�⣺����ȡ������ֵ
ȡֵ��isr:�Ƿ�򿪴����ж� ����0 Ϊ ���򿪽����ж�
														   1 Ϊ �򿪽����ж� 
*/


extern void UART_Send_string(int pin,unsigned char *pt);   //UARTģ�鷢��һ���ַ���
/*	
ȡֵ��pin:Ҫʹ�õĴ���      ����1 Ϊ ����ģ��ͨ��1
														    2 Ϊ ����ģ��ͨ��2 
																3 Ϊ ����ģ��ͨ��3	
														    4 Ϊ ����ģ��ͨ��4 
ȡֵ��*pt:									Ҫ���͵��ַ�����Ϣ 
*/

extern void UART_Send_byte(int pin,unsigned char c);		 //UARTģ�鷢��һ���ַ�
/*
ȡֵ��pin:Ҫʹ�õĴ���     ����1 Ϊ ����ģ��ͨ��1
														   2 Ϊ ����ģ��ͨ��2 
															 3 Ϊ ����ģ��ͨ��3	
														   4 Ϊ ����ģ��ͨ��4 
ȡֵ��c:									 Ҫ���͵��ַ���Ϣ 
*/