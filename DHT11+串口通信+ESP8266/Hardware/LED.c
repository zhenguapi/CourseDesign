#include "stm32f10x.h"                  // Device header

void LED_init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);
	
}

void set_LED(uint8_t LEDx){
	if(LEDx == 1){
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	} else if(LEDx == 2){
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	}
}

void reset_LED(uint8_t LEDx){
	if(LEDx == 1){
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
	} else if(LEDx == 2){
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
	}
}

void toggle_LED(uint8_t LEDx){
	uint16_t pin;
	if(LEDx==1)
		pin=GPIO_Pin_14;
	else if(LEDx == 2)
		pin=GPIO_Pin_15;
	
	if(GPIO_ReadInputDataBit(GPIOB, pin) == 0){
		GPIO_SetBits(GPIOB, pin);
	}else {
		GPIO_ResetBits(GPIOB, pin);
	}
	
}
