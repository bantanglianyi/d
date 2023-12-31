/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

/*************  功能说明    **************

本例程基于STC32G为主控芯片的实验箱进行编写测试。

使用Keil C251编译器，Memory Model推荐设置XSmall模式，默认定义变量在edata，单时钟存取访问速度快。

edata建议保留1K给堆栈使用，空间不够时可将大数组、不常用变量加xdata关键字定义到xdata空间。

高级PWM定时器 PWM1P/PWM1N,PWM2P/PWM2N,PWM3P/PWM3N,PWM4P/PWM4N 每个通道都可独立实现PWM输出，或者两两互补对称输出.

8个通道PWM设置对应P6的8个端口.

通过P6口上连接的8个LED灯，利用PWM实现呼吸灯效果.

PWM周期和占空比可以根据需要自行设置，最高可达65535.

下载时, 选择时钟 24MHz (用户可自行修改频率).

******************************************/

#include "pwm.h"

#define PWMA_PSC 		(12 - 1)	//240分频

//#define PWMB_PSC 		(12 - 1)	//240分频
//****************************** 用户定义宏 ***********************************/


#define PWM1_0      0x00	//P:P1.0  N:P1.1
#define PWM1_1      0x01	//P:P2.0  N:P2.1
#define PWM1_2      0x02	//P:P6.0  N:P6.1

#define PWM2_0      0x00	//P:P1.2/P5.4  N:P1.3
#define PWM2_1      0x04	//P:P2.2  N:P2.3
#define PWM2_2      0x08	//P:P6.2  N:P6.3

#define PWM3_0      0x00	//P:P1.4  N:P1.5
#define PWM3_1      0x10	//P:P2.4  N:P2.5
#define PWM3_2      0x20	//P:P6.4  N:P6.5

#define PWM4_0      0x00	//P:P1.6  N:P1.7
#define PWM4_1      0x40	//P:P2.6  N:P2.7
#define PWM4_2      0x80	//P:P6.6  N:P6.7
#define PWM4_3      0xC0	//P:P3.4  N:P3.3

#define ENO1P       0x01
#define ENO1N       0x02
#define ENO2P       0x04
#define ENO2N       0x08
#define ENO3P       0x10
#define ENO3N       0x20
#define ENO4P       0x40
#define ENO4N       0x80

/*****************************************************************************/





/*************  本地变量声明    **************/


void PWM_Init()
{
	PWMA_PSCRH = (unsigned int)(PWMA_PSC >> 8);
	PWMA_PSCRL = (unsigned int)(PWMA_PSC); 	
	
//	PWMB_PSCRH = (unsigned int)(PWMB_PSC >> 8);
//	PWMB_PSCRL = (unsigned int)(PWMB_PSC); 				//119+1=120预分频


    PWMA_CCER1 = 0x00; //写 CCMRx 前必须先清零 CCxE 关闭通道
    PWMA_CCER2 = 0x00;
    PWMA_CCMR1 = 0x68; //通道模式配置
    PWMA_CCMR2 = 0x68;
    PWMA_CCMR3 = 0x68;
    PWMA_CCMR4 = 0x68;
    PWMA_CCER1 = 0x55; //配置通道输出使能和极性
    PWMA_CCER2 = 0x55;
	
	PWMB_CCER1 = 0x00; // 写 CCMRx 前必须先清零 CCERx 关闭通道
	PWMB_CCER2 = 0x00; 
	PWMB_CCMR1 = 0x70; // 设置 CC5 为 PWM模式2
	PWMB_CCMR2 = 0x70; // 设置 CC6 为 PWM模式2
	PWMB_CCMR3 = 0x70; // 设置 CC7 为 PWM模式2
	PWMB_CCMR4 = 0x70; // 设置 CC8 为 PWM模式2
	PWMB_CCER1 = 0x11; // 使能 CC5 CC6通道
	PWMB_CCER2 = 0x11; // 使能 CC7 CC8通道

    PWMA_ARRH = (unsigned int)(PWMA_PERIOD >> 8); //设置周期时间
    PWMA_ARRL = (unsigned int)PWMA_PERIOD;
	PWMB_ARRH = (unsigned int)(PWMB_PERIOD >> 8); // 设置周期毫秒
	PWMB_ARRL = (unsigned int)(PWMB_PERIOD); 

//    PWMA_ENO = 0x00;
    PWMA_ENO |= ENO1P; //使能输出
    PWMA_ENO |= ENO1N; //使能输出
//    PWMA_ENO |= ENO2P; //使能输出
//    PWMA_ENO |= ENO2N; //使能输出
//    PWMA_ENO |= ENO3P; //使能输出
//    PWMA_ENO |= ENO3N; //使能输出
//    PWMA_ENO |= ENO4P; //使能输出
//    PWMA_ENO |= ENO4N; //使能输出
	//PWMB_ENO = 0x55; // 使能 PWM5 6 7 8 端口输出

	//PWMA_PS = 0x00;  //高级 PWM 通道输出脚选择位
	PWMA_PS |= PWM1_1 ; //选择 PWM1_2 通道
	//PWMA_PS |= PWM2_1; //选择 PWM2_2 通道
//    PWMA_PS |= PWM3_2; //选择 PWM3_2 通道
//    PWMA_PS |= PWM4_2; //选择 PWM4_2 通道
	//PWMB_PS = 0xAA;	

    PWMA_BKR = 0x80;  //使能主输出
	PWMB_BKR = 0x80;
    PWMA_CR1 |= 0x81; //使能ARR预装载,开始计时
	PWMB_CR1 |= 0x81;

}

//========================================================================
// 函数: UpdatePwm(void)
// 描述: 更新PWM占空比. 
// 参数: none.
// 返回: none.
// 版本: V1.0, 2012-11-22
//========================================================================*/
void UpdatePwm(void)//PWMx_DUTY的值不要超过周期值
{
    PWMA_CCR1H = (unsigned int)(PWM1_Duty >> 8); //设置占空比时间
    PWMA_CCR1L = (unsigned int)(PWM1_Duty);
//    PWMA_CCR2H = (unsigned int)(PWM2_Duty >> 8); //设置占空比时间
//    PWMA_CCR2L = (unsigned int)(PWM2_Duty);
//    PWMA_CCR3H = (u8)(PWM3_Duty >> 8); //设置占空比时间
//    PWMA_CCR3L = (u8)(PWM3_Duty);
//    PWMA_CCR4H = (u8)(PWM4_Duty >> 8); //设置占空比时间
//    PWMA_CCR4L = (u8)(PWM4_Duty);
//	  PWMB_CCR5H = (unsigned int)( PWM5_Duty >> 8); // 设置CC5占空比时间 占空比2.5%
//	  PWMB_CCR5L = (unsigned int)(PWM5_Duty ); 
//	  PWMB_CCR6H = (unsigned int)( PWM6_Duty >> 8); // 设置CC5占空比时间 占空比2.5%
//	  PWMB_CCR6L = (unsigned int)(PWM6_Duty ); 
//	  PWMB_CCR7H = (unsigned int)( PWM7_Duty >> 8); // 设置CC5占空比时间 占空比2.5%
//	  PWMB_CCR7L = (unsigned int)(PWM7_Duty ); 
//	  PWMB_CCR8H = (unsigned int)( PWM8_Duty >> 8); // 设置CC5占空比时间 占空比2.5%
//	  PWMB_CCR8L = (unsigned int)(PWM8_Duty ); 
	
}
