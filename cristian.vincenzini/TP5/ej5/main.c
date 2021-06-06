#include <avr/interrupt.h>

#include "timer.h"
#include "serial.h"
#include "utils.h"

int main(void)
{
        serial_init();
        timer1_init();
        pin9_init();

        volatile char dato;
        
        /* habilitar las interrupciones */
        sei();

        while (1) {
                dato = serial_get_char();

                cli();
                actualizar_dato_pc(dato);
                sei();
        }
}
