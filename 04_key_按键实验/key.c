#include"key.h"
#include"sys.h"
#include"delay.h"

//初始化GPIO口
void key_init(void)
{
		GPIO_InitTypeDef gpio_initstruct;
	//打开时钟
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	//调用GPIO的初始化函数
	gpio_initstruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	gpio_initstruct.Pull = GPIO_PULLUP;
	gpio_initstruct.Mode = GPIO_MODE_INPUT;
	gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA,&gpio_initstruct);
}
//按键扫描函数
uint8_t  key_scan(void)
{
	//检测按键是不是已经按下
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_RESET)
	{
		//消抖
			delay_ms(10);
		//判断按键是不是已经按下
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_RESET)
		{
		//如果确实是按下的状态，等待按键松开
			while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_RESET);
		//返回按键的值
			return 1;
		}
		//返回默认值
	}
	//检测按键是不是已经按下
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) == GPIO_PIN_RESET)
	{
		//消抖
			delay_ms(10);
		//判断按键是不是已经按下
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) == GPIO_PIN_RESET)
		{
		//如果确实是按下的状态，等待按键松开
			while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) == GPIO_PIN_RESET);
		//返回按键的值
			return 2;
		}
		//返回默认值
	}
	return 0;
}
