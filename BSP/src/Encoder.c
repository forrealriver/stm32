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
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // 初值为0
  TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_PPR)-1;  //最多计数4*ENCODER_PPR，如超出则启动TIM中断一次
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //向上计数
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  
 // Clear all pending interrupts
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//溢出中断开启
  //Reset counter
  TIM3->CNT = COUNTER_RESET;
  
  ENC_Clear_Speed_Buffer();
  
  TIM_Cmd(TIM3, ENABLE);  

}

/*******************************************************************************
* Function Name  : ENC_Get_Electrical_Angle
* Description    : Returns the absolute electrical Rotor angle 返回转的角度
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
* Description    : Clear speed buffer used for average speed calculation  清除速度标志
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
* Description    : Compute return latest speed measurement 返回一次周期的速度
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
   
    hEnc_Timer_Overflow_sample_one = hEncoder_Timer_Overflow; //第一次角度值样本1
    hCurrent_angle_sample_one = TIM3->CNT;//第一次角度值采样
    hEnc_Timer_Overflow_sample_two = hEncoder_Timer_Overflow;//第二次角度值样本2 
    hCurrent_angle_sample_two = TIM3->CNT;      //第二次角度值采样


    hEncoder_Timer_Overflow = 0;//重置计数周期，为下一次采样做准备
    haux = TIM3->CNT;   
    
    if (hEncoder_Timer_Overflow != 0) //检查是否复位成功
    {
      haux = TIM3->CNT; 
      hEncoder_Timer_Overflow = 0;            
    }
     
    if (hEnc_Timer_Overflow_sample_one != hEnc_Timer_Overflow_sample_two)//检查样本1,2是否溢出，如果溢出，则相信样本2的值
    { 
      hCurrent_angle_sample_one = hCurrent_angle_sample_two;
      hEnc_Timer_Overflow_sample_one = hEnc_Timer_Overflow_sample_two;
    }
    
    if ( (TIM3->CR1 & TIM_CounterMode_Down) == TIM_CounterMode_Down)  //计数方向判断，这个会影响编码器的计算，与编码器判断方向有关
    {//如果编码器下降计数——这个由TIM初始化的时候设定
      wDelta_angle = (s32)(hCurrent_angle_sample_one - hPrevious_angle - 
                    (hEnc_Timer_Overflow_sample_one) * (4*ENCODER_PPR));//两次采样值的差加上溢出中断的个数
    }
    else  
    {//如果编码器下降计数
      wDelta_angle = (s32)(hCurrent_angle_sample_one - hPrevious_angle + 
                    (hEnc_Timer_Overflow_sample_one) * (4*ENCODER_PPR));
    }
    
		//偏角乘上计数频率为速度
    temp = (signed long long)(wDelta_angle * SPEED_SAMPLING_FREQ);
    temp *= 10; 
    temp /= (4*ENCODER_PPR);//表示多少S转一圈,乘上4的原因请查看AB相编码的分频与倍频
        
  }
  else //上次数据是否清除
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
速度的平均值求法：可以当做速度的滤波处理
*******************************************************************************/
s16 ENC_Calc_Average_Speed(void)
{   
  s32 wtemp;
  u32 i;
  
  wtemp = ENC_Calc_Rot_Speed();//读取一次速度
        
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


