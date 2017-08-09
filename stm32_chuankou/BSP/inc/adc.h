#ifndef __ADC_H
#define	__ADC_H

#include "stm32f10x.h"

#define AdcVoltage ADC_Channel_10
#define AdcCurrent ADC_Channel_11

struct Adc_System{
	float voltage;
	float current;
};

extern struct Adc_System syscharacter;
extern __IO uint16_t ADC1_ConvertedValue[20];

void ADC2_Init(void);
uint16_t ADC2_GetConvert(uint8_t ch);
void PowConvert(uint32_t cur,uint32_t vol,uint16_t num);//num为连续采集的次数


#endif /* __ADC_H */

