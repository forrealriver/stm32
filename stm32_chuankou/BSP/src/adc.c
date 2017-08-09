#include "adc.h"
#include "math.h"

struct Adc_System syscharacter;

///////////////////无DMA的多通道ADC采集///////////////////
static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable ADC1 and GPIOC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 | RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);				// PA5,输入时不用设置速率
}

static void ADC2_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	/* ADC1 configuration */
	ADC_DeInit(ADC2);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//独立ADC模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 	 //扫描模式，扫描模式用于多通道采集
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//开启连续转换模式，即不停地进行ADC转换
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//不使用外部触发转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	//采集数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	 	//要转换的通道数目9
	ADC_Init(ADC2, &ADC_InitStructure);
	
	/*配置ADC时钟，为PCLK2的8分频，即9Hz*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	/* Enable ADC1 */
	ADC_Cmd(ADC2, ENABLE);
	
	/*复位校准寄存器 */   
	ADC_ResetCalibration(ADC2);
	/*等待校准寄存器复位完成 */
	while(ADC_GetResetCalibrationStatus(ADC2));
	
	/* ADC校准 */
	ADC_StartCalibration(ADC2);
	/* 等待校准完成*/
	while(ADC_GetCalibrationStatus(ADC2));
	
	/* 由于没有采用外部触发，所以使用软件触发ADC转换 */ 
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);
}

/*
 * 函数名：ADC1_Init
 * 描述  ：无
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
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
	
  //设置指定ADC的规则组通道，设置它们的转化顺序和采样时间
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道ch,规则采样顺序值序列为1,采样时间为239.5周期	  			    
  for(i=0;i<10;i++)
	{
		ADC_SoftwareStartConvCmd(ADC2, ENABLE);		//使能指定的ADC1的软件转换启动功能	 
		while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//等待转换结束
		result+=ADC_GetConversionValue(ADC2);
	}
	result=result/10;	 //取10次采样的平均值
	return result;	//返回平均值
}

//求电压vol电流cur平均值
void PowConvert(uint32_t cur,uint32_t vol,uint16_t num)//num为连续采集的次数
{
		uint32_t avrcur;
		uint32_t avrvol;
		float cvol1,vvol1;
		float cvol2,vvol2;
		float current;
		avrcur = cur/num;
		avrvol = vol/num;
		cvol1 = avrcur*3.37/4096;	//参考电压3.37V，AD为12位值
		vvol1 = avrvol*3.37/4096;
		
		cvol2 = cvol1*9.8/6.2;	//这里由于电压过高，采用(6.2/(3.6+6.2))k分压式采集
		vvol2 = vvol1*101/10;		//这里由于电压过高，采用(10/(91+10))k分压式采集
		
		current = (cvol2-2.50)/0.1; //电流传感器模拟输出为100mv/A，零电流时输出电压为2.5V
		
		syscharacter.current = current;
		syscharacter.voltage = vvol2;
}


/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

