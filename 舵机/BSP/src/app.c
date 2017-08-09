/******************** (C) COPYRIGHT 2014 Air Nano Team ***************************
 * �ļ���  ��INIT.c
 * ����    ��ϵͳ��ʼ��         
 * ʵ��ƽ̨��HT�ɿ�
 * ��汾  ��ST3.5.0
 * ����    ��Air Nano Team 
**********************************************************************************/
#include "app.h"
#include "main.h"

Model_State Init_State;

void System_Init(void)
{
		delay_init(72);  	//��ʱ������ʼ��
		Nvic_Init();     	//�жϳ�ʼ�� 
	  LED_Init();      	//led��ʼ��
		OLED_Init();     	//oled��ʼ��
		Switch_Init();		//���뿪��
		Beep_Init();			//��������ʼ��
		ADC2_Init();     	//AD��ʼ�������ڲɼ������͵�ѹ
	  I2C_INIT();      	//IIC��ʼ�������������ݲɼ�
		Moto_Init();			//���PWM��ʼ��

#ifdef USART_MODE
	  Usart_Init(115200);//����תWIFIģ���ʼ��
#else
		BlueTooth_Init(115200); 		//����1��ʼ��
#endif	
	
		TIM2_Init(5000);		//��ʱ��2��ʼ�� time = 1000 * 1ns = 5ms
		TIM3_Init(200); 		//��ʱ��3��ʼ�� time = 200 * 0.1ms =20ms
	
		Sensor_Init(); 			//������ģ���ʼ��
}

void Sensor_Init(void)
{
	Init_State.MPU6050_State = InitMPU6050();      //MPU6050��ʼ��	
}

