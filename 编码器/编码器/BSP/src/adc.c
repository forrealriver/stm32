#include "adc.h"
#include "math.h"

struct Adc_System syscharacter;

///////////////////��DMA�Ķ�ͨ��ADC�ɼ�///////////////////
static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable ADC1 and GPIOC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 | RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);				// PA5,����ʱ������������
}

static void ADC2_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	/* ADC1 configuration */
	ADC_DeInit(ADC2);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//����ADCģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 	 //ɨ��ģʽ��ɨ��ģʽ���ڶ�ͨ���ɼ�
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//��������ת��ģʽ������ͣ�ؽ���ADCת��
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//��ʹ���ⲿ����ת��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	//�ɼ������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	 	//Ҫת����ͨ����Ŀ9
	ADC_Init(ADC2, &ADC_InitStructure);
	
	/*����ADCʱ�ӣ�ΪPCLK2��8��Ƶ����9Hz*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	/* Enable ADC1 */
	ADC_Cmd(ADC2, ENABLE);
	
	/*��λУ׼�Ĵ��� */   
	ADC_ResetCalibration(ADC2);
	/*�ȴ�У׼�Ĵ�����λ��� */
	while(ADC_GetResetCalibrationStatus(ADC2));
	
	/* ADCУ׼ */
	ADC_StartCalibration(ADC2);
	/* �ȴ�У׼���*/
	while(ADC_GetCalibrationStatus(ADC2));
	
	/* ����û�в����ⲿ����������ʹ���������ADCת�� */ 
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);
}

/*
 * ��������ADC1_Init
 * ����  ����
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void ADC2_Init(void)
{
	ADC_GPIO_Config();
	ADC2_Mode_Config();
}

uint16_t ADC2_GetConvert(uint8_t ch)
{
	unsigned int result=0;
	unsigned char i;
	
  //����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��ch,�������˳��ֵ����Ϊ1,����ʱ��Ϊ239.5����	  			    
  for(i=0;i<10;i++)
	{
		ADC_SoftwareStartConvCmd(ADC2, ENABLE);		//ʹ��ָ����ADC1�����ת����������	 
		while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//�ȴ�ת������
		result+=ADC_GetConversionValue(ADC2);
	}
	result=result/10;	 //ȡ10�β�����ƽ��ֵ
	return result;	//����ƽ��ֵ
}

//���ѹvol����curƽ��ֵ
void PowConvert(uint32_t cur,uint32_t vol,uint16_t num)//numΪ�����ɼ��Ĵ���
{
		uint32_t avrcur;
		uint32_t avrvol;
		float cvol1,vvol1;
		float cvol2,vvol2;
		float current;
		avrcur = cur/num;
		avrvol = vol/num;
		cvol1 = avrcur*3.37/4096;	//�ο���ѹ3.37V��ADΪ12λֵ
		vvol1 = avrvol*3.37/4096;
		
		cvol2 = cvol1*9.8/6.2;	//�������ڵ�ѹ���ߣ�����(6.2/(3.6+6.2))k��ѹʽ�ɼ�
		vvol2 = vvol1*101/10;		//�������ڵ�ѹ���ߣ�����(10/(91+10))k��ѹʽ�ɼ�
		
		current = (cvol2-2.50)/0.1; //����������ģ�����Ϊ100mv/A�������ʱ�����ѹΪ2.5V
		
		syscharacter.current = current;
		syscharacter.voltage = vvol2;
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

