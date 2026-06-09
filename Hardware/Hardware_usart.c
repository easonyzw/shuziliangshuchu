#include "Hardware_usart.h"
#include "string.h"

sModbus_management    modbus_management;


/******************************************************************
 * @brief   USART Initializes
 * @input   none
 * @return  none
******************************************************************/
void RS485_initializes(void)
{
  USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  USART_OverSampling8Cmd(USART1,ENABLE);
	USART_InitStructure.USART_BaudRate = 6000000;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
  /*********************************************/
	USART_DECmd(USART1,ENABLE);
	USART_SetDEAssertionTime(USART1,0x1F);
	USART_DEPolarityConfig(USART1,USART_DEPolarity_High);
	/*********************************************/
	
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	USART_DMACmd(USART1,USART_DMAReq_Rx | USART_DMAReq_Tx,ENABLE);
	USART_Cmd(USART1, ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	DMA_Config_TX(DMA1_Channel2,(unsigned int)&USART1->TDR,(unsigned int)modbus_management.sendBuffer,USART1_SEND_BUFFER_SIZE); 
  DMA_Config_RX(DMA1_Channel3,(unsigned int)&USART1->RDR,(unsigned int)modbus_management.receiveBuffer,USART1_RECEIVE_BUFFER_SIZE);
	
}

/******************************************************************
 * @brief   DMA_Config_TX
 * @input   DMA_CHx :
 *          cpar    :  DMA_PeripheralBaseAddr
 *          cmar    :  DMA_MemoryBaseAddr
 *          cndtr   :  DMA_BufferSize
 * @return  none
******************************************************************/
void DMA_Config_TX(DMA_Channel_TypeDef* DMA_CHx,unsigned int cpar,unsigned int cmar,unsigned short int cndtr)
{
    DMA_InitTypeDef DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
    DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;
    DMA_InitStructure.DMA_MemoryBaseAddr = cmar;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = cndtr;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);
}
/******************************************************************
 * @brief   DMA_Config_RX
 * @input   DMA_CHx :
 *          cpar    :  DMA_PeripheralBaseAddr
 *          cmar    :  DMA_MemoryBaseAddr
 *          cndtr   :  DMA_BufferSize
 * @return  none
******************************************************************/
void DMA_Config_RX(DMA_Channel_TypeDef* DMA_CHx,unsigned int cpar,unsigned int cmar,unsigned short int cndtr)
{
    DMA_InitTypeDef DMA_InitStructure;
	
    DMA_DeInit(DMA_CHx);
    DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;
    DMA_InitStructure.DMA_MemoryBaseAddr = cmar;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = cndtr;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA_CHx, &DMA_InitStructure);

    DMA_Cmd(DMA_CHx, ENABLE);
}
/******************************************************************
 * @brief   DMA_Enable
 * @input   DMA_CHx :
 *          CNDTR   :
 * @return  none
******************************************************************/
void DMA_Enable(DMA_Channel_TypeDef*DMA_CHx,u16 CNDTR)
{
    DMA_CHx->CCR&=~(1<<0);      
    DMA_CHx->CNDTR = CNDTR;     
    DMA_CHx->CCR|=1<<0;          
}




/******************************************************************
 * @brief  485 Sender Function
 * @input  none
 * @return  none
******************************************************************/
void usart1_send_data(unsigned char* data , unsigned char len)
{
	DMA_ClearFlag(DMA1_FLAG_TC2);                   
	DMA_Cmd(DMA1_Channel2, DISABLE );               
	memcpy(modbus_management.sendBuffer,data,len);
	DMA_Enable(DMA1_Channel2,len);
}

/******************************************************************
 * @brief  Serial transaction functions
 * @input  none
 * @return  none
******************************************************************/
void USART1_IRQHandler(void)
{
	volatile unsigned char temp;
  
	if(USART_GetFlagStatus(USART1,USART_FLAG_IDLE) != RESET)
	{

		DMA_Cmd(DMA1_Channel3,DISABLE);
    
		modbus_management.receive_length = USART1_RECEIVE_BUFFER_SIZE- DMA_GetCurrDataCounter(DMA1_Channel3); 
    DMA_Enable(DMA1_Channel3,USART1_RECEIVE_BUFFER_SIZE);
		USART_ClearITPendingBit(USART1,USART_IT_IDLE);
    
		temp = USART1 -> ISR;
		temp = USART1 -> RDR;

	  if(modbus_management.receive_length>5)
		{
			rs485_receive_data_handler();
		}
		
	}
  
  USART_ClearITPendingBit(USART1,USART_IT_IDLE);
  
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE) == SET) 
	{
		USART_ClearFlag(USART1,USART_FLAG_ORE);
	}
}


