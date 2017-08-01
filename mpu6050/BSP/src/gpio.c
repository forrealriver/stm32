#include "gpio.h"

//GPIO_Mode_AIN 					模拟输入
//GPIO_Mode_IN_FLOATING 	浮空输入
//GPIO_Mode_IPD 					下拉输入
//GPIO_Mode_IPU 					上拉输入
//GPIO_Mode_Out_OD 				开漏输出
//GPIO_Mode_Out_PP 				推挽输出
//GPIO_Mode_AF_OD 				复用开漏输出
//GPIO_Mode_AF_PP 				复用推挽输出

void Beep_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void GPIOB_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5;	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void GPIOC_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_13;	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void GPIOD_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_7;	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
}


