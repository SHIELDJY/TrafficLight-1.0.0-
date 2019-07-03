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
  /*  ������ RCC �Ĵ�������Ϊȱʡֵ�����йؼĴ�����λ�����ú������Ķ��Ĵ���
  RCC_CR ��HSITRIM[4:0]λ��Ҳ�����üĴ��� RCC_BDCR �ͼĴ��� RCC_CSR */ 
	ErrorStatus HSEStartUpStatus;
	RCC_DeInit();

	RCC_HSEConfig(RCC_HSE_ON); /* ʹ���ⲿHSE ���پ��� */
   
	 /*  �ȴ� HSE���پ����ȶ��������ڳ�ʱ��������˳� */  
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
  
	/* SUCCESS��HSE �����ȶ��Ҿ�����ERROR��HSE ����δ���� */ 
	if(HSEStartUpStatus == SUCCESS)
	{ 
		RCC_HCLKConfig(RCC_SYSCLK_Div1);  /* HCLK = SYSCLK ���ø�������ʱ��=ϵͳʱ��*/ 

		RCC_PCLK2Config(RCC_HCLK_Div1);  /* PCLK2 = HCLK  ���õ������� 2 ʱ��=��������ʱ��*/  
		RCC_PCLK1Config(RCC_HCLK_Div2);	 /* PCLK1 = HCLK/2 ���õ������� 1 ��ʱ��=����ʱ�ӵĶ���Ƶ*/ 
		/*  �������໷�� HSE �ⲿ 8MHz���� 9 ��Ƶ�� 72MHz */  
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		/* Enable PLL��ʹ�� PLL���໷*/ 
		RCC_PLLCmd(ENABLE);
		/* Wait till PLL is ready���ȴ����໷����ȶ� */ 
		/* RCC_FLAG_HSIRDY��HSI ���������RCC_FLAG_HSERDY��HSE ������� 
		RCC_FLAG_PLLRDY��PLL������RCC_FLAG_LSERDY��LSE ������� 
		RCC_FLAG_LSIRDY��LSI ���������RCC_FLAG_PINRST���ܽŸ�λ 
		RCC_FLAG_PORRST��POR/PDR ��λ��RCC_FLAG_SFTRST�������λ 
		RCC_FLAG_IWDGRST��IWDG ��λ��RCC_FLAG_WWDGRST��WWDG��λ 
		RCC_FLAG_LPWRRST���͹��ĸ�λ */ 
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)	;
		/* Select PLL as system clock source�������໷�������Ϊϵͳʱ�� */ 
		/* RCC_SYSCLKSource_HSI��ѡ�� HSI ��Ϊϵͳʱ�� 
		RCC_SYSCLKSource_HSE��ѡ�� HSE��Ϊϵͳʱ��  
		RCC_SYSCLKSource_PLLCLK��ѡ�� PLL��Ϊϵͳʱ��*/ 
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
		/* �ȴ�PLL��Ϊϵͳʱ�ӱ�־λ��λ */ 
		/*0x00��HSI��Ϊϵͳʱ�ӣ�0x04��HSE ��Ϊϵͳʱ�� 
		0x08��PLL��Ϊϵͳʱ�� */ 
		while(RCC_GetSYSCLKSource() != 0x08);
	}
   
    /* Enable GPIOA��E and AFIO clocks*/ 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);
  
    /* USART1 clock enable��USART1 ʱ��ʹ�� */ 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* TIM1 clock enable *//* TIM1 clock enable��TIM1 ʱ��ʹ�� */ 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    /* TIM2 clock enable *//* TIM2 clock enable��TIM2 ʱ��ʹ��*/ 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* USART3 clock enable *//* ADC1 clock enable��ADC1 ʱ��ʹ��*/ 
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
