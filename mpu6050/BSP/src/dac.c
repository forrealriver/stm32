#include "dac.h"


__IO uint16_t DAC_ConvertedValue[2];


void DAC_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* ʹ��GPIOAʱ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	
	/* ʹ��DACʱ�� */	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	
  /* DAC��GPIO���ã�ģ������ */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
void DAC_Mode_Config(void)
{
	DMA_InitTypeDef  DMA_InitStructure;
	DAC_InitTypeDef  DAC_InitStructure;
	/* ʹ��DMA2ʱ�� */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	
	/* ����DMA2 */
  DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12RD_Address;					//�������ݵ�ַ
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&DAC_ConvertedValue ;				//�ڴ����ݵ�ַ DualSine12bit
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;											//���ݴ��䷽���ڴ�������
  DMA_InitStructure.DMA_BufferSize = 32;																	//�����СΪ32�ֽ�	
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;				//�������ݵ�ַ�̶�	
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;									//�ڴ����ݵ�ַ����
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;	//������������Ϊ��λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;					//�ڴ���������Ϊ��λ	
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;													//ѭ��ģʽ
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;											//��DMAͨ�����ȼ�
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;														//���ڴ����ڴ�ģʽ	

  DMA_Init(DMA2_Channel4, &DMA_InitStructure);
	
  /* ʹ��DMA2-14ͨ�� */
  DMA_Cmd(DMA2_Channel4, ENABLE);	
	
	
  /* ����DAC ͨ��1 */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;						    //DAC�Զ�ת��
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;	//��ʹ�ò��η�����
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;	//��ʹ��DAC�������
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);
  /* ����DAC ͨ��2 */
  DAC_Init(DAC_Channel_2, &DAC_InitStructure);
  /* ʹ��ͨ��1 ��PA4��� */
  DAC_Cmd(DAC_Channel_1, ENABLE);
  /* ʹ��ͨ��2 ��PA5��� */
  DAC_Cmd(DAC_Channel_2, ENABLE);
  /* ʹ��DAC��DMA���� */
  DAC_DMACmd(DAC_Channel_1, ENABLE);
//  DAC_DMACmd(DAC_Channel_2, ENABLE);
	/* ����̶���ƽ */
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
	DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);
}
void DAC_Config(void)
{
	DAC_GPIO_Config();
	DAC_Mode_Config();
}
/* ����DAC��������ֵ */
/* �����Χ��0 ~ 4095  */
/* ��ѹ��0 ~ 3.3V      */
void DAC_OutPut_Data(uint16_t data0,uint16_t data1)
{
	DAC_ConvertedValue[0] = data0;
	DAC_SetChannel1Data(DAC_Align_12b_R,DAC_ConvertedValue[0]);
	DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);//ͨ��1 PA.4
	
	DAC_ConvertedValue[1] = data1;
	DAC_SetChannel2Data(DAC_Align_12b_R,DAC_ConvertedValue[1]);
	DAC_SoftwareTriggerCmd(DAC_Channel_2,ENABLE);//ͨ��2 PA.5
}
	
