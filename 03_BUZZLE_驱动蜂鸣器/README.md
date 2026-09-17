- # 项目名称

  使用 STM32F103C8T6 实现 GPIO控制蜂鸣器。

  ## 一、实验目标

  - 学习 STM32 GPIO 的基本使用
  - 掌握 GPIO 输出模式配置
  - 实现蜂鸣器的打开OR关闭

  ## 二、开发环境

  - MCU：STM32F103C8T6
  - IDE：Keil MDK
  - 固件库：STM32 HAL Library
  - 编程语言：C

  ## 三、硬件连接

  - 蜂鸣器：PA0
  
## 四、知识点介绍

蜂鸣器分为有源蜂鸣器和无源蜂鸣器；两者的区别在于有源蜂鸣器内部自带震荡源，只要通电就会发声；无源蜂鸣器内部没有震荡电路，需要自己给他一个方波；

有源：给电就叫 ；

```
beep_on();
delay_ms(500);
```

无源：给节奏才叫；一直输出高电平是不会叫的，需要不断转换高低电平；

```
while(1)
{
    beep_on();
    delay_ms(250);
    beep_off();
    delay_ms(250);
 }
```

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
#include "beep.h"

int main(void)
{
    uint16_t i;

    HAL_Init();
    stm32_clock_init(RCC_PLL_MUL9);
    beep_init();

    while(1)
    {
        for(i = 0; i < 1000; i++)
        {
            beep_on();
            delay_us(250);

            beep_off();
            delay_us(250);
        }

        beep_off();
        delay_ms(500);
    }
}
  ```

  ### 2. led.c

  ```c
#include "beep.h"
#include "sys.h"

//初始化GPIO函数
void beep_init(void)
{
	GPIO_InitTypeDef gpio_initstruct;
	//打开时钟
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	//调用GPIO的初始化函数
	gpio_initstruct.Pin = GPIO_PIN_8;
	gpio_initstruct.Pull = GPIO_PULLUP;
	gpio_initstruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_initstruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB,&gpio_initstruct);
	
	//关闭蜂鸣器
	beep_off();
}

//打开蜂鸣器的函数
void beep_on(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
}

//关闭蜂鸣器的函数
void beep_off(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);
}

  ```

  ### 3. led.h

  ```
#ifndef __BEEP_H__
#define __BEEP_H__
	void beep_init(void);
	void beep_on(void);
	void beep_off(void);
#endif
  ```

  ## 七、学习总结

  本实验学习了如何驱动蜂鸣器，蜂鸣器分为有源和无源两种，两种蜂鸣器由于硬件不用，驱动方法也不同，有源的可以直接用高电平驱动，但是无源的需要用高低电平转换来驱动；  无源的根据频率的不同可以发出不同的声音，可以做一个电子琴键？

  ## 八、文件说明

  ```text
01_LED/
  ├── README.md
├── main.c
	├── beep.c
	└── beep.h
  ```

  - `main.c`：主程序
- `beep.c`：蜂鸣器驱动程序
- `beep.h`：蜂鸣器相关宏定义和函数声明

