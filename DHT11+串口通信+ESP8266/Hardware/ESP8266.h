#ifndef __ESP8266_H
#define __ESP8266_H

#include <stdint.h>
#include "Serial.h"
#include "Delay.h"
#include <String.h>
#include <stdio.h>


void esp8266_Config(void);
void esp8266_Send(char* data);
void esp8266_Send_cmd(void);
void esp8266_Subscribe(char* topic);
void esp8266_quit(void);

// 函数

//u8 esp8266_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
//u8* esp8266_send_data(u8 *cmd,u16 waittime);
//u8* esp8266_check_cmd(u8 *str);
//void esp8266_start_trans(void);
//u8 esp8266_quit_trans(void);

#endif
