#include "stm32f10x.h"                  // Device header
#include "Delay.h"


void key_init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

uint16_t get_KeyNum(void)
{	
	
	
	uint16_t keyStatus = 0;
	
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0){ // 读取按键1
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0);
		Delay_ms(20);
		keyStatus = 1;
	}
		
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0){ // 读取按键1
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0);
		Delay_ms(20);
		keyStatus = 2;
	}
	return keyStatus;
}

