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

int main()
{
	  
		OLED_Init();
	  delay_init(72);
	  I2C_INIT();
	  InitMPU6050();  
    OLED_P6x8Str(0,2,"Angle x:");
	  OLED_P6x8Str(0,3,"Angle y:"); 
	  OLED_P6x8Str(0,4,"Angle z:");	
	
	  Gyro_OFFEST();
	  while(1){
			Get_Attitude();	
			//delay_ms(50);
      OLED_P6x8Float(54,2,angle.x,2);
			OLED_P6x8Float(54,3,angle.y,2);
			OLED_P6x8Float(54,4,angle.z,2);
	  }
}
