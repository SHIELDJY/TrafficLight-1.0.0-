#ifndef  __BSP_ESP8266_H
#define	 __BSP_ESP8266_H

/* Includes ------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "Delay.h"


/* Port Definitions ------------------------*/
#define      macESP8266_CH_PD_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      macESP8266_CH_PD_CLK                             RCC_APB2Periph_GPIOC  
#define      macESP8266_CH_PD_PORT                            GPIOC
#define      macESP8266_CH_PD_PIN                             GPIO_Pin_6

#define      macESP8266_RST_APBxClock_FUN                     RCC_APB2PeriphClockCmd
#define      macESP8266_RST_CLK                               RCC_APB2Periph_GPIOC
#define      macESP8266_RST_PORT                              GPIOC
#define      macESP8266_RST_PIN                               GPIO_Pin_7

#define      macESP8266_Tx_APBxClock_FUN                      RCC_APB2PeriphClockCmd
#define      macESP8266_Tx_CLK                                RCC_APB2Periph_GPIOA
#define      macESP8266_Tx_PORT                               GPIOA
#define      macESP8266_Tx_PIN                                GPIO_Pin_9

#define      macESP8266_Rx_APBxClock_FUN                      RCC_APB2PeriphClockCmd
#define      macESP8266_Rx_CLK                                RCC_APB2Periph_GPIOA
#define      macESP8266_Rx_PORT                               GPIOA
#define      macESP8266_Rx_PIN                                GPIO_Pin_10

/* Function Macro Definitions ------------------------*/

#define     macESP8266_CH_ENABLE()                 GPIO_SetBits ( macESP8266_CH_PD_PORT, macESP8266_CH_PD_PIN )
#define     macESP8266_CH_DISABLE()                GPIO_ResetBits ( macESP8266_CH_PD_PORT, macESP8266_CH_PD_PIN )

#define     macESP8266_RST_HIGH_LEVEL()            GPIO_SetBits ( macESP8266_RST_PORT, macESP8266_RST_PIN )
#define     macESP8266_RST_LOW_LEVEL()             GPIO_ResetBits ( macESP8266_RST_PORT, macESP8266_RST_PIN )


/* Exported Functions ------------------------*/
void ESP8266_Rst ( void );
void ESP8266_SendString (char * pStr, u8 ulStrLength);
uint16_t ESP8266_ReceiveValue (void);
void ESP8266_Init(void);


#endif
