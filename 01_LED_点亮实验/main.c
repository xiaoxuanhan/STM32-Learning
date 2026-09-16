#include "sys.h"
#include "delay.h"
#include "led.h"

int main(void)
{
    HAL_Init();                         /* ³õÊ¼»¯HAL¿â */
    stm32_clock_init(RCC_PLL_MUL9); /* ÉèÖÃÊ±ÖÓ, 72Mhz */
		led_init();
	
    while(1)
    { 
				led1_on();
				delay_ms(500);
				led1_off();
				delay_ms(500);
    }
}
