#include "hmc5883.h"
#include "IMU.h"
#include  <math.h>
#define  FILL_NUM  10

int16_t X_HMC,Y_HMC,Z_HMC,x,y,z;
int16_t x_offest=10,y_offest=175;
double y_gain=0.967;
int16_t HMC_Angle;

int16_t X_BUFF[FILL_NUM],Y_BUFF[FILL_NUM],Z_BUFF[FILL_NUM];



u8 Init_HMC5883L(void)
{
	 u8 date;
   date = Single_Write(HMC5883L_ADDRESS,0x02,0x00);
   return date; 		 
}



//******************************************************
//��������HMC5883�ڲ��Ƕ����ݣ���ַ��Χ0x3~0x5
//******************************************************
void Multiple_Read_HMC5883L(void)
{      	
 	 u8 i;
	 uint8_t BUF[8];
	 static uint8_t filter_cnt=0;
	 int32_t temp1=0,temp2=0,temp3=0;
	
    I2C_Start();                          //��ʼ�ź�
    I2C_SendByte(HMC5883L_ADDRESS);                   //�����豸��ַ+д�ź�
	  I2C_WaitAck();
    I2C_SendByte(0x03);                   //���ʹ洢��Ԫ��ַ����0x3��ʼ	
	  I2C_WaitAck();
    I2C_Start();                          //��ʼ�ź�
    I2C_SendByte(HMC5883L_ADDRESS+1);     //�����豸��ַ+���ź�
	  I2C_WaitAck();
	  for (i=0; i<6; i++)                   //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = I2C_RadeByte();          //BUF[0]�洢����
        if (i == 5)
           I2C_NoAck();                   //���һ��������Ҫ��NOACK
        else
           I2C_Ack();                     //��ӦACK
    }
    I2C_Stop();                           //ֹͣ�ź�
    I2C_delay();

		X_BUFF[filter_cnt] = BUF[0] << 8 | BUF[1]; //Combine MSB and LSB of X Data output register;
	  Y_BUFF[filter_cnt] = BUF[4] << 8 | BUF[5]; //Combine MSB and LSB of Y Data output register;
	  Z_BUFF[filter_cnt] = BUF[2] << 8 | BUF[3]; //Combine MSB and LSB of Z Data output register;
	  for(i=0;i<FILL_NUM;i++)  //10��ȵĻ����˲�
	  {
		   temp1 += X_BUFF[i];
		   temp2 += Y_BUFF[i];
		   temp3 += Z_BUFF[i];
	  }
	  x = temp1 / FILL_NUM;
	  y = temp2 / FILL_NUM;
	  z = temp3 / FILL_NUM;
		
	  filter_cnt++;
	  if(filter_cnt==FILL_NUM)	filter_cnt=0;
	 
		/*   �ش���Բ����                              */  
    /*  ������ν�����Բ���� �������°汾 ��ϸ˵�� */		
    X_HMC = 1 *(x + x_offest);
    Y_HMC = (double)(y_gain * (y + y_offest));
	  Z_HMC = (double)(1.073 * (z +30));
		
		angle.z = atan2((double)Y_HMC,(double)X_HMC) * RtA + 180; // angle in degrees
//		HMC_Angle = atan2((double)Y_HMC,(double)X_HMC) * (180 / 3.14159265) + 180; // angle in degrees
}	   

