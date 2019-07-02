/**
  ******************************************************************************
  * @file 		pwm.c
  * @author  	Jiayi
  * @version  V1.0.0
  * @date  		27/1/2019
  * @brief  	This file provides some of the PWM firmware functions.
  ******************************************************************************
	*/ 
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "pwm.h"
#include "common.h"

/**
  * @brief  TIM3 PWM 初始化
  * @param freq: PWM频率
  * @retval : None
  */
void TIM3_PWM_Init(uint16_t	freq)
{
		uint16_t	psc=0;		//psc   预分频系数
		uint16_t	arr;			//arr   重装载值
		uint32_t	clock;

		/* GPIO相关设置 */
    GPIO_InitTypeDef     GPIO_InitStrue;
    TIM_OCInitTypeDef     TIM_OCInitStrue;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);       //	使能TIM3和相关GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);				//	使能GPIOB时钟(LED在BP5引脚),使能AFIO时钟(定时器3通道2需要重映射到BP5引脚)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_5;     			//	TIM_CH2
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    	//	复用推挽
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;   //	设置最大输出速度
    GPIO_Init(GPIOB,&GPIO_InitStrue);							//	GPIO端口初始化设置
    
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
		
		/* 获取系统时钟 */
		clock = GetSysClock();
		if(!clock)			//clock = 0时错误
		{
			while(1);
		}
		/* 计算重装载值 */
		arr	=	clock/(freq*(psc+1)) - 1;

		/* Timer相关设置 */
    TIM_TimeBaseInitStrue.TIM_Period=arr;    				//设置自动重装载值
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        //预分频系数
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;   //计数器向上溢出
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;       //时钟的分频因子，起到了一点点的延时作用，一般设为TIM_CKD_DIV1
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue);        			//TIM3初始化设置(设置PWM的周期)
    
    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM2;        			// PWM模式2:CNT>CCR时输出有效
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;			// 设置极性-有效为高电平
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;	// 输出使能
    TIM_OC2Init(TIM3,&TIM_OCInitStrue);        							//TIM3的通道2PWM 模式设置

    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);        //使能预装载寄存器
    
    TIM_Cmd(TIM3,ENABLE);        //使能TIM3
    
}
