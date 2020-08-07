
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"
#define LED_ROJO (0x20)
void led_init();

int main(void)
{	
	// init
	led_init();	

	while (1) {
		esperar();
		prender_led();

		esperar();
		apagar_led();
    }
}


void led_init(){

volatile unsigned char * DDR_B = 0x24; /* direccion de DDR B */
volatile unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */

/* turn the GPIO pin voltage off* (this should be done before the pins are configured)*/

	*(PUERTO_B) = *(PUERTO_B) & (~ LED_ROJO);

/* make sure the LED control pin is set to operate as OUTPUT */

	*(DDR_B) = *(DDR_B) | (LED_ROJO);

}

