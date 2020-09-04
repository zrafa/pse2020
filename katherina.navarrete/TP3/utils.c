
/* utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#define LEDS (0x3F)


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
void lets_init()
{
	*puerto_b = *puerto_b & (~ LEDS);
	*ddr_b = *ddr_b | (LEDS);
}

void esperar_dos_seg() 
{
	volatile unsigned long i;
	for (i=0; i<900000; i++);
}
void esperar_medio_seg()
{
	volatile unsigned long i;
	for (i=0; i<22500; i++);
}


void prender_leds() 
{
	volatile unsigned char valor_b = *puerto_b;
	valor_b |=  LEDS ;
	*(puerto_b) = valor_b;
}

void apagar_leds() 
{
	volatile unsigned char valor_b = *puerto_b;
	valor_b &= ~(LEDS);
	*puerto_b = valor_b;
}

void prender_leds_elegidos(unsigned char bits_elegidos)
{
	volatile unsigned char valor_b = *puerto_b;
	valor_b ^= bits_elegidos;
	*puerto_b = valor_b;
	
}




#define bit_0 0x01
#define bit_3_2_1 0x07

void contar_binario()
{
	unsigned char tmp = bit_0;
	unsigned char i;

	apagar_leds();
	for (i=0; i < 3; i++) {
		
		prender_leds_elegidos(bit_0);
		esperar_dos_seg();

		if (tmp == bit_3_2_1) {

			tmp = tmp >> 1;

		} else { 

			tmp = (tmp << 1);
			tmp |= bit_0;
		}

		prender_leds_elegidos(tmp);
		esperar_dos_seg();
	}

	prender_leds_elegidos(bit_0);
	esperar_dos_seg();
	apagar_leds();
}



#define maximo 0x20
#define minimo 0x01
#define bit_7_6 0xc0

void knight_rider()
{
	volatile unsigned char valor_b = *puerto_b;
	unsigned char tmp = maximo;
	
	while (tmp != minimo) {
		*puerto_b = ( bit_7_6 & valor_b ) | (tmp);
		esperar_medio_seg();
		tmp = tmp >> 1;
 	}

	while (tmp != maximo) {
		*puerto_b = ( bit_7_6 & valor_b ) | (tmp);
		esperar_medio_seg();
		tmp = tmp << 1;
 	}
	*puerto_b = ( bit_7_6 & valor_b );
}



