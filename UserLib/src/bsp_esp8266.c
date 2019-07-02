#include "bsp_esp8266.h"

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
	ESP8266_GPIO_Config();
	ESP8266_USART_Config();
    int i = 0;  
    for(i = 0; i < 13; i++){  
        USART1->DR = at_cwmode[i];//送出AT+CWMODE=3(回车)  
        while((USART1->SR & 0x40) == 0);//直到发送成功  
    }  
    delay_nms(1000);  
    for(i = 0; i < 8; i++){  
        USART1->DR = at_rst[i];//送出AT+RST(回车)  
        while((USART1->SR & 0x40) == 0);//直到发送成功  
    }  
    delay_nms(2000);  
    for(i = 0; i < 42; i++){  
        USART1->DR = at_cwsap[i];//送出AT+CWSAP="ESP8266_TEST","1234567890",1,3(回车)  
        while((USART1->SR & 0x40) == 0);//直到发送成功  
    }  
    delay_nms(1000);  
    for(i = 0; i < 13; i++){  
        USART1->DR = at_cipmux[i];//送出AT+CIPMUX=1(回车)  
        while((USART1->SR & 0x40) == 0);//直到发送成功  
    }  
    delay_nms(1000);  
    for(i = 0; i < 21; i++){  
        USART1->DR = at_cipserver[i];//送出AT+CIPSERVER=1,8080(回车)  
        while((USART1->SR & 0x40) == 0);//直到发送成功  
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
	USART_Init(USART1, &USART_InitStructure); 

	/* 使能串口2接收中断 */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	/* 使能串口2总线空闲中断 */
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART1, ENABLE);

	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
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
		USART_SendData(USART1, pStr[i]);
}

/*
 * 函数名：ESP8266_ReceiveValue
 * 描述  ：WF-ESP8266模块接收值
 * 输入  ：无
 * 返回  : 收到的值
 */
uint16_t ESP8266_ReceiveValue (void)
{
	uint16_t Res_USART1;
	Res_USART1=USART_ReceiveData(USART1);
	return Res_USART1;
}
