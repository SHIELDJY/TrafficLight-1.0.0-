/**
  ******************************************************************************
  * @file  main.h
  * @author  Li Jiayi
  * @version  V0.0.1
  * @date  05/08/2019
  * @brief  This file contains all the functions prototypes for the main.c file.
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

/* Main_Exported_Functions ---------------------------------------------------*/
void delay_ms(unsigned long n);
void delay_us(unsigned long n);

#endif /* __MAIN_H */
