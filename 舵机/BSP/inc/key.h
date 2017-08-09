#ifndef _KEY_H
#define _KEY_H
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#define KEY_GPIO    GPIOE
#define KEY_RCCEN   RCC_APB2Periph_GPIOE
#define KEY1        GPIO_Pin_8      
#define KEY2        GPIO_Pin_9      
#define KEY3        GPIO_Pin_10     
#define KEY4        GPIO_Pin_11       

 /*******
 *按键按下标置
 KEY_ON 0
 KEY_OFF 1
 ********/

#define KEY_ON	  0
#define KEY_OFF	  1
#define KEY1_EN		2
#define KEY2_EN  	3
#define KEY3_EN		4
#define KEY4_EN		5

#define KEY_MAX 2
#define KEY_MIN 0

extern uint8_t key_count;

void KEY_Init(void);
uint8_t Key_Scan(void);
void key_control();
#endif