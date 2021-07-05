/* Pulsador que intercambia modos de operacion */

#include "utils.h"
#include <avr/interrupt.h>

unsigned char mode = 0;

int main(void)
{
        leds_init();
        sei();

        while (1) {
                if (mode) {
                        suma_binaria();
                } else {
                        leds_on();
                }

                delay_ms(1000);
        }
}

ISR(PCINT0_vect)
{
        mode = !mode;

        if (mode) {
                debug_led_on();
        } else {
                debug_led_off();
        }
}
