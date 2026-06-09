#ifndef _Hardware_GPIO_H
#define _Hardware_GPIO_H

#include "Hardware.h"
#include "stm32f0xx.h"

/***********************************   Macro Definition   ********************************/  
/* LED GPIO Pin */
#define LED_0_OFF  GPIO_SetBits(GPIOA,GPIO_Pin_15)
#define LED_0_ON   GPIO_ResetBits(GPIOA,GPIO_Pin_15)

#define LED_1_OFF  GPIO_SetBits(GPIOC,GPIO_Pin_11)
#define LED_1_ON   GPIO_ResetBits(GPIOC,GPIO_Pin_11)

#define LED_2_OFF  GPIO_SetBits(GPIOD,GPIO_Pin_2)
#define LED_2_ON   GPIO_ResetBits(GPIOD,GPIO_Pin_2)

#define LED_3_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_4)
#define LED_3_ON   GPIO_ResetBits(GPIOB,GPIO_Pin_4)

#define LED_4_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define LED_4_ON   GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define LED_5_OFF  GPIO_SetBits(GPIOC,GPIO_Pin_13)
#define LED_5_ON   GPIO_ResetBits(GPIOC,GPIO_Pin_13)

#define LED_6_OFF  GPIO_SetBits(GPIOC,GPIO_Pin_14)
#define LED_6_ON   GPIO_ResetBits(GPIOC,GPIO_Pin_14)

#define LED_7_OFF  GPIO_SetBits(GPIOC,GPIO_Pin_15)
#define LED_7_ON   GPIO_ResetBits(GPIOC,GPIO_Pin_15)

#define LED_8_OFF  GPIO_SetBits(GPIOF,GPIO_Pin_7)
#define LED_8_ON   GPIO_ResetBits(GPIOF,GPIO_Pin_7)

#define LED_9_OFF  GPIO_SetBits(GPIOC,GPIO_Pin_10)
#define LED_9_ON   GPIO_ResetBits(GPIOC,GPIO_Pin_10)

#define LED_10_OFF  GPIO_SetBits(GPIOC,GPIO_Pin_12)
#define LED_10_ON   GPIO_ResetBits(GPIOC,GPIO_Pin_12)

#define LED_11_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define LED_11_ON   GPIO_ResetBits(GPIOB,GPIO_Pin_3)

#define LED_12_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define LED_12_ON   GPIO_ResetBits(GPIOB,GPIO_Pin_5)

#define LED_13_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define LED_13_ON   GPIO_ResetBits(GPIOB,GPIO_Pin_6)

#define LED_14_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define LED_14_ON   GPIO_ResetBits(GPIOB,GPIO_Pin_8)

#define LED_15_OFF  GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define LED_15_ON   GPIO_ResetBits(GPIOB,GPIO_Pin_9)




#define CH_0_OFF GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define CH_0_ON  GPIO_ResetBits(GPIOA,GPIO_Pin_1)

#define CH_1_OFF GPIO_SetBits(GPIOC,GPIO_Pin_5)
#define CH_1_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_5)

#define CH_2_OFF GPIO_SetBits(GPIOA,GPIO_Pin_0)
#define CH_2_ON  GPIO_ResetBits(GPIOA,GPIO_Pin_0)

#define CH_3_OFF GPIO_SetBits(GPIOC,GPIO_Pin_4)
#define CH_3_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_4)

#define CH_4_OFF GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define CH_4_ON  GPIO_ResetBits(GPIOA,GPIO_Pin_7)

#define CH_5_OFF GPIO_SetBits(GPIOA,GPIO_Pin_6)
#define CH_5_ON  GPIO_ResetBits(GPIOA,GPIO_Pin_6)

#define CH_6_OFF GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define CH_6_ON  GPIO_ResetBits(GPIOA,GPIO_Pin_5)

#define CH_7_OFF GPIO_SetBits(GPIOC,GPIO_Pin_3)
#define CH_7_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_3)


#define CH_8_OFF GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define CH_8_ON  GPIO_ResetBits(GPIOA,GPIO_Pin_4)

#define CH_9_OFF GPIO_SetBits(GPIOF,GPIO_Pin_5)
#define CH_9_ON  GPIO_ResetBits(GPIOF,GPIO_Pin_5)

#define CH_10_OFF GPIO_SetBits(GPIOF,GPIO_Pin_4)
#define CH_10_ON  GPIO_ResetBits(GPIOF,GPIO_Pin_4)

#define CH_11_OFF GPIO_SetBits(GPIOA,GPIO_Pin_3)
#define CH_11_ON  GPIO_ResetBits(GPIOA,GPIO_Pin_3)

#define CH_12_OFF GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define CH_12_ON  GPIO_ResetBits(GPIOA,GPIO_Pin_2)

#define CH_13_OFF GPIO_SetBits(GPIOC,GPIO_Pin_2)
#define CH_13_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_2)

#define CH_14_OFF GPIO_SetBits(GPIOC,GPIO_Pin_1)
#define CH_14_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_1)

#define CH_15_OFF GPIO_SetBits(GPIOC,GPIO_Pin_0)
#define CH_15_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_0)



/* BUS GPIO Pin*/
#define BUS_input   PBin(2)
#define BUS_output  PBout(1)

/***********************************    Function    **************************************/
/* GPIO initializes */
void GPIO_initializes(void);
/* LED */
void GPIO_LED_Configuration(void);
/* Input pin */
void GPIO_output_Configuration(void);
/* BUS */
void GPIO_BUS_Configuration(void);
/* USART */
void GPIO_usart1_Configuration(void);



#endif

