
/* utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */
#define LED (0x3F)


/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/
unsigned char valor_b = 0x20;


/* 
 * Configuración: Establecer el 5to bit del puerto B como entrada
 *
 * 	Poner en '0' el 5to bit de la dirección 0x24, que 
 * 	es el la dirección del registro de control
 *	(direccion de los datos) del puerto B (DDRB - Data Direction Register).
 *      El 5to bit define la entrada o salida del
 * 	pin del atmega328p que tiene conectado un led en una board arduino
 */
void led_init() {
	*(puerto_b) = *(puerto_b) & (~ LED);
	*(ddr_b) = *(ddr_b) | (LED);
}

void esperar() {
	unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<56250; i++);
}

void knight_rider(){
	while (valor_b > 0x01) 
	{
		*(puerto_b) = valor_b;
		esperar();
		if (valor_b > 0x01) {
			valor_b >>= 1;
		}
	}
}

void knight_rider_reverso(){
	while (valor_b < 0x20) 
	{
		*(puerto_b) = valor_b;
		esperar();
		if (valor_b < 0x20) {
			valor_b <<= 1;
		}
	}
}
