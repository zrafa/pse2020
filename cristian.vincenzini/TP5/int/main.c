#include <avr/interrupt.h>
#include <stdio.h>

#include "utils.h"

int main(void)
{
        leds_init();
        sei();

        for(;;);
}

ISR(PCINT0_vect)
{
        led_toggle();
}
