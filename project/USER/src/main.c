/**
 * @File: Main.c
 * @Brief: Main function for traffic light
 * @Author: J.T. Yu
 * @Date: 2019/7/1
 */


#include "main.h"


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
	ESP8266_Init();
	TestRun();
	ESP8266_SendString("Welcome To Traffic Light Control System \n",42);
	ESP8266_SendString("*****Menu**** \n",16);
	ESP8266_SendString("Reset-->0xFF \n All Yellow-->0xFE \n All Red-->0xFD \n NSRed-->0xE0 \n WERed-->0xE1 \n ",83);
	ESP8266_SendString("---State Broadcast-----------\n",31);
	TIM_Configuration();

	/* Infinite loop */
	while (1)
	{
	}
}
