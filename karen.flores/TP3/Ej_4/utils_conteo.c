
/* utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */
#define LED (0x38)
#define BIT2 (0x04)
#define CONF_ENTRADAS (0x3C)

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
void let_init()
{
	*(puerto_b) = *(puerto_b) & (~ CONF_ENTRADAS);
	*(ddr_b) = *(ddr_b) | (LED);
	*(ddr_b) = *(ddr_b) & (~ BIT2);
	*(pin_b) =  0x04;
}

void esperar() 
{
	volatile unsigned long i;
	/* delay de 1/2 segundo */
	for (i=0; i<225000; i++);
}

void prender_led() 
{
	unsigned char valor_b = *(puerto_b);
	valor_b |=  LED ;
	*(puerto_b) = valor_b;
}

void apagar_led() 
{
	unsigned char valor_b = *(puerto_b);
	valor_b &= ~(LED);
	*(puerto_b) = valor_b;
}

void conteo_binario()
{
	unsigned char c;
	unsigned char b;
	int i = 0;
	while (i < 7) {
		c++;
		switch (c) {
			case 1:
				b = c << 5;
			break;
			case 2:
				b = c << 3;
			break;
			case 3:
				b = c << 4;
			break;
			case 4:
				b = c << 1;
			break;
			case 5:
				b = c << 3;
			break;	
			case 6:
				b = c << 2;
			break;	
			case 7:
				b = c << 3;
			break;
		}
		*(puerto_b) = b;
		i++;
		esperar();
	}
}
