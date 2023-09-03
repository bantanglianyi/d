
#include <STC32G.H>
#define MAIN_Fosc 11059200
extern void UART_init(int pin,unsigned long btl,int isr); //UART模块初始化函数
/*
取值：p:要初始化通道       例：1 为 串口模块通道1	引脚为RXD=P3.0和TXD=P3.1
														   2 为 串口模块通道2 引脚为RXD=P4.0和TXD=P4.2
															 3 为 串口模块通道3	引脚为RXD=P5.0和TXD=P5.1
														   4 为 串口模块通道4 引脚为RXD=P5.2和TXD=P5.3
取值：btl:UART通信波特率   例：  取值范围：2400,4800.9600.19200.38400.115200
													 注意：不能取其他数值
取值：isr:是否打开串口中断 例：0 为 不打开接收中断
														   1 为 打开接收中断 
*/


extern void UART_Send_string(int pin,unsigned char *pt);   //UART模块发送一个字符串
/*	
取值：pin:要使用的串口      例：1 为 串口模块通道1
														    2 为 串口模块通道2 
																3 为 串口模块通道3	
														    4 为 串口模块通道4 
取值：*pt:									要发送的字符串信息 
*/

extern void UART_Send_byte(int pin,unsigned char c);		 //UART模块发送一个字符
/*
取值：pin:要使用的串口     例：1 为 串口模块通道1
														   2 为 串口模块通道2 
															 3 为 串口模块通道3	
														   4 为 串口模块通道4 
取值：c:									 要发送的字符信息 
*/