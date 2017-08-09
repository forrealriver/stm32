#ifndef __TIME_H__
#define __TIME_H__
#include "stm32f10x.h"

#define EnTIM3()  TIM_Cmd(TIM3,ENABLE)
#define EnTIM2()  TIM_Cmd(TIM2,ENABLE)
#define DisTIM3()  TIM_Cmd(TIM3,Disable)
#define DisTIM2()  TIM_Cmd(TIM2,Disable)


void Nvic_Init(void);
void TIM2_Init(u16 period_num);
void TIM3_Init(u16 period_num);


#endif 
