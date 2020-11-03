#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "utils.h"
#include "tasks.h"
#include "serial.h"

char buffer[23];

void enviar_hora()
{
	
	cli();
	timer0_rtc_to_str(buffer); 		 
	serial_put_String(buffer);
	sei();
	serial_put_String("\r\n");
}

int main(void)
{
        timer0_init();
        leds_init();
	serial_init();
	tasks_init();
	
	timer0_rtc_set(2020, 10, 29, 19, 34, 0);
	
	/* definimos una tarea periódica a 300ms */
	tasks_def(300, toggle13);
	tasks_def(200, toggle12);
	tasks_def(1000, enviar_hora);
	tasks_def(2000, knight_rider);

	/* habilitamos las interrupciones */
	sei();
	
        while (1) {

		tasks_do();
        }

        return 0;
}
