#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "utils.h"


int main(void)
{
        led_init();
        timer0_init();

        /* seccion critica */
        cli();
        int ticks = cant_ticks();
        int flag  = -1;
        sei();

        while (1) {

                /* si paso un segundo entonces toggle_led(); */
                if ((flag != ticks) & ticks == 0) {
                        led_toggle();
                }

                /* la variable flag soluciona el problema de sincronismo:
                 * antes que se produzca una interrupcion el while se ejecuto varias veces
                 * flag impone una espera en el bucle
                 * */
                
                cli();
                flag  = ticks;
                ticks = cant_ticks();
                sei();
        }
}
