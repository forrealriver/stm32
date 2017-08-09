#include "spi.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//SPI���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

void SPI1_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);  
    
    //  PA5--CLK  PA7--MOSI  
    GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_5|GPIO_Pin_7; 
    GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_AF_PP; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    //PA6--MISO 
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    //PA4--NSS
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);
 
		//PC2---CE
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; 
    GPIO_Init(GPIOC, &GPIO_InitStructure);
		
		//PC3---IRQ  
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; //��������
    GPIO_Init(GPIOC, &GPIO_InitStructure);
 
	                     
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                      //��ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                  //һ��ת��8λ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                        //���е�ƽ�͵�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                      //��һ�������ز���
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                         // NSSΪ���ģʽ
	SPI_InitStructure.SPI_BaudRatePrescaler =SPI_BaudRatePrescaler_8; //9MHz
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;        					//���ݴ����λ��ǰ
	SPI_InitStructure.SPI_CRCPolynomial = 7;                           //CRCУ��ģʽ
    SPI_Init(SPI1, &SPI_InitStructure);                                //��ʼ��
    
   // SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
    
    SPI_Cmd(SPI1, ENABLE); //SPI1
	SPI1_ReadWriteByte(0xff);//��������	
}
//SPI �ٶ����ú���
//SpeedSet:
//SPI_BaudRatePrescaler_2   2��Ƶ   
//SPI_BaudRatePrescaler_8   8��Ƶ   
//SPI_BaudRatePrescaler_16  16��Ƶ  
//SPI_BaudRatePrescaler_256 256��Ƶ 
  
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI1->CR1&=0XFFC7;
	SPI1->CR1|=SPI_BaudRatePrescaler;	//����SPI2�ٶ� 
	SPI_Cmd(SPI1,ENABLE); 

} 


//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI1_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����					    
}









































