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
  * @brief  TIM3 PWM ��ʼ��
  * @param freq: PWMƵ��
  * @retval : None
  */
void TIM3_PWM_Init(uint16_t	freq)
{
		uint16_t	psc=0;		//psc   Ԥ��Ƶϵ��
		uint16_t	arr;			//arr   ��װ��ֵ
		uint32_t	clock;

		/* GPIO������� */
    GPIO_InitTypeDef     GPIO_InitStrue;
    TIM_OCInitTypeDef     TIM_OCInitStrue;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStrue;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);       //	ʹ��TIM3�����GPIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);				//	ʹ��GPIOBʱ��(LED��BP5����),ʹ��AFIOʱ��(��ʱ��3ͨ��2��Ҫ��ӳ�䵽BP5����)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    GPIO_InitStrue.GPIO_Pin=GPIO_Pin_5;     			//	TIM_CH2
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;    	//	��������
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;   //	�����������ٶ�
    GPIO_Init(GPIOB,&GPIO_InitStrue);							//	GPIO�˿ڳ�ʼ������
    
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
		
		/* ��ȡϵͳʱ�� */
		clock = GetSysClock();
		if(!clock)			//clock = 0ʱ����
		{
			while(1);
		}
		/* ������װ��ֵ */
		arr	=	clock/(freq*(psc+1)) - 1;

		/* Timer������� */
    TIM_TimeBaseInitStrue.TIM_Period=arr;    				//�����Զ���װ��ֵ
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        //Ԥ��Ƶϵ��
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;   //�������������
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;       //ʱ�ӵķ�Ƶ���ӣ�����һ������ʱ���ã�һ����ΪTIM_CKD_DIV1
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue);        			//TIM3��ʼ������(����PWM������)
    
    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM2;        			// PWMģʽ2:CNT>CCRʱ�����Ч
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;			// ���ü���-��ЧΪ�ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;	// ���ʹ��
    TIM_OC2Init(TIM3,&TIM_OCInitStrue);        							//TIM3��ͨ��2PWM ģʽ����

    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);        //ʹ��Ԥװ�ؼĴ���
    
    TIM_Cmd(TIM3,ENABLE);        //ʹ��TIM3
    
}
