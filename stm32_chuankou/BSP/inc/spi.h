#ifndef __SPI_H
#define __SPI_H
#include "NRF24L01.h"

#define SPI_CE_H()   GPIO_SetBits(GPIOC, GPIO_Pin_2) 
#define SPI_CE_L()   GPIO_ResetBits(GPIOC, GPIO_Pin_2)

#define SPI_CSN_H()  GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define SPI_CSN_L()  GPIO_ResetBits(GPIOA, GPIO_Pin_4)

void SPI2_Init(void);			 //��ʼ��SPI��
void SPI1_Config(void);
void SPI1_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI1_ReadWriteByte(u8 TxData);
		 
#endif

