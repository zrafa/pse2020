
/* utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#define prende (0x38)
#define bit2 (0x04)

/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/
volatile unsigned char estado=0;


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
	*(pin_b) =  0x04;
}

void esperar() {
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<450000; i++);
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


void contar(unsigned char num){
	volatile unsigned char valor_b = *(puerto_b);
	valor_b ^= num;
	*(puerto_b) = valor_b;
	
}
unsigned char get_estado(){
volatile unsigned char valor_b = *(pin_b);
	valor_b &=  bit2 ;
	if(valor_b != bit2){
		if(estado == 0){estado =1;}
		else{(estado = 0);}
	}
	
	return estado;
}
