/* Pulsador que intercambia modos de operacion */

#include "utils.h"

unsigned char mode = 0;
unsigned char state, old_state;

int main(void)
{
        leds_init();

        while (1) {
                state = switch_state();

                if (state && !old_state) {
                        mode = !mode;
                        toggle_debug_led();  /* visually show mode */
                        delay_ms(500);
                }

                old_state = state;

                if (mode) {
                        suma_binaria();
                } else {
                        leds_on();
                }

                delay_ms(1000);
        }
}
