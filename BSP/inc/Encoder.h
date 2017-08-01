/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_ENCODER_H
#define __STM32F10x_ENCODER_H
#include "stm32f10x.h"
/* Private typedef -----------------------------------------------------------*/
typedef enum {DISPLAY_TIMCNT = 0,DISPLAY_THETA,DISPLAY_W} DisplayType;

/* Includes ------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SPEED_SAMPLING_TIME  9     // (9+1)*500usec = 10msec
#define ENCODER_PPR           (u16)(200)   // number of pulses per revolution
#define SPEED_BUFFER_SIZE 8

#define COUNTER_RESET   (u16)0
#define ICx_FILTER      (u8) 6 //ÂË²¨


#define U16_MAX 131000 //2^16-1
#define SPEED_SAMPLING_FREQ (u16)(2000/(SPEED_SAMPLING_TIME+1))
/* Exported functions ------------------------------------------------------- */
void ENC_Init(void);
s16 ENC_Get_Electrical_Angle(void);
void ENC_Clear_Speed_Buffer(void);
s16 ENC_Calc_Average_Speed(void);
extern u16 hEncoder_Timer_Overflow;
#endif  /*__STM32F10x_ENCODER_H*/
