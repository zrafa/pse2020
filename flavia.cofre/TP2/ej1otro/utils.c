
/* utils.c - funciones utiles al TP2 */

#define MASK5 (0x20)


/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */


/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */


/* 
 * Configuración: Establecer el 5to bit del puerto B como entrada
 *
 * 	Poner en '0' el 5to bit de la dirección 0x24, que 
 * 	es el la dirección del registro de control
 *  (direccion de los datos) del puerto B (DDRB - Data Direction Register).
 *  El 5to bit define la entrada o salida del
 * 	pin del atmega328p que tiene conectado un led en una board arduino
 */

void esperar(unsigned long segundos) 
{
	volatile unsigned long i;
	/* delay de n segundos */
	for (i=0; i<450000*segundos; i++);
}




void prender_led() {

    unsigned char valor_b;
    valor_b = *(puerto_b);
    valor_b ^= MASK5;
    *(puerto_b) = valor_b;
}

void apagar_led() {

    unsigned char valor_b;
    valor_b = *(puerto_b);
    valor_b ^= MASK5;
    *(puerto_b) = valor_b;
}

