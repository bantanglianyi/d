#include <oled.h>
#include <oledfont.h>  	 
//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	                                                               
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
void delay_ms(unsigned int ms)
{                         
	unsigned int a;
	while(ms)
	{
		a=1800;
		while(a--);
		ms--;
	}
	return;
}

//反显函数
void OLED_ColorTurn(u8 i)
{
	if(i==0)
		{
			OLED_WR_Byte(0xA6,OLED_CMD);//正常显示
		}
	if(i==1)
		{
			OLED_WR_Byte(0xA7,OLED_CMD);//反色显示
		}
}

//屏幕旋转180度
void OLED_DisplayTurn(u8 i)
{
	if(i==0)
		{
			OLED_WR_Byte(0xC8,OLED_CMD);//正常显示
			OLED_WR_Byte(0xA1,OLED_CMD);
		}
	if(i==1)
		{
			OLED_WR_Byte(0xC0,OLED_CMD);//反转显示
			OLED_WR_Byte(0xA0,OLED_CMD);
		}
}


void OLED_WR_Byte(u16 dat,u16 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCL_Clr();
		if(dat&0x80)
		{
		 OLED_SDA_Set();
		}
		else
		{
		 OLED_SDA_Clr();
		}
	  OLED_SCL_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 

//坐标设置

void OLED_Set_Pos(u16 x, u16 y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}   	  
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63				 
//sizey:选择字体 6x8  8x16
void OLED_ShowChar(u16 x,u16 y,u16 chr,u16 sizey)
{      	
	u8 c=0,sizex=sizey/2;
	u16 i=0,size1;
	if(sizey==8)size1=6;
	else size1=(sizey/8+((sizey%8)?1:0))*(sizey/2);
	c=chr-' ';//得到偏移后的值
	OLED_Set_Pos(x,y);
	for(i=0;i<size1;i++)
	{
		if(i%sizex==0&&sizey!=8) OLED_Set_Pos(x,y++);
		if(sizey==8) OLED_WR_Byte(asc2_0806[c][i],OLED_DATA);//6X8字号
		else if(sizey==16) OLED_WR_Byte(asc2_1608[c][i],OLED_DATA);//8x16字号
//		else if(sizey==xx) OLED_WR_Byte(asc2_xxxx[c][i],OLED_DATA);//用户添加字号
		else return;
	}
}
//m^n函数
u32 oled_pow(u16 m,u16 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示数字
//x,y :起点坐标
//num:要显示的数字
//len :数字的位数
//sizey:字体大小		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey)
{         	
	u8 t;
	u8 temp,m=0;
	u8 enshow=0;
	if(sizey==8)m=2;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(sizey/2+m)*t,y,' ',sizey);
				continue;
			}else enshow=1;
		}
	 	OLED_ShowChar(x+(sizey/2+m)*t,y,temp+'0',sizey);
	}
}
//显示一个字符号串
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey)
{
	u8 j=0;
	while (chr[j]!='\0')
	{		
		OLED_ShowChar(x,y,chr[j++],sizey);
		if(sizey==8)x+=6;
		else x+=sizey/2;
	}
}
//显示汉字
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey)
{
	u16 i,size1=(sizey/8+((sizey%8)?1:0))*sizey;
	for(i=0;i<size1;i++)
	{
		if(i%sizey==0) OLED_Set_Pos(x,y++);
		if(sizey==16) OLED_WR_Byte(Hzk[no][i],OLED_DATA);//16x16字号
//		else if(sizey==xx) OLED_WR_Byte(xxx[c][i],OLED_DATA);//用户添加字号
		else return;
	}				
}


//显示图片
//x,y显示坐标
//sizex,sizey,图片长宽
//BMP：要显示的图片
void OLED_DrawBMP(u8 x,u8 y,u8 sizex, u8 sizey,u8 BMP[])
{ 	
  u16 j=0;
	u8 i,m;
	sizey=sizey/8+((sizey%8)?1:0);
	for(i=0;i<sizey;i++)
	{
		OLED_Set_Pos(x,i+y);
    for(m=0;m<sizex;m++)
		{      
			OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
		}
	}
} 



//初始化				    
void OLED_Init(void)
{
	OLED_RES_Clr();
  delay_ms(200);
	OLED_RES_Set();
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0xFD,OLED_CMD);
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0xA0,OLED_CMD);
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xBF,OLED_CMD);// Set SEG Output Current Brightness
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0x25,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x34,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7)
	OLED_Clear();
	OLED_WR_Byte(0xAF,OLED_CMD);
}




