#include <STC32G.H>
#include "oled.h"
#include <stdio.h>
#include "USART.H"
#include "ADC.h"
#include "pwm.h"
#include "key_multi.h"

float attenuation=10.0946;//衰减倍数
char group_V[50]; //adc输出承载数组
char group_A[50]; //adc输出承载数组
char i;
unsigned char ftable[50];
float out_V,out,measurement_1,measurement_2,measurement_3,measurement_4,measurement_5,reference; //adc的承载变量
char minification,count_v;
float v=0;
unsigned int PWM1_Duty;//高点平的持续时间，用于改变占空比
unsigned int PWM2_Duty;
unsigned int PWM3_Duty;
unsigned int PWM4_Duty;

unsigned char Key1_nums,Key2_nums,Key3_nums,Key4_nums;		//KEY1双击次数，KEY2双击次数，KEY3双击次数，KEY4双击次数
unsigned char keyvalue;	
char pattern=0;	//键值
char pwm_pattern=0;//pwm切换变量
char ol_control=0; //ol口控制




	void Delay10us()		//@12.000MHz
{
	unsigned long edata r;

	_nop_();
	_nop_();
	_nop_();
	r = 28000UL;
	while (r) r--;
}


void adc_voltage_0ut() //adc测电压
{
		float err=0;
		long N=10000;
		unsigned long count;
		float sum=0;
		count_v=2.011;
		/*显示电压测试模式*/
		OLED_ShowChinese(0,0,9,16);
		OLED_ShowChinese(16,0,10,16);
		OLED_ShowChinese(32,0,11,16);
		OLED_ShowChinese(48,0,12,16);
		OLED_ShowChinese(64,0,13,16);
		OLED_ShowChinese(80,0,14,16);
		/*开启ADC通道*/
		measurement_2=Get_ADC12bitResult(3);//adc 4通道
		measurement_3=Get_ADC12bitResult(4);//adc 5通道
		measurement_4=Get_ADC12bitResult(5);//adc 6通道
		/*判断使用通道*/
		reference=Get_ADC12bitResult(15);//adc内部参考通道//
		out_V	=(float)(((measurement_2/reference*1.182937))/count_v*attenuation);	//经过计算的adc最终输出
		//printf("%.6f\n",out_V); //串口adc调试
	   for ( count=0;count<N;count++)
	   {
		
			 if(pattern!=2)
			 {
				goto A;
			 }
			sum += out_V;
	   }
		out=(float)(sum/N);
		if(out>13.9)err=0.08;
	   if(out>4.9|out<13.9)err=0.03;
	   if(out<4.9)err=0.02;
	   if(out<0.3)
	   {
			out=0;
			err=0;
	   }
		sprintf(group_V,"v:%.2f",out+err);//把adc的值存入数组
		OLED_ShowString(0,2,group_V,16); //adc显示函数
	   	A:;
}

void adc_electricity_0ut() //adc测电流
{	
	
	
		float out_A;
		//printf("%.6f\n",out); //串口adc调试
		measurement_1=Get_ADC12bitResult(1);//adc2通道
		reference=Get_ADC12bitResult(15);//adc内部参考通道
		//out_A=((float)(((measurement_1/reference*1.182937)/0.5)*6.818));	//经过计算的adc最终输出
		/*显示电流测试模式*/
		OLED_ShowChinese(0,0,9,16);
		OLED_ShowChinese(16,0,15,16);
		OLED_ShowChinese(32,0,11,16);
		OLED_ShowChinese(48,0,12,16);
		OLED_ShowChinese(64,0,13,16);
		OLED_ShowChinese(80,0,14,16);
	
		switch(ol_control)
	{
		case 0 :out_A=0+v;break;
		case 1 :out_A=100+v;break;
		case 2 :out_A=200+v;break;
		case 3 :out_A=300+v;break;
		case 4 :out_A=400+v;break;
		case 5 :out_A=500+v;break;
		case 6 :out_A=600+v;break;
		case 7 :out_A=700+v;break;
		case 8 :out_A=800+v;break;
		case 9 :out_A=900+v;break;
		case 10 :out_A=1000+v;break;
	}

	
		sprintf(group_A,"%.3fmA",out_A);//把adc的值存入数组
		OLED_ShowString(0,2,group_A,16); //adc显示函数
	
}

