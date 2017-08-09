#include "switch.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "stm32f10x_it.h"
void Switch_Init(void)        
{
   GPIO_InitTypeDef  SW_GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 	 //GPIO始终使能

   SW_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	 SW_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 SW_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_Init(GPIOA, &SW_GPIO_InitStructure); 		           //配置OLED端口引脚为GPIO输出
}