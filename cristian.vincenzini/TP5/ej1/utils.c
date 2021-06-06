/* utils.c - implementacion de funciones utiles al TP2 */
#include "utils.h"


/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */
#define LED (0x20)  /* 0b00100000 */

#define CYCLES_PER_MS (450)

/* puertos de E/S */
volatile unsigned char * PORTB = (unsigned char *) 0x25;  /* direccion de PORTB: SALIDA */
volatile unsigned char * DDRB  = (unsigned char *) 0x24;  /* direccion de DDR B (registro de control) */
volatile unsigned char * PINB  = (unsigned char *) 0x23;  /* direccion PIN B (registro de datos)*/


/* 
 * Configuración: Establecer el 5to bit del puerto B como entrada
 *
 * Poner en '0' el 5to bit de la dirección 0x24, que 
 * es el la dirección del registro de control
 * (direccion de los datos) del puerto B (DDRB - Data Direction Register).
 * El 5to bit define la entrada o salida del
 * pin del atmega328p que tiene conectado un led en una board arduino
 */


void delay_ms(unsigned long ms)
{
	volatile unsigned long i;  /* no quitar volatile o NO funciona */

	for (i = 0; i < CYCLES_PER_MS * ms; i++);
}

void led_toggle(void)
{
        *PORTB ^= LED;
}

void led_init(void)
{
        *PORTB &= ~LED;  /* set voltage off */
        *DDRB  |= LED;   /* set pin as OUTPUT */
}
