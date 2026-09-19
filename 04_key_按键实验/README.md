- # 项目名称

  使用 STM32F103C8T6 实现 按键控制led灯。

  ## 一、实验目标

  - 学习 STM32 GPIO 的基本使用
  - 掌握 GPIO 输出模式配置
  - 实现按键控制LED灯的亮暗

  ## 二、开发环境

  - MCU：STM32F103C8T6
  - IDE：Keil MDK
  - 固件库：STM32 HAL Library
  - 编程语言：C

  ## 三、硬件连接

  - KEY1：PA0；
  - KEY2：PA1；
  
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

int main(void)
{
    uint8_t key;

    HAL_Init();
    stm32_clock_init(RCC_PLL_MUL9);

    led_init();
    key_init();

    while(1)
    {
        key = key_scan();

        if(key == 1)
        {
            led1_toggle();
        }
        else if(key == 2)
        {
            led2_toggle();
        }
    }
}

  ```

  ### 2. led.c

  ```c
#include "led.h"
#include "sys.h"

//初始化GPIO函数
void led_init(void)
{
	GPIO_InitTypeDef gpio_initstruct;
	//打开时钟
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	//调用GPIO的初始化函数
	gpio_initstruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	gpio_initstruct.Pull = GPIO_PULLUP;
	gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB,&gpio_initstruct);
	
	//关闭LED
	led1_off();
	led2_off();
}

//点亮LED1的函数
void led1_on(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
}

//点亮LED2的函数
void led2_on(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET);
}

//熄灭LED1的函数
void led1_off(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);
}

//熄灭LED2的函数
void led2_off(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET);
}

//翻转LED1的函数
void led1_toggle(void)
{
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_8);
}

//翻转LED2的函数
void led2_toggle(void)
{
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_9);
}
  ```

  ### 3. led.h

  ```
#ifndef __LED_H__
#define __LED_H__
	void led_init(void);
	void led1_on(void);
	void led1_off(void);
	void led1_toggle(void);
	void led2_on(void);
	void led2_off(void);
	void led2_toggle(void);
#endif
  ```

### 4.key.c

读取引脚电平状态判断按键有没有按下（即按键引脚状态是不是低电平，因为初始化的时候设置的是上拉电阻，上拉输入+按键接地）

按键按下之后要消抖，delay_ms(10);

消抖之后继续判断按键状态，用while循环等待按键松开，然后返回按键的值，如果是按键1按下则返回1，如果是按键2按下则返回2；

每次扫描函数都要判断一下是1按下去了还是2按下去了；

```
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
```

### 5.key.h

因为key_scan(void)，是一个有返回值的函数，所以要在前面包含头文件#include "sys.h"

```
#ifndef __KEY_H__
#define __KEY_H__

#include "sys.h"
	void key_init(void);
	uint8_t  key_scan(void);
	
#endif

```

  ## 七、学习总结

  本实验学习了如何用按键控制Led灯的亮暗，要注意按键要消抖；其实这个实验原理还是很简单的，就是通过读取按键状态，返回相应的值，通过这个值来控制LED是亮还是暗，这里可以用翻转函数，当读到有按键输入的时候，可以通过翻转函数来控制LED电平的翻转，那么LED亮暗状态也就翻转了；

  ## 八、文件说明

  ```text
05_key/
  ├── README.md
├── main.c
	├── key.c
	├── key.h
	├── led.c
	└── led.h
	
  ```

  - `main.c`：主程序
- `key.c`：按键驱动程序
- `key.h`：按键相关宏定义和函数声明
- `led.c`：LED驱动程序
- `led.h`：LED相关宏定义和函数声明

