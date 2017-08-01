#include "led.h"

/*
 * 函数名：LED_GPIO_Config
 * 描述  ：配置LED用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
void LED_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	 GPIO_SetBits(GPIOB,GPIO_Pin_12 | GPIO_Pin_13);	 // turn off all led
	 GPIO_SetBits(GPIOD,GPIO_Pin_10 | GPIO_Pin_11);	 // turn off all led
}

uint8_t LED_Set(uint8_t LED, uint8_t state)
{
	switch(LED)
	{
		case LED1:
			if(state)			
				GPIO_SetBits(GPIOB,GPIO_Pin_12);
			else		
				GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			break;
			
		case LED2:
			if(state)			
				GPIO_SetBits(GPIOB,GPIO_Pin_13);
			else		
				GPIO_ResetBits(GPIOB,GPIO_Pin_13);
			break;
			
		case LED3:
			if(state)			
				GPIO_SetBits(GPIOD,GPIO_Pin_10);
			else		
				GPIO_ResetBits(GPIOD,GPIO_Pin_10);
			break;
			
		case LED4:
			if(state)			
				GPIO_SetBits(GPIOD,GPIO_Pin_11);
			else		
				GPIO_ResetBits(GPIOD,GPIO_Pin_11);
			break;
			
		default: return LED_error;
	}
	return LED_Setsuccess;
}

void LED_Set4(uint8_t state)
{
	if(state&0x01)
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
	if(state&0x02)
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	else
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
	if(state&0x04)
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);
	else
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
	if(state&0x08)
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);
	else
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
}
