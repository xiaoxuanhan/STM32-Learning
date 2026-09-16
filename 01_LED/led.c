#include "led.h"
#include "sys.h"

//初始化GPIO函数
void led_init(void)
{
	GPIO_InitTypeDef gpio_initstruct;
	//打开时钟
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	//调用GPIO的初始化函数
	gpio_initstruct.Pin = GPIO_PIN_8;//8号引脚
	gpio_initstruct.Pull = GPIO_PULLUP;//上拉电阻
	gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;//推挽输出，既可以输出高电平也可以输出低电平；
	gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB,&gpio_initstruct);
	
	//关闭LED
	led1_off();
}

//点亮LED1的函数
void led1_on(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);//写入一个低电平
}

//熄灭LED1的函数
void led1_off(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);//写入一个高电平
}

//翻转LED1的函数
void led1_toggle(void)
{
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_8);
}
