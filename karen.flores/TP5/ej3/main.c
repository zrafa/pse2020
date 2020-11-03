#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "utils.h"
#include "serial.h"


int convertir_ASCII(int val, char cadena[])
{
	int i=0;
	while (val >= 10) { 	
		cadena[i]=(val % 10+48);
		val = val /10;
		i++;
	}
	cadena[i] = val+48;
	cadena[i+1] ='\0';
	return i;
}

int main(void)
{

	/* las interrupciones están deshabilitadas */
	serial_init();
	
        /* habilitar las interrupciones */
	timer0_init();

	int cant_serial = 0; 

	cli();
	timer0_rtc_set(0,0,0,0,0,0);
	sei();

	while(timer0_rtc_get_sec() == 0)
	{
		serial_put_char('a');
		cant_serial++;
	}
	serial_put_String("\r\n");
	serial_put_String("la cantidad de E/S en un segundo es: ");
	char cadena[6];
	int i = convertir_ASCII(cant_serial, cadena);
	for(i; i>=0 ; i--)
		serial_put_char(cadena[i]);
	serial_put_String("\r\n");
	for (;;);
		
}




