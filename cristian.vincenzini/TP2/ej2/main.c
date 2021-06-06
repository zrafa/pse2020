/* Pulsador que intercambia modos de operacion */

#include "utils.h"

unsigned char mode = 0;
extern unsigned char switch_up;

int main(void)
{
        leds_init();

        while (1) {
                switch_state();

                if (!switch_up) {
                        mode = !mode;
                        toggle_debug_led();
                        delay_ms(500);
                }

                if (mode) {
                        suma_binaria();
                } else {
                        leds_on();
                }

                delay_ms(1000);
        }
}
