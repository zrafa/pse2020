
/* utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */
#define LED (0x38)
#define BIT2 (0x04)
#define CONF_ENTRADA (0x3C)

/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/
unsigned char estado;


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
	*(puerto_b) = *(puerto_b) & (~ CONF_ENTRADA);
	*(ddr_b) = *(ddr_b) | (LED);
	*(ddr_b) = *(ddr_b) & (~ BIT2);
	*(pin_b) =  0x04;
}

void esperar() {
	unsigned long i;
	/* delay de 2 segundo */
	for (i=0; i<900000; i++);
}

void prender_led() {
	unsigned char valor_b = *(puerto_b);
	valor_b |=  LED ;
	*(puerto_b) = valor_b;
}

void apagar_led() {
	unsigned char valor_b = *(puerto_b);
	valor_b &= ~(LED);
	*(puerto_b) = valor_b;
}

unsigned char get_estado() {
	unsigned char valor_b = *(pin_b);
	valor_b &=  BIT2 ;
	if (valor_b != BIT2){
		if(estado == 0){estado =1;}
		else{estado = 0;}
	}
	
	return estado;
}

void conteo_binario() {
	unsigned char valor_b = *(pin_b);
	valor_b ^= 0x20;
	*(puerto_b) = valor_b;
	esperar();
	
	valor_b ^= 0x30;
	*(puerto_b) = valor_b;
	esperar();
	
	valor_b ^= 0x20;
	*(puerto_b) = valor_b;
	esperar();
	
	valor_b ^= 0x38;
	*(puerto_b) = valor_b;
	esperar();

	valor_b ^= 0x20;
	*(puerto_b) = valor_b;
	esperar();

	valor_b ^= 0x30;
	*(puerto_b) = valor_b;
	esperar();
	
	valor_b ^= 0x20;
	*(puerto_b) = valor_b;
	esperar();
}
