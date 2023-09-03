#include "USART.h"

void UartInit(void)		//9600bps@12.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0xE6;			//设置定时初始值
	T2H = 0xFF;			//设置定时初始值
	AUXR |= 0x10;		//定时器2开始计时
}

void SendByte(unsigned char dat)
{
    SBUF = dat;
    while(!TI);
    TI = 0;
}

char putchar(char character_string)
{
    SendByte(character_string);
    return character_string;
}