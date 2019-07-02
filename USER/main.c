/**
 * @File: Main.c
 * @Brief: Main function for traffic light
 * @Author: J.T. Yu
 * @Date: 2019/7/1
 */

#include "System_Init.h"
#include "Delay.h"

/**
  * @brief  Main
  * @param  None
  * @retval None
  */
int main(void)
{
	RCC_Configuration();
	GPIO_Configuration();
	NVIC_Configuration();
	TIM_Configuration();
	//GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
	//GPIO_ResetBits(GPIOB, GPIO_Pin_1);	
	//GPIO_SetBits(GPIOA, GPIO_Pin_9);
	//GPIO_SetBits(GPIOB, GPIO_Pin_0);
	//GPIO_SetBits(GPIOB, GPIO_Pin_6);

	/* Infinite loop */
	while (1)
	{
	}
}
