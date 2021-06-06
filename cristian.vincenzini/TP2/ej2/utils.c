/* utils.c - implementacion de funciones utiles al TP2 */
#include "utils.h"

#define CYCLES_PER_MS (450)

#define PB0 (0x01)  /* 0b 0000 0001 PIN 8 en placa  */
#define PB1 (0x02)  /* 0b 0000 0010 PIN 9 en placa  */
#define PB2 (0x04)  /* 0b 0000 0100 PIN 10 en placa */
#define PB3 (0x08)  /* 0b 0000 1000 PIN 11 en placa */
#define PB4 (0x10)  /* 0b 0001 0000 PIN 12 en placa */
#define PB5 (0x20)  /* 0b 0010 0000 PIN 13 en placa */

/* puertos de E/S */
volatile unsigned char * PORTB = (unsigned char *) 0x25;  /* direccion de PORTB */
volatile unsigned char * DDRB  = (unsigned char *) 0x24;  /* direccion de DDR B (registro de control) */
volatile unsigned char * PINB  = (unsigned char *) 0x23;  /* direccion PIN B (registro de datos) */

void delay_ms(unsigned long ms)
{
        volatile unsigned long i;  /* no quitar volatile o NO funciona */

        for (i = 0; i < CYCLES_PER_MS * ms; i++);
}

unsigned char switch_up;

void switch_state()
{
        //unsigned char switch_up;
        unsigned long i;

        switch_up = *PINB & PB4;

        /* retardo para quitar el rebote */
        for (i = 0; i < 100000; i++) {
                switch_up &= *PINB & PB4;  /* estado HIGH mientras no se presione switch */
        }
}

void suma_binaria()
{
        int i;

        for (i = 0; i < 15; i++) {
                delay_ms(500);
                *PORTB += 1;
        }

        /* setea pins en OFF */
        *PORTB &= ( ~PB0 & ~PB1 & ~PB2 & ~PB3 );
}

void leds_on()
{
        *PORTB &= ( ~PB0 & ~PB1 & ~PB2 & ~PB3 );
        delay_ms(500);
        *PORTB |= ( PB0 | PB1 | PB2 | PB3 );
        delay_ms(500);
        *PORTB &= ( ~PB0 & ~PB1 & ~PB2 & ~PB3 );
}

void leds_init()
{
        /* setea en OFF el voltaje de los pines */
        *PORTB &= ( ~PB0 & ~PB1 & ~PB2 & ~PB3 );

        /* setea pines en modo OUTPUT */
        *DDRB |= (PB0 | PB1 | PB2 | PB3);
        
        /* configuracion del boton */
        *DDRB &= ~PB4;  /* setea pin del boton en modo INPUT (bit ddrb = 0) */
        *PORTB |= PB4;  /* activa modo PULL-UP (bit portb = 1) */
}

void toggle_debug_led()
{
        *PORTB ^= PB5;
}