#include "usart.h"
#include "trxddata.h"

float OutData[4];

void BlueTooth_Init(uint32_t BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	DataInit();
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = BaudRate;                 /*设置波特率为115200*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  /*设置数据位为8位*/
	USART_InitStructure.USART_StopBits = USART_StopBits_1;       /*设置停止位为1位*/
	USART_InitStructure.USART_Parity = USART_Parity_No;          /*无奇偶校验*/    
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /*没有硬件流控*/
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      /*发送与接收*/
    /*完成串口COM1的时钟配置、GPIO配置，根据上述参数初始化并使能*/
		
	USART_Init(BLUETOOTH, &USART_InitStructure);
	USART_Cmd(BLUETOOTH, ENABLE);
	BLUETOOTH_RXIT_EN(DISABLE);
}

void Usart_Init(u32 BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	DataInit();	
		/* config USART2 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //使能AFIO功能的时钟
  GPIO_PinRemapConfig(GPIO_Remap_USART2 ,ENABLE);  //进行重映射
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	    
  /* Configure USART3 Rx (PD.09) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = BaudRate;                 /*设置波特率为115200*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  /*设置数据位为8位*/
	USART_InitStructure.USART_StopBits = USART_StopBits_1;       /*设置停止位为1位*/
	USART_InitStructure.USART_Parity = USART_Parity_No;          /*无奇偶校验*/    
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /*没有硬件流控*/
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      /*发送与接收*/
	/*完成串口COM2的时钟配置、GPIO配置，根据上述参数初始化并使能*/
	
	USART_Init(USART, &USART_InitStructure);
	USART_Cmd(USART, ENABLE);
	USART_RXIT_EN(DISABLE);
}


void Obstacle_Init(u32 BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
		/* config USART2 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	    
  /* Configure USART3 Rx (PD.09) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = BaudRate;                 /*设置波特率为115200*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  /*设置数据位为8位*/
	USART_InitStructure.USART_StopBits = USART_StopBits_1;       /*设置停止位为1位*/
	USART_InitStructure.USART_Parity = USART_Parity_No;          /*无奇偶校验*/    
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /*没有硬件流控*/
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;      /*发送与接收*/
	/*完成串口COM2的时钟配置、GPIO配置，根据上述参数初始化并使能*/
	
	USART_Init(OBSTACLE, &USART_InitStructure);
	USART_Cmd(OBSTACLE, ENABLE);
	OBSTACLE_RXIT_EN(DISABLE);
}


/**************************实现函数********************************************
*函数原型:		void UART1_Put_Char(unsigned char DataToSend)
*功　　能:		RS232发送一个字节
输入参数：
		unsigned char DataToSend   要发送的字节数据
输出参数：没有	
*******************************************************************************/
uint8_t USART_SendChar(USART_TypeDef* USARTx,unsigned char DataToSend)
{
	//将要发送的字节写到UART1的发送缓冲区
	USART_SendData(USARTx, (unsigned char) DataToSend);
	//等待发送完成
  	while (!(USARTx->SR & USART_FLAG_TXE));
	return DataToSend;
}


/***************************************************************************
函数名称：USART3_SendString
函数功能：发送字符串
函数参数：char*
函数返回：无
*****************************************************************************/
void USART_SendString(USART_TypeDef* USARTx,char *str)
{
    while(*str != '\0')  
        USART_SendChar(USARTx,*str++);
}

void USART_SendInt(USART_TypeDef* USARTx,int num)
{
	char Str[10];
  memset(Str, '\0', 10);
	myitoa(num,Str);
	USART_SendString(USARTx,Str);
}

void USART_SendFloat(USART_TypeDef* USARTx,float num)
{
	char Str[20];
	memset(Str, '\0', 20);
	ftostr(num,Str);
	USART_SendString(USARTx,Str);
}


/*
 * 函数名：fputc
 * 描述  ：重定向c库函数printf到USART1
 * 输入  ：无
 * 输出  ：无
 * 调用  ：由printf调用
 */
int fputc(int ch, FILE *f)
{
/* 将Printf内容发往串口 */
  USART_SendData(USART1, (unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));
 
  return (ch);
}

