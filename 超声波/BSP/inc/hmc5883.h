#ifndef _HMC5883_H
#define _HMC5883_H
#include "stm32f10x.h"
#include "I2C.h"
#define	HMC5883L_ADDRESS   0x3C	  //定义器件在IIC总线中的从地址

u8 Init_HMC5883L(void);
void Multiple_Read_HMC5883L(void);

extern int16_t X_HMC,Y_HMC,Z_HMC,x,y,z;
#endif

