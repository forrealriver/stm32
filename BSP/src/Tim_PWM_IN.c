#include "TIM_PWM_IN.h"

Data_In PWM_In;//1000~2000


void TIM4_Cap_Init(void)
{	 
	  GPIO_InitTypeDef GPIO_InitStructure;
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_ICInitTypeDef  TIM4_ICInitStructure;

	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	 //使能TIM4时钟
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //使能GPIOD时钟
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //使能复用端口功能时钟，使能AFIO功能的时钟
      
	  GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  //进行重映射
	
		//对捕获的引脚进行配置
	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;             //PB6 清除之前设置  
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;    //下拉输入        这样设置则只采集高电平，即为上升沿捕获，若为上升下降沿捕获则采用浮点输入模式，下降沿捕获请自己想。。。
	  GPIO_Init(GPIOD, &GPIO_InitStructure);
	  GPIO_ResetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);		

	  //初始化定时器4 TIM4	 
	  TIM_TimeBaseStructure.TIM_Period = 0XFFFF;                      //设定计数器自动重装值 
	  TIM_TimeBaseStructure.TIM_Prescaler =71; 	                 //预分频器   
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	  //初始化TIM4输入捕获参数
	  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1;                //CC1S=01 	选择输入端 IC1映射到TI1上 IC2映射到TI2上.....
  	TIM4_ICInitStructure.TIM_ICPolarity =TIM_ICPolarity_Rising;	   //上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3;                //CC1S=01 	选择输入端 IC1映射到TI1上 IC2映射到TI2上.....
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	
	  TIM_Cmd(TIM4,ENABLE ); 
		
	  TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);        //允许更新中断 ,允许CC1IE捕获中断更新数据,既可以实施更改PWM波输出的值
	  TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
			
}


