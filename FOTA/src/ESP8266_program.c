/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/



#include "UART_interface.h"

#include "ESP8266_INTERFACE.h"



int volatile Iterator = 0  ;

u8 volatile result =0;
extern volatile u8 DataCome[100] ;
extern volatile u8 Data_Pure[100] ;


void ValidateCommand( void )
{   asm("NOP");
	while(result ==0){
	for(u8 i=0;i<Iterator;i++){
		if ((DataCome[i] == 'O' && DataCome[(i+1)] == 'K')||(DataCome[i] == 'A' && DataCome[(i+1)] == 'T'))
	        {
	        	result = 1;
	        }
	}
	}
}


void MUSART_CallBack ( void ){

	/* Receive ESP8266 Response */
	DataCome[ Iterator ] = MUSART1_u8ReadDataRegister();
	/* ------------------ */
	Iterator++;
	asm("NOP");


	MUSART1_VidClearFlags();

}

void ESP8266_VidInit ( void ){

	/* Set USART1 CallBack To Receive The Response Of The ESP8266 */
	MUSART1_VidSetCallBack( MUSART_CallBack );

	/* Sending AT Command To Check ESP8266 Is Working Or Not  */
	MUSART1_voidSendStringSynchronous( (u8 *)"AAT\r\n" );
	//MSTK_voidSetBusyWait(1000);

    ValidateCommand();
    //MSTK_voidSetBusyWait(1000);
	/* Clear ESP8266 Buffer */
	ESP8266_VidClearBuffer();

	MUSART1_voidSendStringSynchronous( (u8 *)"AT+CWMODE=3\r\n" );
	MSTK_voidSetBusyWait(1000);

	ValidateCommand();

	ESP8266_VidClearBuffer();

	MUSART1_voidSendStringSynchronous( (u8 *)"AT+CIPMODE=0\r\n" );
	ValidateCommand();

}

void ESP8266_VidConnectToWiFi ( u8 * SSID , u8 * Password ){

	ESP8266_VidClearBuffer();

	MUSART1_voidSendStringSynchronous( (u8 *) "AT+CWJAP=\"" );
	MUSART1_voidSendStringSynchronous( (u8 *) SSID );
	MUSART1_voidSendStringSynchronous( (u8 *) "\",\"" );
	MUSART1_voidSendStringSynchronous( (u8 *) Password);
	MUSART1_voidSendStringSynchronous( (u8 *) "\"\r\n");
	ValidateCommand();

}


void ESP8266_VidConnectToSrvTcp ( u8 * Copy_u8Domain , u8 * Copy_u8Port ){

	ESP8266_VidClearBuffer();

	MUSART1_voidSendStringSynchronous( (u8 *) "AT+CIPSTART=\"TCP\",\"" );
	MUSART1_voidSendStringSynchronous( (u8 *) Copy_u8Domain );
	MUSART1_voidSendStringSynchronous( (u8 *) "\"," );
	MUSART1_voidSendStringSynchronous( (u8 *) Copy_u8Port );
	MUSART1_voidSendStringSynchronous( (u8 *) "\r\n" );
	MSTK_voidSetBusyWait( 2000000 );

}

void ESP8266_VidSendHttpReq( u8 * Copy_u8Key , u8 * Copy_u8Data , u8 * Copy_u8Length ){

	ESP8266_VidClearBuffer();

	MUSART1_voidSendStringSynchronous( (u8 *) "AT+CIPSEND=" );
	MUSART1_voidSendStringSynchronous( (u8 *) Copy_u8Length );
	MUSART1_voidSendStringSynchronous( (u8 *) "\r\n" );
	MSTK_voidSetBusyWait( 1000000 );

	ESP8266_VidClearBuffer();

	MUSART1_voidSendStringSynchronoush( (u8 *) "GET /update?api_key=" );
	MUSART1_voidSendStringSynchronous( (u8 *) Copy_u8Key );
	MUSART1_voidSendStringSynchronous( (u8 *) "&field1=" );
	MUSART1_voidSendStringSynchronous( (u8 *) Copy_u8Data );
	MUSART1_voidSendStringSynchronous( (u8 *) "\r\n" );
	MSTK_voidSetBusyWait( 2000000);

}

u8   ESP8266_u8ReceiveHttpReq( u8 * Copy_u8ChannelID , u8 * Copy_u8Length ){

	ESP8266_VidClearBuffer();

	MUSART1_voidSendStringSynchronous( (u8 *) "AT+CIPSEND=" );
	MUSART1_voidSendStringSynchronous( (u8 *) Copy_u8Length );
	MUSART1_voidSendStringSynchronous( (u8 *) "\r\n" );
	MSTK_voidSetBusyWait( 2000000 );

	ESP8266_VidClearBuffer();


	MUSART1_voidSendStringSynchronous( (u8 *) Copy_u8ChannelID );

	MSTK_voidSetBusyWait( 1000000 );

	//ESP8266_VidConnectToSrvTcp( (u8 *)"69.197.143.14" , (u8 *)"80" );

	/*For yrabiot3.freevar.com ( Value Array Index )*/

	return  DataCome[82] ;

}

void ESP8266_VidClearBuffer ( void ){

	int LOC_u8Iterator1 = 0 ;
	Iterator     = 0 ;
	result       = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 1900 ; LOC_u8Iterator1++ ){

    DataCome[ LOC_u8Iterator1 ] = 0 ;
    Data_Pure[ LOC_u8Iterator1 ] = 0 ;


	}

}
