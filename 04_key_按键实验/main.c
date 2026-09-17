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
