#ifndef __TIM_PWM_IN_H_
#define __TIM_PWM_IN_H_
#include "stm32f10x.h"

typedef struct int16_rcget{
				int16_t first;
				int16_t second;
}Data_In;

				
extern Data_In PWM_In;//1000~2000


void TIM4_Cap_Init(void);
void GET_FOUR_PWM(void);
#endif
