#include "mpu6050.h"


#define UART_Put_Char(x)  UART1_Put_Char(x)//UART3_SendChar(x)

struct _sensor sensor;	
u8		 mpu6050_buffer[14];					//iic读取后存放数据 	

u8		ACC_OFFSET_OK = 0;


extern vs16 Moto_duty[4];

//**************************************
//初始化MPU6050
//**************************************
void InitMPU6050(void)//量程越小精度越高
{
	u8 date = 0;
//	u8 whoami = Single_Read(MPU6050_ADDRESS,WHO_AM_I);
//	date = Single_Write(MPU6050_ADDRESS,PWR_MGMT_1, 0x80);        
//  delay_ms(5);
//	date = Single_Write(MPU6050_ADDRESS,SIGNAL_RESET, 0x07); 
//	delay_ms(5);
	date += Single_Write(MPU6050_ADDRESS, PWR_MGMT_1, 0x00);  	//解除休眠状态
	date += Single_Write(MPU6050_ADDRESS, SMPLRT_DIV, 0x07);     //陀螺仪的采样频率为1kHz
	date += Single_Write(MPU6050_ADDRESS, cONFIG, 0x03);        
	date += Single_Write(MPU6050_ADDRESS, GYRO_CONFIG, 0x10);  //+-1000
	date += Single_Write(MPU6050_ADDRESS, ACCEL_CONFIG, 0x09);   //+-4G

}
//**************************实现函数********************************************
//将iic读取到得数据分拆,放入相应寄存器,更新MPU6050_Last
//******************************************************************************
void MPU6050_Read(void)
{
	mpu6050_buffer[0]=Single_Read(MPU6050_ADDRESS, 0x3B);
	mpu6050_buffer[1]=Single_Read(MPU6050_ADDRESS, 0x3C);
	mpu6050_buffer[2]=Single_Read(MPU6050_ADDRESS, 0x3D);
	mpu6050_buffer[3]=Single_Read(MPU6050_ADDRESS, 0x3E);
	mpu6050_buffer[4]=Single_Read(MPU6050_ADDRESS, 0x3F);
	mpu6050_buffer[5]=Single_Read(MPU6050_ADDRESS, 0x40);
	mpu6050_buffer[8]=Single_Read(MPU6050_ADDRESS, 0x43);
	mpu6050_buffer[9]=Single_Read(MPU6050_ADDRESS, 0x44);
	mpu6050_buffer[10]=Single_Read(MPU6050_ADDRESS, 0x45);
	mpu6050_buffer[11]=Single_Read(MPU6050_ADDRESS, 0x46);
	mpu6050_buffer[12]=Single_Read(MPU6050_ADDRESS, 0x47);
	mpu6050_buffer[13]=Single_Read(MPU6050_ADDRESS, 0x48);
}
/**************************实现函数********************************************
//将iic读取到得数据分拆,放入相应寄存器
*******************************************************************************/
void MPU6050_Dataanl(void)
{
	MPU6050_Read();
	
	sensor.acc.origin.x = ((((int16_t)mpu6050_buffer[0]) << 8) | mpu6050_buffer[1]) ;
	sensor.acc.origin.y = ((((int16_t)mpu6050_buffer[2]) << 8) | mpu6050_buffer[3]) ;
	sensor.acc.origin.z = ((((int16_t)mpu6050_buffer[4]) << 8) | mpu6050_buffer[5]) ;

	sensor.gyro.origin.x = ((((int16_t)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9])  ;
	sensor.gyro.origin.y = ((((int16_t)mpu6050_buffer[10]) << 8)| mpu6050_buffer[11]) ;
	sensor.gyro.origin.z = ((((int16_t)mpu6050_buffer[12]) << 8)| mpu6050_buffer[13]) ;
  
	sensor.gyro.radian.x = sensor.gyro.origin.x * Gyro_Gr - sensor.gyro.quiet.x * Gyro_Gr;
	sensor.gyro.radian.y = sensor.gyro.origin.y * Gyro_Gr - sensor.gyro.quiet.y * Gyro_Gr;
	sensor.gyro.radian.z = sensor.gyro.origin.z * Gyro_Gr - sensor.gyro.quiet.z * Gyro_Gr;
}	
/**************************实现函数********************************************
//陀螺仪零点校准
*******************************************************************************/

void Gyro_OFFEST(void)
{
   int cnt_g=5000;
	 int32_t  tempgx=0,tempgy=0,tempgz=0;
	 sensor.gyro.averag.x=0;    //零点偏移清零
	 sensor.gyro.averag.y=0;  
	 sensor.gyro.averag.z=0;
	 while(cnt_g--)       //循环采集5000次   求平均
	 {
		  MPU6050_Read();
		 
		  sensor.gyro.origin.x = ((((int16_t)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9]);
	    sensor.gyro.origin.y = ((((int16_t)mpu6050_buffer[10]) << 8)| mpu6050_buffer[11]);
	    sensor.gyro.origin.z = ((((int16_t)mpu6050_buffer[12]) << 8)| mpu6050_buffer[13]);
      tempgx+= sensor.gyro.origin.x;
			tempgy+= sensor.gyro.origin.y;
			tempgz+= sensor.gyro.origin.z;
			delay_ms(1);
   }
	 sensor.gyro.quiet.x=tempgx/3000;
	 sensor.gyro.quiet.y=tempgy/3000;
	 sensor.gyro.quiet.z=tempgz/3000;  
}

 

