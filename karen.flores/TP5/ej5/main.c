#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "serial.h"


int main(void)
{
	/*Se habilita el pin PB1 (OC1A) como pin de salida*/
	DDRB = 0x02;
	/* las interrupciones están deshabilitadas */
	serial_init();
	timer1_init();
	volatile char dato;
	/* habilitar las interrupciones */
	sei();
        while (1) {

		dato = serial_get_char();
		cli();
		actualizar_dato_PC(dato);
		sei();
        }
}
