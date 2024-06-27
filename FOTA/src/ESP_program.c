#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_interface.h"
#include "STK_interface.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"



void delay_us(u32 us) {
    // Assuming the system clock is 84 MHz (typical for STM32F4 running at max speed)
    // One clock cycle at 84 MHz is approximately 11.9 ns (1 / 84,000,000)
    // Therefore, we need about 84 cycles per microsecond

    u32 count = us * 16;
    while (count--) {
        asm("NOP");
    }
}


#define Buffer_Size     2000


void ESP_voidInit(void)
{
	char Local_charDataReceive1[6] = {0};
	char Local_charDataReceive2[6] = {0};
	u8 Local_u8Event = 0;
	u8 Local_u8Counter = 0;

	/* stop ECHO */
	while(Local_u8Event == 0)
	{
		MUSART1_voidTransmit((u8*)"ATE0\r\n");
		MUSART1_voidReceiveBuffer(Local_charDataReceive1 , 6);
		for(Local_u8Counter = 0; Local_u8Counter < 6; Local_u8Counter++)
		{
			if((Local_charDataReceive1[Local_u8Counter] == 'O') && (Local_charDataReceive1[Local_u8Counter+1] == 'K'))
			{
				Local_u8Event = 1;
				//MSTK_voidSetBusyWait(100);

				break;
			}
		}


		delay_us(100*1000);

	}
//	MSTK_voidSetBusyWait(100);
	asm("NOP");
	Local_u8Event = 0;

	/* Set station mode */
	while(Local_u8Event == 0)
	{
		MUSART1_voidTransmit((u8*)"AT+CWMODE=1\r\n");
		MUSART1_voidReceiveBuffer(Local_charDataReceive2 , 6);
		for(Local_u8Counter = 0; Local_u8Counter < 6; Local_u8Counter++)
		{
			if((Local_charDataReceive2[Local_u8Counter] == 'O') && (Local_charDataReceive2[Local_u8Counter+1] == 'K'))
			{
				Local_u8Event = 1;
				break;
			}
		}

		delay_us(100*1000);
		//MSTK_voidSetBusyWait(100);
	}

}


void ESP_voidConnectToWiFi(u8 *Copy_name , u8 *Copy_pass)
{
	char Local_charDataReceive1[255] = {0};
	char Local_charDataReceive2[255] = {0};

	MUSART1_voidTransmit((u8*)"AT+CWJAP_CUR=\"");
	MUSART1_voidTransmit((u8*)Copy_name);
	MUSART1_voidTransmit((u8*)"\",\"");
	MUSART1_voidTransmit((u8*)Copy_pass);
	MUSART1_voidTransmit((u8*)"\"\r\n");
	MUSART1_voidReceiveBuffer(Local_charDataReceive1 , 255);
	MUSART1_voidReceiveBuffer(Local_charDataReceive2 , 255);
	delay_us(10*1000);
	//MSTK_voidSetBusyWait(10);
}


void ESP_voidConnectToSrvTcp (u8 *Copy_u8Domain , u8 *Copy_u8Port)
{
	char Local_charDataReceive[25] = {0};

	/* connect to server */
	MUSART1_voidTransmit((u8*)"AT+CIPSTART=\"TCP\",\"");
	MUSART1_voidTransmit((u8*)Copy_u8Domain);
	MUSART1_voidTransmit((u8*)"\",");
	MUSART1_voidTransmit((u8*)Copy_u8Port);
	MUSART1_voidTransmit((u8*)"\r\n");
	MUSART1_voidReceiveBuffer(Local_charDataReceive , 25);
}


