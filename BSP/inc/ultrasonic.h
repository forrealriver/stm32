#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_
#include "stm32f10x.h"	

#define CounterEnable(x) 	TIM_Cmd(TIM1,x)					//计数器使能
#define CounterSet(x) 		TIM_SetCounter(TIM1,x)	//计数器装载值
#define CounterRead()			TIM_GetCounter(TIM1)		//读计数器当前计数值

#define SetObs(x)		GPIO_WriteBit(GPIOD,GPIO_Pin_4,x)
#define ReadObs()		GPIO_ReadInputData(GPIOE)

extern float obs_distance[8];
extern u16 obsconsta[8];
extern u16 obsconend[8];		
extern u8 Obs_Count;
extern u8 obs_state[8];
extern u16 obsbits[8];	
extern u8  StartCap_Flag;			
extern u16 ObsDataBits;
extern u8  obs_discm[8];
extern u8 obs_normal_count[8];
extern u8 obs_flag[8];
extern u8 dir_state;
extern u8 last_dir_state ;
extern u8 obscmp[8];

void TimeUltra_Init();
void Exti_Set(u8 en);
void Obs_Analysis();
			
#endif
