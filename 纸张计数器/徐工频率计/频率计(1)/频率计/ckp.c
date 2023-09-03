#include "REG51.H"
#include "STDIO.H"
#include "CKP.H"
/*************** 用户定义参数 *****************************/

#define MAIN_Fosc		22118400L	//define main clock		11059200L

#define Baudrate1		9600		//define the baudrate, 如果使用BRT做波特率发生器,则波特率跟串口2一样
									//12T mode: 600~115200 for 22.1184MHZ, 300~57600 for 11.0592MHZ

#define Baudrate2		19200		//define the baudrate2,
									//12T mode: 600~115200 for 22.1184MHZ, 300~57600 for 11.0592MHZ

#define		BUF_LENTH	128		//定义串口接收缓冲长度

/**********************************************************/




sfr AUXR1 = 0xA2;
sfr	AUXR  = 0x8E;
sfr S2CON = 0x9A;	//12C5A60S2双串口系列
sfr S2BUF = 0x9B;	//12C5A60S2双串口系列
sfr IE2   = 0xAF;	//STC12C5A60S2系列
sfr BRT   = 0x9C;

unsigned char 	uart1_wr;		//写指针
unsigned char 	uart1_rd;		//读指针
unsigned char 	xdata RX1_Buffer[BUF_LENTH];
bit		B_TI;

unsigned char 	uart2_wr;		//写指针
unsigned char 	uart2_rd;		//读指针
unsigned char 	xdata RX2_Buffer[BUF_LENTH];
bit		B_TI2;


/****************** 编译器自动生成，用户请勿修改 ************************************/

#define T1_TimerReload	(256 - MAIN_Fosc / 192 / Baudrate1)			//Calculate the timer1 reload value	at 12T mode
#define BRT_Reload		(256 - MAIN_Fosc / 12 / 16 / Baudrate2)		//Calculate BRT reload value

#define	TimeOut1		(28800 / (unsigned long)Baudrate1 + 2)
#define	TimeOut2		(28800 / (unsigned long)Baudrate2 + 2)

#define	TI2				(S2CON & 0x02) != 0
#define	RI2				(S2CON & 0x01) != 0
#define	CLR_TI2()		S2CON &= ~0x02
#define	CLR_RI2()		S2CON &= ~0x01

/**********************************************************/

/******************** 本地函数声明 ***************/
void	uart1_init(void);
void	uart2_init(void);
void	UART1_TxByte(unsigned char dat);
void	UART2_TxByte(unsigned char dat);
void	PrintString1(char  *puts);
void	PrintString2(unsigned char code *puts);
char    putchar(char c);
unsigned char x,h;
//extern int adc1,ci=0;
//extern char b=0,a=0,i=0;
//void Delay10ms(x)		//@11.0592MHz
//{
//	unsigned char i, j;
//	for(i=x;i>0;i--)
//		for(j=110;j>0;j--);
//}




void	UART1_TxByte(unsigned char dat)
{
	B_TI = 0;
	SBUF = dat;
	while(!B_TI);
	B_TI = 0;
}


void PrintString1(char  *puts)		//发送一串字符串
{
    for (; *puts != 0;	puts++)  UART1_TxByte(*puts); 	//遇到停止符0结束
}



char putchar(char c)
{
    UART1_TxByte(c);
    return c;
}

void	uart1_init(void)
{
	PCON &= 0x7F;		//波特率不倍速
	SCON  = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
	BRT   = 0xfa;		//设定独立波特率发生器重装值		 0xFD 11晶振
	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
	ES    = 1;
	EA    = 1;
}



/**********************************************/
void UART0_RCV (void) interrupt 4
{
	if(RI)
	{
		RI = 0;
		RX1_Buffer[uart1_wr] = SBUF;
		if(++uart1_wr >= BUF_LENTH)	uart1_wr = 0;
	}

	if(TI)
	{
		TI = 0;
		B_TI = 1;
	}
}



