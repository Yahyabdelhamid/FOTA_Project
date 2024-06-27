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
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"
#include "GPIO_interface.h"



/* USART1 */
void MUSART1_voidInit(void)

{
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN9, GPIO_AF);  // Tx
//	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN9, GPIO_OUTPUT);
//	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN9, GPIO_MED_SPEED);
//	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN9, GPIO_OUTPUT_PP);
//	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN10, GPIO_INPUT);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN10, GPIO_AF); // Rx

	MGPIO_voidSetAlternativeFunction(GPIO_PORTA, GPIO_PIN9, 7);
	MGPIO_voidSetAlternativeFunction(GPIO_PORTA, GPIO_PIN10, 7);

	    USART1 -> CR1 = 0x200C;
	    USART1 -> BRR = 0x45;

	/* clear status register */
	USART1 -> SR = 0;

}

void MUSART1_voidTransmit(u8 *ptr)
{
	u8 Local_u8Counter = 0;
	while(ptr[Local_u8Counter] != '\0')
	{
		USART1 -> DR = ptr[Local_u8Counter];

		/* wait till transmit is complete */
		while((GET_BIT((USART1 -> SR), 6)) == 0);
		Local_u8Counter++;
	}
}

void MUSART1_voidSendChar(u8 Copy_u8Data)
{
		USART1 -> DR = Copy_u8Data;

		/* wait till transmit is complete */
		while((GET_BIT((USART1 -> SR), 6)) == 0);
}

u8   MUSART1_u8Receive(void)
{
	u8 Local_s8ReceivedData = 0;
	while(((USART1 -> SR) & (1 << 5)) == 0);
	Local_s8ReceivedData = ((0xFF) & (USART1 -> DR)) ;

	return (Local_s8ReceivedData);
}


void MUSART1_voidReceiveBuffer(char *Copy_ptrBuffer , u32 Copy_SizeBuffer)
{
	u32 Local_u8Iterator = 0;


	for(Local_u8Iterator = 0; Local_u8Iterator < Copy_SizeBuffer; Local_u8Iterator++ )
	{
		Copy_ptrBuffer[Local_u8Iterator] = MUSART1_u8ReceiveTimeOut();
	}
}

u8   MUSART1_u8ReceiveTimeOut(void)
{
	u32 timeout = 0;
	char Local_s8ReceivedData = 0;
	while(((USART1 -> SR) & (1 << 5)) == 0)
	{
		timeout++;
		if(timeout == 10000)

		{
			Local_s8ReceivedData = 255;
			break;
		}
	}
	if(Local_s8ReceivedData == 0)
	{
		Local_s8ReceivedData = ((0xFF) & (USART1 -> DR)) ;
	}

	return (Local_s8ReceivedData);
}



u8 MUSART1_u8ReceiveDataIfReceived(u8 * Copy_pu8ReceivedData)
{
    u8 Local_u8ReceiveState = 0;
    if(GET_BIT(USART1 -> SR, 5) == 1)
    {
        *Copy_pu8ReceivedData = USART1 -> DR;
        CLR_BIT(USART1 -> SR, 5);
        Local_u8ReceiveState = 1;
    }
    else
    {
        Local_u8ReceiveState = 0;
    }
    return Local_u8ReceiveState;
}





/************************************************************************
 * **********************************************************************
 * **********************************************************************/

