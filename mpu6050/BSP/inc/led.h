#ifndef __LED_H
#define	__LED_H
#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  0
#define OFF 1

#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
 					
#define LED_error 0
#define LED_Setsuccess 1 

void LED_Init(void);
uint8_t LED_Set(uint8_t LED, uint8_t state);
void LED_Set4(uint8_t state);

#endif /* __LED_H */