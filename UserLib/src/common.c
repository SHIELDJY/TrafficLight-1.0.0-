/**
  ******************************************************************************
  * @file  		common.c
  * @author  	Jiayi
  * @version  V1.0.0
  * @date  		27/1/2019
  * @brief  	This file provides some of the common functions.
  ******************************************************************************
	*/ 
/* Includes ------------------------------------------------------------------*/
#include "common.h"
 /**
 * @brief  ���ϵͳʱ�ӵ�Ƶ��
 * @param[in]  none
 * @retval 0    �ɹ�
 * \retval ��0  ����
 */
uint32_t GetSysClock(void)
{
    uint32_t clock = 0;

#ifdef SYSCLK_FREQ_HSE
  clock=0;
#elif defined SYSCLK_FREQ_20MHz
  clock=20;
#elif defined SYSCLK_FREQ_36MHz
  clock=36;
#elif defined SYSCLK_FREQ_48MHz
  clock=48;
#elif defined SYSCLK_FREQ_56MHz
  clock=56;  
#elif defined SYSCLK_FREQ_72MHz
  clock=72;
#endif
	
		clock = clock * 1000000;
		return clock;
}
