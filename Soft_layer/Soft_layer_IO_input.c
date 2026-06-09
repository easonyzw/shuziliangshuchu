#include "soft_layer_IO_input.h"

sIO_parameter IO_parameter[16];

/******************************************************************
 * @brief  digital input data initialize
 * @input  none
 * @return  none
******************************************************************/
void digital_output_initialization(void)
{
  unsigned char i;
		
	for(i=0;i<16;i++)
	{
			IO_parameter[i].filter=1;
	}
	
}


/******************************************************************
 * @brief  Port LED 
 * @input  none
 * @return  none
******************************************************************/
void IO_state_update(void)                          
{
  
    if(((modbus_management.data_output>>0)&0x01) == 0x01)
		{
			CH_0_ON;
			LED_0_ON;
		}
		else 
    {
			CH_0_OFF;
			LED_0_OFF;
		}
    
    if(((modbus_management.data_output>>1)&0x01) == 0x01)
		{
			CH_1_ON;
			LED_1_ON;
		}
		else 
    {
			CH_1_OFF;
			LED_1_OFF;
		}
    
    if(((modbus_management.data_output>>2)&0x01) == 0x01)
		{
			CH_2_ON;
			LED_2_ON;
		}
		else 
    {
			CH_2_OFF;
			LED_2_OFF;
		}
    
    if(((modbus_management.data_output>>3)&0x01) == 0x01)
		{
			CH_3_ON;
			LED_3_ON;
		}
		else 
    {
			CH_3_OFF;
			LED_3_OFF;
		}
    
    if(((modbus_management.data_output>>4)&0x01) == 0x01)
		{
			CH_4_ON;
			LED_4_ON;
		}
		else 
    {
			CH_4_OFF;
			LED_4_OFF;
		}
    
    if(((modbus_management.data_output>>5)&0x01) == 0x01)
		{
			CH_5_ON;
			LED_5_ON;
		}
		else 
    {
			CH_5_OFF;
			LED_5_OFF;
		}
    
    if(((modbus_management.data_output>>6)&0x01) == 0x01)
		{
			CH_6_ON;
			LED_6_ON;
		}
		else 
    {
			CH_6_OFF;
			LED_6_OFF;
		}
    
    if(((modbus_management.data_output>>7)&0x01) == 0x01)
		{
			CH_7_ON;
			LED_7_ON;
		}
		else 
    {
			CH_7_OFF;
			LED_7_OFF;
		}
    
    if(((modbus_management.data_output>>8)&0x01) == 0x01)
		{
			CH_8_ON;
			LED_8_ON;
		}
		else 
    {
			CH_8_OFF;
			LED_8_OFF;
		}
    
    if(((modbus_management.data_output>>9)&0x01) == 0x01)
		{
			CH_9_ON;
			LED_9_ON;
		}
		else 
    {
			CH_9_OFF;
			LED_9_OFF;
		}
    
    if(((modbus_management.data_output>>10)&0x01) == 0x01)
		{
			CH_10_ON;
			LED_10_ON;
		}
		else 
    {
			CH_10_OFF;
			LED_10_OFF;
		}
    
    if(((modbus_management.data_output>>11)&0x01) == 0x01)
		{
			CH_11_ON;
			LED_11_ON;
		}
		else 
    {
			CH_11_OFF;
			LED_11_OFF;
		}
    
    if(((modbus_management.data_output>>12)&0x01) == 0x01)
		{
			CH_12_ON;
			LED_12_ON;
		}
		else 
    {
			CH_12_OFF;
			LED_12_OFF;
		}
    
    if(((modbus_management.data_output>>13)&0x01) == 0x01)
		{
			CH_13_ON;
			LED_13_ON;
		}
		else 
    {
			CH_13_OFF;
			LED_13_OFF;
		}
    
    if(((modbus_management.data_output>>14)&0x01) == 0x01)
		{
			CH_14_ON;
			LED_14_ON;
		}
		else 
    {
			CH_14_OFF;
			LED_14_OFF;
		}
    
    if(((modbus_management.data_output>>15)&0x01) == 0x01)
		{
			CH_15_ON;
			LED_15_ON;
		}
		else 
    {
			CH_15_OFF;
			LED_15_OFF;
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
  if(timer_counter.LED_ms>500)
  {
    LED_all_close();
    timer_counter.LED_ms=0;
  }
  else if(timer_counter.LED_ms>250)
  {    
    LED_all_open();
  }
}

void module_show_status_running(void)
{
  if(modbus_management.data_output!=0)
  {
    return;
  }
  
  if(timer_counter.LED_ms>5200)
  {
    LED_all_close();
    timer_counter.LED_ms=0;
  }
  else if(timer_counter.LED_ms>5000)
  {    
    LED_all_open();
  }
}

void LED_all_open(void)
{
	PCout(13)=0;
  PCout(14)=0;
  PCout(15)=0;
  PBout(4)=0;
  PBout(7)=0;
  PDout(2)=0;
  PCout(10)=0;
  PAout(15)=0;	
  PBout(9)=0;
  PBout(8)=0;
  PBout(6)=0;
  PBout(5)=0;
  PBout(3)=0;
  PCout(12)=0;
  PCout(11)=0;
  PFout(7)=0;
}


void LED_all_close(void)
{
	PCout(13)=1;
  PCout(14)=1;
  PCout(15)=1;
  PBout(4)=1;
  PBout(7)=1;
  PDout(2)=1;
  PCout(10)=1;
  PAout(15)=1;	
  PBout(9)=1;
  PBout(8)=1;
  PBout(6)=1;
  PBout(5)=1;
  PBout(3)=1;
  PCout(12)=1;
  PCout(11)=1;
  PFout(7)=1;
}


