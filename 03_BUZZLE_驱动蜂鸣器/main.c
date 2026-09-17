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