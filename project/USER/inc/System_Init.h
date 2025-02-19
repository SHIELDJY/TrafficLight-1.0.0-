/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

/* Includes ------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

/* Exported Functions ------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM_Configuration(void);
void NVIC_Configuration(void);

#endif /* __SYSTEM_INIT_H */
