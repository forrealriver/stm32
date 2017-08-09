#ifndef _APP_H_
#define _APP_H_
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

typedef struct {
				u8 MPU6050_State;
				u8 HMC5883_State;
				u8 SDCARD_state;
         }Model_State;

void MCO_INIT(void);
void System_Init(void);
void Sensor_Init(void);

#endif /* __APP_H */



