#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "utils.h"
#include "tasks.h"
#include "serial.h"

char buffer[23];

void enviarFecha()
{
	
	cli();
	timer0_rtc_to_str(buffer); 		 
	serial_put_String(buffer);
	sei();
	serial_put_String("\r\n");
}

void put_char()
{
	
	serial_put_char('a'); 
	serial_put_String("\r\n");
}

int main(void)
{
        timer0_init();
        leds_init();
	tasks_init();
	serial_init();
	
	/* definimos una tarea periódica a 300ms */
	tasks_def(100, toggle13);
	tasks_def(200, toggle12);
	tasks_def(500, put_char);
	tasks_def(1000, enviarFecha);

	/* habilitamos las interrupciones */
	sei();
	
        while (1) {

		tasks_do();
        }

        return 0;
}
