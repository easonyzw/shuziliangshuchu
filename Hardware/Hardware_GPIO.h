#ifndef _Hardware_GPIO_H
#define _Hardware_GPIO_H

#include "Hardware.h"
#include "stm32f0xx.h"

/***********************************   Macro Definition   ********************************/  

/* 引脚配置结构体 —— 每个通道一对 (CH引脚 + LED引脚) */
typedef struct {
    GPIO_TypeDef* ch_port;
    uint16_t      ch_pin;
    GPIO_TypeDef* led_port;
    uint16_t      led_pin;
} PinConfig_TypeDef;

extern const PinConfig_TypeDef pin_config_table[16];

/* 表驱动：置位 / 复位宏 */
#define CH_ON(idx)   GPIO_ResetBits(pin_config_table[idx].ch_port,  pin_config_table[idx].ch_pin)
#define CH_OFF(idx)  GPIO_SetBits  (pin_config_table[idx].ch_port,  pin_config_table[idx].ch_pin)
#define LED_ON(idx)  GPIO_ResetBits(pin_config_table[idx].led_port, pin_config_table[idx].led_pin)
#define LED_OFF(idx) GPIO_SetBits  (pin_config_table[idx].led_port, pin_config_table[idx].led_pin)


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

