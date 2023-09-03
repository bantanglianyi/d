#include "MAIN.H" 
bit qie = 0;
char buf[60];
f32 hz=0.0,pl=0.0,zhoo=0.0;
extern f32 zhou;
extern u16 ds_w,wb_w;
extern u8 TL_0,TH_0;
void main()
{

	uart1_init();	//串口初始化   
	sprintf(buf,"CLS(0);CLS(0);CLS(0);\r\n");		   //清屏
	PrintString1(buf);
	init();			//定时器初始化
	while(1)
	{  
			pl = 65535*ds_w+256*TH_0+TL_0;					//测周法
			//hz =(1842997/pl*wb_w);  //12T模式 上限122KHZ
			hz =(22115890/pl*wb_w);   //1T模式  上限220KHZ
			sprintf(buf,"DS32(330,0,'频率计',17);DS48(60,200,'频率:%3.4f HZ',17);\r\n",hz);		   
			PrintString1(buf);
			if(hz>=221000)qie=1;
//		if(qie==1)
//		{
//				zhoo = zhou/1000.0;
//				sprintf(buf,"DS48(330,0,'频率计',17);DS32(20,120,'频率:%3.4f KHZ',17);\r\n",zhoo);		   
//				PrintString1(buf);
//		}
	}
}