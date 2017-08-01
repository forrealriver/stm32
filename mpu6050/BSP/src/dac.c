#include "dac.h"


__IO uint16_t DAC_ConvertedValue[2];


void DAC_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* 使能GPIOA时钟 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	
	/* 使能DAC时钟 */	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
  /* DAC的GPIO配置，模拟输入 */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
void DAC_Mode_Config(void)
{
	DMA_InitTypeDef  DMA_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;
	/* 使能DMA2时钟 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	
	/* 配置DMA2 */
  DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12RD_Address;					//外设数据地址
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&DAC_ConvertedValue ;				//内存数据地址 DualSine12bit
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;											//数据传输方向内存至外设
  DMA_InitStructure.DMA_BufferSize = 32;																	//缓存大小为32字节	
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;				//外设数据地址固定	
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;									//内存数据地址自增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;	//外设数据以字为单位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;					//内存数据以字为单位	
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;													//循环模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;											//高DMA通道优先级
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;														//非内存至内存模式	

  DMA_Init(DMA2_Channel4, &DMA_InitStructure);
	
  /* 使能DMA2-14通道 */
  DMA_Cmd(DMA2_Channel4, ENABLE);	
	
	
  /* 配置DAC 通道1 */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;						    //DAC自动转换
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;	//不使用波形发生器
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;	//不使用DAC输出缓冲
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);
  /* 配置DAC 通道2 */
  DAC_Init(DAC_Channel_2, &DAC_InitStructure);
  /* 使能通道1 由PA4输出 */
  DAC_Cmd(DAC_Channel_1, ENABLE);
  /* 使能通道2 由PA5输出 */
  DAC_Cmd(DAC_Channel_2, ENABLE);
  /* 使能DAC的DMA请求 */
  DAC_DMACmd(DAC_Channel_1, ENABLE);
//  DAC_DMACmd(DAC_Channel_2, ENABLE);
	/* 输出固定电平 */
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
	DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);
}
void DAC_Config(void)
{
	DAC_GPIO_Config();
	DAC_Mode_Config();
}
/* 设置DAC软件输出的值 */
/* 输出范围是0 ~ 4095  */
/* 电压是0 ~ 3.3V      */
void DAC_OutPut_Data(uint16_t data0,uint16_t data1)
{
	DAC_ConvertedValue[0] = data0;
	DAC_SetChannel1Data(DAC_Align_12b_R,DAC_ConvertedValue[0]);
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);//通道1 PA.4
	
	DAC_ConvertedValue[1] = data1;
	DAC_SetChannel2Data(DAC_Align_12b_R,DAC_ConvertedValue[1]);
	DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);//通道2 PA.5
}
	
