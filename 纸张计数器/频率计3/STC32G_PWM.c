#include "STC32G_PWM.h"

#define sys_clk 22118400									//系统频率
#define freqA 500										//A通道pwm频率
#define freqA_div ((sys_clk / freqA) >> 15)				//自动计算A通道分频系数
#define PWMA_period (sys_clk / freqA / (freqA_div + 1))	//自动计算A通道计算周期
//#define PWMA_period	6000	//定义PWMA周期 0~65535
//#define freqA_div 0			//定义周期时不需要分频或者手动输入

#define freqB 1									//B通道pwm频率
#define freqB_div ((sys_clk / freqB) >> 15)				//自动计算B通道分频系数
#define PWMB_period (sys_clk / freqB / (freqB_div + 1))	//自动计算B通道计算周期
//#define PWMB_period	65535	//定义PWMB周期 0~65535
//#define freqB_div 0			//定义周期时不需要分频或者手动输入

u8 PWM_Configuration(u8 PWM, PWMx_InitDefine *PWMx)	//PWM初始化函数
{
	if(PWM == PWM1)
	{
		PWMA_CC1E_Disable();		//关闭输入捕获/比较输出
		PWMA_CC1NE_Disable();		//关闭比较输出
		PWMA_CC1S_Direction(CCAS_OUTPUT);		//CCnS仅在通道关闭时才是可写的
		PWMA_OC1ModeSet(PWMx->PWM_Mode);		//设置输出比较模式

		if(PWMx->PWM_EnoSelect & ENO1P)
		{
			PWMA_CC1E_Enable();			//开启输入捕获/比较输出
			PWMA_ENO |= ENO1P;
		}
		else
		{
			PWMA_CC1E_Disable();		//关闭输入捕获/比较输出
			PWMA_ENO &= ~ENO1P;
		}
		if(PWMx->PWM_EnoSelect & ENO1N)
		{
			PWMA_CC1NE_Enable();		//开启输入捕获/比较输出
			PWMA_ENO |= ENO1N;
		}
		else
		{
			PWMA_CC1NE_Disable();		//关闭输入捕获/比较输出
			PWMA_ENO &= ~ENO1N;
		}
		PWMA_Duty1(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWM2)
	{
		PWMA_CC2E_Disable();		//关闭输入捕获/比较输出
		PWMA_CC2NE_Disable();		//关闭比较输出
		PWMA_CC2S_Direction(CCAS_OUTPUT);		//CCnS仅在通道关闭时才是可写的
		PWMA_OC2ModeSet(PWMx->PWM_Mode);		//设置输出比较模式

		if(PWMx->PWM_EnoSelect & ENO2P)
		{
			PWMA_CC2E_Enable();			//开启输入捕获/比较输出
			PWMA_ENO |= ENO2P;
		}
		else
		{
			PWMA_CC2E_Disable();		//关闭输入捕获/比较输出
			PWMA_ENO &= ~ENO2P;
		}
		if(PWMx->PWM_EnoSelect & ENO2N)
		{
			PWMA_CC2NE_Enable();		//开启输入捕获/比较输出
			PWMA_ENO |= ENO2N;
		}
		else
		{
			PWMA_CC2NE_Disable();		//关闭输入捕获/比较输出
			PWMA_ENO &= ~ENO2N;
		}
		PWMA_Duty2(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWM3)
	{
		PWMA_CC3E_Disable();		//关闭输入捕获/比较输出
		PWMA_CC3NE_Disable();		//关闭比较输出
		PWMA_CC3S_Direction(CCAS_OUTPUT);		//CCnS仅在通道关闭时才是可写的
		PWMA_OC3ModeSet(PWMx->PWM_Mode);		//设置输出比较模式

		if(PWMx->PWM_EnoSelect & ENO3P)
		{
			PWMA_CC3E_Enable();			//开启输入捕获/比较输出
			PWMA_ENO |= ENO3P;
		}
		else
		{
			PWMA_CC3E_Disable();		//关闭输入捕获/比较输出
			PWMA_ENO &= ~ENO3P;
		}
		if(PWMx->PWM_EnoSelect & ENO3N)
		{
			PWMA_CC3NE_Enable();		//开启输入捕获/比较输出
			PWMA_ENO |= ENO3N;
		}
		else
		{
			PWMA_CC3NE_Disable();		//关闭输入捕获/比较输出
			PWMA_ENO &= ~ENO3N;
		}
		PWMA_Duty3(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWM4)
	{
		PWMA_CC4E_Disable();		//关闭输入捕获/比较输出
		PWMA_CC4NE_Disable();		//关闭比较输出
		PWMA_CC4S_Direction(CCAS_OUTPUT);		//CCnS仅在通道关闭时才是可写的
		PWMA_OC4ModeSet(PWMx->PWM_Mode);		//设置输出比较模式

		if(PWMx->PWM_EnoSelect & ENO4P)
		{
			PWMA_CC4E_Enable();			//开启输入捕获/比较输出
			PWMA_ENO |= ENO4P;
		}
		else
		{
			PWMA_CC4E_Disable();		//关闭输入捕获/比较输出
			PWMA_ENO &= ~ENO4P;
		}
		if(PWMx->PWM_EnoSelect & ENO4N)
		{
			PWMA_CC4NE_Enable();		//开启输入捕获/比较输出
			PWMA_ENO |= ENO4N;
		}
		else
		{
			PWMA_CC4NE_Disable();		//关闭输入捕获/比较输出
			PWMA_ENO &= ~ENO4N;
		}
		PWMA_Duty4(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWMA)
	{
//		PWMA_OC1_ReloadEnable(PWMx->PWM_Reload);	//输出比较的预装载使能
//		PWMA_OC1_FastEnable(PWMx->PWM_Fast);		//输出比较快速功能使能
//		PWMA_CCPCAPreloaded(PWMx->PWM_PreLoad);	//捕获/比较预装载控制位(该位只对具有互补输出的通道起作用)
//		PWMA_BrakeEnable(PWMx->PWM_BrakeEnable);	//开启/禁止刹车输入

		PWMA_DeadTime(PWMx->PWM_DeadTime);	//死区发生器设置
		PWMA_AutoReload(PWMx->PWM_Period);	//周期设置
		PWMA_BrakeOutputEnable(PWMx->PWM_MainOutEnable);	//主输出使能
		PWMA_CEN_Enable(PWMx->PWM_CEN_Enable);	//使能计数器
		return	SUCCESS;
	}

	if(PWM == PWM5)
	{
		PWMB_CC5E_Disable();		//关闭输入捕获/比较输出
		PWMB_CC5S_Direction(CCAS_OUTPUT);		//CCnS仅在通道关闭时才是可写的
		PWMB_OC5ModeSet(PWMx->PWM_Mode);		//设置输出比较模式

		if(PWMx->PWM_EnoSelect & ENO5P)
		{
			PWMB_CC5E_Enable();			//开启输入捕获/比较输出
			PWMB_ENO |= ENO5P;
		}
		else
		{
			PWMB_CC5E_Disable();		//关闭输入捕获/比较输出
			PWMB_ENO &= ~ENO5P;
		}
		PWMB_Duty5(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWM6)
	{
		PWMB_CC6E_Disable();		//关闭输入捕获/比较输出
		PWMB_CC6S_Direction(CCAS_OUTPUT);		//CCnS仅在通道关闭时才是可写的
		PWMB_OC6ModeSet(PWMx->PWM_Mode);		//设置输出比较模式

		if(PWMx->PWM_EnoSelect & ENO6P)
		{
			PWMB_CC6E_Enable();			//开启输入捕获/比较输出
			PWMB_ENO |= ENO6P;
		}
		else
		{
			PWMB_CC6E_Disable();		//关闭输入捕获/比较输出
			PWMB_ENO &= ~ENO6P;
		}
		PWMB_Duty6(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWM7)
	{
		PWMB_CC7E_Disable();		//关闭输入捕获/比较输出
		PWMB_CC7S_Direction(CCAS_OUTPUT);		//CCnS仅在通道关闭时才是可写的
		PWMB_OC7ModeSet(PWMx->PWM_Mode);		//设置输出比较模式

		if(PWMx->PWM_EnoSelect & ENO7P)
		{
			PWMB_CC7E_Enable();			//开启输入捕获/比较输出
			PWMB_ENO |= ENO7P;
		}
		else
		{
			PWMB_CC7E_Disable();		//关闭输入捕获/比较输出
			PWMB_ENO &= ~ENO7P;
		}
		PWMB_Duty7(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWM8)
	{
		PWMB_CC8E_Disable();		//关闭输入捕获/比较输出
		PWMB_CC8S_Direction(CCAS_OUTPUT);		//CCnS仅在通道关闭时才是可写的
		PWMB_OC8ModeSet(PWMx->PWM_Mode);		//设置输出比较模式

		if(PWMx->PWM_EnoSelect & ENO8P)
		{
			PWMB_CC8E_Enable();			//开启输入捕获/比较输出
			PWMB_ENO |= ENO8P;
		}
		else
		{
			PWMB_CC8E_Disable();		//关闭输入捕获/比较输出
			PWMB_ENO &= ~ENO8P;
		}
		PWMB_Duty8(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWMB)
	{
//		PWMB_OC5_ReloadEnable(PWMx->PWM_Reload);	//输出比较的预装载使能
//		PWMB_OC5_FastEnable(PWMx->PWM_Fast);		//输出比较快速功能使能
//		PWMB_CCPCBPreloaded(PWMx->PWM_PreLoad);	//捕获/比较预装载控制位(该位只对具有互补输出的通道起作用)
//		PWMB_BrakeEnable(PWMx->PWM_BrakeEnable);	//开启/禁止刹车输入

		PWMB_DeadTime(PWMx->PWM_DeadTime);	//死区发生器设置
		PWMB_AutoReload(PWMx->PWM_Period);	//周期设置
		PWMB_BrakeOutputEnable(PWMx->PWM_MainOutEnable);	//主输出使能
		PWMB_CEN_Enable(PWMx->PWM_CEN_Enable);	//使能计数器
		return	SUCCESS;
	}
	return	FALL;	//错误
}

//void UpdatePwm(u8 PWM, PWMx_Duty *PWMx)	//PWM占空比更新程序
//{
//	switch(PWM)
//	{
//		case PWM1:
//			PWMA_Duty1(PWMx->PWM1_Duty);
//			break;
//		case PWM2:
//			PWMA_Duty2(PWMx->PWM2_Duty);
//			break;
//		case PWM3:
//			PWMA_Duty3(PWMx->PWM3_Duty);
//			break;
//		case PWM4:
//			PWMA_Duty4(PWMx->PWM4_Duty);
//			break;
//		case PWM5:
//			PWMB_Duty5(PWMx->PWM5_Duty);
//			break;
//		case PWM6:
//			PWMB_Duty6(PWMx->PWM6_Duty);
//			break;
//		case PWM7:
//			PWMB_Duty7(PWMx->PWM7_Duty);
//			break;
//		case PWM8:
//			PWMB_Duty8(PWMx->PWM8_Duty);
//			break;
//		case PWMA:
//			PWMA_Duty1(PWMx->PWM1_Duty);
//			PWMA_Duty2(PWMx->PWM2_Duty);
//			PWMA_Duty3(PWMx->PWM3_Duty);
//			PWMA_Duty4(PWMx->PWM4_Duty);
//			break;
//		case PWMB:
//			PWMB_Duty5(PWMx->PWM5_Duty);
//			PWMB_Duty6(PWMx->PWM6_Duty);
//			PWMB_Duty7(PWMx->PWM7_Duty);
//			PWMB_Duty8(PWMx->PWM8_Duty);
//			break;
//		default:break;
//	}
//}

PWMx_Duty PWMA_Duty,PWMB_Duty;
void PWM_init()	//在STC32G_PWM.c中修改配置
{
	PWMx_InitDefine	PWMx_InitStructure;
	PWMA_Prescaler(freqA_div);	//自动分频
	PWMB_Prescaler(freqB_div);	//自动分频
	
	PWMA_Duty.PWM1_Duty = 128;	//PWM占空比时间, 0~Period
	PWMA_Duty.PWM2_Duty = 256;	//PWM占空比时间, 0~Period
	PWMA_Duty.PWM3_Duty = 512;	//PWM占空比时间, 0~Period
	PWMA_Duty.PWM4_Duty = 1024;	//PWM占空比时间, 0~Period
	PWMB_Duty.PWM5_Duty = 128;	//PWM占空比时间, 0~Period
	PWMB_Duty.PWM6_Duty = 256;	//PWM占空比时间, 0~Period
	PWMB_Duty.PWM7_Duty = 512;	//PWM占空比时间, 0~Period
	PWMB_Duty.PWM8_Duty = 1024;	//PWM占空比时间, 0~Period
	//PWMA
	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMA_Duty.PWM1_Duty;	//PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO1N|ENO1P;		//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P，参数同组可以使用或(|)运算
	PWM_Configuration(PWM1, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMA_Duty.PWM2_Duty;	//PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO2P;				//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM2, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMA_Duty.PWM3_Duty;	//PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO3P;				//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM3, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMA_Duty.PWM4_Duty;	//PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect   = ENO4P;				//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM4, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Period = PWMA_period;			//周期时间,   0~65535	24M--12.5k--1920
	PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255		原32usP-48usN -> 设置死区4us -> 28usP--4us低电平--44usN--4us低电平
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable = ENABLE;			//使能计数器, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB
	//PWMB
	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMB_Duty.PWM5_Duty;	//PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO5P;				//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM5, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

//	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
//	PWMx_InitStructure.PWM_Duty = PWMB_Duty.PWM6_Duty;	//PWM占空比时间, 0~Period
//	PWMx_InitStructure.PWM_EnoSelect = ENO6P;				//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
//	PWM_Configuration(PWM6, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

//	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
//	PWMx_InitStructure.PWM_Duty = PWMB_Duty.PWM7_Duty;	//PWM占空比时间, 0~Period
//	PWMx_InitStructure.PWM_EnoSelect = ENO7P;				//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
//	PWM_Configuration(PWM7, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

//	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
//	PWMx_InitStructure.PWM_Duty = PWMB_Duty.PWM8_Duty;	//PWM占空比时间, 0~Period
//	PWMx_InitStructure.PWM_EnoSelect = ENO8P;				//输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
//	PWM_Configuration(PWM8, &PWMx_InitStructure);			//初始化PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Period = PWMB_period;			//周期时间,   0~65535
	PWMx_InitStructure.PWM_DeadTime = 0;					//死区发生器设置, 0~255
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//主输出使能, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable = ENABLE;			//使能计数器, ENABLE,DISABLE
	PWM_Configuration(PWMB, &PWMx_InitStructure);			//初始化PWM通用寄存器,  PWMA,PWMB
	
//	PWM1_USE_P60P61();	//引脚却换
//	PWM2_USE_P62P63();	//引脚却换
//	PWM3_USE_P64P65();	//引脚却换
//	PWM4_USE_P66P67();	//引脚却换
	PWM1_USE_P20P21();
	PWM2_USE_P22P23();
	PWM3_USE_P24P25();
	PWM4_USE_P26P27();
//	PWM5_USE_P20();	//引脚却换
//	PWM6_USE_P21();	//引脚却换
//	PWM7_USE_P22();	//引脚却换
//	PWM8_USE_P23();	//引脚却换
	PWM5_USE_P74();
	PWM6_USE_P75();
//	PWM6_USE_P54();
	PWM7_USE_P76();
	PWM8_USE_P77();
}

void HPWM_Set(u8 PWMchannel,float zkb)	//PWMchannel: 1~8	zkb: 0~1
{
	switch(PWMchannel)
	{
		case PWM1:	//1
			PWMA_Duty.PWM1_Duty = zkb*PWMA_period;	//若以1us脉宽形式调整，将PWMA_period改为 PWMA_period*freqA*0.000001 的值即可
			PWMA_Duty1(PWMA_Duty.PWM1_Duty);
			break;
		case PWM2:
			PWMA_Duty.PWM2_Duty = zkb*PWMA_period;
			PWMA_Duty2(PWMA_Duty.PWM2_Duty);
			break;
		case PWM3:
			PWMA_Duty.PWM3_Duty = zkb*PWMA_period;
			PWMA_Duty3(PWMA_Duty.PWM3_Duty);
			break;
		case PWM4:
			PWMA_Duty.PWM4_Duty = zkb*PWMA_period;
			PWMA_Duty4(PWMA_Duty.PWM4_Duty);
			break;
		case PWM5:
			PWMB_Duty.PWM5_Duty = zkb*PWMB_period;
			PWMB_Duty5(PWMB_Duty.PWM5_Duty);
			break;
		case PWM6:
			PWMB_Duty.PWM6_Duty = zkb*PWMB_period;
			PWMB_Duty6(PWMB_Duty.PWM6_Duty);
			break;
		case PWM7:
			PWMB_Duty.PWM7_Duty = zkb*PWMB_period;
			PWMB_Duty7(PWMB_Duty.PWM7_Duty);
			break;
		case PWM8:
			PWMB_Duty.PWM8_Duty = zkb*PWMB_period;
			PWMB_Duty8(PWMB_Duty.PWM8_Duty);
			break;
		default:break;
	}
}


/*
u8 ReadPWMA(u8 addr)	//异步读取PWMA特殊功能寄存器函数
{
	u8 dat;
	
	while (HSPWMA_ADR &	0x80); //等待前一个异步读写完成
	HSPWMA_ADR = addr |	0x80;  //设置间接访问地址,只需要设置原XFR地址的低7位
								//HSPWMA_ADDR寄存器的最高位写1,表示读数据
	while (HSPWMA_ADR &	0x80); //等待当前异步读取完成
	dat	= HSPWMA_DAT;		   //读取异步数据
	
	return dat;
}

u8 ReadPWMB(u8 addr)	//异步读取PWMB特殊功能寄存器函数
{
	u8 dat;
	
	while (HSPWMB_ADR &	0x80); //等待前一个异步读写完成
	HSPWMB_ADR = addr |	0x80;  //设置间接访问地址,只需要设置原XFR地址的低7位
								//HSPWMB_ADDR寄存器的最高位写1,表示读数据
	while (HSPWMB_ADR &	0x80); //等待当前异步读取完成
	dat	= HSPWMB_DAT;		   //读取异步数据
	
	return dat;
}

void WritePWMA(u8 addr, u8 dat)	//异步读取PWMA特殊功能寄存器函数
{
	while (HSPWMA_ADR &	0x80); //等待前一个异步读写完成
	HSPWMA_DAT = dat;		   //准备需要写入的数据
	HSPWMA_ADR = addr &	0x7f;  //设置间接访问地址,只需要设置原XFR地址的低7位
								//HSPWMA_ADDR寄存器的最高位写0,表示写数据
}

void WritePWMB(u8 addr, u8 dat)	//异步读取PWMB特殊功能寄存器函数
{
	while (HSPWMB_ADR &	0x80); //等待前一个异步读写完成
	HSPWMB_DAT = dat;		   //准备需要写入的数据
	HSPWMB_ADR = addr &	0x7f;  //设置间接访问地址,只需要设置原XFR地址的低7位
								//HSPWMB_ADDR寄存器的最高位写0,表示写数据
}

void HSPWM_Configuration(u8 PWM, HSPWMx_InitDefine *PWMx, PWMx_Duty *DUTYx)	//HSPWM初始化程序
{
	u8 tmpENO,tmpCCER1,tmpCCER2;
	
	if(PWM == PWMA)
	{
		HSPWMA_CFG = 0x03;			//使能PWMA相关寄存器异步访问功能

		if(PWMx->PWM_EnoSelect & ENO1P)
		{
			tmpENO |= ENO1P;
			tmpCCER1 |= 0x01;
		}
		else
		{
			tmpENO &= ~ENO1P;
			tmpCCER1 &= ~0x01;
		}
		if(PWMx->PWM_EnoSelect & ENO1N)
		{
			tmpENO |= ENO1N;
			tmpCCER1 |= 0x04;
		}
		else
		{
			tmpENO &= ~ENO1N;
			tmpCCER1 &= ~0x04;
		}
		if(PWMx->PWM_EnoSelect & ENO2P)
		{
			tmpENO |= ENO2P;
			tmpCCER1 |= 0x10;
		}
		else
		{
			tmpENO &= ~ENO2P;
			tmpCCER1 &= ~0x10;
		}
		if(PWMx->PWM_EnoSelect & ENO2N)
		{
			tmpENO |= ENO2N;
			tmpCCER1 |= 0x40;
		}
		else
		{
			tmpENO &= ~ENO2N;
			tmpCCER1 &= ~0x40;
		}
		if(PWMx->PWM_EnoSelect & ENO3P)
		{
			tmpENO |= ENO3P;
			tmpCCER2 |= 0x01;
		}
		else
		{
			tmpENO &= ~ENO3P;
			tmpCCER2 &= ~0x01;
		}
		if(PWMx->PWM_EnoSelect & ENO3N)
		{
			tmpENO |= ENO3N;
			tmpCCER2 |= 0x04;
		}
		else
		{
			tmpENO &= ~ENO3N;
			tmpCCER2 &= ~0x04;
		}
		if(PWMx->PWM_EnoSelect & ENO4P)
		{
			tmpENO |= ENO4P;
			tmpCCER2 |= 0x10;
		}
		else
		{
			tmpENO &= ~ENO4P;
			tmpCCER2 &= ~0x10;
		}
		if(PWMx->PWM_EnoSelect & ENO4N)
		{
			tmpENO |= ENO4N;
			tmpCCER2 |= 0x40;
		}
		else
		{
			tmpENO &= ~ENO4N;
			tmpCCER2 &= ~0x40;
		}
		
		//通过异步方式设置PWMA的相关寄存器
		WritePWMA((u8)&PWMA_CCER1, 0x00);
		WritePWMA((u8)&PWMA_CCER2, 0x00);
		WritePWMA((u8)&PWMA_CCMR1, CCMRn_PWM_MODE1);				//通道模式配置
		WritePWMA((u8)&PWMA_CCMR2, CCMRn_PWM_MODE1);
		WritePWMA((u8)&PWMA_CCMR3, CCMRn_PWM_MODE1);
		WritePWMA((u8)&PWMA_CCMR4, CCMRn_PWM_MODE1);
		WritePWMA((u8)&PWMA_CCER1, tmpCCER1);						//配置通道输出使能和极性
		WritePWMA((u8)&PWMA_CCER2, tmpCCER2);
		WritePWMA((u8)&PWMA_ENO, tmpENO);							//使能PWM信号输出端口
		WritePWMA((u8)&PWMA_CCR1H, (u8)(DUTYx->PWM1_Duty >> 8));	//设置输出PWM的占空比
		WritePWMA((u8)&PWMA_CCR1L, (u8)DUTYx->PWM1_Duty);
		WritePWMA((u8)&PWMA_CCR2H, (u8)(DUTYx->PWM2_Duty >> 8));	//设置输出PWM的占空比
		WritePWMA((u8)&PWMA_CCR2L, (u8)DUTYx->PWM2_Duty);
		WritePWMA((u8)&PWMA_CCR3H, (u8)(DUTYx->PWM3_Duty >> 8));	//设置输出PWM的占空比
		WritePWMA((u8)&PWMA_CCR3L, (u8)DUTYx->PWM3_Duty);
		WritePWMA((u8)&PWMA_CCR4H, (u8)(DUTYx->PWM4_Duty >> 8));	//设置输出PWM的占空比
		WritePWMA((u8)&PWMA_CCR4L, (u8)DUTYx->PWM4_Duty);
		WritePWMA((u8)&PWMA_ARRH, (u8)(PWMx->PWM_Period >> 8));		//设置输出PWM的周期
		WritePWMA((u8)&PWMA_ARRL, (u8)(PWMx->PWM_Period));
		WritePWMA((u8)&PWMA_DTR, PWMx->PWM_DeadTime);				//设置互补对称输出PWM的死区
		WritePWMA((u8)&PWMA_BRK, PWMx->PWM_MainOutEnable<<7);		//使能主输出
		WritePWMA((u8)&PWMA_CR1, PWMx->PWM_CEN_Enable);				//开始PWM计数
	}
	else if(PWM == PWMB)
	{
		HSPWMB_CFG = 0x03;			//使能PWMB相关寄存器异步访问功能

		if(PWMx->PWM_EnoSelect & ENO5P)
		{
			tmpENO |= ENO5P;
			tmpCCER1 |= 0x01;
		}
		else
		{
			tmpENO &= ~ENO5P;
			tmpCCER1 &= ~0x01;
		}
		if(PWMx->PWM_EnoSelect & ENO6P)
		{
			tmpENO |= ENO6P;
			tmpCCER1 |= 0x10;
		}
		else
		{
			tmpENO &= ~ENO6P;
			tmpCCER1 &= ~0x10;
		}
		if(PWMx->PWM_EnoSelect & ENO7P)
		{
			tmpENO |= ENO7P;
			tmpCCER2 |= 0x01;
		}
		else
		{
			tmpENO &= ~ENO7P;
			tmpCCER2 &= ~0x01;
		}
		if(PWMx->PWM_EnoSelect & ENO8P)
		{
			tmpENO |= ENO8P;
			tmpCCER2 |= 0x10;
		}
		else
		{
			tmpENO &= ~ENO8P;
			tmpCCER2 &= ~0x10;
		}
		
		//通过异步方式设置PWMA的相关寄存器
		WritePWMB((u8)&PWMB_CCER1, 0x00);
		WritePWMB((u8)&PWMB_CCER2, 0x00);
		WritePWMB((u8)&PWMB_CCMR1, CCMRn_PWM_MODE1);				//通道模式配置
		WritePWMB((u8)&PWMB_CCMR2, CCMRn_PWM_MODE1);
		WritePWMB((u8)&PWMB_CCMR3, CCMRn_PWM_MODE1);
		WritePWMB((u8)&PWMB_CCMR4, CCMRn_PWM_MODE1);
		WritePWMB((u8)&PWMB_CCER1, tmpCCER1);						//配置通道输出使能和极性
		WritePWMB((u8)&PWMB_CCER2, tmpCCER2);
		WritePWMB((u8)&PWMB_ENO, tmpENO);							//使能PWM信号输出端口
		WritePWMB((u8)&PWMB_CCR5H, (u8)(DUTYx->PWM5_Duty >> 8));	//设置输出PWM的占空比
		WritePWMB((u8)&PWMB_CCR5L, (u8)DUTYx->PWM5_Duty);
		WritePWMB((u8)&PWMB_CCR6H, (u8)(DUTYx->PWM6_Duty >> 8));	//设置输出PWM的占空比
		WritePWMB((u8)&PWMB_CCR6L, (u8)DUTYx->PWM6_Duty);
		WritePWMB((u8)&PWMB_CCR7H, (u8)(DUTYx->PWM7_Duty >> 8));	//设置输出PWM的占空比
		WritePWMB((u8)&PWMB_CCR7L, (u8)DUTYx->PWM7_Duty);
		WritePWMB((u8)&PWMB_CCR8H, (u8)(DUTYx->PWM8_Duty >> 8));	//设置输出PWM的占空比
		WritePWMB((u8)&PWMB_CCR8L, (u8)DUTYx->PWM8_Duty);
		WritePWMB((u8)&PWMB_ARRH, (u8)(PWMx->PWM_Period >> 8));		//设置输出PWM的周期
		WritePWMB((u8)&PWMB_ARRL, (u8)(PWMx->PWM_Period));
		WritePWMB((u8)&PWMB_DTR, PWMx->PWM_DeadTime);				//设置互补对称输出PWM的死区
		WritePWMB((u8)&PWMB_BRK, PWMx->PWM_MainOutEnable<<7);		//使能主输出
		WritePWMB((u8)&PWMB_CR1, PWMx->PWM_CEN_Enable);				//开始PWM计数
	}
}

void UpdateHSPwm(u8 PWM, PWMx_Duty *PWMx)	//HSPWM占空比更新程序
{
	switch(PWM)
	{
		case PWM1:
			WritePWMA((u8)&PWMA_CCR1H, (u8)(PWMx->PWM1_Duty >> 8));	//设置输出PWM的占空比
			WritePWMA((u8)&PWMA_CCR1L, (u8)PWMx->PWM1_Duty);
			break;
		case PWM2:
			WritePWMA((u8)&PWMA_CCR2H, (u8)(PWMx->PWM2_Duty >> 8));	//设置输出PWM的占空比
			WritePWMA((u8)&PWMA_CCR2L, (u8)PWMx->PWM2_Duty);
			break;
		case PWM3:
			WritePWMA((u8)&PWMA_CCR3H, (u8)(PWMx->PWM3_Duty >> 8));	//设置输出PWM的占空比
			WritePWMA((u8)&PWMA_CCR3L, (u8)PWMx->PWM3_Duty);
			break;
		case PWM4:
			WritePWMA((u8)&PWMA_CCR4H, (u8)(PWMx->PWM4_Duty >> 8));	//设置输出PWM的占空比
			WritePWMA((u8)&PWMA_CCR4L, (u8)PWMx->PWM4_Duty);
			break;
		case PWM5:
			WritePWMB((u8)&PWMB_CCR5H, (u8)(PWMx->PWM5_Duty >> 8));	//设置输出PWM的占空比
			WritePWMB((u8)&PWMB_CCR5L, (u8)PWMx->PWM5_Duty);
			break;
		case PWM6:
			WritePWMB((u8)&PWMB_CCR6H, (u8)(PWMx->PWM6_Duty >> 8));	//设置输出PWM的占空比
			WritePWMB((u8)&PWMB_CCR6L, (u8)PWMx->PWM6_Duty);
			break;
		case PWM7:
			WritePWMB((u8)&PWMB_CCR7H, (u8)(PWMx->PWM7_Duty >> 8));	//设置输出PWM的占空比
			WritePWMB((u8)&PWMB_CCR7L, (u8)PWMx->PWM7_Duty);
			break;
		case PWM8:
			WritePWMB((u8)&PWMB_CCR8H, (u8)(PWMx->PWM8_Duty >> 8));	//设置输出PWM的占空比
			WritePWMB((u8)&PWMB_CCR8L, (u8)PWMx->PWM8_Duty);
			break;
		case PWMA:
			WritePWMA((u8)&PWMA_CCR1H, (u8)(PWMx->PWM1_Duty >> 8));	//设置输出PWM的占空比
			WritePWMA((u8)&PWMA_CCR1L, (u8)PWMx->PWM1_Duty);
			WritePWMA((u8)&PWMA_CCR2H, (u8)(PWMx->PWM2_Duty >> 8));	//设置输出PWM的占空比
			WritePWMA((u8)&PWMA_CCR2L, (u8)PWMx->PWM2_Duty);
			WritePWMA((u8)&PWMA_CCR3H, (u8)(PWMx->PWM3_Duty >> 8));	//设置输出PWM的占空比
			WritePWMA((u8)&PWMA_CCR3L, (u8)PWMx->PWM3_Duty);
			WritePWMA((u8)&PWMA_CCR4H, (u8)(PWMx->PWM4_Duty >> 8));	//设置输出PWM的占空比
			WritePWMA((u8)&PWMA_CCR4L, (u8)PWMx->PWM4_Duty);
			break;
		case PWMB:
			WritePWMB((u8)&PWMB_CCR5H, (u8)(PWMx->PWM5_Duty >> 8));	//设置输出PWM的占空比
			WritePWMB((u8)&PWMB_CCR5L, (u8)PWMx->PWM5_Duty);
			WritePWMB((u8)&PWMB_CCR6H, (u8)(PWMx->PWM6_Duty >> 8));	//设置输出PWM的占空比
			WritePWMB((u8)&PWMB_CCR6L, (u8)PWMx->PWM6_Duty);
			WritePWMB((u8)&PWMB_CCR7H, (u8)(PWMx->PWM7_Duty >> 8));	//设置输出PWM的占空比
			WritePWMB((u8)&PWMB_CCR7L, (u8)PWMx->PWM7_Duty);
			WritePWMB((u8)&PWMB_CCR8H, (u8)(PWMx->PWM8_Duty >> 8));	//设置输出PWM的占空比
			WritePWMB((u8)&PWMB_CCR8L, (u8)PWMx->PWM8_Duty);
			break;
		default:break;
	}
}
*/
/*********************************************************/
