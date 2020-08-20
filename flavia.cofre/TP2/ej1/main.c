/**********************************************************************
*
* Function: main
*
* Descripcion: Enciende y apaga (parpadea) el LED rojo de la 
* placa arduino pro mini que está controlado por la señal de
* salida PORTB5 (Puerto B bit 5) del microcontrolador atmega328p.
* Notes: Esta rutina contiene un bucle infinito.
*
**********************************************************************/


#include "utils.h"
#define segundos 1

int main(void)
{	

    /* configura el pin que controla el LED rojo. */
	led_init();

	while (1) {	

        /* cambia el estado del LED rojo. */
		led_toggle();

        /* realiza una pausa en segundos. */
        esperar(segundos);
	}
}


