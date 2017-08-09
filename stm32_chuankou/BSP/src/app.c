/******************** (C) COPYRIGHT 2014 Air Nano Team ***************************
 * 文件名  ：INIT.c
 * 描述    ：系统初始化         
 * 实验平台：HT飞控
 * 库版本  ：ST3.5.0
 * 作者    ：Air Nano Team 
**********************************************************************************/
#include "app.h"
#include "main.h"

Model_State Init_State;

void System_Init(void)
{
		delay_init(72);  	//延时函数初始化
		Nvic_Init();     	//中断初始化 
	  LED_Init();      	//led初始化
		OLED_Init();     	//oled初始化
		Switch_Init();		//拨码开关
		Beep_Init();			//蜂鸣器初始化
		ADC2_Init();     	//AD初始化，用于采集电流和电压
	  I2C_INIT();      	//IIC初始化，陀螺仪数据采集
		Moto_Init();			//电机PWM初始化

#ifdef USART_MODE
	  Usart_Init(115200);//串口转WIFI模块初始化
#else
		BlueTooth_Init(115200); 		//串口1初始化
#endif	
	
		TIM2_Init(5000);		//定时器2初始化 time = 1000 * 1ns = 5ms
		TIM3_Init(200); 		//定时器3初始化 time = 200 * 0.1ms =20ms
	
		Sensor_Init(); 			//传感器模块初始化
}

void Sensor_Init(void)
{
	Init_State.MPU6050_State = InitMPU6050();      //MPU6050初始化	
}

