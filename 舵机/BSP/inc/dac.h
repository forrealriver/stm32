#ifndef __DAC_H
#define	__DAC_H


#include "stm32f10x.h"
#define DAC_DHR12RD_Address      0x40007420 //0x40007420

extern __IO uint16_t DAC_ConvertedValue[2];
void DAC_GPIO_Config(void);
void DAC_Mode_Config(void);
void DAC_Config(void);
void DAC_OutPut_Data(uint16_t data0,uint16_t data1);
#endif /* __DAC_H */
