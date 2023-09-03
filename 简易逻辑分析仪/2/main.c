#include <STC32G.H>
#include <stdio.h>
char count=0;
bit INT0_judge=0;
char time_series[]={0XA0,0X50,0X28,0X14,0X0A,0X05,0X82,0X41};
void main()
{
	
	EAXFR=1;
	CKCON=0X00;
	WTST=0X00;
	
	P6M0 = 0x00; P6M1 = 0x00; 

	IT0 = 0;      
	EX0 = 1;      //打开外部中断1
	EA=1;
	while(1)
	{
		P6=time_series[count];
	}
}


void INT0_Routine() interrupt 0
{
	if(INT0_judge==0)
	{
		INT0_judge=1;
		count++;
		if(count>=8)
		{
			count=0;
		}
	}
	else if(INT0_judge==1)
	{
		INT0_judge=0;
	}
}

