#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "stm32f10x_it.h"
#include "oled.h"
#include "Encoder.h"
#include "delay.h"
int main()
{
	  ENC_Init();
		OLED_Init();
	  delay_init(72);
	
	  while(1){
			delay_ms(50);
			OLED_P6x8Float(0,0,TIM_GetCounter(TIM4),1);
			//delay_ms(30);
			OLED_P6x8Float(0,2,ENC_Get_Electrical_Angle(),1);
			//delay_ms(30);
			OLED_P6x8Float(0,4,ENC_Calc_Average_Speed(),1);
	  }
}
