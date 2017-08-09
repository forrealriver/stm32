#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "stm32f10x_it.h"
#include "oled.h"
#include "Encoder.h"
#include "delay.h"
#include "I2C.h"
#include "mpu6050.h"

unsigned int overcount=0;
void NVIC_Config(void)
{
NVIC_InitTypeDef NVIC_InitStructer;

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

NVIC_InitStructer.NVIC_IRQChannelPreemptionPriority=0;
NVIC_InitStructer.NVIC_IRQChannelSubPriority=0;
NVIC_InitStructer.NVIC_IRQChannel=TIM2_IRQn;
NVIC_InitStructer.NVIC_IRQChannelCmd=ENABLE;

NVIC_Init(&NVIC_InitStructer);
}

void CH_SR04_Init(void)
{
GPIO_InitTypeDef GPIO_InitStructer;
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructer;

RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

GPIO_InitStructer.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_InitStructer.GPIO_Mode=GPIO_Mode_Out_PP;
GPIO_InitStructer.GPIO_Pin=GPIO_Pin_1;
GPIO_Init(GPIOD, &GPIO_InitStructer);


GPIO_InitStructer.GPIO_Mode=GPIO_Mode_IN_FLOATING;
GPIO_InitStructer.GPIO_Pin=GPIO_Pin_0;
GPIO_Init(GPIOD, & GPIO_InitStructer);

TIM_DeInit(TIM2);
TIM_TimeBaseInitStructer.TIM_Period=999;
TIM_TimeBaseInitStructer.TIM_Prescaler=71; 
TIM_TimeBaseInitStructer.TIM_ClockDivision=TIM_CKD_DIV1;
TIM_TimeBaseInitStructer.TIM_CounterMode=TIM_CounterMode_Up;
TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructer);

TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
NVIC_Config();
TIM_Cmd(TIM2,DISABLE);

}

float Senor_Using(void)
{
	float length=0,sum=0;
	u16 tim;	
//    GPIO_ResetBits(GPIOD,GPIO_Pin_1);  
//	  delay_us(10);
		GPIO_SetBits(GPIOD,GPIO_Pin_1);
		delay_us(11); 
		GPIO_ResetBits(GPIOD,GPIO_Pin_1);
   
		while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)==RESET);
		TIM_Cmd(TIM2,ENABLE);
		
		while(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)==SET);
		
		TIM_Cmd(TIM2,DISABLE);
		tim=TIM_GetCounter(TIM2);
		
		length=(tim+overcount*1000)*0.0172;
    
		sum=length+sum;
		TIM2->CNT=0;  
		overcount=0; 
		delay_ms(50);
	length=sum;
	return length;
}
int main()
{
	  delay_init(72);
	  CH_SR04_Init();
	  OLED_Init();
	  while(1)
		{
			float x=Senor_Using();
			int xx=(int)x;
			int xxx;
			x=x-xx;
			xxx=x*10000;
			OLED_4num(0,0,xx);
			OLED_P6x8Str(30,0,".");
			
			OLED_4num(32,0,xxx);
	  }
}