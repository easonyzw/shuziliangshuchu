#include "soft_layer_IO_input.h"

sIO_parameter IO_parameter[16];

/* 引脚配置表：{CH端口, CH引脚, LED端口, LED引脚} */
const PinConfig_TypeDef pin_config_table[16] = {
    {GPIOA, GPIO_Pin_1,  GPIOA, GPIO_Pin_15},   /* CH0 */
    {GPIOC, GPIO_Pin_5,  GPIOC, GPIO_Pin_11},   /* CH1 */
    {GPIOA, GPIO_Pin_0,  GPIOD, GPIO_Pin_2},    /* CH2 */
    {GPIOC, GPIO_Pin_4,  GPIOB, GPIO_Pin_4},    /* CH3 */
    {GPIOA, GPIO_Pin_7,  GPIOB, GPIO_Pin_7},    /* CH4 */
    {GPIOA, GPIO_Pin_6,  GPIOC, GPIO_Pin_13},   /* CH5 */
    {GPIOA, GPIO_Pin_5,  GPIOC, GPIO_Pin_14},   /* CH6 */
    {GPIOC, GPIO_Pin_3,  GPIOC, GPIO_Pin_15},   /* CH7 */
    {GPIOA, GPIO_Pin_4,  GPIOF, GPIO_Pin_7},    /* CH8 */
    {GPIOF, GPIO_Pin_5,  GPIOC, GPIO_Pin_10},   /* CH9 */
    {GPIOF, GPIO_Pin_4,  GPIOC, GPIO_Pin_12},   /* CH10 */
    {GPIOA, GPIO_Pin_3,  GPIOB, GPIO_Pin_3},    /* CH11 */
    {GPIOA, GPIO_Pin_2,  GPIOB, GPIO_Pin_5},    /* CH12 */
    {GPIOC, GPIO_Pin_2,  GPIOB, GPIO_Pin_6},    /* CH13 */
    {GPIOC, GPIO_Pin_1,  GPIOB, GPIO_Pin_8},    /* CH14 */
    {GPIOC, GPIO_Pin_0,  GPIOB, GPIO_Pin_9},    /* CH15 */
};

/******************************************************************
 * @brief  digital input data initialize
 * @input  none
 * @return  none
******************************************************************/
void digital_output_initialization(void)
{
    unsigned char i;

    for(i = 0; i < 16; i++)
    {
        IO_parameter[i].filter = 1;
    }
}

/******************************************************************
 * @brief  表驱动：根据 data_output 逐位控制 16 路通道+LED
 * @input  none
 * @return  none
******************************************************************/
void IO_state_update(void)
{
    unsigned char i;

    for(i = 0; i < 16; i++)
    {
        if((modbus_management.data_output >> i) & 0x01)
        {
            CH_ON(i);
            LED_ON(i);
        }
        else
        {
            CH_OFF(i);
            LED_OFF(i);
        }
    }

    module_show_status_running();
}

/******************************************************************
 * @brief  LED status of station number waiting
 * @input  none
 * @return  none
******************************************************************/
void module_show_status(void)
{
    if(timer_counter.LED_ms > 500)
    {
        LED_all_close();
        timer_counter.LED_ms = 0;
    }
    else if(timer_counter.LED_ms > 250)
    {
        LED_all_open();
    }
}

void module_show_status_running(void)
{
    if(modbus_management.data_output != 0)
    {
        return;
    }

    if(timer_counter.LED_ms > 5200)
    {
        LED_all_close();
        timer_counter.LED_ms = 0;
    }
    else if(timer_counter.LED_ms > 5000)
    {
        LED_all_open();
    }
}

void LED_all_open(void)
{
    unsigned char i;
    for(i = 0; i < 16; i++)
    {
        LED_ON(i);
    }
}

void LED_all_close(void)
{
    unsigned char i;
    for(i = 0; i < 16; i++)
    {
        LED_OFF(i);
    }
}