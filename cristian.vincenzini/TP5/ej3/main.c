#include <avr/interrupt.h>
#include <stdio.h>

#include "timer.h"
#include "serial.h"

int to_ASCII(int, char[]);

int main(void)
{
        serial_init();
        timer0_init();

        int cant_serial = 0; 

        cli();
        timer0_rtc_set(0, 0, 0, 0, 0, 0);
        int tmp = timer0_rtc_get_sec();
        sei();

        while (tmp == 0) {
                serial_put_char('a');
                cant_serial++;

                cli();
                tmp = timer0_rtc_get_sec();
                sei();
        }

        serial_put_str("\r\n");
        serial_put_str("La cantidad de E/S en un segundo es: ");

        char cadena[6];
        int i = to_ASCII(cant_serial, cadena);

        for (i; i >= 0; i--)
                serial_put_char(cadena[i]);

        serial_put_str("\r\n");
	
	for (;;);	
}

/*
 * Convierte entero en secuencia de caracteres.
 * Ejemplo: 581 -> {'5', '8', '1'}
 *
 * Retorna cantidad de digitos leidos,
 * tomando el ejemplo: 3
 */
int to_ASCII(int val, char str[])
{
        int i = 0;
        while (val >= 10) { 	
                str[i] = (val % 10 + '0');
                val = val / 10;
                i++;
        }
        str[i]   = val + '0';
        str[i+1] ='\0';

        return i;
}

