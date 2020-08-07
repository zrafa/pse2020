
/* Pulsador que intercambia modos de operacion */

#include "utils.h"

unsigned char modo = 0;
unsigned char se_presiono_boton = 0;

int main(void)
{	
	setup();

	while (1) {
		se_presiono_boton = leer_boton();

		if (se_presiono_boton) {
			reiniciar_leds();
			modo = !modo;
		}

		if (modo) {
			suma_binaria();
		} else {
			// modo 0 inicial
			encender_leds();
		}
	}
}


