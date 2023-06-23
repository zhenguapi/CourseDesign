#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "dht11.h"


int main(void)	
{
	
	OLED_Init();
	
	dht11_init();
	
	int32_t rt=0;
	uint8_t dht11_data[5]={0};  
	
	OLED_ShowString(1,1, "Hello LED");
	
	while(1){
		
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
			
		}
		
	}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
}

