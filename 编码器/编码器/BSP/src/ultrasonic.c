#include "ultrasonic.h"

float obs_distance[8];
u8  obs_discm[8];
u16 obsconsta[8]={0,0,0,0,0,0,0,0};
u16 obsconend[8]={0,0,0,0,0,0,0,0};
u8 Obs_Count=0;
u8 obs_state[8]={0,0,0,0,0,0,0,0};
u16 obsbits[8]={0x0008,0x0020,0x0080,0x0200,0x0800,0x2000,0x4000,0x8000};
u8  StartCap_Flag=0;
u16 ObsDataBits;
u8 obs_normal_count[8];
u8 obs_flag[8];
u8 dir_state = 0;
u8 last_dir_state = 0;
u8 obscmp[8] = {30,30,30,30,30,30,30,30};

void TimeUltra_Init()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	//基础设置，时基和比较输出设置，由于这里只需定时，所以不用OC比较输出
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	TIM_DeInit(TIM1);

	TIM_TimeBaseStructure.TIM_Period=65535;//装载值
	//prescaler is 1200,that is 72000000/72/500=2000Hz;
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;//分频系数
	//set clock division 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //or TIM_CKD_DIV2 or TIM_CKD_DIV4
	//count up
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	//clear the TIM3 overflow interrupt flag
	TIM_ClearFlag(TIM1,TIM_FLAG_Update);
	
	TIM_SetCounter(TIM1,0);
	//enable TIM3
	TIM_Cmd(TIM1,DISABLE);


	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 |
																 GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ;	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	      
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOE, &GPIO_InitStructure);
	 
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource5);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource7);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource9);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource11);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource13);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource14);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource15);
	 
	 
	 EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStructure);
	 	 EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStructure);
	 	 EXTI_InitStructure.EXTI_Line = EXTI_Line7;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStructure);
	 	 EXTI_InitStructure.EXTI_Line = EXTI_Line9;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStructure);
	 	 EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStructure);
	 	 EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStructure);
	 	 EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStructure);
	 	 EXTI_InitStructure.EXTI_Line = EXTI_Line15;
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	 EXTI_Init(&EXTI_InitStructure);
	 Exti_Set(0);
		 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 ;	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void Exti_Set(u8 en)
{
    EXTI->PR=0xeaa8;  
    if(en)
			EXTI->IMR|=0xeaa8;
    else EXTI->IMR&=~0xeaa8;
}

//将距离转换为（0~250）cm范围的数据，并存储obscmp数组中
void Obs_Analysis()
{
	u16 distance;
	u8 i;
	for(i=0;i<8;i++)
	{
		distance = (u16)(obs_distance[i]*100);
		obs_discm[i] = (u8)( distance > 250 ? 250 : distance );
	}
}