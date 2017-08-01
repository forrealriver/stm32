#ifndef _SWITCH_H
#define _SWITCH_H

#include "stm32f10x.h"

#define ModoRead() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)

void Switch_Init();

#endif

