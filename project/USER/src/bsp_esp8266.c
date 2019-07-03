/**
 * @File: System_Init.c
 * @Brief: Provide funtions used for init the system
 * @Author: J. Y. Li
 * @Date: 2019/7/2
 */
#include "bsp_esp8266.h"

/* Private Variable ------------------------*/
u8 at_cwmode[] = {0x00, 0x41, 0x54, 0x2B, 0x43, 0x57, 0x4D, 0x4F, 0x44, 0x45, 0x3D,   
                  0x33, 0x0D, 0x0A};//AT+CWMODE=3(回车)  
u8 null[] = {0x00, 0x00, 0x00};
u8 at_rst[] = {0x41, 0x54, 0x2B, 0x52, 0x53, 0x54, 0x0D, 0x0A};//AT+RST(回车)  
u8 at_cwsap[] = {0x41, 0x54, 0x2B, 0x43, 0x57, 0x53, 0x41, 0x50, 0x3D, 0x22,   
         0x45, 0x53, 0x50, 0x38, 0x32, 0x36, 0x36, 0x5F, 0x54, 0x45,   
         0x53, 0x54, 0x22, 0x2C, 0x22, 0x31, 0x32, 0x33, 0x34, 0x35,   
         0x36, 0x37, 0x38, 0x39, 0x30, 0x22, 0x2C, 0x31, 0x2C, 0x33,   
         0x0D, 0x0A};//AT+CWSAP="ESP8266_TEST","1234567890",1,3(回车)  
u8 at_cipmux[] = {0x41, 0x54, 0x2B, 0x43, 0x49, 0x50, 0x4D, 0x55, 0x58,   
          0x3D, 0x31, 0x0D, 0x0A};//AT+CIPMUX=1(回车)  
u8 at_cipserver[] = {0x41, 0x54, 0x2B, 0x43, 0x49, 0x50, 0x53, 0x45, 0x52, 0x56,   
             0x45, 0x52, 0x3D, 0x31, 0x2C, 0x38, 0x30, 0x38, 0x30, 0x0D,   
             0x0A};//AT+CIPSERVER=1,8080(回车)
u8 at_cipstart[] = {0x41, 0x54, 0x2B, 0x43, 0x49, 0x50, 0x53, 0x54, 0x41, 0x52, 0x54, 0x3D, 0x22, 0x54, 0x43, 0x50, 
			0x22, 0x2C, 0x22, 0x31, 0x39, 0x32, 0x2E, 0x31, 0x36, 0x38, 0x2E, 0x34, 0x33, 0x2E, 0x31, 0x22,
			0x2C, 0x37, 0x37, 0x37, 0x37, 0x0D, 0x0A};//AT+CIPSTART="TCP","192.168.43.1",7777
u8 at_cipmode[] = {0x41, 0x54, 0x2B, 0x43, 0x49, 0x50, 0x4D, 0x4F, 0x44, 0x45, 0x3D, 0x31, 0x0D, 0x0A};
				//AT+CIPMODE=1
u8 at_cipsend[] = {0X41, 0X54, 0X2B, 0X43, 0X49, 0X50, 0X53, 0X45, 0X4E, 0X44, 0X0D, 0X0A};
				//AT+CIPSEND

/* Private Functions-------------- */
void ESP8266_GPIO_Config ( void );
void ESP8266_USART_Config(void);

/* Function Prototype--------------- */
/**
  * @brief  ESP8266初始化函数
  * @param  无
  * @retval 无
  */
void ESP8266_Init(void)
{  
	int i = 0;  
	ESP8266_GPIO_Config();
	ESP8266_USART_Config(); 
	delay_nms(1000);
	for(i = 0; i < 3; i++){  
		USART3->DR = null[i];//
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//直到发送成功  
    } 
	delay_nms(1000);
    for(i = 0; i < 39; i++){  
        USART3->DR = at_cipstart[i];//送出AT+CIPSTART="TCP","192.168.43.1",7777  
        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//直到发送成功  
    }  
    delay_nms(2000); 
	for(i = 0; i < 14; i++){  
        USART3->DR = at_cipmode[i];//送出AT+CIPMODE=1  
        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//直到发送成功  
    }  
    delay_nms(1000);
	for(i = 0; i < 12; i++){  
        USART3->DR = at_cipsend[i];//送出AT+CIPSEND  
        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//直到发送成功  
    }  
}  

/**
  * @brief  初始化ESP8266用到的GPIO引脚
  * @param  无
  * @retval 无
  */
void ESP8266_GPIO_Config ( void )
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/* 配置 CH_PD 引脚*/
	macESP8266_CH_PD_APBxClock_FUN ( macESP8266_CH_PD_CLK, ENABLE ); 									   
	GPIO_InitStructure.GPIO_Pin = macESP8266_CH_PD_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( macESP8266_CH_PD_PORT, & GPIO_InitStructure );	 	
	/* 配置 RST 引脚*/
	macESP8266_RST_APBxClock_FUN ( macESP8266_RST_CLK, ENABLE ); 											   
	GPIO_InitStructure.GPIO_Pin = macESP8266_RST_PIN;	
	GPIO_Init ( macESP8266_RST_PORT, & GPIO_InitStructure );	
	/* 配置 Tx 引脚*/
	macESP8266_RST_APBxClock_FUN ( macESP8266_Tx_CLK, ENABLE ); 											   
	GPIO_InitStructure.GPIO_Pin = macESP8266_Tx_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init ( macESP8266_Tx_PORT, & GPIO_InitStructure ); 
	/* 配置 Rx 引脚*/
	macESP8266_RST_APBxClock_FUN ( macESP8266_Rx_CLK, ENABLE ); 											   
	GPIO_InitStructure.GPIO_Pin = macESP8266_Rx_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init ( macESP8266_Rx_PORT, & GPIO_InitStructure ); 
}

/**
  * @brief  初始化ESP8266用到的USART端口
  * @param  无
  * @retval 无
  */
void ESP8266_USART_Config(void)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 

	/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = 115200;               
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure); 

	/* 使能串口3总线空闲中断 */
//	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	
		/* 使能串口3接收中断 */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* Enable the USART3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART3, ENABLE);
}
/*
 * 函数名：ESP8266_Rst
 * 描述  ：重启WF-ESP8266模块
 * 输入  ：无
 * 返回  : 无
 */
void ESP8266_Rst ( void )
{
	//采用硬件RST引脚至低置高来复位
	 macESP8266_RST_LOW_LEVEL();
	 delay_nms ( 50 ); 
	 macESP8266_RST_HIGH_LEVEL();
}

/*
 * 函数名：ESP8266_SendString
 * 描述  ：WF-ESP8266模块发送字符串
 * 输入  ：pStr，要发送的字符串
 *       ：ulStrLength，要发送的字符串的字节数
 * 返回  : 无
 */
void ESP8266_SendString (char * pStr, u8 ulStrLength)
{
	u8 i;
	for(i=0; i<ulStrLength;i++)
		{
			USART_SendData(USART3, pStr[i]);
			while((USART3->SR & 0x40) == 0);
		}
}

/*
 * 函数名：ESP8266_ReceiveValue
 * 描述  ：WF-ESP8266模块接收值
 * 输入  ：无
 * 返回  : 收到的值
 */
uint16_t ESP8266_ReceiveValue (void)
{
	uint16_t Res_USART3;
	uint8_t i;
	Res_USART3=USART_ReceiveData(USART3);
	return Res_USART3;
}
