#include "dht11.h"


//DHT11初始化 
//GPIO初始化的结构体
static GPIO_InitTypeDef  GPIO_InitStructure;
//USART初始化的结构体
static USART_InitTypeDef USART_InitStructure;
//NVIC初始化的结构体
static NVIC_InitTypeDef   NVIC_InitStructure;

// System.h宏 所需的引脚参数 (0~15)
uint16_t PIN_NUM = 1;
// 初始化的引脚
#define  GPIO_PIN_NUM GPIO_Pin_1

void dht11_pin_mode(GPIOMode_TypeDef pin_mode)
{
	if(pin_mode == GPIO_Mode_Out_PP)
	{
		/* 配置GPIO为输出模式，让这根引脚具有输出高低电平的功能 */
		GPIO_InitStructure.GPIO_Pin = GPIO_PIN_NUM;				//指定引脚
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			//输出模式
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//引脚的速度最大为100MHz

	
	}
	else
	{
		/* 配置GPIO为输入模式 */
		GPIO_InitStructure.GPIO_Pin = GPIO_PIN_NUM;				//指定引脚
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//输入模式
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//引脚的速度最大为100MHz
	
	}


	GPIO_Init(GPIOA, &GPIO_InitStructure);	

}


void dht11_init(void)
{

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
		
	dht11_pin_mode(GPIO_Mode_Out_PP);

	
	//默认初始化完毕后，时序图告诉我们，引脚为高电平
	PAout(PIN_NUM)=1;

}

int32_t dht11_start(void)
{
	uint32_t t=0;
	
	u8 retry=0;
	
	//配置引脚为输出模式
	dht11_pin_mode(GPIO_Mode_Out_PP);
	
	//发送开始信号
	PAout(PIN_NUM)=0;
	
	
	//延时至少18ms
	Delay_ms(18);
	
	//拉高
	PAout(PIN_NUM)=1;	
	
	Delay_us(30);
	
	//配置引脚为输入模式
	dht11_pin_mode(GPIO_Mode_IPD);
	
	
	
	
	
	//等待dht11拉低引脚
	t=0;
	while(!PAin(PIN_NUM))
	{
		
		
		
		t++;
		Delay_us(1);

	}
	if (t>100 || t<20) //判断响应时间
    {
        __set_PRIMASK(0);       //开总中断
        return 0;
    }
	
	
	t = 0;
    while (PAin(PIN_NUM))            //等待DHT11释放总线，持续时间40~80us
    {
        t++;               //总线拉高时计数
        Delay_us(1);
    }
    __set_PRIMASK(0);          //开总中断
    if (t>100 || t<20) //检测响应信号之后的高电平
    {
        return 0;
    }
    return 1;
	
	
	



}

uint8_t dht11_read_byte(void)
{
	uint32_t i=0;
	
	uint8_t d=0;
	
	for(i=0; i<8; i++)
	{
		//等待低电平持续完毕
		while(PAin(PIN_NUM)==0);
		
		//延时40us
		Delay_us(40);
		
		
		//判断当前引脚电平的状态，判断出是数据0和数据1
		if(PAin(PIN_NUM))
		{
			//由于传输的数据是高位先出，因此将数据保存到高位
			d|=1<<(7-i);
			
			//等待高电平持续完毕
			while(PAin(PIN_NUM));
		
		}
	}


	return d;
}

int32_t dht11_read_data(uint8_t *pbuf)
{
	int32_t rt=-1;
	
	uint32_t i=0;
	
	uint8_t check_sum=0;
	
	//发送开始信号，并检查dht11是否有响应
	rt = dht11_start();
	
	
	if(rt < 0)
		return rt;
	
	//读取5个字节
	for(i=0 ; i<5; i++)
	{
		pbuf[i]=dht11_read_byte();

	}
		
	
	
	//判断所得到的温度和数据是否是正确
	
	//计算校验和
	check_sum = pbuf[0]+pbuf[1]+pbuf[2]+pbuf[3];
	
	if(check_sum != pbuf[4])
		return -4;

	//忽略结束信号
	Delay_us(100);
	
	
	return 0;
}






