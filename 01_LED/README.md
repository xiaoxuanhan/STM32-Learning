# 项目名称

使用 STM32F103C8T6 实现 GPIO 控制 LED 点亮。

## 一、实验目标

- 学习 STM32 GPIO 的基本使用
- 掌握 GPIO 输出模式配置
- 实现 LED 点亮和熄灭控制

## 二、开发环境

- MCU：STM32F103C8T6
- IDE：Keil MDK
- 固件库：STM32 HAL Library
- 编程语言：C

## 三、硬件连接

- LED1：PA0
- LED2：PA1

## 四、知识点介绍

输入部分：
浮空输入-->I/O电平状态不确定，完全由外部输入决定；（上拉下拉电阻都不工作）
上拉输入-->I/O口在无输入的情况下，保持高电平；
下拉输入-->I/O口在无输入的情况下，保持低电平；
模拟输入-->输入量为模拟量；

输出部分：
开漏输出-->只输出低电平；
推挽输出-->可以输出高电平和低电平；
(复用功能就是GPIO不再由普通GPIO寄存器控制，而是由外设控制)
复用推挽输出-->外设控制推挽输出
复用开漏输出-->外设控制开漏输出

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

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
	led_init();
	
    while(1)
    { 
		led1_on();
		delay_ms(500);
		led1_off();
		delay_ms(500);
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

```

### 3. led.h

```
#ifndef __LED_H__
#define __LED_H__
	void led_init(void);
	void led1_on(void);
	void led1_off(void);
	void led1_toggle(void);
#endif

```

## 七、学习总结

通过本实验学习了：

- STM32 GPIO 初始化方法
- 推挽输出模式
- GPIO 高低电平控制
- LED 的基本控制方法

## 八、文件说明

```text
01_LED/
├── README.md
├── main.c
├── led.c
└── led.h
```

- `main.c`：主程序
- `led.c`：LED 驱动程序
- `led.h`：LED 相关宏定义和函数声明
