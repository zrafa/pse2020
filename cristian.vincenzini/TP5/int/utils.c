/* utils.c - implementacion de funciones utiles al TP2 */
#include "utils.h"

#define LED (0x20)  /* 0b00100000 */
#define PB4 (1 << 4)
#define CYCLES_PER_MS (450)

/* puertos de E/S */
volatile unsigned char * PORTB  = (unsigned char *) 0x25;  /* direccion de PORTB: SALIDA */
volatile unsigned char * DDRB   = (unsigned char *) 0x24;  /* direccion de DDR B (registro de control) */
volatile unsigned char * PINB   = (unsigned char *) 0x23;  /* direccion PIN B (registro de datos)*/
volatile unsigned char * PCICR  = (unsigned char *) 0x68;
volatile unsigned char * PCMSK0 = (unsigned char *) 0x6B;


void delay_ms(unsigned long ms)
{
        volatile unsigned long i;  /* no quitar volatile o NO funciona */

        for (i = 0; i < CYCLES_PER_MS * ms; i++);
}

void led_toggle(void)
{
        *PORTB ^= LED;
}

void leds_init(void)
{
        *PORTB &= ~LED;  /* set voltage off */
        *DDRB  |= LED;   /* set pin as OUTPUT */
        
         /* configuracion del boton */
        *DDRB  &= ~PB4;  /* setea pin del boton en modo INPUT (bit ddrb = 0) */
        *PORTB |= PB4;  /* activa modo PULL-UP (bit portb = 1) */

        *PCICR  |= (1 << 0);
        *PCMSK0 |= PB4;  /* activa interrupcion */
}
