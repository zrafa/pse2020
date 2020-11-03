/**********************************************************************
 *
 * utils.c - Funciones de utilidad
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/
#include "utils.h"

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */
#define PB5 (0x20)  /* 0b 0010 0000 PIN 13 en placa */
#define PB4 (0x10)  /* 0b 0001 0000 PIN 12 en placa */
#define LEDS (0x3F)

/* puertos de E/S */
volatile unsigned char * PORTB = (unsigned char *) 0x25;  /* direccion de PORTB: SALIDA */
volatile unsigned char * DDRB  = (unsigned char *) 0x24;  /* direccion de DDR B (registro de control) */
volatile unsigned char * PINB  = (unsigned char *) 0x23;  /* direccion PIN B (registro de datos)*/

/* funciones */

void toggle12()
{
        *PORTB ^= PB4;
}

void toggle13()
{
        *PORTB ^= PB5;
}

void leds_init()
{
        /* setea en OFF el voltaje de los pines */
        *PORTB &= ( ~LEDS );

        /* setea pines en modo OUTPUT */
        *DDRB |= (LEDS);
        
}
#define maximo 0x20
#define minimo 0x01
#define bit_7_6 0xc0

void knight_rider()
{
	volatile unsigned char valor_b = *PORTB;
	unsigned char tmp = maximo;
	
	while (tmp != minimo) {
		*PORTB = ( bit_7_6 & valor_b ) | (tmp);

		for(int i = 0; i < 10000; i++ );
		tmp = tmp >> 1;
 	}

	while (tmp != maximo) {
		*PORTB = ( bit_7_6 & valor_b ) | (tmp);

		for(int i = 0; i < 10000; i++ );
		tmp = tmp << 1;
 	}
	*PORTB = ( bit_7_6 & valor_b );
}
