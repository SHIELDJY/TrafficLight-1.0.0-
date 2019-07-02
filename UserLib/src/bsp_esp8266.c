#include "bsp_esp8266.h"

/* Private Functions-------------- */
void ESP8266_GPIO_Config ( void );
void ESP8266_USART_Config(void);

/* Function Prototype--------------- */
/**
  * @brief  ESP8266��ʼ������
  * @param  ��
  * @retval ��
  */
void ESP8266_Init(void)
{  
	ESP8266_GPIO_Config();
	ESP8266_USART_Config();
    int i = 0;  
    for(i = 0; i < 13; i++){  
        USART1->DR = at_cwmode[i];//�ͳ�AT+CWMODE=3(�س�)  
        while((USART1->SR & 0x40) == 0);//ֱ�����ͳɹ�  
    }  
    delay_nms(1000);  
    for(i = 0; i < 8; i++){  
        USART1->DR = at_rst[i];//�ͳ�AT+RST(�س�)  
        while((USART1->SR & 0x40) == 0);//ֱ�����ͳɹ�  
    }  
    delay_nms(2000);  
    for(i = 0; i < 42; i++){  
        USART1->DR = at_cwsap[i];//�ͳ�AT+CWSAP="ESP8266_TEST","1234567890",1,3(�س�)  
        while((USART1->SR & 0x40) == 0);//ֱ�����ͳɹ�  
    }  
    delay_nms(1000);  
    for(i = 0; i < 13; i++){  
        USART1->DR = at_cipmux[i];//�ͳ�AT+CIPMUX=1(�س�)  
        while((USART1->SR & 0x40) == 0);//ֱ�����ͳɹ�  
    }  
    delay_nms(1000);  
    for(i = 0; i < 21; i++){  
        USART1->DR = at_cipserver[i];//�ͳ�AT+CIPSERVER=1,8080(�س�)  
        while((USART1->SR & 0x40) == 0);//ֱ�����ͳɹ�  
    }  
}  

/**
  * @brief  ��ʼ��ESP8266�õ���GPIO����
  * @param  ��
  * @retval ��
  */
void ESP8266_GPIO_Config ( void )
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	/* ���� CH_PD ����*/
	macESP8266_CH_PD_APBxClock_FUN ( macESP8266_CH_PD_CLK, ENABLE ); 									   
	GPIO_InitStructure.GPIO_Pin = macESP8266_CH_PD_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init ( macESP8266_CH_PD_PORT, & GPIO_InitStructure );	 	
	/* ���� RST ����*/
	macESP8266_RST_APBxClock_FUN ( macESP8266_RST_CLK, ENABLE ); 											   
	GPIO_InitStructure.GPIO_Pin = macESP8266_RST_PIN;	
	GPIO_Init ( macESP8266_RST_PORT, & GPIO_InitStructure );	
	/* ���� Tx ����*/
	macESP8266_RST_APBxClock_FUN ( macESP8266_Tx_CLK, ENABLE ); 											   
	GPIO_InitStructure.GPIO_Pin = macESP8266_Tx_PIN;	
	GPIO_Init ( macESP8266_Tx_PORT, & GPIO_InitStructure ); 
	/* ���� Rx ����*/
	macESP8266_RST_APBxClock_FUN ( macESP8266_Rx_CLK, ENABLE ); 											   
	GPIO_InitStructure.GPIO_Pin = macESP8266_Rx_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init ( macESP8266_Rx_PORT, & GPIO_InitStructure ); 
}

/**
  * @brief  ��ʼ��ESP8266�õ���USART�˿�
  * @param  ��
  * @retval ��
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

	/* ʹ�ܴ���2�����ж� */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	/* ʹ�ܴ���2���߿����ж� */
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
 * ��������ESP8266_Rst
 * ����  ������WF-ESP8266ģ��
 * ����  ����
 * ����  : ��
 */
void ESP8266_Rst ( void )
{
	//����Ӳ��RST���������ø�����λ
	 macESP8266_RST_LOW_LEVEL();
	 delay_nms ( 50 ); 
	 macESP8266_RST_HIGH_LEVEL();
}

/*
 * ��������ESP8266_SendString
 * ����  ��WF-ESP8266ģ�鷢���ַ���
 * ����  ��pStr��Ҫ���͵��ַ���
 *       ��ulStrLength��Ҫ���͵��ַ������ֽ���
 * ����  : ��
 */
void ESP8266_SendString (char * pStr, u8 ulStrLength)
{
	u8 i;
	for(i=0; i<ulStrLength;i++)
		USART_SendData(USART1, pStr[i]);
}

/*
 * ��������ESP8266_ReceiveValue
 * ����  ��WF-ESP8266ģ�����ֵ
 * ����  ����
 * ����  : �յ���ֵ
 */
uint16_t ESP8266_ReceiveValue (void)
{
	uint16_t Res_USART1;
	Res_USART1=USART_ReceiveData(USART1);
	return Res_USART1;
}
