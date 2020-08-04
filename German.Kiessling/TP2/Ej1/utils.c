
/* utils.c - funciones utiles al TP2 */
#define LED_ROJO (0x20) /* 0b00100000 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */


/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/


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
    volatile unsigned char * DDR_B = 0x24; /* direccion de DDR B */
    volatile unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */
    /* turn the GPIO pin voltage off
    * (this should be done before the pins are configured)
    */
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_ROJO);
    /* make sure the LED control pin is set to operate as OUTPUT */
    *(DDR_B) = *(DDR_B) | (LED_ROJO);
}


void esperar() {
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<450000; i++);
}

// Se puede unificar los metodos de prender_led y apagar ya que ambos relizan 
// la accion de cambiar el estado del bit de 0 a 1 o de 1 a 0
void prender_led() {
    volatile unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */
    unsigned char valor_b;
    valor_b = *(PUERTO_B);
    valor_b ^= LED_ROJO;
    *(PUERTO_B) = valor_b;

}

void apagar_led() {
    volatile unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */
    unsigned char valor_b;
    valor_b = *(PUERTO_B);
    valor_b ^= LED_ROJO;
    *(PUERTO_B) = valor_b;

}
