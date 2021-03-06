/**********************************************************************
 *
 * utils.c - Funciones de utilidad
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/
#include "utils.h"

#define CYCLES_PER_MS (450)

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */
#define PB0 (0x01)  /* 0b 0000 0001 PIN 8 en placa  */
#define PB1 (0x02)  /* 0b 0000 0010 PIN 9 en placa  */
#define PB2 (0x04)  /* 0b 0000 0100 PIN 10 en placa */
#define PB3 (0x08)  /* 0b 0000 1000 PIN 11 en placa */
#define PB4 (0x10)  /* 0b 0001 0000 PIN 12 en placa */
#define PB5 (0x20)  /* 0b 0010 0000 PIN 13 en placa */

/* puertos de E/S */
volatile unsigned char * PORTB = (unsigned char *) 0x25;  /* direccion de PORTB: SALIDA */
volatile unsigned char * DDRB  = (unsigned char *) 0x24;  /* direccion de DDR B (registro de control) */
volatile unsigned char * PINB  = (unsigned char *) 0x23;  /* direccion PIN B (registro de datos)*/

/* funciones */

void delay_ms(unsigned long ms)
{
        volatile unsigned long i;

        for (i = 0; i < CYCLES_PER_MS * ms; i++);
}

void suma_binaria()
{
        int i, j;

        for (i = 0; i < 15; i++) {
                *PORTB += 1;
                delay_ms(500);
        }

        /* setea en OFF el voltaje de los pines */
        *PORTB &= ( ~PB0 & ~PB1 & ~PB2 & ~PB3 );
}

void prender_apagar(unsigned char pin)
{
        *PORTB |= pin;
        delay_ms(50);
        *PORTB &= ~pin;
        delay_ms(50);
}

void knight_rider()
{
        unsigned char pin[4] = {PB0, PB1, PB2, PB3};
        int i;

        for (i = 0; i < 4; i++) {
                prender_apagar(pin[i]);
        }

        for (i = 2; i >= 0; i--) {
                prender_apagar(pin[i]);
        }

        /* setea en OFF el voltaje de los pines */
        *PORTB &= ( ~PB0 & ~PB1 & ~PB2 & ~PB3 );
}

void leds_init()
{
        /* setea en OFF el voltaje de los pines */
        *PORTB &= ( ~PB0 & ~PB1 & ~PB2 & ~PB3 );

        /* setea pines en modo OUTPUT */
        *DDRB |= (PB0 | PB1 | PB2 | PB3);
}
