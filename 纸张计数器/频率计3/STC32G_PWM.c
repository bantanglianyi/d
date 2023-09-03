#include "STC32G_PWM.h"

#define sys_clk 22118400									//ϵͳƵ��
#define freqA 500										//Aͨ��pwmƵ��
#define freqA_div ((sys_clk / freqA) >> 15)				//�Զ�����Aͨ����Ƶϵ��
#define PWMA_period (sys_clk / freqA / (freqA_div + 1))	//�Զ�����Aͨ����������
//#define PWMA_period	6000	//����PWMA���� 0~65535
//#define freqA_div 0			//��������ʱ����Ҫ��Ƶ�����ֶ�����

#define freqB 1									//Bͨ��pwmƵ��
#define freqB_div ((sys_clk / freqB) >> 15)				//�Զ�����Bͨ����Ƶϵ��
#define PWMB_period (sys_clk / freqB / (freqB_div + 1))	//�Զ�����Bͨ����������
//#define PWMB_period	65535	//����PWMB���� 0~65535
//#define freqB_div 0			//��������ʱ����Ҫ��Ƶ�����ֶ�����

u8 PWM_Configuration(u8 PWM, PWMx_InitDefine *PWMx)	//PWM��ʼ������
{
	if(PWM == PWM1)
	{
		PWMA_CC1E_Disable();		//�ر����벶��/�Ƚ����
		PWMA_CC1NE_Disable();		//�رձȽ����
		PWMA_CC1S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMA_OC1ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO1P)
		{
			PWMA_CC1E_Enable();			//�������벶��/�Ƚ����
			PWMA_ENO |= ENO1P;
		}
		else
		{
			PWMA_CC1E_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO1P;
		}
		if(PWMx->PWM_EnoSelect & ENO1N)
		{
			PWMA_CC1NE_Enable();		//�������벶��/�Ƚ����
			PWMA_ENO |= ENO1N;
		}
		else
		{
			PWMA_CC1NE_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO1N;
		}
		PWMA_Duty1(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWM2)
	{
		PWMA_CC2E_Disable();		//�ر����벶��/�Ƚ����
		PWMA_CC2NE_Disable();		//�رձȽ����
		PWMA_CC2S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMA_OC2ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO2P)
		{
			PWMA_CC2E_Enable();			//�������벶��/�Ƚ����
			PWMA_ENO |= ENO2P;
		}
		else
		{
			PWMA_CC2E_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO2P;
		}
		if(PWMx->PWM_EnoSelect & ENO2N)
		{
			PWMA_CC2NE_Enable();		//�������벶��/�Ƚ����
			PWMA_ENO |= ENO2N;
		}
		else
		{
			PWMA_CC2NE_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO2N;
		}
		PWMA_Duty2(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWM3)
	{
		PWMA_CC3E_Disable();		//�ر����벶��/�Ƚ����
		PWMA_CC3NE_Disable();		//�رձȽ����
		PWMA_CC3S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMA_OC3ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO3P)
		{
			PWMA_CC3E_Enable();			//�������벶��/�Ƚ����
			PWMA_ENO |= ENO3P;
		}
		else
		{
			PWMA_CC3E_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO3P;
		}
		if(PWMx->PWM_EnoSelect & ENO3N)
		{
			PWMA_CC3NE_Enable();		//�������벶��/�Ƚ����
			PWMA_ENO |= ENO3N;
		}
		else
		{
			PWMA_CC3NE_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO3N;
		}
		PWMA_Duty3(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWM4)
	{
		PWMA_CC4E_Disable();		//�ر����벶��/�Ƚ����
		PWMA_CC4NE_Disable();		//�رձȽ����
		PWMA_CC4S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMA_OC4ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO4P)
		{
			PWMA_CC4E_Enable();			//�������벶��/�Ƚ����
			PWMA_ENO |= ENO4P;
		}
		else
		{
			PWMA_CC4E_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO4P;
		}
		if(PWMx->PWM_EnoSelect & ENO4N)
		{
			PWMA_CC4NE_Enable();		//�������벶��/�Ƚ����
			PWMA_ENO |= ENO4N;
		}
		else
		{
			PWMA_CC4NE_Disable();		//�ر����벶��/�Ƚ����
			PWMA_ENO &= ~ENO4N;
		}
		PWMA_Duty4(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWMA)
	{
//		PWMA_OC1_ReloadEnable(PWMx->PWM_Reload);	//����Ƚϵ�Ԥװ��ʹ��
//		PWMA_OC1_FastEnable(PWMx->PWM_Fast);		//����ȽϿ��ٹ���ʹ��
//		PWMA_CCPCAPreloaded(PWMx->PWM_PreLoad);	//����/�Ƚ�Ԥװ�ؿ���λ(��λֻ�Ծ��л��������ͨ��������)
//		PWMA_BrakeEnable(PWMx->PWM_BrakeEnable);	//����/��ֹɲ������

		PWMA_DeadTime(PWMx->PWM_DeadTime);	//��������������
		PWMA_AutoReload(PWMx->PWM_Period);	//��������
		PWMA_BrakeOutputEnable(PWMx->PWM_MainOutEnable);	//�����ʹ��
		PWMA_CEN_Enable(PWMx->PWM_CEN_Enable);	//ʹ�ܼ�����
		return	SUCCESS;
	}

	if(PWM == PWM5)
	{
		PWMB_CC5E_Disable();		//�ر����벶��/�Ƚ����
		PWMB_CC5S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMB_OC5ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO5P)
		{
			PWMB_CC5E_Enable();			//�������벶��/�Ƚ����
			PWMB_ENO |= ENO5P;
		}
		else
		{
			PWMB_CC5E_Disable();		//�ر����벶��/�Ƚ����
			PWMB_ENO &= ~ENO5P;
		}
		PWMB_Duty5(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWM6)
	{
		PWMB_CC6E_Disable();		//�ر����벶��/�Ƚ����
		PWMB_CC6S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMB_OC6ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO6P)
		{
			PWMB_CC6E_Enable();			//�������벶��/�Ƚ����
			PWMB_ENO |= ENO6P;
		}
		else
		{
			PWMB_CC6E_Disable();		//�ر����벶��/�Ƚ����
			PWMB_ENO &= ~ENO6P;
		}
		PWMB_Duty6(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWM7)
	{
		PWMB_CC7E_Disable();		//�ر����벶��/�Ƚ����
		PWMB_CC7S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMB_OC7ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO7P)
		{
			PWMB_CC7E_Enable();			//�������벶��/�Ƚ����
			PWMB_ENO |= ENO7P;
		}
		else
		{
			PWMB_CC7E_Disable();		//�ر����벶��/�Ƚ����
			PWMB_ENO &= ~ENO7P;
		}
		PWMB_Duty7(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWM8)
	{
		PWMB_CC8E_Disable();		//�ر����벶��/�Ƚ����
		PWMB_CC8S_Direction(CCAS_OUTPUT);		//CCnS����ͨ���ر�ʱ���ǿ�д��
		PWMB_OC8ModeSet(PWMx->PWM_Mode);		//��������Ƚ�ģʽ

		if(PWMx->PWM_EnoSelect & ENO8P)
		{
			PWMB_CC8E_Enable();			//�������벶��/�Ƚ����
			PWMB_ENO |= ENO8P;
		}
		else
		{
			PWMB_CC8E_Disable();		//�ر����벶��/�Ƚ����
			PWMB_ENO &= ~ENO8P;
		}
		PWMB_Duty8(PWMx->PWM_Duty);
		return	SUCCESS;
	}
	
	if(PWM == PWMB)
	{
//		PWMB_OC5_ReloadEnable(PWMx->PWM_Reload);	//����Ƚϵ�Ԥװ��ʹ��
//		PWMB_OC5_FastEnable(PWMx->PWM_Fast);		//����ȽϿ��ٹ���ʹ��
//		PWMB_CCPCBPreloaded(PWMx->PWM_PreLoad);	//����/�Ƚ�Ԥװ�ؿ���λ(��λֻ�Ծ��л��������ͨ��������)
//		PWMB_BrakeEnable(PWMx->PWM_BrakeEnable);	//����/��ֹɲ������

		PWMB_DeadTime(PWMx->PWM_DeadTime);	//��������������
		PWMB_AutoReload(PWMx->PWM_Period);	//��������
		PWMB_BrakeOutputEnable(PWMx->PWM_MainOutEnable);	//�����ʹ��
		PWMB_CEN_Enable(PWMx->PWM_CEN_Enable);	//ʹ�ܼ�����
		return	SUCCESS;
	}
	return	FALL;	//����
}

