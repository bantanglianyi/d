#ifndef __OLED_H
#define __OLED_H

#include <STC32G.H>	 
#include <stdlib.h>

#define  u8 unsigned char 
#define  u16 unsigned int
#define  u32 unsigned long
	
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

sbit OLED_SCL=P4^0;//SCL
sbit OLED_SDA=P4^1;//SDA
sbit OLED_RES =P4^2;//RES
sbit OLED_DC =P4^3;//DC
sbit OLED_CS=P4^4; //CS

extern unsigned char accomplish;

//-----------------OLED端口定义----------------

#define OLED_SCL_Clr() OLED_SCL=0
#define OLED_SCL_Set() OLED_SCL=1

#define OLED_SDA_Clr() OLED_SDA=0
#define OLED_SDA_Set() OLED_SDA=1

#define OLED_RES_Clr() OLED_RES=0
#define OLED_RES_Set() OLED_RES=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1

//OLED控制用函数
void delay_ms(unsigned int ms);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Set_Pos(u8 x, u8 y);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey);
u32 oled_pow(u8 m,u8 n);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey);
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey);
void OLED_DrawBMP(u8 x,u8 y,u8 sizex, u8 sizey,unsigned long BMP[]);
void OLED_Init(void);
void Draw_Hline(unsigned char x0,unsigned char y0,unsigned char x,unsigned int time);//画横线
void Draw_Vline(unsigned char x0,unsigned char y0 ,unsigned char y,unsigned int time);//画竖线
void Clear(unsigned char y0,unsigned char y,unsigned char x0,unsigned int time);//画方块
void Draw_VlineF(unsigned char y0,unsigned char y,unsigned char x0,unsigned int time);//反向竖线
void Draw_Rectangle(unsigned char x0,unsigned char y0,unsigned char x,unsigned char y,unsigned int time);//画矩形
void Setpos(unsigned char x0,unsigned char y0);//画点
void OLED_DrawLine(int x1,int y1,int x2,int y2); //任意方向直线
void Draw_dimond(unsigned char x0,unsigned char y0,unsigned char R);//画棱形








#endif  
	 



