/**********************************************************************
 *
 * utils.c - Funciones de utilidad
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#define LEDS (0x20)


/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/


void lets_init()
{
	*(puerto_b) = *(puerto_b) & (~ LEDS);
	*(ddr_b) = *(ddr_b) | (LEDS);
}

void esperar() 
{
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<90000; i++);
}

void prender_leds() 
{
	volatile unsigned char valor_b = *(puerto_b);
	valor_b |=  LEDS ;
	*(puerto_b) = valor_b;
}

void apagar_leds() 
{
	volatile unsigned char valor_b = *(puerto_b);
	valor_b &= ~(LEDS);
	*(puerto_b) = valor_b;
}
void toggle_leds() 
{
	volatile unsigned char valor_b = *(puerto_b);
	valor_b ^= LEDS;
	*(puerto_b) = valor_b;
}

