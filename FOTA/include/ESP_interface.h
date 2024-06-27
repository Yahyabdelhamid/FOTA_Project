#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H

void ESP_voidInit(void);
void ESP_voidConnectToWiFi(u8 *Copy_name , u8 *Copy_pass);
void ESP_voidConnectToSrvTcp (u8 *Copy_u8Domain , u8 *Copy_u8Port);
u8   ESP_u8ReceiveHttpReq(u8 *Copy_u8ChannelID , u8 *Copy_u8Length);
void ESP_voidSendOk(u8 * Copy_u8ChannelID , u8 * Copy_u8Length);
void ESP_voidReceiveHttpReq(u8 * Copy_u8ChannelID , u8 * Copy_u8Length , char* Data);

#endif
