#ifndef __USART_H_
#define __USART_H_
#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>
#include <system_stm32f10x.h> 
#include "string.h"

#define BLUETOOTH	USART1
#define USART			USART2
#define OBSTACLE	USART3


#define BLUETOOTH_RXIT_EN(x) 	USART_ITConfig(BLUETOOTH,USART_IT_RXNE,x);
#define USART_RXIT_EN(x) 			USART_ITConfig(USART,USART_IT_RXNE,x);
#define OBSTACLE_RXIT_EN(x) 	USART_ITConfig(OBSTACLE,USART_IT_RXNE,x);

extern float OutData[4];

void BlueTooth_Init(u32 BaudRate);
void Usart_Init(u32 BaudRate);
void Obstacle_Init(u32 BaudRate);


uint8_t USART_SendChar(USART_TypeDef* USARTx,unsigned char DataToSend);
void USART_SendString(USART_TypeDef* USARTx,char *str);
void USART_SendInt(USART_TypeDef* USARTx,int num);
void USART_SendFloat(USART_TypeDef* USARTx,float num);
int  fputc(int ch, FILE *f);
void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...);

void PC_Debug_Show(u8 num,u16 sta);
static char *itoa(int value, char *string, int radix);

//float转换成str，保留四位小数
void ftostr(float num,char *str);
void myitoa(int num,char *str);

unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT);
void OutPut_Data(void);


#endif
