#include "capture_in.h"

capture_ch capture_value;//1000~2000



void TIM4_Cap_Init(void)
{	 
	  GPIO_InitTypeDef         GPIO_InitStructure;
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_ICInitTypeDef  TIM4_ICInitStructure;

	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	 //使能TIM4时钟
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //使能GPIOB时钟
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //使能AFIO功能的时钟
    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  //进行重映射
	
	
	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;             //PB6 清除之前设置  
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;            
	  GPIO_Init(GPIOD, &GPIO_InitStructure);
	  GPIO_ResetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);		

	  //初始化定时器4 TIM4	 
	  TIM_TimeBaseStructure.TIM_Period = 0XFFFF;                      //设定计数器自动重装值 
	  TIM_TimeBaseStructure.TIM_Prescaler =71; 	                 //预分频器   
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);              //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	  //初始化TIM4输入捕获参数
	  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1;                //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPolarity =TIM_ICPolarity_Rising;	   //上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2;                //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3;                //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4;                //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //上升沿捕获
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //配置输入分频,不分频 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	  TIM_Cmd(TIM4,ENABLE ); 
		
	  TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);        //允许更新中断 ,允许CC1IE捕获中断	
	  TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
	  TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
	  TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);
			
}

//定时器4中断服务程序	 
void TIM4_IRQHandler(void)
{ 
    if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)            //捕获1发生捕获事件
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC1); //清除中断标志位
			capture_value.channel1.count++;	    
		}	
		if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)            //捕获1发生捕获事件
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC2); //清除中断标志位
			capture_value.channel2.count++;	    
		}	
		if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)            //捕获1发生捕获事件
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC3); //清除中断标志位
			capture_value.channel3.count++;	    
		}	
		if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)            //捕获1发生捕获事件
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC4); //清除中断标志位
			capture_value.channel4.count++;	    
		}	
	
//    if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)            //捕获1发生捕获事件
//		{	
//			TIM_ClearITPendingBit(TIM4, TIM_IT_CC4); //清除中断标志位
//			if(TIM4CH4_CAPTURE_STA&0X40)		                       //捕获到一个下降沿 		
//			{	  			
//				TIM4CH4_CAPTURE_STA|=0X80;		                       //标记成功捕获到一次上升沿
//				TIM4CH4_CAPTURE_VAL=TIM_GetCapture4(TIM4);
//		   		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
//			}else  								                                 //还未开始,第一次捕获上升沿
//			{
//				TIM4CH4_CAPTURE_STA=0;			                         //清空
//				TIM4CH4_CAPTURE_VAL=0;
//	 			TIM_SetCounter(TIM4,0);
//				TIM4CH4_CAPTURE_STA|=0X40;		                        //标记捕获到了上升沿
//		    TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
//			}		    
//		}		
}

//获取4路PWM值
void Get_CaptureValue(void)
{
		capture_value.channel1.histor = capture_value.channel1.origin;
		capture_value.channel1.origin = capture_value.channel1.count;
		capture_value.channel1.count = 0;
		capture_value.channel2.histor = capture_value.channel2.origin;
		capture_value.channel2.origin = capture_value.channel2.count;
		capture_value.channel2.count = 0;
		capture_value.channel3.histor = capture_value.channel3.origin;
		capture_value.channel3.origin = capture_value.channel3.count;
		capture_value.channel3.count = 0;
		capture_value.channel4.histor = capture_value.channel4.origin;
		capture_value.channel4.origin = capture_value.channel4.count;
		capture_value.channel4.count = 0;
	  TIM_SetCounter(TIM4,0);
}


void InPulseCount_Init()
{
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_DeInit(TIM8);
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;		//计数上线	
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	//pwm时钟分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
	TIM_ETRClockMode2Config(TIM8, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted,0);
	TIM_SetCounter(TIM8,0);
	TIM_Cmd(TIM8, ENABLE);
}

void Read_PulseValue()
{
	capture_value.channel_pulse.histor = capture_value.channel_pulse.origin;
	capture_value.channel_pulse.origin = TIM8->CNT;
	TIM_SetCounter(TIM8,0);
}
