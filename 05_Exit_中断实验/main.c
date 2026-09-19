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
