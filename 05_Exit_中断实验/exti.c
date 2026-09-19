#include "exti.h"
#include "sys.h"
#include "delay.h"
#include "led.h"

void exti_init(void)
{
	GPIO_InitTypeDef gpio_initstruct;
	//打开时钟
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	//调用GPIO的初始化函数
	gpio_initstruct.Pin = GPIO_PIN_0;
	gpio_initstruct.Pull = GPIO_PULLUP;
	gpio_initstruct.Mode = GPIO_MODE_IT_FALLING;//下降沿触发中断函数
	HAL_GPIO_Init(GPIOA,&gpio_initstruct);
	HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	
}
void EXTI0_IRQHandler(void) //中断服务函数，当中断产生的时候，CPU自动寻找这个函数
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);//HAL处理完这个之后会自动调用HAL_GPIO_EXTI_Callback
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	delay_ms(20);
	if (GPIO_Pin == GPIO_PIN_0)
	{
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_RESET)
		{
			led1_toggle();
		}
	}
}