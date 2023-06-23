#include "ESP8266.H"

/** 
  * @brief	初始化-主要用于连接本地服务以及订阅主题
  * @param	
  * @retval	
  */
void esp8266_Config(void){
	
	/*
	* 1.AT+CWMODE=1 :设置模组为STA模式。（串口助手）
	* 2.AT+CWLAP :查询附近WIFI（串口助手）
	* 3.AT+CWJAP="123123","12345678" :连接?WIFI（串口助手）
	* 4.AT+CIFSR :查看路由器分配给模组的IP地址,例如192.168.43.104（串口助手）
	* 5.AT+CIPMUX=1 :打开多连接（串口助手）
	* 6.AT+CIPSERVER=1,8800 :设置模块服务器端口（串口助手）
	*/
	Delay_s(2);
	Serial_Printf("AT+RST\r\n");
	Delay_s(6);
	Serial_Printf("AT+CWMODE=1\r\n");
	Delay_s(2);
	Serial_Printf("AT+CWJAP=\"mired\",\"11111111\"\r\n");
	Delay_s(3);
	Serial_Printf("AT+MQTTUSERCFG=0,1,\"esp_test\",\"admin\",\"public\",0,0,\"\"\r\n");
	Delay_s(2);
	Serial_Printf("AT+MQTTCONN=0,\"192.168.43.128\",1883,0\r\n");
	Delay_s(4);

//	Serial_Printf("AT+CIPSERVER=1,8800\r\n");
//	Delay_s(5);
//	Serial_Printf("AT+CIPSEND\r\n");
//	Delay_s(5);

}

/** 
  * @brief	作为 publisher 推送 一条消息
  * @param	
  * @retval	
  */
void esp8266_Send(char* data){
	
//	char end[] = ",0,0\r\n";
//	char tempb[100] = "AT+MQTTPUB=0,\"esp_send\",";
	char temp[100];
	
	sprintf(temp, "AT+MQTTPUB=0,\"esp_send\",\"%s\",0,0\r\n", data);
	
//	strcat(tempb, data);
//	strcat(tempb, end);
	
	Serial_Printf(temp);
	Delay_ms(100);
	
}

/** 
  * @brief	发送命令的基本方法
  * @param	
  * @retval	
  */
void esp8266_Send_cmd(void){
	Delay_s(2);
	Serial_Printf("AT+RST\r\n");
	Delay_s(6);
	Serial_Printf("AT+CWMODE=1\r\n");
}

/** 
  * @brief	订阅指定主题
  * @param	
  * @retval	
  */
void esp8266_Subscribe(char* topic){
	
	char temp[100];
	
	sprintf(temp, "AT+MQTTSUB=0,\"%s\",0\r\n", topic);
	
	Serial_Printf(temp);
//	Delay_s(2);
}

/** 
  * @brief	退出透传模式? 应该用 AT+MQTTCLEAN 断开 MQTT 连接，释放资源
  * @param	
  * @retval	
  */
void esp8266_quit(void){
	Serial_Printf("AT+MQTTCLEAN=0\r\n");
	Delay_s(2);
}

