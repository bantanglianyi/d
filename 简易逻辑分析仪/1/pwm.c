/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

/*************  ����˵��    **************

�����̻���STC32GΪ����оƬ��ʵ������б�д���ԡ�

ʹ��Keil C251��������Memory Model�Ƽ�����XSmallģʽ��Ĭ�϶��������edata����ʱ�Ӵ�ȡ�����ٶȿ졣

edata���鱣��1K����ջʹ�ã��ռ䲻��ʱ�ɽ������顢�����ñ�����xdata�ؼ��ֶ��嵽xdata�ռ䡣

�߼�PWM��ʱ�� PWM1P/PWM1N,PWM2P/PWM2N,PWM3P/PWM3N,PWM4P/PWM4N ÿ��ͨ�����ɶ���ʵ��PWM������������������Գ����.

8��ͨ��PWM���ö�ӦP6��8���˿�.

ͨ��P6�������ӵ�8��LED�ƣ�����PWMʵ�ֺ�����Ч��.

PWM���ں�ռ�ձȿ��Ը�����Ҫ�������ã���߿ɴ�65535.

����ʱ, ѡ��ʱ�� 24MHz (�û��������޸�Ƶ��).

******************************************/

#include "pwm.h"

#define PWMA_PSC 		(12 - 1)	//240��Ƶ

//#define PWMB_PSC 		(12 - 1)	//240��Ƶ
//****************************** �û������ ***********************************/


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





/*************  ���ر�������    **************/


void PWM_Init()
{
	PWMA_PSCRH = (unsigned int)(PWMA_PSC >> 8);
	PWMA_PSCRL = (unsigned int)(PWMA_PSC); 	
	
//	PWMB_PSCRH = (unsigned int)(PWMB_PSC >> 8);
//	PWMB_PSCRL = (unsigned int)(PWMB_PSC); 				//119+1=120Ԥ��Ƶ


    PWMA_CCER1 = 0x00; //д CCMRx ǰ���������� CCxE �ر�ͨ��
    PWMA_CCER2 = 0x00;
    PWMA_CCMR1 = 0x68; //ͨ��ģʽ����
    PWMA_CCMR2 = 0x68;
    PWMA_CCMR3 = 0x68;
    PWMA_CCMR4 = 0x68;
    PWMA_CCER1 = 0x55; //����ͨ�����ʹ�ܺͼ���
    PWMA_CCER2 = 0x55;
	
	PWMB_CCER1 = 0x00; // д CCMRx ǰ���������� CCERx �ر�ͨ��
	PWMB_CCER2 = 0x00; 
	PWMB_CCMR1 = 0x70; // ���� CC5 Ϊ PWMģʽ2
	PWMB_CCMR2 = 0x70; // ���� CC6 Ϊ PWMģʽ2
	PWMB_CCMR3 = 0x70; // ���� CC7 Ϊ PWMģʽ2
	PWMB_CCMR4 = 0x70; // ���� CC8 Ϊ PWMģʽ2
	PWMB_CCER1 = 0x11; // ʹ�� CC5 CC6ͨ��
	PWMB_CCER2 = 0x11; // ʹ�� CC7 CC8ͨ��

    PWMA_ARRH = (unsigned int)(PWMA_PERIOD >> 8); //��������ʱ��
    PWMA_ARRL = (unsigned int)PWMA_PERIOD;
	PWMB_ARRH = (unsigned int)(PWMB_PERIOD >> 8); // �������ں���
	PWMB_ARRL = (unsigned int)(PWMB_PERIOD); 

//    PWMA_ENO = 0x00;
    PWMA_ENO |= ENO1P; //ʹ�����
    PWMA_ENO |= ENO1N; //ʹ�����
//    PWMA_ENO |= ENO2P; //ʹ�����
//    PWMA_ENO |= ENO2N; //ʹ�����
//    PWMA_ENO |= ENO3P; //ʹ�����
//    PWMA_ENO |= ENO3N; //ʹ�����
//    PWMA_ENO |= ENO4P; //ʹ�����
//    PWMA_ENO |= ENO4N; //ʹ�����
	//PWMB_ENO = 0x55; // ʹ�� PWM5 6 7 8 �˿����

	//PWMA_PS = 0x00;  //�߼� PWM ͨ�������ѡ��λ
	PWMA_PS |= PWM1_1 ; //ѡ�� PWM1_2 ͨ��
	//PWMA_PS |= PWM2_1; //ѡ�� PWM2_2 ͨ��
//    PWMA_PS |= PWM3_2; //ѡ�� PWM3_2 ͨ��
//    PWMA_PS |= PWM4_2; //ѡ�� PWM4_2 ͨ��
	//PWMB_PS = 0xAA;	

    PWMA_BKR = 0x80;  //ʹ�������
	PWMB_BKR = 0x80;
    PWMA_CR1 |= 0x81; //ʹ��ARRԤװ��,��ʼ��ʱ
	PWMB_CR1 |= 0x81;

}

//========================================================================
// ����: UpdatePwm(void)
// ����: ����PWMռ�ձ�. 
// ����: none.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================*/
void UpdatePwm(void)//PWMx_DUTY��ֵ��Ҫ��������ֵ
{
    PWMA_CCR1H = (unsigned int)(PWM1_Duty >> 8); //����ռ�ձ�ʱ��
    PWMA_CCR1L = (unsigned int)(PWM1_Duty);
//    PWMA_CCR2H = (unsigned int)(PWM2_Duty >> 8); //����ռ�ձ�ʱ��
//    PWMA_CCR2L = (unsigned int)(PWM2_Duty);
//    PWMA_CCR3H = (u8)(PWM3_Duty >> 8); //����ռ�ձ�ʱ��
//    PWMA_CCR3L = (u8)(PWM3_Duty);
//    PWMA_CCR4H = (u8)(PWM4_Duty >> 8); //����ռ�ձ�ʱ��
//    PWMA_CCR4L = (u8)(PWM4_Duty);
//	  PWMB_CCR5H = (unsigned int)( PWM5_Duty >> 8); // ����CC5ռ�ձ�ʱ�� ռ�ձ�2.5%
//	  PWMB_CCR5L = (unsigned int)(PWM5_Duty ); 
//	  PWMB_CCR6H = (unsigned int)( PWM6_Duty >> 8); // ����CC5ռ�ձ�ʱ�� ռ�ձ�2.5%
//	  PWMB_CCR6L = (unsigned int)(PWM6_Duty ); 
//	  PWMB_CCR7H = (unsigned int)( PWM7_Duty >> 8); // ����CC5ռ�ձ�ʱ�� ռ�ձ�2.5%
//	  PWMB_CCR7L = (unsigned int)(PWM7_Duty ); 
//	  PWMB_CCR8H = (unsigned int)( PWM8_Duty >> 8); // ����CC5ռ�ձ�ʱ�� ռ�ձ�2.5%
//	  PWMB_CCR8L = (unsigned int)(PWM8_Duty ); 
	
}
