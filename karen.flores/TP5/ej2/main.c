#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "utils.h"
#include "serial.h"


int main(void)
{
	/* las interrupciones están deshabilitadas */
	serial_init();
	
        /* habilitar las interrupciones */
	timer0_init();
	char buffer[23];
	char dec_nueva;
	char dec_anterior;
	cli();
	dec_anterior = timer0_rtc_get_tos();
	sei();
	dec_nueva = dec_anterior;
	for (;;) {
		timer0_rtc_to_str(buffer); 
		
		serial_put_String(buffer);
		serial_put_String("\r\n");
		
		while (dec_nueva == dec_anterior) {
			cli();
			dec_nueva = timer0_rtc_get_tos();	
			sei();
		}

		dec_anterior = dec_nueva;

	}
}




