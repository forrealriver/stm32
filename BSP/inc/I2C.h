#ifndef __I2C_H__
#define __I2C_H__
#include "stm32f10x.h"

#define FALSE 0
#define TRUE  1

#define SCL_PIN GPIO_Pin_6
#define SDA_PIN GPIO_Pin_7

#define SCL_H         GPIOB->BSRR = SCL_PIN /* GPIO_SetBits(GPIOB , GPIO_Pin_10)   */
#define SCL_L         GPIOB->BRR  = SCL_PIN /* GPIO_ResetBits(GPIOB , GPIO_Pin_10) */

#define SDA_H         GPIOB->BSRR = SDA_PIN /* GPIO_SetBits(GPIOB , GPIO_Pin_11)   */
#define SDA_L         GPIOB->BRR  = SDA_PIN /* GPIO_ResetBits(GPIOB , GPIO_Pin_11) */

#define SCL_read      GPIOB->IDR  & SCL_PIN /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_10) */
#define SDA_read      GPIOB->IDR  & SDA_PIN /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_11) */

void I2C_INIT(void);
void I2C_delay(void);
void delay5us(void);
void delay5ms(void);
uint16_t I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void); 
void I2C_NoAck(void);
uint16_t I2C_WaitAck(void);
void I2C_SendByte(unsigned char SendByte);
unsigned char I2C_RadeByte(void);
uint16_t Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
uint16_t Single_Write_MS5611(unsigned char SlaveAddress,unsigned char REG_Address);	
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);


#endif // __MYI2C_H__
