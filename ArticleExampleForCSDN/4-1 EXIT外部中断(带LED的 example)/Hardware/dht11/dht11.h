#ifndef _dht11_H
#define _dht11_H

#include "system.h"
//#include "SysTick.h"
#include "Delay.h"


void dht11_pin_mode(GPIOMode_TypeDef pin_mode);
void dht11_init(void);
int32_t dht11_start(void);
uint8_t dht11_read_byte(void);
int32_t dht11_read_data(uint8_t *pbuf);

#endif
