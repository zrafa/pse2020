/* utils.c - implementacion de funciones utiles al TP2 */
#include "utils.h"


/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */
#define PB5 (0x20)  /* 0b00100000 */

/* puertos de E/S */
volatile unsigned char * PORTB = (unsigned char *) 0x25;  /* direccion de PORTB: SALIDA */
volatile unsigned char * DDRB  = (unsigned char *) 0x24;  /* direccion de DDR B (registro de control) */
volatile unsigned char * PINB  = (unsigned char *) 0x23;  /* direccion PIN B (registro de datos)*/


/* 
 * Configuración: Establecer el 5to bit del puerto B como entrada
 *
 * 	Poner en '0' el 5to bit de la dirección 0x24, que 
 * 	es el la dirección del registro de control
 *	(direccion de los datos) del puerto B (DDRB - Data Direction Register).
 *      El 5to bit define la entrada o salida del
 * 	pin del atmega328p que tiene conectado un led en una board arduino
 */

void esperar(unsigned long sec)
{
        unsigned long i;

        /* delay de 1 segundo */
        for (i=0; i<450000*sec; i++);
}

void cambiar_estado()
{
        volatile unsigned char valor_b;
        
        valor_b = *PORTB; /* lectura */

        valor_b ^= PB5;   /* modificacion */

        *PORTB = valor_b; /* escritura */
}

void setup(void)
{
        *PORTB = *PORTB & (~PB5);

        *DDRB  = *DDRB | (PB5);
}