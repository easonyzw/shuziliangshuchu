#include "Soft_layer.h"
#include "Soft_layer_RS485.h"

#include "Hardware_EXTI.h"

/******************************************************************
 * @brief  software_init
 * @input  none
 * @return  none
******************************************************************/
void software_init(void)
{
	digital_output_initialization();

	station_number_initialization();
  
  EXTI2_close();
  
  rs485_send_04_buf[12]=0x00;
}

