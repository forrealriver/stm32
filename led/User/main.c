#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Delay(uint16_t);
int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB	, ENABLE);
/*
typedef struct {
	uint16_t GPIO_Pin;
	GPIOSpeed_TypeDef GPIO_Speed;
	GPIOMode_TypeDef GPIO_Mode;
 } GPIO_InitTypeDef;
*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
/*
typedef enum {
	GPIO_Speed_10MHz = 1,
	GPIO_Speed_2MHz,
	GPIO_Speed_50MHz
} GPIOSpeed_TypeDef;
*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
/*
typedef enum {
	GPIO_Mode_AIN = 0x0,      		// 模拟输入
	GPIO_Mode_IN_FLOATING = 0x04, 	// 浮空输入（复位后的状态）
	GPIO_Mode_IPD = 0x28,     		// 下拉输入
	GPIO_Mode_IPU = 0x48,     		// 上拉输入
	GPIO_Mode_Out_OD = 0x14, 		// 通用开漏输出
	GPIO_Mode_Out_PP = 0x10, 		// 通用推挽输出
	GPIO_Mode_AF_OD = 0x1C,   		// 复用开漏输出
	GPIO_Mode_AF_PP = 0x18    		//  复用推挽输出
}GPIOMode_TypeDef;
*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP	;
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
