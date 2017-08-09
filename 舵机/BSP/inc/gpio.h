#ifndef __GPIO_H
#define	__GPIO_H
#include "stm32f10x.h"

#define beep(x)		  GPIO_WriteBit(GPIOA,GPIO_Pin_8,x)
			
void Beep_Init(void);
void GPIOB_Init(void);
void GPIOC_Init(void);
void GPIOD_Init(void);
void GPIOE_Init(void);

#endif
