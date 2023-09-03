#include "TIME.H"	 
u16 ds_w=0,ds=0,wb=0,wb_w=0,js=0;		   //,js_w=0,TH_1=0,TL_1=0
u8 TL_0=0,TH_0=0;
f32 zhou =0.0;
extern bit qie;
void init()  //初始化函数
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD = 0X51;//TMOD=0x51 5T1 16位计数器 1T0 16定时器
	TH0  = 0;	//高6.5535ms*152=996.132ms
	TL0  = 0;	//低
	TH1  = 0;
	TL1  = 0;
	TR1  = 1;  	//定时器1 开关
	TR0  = 1;	//定时器0 开关
	ET0  = 1;	//允许T0 中断
	ET1  = 1;	//允许T1 中断
	IT0  = 1;	//外部中断0下降沿中断
	EX0  = 1;	//外部中断0允许
	EA   = 1;	//允许所有中断	 	 
}

void time_0()interrupt 1 //T0 定时器  152
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
void int_0()interrupt 0	//外部中断
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
void time_1()interrupt 3 //T1 计数器 
{
	js++;	
}  

