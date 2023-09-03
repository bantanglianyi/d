#include "REG51.H"
#include "STDIO.H"
#include "CKP.H"
/*************** �û�������� *****************************/

#define MAIN_Fosc		22118400L	//define main clock		11059200L

#define Baudrate1		9600		//define the baudrate, ���ʹ��BRT�������ʷ�����,�����ʸ�����2һ��
									//12T mode: 600~115200 for 22.1184MHZ, 300~57600 for 11.0592MHZ

#define Baudrate2		19200		//define the baudrate2,
									//12T mode: 600~115200 for 22.1184MHZ, 300~57600 for 11.0592MHZ

#define		BUF_LENTH	128		//���崮�ڽ��ջ��峤��

/**********************************************************/




sfr AUXR1 = 0xA2;
sfr	AUXR  = 0x8E;
sfr S2CON = 0x9A;	//12C5A60S2˫����ϵ��
sfr S2BUF = 0x9B;	//12C5A60S2˫����ϵ��
sfr IE2   = 0xAF;	//STC12C5A60S2ϵ��
sfr BRT   = 0x9C;

unsigned char 	uart1_wr;		//дָ��
unsigned char 	uart1_rd;		//��ָ��
unsigned char 	xdata RX1_Buffer[BUF_LENTH];
bit		B_TI;

unsigned char 	uart2_wr;		//дָ��
unsigned char 	uart2_rd;		//��ָ��
unsigned char 	xdata RX2_Buffer[BUF_LENTH];
bit		B_TI2;


/****************** �������Զ����ɣ��û������޸� ************************************/

#define T1_TimerReload	(256 - MAIN_Fosc / 192 / Baudrate1)			//Calculate the timer1 reload value	at 12T mode
#define BRT_Reload		(256 - MAIN_Fosc / 12 / 16 / Baudrate2)		//Calculate BRT reload value

#define	TimeOut1		(28800 / (unsigned long)Baudrate1 + 2)
#define	TimeOut2		(28800 / (unsigned long)Baudrate2 + 2)

#define	TI2				(S2CON & 0x02) != 0
#define	RI2				(S2CON & 0x01) != 0
#define	CLR_TI2()		S2CON &= ~0x02
#define	CLR_RI2()		S2CON &= ~0x01

/**********************************************************/

/******************** ���غ������� ***************/
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


void PrintString1(char  *puts)		//����һ���ַ���
{
    for (; *puts != 0;	puts++)  UART1_TxByte(*puts); 	//����ֹͣ��0����
}



char putchar(char c)
{
    UART1_TxByte(c);
    return c;
}

void	uart1_init(void)
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON  = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//���������ʷ�����ʱ��ΪFosc,��1T
	BRT   = 0xfa;		//�趨���������ʷ�������װֵ		 0xFD 11����
	AUXR |= 0x01;		//����1ѡ����������ʷ�����Ϊ�����ʷ�����
	AUXR |= 0x10;		//�������������ʷ�����
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



