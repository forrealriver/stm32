#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "stm32f10x_it.h"
#include "oled.h"
#include "Encoder.h"
#include "delay.h"
#include "I2C.h"
#include "mpu6050.h"
#include "stm32f10x_usart.h"
int data1;
int data2;
int flag=0;
void Usart_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;  
    USART_InitTypeDef USART_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure;  
    USART_ClockInitTypeDef USART_ClockInitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);  
      
    /* Configure USART Tx as alternate function push-pull */  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
      
    /* Configure USART Rx as input floating */  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
      
    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
  
    USART_InitStructure.USART_BaudRate = 9600;  
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  
    USART_InitStructure.USART_Parity = USART_Parity_No;  
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
    USART_Init(USART2, &USART_InitStructure );   
		
    USART_ClockInitStruct.USART_Clock=USART_Clock_Disable;
		USART_ClockInitStruct.USART_CPOL=USART_CPOL_Low;
		USART_ClockInitStruct.USART_CPHA=USART_CPHA_2Edge;
	  USART_ClockInitStruct.USART_LastBit=USART_LastBit_Disable;
	  USART_ClockInit(USART2, &USART_ClockInitStruct); 
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 
    USART_Cmd(USART2, ENABLE);  
  
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
}

int main()
{
	  Usart_Init();
		OLED_Init();
	  delay_init(72);
	while(1)
	{
		OLED_4num(0,0,data1);
		OLED_4num(32,0,data2);
	}
    
}
