#include <STC32G.H>
#include "USART.H"
#include <stdio.h>

#define PWM_PERIOD  1000   //设置周期值
#define ENO3P       0x10
#define ENO3N       0x20
#define PWM3_1      0x10	//P:P2.4  N:P2.5
unsigned int PWM3_Duty;
unsigned char cnt_H,cnt_L;
unsigned int newcount,oldcount;						//计数值、新计数值
unsigned int number,out;										//数码管计数值
						


float PID(float Sample,float Position); //增量式PID
void PWM_Config();
void Encoder_Check();
void Timer0_Init(void);		//100微秒@12.000MHz



void main()
{
	EAXFR = 1; 									// 使能访问 XFR
	CKCON = 0x00;							  // 设置外部数据总线速度为最快
	WTST = 0x00; 								// 设置程序代码等待参数，赋值为 0 可将 CPU 执行程序的速度设置为最快

	P0M1 = 0x00;P0M0 = 0x00;		//设置P0口为准双向口模式 //00：准双向口 01：推挽输出 10：高阻输入 11：开漏输出
	P1M1 = 0x00;P1M0 = 0xff;		//设置P1口为准双向口模式 //00：准双向口 01：推挽输出 10：高阻输入 11：开漏输出
	P2M1 = 0x00;P2M0 = 0x00;		//设置P2口为准双向口模式 //00：准双向口 01：推挽输出 10：高阻输入 11：开漏输出
	P3M1 = 0x00;P3M0 = 0x00;		//设置P3口为准双向口模式 //00：准双向口 01：推挽输出 10：高阻输入 11：开漏输出
	P4M1 = 0x00;P4M0 = 0x00;		//设置P4口为准双向口模式 //00：准双向口 01：推挽输出 10：高阻输入 11：开漏输出
	P5M1 = 0x00;P5M0 = 0x00;		//设置P5口为准双向口模式 //00：准双向口 01：推挽输出 10：高阻输入 11：开漏输出
	P6M1 = 0x00;P6M0 = 0x00;		//设置P6口为准双向口模式 //00：准双向口 01：推挽输出 10：高阻输入 11：开漏输出
	P7M1 = 0x00;P7M0 = 0x00;		//设置P7口为准双向口模式 //00：准双向口 01：推挽输出 10：高阻输入 11：开漏输出
	
	EA=1;
	PWM_Config();
	UartInit();
//	Timer0_Init();
	PWM3_Duty=100;

	while(1)
	{		

		
			printf("%d\n",newcount);
			
	}		
}
//void Timer0_Isr(void) interrupt 1
//{
//	out=(newcount-oldcount);
//	oldcount=newcount;
//}

//void Timer0_Init(void)		//100微秒@12.000MHz
//{
//	AUXR &= 0x7F;			//定时器时钟12T模式
//	TMOD &= 0xF0;			//设置定时器模式
//	TL0 = 0xF0;				//设置定时初始值
//	TH0 = 0xD8;				//设置定时初始值
//	TF0 = 0;				//清除TF0标志
//	TR0 = 1;				//定时器0开始计时
//	ET0 = 1;				//使能定时器0中断z
//}


//float PID(float expect,float practical) //增量式PID
//{
//	float out;
//	errir = expect - practical;
//	total_errir += errir;
//	ratio = kp * errir;	
//	integral =  total_errir * ki;
//	differential = (errir - last1_errir)*kd;
//	last1_errir = errir;
//	out = ratio + integral + differential;
//	if(integral>1000) integral = 1000;
//	if(integral<-1000) integral = -1000;
//	return out;
//}
float PID(float Sample,float Position)//位置式PID
{
	float Kp =0.04;
	float Ki =0;
	float Kd =0.009;
	float ErrPres,Pias,Out,ErrPres_formerly,ErrPres_lastseen;
	ErrPres=(Position-Sample);
	Pias+=ErrPres;//每次误差的总值
	Out=((ErrPres_formerly-ErrPres)*Kp)+(Pias*Ki)+((ErrPres-2*ErrPres_formerly+	ErrPres_lastseen)*Kd);
	//输出=（上次误差-这次误差）*p  +   误差的总值*i   +    （误差-2*上次误差+上上次误差）*d
	ErrPres_formerly=ErrPres;//上次误差
	ErrPres_lastseen=ErrPres_formerly;//上上次误差
	if(Out>1000)Out=1000;
	if(Out<0)Out=0;
	return Out;
}



void PWM_Config()
{
	PWMA_PS|=0x01	;
	PWMA_PS|=0x04	;
	PWMA_ENO = 0x00;// 配置成 TRGI 的 pin 需关掉 ENO 对应 bit 并配成 input
	
	
	
	PWMA_CCER1 = 0x00;					// 清零CCER，关闭通道
	PWMA_CCER2 = 0x00;					//写 CCMRx 前必须先清零 CCxE 关闭通道
	
	PWMA_CCMR1 = 0x21; 					// 通道模式配置为输入，接编码器 , 滤波器 4 时钟
	PWMA_CCMR2 = 0x21; 					// 通道模式配置为输入，接编码器 , 滤波器 4 时钟
	
//	PWMA_CCMR3 = 0x68;
//    PWMA_CCMR4 = 0x68;
//	
	PWMA_CCER1 = 0x55; 					// 配置通道使能和极性
	PWMA_CCER2 = 0x55; 					// 配置通道使能和极性
	
//	PWMA_SMCR = 0x01; 					// 编码器模式 1
//	PWMA_SMCR = 0x02; 					// 编码器模式 2	
	PWMA_SMCR = 0x03; 					// 编码器模式 3
	

	PWMA_ARRH = (unsigned char)(PWM_PERIOD >> 8); //设置周期时间
    PWMA_ARRL = (unsigned char)PWM_PERIOD;
	
//	PWMA_ENO |= ENO3P; //使能输出
//    PWMA_ENO |= ENO3N; //使能输出
//	  PWMA_PS = 0x00;  //高级 PWM 通道输出脚选择位	
	PWMA_IER = 0x82; 						// 使能中断
	PWMA_CR1 |= 0x81; 					// 使能PWM计数器
}



//========================================================================
// 函数: UpdatePwm(void)
// 描述: 更新PWM占空比. 
// 参数: none.
// 返回: none.
// 版本: V1.0, 2012-11-22
//========================================================================*/
//void UpdatePwm(void)//PWMx_DUTY的值不要超过周期值
//{
////    PWMA_CCR1H = (unsigned int)(PWM1_Duty >> 8); //设置占空比时间
////    PWMA_CCR1L = (unsigned int)(PWM1_Duty);
////    PWMA_CCR2H = (unsigned int)(PWM2_Duty >> 8); //设置占空比时间
////    PWMA_CCR2L = (unsigned int)(PWM2_Duty);
//    PWMA_CCR3H = (unsigned int)(PWM3_Duty >> 8); //设置占空比时间
//    PWMA_CCR3L = (unsigned int)(PWM3_Duty);
////    PWMA_CCR4H = (u8)(PWM4_Duty >> 8); //设置占空比时间
////    PWMA_CCR4L = (u8)(PWM4_Duty);
//}

void PWMA_ISR (void) interrupt 26
{
	if(PWMA_SR1 & 0X02)
	{
	
		cnt_H=PWMA_CCR1H;
		cnt_L=PWMA_CCR1L;
		PWMA_SR1 &=~0X02;
		newcount = cnt_H * 256 + cnt_L;	//获取新的计数器值

	}
}


