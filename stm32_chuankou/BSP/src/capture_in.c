#include "capture_in.h"

capture_ch capture_value;//1000~2000



void TIM4_Cap_Init(void)
{	 
	  GPIO_InitTypeDef         GPIO_InitStructure;
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_ICInitTypeDef  TIM4_ICInitStructure;

	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	 //ʹ��TIM4ʱ��
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //ʹ��GPIOBʱ��
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //ʹ��AFIO���ܵ�ʱ��
    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);  //������ӳ��
	
	
	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;             //PB6 ���֮ǰ����  
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;            
	  GPIO_Init(GPIOD, &GPIO_InitStructure);
	  GPIO_ResetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);		

	  //��ʼ����ʱ��4 TIM4	 
	  TIM_TimeBaseStructure.TIM_Period = 0XFFFF;                      //�趨�������Զ���װֵ 
	  TIM_TimeBaseStructure.TIM_Prescaler =71; 	                 //Ԥ��Ƶ��   
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);              //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	  //��ʼ��TIM4���벶�����
	  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1;                //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPolarity =TIM_ICPolarity_Rising;	   //�����ز���
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //���������Ƶ,����Ƶ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2;                //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //�����ز���
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //���������Ƶ,����Ƶ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3;                //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //�����ز���
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //���������Ƶ,����Ƶ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
		TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4;                //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	   //�����ز���
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //���������Ƶ,����Ƶ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	  TIM_Cmd(TIM4,ENABLE ); 
		
	  TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);        //��������ж� ,����CC1IE�����ж�	
	  TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
	  TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);
	  TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);
			
}

//��ʱ��4�жϷ������	 
void TIM4_IRQHandler(void)
{ 
    if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)            //����1���������¼�
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC1); //����жϱ�־λ
			capture_value.channel1.count++;	    
		}	
		if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)            //����1���������¼�
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC2); //����жϱ�־λ
			capture_value.channel2.count++;	    
		}	
		if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)            //����1���������¼�
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC3); //����жϱ�־λ
			capture_value.channel3.count++;	    
		}	
		if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)            //����1���������¼�
		{	
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC4); //����жϱ�־λ
			capture_value.channel4.count++;	    
		}	
	
//    if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)            //����1���������¼�
//		{	
//			TIM_ClearITPendingBit(TIM4, TIM_IT_CC4); //����жϱ�־λ
//			if(TIM4CH4_CAPTURE_STA&0X40)		                       //����һ���½��� 		
//			{	  			
//				TIM4CH4_CAPTURE_STA|=0X80;		                       //��ǳɹ�����һ��������
//				TIM4CH4_CAPTURE_VAL=TIM_GetCapture4(TIM4);
//		   		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
//			}else  								                                 //��δ��ʼ,��һ�β���������
//			{
//				TIM4CH4_CAPTURE_STA=0;			                         //���
//				TIM4CH4_CAPTURE_VAL=0;
//	 			TIM_SetCounter(TIM4,0);
//				TIM4CH4_CAPTURE_STA|=0X40;		                        //��ǲ�����������
//		    TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
//			}		    
//		}		
}

//��ȡ4·PWMֵ
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
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;		//��������	
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	//pwmʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		//���ϼ���
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
