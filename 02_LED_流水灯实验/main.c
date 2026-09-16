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
			led2_off();
			delay_ms(500);
			led2_on();
			led1_off();
			delay_ms(500);
    }
}
