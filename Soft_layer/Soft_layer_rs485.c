#include "soft_layer_rs485.h"

#include "Hardware_usart.h"

#include "string.h"

unsigned char rs485_send_02_buf[13]={0x00,0x02,0x00,0x07,IO_PN16,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00};
unsigned char rs485_send_04_buf[15]={0x00,0x04,0x00,0x08,IO_PN16,IO_output,bool_change,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char rs485_send_05_buf[7]={0x00,0x05,0x00,0x00,0x00,0x00,0x00};



/******************************************************************
 * @brief  02
 * @input  none
 * @return  none
******************************************************************/

void rs485_send_02(void)
{
  unsigned short temp;
  
	temp=crc16(rs485_send_02_buf,11);
	
	rs485_send_02_buf[11]=((temp&0xFF00)>>8);
	rs485_send_02_buf[12]=(unsigned char)(temp&0x00FF);

	usart1_send_data(rs485_send_02_buf,13);
  
}

/******************************************************************
 * @brief  04
 * @input  none
 * @return  none
******************************************************************/

void rs485_send_04(void)
{
  unsigned short temp;
  

	temp=crc16(rs485_send_04_buf,13);

	rs485_send_04_buf[13]=((temp&0xFF00)>>8);
	rs485_send_04_buf[14]=(unsigned char)(temp&0x00FF);

	usart1_send_data(rs485_send_04_buf,15);	
}

/******************************************************************
 * @brief  05
 * @input  none
 * @return  none
******************************************************************/


void rs485_send_05(void)
{
  unsigned short temp;
  
	rs485_send_05_buf[4]=modbus_management.station_address;
	
  temp=crc16(rs485_send_05_buf,5);
          
  
	rs485_send_05_buf[5]=((temp&0xFF00)>>8);
	rs485_send_05_buf[6]=(unsigned char)(temp&0x00FF);

	usart1_send_data(rs485_send_05_buf,7);
	
}

/******************************************************************
 * @brief Receiving Data Processing Function   
 * @input  none
 * @return  none
******************************************************************/
void rs485_receive_data_handler(void)
{
  unsigned short temp=0;
  
	if(modbus_management.receiveBuffer[0]==modbus_management.station_address)
	{
		switch(modbus_management.receiveBuffer[1])
		{
			case 0x01:  
			{
				if(modbus_management.receiveBuffer[3]==0)
				{
					temp=crc16(modbus_management.receiveBuffer,4);          
          
					if(((temp&0xFF00)>>8)==modbus_management.receiveBuffer[4] && 
						 (unsigned char)(temp&0x00FF)==modbus_management.receiveBuffer[5]) 
					{
						rs485_send_02();

					}
				}
				break;
			}

			case 0x03:  
			{
				if(modbus_management.receiveBuffer[3]== 8 && 
					 modbus_management.receiveBuffer[4] == IO_PN16)
				{
          temp=crc16(modbus_management.receiveBuffer,13);
                    
					if(((temp&0xFF00)>>8)==modbus_management.receiveBuffer[13] &&
						 (unsigned char)(temp&0x00FF)==modbus_management.receiveBuffer[14])
					{
            modbus_management.data_output=(modbus_management.receiveBuffer[12]+
            (modbus_management.receiveBuffer[11]<<8));
						rs485_send_04();
					}
				}
				break;
			}
			default:
			{
				break;
			}
		}
    memset(modbus_management.receiveBuffer,0,sizeof(modbus_management.receiveBuffer));
    DMA_SetCurrDataCounter(DMA1_Channel3,USART1_RECEIVE_BUFFER_SIZE);
    
		modbus_management.receiveBuffer[0]=0;
		modbus_management.receiveBuffer[1]=0;
	}
}

