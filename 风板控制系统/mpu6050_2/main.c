#include "MPU6050.H"
#include "oled.h"
#include "config.h"
#include "math.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
u8		edata	tp[16];		//读MP6050缓冲
u8       x_https[50];
u8       y_https[50];
u8       z_https[50];

int		edata g_x=0,g_y=0,g_z=0;					//陀螺仪矫正参数
float	edata a_x=0,a_y=0;							//角度矫正参数

float	edata AngleX=0,AngleY=0,AngleZ=0;					//四元数解算出的欧拉角
float	edata Angle_gx=0,Angle_gy=0,Angle_gz=0;		//由角速度计算的角速率(角度制)
float	edata Angle_ax=0,Angle_ay=0,Angle_az=0;		//由加速度计算的加速度(弧度制)
float edata Out_PID_X=0,Last_Angle_gx=0;
float edata Out_PID_Y=0,Last_Angle_gy=0;
////////////////////////////////////////////////////////
#define	pi		3.14159265f                           
#define	Kp		0.8f                        
#define	Ki		0.001f                         
#define	halfT	0.004f           

float edata q0=1,q1=0,q2=0,q3=0;   
float edata exInt=0,eyInt=0,ezInt=0;  



void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)
{
	float edata norm;
	float edata vx, vy, vz;
	float edata ex, ey, ez;

	norm = sqrt(ax*ax + ay*ay + az*az);	//把加速度计的三维向量转成单维向量   
	ax = ax / norm;
	ay = ay / norm;
	az = az / norm;

		//	下面是把四元数换算成《方向余弦矩阵》中的第三列的三个元素。 
		//	根据余弦矩阵和欧拉角的定义，地理坐标系的重力向量，转到机体坐标系，正好是这三个元素
		//	所以这里的vx vy vz，其实就是当前的欧拉角（即四元数）的机体坐标参照系上，换算出来的
		//	重力单位向量。
	vx = 2*(q1*q3 - q0*q2);
	vy = 2*(q0*q1 + q2*q3);
	vz = q0*q0 - q1*q1 - q2*q2 + q3*q3 ;

	ex = (ay*vz - az*vy) ;
	ey = (az*vx - ax*vz) ;
	ez = (ax*vy - ay*vx) ;

	exInt = exInt + ex * Ki;
	eyInt = eyInt + ey * Ki;
	ezInt = ezInt + ez * Ki;

	gx = gx + Kp*ex + exInt;
	gy = gy + Kp*ey + eyInt;
	gz = gz + Kp*ez + ezInt;

	q0 = q0 + (-q1*gx - q2*gy - q3*gz) * halfT;
	q1 = q1 + ( q0*gx + q2*gz - q3*gy) * halfT;
	q2 = q2 + ( q0*gy - q1*gz + q3*gx) * halfT;
	q3 = q3 + ( q0*gz + q1*gy - q2*gx) * halfT;

	norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
	q0 = q0 / norm;
	q1 = q1 / norm;
	q2 = q2 / norm;
	q3 = q3 / norm;


	AngleZ= atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2*q2 - 2 * q3* q3 + 1)* 57.2957795f; // yaw 
	AngleY= asin(-2 * q1 * q3 + 2 * q0* q2)* 57.2957795f; // pitch 
	AngleX= atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.2957795f; // roll
}


void main()
{
	P4M0 = 0xff; P4M1 = 0x00; 
	P2M0 = 0x00; P2M1 = 0x00; 
	InitMPU6050();
	OLED_Init();

	while(1)
	{
	
				Read_MPU6050(tp);	// 720us @24MHz
				Angle_ax = ((float)(((int *)&tp)[0])) / 8192.0;	//加速度处理	结果单位是 +- g
				Angle_ay = ((float)(((int *)&tp)[1])) / 8192.0;	//转换关系	8192 LSB/g, 1g对应读数8192
				Angle_az = ((float)(((int *)&tp)[2])) / 8192.0;	//加速度量程 +-4g/S
				Last_Angle_gx = Angle_gx;		//储存上一次角速度数据
				Last_Angle_gy = Angle_gy;
				Angle_gx = ((float)(((int *)&tp)[4] - g_x)) / 65.5;	//陀螺仪处理	结果单位是 +-度
				Angle_gy = ((float)(((int *)&tp)[5] - g_y)) / 65.5;	//陀螺仪量程 +-500度/S, 1度/秒 对应读数 65.536
				Angle_gz = ((float)(((int *)&tp)[6] - g_z)) / 65.5;	//转换关系65.5 LSB/度
				IMUupdate(Angle_gx*0.0174533f, Angle_gy*0.0174533f, Angle_gz*0.0174533f, Angle_ax,Angle_ay,Angle_az);	// 0.8~1.0ms @24MHz	
				sprintf(x_https,"x:%.3f",AngleX);
				OLED_ShowString(0,0,x_https,8);
				sprintf(y_https,"y:%.3f",AngleY);
				OLED_ShowString(0,1,y_https,8);
				sprintf(z_https,"z:%.3f",AngleZ);
				OLED_ShowString(0,2,z_https,8);
		

	}
}







