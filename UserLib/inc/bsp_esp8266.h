#ifndef  __BSP_ESP8266_H
#define	 __BSP_ESP8266_H

/* Includes ------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

/* Private Variable ------------------------*/
u8 at_cwmode[] = {0x41, 0x54, 0x2B, 0x43, 0x57, 0x4D, 0x4F, 0x44, 0x45, 0x3D,   
                  0x33, 0x0D, 0x0A};//AT+CWMODE=3(回车)  
u8 at_rst[] = {0x41, 0x54, 0x2B, 0x52, 0x53, 0x54, 0x0D, 0x0A};//AT+RST(回车)  
u8 at_cwsap[] = {0x41, 0x54, 0x2B, 0x43, 0x57, 0x53, 0x41, 0x50, 0x3D, 0x22,   
         0x45, 0x53, 0x50, 0x38, 0x32, 0x36, 0x36, 0x5F, 0x54, 0x45,   
         0x53, 0x54, 0x22, 0x2C, 0x22, 0x31, 0x32, 0x33, 0x34, 0x35,   
         0x36, 0x37, 0x38, 0x39, 0x30, 0x22, 0x2C, 0x31, 0x2C, 0x33,   
         0x0D, 0x0A};//AT+CWSAP="ESP8266_TEST","1234567890",1,3(回车)  
u8 at_cipmux[] = {0x41, 0x54, 0x2B, 0x43, 0x49, 0x50, 0x4D, 0x55, 0x58,   
          0x3D, 0x31, 0x0D, 0x0A};//AT+CIPMUX=1(回车)  
u8 at_cipserver[] = {0x41, 0x54, 0x2B, 0x43, 0x49, 0x50, 0x53, 0x45, 0x52, 0x56,   
             0x45, 0x52, 0x3D, 0x31, 0x2C, 0x38, 0x30, 0x38, 0x30, 0x0D,   
             0x0A};//AT+CIPSERVER=1,8080(回车)

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
void ESP8266_SendString (char * pStr, u32 ulStrLength);
uint16_t ESP8266_ReceiveValue (void);
void ESP8266_Init(void);


#endif
