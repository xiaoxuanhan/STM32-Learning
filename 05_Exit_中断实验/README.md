- # 项目名称

  使用 STM32F103C8T6 实现 中断控制led灯。

  ## 一、实验目标

  - 学习 STM32 GPIO 的基本使用
  - 掌握 GPIO 输出模式配置
  - 实现中断控制LED灯

  ## 二、开发环境

  - MCU：STM32F103C8T6
  - IDE：Keil MDK
  - 固件库：STM32 HAL Library
  - 编程语言：C

  ## 三、硬件连接

  ## 四、知识点介绍

  按键抖动：在按键开关被按下或者释放的瞬间，开关状态不稳定， 会出现短暂的抖动状态；解决办法就是软件消抖和硬件消抖，但是我们平常实验对精度要求不高，可以采用软件消抖，软件消抖就是跳过抖动的时间段，再判断I/o端口的状态；可以用delay()函数；

    ## 五、程序设计思路

    程序执行流程：

1. 初始化 HAL 库
  2. 配置系统时钟
  3. 初始化对应 GPIO
  4. 设置 GPIO 输出状态
  5. 进入主循环

  ## 六、核心代码

  ### 1. main.c

  ```c
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "exti.h"

int main(void)
{
    uint8_t key;

    HAL_Init();
    stm32_clock_init(RCC_PLL_MUL9);

    led_init();
		exti_init();
    while(1)
    {
      led2_off();
			delay_ms (500);
			led2_on ();
			delay_ms (500);
        
    }
}
  ```

  ### 2. exit.c

  ```c
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
  ```

  ### 3. exit.h

  ```
#ifndef __EXTI_H__
#define __EXTI_H__
void exti_init(void);
#endif
  ```

  ## 七、学习总结

  本实验学习了什么是中断，怎么去调用中断函数；一开始设置GPIO口的时候就可以设置成上升沿触发中断或者下降沿出发中断，触发了中断之后就会调用中断服务函数，中断服务函数里面有HAl库的函数，HAL库函数处理完中断之后会自动调用中断回调函数；
