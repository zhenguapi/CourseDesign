#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "LED.h"
#include "string.h"
#include "dht11.H"
#include "ESP8266.H"
#include <stdio.h>

int main(void)
{
	OLED_Init();
	Serial_Init();
	
	LED_init();
	dht11_init();
	
	esp8266_Config();
	
	int32_t rt=0;	// 相当于状态值flag
	uint8_t dht11_data[5]={0};  // 用于接收数据的数组
	
	OLED_ShowString(1,1, "esp finished");
	
	esp8266_Subscribe("HttpSend");
	
	while (1)
	{
		/*
		if (Serial_RxFlag == 1)
		{
			OLED_ShowString(4, 1, "                ");
			OLED_ShowString(4, 1, Serial_RxPacket);
			
			if (strcmp(Serial_RxPacket, "LED_ON") == 0)
			{
				set_LED(1);
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "LED_ON_OK");
			}
			else if (strcmp(Serial_RxPacket, "LED_OFF") == 0)
			{
				reset_LED(1);
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "LED_OFF_OK");
			}
			else
			{
				Serial_SendString("ERROR_COMMAND\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "ERROR_COMMAND");
			}
			
			Serial_RxFlag = 0;
			
		}
		*/
		
		
		
		rt = dht11_read_data(dht11_data);
		
		if(rt == 0)
		{
			
			OLED_ShowString(2,1, "temp:");
			OLED_ShowNum(2,7,dht11_data[2], 2);
			OLED_ShowString(2,9, ".");
			OLED_ShowNum(2,10,dht11_data[3], 1);
			
			OLED_ShowString(3,1, "humid: ");
			OLED_ShowNum(3,7,dht11_data[0], 2);
			OLED_ShowString(3,9, ".");
			OLED_ShowNum(3,10,dht11_data[1], 1);
			
			
			char Json[100];

//			sprintf(Json, "{\\\"Temperature\\\":\\\"%2d.%d\\\",\\\"Humidity\\\":\\\"%2d.%d\\\"}", dht11_data[2], dht11_data[3], dht11_data[0], dht11_data[1]);
			sprintf(Json, "%2d.%d-%2d.%d", dht11_data[2], dht11_data[3], dht11_data[0], dht11_data[1]);
			
			esp8266_Send(Json);
			OLED_ShowString(1,1, "              ");
			OLED_ShowString(1,1, "send OK");
			

			if (Serial_RxFlag == 1)
			{
				OLED_ShowString(4, 1, "                ");
				
				char *token = strtok(Serial_RxPacket, ",");
				uint8_t count = 1;
				while (token != NULL) {
					count+=1;
					if (count > 4) {
						break;
					}
					token = strtok(NULL, ",");
				}
				if (strcmp(token, "LED_ON") == 0)
				{
					set_LED(1);
					OLED_ShowString(4, 1, "                ");
					OLED_ShowString(4, 1, "LED_ON");
				}
				if (strcmp(token, "LED_OFF") == 0)
				{
					reset_LED(1);
					OLED_ShowString(4, 1, "                ");
					OLED_ShowString(4, 1, "LED_OFF");
				}
				
				Serial_RxFlag = 0;
				
			}
			
			
		}
		else
		{
			OLED_ShowString(2,1, "dht11 error");
			OLED_ShowNum(3,1, rt,5);
			
		}
		
		Delay_ms(1000);
		
	}
}
