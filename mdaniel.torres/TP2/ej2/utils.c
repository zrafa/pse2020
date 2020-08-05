
/* utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */


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

void esperar() {
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<450000; i++);
}

void prender_led(){
    unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */
    unsigned char valor_b;
    valor_b = *(PUERTO_B);
    valor_b ^= (0x02);
    *(PUERTO_B) = valor_b;

    //segundo
    unsigned char valor_segundo;
    valor_segundo = *(PUERTO_B);
    valor_segundo ^= (0x04);
    *(PUERTO_B) = valor_segundo;

    //tercero 
    unsigned char valor_tercero;
    valor_tercero= *(PUERTO_B);
    valor_tercero^= (0x08);
    *(PUERTO_B) = valor_tercero;
}


void apagar_led(){
    unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */
    unsigned char valor_b;
    valor_b = *(PUERTO_B);
    valor_b ^= (0x02);
    *(PUERTO_B) = valor_b;

    //segundo
    unsigned char valor_segundo;
    valor_segundo = *(PUERTO_B);
    valor_segundo ^= (0x04);
    *(PUERTO_B) = valor_segundo;

    //tercero
    unsigned char valor_tercero;
    valor_tercero= *(PUERTO_B);
    valor_tercero^= (0x08);
    *(PUERTO_B) = valor_tercero;
}





