/* utils.c - implementacion de funciones utiles al TP2 */
#include "utils.h"

#define MASK5 (0x20)  /* 0b00100000 mascara para controlar el bit 5 */


/* puertos de E/S */
volatile unsigned char * PORTB = (unsigned char *) 0x25;  /* direccion del Puerto B */
volatile unsigned char * DDRB  = (unsigned char *) 0x24;  /* direccion de DDR B (registro de control) */


void led_init(void)
{

    /* voltage de salida en el pin GPIO es establecido a cero */
	*(PORTB) = *(PORTB) & (~MASK5);

    /* 
     *  Configura que el pin GPIO se utilice como SALIDA a traves del registro DDRB,
     *  especificamente su bit 5
     *
     *  lectura: se lee el contenido del registro DDRB
     *  modificacion: se modifica el bit que controla el LED con ayuda de la mascara (PB5)
     *  escritura:se escribe el nuevo valor de vuelta en la ubicación del registro DDRB
     */
	*(DDRB)  = *(DDRB) | (MASK5);

}



/*
 *   Cambia el estado del LED (encendido/apagado) a través del registro PORTB especificamente su bit 5.
 */
void led_toggle()
{
	volatile unsigned char valor_b;
	
	valor_b = *(PORTB); 

	valor_b ^= MASK5;     

	*(PORTB) = valor_b; 
}


/*
 *  Establece una espera de n segundos entre el encendido y apagado del LED
 */
void esperar(unsigned long n)
{
	volatile unsigned long i;

	/* delay de n segundos */
	for (i=0; i<450000*n; i++);
}
