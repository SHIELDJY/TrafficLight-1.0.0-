/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TRAFFIC_LIGHT_H
#define __TRAFFIC_LIGHT_H

/* Includes ------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Delay.h"
#include "misc.h"

/* Exported Functions ------------------------*/
void Init_Configuration(void);
void Segment_led(uint32_t a);
void translate(uint8_t a);
uint32_t circle(uint32_t a,uint32_t b);
void TrafficLight_Check(void);
void TestRun(void);

#endif /* __TRAFFIC_LIGHT_H */