u8   ESP_u8ReceiveHttpReq(u8 *Copy_u8ChannelID , u8 *Copy_u8Length)
{
	char Local_charDataReceive1[6] = {0};
	char Local_charDataReceive2[60] = {0};
	u8 Local_u8Event = 0;
	u8 Local_u8Counter = 0;

	while(Local_u8Event == 0)
	{
		MUSART1_voidTransmit((u8*)"AT+CIPSEND=");
		MUSART1_voidTransmit((u8*)Copy_u8Length);
		MUSART1_voidTransmit((u8*)"\r\n");
		MUSART1_voidReceiveBuffer(Local_charDataReceive1 , 6);
		for(Local_u8Counter = 0; Local_u8Counter < 6; Local_u8Counter++)
		{
			if((Local_charDataReceive1[Local_u8Counter] == 'O') && (Local_charDataReceive1[Local_u8Counter+1] == 'K'))
			//if((Local_charDataReceive1[Local_u8Counter] == 'C') && (Local_charDataReceive1[Local_u8Counter+1] == 'L')&&(Local_charDataReceive1[Local_u8Counter+2] == 'O')&&(Local_charDataReceive1[Local_u8Counter+3] == 'S')&&(Local_charDataReceive1[Local_u8Counter+4] == 'E')&&(Local_charDataReceive1[Local_u8Counter+5] == 'D'))
			{
				Local_u8Event = 1;
				break;
			}
		}
		delay_us(10*1000);
		//MSTK_voidSetBusyWait(10);
	}

	Local_u8Event = 0;

	while(Local_u8Event == 0)
	{
		MUSART1_voidTransmit((u8*)Copy_u8ChannelID);
		MUSART1_voidReceiveBuffer(Local_charDataReceive2 , 60);

		for(Local_u8Counter = 0; Local_u8Counter < 60; Local_u8Counter++)
		{
			if((Local_charDataReceive2[Local_u8Counter] == '+') && (Local_charDataReceive2[Local_u8Counter+1] == 'I') && (Local_charDataReceive2[Local_u8Counter+2] == 'P')&& (Local_charDataReceive2[Local_u8Counter+3] == 'D') && (Local_charDataReceive2[Local_u8Counter+4] == ',') && (Local_charDataReceive2[Local_u8Counter+5] == '1') && (Local_charDataReceive2[Local_u8Counter+6] == ':'))
			{
				Local_u8Event = Local_charDataReceive2[Local_u8Counter+7];
				break;

			}
		}
		delay_us(500*1000);
		//MSTK_voidSetBusyWait(500);
	}
	return Local_u8Event;
}


void ESP_voidSendOk(u8 * Copy_u8ChannelID , u8 * Copy_u8Length)
{
	char Local_charDataReceive1[6] = {0};
	char Local_charDataReceive2[70] = {0};
	u8 Local_u8Event = 0;
	u8 Local_u8Counter = 0;

	while(Local_u8Event == 0)
	{
		MUSART1_voidTransmit((u8*)"AT+CIPSEND=");
		MUSART1_voidTransmit((u8*)Copy_u8Length);
		MUSART1_voidTransmit((u8*)"\r\n");
		MUSART1_voidReceiveBuffer(Local_charDataReceive1 , 6);
		for(Local_u8Counter = 0; Local_u8Counter < 6; Local_u8Counter++)
		{
			if((Local_charDataReceive1[Local_u8Counter] == 'O') && (Local_charDataReceive1[Local_u8Counter+1] == 'K'))
			{
				Local_u8Event = 1;
				break;
			}
		}
		delay_us(10*1000);
		//MSTK_voidSetBusyWait(10);
	}

	Local_u8Event = 0;

	while(Local_u8Event == 0)
	{
		MUSART1_voidTransmit((u8*)Copy_u8ChannelID);
		MUSART1_voidReceiveBuffer(Local_charDataReceive2 , 70);
		for(Local_u8Counter = 0; Local_u8Counter < 70; Local_u8Counter++)
		{
			if((Local_charDataReceive1[Local_u8Counter] == 'O') && (Local_charDataReceive1[Local_u8Counter+1] == 'K'))
			{
				Local_u8Event = 1;
				break;
			}
		}
		delay_us(10*1000);
		//MSTK_voidSetBusyWait(10);
	}
}






//void ESP_voidReceiveHttpReq(u8 * Copy_u8ChannelID, u8 * Copy_u8Length, char* Data) {
//    char Local_charDataReceive1[6] = {0};
//    u8 Local_u8Event = 0;
//    u16 Local_u8Counter = 0;
//
//    /* Clear Data */
//    for(Local_u8Counter = 0; Local_u8Counter < Buffer_Size; Local_u8Counter++) {
//        Data[Local_u8Counter] = 0;
//    }
//
//    /* Send the initial command and wait for OK response */
//    while(Local_u8Event == 0) {
//        MUSART1_voidTransmit((u8*)"AT+CIPSEND=");
//        MUSART1_voidTransmit((u8*)Copy_u8Length);
//        MUSART1_voidTransmit((u8*)"\r\n");
//        MUSART1_voidReceiveBuffer(Local_charDataReceive1, 6);
//
//        /* Check for "OK" response */
//        if (strstr(Local_charDataReceive1, "OK")) {
//            Local_u8Event = 1;
//        }
//
//        delay_us(10 * 1000); // 10 ms delay
//    }
//
//    Local_u8Event = 0;
//
//    /* Send the HTTP GET request and wait for data */
//    while(Local_u8Event == 0) {
//        MUSART1_voidTransmit((u8*)Copy_u8ChannelID);
//        MUSART1_voidReceiveBuffer(Data, Buffer_Size);
//
//        /* Check for end markers '@' or '#' */
//        for(Local_u8Counter = 0; Local_u8Counter < Buffer_Size; Local_u8Counter++) {
//            if(Data[Local_u8Counter] == '@' || Data[Local_u8Counter] == '#') {
//                Local_u8Event = 1;
//                break;
//            }
//        }
//
//        delay_us(500 * 1000); // 500 ms delay
//    }
//}




