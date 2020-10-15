#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "utils.h"
#include "tasks.h"



int main(void)
{
        timer0_init();
        leds_init();
	tasks_init();

	/* definimos una tarea periódica a 300ms */
	tasks_def(300, toggle13);

	/* habilitamos las interrupciones */
	sei();
	
        while (1) {

		tasks_do();
        }

        return 0;
}
