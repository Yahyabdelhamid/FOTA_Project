/*****************************************************************************************
 * Author:				Abdullah M. Abdullah
 * Creation Data:		03 Jun, 2023
 * Version:				v1.0
 * Compiler:			GNU ARM-GCC
 * Controller:			STM32F401CCU6 (32-bit Architecture)
 * Processor:			Cortex M4 (32-bit Architecture)
 * Layer:				MCAL Layer
 *****************************************************************************************/
/*****************************************************************************************
 * Version	  Date				  Author				  Description
 * v1.0		  03 Jun, 2023	Abdullah M. Abdullah		  Initial Creation
*****************************************************************************************/
#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H
#include "STD_TYPES.h"

void MUSART1_voidInit(void);
void MUSART1_voidTransmit(u8 *ptr);
u8   MUSART1_u8Receive(void);
u8   MUSART1_u8ReceiveTimeOut(void);
void MUSART1_voidReceiveBuffer(char *Copy_ptrBuffer , u32 Copy_SizeBuffer);
void MUSART1_voidSendChar(u8 Copy_u8Data);

#endif
