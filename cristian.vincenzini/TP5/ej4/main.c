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
        serial_put_str(buffer);
        sei();
        serial_put_str("\r\n");
}

int main(void)
{
        timer0_init();
        leds_init();
        serial_init();
        tasks_init();
        
        timer0_rtc_set(2021, 6, 1, 13, 30, 0);
        
        /* definimos una tarea periódica a 300ms */
        tasks_def(500, toggle13);
        tasks_def(1000, toggle10);
        tasks_def(2000, enviar_hora);

        /* habilitamos las interrupciones */
        sei();

        while (1) {
                tasks_do();
        }

        return 0;
}
