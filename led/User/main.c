#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Delay(uint16_t);
int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB	, ENABLE);
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
		while (1)
	{
		GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
		Delay(10);
		GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
		Delay(10);
	}
	
	
}
void Delay(uint16_t c)
{
	uint16_t a,b;
	for(; c>0; c--)
		for(a=1000; a>0; a--)
			for(b=1000; b>0; b--);
}