//void UpdatePwm(u8 PWM, PWMx_Duty *PWMx)	//PWMռ�ձȸ��³���
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
void PWM_init()	//��STC32G_PWM.c���޸�����
{
	PWMx_InitDefine	PWMx_InitStructure;
	PWMA_Prescaler(freqA_div);	//�Զ���Ƶ
	PWMB_Prescaler(freqB_div);	//�Զ���Ƶ
	
	PWMA_Duty.PWM1_Duty = 128;	//PWMռ�ձ�ʱ��, 0~Period
	PWMA_Duty.PWM2_Duty = 256;	//PWMռ�ձ�ʱ��, 0~Period
	PWMA_Duty.PWM3_Duty = 512;	//PWMռ�ձ�ʱ��, 0~Period
	PWMA_Duty.PWM4_Duty = 1024;	//PWMռ�ձ�ʱ��, 0~Period
	PWMB_Duty.PWM5_Duty = 128;	//PWMռ�ձ�ʱ��, 0~Period
	PWMB_Duty.PWM6_Duty = 256;	//PWMռ�ձ�ʱ��, 0~Period
	PWMB_Duty.PWM7_Duty = 512;	//PWMռ�ձ�ʱ��, 0~Period
	PWMB_Duty.PWM8_Duty = 1024;	//PWMռ�ձ�ʱ��, 0~Period
	//PWMA
	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMA_Duty.PWM1_Duty;	//PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO1N|ENO1P;		//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P������ͬ�����ʹ�û�(|)����
	PWM_Configuration(PWM1, &PWMx_InitStructure);			//��ʼ��PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMA_Duty.PWM2_Duty;	//PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO2P;				//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM2, &PWMx_InitStructure);			//��ʼ��PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMA_Duty.PWM3_Duty;	//PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO3P;				//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM3, &PWMx_InitStructure);			//��ʼ��PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMA_Duty.PWM4_Duty;	//PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect   = ENO4P;				//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM4, &PWMx_InitStructure);			//��ʼ��PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Period = PWMA_period;			//����ʱ��,   0~65535	24M--12.5k--1920
	PWMx_InitStructure.PWM_DeadTime = 0;					//��������������, 0~255		ԭ32usP-48usN -> ��������4us -> 28usP--4us�͵�ƽ--44usN--4us�͵�ƽ
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//�����ʹ��, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable = ENABLE;			//ʹ�ܼ�����, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);			//��ʼ��PWMͨ�üĴ���,  PWMA,PWMB
	//PWMB
	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = PWMB_Duty.PWM5_Duty;	//PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO5P;				//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM5, &PWMx_InitStructure);			//��ʼ��PWM,  PWMA,PWMB

//	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
//	PWMx_InitStructure.PWM_Duty = PWMB_Duty.PWM6_Duty;	//PWMռ�ձ�ʱ��, 0~Period
//	PWMx_InitStructure.PWM_EnoSelect = ENO6P;				//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
//	PWM_Configuration(PWM6, &PWMx_InitStructure);			//��ʼ��PWM,  PWMA,PWMB

//	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
//	PWMx_InitStructure.PWM_Duty = PWMB_Duty.PWM7_Duty;	//PWMռ�ձ�ʱ��, 0~Period
//	PWMx_InitStructure.PWM_EnoSelect = ENO7P;				//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
//	PWM_Configuration(PWM7, &PWMx_InitStructure);			//��ʼ��PWM,  PWMA,PWMB

//	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;	//ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
//	PWMx_InitStructure.PWM_Duty = PWMB_Duty.PWM8_Duty;	//PWMռ�ձ�ʱ��, 0~Period
//	PWMx_InitStructure.PWM_EnoSelect = ENO8P;				//���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
//	PWM_Configuration(PWM8, &PWMx_InitStructure);			//��ʼ��PWM,  PWMA,PWMB

	PWMx_InitStructure.PWM_Period = PWMB_period;			//����ʱ��,   0~65535
	PWMx_InitStructure.PWM_DeadTime = 0;					//��������������, 0~255
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;			//�����ʹ��, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable = ENABLE;			//ʹ�ܼ�����, ENABLE,DISABLE
	PWM_Configuration(PWMB, &PWMx_InitStructure);			//��ʼ��PWMͨ�üĴ���,  PWMA,PWMB
	
//	PWM1_USE_P60P61();	//����ȴ��
//	PWM2_USE_P62P63();	//����ȴ��
//	PWM3_USE_P64P65();	//����ȴ��
//	PWM4_USE_P66P67();	//����ȴ��
	PWM1_USE_P20P21();
	PWM2_USE_P22P23();
	PWM3_USE_P24P25();
	PWM4_USE_P26P27();
//	PWM5_USE_P20();	//����ȴ��
//	PWM6_USE_P21();	//����ȴ��
//	PWM7_USE_P22();	//����ȴ��
//	PWM8_USE_P23();	//����ȴ��
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
			PWMA_Duty.PWM1_Duty = zkb*PWMA_period;	//����1us������ʽ��������PWMA_period��Ϊ PWMA_period*freqA*0.000001 ��ֵ����
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
u8 ReadPWMA(u8 addr)	//�첽��ȡPWMA���⹦�ܼĴ�������
{
	u8 dat;
	
	while (HSPWMA_ADR &	0x80); //�ȴ�ǰһ���첽��д���
	HSPWMA_ADR = addr |	0x80;  //���ü�ӷ��ʵ�ַ,ֻ��Ҫ����ԭXFR��ַ�ĵ�7λ
								//HSPWMA_ADDR�Ĵ��������λд1,��ʾ������
	while (HSPWMA_ADR &	0x80); //�ȴ���ǰ�첽��ȡ���
	dat	= HSPWMA_DAT;		   //��ȡ�첽����
	
	return dat;
}

u8 ReadPWMB(u8 addr)	//�첽��ȡPWMB���⹦�ܼĴ�������
{
	u8 dat;
	
	while (HSPWMB_ADR &	0x80); //�ȴ�ǰһ���첽��д���
	HSPWMB_ADR = addr |	0x80;  //���ü�ӷ��ʵ�ַ,ֻ��Ҫ����ԭXFR��ַ�ĵ�7λ
								//HSPWMB_ADDR�Ĵ��������λд1,��ʾ������
	while (HSPWMB_ADR &	0x80); //�ȴ���ǰ�첽��ȡ���
	dat	= HSPWMB_DAT;		   //��ȡ�첽����
	
	return dat;
}

void WritePWMA(u8 addr, u8 dat)	//�첽��ȡPWMA���⹦�ܼĴ�������
{
	while (HSPWMA_ADR &	0x80); //�ȴ�ǰһ���첽��д���
	HSPWMA_DAT = dat;		   //׼����Ҫд�������
	HSPWMA_ADR = addr &	0x7f;  //���ü�ӷ��ʵ�ַ,ֻ��Ҫ����ԭXFR��ַ�ĵ�7λ
								//HSPWMA_ADDR�Ĵ��������λд0,��ʾд����
}

void WritePWMB(u8 addr, u8 dat)	//�첽��ȡPWMB���⹦�ܼĴ�������
{
	while (HSPWMB_ADR &	0x80); //�ȴ�ǰһ���첽��д���
	HSPWMB_DAT = dat;		   //׼����Ҫд�������
	HSPWMB_ADR = addr &	0x7f;  //���ü�ӷ��ʵ�ַ,ֻ��Ҫ����ԭXFR��ַ�ĵ�7λ
								//HSPWMB_ADDR�Ĵ��������λд0,��ʾд����
}

void HSPWM_Configuration(u8 PWM, HSPWMx_InitDefine *PWMx, PWMx_Duty *DUTYx)	//HSPWM��ʼ������
{
	u8 tmpENO,tmpCCER1,tmpCCER2;
	
	if(PWM == PWMA)
	{
		HSPWMA_CFG = 0x03;			//ʹ��PWMA��ؼĴ����첽���ʹ���

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
		
		//ͨ���첽��ʽ����PWMA����ؼĴ���
		WritePWMA((u8)&PWMA_CCER1, 0x00);
		WritePWMA((u8)&PWMA_CCER2, 0x00);
		WritePWMA((u8)&PWMA_CCMR1, CCMRn_PWM_MODE1);				//ͨ��ģʽ����
		WritePWMA((u8)&PWMA_CCMR2, CCMRn_PWM_MODE1);
		WritePWMA((u8)&PWMA_CCMR3, CCMRn_PWM_MODE1);
		WritePWMA((u8)&PWMA_CCMR4, CCMRn_PWM_MODE1);
		WritePWMA((u8)&PWMA_CCER1, tmpCCER1);						//����ͨ�����ʹ�ܺͼ���
		WritePWMA((u8)&PWMA_CCER2, tmpCCER2);
		WritePWMA((u8)&PWMA_ENO, tmpENO);							//ʹ��PWM�ź�����˿�
		WritePWMA((u8)&PWMA_CCR1H, (u8)(DUTYx->PWM1_Duty >> 8));	//�������PWM��ռ�ձ�
		WritePWMA((u8)&PWMA_CCR1L, (u8)DUTYx->PWM1_Duty);
		WritePWMA((u8)&PWMA_CCR2H, (u8)(DUTYx->PWM2_Duty >> 8));	//�������PWM��ռ�ձ�
		WritePWMA((u8)&PWMA_CCR2L, (u8)DUTYx->PWM2_Duty);
		WritePWMA((u8)&PWMA_CCR3H, (u8)(DUTYx->PWM3_Duty >> 8));	//�������PWM��ռ�ձ�
		WritePWMA((u8)&PWMA_CCR3L, (u8)DUTYx->PWM3_Duty);
		WritePWMA((u8)&PWMA_CCR4H, (u8)(DUTYx->PWM4_Duty >> 8));	//�������PWM��ռ�ձ�
		WritePWMA((u8)&PWMA_CCR4L, (u8)DUTYx->PWM4_Duty);
		WritePWMA((u8)&PWMA_ARRH, (u8)(PWMx->PWM_Period >> 8));		//�������PWM������
		WritePWMA((u8)&PWMA_ARRL, (u8)(PWMx->PWM_Period));
		WritePWMA((u8)&PWMA_DTR, PWMx->PWM_DeadTime);				//���û����Գ����PWM������
		WritePWMA((u8)&PWMA_BRK, PWMx->PWM_MainOutEnable<<7);		//ʹ�������
		WritePWMA((u8)&PWMA_CR1, PWMx->PWM_CEN_Enable);				//��ʼPWM����
	}
	else if(PWM == PWMB)
	{
		HSPWMB_CFG = 0x03;			//ʹ��PWMB��ؼĴ����첽���ʹ���

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
		
		//ͨ���첽��ʽ����PWMA����ؼĴ���
		WritePWMB((u8)&PWMB_CCER1, 0x00);
		WritePWMB((u8)&PWMB_CCER2, 0x00);
		WritePWMB((u8)&PWMB_CCMR1, CCMRn_PWM_MODE1);				//ͨ��ģʽ����
		WritePWMB((u8)&PWMB_CCMR2, CCMRn_PWM_MODE1);
		WritePWMB((u8)&PWMB_CCMR3, CCMRn_PWM_MODE1);
		WritePWMB((u8)&PWMB_CCMR4, CCMRn_PWM_MODE1);
		WritePWMB((u8)&PWMB_CCER1, tmpCCER1);						//����ͨ�����ʹ�ܺͼ���
		WritePWMB((u8)&PWMB_CCER2, tmpCCER2);
		WritePWMB((u8)&PWMB_ENO, tmpENO);							//ʹ��PWM�ź�����˿�
		WritePWMB((u8)&PWMB_CCR5H, (u8)(DUTYx->PWM5_Duty >> 8));	//�������PWM��ռ�ձ�
		WritePWMB((u8)&PWMB_CCR5L, (u8)DUTYx->PWM5_Duty);
		WritePWMB((u8)&PWMB_CCR6H, (u8)(DUTYx->PWM6_Duty >> 8));	//�������PWM��ռ�ձ�
		WritePWMB((u8)&PWMB_CCR6L, (u8)DUTYx->PWM6_Duty);
		WritePWMB((u8)&PWMB_CCR7H, (u8)(DUTYx->PWM7_Duty >> 8));	//�������PWM��ռ�ձ�
		WritePWMB((u8)&PWMB_CCR7L, (u8)DUTYx->PWM7_Duty);
		WritePWMB((u8)&PWMB_CCR8H, (u8)(DUTYx->PWM8_Duty >> 8));	//�������PWM��ռ�ձ�
		WritePWMB((u8)&PWMB_CCR8L, (u8)DUTYx->PWM8_Duty);
		WritePWMB((u8)&PWMB_ARRH, (u8)(PWMx->PWM_Period >> 8));		//�������PWM������
		WritePWMB((u8)&PWMB_ARRL, (u8)(PWMx->PWM_Period));
		WritePWMB((u8)&PWMB_DTR, PWMx->PWM_DeadTime);				//���û����Գ����PWM������
		WritePWMB((u8)&PWMB_BRK, PWMx->PWM_MainOutEnable<<7);		//ʹ�������
		WritePWMB((u8)&PWMB_CR1, PWMx->PWM_CEN_Enable);				//��ʼPWM����
	}
}

void UpdateHSPwm(u8 PWM, PWMx_Duty *PWMx)	//HSPWMռ�ձȸ��³���
{
	switch(PWM)
	{
		case PWM1:
			WritePWMA((u8)&PWMA_CCR1H, (u8)(PWMx->PWM1_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMA((u8)&PWMA_CCR1L, (u8)PWMx->PWM1_Duty);
			break;
		case PWM2:
			WritePWMA((u8)&PWMA_CCR2H, (u8)(PWMx->PWM2_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMA((u8)&PWMA_CCR2L, (u8)PWMx->PWM2_Duty);
			break;
		case PWM3:
			WritePWMA((u8)&PWMA_CCR3H, (u8)(PWMx->PWM3_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMA((u8)&PWMA_CCR3L, (u8)PWMx->PWM3_Duty);
			break;
		case PWM4:
			WritePWMA((u8)&PWMA_CCR4H, (u8)(PWMx->PWM4_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMA((u8)&PWMA_CCR4L, (u8)PWMx->PWM4_Duty);
			break;
		case PWM5:
			WritePWMB((u8)&PWMB_CCR5H, (u8)(PWMx->PWM5_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMB((u8)&PWMB_CCR5L, (u8)PWMx->PWM5_Duty);
			break;
		case PWM6:
			WritePWMB((u8)&PWMB_CCR6H, (u8)(PWMx->PWM6_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMB((u8)&PWMB_CCR6L, (u8)PWMx->PWM6_Duty);
			break;
		case PWM7:
			WritePWMB((u8)&PWMB_CCR7H, (u8)(PWMx->PWM7_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMB((u8)&PWMB_CCR7L, (u8)PWMx->PWM7_Duty);
			break;
		case PWM8:
			WritePWMB((u8)&PWMB_CCR8H, (u8)(PWMx->PWM8_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMB((u8)&PWMB_CCR8L, (u8)PWMx->PWM8_Duty);
			break;
		case PWMA:
			WritePWMA((u8)&PWMA_CCR1H, (u8)(PWMx->PWM1_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMA((u8)&PWMA_CCR1L, (u8)PWMx->PWM1_Duty);
			WritePWMA((u8)&PWMA_CCR2H, (u8)(PWMx->PWM2_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMA((u8)&PWMA_CCR2L, (u8)PWMx->PWM2_Duty);
			WritePWMA((u8)&PWMA_CCR3H, (u8)(PWMx->PWM3_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMA((u8)&PWMA_CCR3L, (u8)PWMx->PWM3_Duty);
			WritePWMA((u8)&PWMA_CCR4H, (u8)(PWMx->PWM4_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMA((u8)&PWMA_CCR4L, (u8)PWMx->PWM4_Duty);
			break;
		case PWMB:
			WritePWMB((u8)&PWMB_CCR5H, (u8)(PWMx->PWM5_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMB((u8)&PWMB_CCR5L, (u8)PWMx->PWM5_Duty);
			WritePWMB((u8)&PWMB_CCR6H, (u8)(PWMx->PWM6_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMB((u8)&PWMB_CCR6L, (u8)PWMx->PWM6_Duty);
			WritePWMB((u8)&PWMB_CCR7H, (u8)(PWMx->PWM7_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMB((u8)&PWMB_CCR7L, (u8)PWMx->PWM7_Duty);
			WritePWMB((u8)&PWMB_CCR8H, (u8)(PWMx->PWM8_Duty >> 8));	//�������PWM��ռ�ձ�
			WritePWMB((u8)&PWMB_CCR8L, (u8)PWMx->PWM8_Duty);
			break;
		default:break;
	}
}
*/
/*********************************************************/
