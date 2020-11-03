#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "utils.h"


int main(void)
{

	/* las interrupciones están deshabilitadas */

        /* leds_init();	en utils.c */
	leds_init();

	/* habilitar las interrupciones */
	timer0_init();

	cli();
	int ticks_actual = get_ticks();
	int ticks_anterior = ticks_actual-1;
	sei();
        while (1) {
		/* si pasó un segundo entonces toggle_led(); */
		if((ticks_actual != ticks_anterior) & ticks_actual == 0) {	
			led_toggle();
		}
		cli();
		ticks_anterior = ticks_actual;
		ticks_actual = get_ticks();
		sei();
        }
}
