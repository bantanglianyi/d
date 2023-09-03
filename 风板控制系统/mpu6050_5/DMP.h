#ifndef DMP_H_
#define DMP_H_
#include "stdint.h"
extern float Q[4];	//四元数
extern uint8_t dmpdatas[42];	//DMP数据

void MPU6050_DMP_Init(void);
void MPU6050_Refresh_DMP(void);

#endif
