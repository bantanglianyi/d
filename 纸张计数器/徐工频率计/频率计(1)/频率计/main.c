#include "MAIN.H" 
bit qie = 0;
char buf[60];
f32 hz=0.0,pl=0.0,zhoo=0.0;
extern f32 zhou;
extern u16 ds_w,wb_w;
extern u8 TL_0,TH_0;
void main()
{

	uart1_init();	//���ڳ�ʼ��   
	sprintf(buf,"CLS(0);CLS(0);CLS(0);\r\n");		   //����
	PrintString1(buf);
	init();			//��ʱ����ʼ��
	while(1)
	{  
			pl = 65535*ds_w+256*TH_0+TL_0;					//���ܷ�
			//hz =(1842997/pl*wb_w);  //12Tģʽ ����122KHZ
			hz =(22115890/pl*wb_w);   //1Tģʽ  ����220KHZ
			sprintf(buf,"DS32(330,0,'Ƶ�ʼ�',17);DS48(60,200,'Ƶ��:%3.4f HZ',17);\r\n",hz);		   
			PrintString1(buf);
			if(hz>=221000)qie=1;
//		if(qie==1)
//		{
//				zhoo = zhou/1000.0;
//				sprintf(buf,"DS48(330,0,'Ƶ�ʼ�',17);DS32(20,120,'Ƶ��:%3.4f KHZ',17);\r\n",zhoo);		   
//				PrintString1(buf);
//		}
	}
}