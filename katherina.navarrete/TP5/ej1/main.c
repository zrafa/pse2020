#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "utils.h"


int main(void)
{

	/* las interrupciones están deshabilitadas */

        /* leds_init();	en utils.c */
	lets_init();
	timer0_init();
	/* habilitar las interrupciones */
	cli();
	int ticks_nuevo = cant_ticks();
	sei();
	int ticks_ant = -1;
        while (1) {

		/* si pasó un segundo entonces toggle_led(); */
		if ( (ticks_ant != ticks_nuevo) & ticks_nuevo == 0) {
		
			toggle_leds();
			
		}
		ticks_ant = ticks_nuevo;
		cli();
		ticks_nuevo = cant_ticks();
		sei();
        }
}
