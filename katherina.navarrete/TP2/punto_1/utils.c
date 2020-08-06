
/* utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#define prende (0x20)


/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/


void let_init(){
	*(puerto_b) = *(puerto_b) & (~ prende);
	*(ddr_b) = *(ddr_b) | (prende);
}

void esperar() {
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<90000; i++);
}

void prender_led() {
	volatile unsigned char valor_b = *(puerto_b);
	valor_b |=  prende ;
	*(puerto_b) = valor_b;
}

void apagar_led() {
	volatile unsigned char valor_b = *(puerto_b);
	valor_b &= ~(prende);
	*(puerto_b) = valor_b;
}