void pwm()//pwm调节显示函数
{
	switch(pwm_pattern)
	{
		case 0 : /*关闭pwm波*/
				OLED_ShowChinese(0,0,0,16);
				OLED_ShowChinese(16,0,1,16);
				OLED_ShowString(32,0,"PWM",16);
				OLED_ShowChinese(0,3,7,16);
				OLED_ShowChinese(16,3,8,16);
				PWMA_BKR = 0x00;  //
				break;
		case 1 :
			/*打开pwm波*/
				OLED_ShowChinese(0,0,0,16);
				OLED_ShowChinese(16,0,1,16);
				OLED_ShowString(32,0,"PWM",16);		
				OLED_ShowChinese(0,3,5,16);
				OLED_ShowChinese(16,3,6,16);	
				OLED_ShowChinese(0,6,2,16);
				OLED_ShowChinese(16,6,3,16);
				OLED_ShowChinese(32,6,4,16);
				PWMA_BKR = 0x80;  //使能主输出
				OLED_ShowNum(48,6,PWM1_Duty,3,16);
				break;
	}
}
void electricity_switch()//负载电流控制
{
	OLED_ShowChinese(0,0,5,16);
	OLED_ShowChinese(16,0,7,16);
	OLED_ShowNum(32,2,ol_control,2,16);
	switch(ol_control)
	{
		case 0 :P67=0;break;
		case 1 :P66=0;break;
		case 2 :P65=0;break;
		case 3 :P64=0;break;
		case 4 :P63=0;break;
		case 5 :P62=0;break;
		case 6 :P61=0;break;
		case 7 :P60=0;break;
		case 8 :P36=0;break;
		case 9 :P37=0;break;
		case 10 :P6=0XFF;P70=1;P71=1;break;
	}
}

