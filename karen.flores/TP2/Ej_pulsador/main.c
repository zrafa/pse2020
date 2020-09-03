
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"

int main(void)
{	
 	
	led_init(); 
	unsigned char estado = boton_presionado();

	while (1) {

		if (estado == 0) {
			prender_led();
			esperar();
			apagar_led();
		} else {
			esperar();
			conteo_binario();
			apagar_led();
		}
		esperar();
		estado = boton_presionado();
	}
return 0;
}


