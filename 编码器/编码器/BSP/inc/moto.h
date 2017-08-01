#ifndef _MOTO_H_
#define _MOTO_H_
#include "stm32f10x.h"

#define MOTO_LEFT  	0
#define MOTO_RIGHT 	1

#define PWM_TIM5_Period(x)	TIM5->ARR = x		//f=1000000/x
#define PWM1_Duty(x)	x>TIM5->ARR ? (TIM5->CCR4 = TIM5->ARR) : (TIM5->CCR4 = x)

#define PWM_TIM8_Period(x)	TIM8->ARR = x	//f=1000000/x
#define PWM2_Duty(x)	x>TIM8->ARR ? (TIM8->CCR1 = TIM8->ARR) : (TIM8->CCR1 = x)

#define PWM_TIM4_Period(x)	TIM4->ARR = x	//f=1000000/x
#define PWM3_Duty(x)	x>TIM4->ARR ? (TIM4->CCR2 = TIM4->ARR) : (TIM4->CCR2 = x)

//实际应用
#define motoen60(x) 	TIM_Cmd(TIM5, x)
#define motoen180(x)  TIM_Cmd(TIM8, x)
#define motoen300(x) 	TIM_Cmd(TIM4, x)

#define motospeed60(x)	TIM5->ARR = x;PWM1_Duty(x/2)
#define motospeed180(x)	TIM8->ARR = x;PWM2_Duty(x/2)
#define motospeed300(x)	TIM4->ARR = x;PWM3_Duty(x/2)

//方向宏定义
#define motodir60(x)	GPIO_WriteBit(GPIOA,GPIO_Pin_2,x)
#define motodir180(x)	GPIO_WriteBit(GPIOC,GPIO_Pin_5,x)
#define motodir300(x)	GPIO_WriteBit(GPIOD,GPIO_Pin_12,x)

#define MotoPowerEnable(x) GPIO_WriteBit(GPIOA,GPIO_Pin_11,x),GPIO_WriteBit(GPIOE,GPIO_Pin_7,x)

void Moto_Init(void);

#endif
