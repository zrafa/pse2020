#define LEDS (0x38)


/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/


void lets_init()
{
	*puerto_b = *puerto_b & (~ LEDS);
	*ddr_b = *ddr_b | (LEDS);
}

void prender_leds()
{
	unsigned char valor_b = *puerto_b;
	valor_b |=  LEDS ;
	*(puerto_b) = valor_b;
}

void apargar_leds()
{
	unsigned char valor_b = *puerto_b;
	valor_b &= ~(LEDS);
	*puerto_b = valor_b;
}

void esperar_dos_seg() 
{
	 volatile unsigned long i;
	for (i=0; i<900000; i++);
}
void prender_valor(char input)
{
	unsigned char valor_b = *puerto_b;
	valor_b =  (valor_b & ~LEDS) | ((input << 3) & LEDS) ;
	*(puerto_b) = valor_b;
}
