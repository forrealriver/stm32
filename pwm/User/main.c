#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "stm32f10x_it.h"

void RCC_cfg();
void GPIO_cfg();
void TIMER_cfg();
void PWM_cfg();
//占空比，取值范围为0-100
int dutyfactor1 = 75;
int dutyfactor2 = 50;
int dutyfactor3 = 25;
int dutyfactor4 = 10;
 
int main()
{
     int Temp;
       RCC_cfg();
       GPIO_cfg();
       TIMER_cfg();
       PWM_cfg();
 
       //使能TIM2计时器，开始输出PWM
       TIM_Cmd(TIM2, ENABLE);
 
       while(1);
}
 
void RCC_cfg()
{
       //定义错误状态变量
       ErrorStatus HSEStartUpStatus;
      
       //将RCC寄存器重新设置为默认值
       RCC_DeInit();
 
       //打开外部高速时钟晶振
       RCC_HSEConfig(RCC_HSE_ON);
 
       //等待外部高速时钟晶振工作
       HSEStartUpStatus = RCC_WaitForHSEStartUp();
       if(HSEStartUpStatus == SUCCESS)
       {
              //设置AHB时钟(HCLK)为系统时钟
              RCC_HCLKConfig(RCC_SYSCLK_Div1);
 
              //设置高速AHB时钟(APB2)为HCLK时钟
              RCC_PCLK2Config(RCC_HCLK_Div1);
 
              //设置低速AHB时钟(APB1)为HCLK的2分频
              RCC_PCLK1Config(RCC_HCLK_Div2);

              //设置PLL时钟，为HSE的9倍频 8MHz * 9 = 72MHz
              RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
 
              //使能PLL
              RCC_PLLCmd(ENABLE);
 
              //等待PLL准备就绪
              while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
 
              //设置PLL为系统时钟源
              RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
 
              //判断PLL是否是系统时钟
              while(RCC_GetSYSCLKSource() != 0x08);
       }
 
       //开启TIM2的时钟
       RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
       //开启GPIOA的时钟和复用功能
       RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
 
}
 
void GPIO_cfg()
{
       GPIO_InitTypeDef GPIO_InitStructure;
 
      
       //部分映射，将TIM2_CH2映射到PB5
//     GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
//     GPIO_PinRemapConfig(GPIO_PartialRemap_TIM2, ENABLE);
 
       //选择引脚5
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0;
       //输出频率最大50MHz                                                        
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       //复用推挽输出                                              
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
 
       GPIO_Init(GPIOA,&GPIO_InitStructure);
}
 
void TIMER_cfg()
{
       TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
 
       //重新将Timer设置为缺省值
       TIM_DeInit(TIM2);
       //采用内部时钟给TIM2提供时钟源
       TIM_InternalClockConfig(TIM2);
       //预分频系数为0，即不进行预分频，此时TIMER的频率为72MHz
       TIM_TimeBaseStructure.TIM_Prescaler = 143;
       //设置时钟分割
       TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
       //设置计数器模式为向上计数模式
       TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
       //设置计数溢出大小，每计7200个数就产生一个更新事件，即PWM的输出频率为10kHz
       TIM_TimeBaseStructure.TIM_Period = 9999;
       //将配置应用到TIM2中
       TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	     
	       //清除溢出中断标志
       //TIM_ClearFlag(TIM2, TIM_FLAG_Update);
       //禁止ARR预装载缓冲器
       TIM_ARRPreloadConfig(TIM2, ENABLE);
       //开启TIM2的中断
       //TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
}
 
void PWM_cfg()
{
       TIM_OCInitTypeDef TimOCInitStructure;
       //设置缺省值
       TIM_OCStructInit(&TimOCInitStructure);
       //PWM模式1输出
       TimOCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
       
       //TIM输出比较极性高
       TimOCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
       
       
       //设置占空比，占空比=(CCRx/ARR)*100%或(TIM_Pulse/TIM_Period)*100%
	     TimOCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
       TimOCInitStructure.TIM_Pulse = dutyfactor1 * 9999 / 100;
       TIM_OC1Init(TIM2, &TimOCInitStructure);
	     TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	
       //TIM2的CH2输出
	     //使能输出状态
	     TimOCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
       TimOCInitStructure.TIM_Pulse = dutyfactor2 * 9999 / 100;
       TIM_OC2Init(TIM2, &TimOCInitStructure);
	     TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);
	
			 TimOCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	     TimOCInitStructure.TIM_Pulse = dutyfactor3 * 9999 / 100;
	     TIM_OC3Init(TIM2, &TimOCInitStructure);
	     TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
			 
			 TimOCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	     TimOCInitStructure.TIM_Pulse = dutyfactor4 * 9999 / 100;
	     TIM_OC4Init(TIM2, &TimOCInitStructure);
	     TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Enable);
	
       //设置TIM2的PWM输出为使能
       TIM_CtrlPWMOutputs(TIM2,ENABLE);
}