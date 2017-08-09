#include "include.h"

uint8_t key_count=0;


 /*
 * �������� Delay
 * ����  ������ȷ����ʱ
 * ����  ����ʱ������
 * ���  ����
 */
 void KDelay(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
} 

void KEY_Init(void)        
{
   GPIO_InitTypeDef  KEY_GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(KEY_RCCEN, ENABLE); 	 //GPIO始终使能

   KEY_GPIO_InitStructure.GPIO_Pin = KEY1|KEY2|KEY3|KEY4;
	 KEY_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 KEY_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_Init(KEY_GPIO, &KEY_GPIO_InitStructure); 		           //配置OLED端口引脚为GPIO输出
}

 /*
 * ��������Key_Scan
 * ����  ������Ƿ��а�������
 * ����  ��GPIOx��x ������ A��B��C��D���� E
 *		     GPIO_Pin������ȡ�Ķ˿�λ 	
 * ���  ��KEY_OFF(û���°���)��KEY_ON�����°�����
 */
uint8_t Key_Scan(void)
{			
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(KEY_GPIO,KEY1) == KEY_ON ) 
	{	   
		delay_ms(20);		
		if(GPIO_ReadInputDataBit(KEY_GPIO,KEY1) == KEY_ON )  
		{	 
			while(GPIO_ReadInputDataBit(KEY_GPIO,KEY1) == KEY_ON);   
			return 	KEY1_EN;	 
		}
	}
	else if(GPIO_ReadInputDataBit(KEY_GPIO,KEY2) == KEY_ON ) 
	{	   
		delay_ms(20);	
		if(GPIO_ReadInputDataBit(KEY_GPIO,KEY2) == KEY_ON )  
		{	 
			while(GPIO_ReadInputDataBit(KEY_GPIO,KEY2) == KEY_ON);   
			return 	KEY2_EN;	 
		}
	}
	else if(GPIO_ReadInputDataBit(KEY_GPIO,KEY3) == KEY_ON ) 
	{	   
		delay_ms(20);		
		if(GPIO_ReadInputDataBit(KEY_GPIO,KEY3) == KEY_ON )  
		{	 
			while(GPIO_ReadInputDataBit(KEY_GPIO,KEY3) == KEY_ON);   
			return 	KEY3_EN;	 
		}
	}
	else if(GPIO_ReadInputDataBit(KEY_GPIO,KEY4) == KEY_ON ) 
	{	   
		delay_ms(20);	
		if(GPIO_ReadInputDataBit(KEY_GPIO,KEY4) == KEY_ON )  
		{	 
			while(GPIO_ReadInputDataBit(KEY_GPIO,KEY4) == KEY_ON);   
			return 	KEY4_EN;	 
		}
	}
	else return KEY_OFF;
}

void key_control()
{
	uint8_t key_state;
	key_state=Key_Scan();
	if(key_state==KEY4_EN)
	{
		OLED_P6x8Str(120,3+key_count," ");
		if(key_count==KEY_MIN)
			key_count = KEY_MAX;
		else
			key_count--;
		OLED_P6x8Str(120,3+key_count,"*");
	}
	if(key_state==KEY3_EN) 
	{
		OLED_P6x8Str(120,3+key_count," ");
			if(key_count==KEY_MAX)
				key_count=KEY_MIN;
			else
				key_count++;
		OLED_P6x8Str(120,3+key_count,"*");
	}
	
	if(key_state==KEY2_EN)
	{ 
			if(key_count==0)
			{	
				param_setvalue.angle+=5;
				if(param_setvalue.angle>=360)
					param_setvalue.angle-=360;
			}
			if(key_count==1)
			{	
				param_setvalue.distance++;
			}
			if(key_count==2)
			{	
				Radius++;
			}
	}
	if(key_state==KEY1_EN)	
	{
			if(key_count==0)
			{	
				param_setvalue.angle-=5;
				if(param_setvalue.angle<0)
					param_setvalue.angle+=360;
			}
			if(key_count==1)
			{	
				param_setvalue.distance--;
			}
			if(key_count==2)
			{	
				Radius--;
			}

	}
}
