/**
 * @File: System_Init.c
 * @Brief: Provide funtions used for init the system
 * @Author: J.T. Yu
 * @Date: 2019/7/1
 */

/* Includes----------- */
#include "System_Init.h"

/**
  * @brief  RCC configutation.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  /*  将外设 RCC 寄存器重设为缺省值，即有关寄存器复位，但该函数不改动寄存器
  RCC_CR 的HSITRIM[4:0]位，也不重置寄存器 RCC_BDCR 和寄存器 RCC_CSR */ 
	ErrorStatus HSEStartUpStatus;
	RCC_DeInit();

	RCC_HSEConfig(RCC_HSE_ON); /* 使能外部HSE 高速晶振 */
   
	 /*  等待 HSE高速晶振稳定，或者在超时的情况下退出 */  
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
  
	/* SUCCESS：HSE 晶振稳定且就绪，ERROR：HSE 晶振未就绪 */ 
	if(HSEStartUpStatus == SUCCESS)
	{ 
		RCC_HCLKConfig(RCC_SYSCLK_Div1);  /* HCLK = SYSCLK 设置高速总线时钟=系统时钟*/ 

		RCC_PCLK2Config(RCC_HCLK_Div1);  /* PCLK2 = HCLK  设置低速总线 2 时钟=高速总线时钟*/  
		RCC_PCLK1Config(RCC_HCLK_Div2);	 /* PCLK1 = HCLK/2 设置低速总线 1 的时钟=高速时钟的二分频*/ 
		/*  利用锁相环将 HSE 外部 8MHz晶振 9 倍频到 72MHz */  
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		/* Enable PLL：使能 PLL锁相环*/ 
		RCC_PLLCmd(ENABLE);
		/* Wait till PLL is ready：等待锁相环输出稳定 */ 
		/* RCC_FLAG_HSIRDY：HSI 晶振就绪，RCC_FLAG_HSERDY：HSE 晶振就绪 
		RCC_FLAG_PLLRDY：PLL就绪，RCC_FLAG_LSERDY：LSE 晶振就绪 
		RCC_FLAG_LSIRDY：LSI 晶振就绪，RCC_FLAG_PINRST：管脚复位 
		RCC_FLAG_PORRST：POR/PDR 复位，RCC_FLAG_SFTRST：软件复位 
		RCC_FLAG_IWDGRST：IWDG 复位，RCC_FLAG_WWDGRST：WWDG复位 
		RCC_FLAG_LPWRRST：低功耗复位 */ 
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)	;
		/* Select PLL as system clock source：将锁相环输出设置为系统时钟 */ 
		/* RCC_SYSCLKSource_HSI：选择 HSI 作为系统时钟 
		RCC_SYSCLKSource_HSE：选择 HSE作为系统时钟  
		RCC_SYSCLKSource_PLLCLK：选择 PLL作为系统时钟*/ 
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
		/* 等待PLL作为系统时钟标志位置位 */ 
		/*0x00：HSI作为系统时钟；0x04：HSE 作为系统时钟 
		0x08：PLL作为系统时钟 */ 
		while(RCC_GetSYSCLKSource() != 0x08);
	}
   
    /* Enable GPIOA～E and AFIO clocks*/ 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);
  
    /* USART1 clock enable：USART1 时钟使能 */ 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* TIM1 clock enable *//* TIM1 clock enable：TIM1 时钟使能 */ 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    /* TIM2 clock enable *//* TIM2 clock enable：TIM2 时钟使能*/ 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* USART3 clock enable *//* ADC1 clock enable：ADC1 时钟使能*/ 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
}

/**
  * @brief  GPIO configutation.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 			
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; 
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
}

/**
  * @brief  Timer configutation.
  * @param  None
  * @retval None
  * @note  Interrupt Period T=3600*20/72,000,000 = 0.001s =1ms
  */

void TIM_Configuration(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_DeInit( TIM2);
  TIM_TimeBaseStructure.TIM_Period = 3599;
  TIM_TimeBaseStructure.TIM_Prescaler = 19;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
}

/**
  * @brief  NVIC configutation.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
NVIC_InitTypeDef NVIC_InitStruct ;
NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStruct);
}
