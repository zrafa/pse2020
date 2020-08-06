
/* utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#define prende (0x3F)


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
void let_init(){
	*(puerto_b) = *(puerto_b) & (~ prende);
	*(ddr_b) = *(ddr_b) | (prende);
}

void esperar() {
	volatile unsigned long i;
	for (i=0; i<56250; i++);
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
void knight_rider(){
	volatile unsigned char valor_b = *(puerto_b);
	volatile unsigned num = 0x20;
        
	valor_b ^= num;
	num = num ^ (num >> 1);
	*(puerto_b) = valor_b;
	esperar();
	while(num != 1){
		
		valor_b ^= num;
		num = (num >> 1);
		*(puerto_b) = valor_b;
		esperar();
	}
	num = num ^ (num << 1);
	*(puerto_b) = valor_b;
	esperar();
	while(num != 48){
		
		valor_b ^= num;
		num = (num << 1);
		*(puerto_b) = valor_b;
		esperar();
	}
apagar_led();
}

