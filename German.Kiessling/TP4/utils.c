/* utils.c - funciones utiles al TP2 */

#define LED_1 (0x01) /*pin 8  0b00000001 */
#define LED_2 (0x02) /*pin 9  0b00000010 */
#define LED_3 (0x04) /*pin 10 0b00000100 */ 
#define LED_4 (0x08) /*pin 11 0b00001000 */
//#define LED_5 (0x10) /*pin 12 0b00010000 */
//#define LED_6 (0x20) /*pin 13 0b00100000 */




/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */


/* puertos de E/S */
volatile unsigned char * PUERTO_B = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * DDR_B = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * PIN_B = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/


/* 
 * Configuración: Establecer el 5to bit del puerto B como entrada
 *
 * 	Poner en '0' el 5to bit de la dirección 0x24, que 
 * 	es el la dirección del registro de control
 *	(direccion de los datos) del puerto B (DDRB - Data Direction Register).
 *      El 5to bit define la entrada o salida del
 * 	pin del atmega328p que tiene conectado un led en una board arduino
 */

void led_init(void)
{
    /* turn the GPIO pin voltage off
    * (this should be done before the pins are configured)
    */
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_1);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_2);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_3);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_4);
    //*(PUERTO_B) = *(PUERTO_B) & (~ LED_5);
    //*(PUERTO_B) = *(PUERTO_B) & (~ LED_6);

    /* make sure the LED control pin is set to operate as OUTPUT */
    *(DDR_B) = *(DDR_B) | (LED_1);
    *(DDR_B) = *(DDR_B) | (LED_2);
    *(DDR_B) = *(DDR_B) | (LED_3);
    *(DDR_B) = *(DDR_B) | (LED_4);
    //*(DDR_B) = *(DDR_B) | (LED_5);
    //*(DDR_B) = *(DDR_B) | (LED_6);
}


void esperar(unsigned long segundos) {
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<segundos; i++);
}

void conteo(unsigned int num)
{
	int i;

	for (i = 0; i < num; i++) {
		*(PUERTO_B) += 1;
		esperar(450000);
	}

	// setea en OFF el voltaje de los pines
	*(PUERTO_B) &= ( ~LED_1 & ~LED_2 & ~LED_3 & ~LED_4);
}
void intensidad(unsigned int num)
{
	// setea en OFF el voltaje de los pines
	*(PUERTO_B) &= ( ~LED_1 & ~LED_2 & ~LED_3);
    *(PUERTO_B) += num;
    esperar(10000);
}

void knight_rider() {
    unsigned char leds[6] = {LED_1, LED_2, LED_3, LED_4};
    unsigned char valor_led1;
    unsigned char valor_led2;
	int i;

    // ida 
	for (i = 0; i < 5; i++) {
        // encender
		*(PUERTO_B) |= leds[i];
        esperar(20000);
        *(PUERTO_B) |= leds[i+1];
        // apagar
        *(PUERTO_B) &= ~leds[i];
        esperar(20000);
        *(PUERTO_B) &= ~leds[i+1];
	}

    // vuelta
	for (i = 5; i > 0; i--) {
		// encender
		*(PUERTO_B) |= leds[i];
        esperar(20000);
        *(PUERTO_B) |= leds[i-1];
        // apagar
        *(PUERTO_B) &= ~leds[i];
        esperar(20000);
        *(PUERTO_B) &= ~leds[i-1];
	}



	// setea en OFF el voltaje de los pines
	*(PUERTO_B) &= ( ~LED_1 & ~LED_2 & ~LED_3 & ~LED_4 );
}