/*
 * 函数名：itoa
 * 描述  ：将整形数据转换成字符串
 * 输入  ：-radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 * 输出  ：无
 * 返回  ：无
 * 调用  ：被USART1_printf()调用
 */
static char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

/*
 * 函数名：USART1_printf
 * 描述  ：格式化输出，类似于C库中的printf，但这里没有用到C库
 * 输入  ：-USARTx 串口通道，这里只用到了串口1，即USART1
 *		     -Data   要发送到串口的内容的指针
 *			   -...    其他参数
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用
 *         典型应用USART1_printf( USART1, "\r\n this is a demo \r\n" );
 *            		 USART1_printf( USART1, "\r\n %d \r\n", i );
 *            		 USART1_printf( USART1, "\r\n %s \r\n", j );
 */
void USART_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
	const char *s;
  int d;   
  char buf[16];

  va_list ap;
  va_start(ap, Data);

	while ( *Data != 0)     // 判断是否到达字符串结束符
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //回车符
					USART_SendData(USARTx, 0x0d);
					Data ++;
					break;

				case 'n':							          //换行符
					USART_SendData(USARTx, 0x0a);	
					Data ++;
					break;
				
				default:
					Data ++;
				    break;
			}			 
		}
		else if ( *Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //字符串
					s = va_arg(ap, const char *);
          for ( ; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
          }
					Data++;
          break;

        case 'd':										//十进制
          d = va_arg(ap, int);
          itoa(d, buf, 10);
          for (s = buf; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
          }
					Data++;
          break;
				 default:
						Data++;
				    break;
			}		 
		} /* end of else if */
		else USART_SendData(USARTx, *Data++);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
	}
}



/*******************************************************************************
* Function Name  : USART_Scanf
* Description    : Gets numeric values from the hyperterminal.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 USART_Scanf(u32 value)
{
  u32 index = 0;
  u32 tmp[2] = {0, 0};

  while (index < 2)
  {
    /* Loop until RXNE = 1 */
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
    {}
    tmp[index++] = (USART_ReceiveData(USART1));
    if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
    {
      printf("\n\rPlease enter valid number between 0 and 9");
      index--;
    }
  }
  /* Calculate the Corresponding value */
  index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10);
  /* Checks */
  if (index > value)
  {
    printf("\n\rPlease enter valid number between 0 and %d", value);
    return 0xFF;
  }
  return index;
}




//float转换成str，保留四位小数
void ftostr(float num,char *str)
{
	int zhengshu,xiaoshu;
	char f[10];
	memset(str, '\0', 10);
	if(num<0)
	{
		str[0]='-';
		num=-num;
	}
	zhengshu=(int)num;
	xiaoshu=(int)((num-zhengshu)*10000);
	f[0]=zhengshu/10%10+'0';
	f[1]=zhengshu/1%10+'0';
	f[2]='.';
	f[3]=xiaoshu/1000%10+'0';
	f[4]=xiaoshu/100%10+'0';
	f[5]=xiaoshu/10%10+'0';
	f[6]=xiaoshu/1%10+'0';
	strcat(str,f);
}

void myitoa(int num,char *str)
{
    int i = 0, j = 0;
    char tmp = '\0';
    do
    {
        str[i++]=num%10+'0';//取下一个数字
    }while ((num/=10)>0);//删除该数字
    for(j = 0;j<=(i-1)/2;j++)
    {
        tmp=str[j];
        str[j] = str[i-1-j];
        str[i-1-j] = tmp;
    }
}

unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){      
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}

void OutPut_Data(void)
{
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0};
  unsigned char i;
  unsigned short CRC16 = 0;
  for(i=0;i<4;i++)
   {
    
    temp[i]  = (int)OutData[i];
    temp1[i] = (unsigned int)temp[i];
    
   }
   
  for(i=0;i<4;i++) 
  {
    databuf[i*2]   = (unsigned char)(temp1[i]%256);
    databuf[i*2+1] = (unsigned char)(temp1[i]/256);
  }
  
  CRC16 = CRC_CHECK(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;
  
  for(i=0;i<10;i++)
		USART_SendChar(USART2,databuf[i]);
}
