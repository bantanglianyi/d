#include "UART.h"


void UART_init(int pin,unsigned long btl,int isr)
{
	if(pin==1)		//串口1
	{
      P_SW1 |= 0x00;   //串口1引脚切换到 P30.P31
		  SCON = 0x50;    //串口1工作模式为0，8位数据模式
		  AUXR &= 0xFE;   //串口1选择定时器1作为波特率发生器
		  TMOD |= 0x00;    
			TL1 = (65536 - MAIN_Fosc / btl / 4); //定时器2装初值
			TH1 = (65536 - MAIN_Fosc / btl / 4) >> 8; 
			TR1 = 1;																 //启动定时器1
			AUXR |= 0x40;                            //定时器1，1T模式
			if(isr==1)
			{ES = 1;}                                  //使能串口1中断
	}
	if(pin ==2) 
	{
			P_SW2 |= 0x01;   //串口2引脚切换到 P40.P42
		  S2CON = 0x10;    //串口2选择定时器2作为波特率发生器
			T2L = (65536 - MAIN_Fosc / btl / 4); //定时器2装初值
			T2H = (65536 - MAIN_Fosc / btl / 4) >> 8; 
			AUXR |= 0x14;																 //启动定时器2，1T模式
			if(isr==1)
			{IE2 |= ES2;}                                  //使能串口2中断
	}
	if(pin ==3) 
	{
			P_SW2 |= 0x02;   //串口3引脚切换到 P50.P51
		  S3CON = 0x50;    //串口3选择定时器3作为波特率发生器
			T3L = (65536 - MAIN_Fosc / btl / 4); //定时器3装初值
			T3H = (65536 - MAIN_Fosc / btl / 4) >> 8; 
			T4T3M |= 0x0a;																 //启动定时器3，1T模式
			if(isr==1)
			{IE2 |= ES3;}                                  //使能串口3中断
	}
	if(pin ==4) 
	{
			P_SW2 |= 0x04;   //串口4引脚切换到 P52.P53
		  S4CON = 0x50;    //串口4选择定时器4作为波特率发生器
			T4L = (65536 - MAIN_Fosc / btl / 4); //定时器4装初值
			T4H = (65536 - MAIN_Fosc / btl / 4) >> 8; 
			T4T3M |= 0xa0;																 //启动定时器4，1T模式
			if(isr==1)
			{IE2 |= ES4;}                                  //使能串口4中断
	}
	EA=1;            //允许所有中断
}

void UART_Send_byte(int pin,unsigned char c)  //调用串口模块发送单个字符
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

void UART_Send_string(int pin,unsigned char *pt) //调用串口模块发送字符串
{
	while(*pt != '\0')
	{
		UART_Send_byte(pin,*pt++);
	}
}