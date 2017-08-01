#include "include.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
s16 ENC_Calc_Rot_Speed(void);

/* Private variables ---------------------------------------------------------*/
static s16 hPrevious_angle, hSpeed_Buffer[SPEED_BUFFER_SIZE], hRot_Speed;
static u8 bSpeed_Buffer_Index = 0;
u16 hEncoder_Timer_Overflow; 
static int bIs_First_Measurement = SUCCESS;
/*******************************************************************************
* Function Name  : ENC_Init
* Description    : General Purpose Timer 3 set-up for encoder speed/position 
*                  sensors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  
/* Encoder unit connected to TIM3, 4X mode */    
  GPIO_InitTypeDef GPIO_InitStructure;
  /* TIM3 clock source enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  /* Enable GPIOA, clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.06,07 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  

  /* Timer configuration in Encoder mode */
  TIM_DeInit(TIM3);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // ��ֵΪ0
  TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_PPR)-1;  //������4*ENCODER_PPR���糬��������TIM�ж�һ��
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //���ϼ���
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  
 // Clear all pending interrupts
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//����жϿ���
  //Reset counter
  TIM3->CNT = COUNTER_RESET;
  
  ENC_Clear_Speed_Buffer();
  
  TIM_Cmd(TIM3, ENABLE);  

}

/*******************************************************************************
* Function Name  : ENC_Get_Electrical_Angle
* Description    : Returns the absolute electrical Rotor angle ����ת�ĽǶ�
* Input          : None
* Output         : None
* Return         : Rotor electrical angle: 0 -> 0 degrees, 
*                                          S16_MAX-> 180 degrees, 
*                                          S16_MIN-> -180 degrees                  
*******************************************************************************/
s16 ENC_Get_Electrical_Angle(void)
{
  s32 temp;
  
	temp = (s32)(TIM_GetCounter(TIM3)) * (s32)(U16_MAX / (4*ENCODER_PPR));
  return((s16)(temp/65536)); // s16 result
}

/*******************************************************************************
* Function Name  : ENC_Clear_Speed_Buffer
* Description    : Clear speed buffer used for average speed calculation  ����ٶȱ�־
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_Clear_Speed_Buffer(void)
{   
  u32 i;

  for (i=0;i<SPEED_BUFFER_SIZE;i++)
  {
    hSpeed_Buffer[i] = 0;
  }
  bIs_First_Measurement = SUCCESS;
}

/*******************************************************************************
* Function Name  : ENC_Calc_Rot_Speed
* Description    : Compute return latest speed measurement ����һ�����ڵ��ٶ�
* Input          : None
* Output         : s16
* Return         : Return the speed in 0.1 Hz resolution.                    
*******************************************************************************/
s16 ENC_Calc_Rot_Speed(void)
{   
  s32 wDelta_angle;
  u16 hEnc_Timer_Overflow_sample_one, hEnc_Timer_Overflow_sample_two;
  u16 hCurrent_angle_sample_one, hCurrent_angle_sample_two;
  signed long long temp;
  s16 haux;
  
  if (!bIs_First_Measurement)
  {
   
    hEnc_Timer_Overflow_sample_one = hEncoder_Timer_Overflow; //��һ�νǶ�ֵ����1
    hCurrent_angle_sample_one = TIM3->CNT;//��һ�νǶ�ֵ����
    hEnc_Timer_Overflow_sample_two = hEncoder_Timer_Overflow;//�ڶ��νǶ�ֵ����2 
    hCurrent_angle_sample_two = TIM3->CNT;      //�ڶ��νǶ�ֵ����


    hEncoder_Timer_Overflow = 0;//���ü������ڣ�Ϊ��һ�β�����׼��
    haux = TIM3->CNT;   
    
    if (hEncoder_Timer_Overflow != 0) //����Ƿ�λ�ɹ�
    {
      haux = TIM3->CNT; 
      hEncoder_Timer_Overflow = 0;            
    }
     
    if (hEnc_Timer_Overflow_sample_one != hEnc_Timer_Overflow_sample_two)//�������1,2�Ƿ������������������������2��ֵ
    { 
      hCurrent_angle_sample_one = hCurrent_angle_sample_two;
      hEnc_Timer_Overflow_sample_one = hEnc_Timer_Overflow_sample_two;
    }
    
    if ( (TIM3->CR1 & TIM_CounterMode_Down) == TIM_CounterMode_Down)  //���������жϣ������Ӱ��������ļ��㣬��������жϷ����й�
    {//����������½��������������TIM��ʼ����ʱ���趨
      wDelta_angle = (s32)(hCurrent_angle_sample_one - hPrevious_angle - 
                    (hEnc_Timer_Overflow_sample_one) * (4*ENCODER_PPR));//���β���ֵ�Ĳ��������жϵĸ���
    }
    else  
    {//����������½�����
      wDelta_angle = (s32)(hCurrent_angle_sample_one - hPrevious_angle + 
                    (hEnc_Timer_Overflow_sample_one) * (4*ENCODER_PPR));
    }
    
		//ƫ�ǳ��ϼ���Ƶ��Ϊ�ٶ�
    temp = (signed long long)(wDelta_angle * SPEED_SAMPLING_FREQ);
    temp *= 10; 
    temp /= (4*ENCODER_PPR);//��ʾ����SתһȦ,����4��ԭ����鿴AB�����ķ�Ƶ�뱶Ƶ
        
  }
  else //�ϴ������Ƿ����
  {
    bIs_First_Measurement = ERROR;
    temp = 0;
    hEncoder_Timer_Overflow = 0;
    haux = TIM3->CNT;       
    if (hEncoder_Timer_Overflow != 0) 
    {
      haux = TIM3->CNT; 
      hEncoder_Timer_Overflow = 0;            
    }
  }
  
  hPrevious_angle = haux;  
 
  return((s16) temp);
}

/*******************************************************************************
�ٶȵ�ƽ��ֵ�󷨣����Ե����ٶȵ��˲�����
*******************************************************************************/
s16 ENC_Calc_Average_Speed(void)
{   
  s32 wtemp;
  u32 i;
  
  wtemp = ENC_Calc_Rot_Speed();//��ȡһ���ٶ�
        
  hSpeed_Buffer[bSpeed_Buffer_Index] = (s16)wtemp;
  bSpeed_Buffer_Index++;
  
  if (bSpeed_Buffer_Index == SPEED_BUFFER_SIZE) 
  {
    bSpeed_Buffer_Index = 0;
  }

  wtemp=0;

  for (i=0;i<SPEED_BUFFER_SIZE;i++)
  {
    wtemp += hSpeed_Buffer[i];
  }
  wtemp /= SPEED_BUFFER_SIZE;
  
  hRot_Speed = ((s16)(wtemp));
	return hRot_Speed;
}


