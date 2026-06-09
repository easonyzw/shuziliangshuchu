#include "Soft_layer_bus.h"

/******************************************************************
 * @brief   Station number initialization
 * @input   none
 * @return  none
******************************************************************/
void station_number_initialization(void)
{
	receive_pulse_station_number();
  last_station_handle();
}

/******************************************************************
 * @brief   Receive station number
 * @input   none
 * @return  none
******************************************************************/
void receive_pulse_station_number(void)
{
  memset(&timer_counter,NULL,sizeof(timer_counter));
  memset(&modbus_management,NULL,sizeof(modbus_management));
  
	while(1)
	{
    module_show_status();
    
    if(modbus_management.flag_got_pulse==1)
    {
      
    }
    else
    {
      timer_counter.bus=0;
    }
    
    if(timer_counter.bus>10)
    {
      return;
    }    
	}
}

/******************************************************************
 * @brief   Last station handle
 * @input   none
 * @return  none
******************************************************************/
void last_station_handle(void)
{
  
  unsigned char i=0;
  
	GPIO_InitTypeDef GPIO_InitStructure;

  rs485_send_02_buf[0]=modbus_management.station_address;
  rs485_send_04_buf[0]=modbus_management.station_address;
  rs485_send_05_buf[0]=modbus_management.station_address;
  
  
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==1)
	{
			delay_ms(5);
    
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==1)
			{
				/* Send 05 function code */ 
				rs485_send_05();  
			}
      else
      {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;          
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        BUS_output=0;
        
        for(i=0;i<modbus_management.station_address+1;i++)
        {

          BUS_output=1;
          delay_us(50);          
          BUS_output=0;
          delay_us(50);
        }
      }
	}
  else
  {

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;          
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    BUS_output=0;
    
    for(i=0;i<modbus_management.station_address+1;i++)
    {
      
      BUS_output=1;
      delay_us(50);          
      BUS_output=0;
      delay_us(50);
    }
    
  }
}







