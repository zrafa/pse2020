/* habilita PB1(OC1A) como pin de salida */
#include "utils.h"

#define PIN9 (1 << 1)

volatile unsigned char * PORTB = (unsigned char *) 0x25;  /* direccion de PORTB */
volatile unsigned char * DDRB  = (unsigned char *) 0x24;  /* direccion de DDR B (registro de control) */
volatile unsigned char * PINB  = (unsigned char *) 0x23;  /* direccion PIN B (registro de datos) */

void pin9_init(void)
{
        *PORTB &= ~PIN9;  /* set voltage off */
        *DDRB  |= PIN9;   /* set pin as OUTPUT */
        *PORTB |= PIN9;   /* turn on */
}

/* usando macro en main: DDRB = 0x02; */