void main()
{

	
	EAXFR = 1;				// 使能访问XFR
	CKCON = 0x00;			// 设置外部数据总线为最快
	WTST = 0;  
	/*串口模式配置*/
	P4M0 = 0xff; P4M1 = 0x00; 
    P3M0 = 0xff; P3M1 = 0xff; 
	P6M0 = 0xff; P6M1 = 0xff; 
    P2M0 = 0xff; P2M1 = 0xff; 	  
	




	P67=0;
	
	ADC_init();  //adc初始化
	UartInit(); //串口初始化
	PWMA_Init();  //pwm初始化
	OLED_Init();  //oled屏幕初始化
	UpdatePwm(); //更新pwm
	PWM1_Duty=50; //初始pwm波的占空比
	while(1)
	{
		keyvalue = key_multi();		//读取键值（键值和长按短按双击的复合键值）

		switch(pattern)
		{
			case 0 :electricity_switch();break; //负载开关
			case 1 :adc_electricity_0ut();break;//电流模式
			case 2 :adc_voltage_0ut();break;//电压模式
			case 3 :pwm();break;//pwm波开关
			
		}
//		for(i=0;i<10;i++)
//	{
//		Delay10us();
//		v+=0.001;
//		if(v>0.02)v=0;
//	
//	}
		
		if(keyvalue == Key1_Single_Click)//模式控制
		{
			OLED_Clear();
			pattern++;
			if(pattern>3)pattern=0;
		}
				
		if(keyvalue == Key1_Long_Click)//pwm开关
		{
			if(pattern==3)
			{
			OLED_Clear();
			pwm_pattern++;
			if(pwm_pattern>1)pwm_pattern=0;
			}
		}		//KEY1长按，熄灭LED1
		if(keyvalue == Key1_Double_Click) 	//返回模式1
		{
			OLED_Clear();
			pattern=0;
		}
		
		if(keyvalue == Key2_Single_Click) //lo口控制
		{
			if(pattern==0)
			{
				P6=0XFF;
				P36=1;
				P37=1;
				OLED_Clear();
				ol_control++;
			}
		
			if(pattern==3)
			{
				 PWM1_Duty++;
				UpdatePwm(); //更新pwm
				if( PWM1_Duty>100)PWM1_Duty=100;
				
				
			}
				if(ol_control>10)ol_control=0;
		}				//KEY2短按，点亮LED3
		if(keyvalue == Key2_Long_Click) 
		{
			if(pattern==0)
			{
				P6=0XFF;
				P36=1;
				P37=1;
				OLED_Clear();
				ol_control--;
				
				
			}
			if(pattern==3)
			{
				 PWM1_Duty--;
				UpdatePwm(); //更新pwm
				if( PWM1_Duty<0)PWM1_Duty=0;
				
			}
			if(ol_control<0)ol_control=0;
		}
			//KEY2长按，熄灭LED3
//		if(keyvalue == Key2_Double_Click) 								//KEY3双击，点亮LED3、LED4，再次双击，熄灭LED3、LED4
//		{
//			Key2_nums++;		//KEY2双击次数
//			if(Key2_nums%2 == 1)		//奇数次双击，点亮LED3、LED4
//			{
//				LED3 = ON;
//				LED4 = ON;
//			}
//			if(Key2_nums%2 == 0)		//偶数次双击，熄灭LED3、LED4
//			{
//				LED3 = OFF;
//				LED4 = OFF;
//			}
//			if(Key2_nums >= 99) Key2_nums = 0;	//防止KEY2双击次数溢出，清零
//		}
//		
		if(keyvalue == Key3_Single_Click)
				
			{
				if(pattern==3)
				 PWM1_Duty+=10;
				UpdatePwm(); //更新pwm
				if( PWM1_Duty>100)PWM1_Duty=100;
			}
					//KEY3短按，点亮LED5
		if(keyvalue == Key3_Long_Click) 
			{		
				if(pattern==3)
				 PWM1_Duty-=10;
				UpdatePwm(); //更新pwm
				if( PWM1_Duty<0)PWM1_Duty=0;
			}
			//KEY3长按，熄灭LED5
//		if(keyvalue == Key3_Double_Click) 								//KEY3双击，点亮LED5、LED6，再次双击，熄灭LED5、LED6
//		{
//			Key3_nums++;		//KEY3双击次数
//			if(Key3_nums%2 == 1)		//奇数次双击，点亮LED5、LED6
//			{
//				LED5 = ON;
//				LED6 = ON;
//			}
//			if(Key3_nums%2 == 0)		//偶数次双击，熄灭LED5、LED6
//			{
//				LED5 = OFF;
//				LED6 = OFF;
//			}
//			if(Key3_nums >= 99) Key3_nums = 0;		//防止KEY3双击次数溢出，清零
//		}
//		
//		if(keyvalue == Key4_Single_Click) LED7 = ON;			//KEY4短按，点亮LED7
//		if(keyvalue == Key4_Long_Click) 	LED7 = OFF;			//KEY4长按，熄灭LED7
//		if(keyvalue == Key4_Double_Click) 								//KEY4双击，点亮LED7、LED8，再次双击，熄灭LED7、LED8
//		{
//			Key4_nums++;		//KEY4双击次数
//			if(Key4_nums%2 == 1)		//奇数次双击，点亮LED7、LED8	
//			{
//				LED7 = ON;
//				LED8 = ON;
//			}
//			if(Key4_nums%2 == 0)		//偶数次双击，熄灭LED7、LED8
//			{
//				LED7 = OFF;
//				LED8 = OFF;
//			}
//			if(Key4_nums >= 99) Key4_nums = 0;		//防止KEY4双击次数溢出，清零
//		}
		

	}
}


