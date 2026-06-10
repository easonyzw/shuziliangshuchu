#include "Soft_layer_IO_input.h"

sIO_parameter IO_parameter[16];

/*
 * 16 路数字量输出通道表。
 *
 * 原来的 IO_state_update() 对 CH0 ~ CH15 分别写了 16 段 if/else，
 * 每一路逻辑完全相同，只有 GPIO 端口和引脚不同。
 *
 * 这里改成表驱动：
 * - output_port/output_pin：实际数字量输出引脚
 * - led_port/led_pin：对应通道指示灯
 *
 * 注意：当前板子的输出通道和 LED 都是低电平有效：
 * - GPIO_ResetBits() 表示 ON
 * - GPIO_SetBits()   表示 OFF
 */
typedef struct
{
    GPIO_TypeDef *output_port;
    unsigned short output_pin;

    GPIO_TypeDef *led_port;
    unsigned short led_pin;
} sOutput_channel_config;

#define OUTPUT_CHANNEL_NUMBER 16

static const sOutput_channel_config output_channel_table[OUTPUT_CHANNEL_NUMBER] =
{
    /* output port, output pin, led port, led pin */
    {GPIOA, GPIO_Pin_1, GPIOA, GPIO_Pin_15},  /* CH0  -> LED0  */
    {GPIOC, GPIO_Pin_5, GPIOC, GPIO_Pin_11},  /* CH1  -> LED1  */
    {GPIOA, GPIO_Pin_0, GPIOD, GPIO_Pin_2 },  /* CH2  -> LED2  */
    {GPIOC, GPIO_Pin_4, GPIOB, GPIO_Pin_4 },  /* CH3  -> LED3  */
    {GPIOA, GPIO_Pin_7, GPIOB, GPIO_Pin_7 },  /* CH4  -> LED4  */
    {GPIOA, GPIO_Pin_6, GPIOC, GPIO_Pin_13},  /* CH5  -> LED5  */
    {GPIOA, GPIO_Pin_5, GPIOC, GPIO_Pin_14},  /* CH6  -> LED6  */
    {GPIOC, GPIO_Pin_3, GPIOC, GPIO_Pin_15},  /* CH7  -> LED7  */

    {GPIOA, GPIO_Pin_4, GPIOF, GPIO_Pin_7 },  /* CH8  -> LED8  */
    {GPIOF, GPIO_Pin_5, GPIOC, GPIO_Pin_10},  /* CH9  -> LED9  */
    {GPIOF, GPIO_Pin_4, GPIOC, GPIO_Pin_12},  /* CH10 -> LED10 */
    {GPIOA, GPIO_Pin_3, GPIOB, GPIO_Pin_3 },  /* CH11 -> LED11 */
    {GPIOA, GPIO_Pin_2, GPIOB, GPIO_Pin_5 },  /* CH12 -> LED12 */
    {GPIOC, GPIO_Pin_2, GPIOB, GPIO_Pin_6 },  /* CH13 -> LED13 */
    {GPIOC, GPIO_Pin_1, GPIOB, GPIO_Pin_8 },  /* CH14 -> LED14 */
    {GPIOC, GPIO_Pin_0, GPIOB, GPIO_Pin_9 }   /* CH15 -> LED15 */
};

static void output_gpio_set(unsigned char channel, unsigned char on)
{
    if(on)
    {
        GPIO_ResetBits(output_channel_table[channel].output_port,
                       output_channel_table[channel].output_pin);
    }
    else
    {
        GPIO_SetBits(output_channel_table[channel].output_port,
                     output_channel_table[channel].output_pin);
    }
}

static void output_led_set(unsigned char channel, unsigned char on)
{
    if(on)
    {
        GPIO_ResetBits(output_channel_table[channel].led_port,
                       output_channel_table[channel].led_pin);
    }
    else
    {
        GPIO_SetBits(output_channel_table[channel].led_port,
                     output_channel_table[channel].led_pin);
    }
}

static void output_channel_set(unsigned char channel, unsigned char on)
{
    output_gpio_set(channel, on);
    output_led_set(channel, on);
}

/******************************************************************
 * @brief  digital output data initialize
 * @input  none
 * @return none
 ******************************************************************/
void digital_output_initialization(void)
{
    unsigned char i;

    for(i = 0; i < OUTPUT_CHANNEL_NUMBER; i++)
    {
        IO_parameter[i].filter = 1;
    }
}

/******************************************************************
 * @brief  Update 16-channel output status and related LEDs
 * @input  none
 * @return none
 ******************************************************************/
void IO_state_update(void)
{
    unsigned char i;
    unsigned short output_data;

    output_data = modbus_management.data_output;

    for(i = 0; i < OUTPUT_CHANNEL_NUMBER; i++)
    {
        if((output_data & ((unsigned short)1 << i)) != 0)
        {
            output_channel_set(i, 1);
        }
        else
        {
            output_channel_set(i, 0);
        }
    }

    module_show_status_running();
}

/******************************************************************
 * @brief  LED status of station number waiting
 * @input  none
 * @return none
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

    for(i = 0; i < OUTPUT_CHANNEL_NUMBER; i++)
    {
        output_led_set(i, 1);
    }
}

void LED_all_close(void)
{
    unsigned char i;

    for(i = 0; i < OUTPUT_CHANNEL_NUMBER; i++)
    {
        output_led_set(i, 0);
    }
}
