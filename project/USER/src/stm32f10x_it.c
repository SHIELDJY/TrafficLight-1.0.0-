/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "Traffic_Light.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/**
  * @brief  This function handles TIMER2 Handler.
  * @param  None
  * @retval None
  */
uint32_t j=1;
uint32_t t=0;
uint32_t h=0;
uint8_t flag_red = 0;
void TIM2_IRQHandler(void)
{
if (TIM_GetITStatus(TIM2, TIM_FLAG_Update)!=RESET)
{ 
  	if (t == 0)
	{
		if (j == 0)//check
			TestRun();			
		else if (j > 0 )
		{
			t = circle(j,t);		
		}//first circle is end.
	}
	else
	{	
		t = circle(j,t);
	}

	if (flag_red == 0)
	{ 
    j++;
    h = j;
  }
  else
  { 
    if (j!=h) j--;
    else j++;
    GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	  GPIO_ResetBits(GPIOB,GPIO_Pin_1);
  }
  
	if (j>80000)
		j=0;
 	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	}
}

/**
  * @brief  This function handles USART1 Handler.
  * @param  None
  * @retval None
  */
 #define RST_ALL_LIGHTS 0xFF
 #define ALL_YELLOW 0xFE
 #define ALL_RED 0xFD
 #define NS_RED 0xE0
 #define EW_RED 0xE1
void USART3_IRQHandler( void )
{   
	uint16_t Res_Val = 0;

//    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
		Res_Val = ESP8266_ReceiveValue();
		switch (Res_Val)
		{
		case RST_ALL_LIGHTS:
			j=0;t=0;
      flag_red = 0;
      ESP8266_SendString("Reset All Light \n",18);
      TIM_Cmd(TIM2, ENABLE);
      delay_nms(1000);
			break;
    case ALL_YELLOW:
      TIM_Cmd(TIM2, DISABLE);
      AllYellow();
      ESP8266_SendString("ALL YELLOW!! \n",15);
      break;
    case ALL_RED:
      TIM_Cmd(TIM2, DISABLE);
      AllRed();
      ESP8266_SendString("ALL RED!! \n",12);
      break;
		case NS_RED:
      j=40201;
      h = j;
      flag_red = 1;
      ESP8266_SendString("North Sorth Red East West Green \n",34);
      break;
    case EW_RED:
      j=201;
      h = j;
      flag_red = 1;
      ESP8266_SendString("North Sorth Green East West Red \n",34);
      break;
		default:
			break;
		}
	  }
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
//	
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
