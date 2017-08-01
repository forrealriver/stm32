#ifndef __CAPTURE_IN_H_
#define __CAPTURE_IN_H_
#include "stm32f10x.h"

typedef struct capture_time{
				int16_t origin;  //原始值
				int32_t averag;  //平均值
				int16_t histor;	//历史值
				int32_t count; 
				}_capture; 

typedef struct capture_ch{
				_capture channel1;
				_capture channel2;
				_capture channel3;
				_capture channel4;
				_capture channel_pulse;
				}capture_ch;

				
extern capture_ch capture_value;

				
void TIM4_Cap_Init(void);
void Get_CaptureValue(void);
void InPulseCount_Init();
void Read_PulseValue(); 
#endif
