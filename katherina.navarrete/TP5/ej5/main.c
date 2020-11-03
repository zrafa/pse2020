#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "serial.h"


int main(void)
{

	DDRB = 0x02; /*habilita PB1(OC1A) como pin de salida*/

	serial_init();    
	timer1_init();
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
