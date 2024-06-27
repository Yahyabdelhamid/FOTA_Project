#include "STD_TYPES.h"
#include "RCC_INTERFACE.h"
#include "GPIO_INTERFACE.h"
#include "UART_INTERFACE.h"
#include "FPEC_interface.h"
#include "ESP_INTERFACE.h"

#define Buffer_Size     2000

typedef void (*Function_t)(void);
Function_t addr_to_call = 0;


void Func(void)
{
	#define SCB_VTOR *((volatile u32 *)0xE000ED08)
	/*Set the offset of the Vector Table Offset Address Of The Application In The Flash Memory*/
	SCB_VTOR = 0x08004000;
	/*Declare a Pointer To Function to the Start function of the application*/
	addr_to_call = *(Function_t*)(0x08004004);
	/*Execute the Start Function of the application using Software Function Call*/
	addr_to_call();
}



void Parser_voidParseRecord(u8* Copy_u8BufData);
volatile u8 EndFlag = 0;


char DataCome[Buffer_Size] = {0};

void send_rec(void){

	u8 Local_u8Event = 0;
	u16 Local_u16CounterStart = 0;
	u16 Local_u16Counter;
	u8  Local_u8CounterBuffer = 0;
	u8 u8RecBuffer[100] = {0};


	/* Reach to first : */
	SecondColumn:
	while(Local_u8Event == 0)
	{
		if(DataCome[Local_u16CounterStart] == ':')
		{
			Local_u8Event = 1;
		}
		Local_u16CounterStart++;
	}

	/* Start from index of second : */
	for(Local_u16Counter = Local_u16CounterStart; Local_u16Counter < Buffer_Size; Local_u16Counter++)
	{
		if(DataCome[Local_u16Counter] == '\r')
		{
			continue;
		}
		else if((DataCome[Local_u16Counter] == '\n') && (DataCome[Local_u16Counter+1] == '+'))
		{
			Local_u8Event = 0;
			Local_u16CounterStart = Local_u16Counter+1;
			goto SecondColumn;
		}
		else if(DataCome[Local_u16Counter] == '@')
		{
			break;
		}
		else if(DataCome[Local_u16Counter] == '#')
		{
			EndFlag = 1;
			break;
		}
		else
		{
			u8RecBuffer[Local_u8CounterBuffer] = DataCome[Local_u16Counter];
			if(u8RecBuffer[Local_u8CounterBuffer] == '\n')
			{
				u8RecBuffer[Local_u8CounterBuffer]   = '\r';
				u8RecBuffer[Local_u8CounterBuffer+1] = '\n';
				Local_u8CounterBuffer = 0;
				Parser_voidParseRecord(u8RecBuffer);
			}
			else
			{
				Local_u8CounterBuffer++;
			}
		}
	}
}






void main ( void ){

	/* Create Variable To Receive Data From Server */
	u8 status=0;

	RCC_voidInit();
	RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_GPIOAEN);
	RCC_voidEnablePeripheralClock(RCC_APB2, RCC_APB2_USART1EN);
	RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_FLITF);

	MUSART1_voidInit();

	MSTK_voidInit();

	/* Initialize USART BaudRate = 115200 */
	//MUSART1_voidInit();
	/* Setting ESP8266 Mode */
	ESP_voidInit();

    //MSTK_voidSetSingleInterval(10000000, &Func);

	/* Connecting To WIFI Network */
	ESP_voidConnectToWiFi((u8*)"yahya" , (u8*)"123456789");


	/* Connecting To overtheair.freevar.com to check if there is a new hex file to burn*/
	//ESP_voidConnectToSrvTcp( (u8 *)"128.204.223.70" , (u8 *)"80" );
	ESP_voidConnectToSrvTcp( (u8 *)"192.168.1.8" , (u8 *)"80" );
	//status = ESP_u8ReceiveHttpReq((u8*)"GET https://192.168.1.4/FOTA_WEB/mc_check.txt\r\n" , (u8*)"47");




	//status = ESP_u8ReceiveHttpReq((u8*)"GET https://yahya.serv00.net/status.txt\r\n" , (u8*)"41");
	status = ESP_u8ReceiveHttpReq((u8*)"GET http://192.168.1.8/ota_update/status.txt\r\n" , (u8*)"46");
	//status = ESP_u8ReceiveHttpReq((u8*)"GET http://192.168.1.7/ota_update/FOTA_WEB/mc_check.txt\r\n" , (u8*)"57");

	//status = ESP_u8ReceiveHttpReq((u8*)"GET http://192.168.1.7/upload_file/start_flash.php?config=ok\r\n" , (u8*)"62");

	if(status == '1')
	{
		//MSTK_voidSTKDisable();
		MFPEC_voidEraseAppArea();


		while(1)
		{
			ESP_voidConnectToSrvTcp( (u8 *)"192.168.1.8" , (u8 *)"80" );
			//ESP_voidConnectToSrvTcp( (u8 *)"192.168.1.7" , (u8 *)"80" );
			//ESP_voidConnectToSrvTcp( (u8 *)"192.168.1.4" , (u8 *)"8080" );
			ESP_voidSendOk( (u8 *)"GET http://192.168.1.8/ota_update/Reciver.php?Rx=ok\r\n" , (u8 *)"53" );
			//delay_us(100);
			ESP_voidConnectToSrvTcp( (u8 *)"192.168.1.8" , (u8 *)"80" );

			ESP_voidReceiveHttpReq( (u8 *)"GET http://192.168.1.8/ota_update/ota.php?config=ok\r\n" , (u8 *)"53",DataCome );
            asm("NOP");

			//ESP_voidConnectToSrvTcp( (u8 *)"192.168.1.7" , (u8 *)"80" );


			//ESP_voidSendOk( (u8 *)"GET https://yahya.serv00.net/FOTA_WEB/Reciver.php?Rx=ok\r\n" , (u8 *)"57" );
			//ESP_voidReceiveHttpReq( (u8 *)"GET http://192.168.1.7/ota_update/FOTA_WEB/record.txt\r\n" , (u8 *)"55" ,DataCome);
			//delay_us(100);
			//ESP_voidSendOk( (u8 *)"GET https://yahya.serv00.net/ota.php?config=ok\r\n" , (u8 *)"48" );
			//ESP_voidConnectToSrvTcp( (u8 *)"192.168.1.7" , (u8 *)"80" );

			//ESP_voidReceiveHttpReq( (u8 *)"GET https://yahya.serv00.net/ota.php?config=none\r\n" , (u8 *)"50" , DataCome);
			//ESP_voidReceiveHttpReq( (u8 *)"GET http://192.168.1.7/upload_file/start_flash.php?config=none\r\n" , (u8 *)"64" , DataCome);

			send_rec();

			if(EndFlag == 1)
			{
				break;
			}
		}
	}

	/*    Jump to the application "Entry Point"      */
	Func();
}
















