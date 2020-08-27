
#include "utils.h"
#define MASK5 (0x20)


/**********************************************************************
*
* Function: led_init
*
* Description: Initialize the GPIO pin that controls the LED.
* Notes: This function is specific to the atmega328p.
*
**********************************************************************/
void led_init(void)
{
    volatile unsigned char * DDR_B = (unsigned char *)0x24; /* direccion de DDR B */
    volatile unsigned char * PUERTO_B = (unsigned char *) 0x25; /* direccion de PUERTO B */

    /* turn the GPIO pin voltage off */
    *(PUERTO_B) = *(PUERTO_B) & (~ MASK5);

    /* make sure the LED control pin is set to operate as OUTPUT */
    *(DDR_B) = *(DDR_B) | (MASK5);
}



/**********************************************************************
*
* Function: main
*
* Description: 
* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328.
* el pin del arduino pro mini es 13
*
* Notes: This routine contains an infinite loop.
* El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
* pines 8-13 de arduino
*
**********************************************************************/

int main(void)
{	
	/* configure the red LED control pin. */
    led_init( );

	while (1) {
		esperar(2);
		prender_led();

		esperar(5);
		apagar_led();
    	}
}



