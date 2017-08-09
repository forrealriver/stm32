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

void TIM_PWM_Init(u16 arr,u16 psc) ;
void Angle(u8 ID ,float angle)
{
	  u16 an1,an2;
	switch(ID)
	{
		case 1: an1=(u16)(u16)(46.0*angle/9.0+249.0);  
    TIM_SetCompare1(TIM4,an1);    break;
		case 2:an2=(u16)(u16)(46.0*angle/9.0+249.0);  
    TIM_SetCompare2(TIM4,an2);    break;
		default: break;  
	}
}
int main()
{
	  u16 pwmval1=749;
	  float x=0;
	int flag=0;
	  delay_init(72);
	  TIM_PWM_Init(9999,143);// ±–ÚŒ Ã‚
	  OLED_Init();
	  //Angle(2,180);
	  TIM_SetCompare2(TIM4,1200);
	 delay_ms(50);
	  while(0){
	   if(flag==0)
			x=x+1;
		 else if(flag==1)
			 x=x-1;
	   delay_ms(5);
	    Angle(2,x);
			if(x==180)
				flag=1;
			else if(x==0)
				flag=0;
	  }
}

void TIM_PWM_Init(u16 arr,u16 psc)  
{    
    GPIO_InitTypeDef GPIO_InitStructure;  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef  TIM_OCInitStructure;  
  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);                                                                  
      
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12 | GPIO_Pin_13; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	
    GPIO_Init(GPIOD,&GPIO_InitStructure);  
  
      
    TIM_TimeBaseStructure.TIM_Period = arr; 
    TIM_TimeBaseStructure.TIM_Prescaler =psc; 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
  
   
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
  
		
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
      
    TIM_ARRPreloadConfig(TIM4, ENABLE); 
    TIM_CtrlPWMOutputs(TIM4,ENABLE);    
    TIM_Cmd(TIM4, ENABLE); 
}  