void ESP_voidReceiveHttpReq(u8 * Copy_u8ChannelID , u8 * Copy_u8Length , char* Data)
{
	char Local_charDataReceive1[6] = {0};
	u8 Local_u8Event = 0;
	u16 Local_u8Counter = 0;

	/*Clear Data*/
	for(Local_u8Counter = 0; Local_u8Counter < Buffer_Size; Local_u8Counter++)
	{
		Data[Local_u8Counter] = 0;
	}

	while(Local_u8Event == 0)
	{
		MUSART1_voidTransmit((u8*)"AT+CIPSEND=");
		MUSART1_voidTransmit((u8*)Copy_u8Length);
		MUSART1_voidTransmit((u8*)"\r\n");
		MUSART1_voidReceiveBuffer(Local_charDataReceive1 , 6);
		for(Local_u8Counter = 0; Local_u8Counter < 6; Local_u8Counter++)
		{
			if((Local_charDataReceive1[Local_u8Counter] == 'O') && (Local_charDataReceive1[Local_u8Counter+1] == 'K'))
			{
				Local_u8Event = 1;
				break;
			}
		}
		delay_us(10);
	}



	Local_u8Event = 0;

	while(Local_u8Event == 0)
	{
		MUSART1_voidTransmit((u8*)Copy_u8ChannelID);
		MUSART1_voidReceiveBuffer(Data , Buffer_Size);


		for(Local_u8Counter = 0; Local_u8Counter < Buffer_Size; Local_u8Counter++)
		{
			if((Data[Local_u8Counter] == '@') || (Data[Local_u8Counter] == '#') )
			{
				Local_u8Event = 1;
				break;
			}
		}
		 delay_us(500 * 1000);;
	}
}
























































































//void ESP_voidReceiveHttpReq(u8 * Copy_u8ChannelID , u8 * Copy_u8Length , char* Data)
//{
//	char Local_charDataReceive1[6] = {0};
//	u8 Local_u8Event = 0;
//	u16 Local_u8Counter = 0;
//
//	/*Clear Data*/
//	for(Local_u8Counter = 0; Local_u8Counter < Buffer_Size; Local_u8Counter++)
//	{
//		Data[Local_u8Counter] = 0;
//	}
//
//	while(Local_u8Event == 0)
//	{
//		MUSART1_voidTransmit((u8*)"AT+CIPSEND=");
//		MUSART1_voidTransmit((u8*)Copy_u8Length);
//		MUSART1_voidTransmit((u8*)"\r\n");
//		MUSART1_voidReceiveBuffer(Local_charDataReceive1 , 6);
//		for(Local_u8Counter = 0; Local_u8Counter < 6; Local_u8Counter++)
//		{
//			if((Local_charDataReceive1[Local_u8Counter] == 'O') && (Local_charDataReceive1[Local_u8Counter+1] == 'K'))
//			{
//				Local_u8Event = 1;
//				break;
//			}
//		}
//
//		delay_us(10*1000);
//		//MSTK_voidSetBusyWait(10);
//	}
//
//	Local_u8Event = 0;
//
//	while(Local_u8Event == 0)
//	{
//		MUSART1_voidTransmit((u8*)Copy_u8ChannelID);
//		MUSART1_voidReceiveBuffer(Data , Buffer_Size);
//
//		for(Local_u8Counter = 0; Local_u8Counter < Buffer_Size; Local_u8Counter++)
//		{
//			if((Data[Local_u8Counter] == '@') || (Data[Local_u8Counter] == '#') )
//			{
//				Local_u8Event = 1;
//				break;
//			}
//		}
//		delay_us(500*1000);
//		//MSTK_voidSetBusyWait(500);
//	}
//}
