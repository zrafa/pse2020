/**********************************************************************
 *
 * utils.c - Funciones de utilidad
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#define LED (0x20)
#define BIT2 (0x04)

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

void leds_init(){
	*(puerto_b) = *(puerto_b) & (~ 0x3C);
	*(ddr_b) = *(ddr_b) | (LED);
	*(ddr_b) = *(ddr_b) & (~ BIT2);
	*(pin_b) =  0x04;
}

void led_toggle()
{
	volatile unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */
	unsigned char valor_b;
	valor_b = *(PUERTO_B);
	valor_b ^= LED;
	*(PUERTO_B) = valor_b;
}
