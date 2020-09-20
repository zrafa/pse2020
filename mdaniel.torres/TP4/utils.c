
/* utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

/* puertos de E/S */
volatile unsigned char *puerto_b = (unsigned char *)0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char *ddr_b = (unsigned char *)0x24;	  /* direccion de DDR B (registro de control) */
volatile unsigned char *pin_b = (unsigned char *)0x23;	  /* direccion PIN B (registro de datos)*/

/* 0x28 0x27 0x26 puerto_c ddr_c pin_c */

/* 
 * Configuración: Establecer el 5to bit del puerto B como entrada
 *
 * 	Poner en '0' el 5to bit de la dirección 0x24, que 
 * 	es el la dirección del registro de control
 *	(direccion de los datos) del puerto B (DDRB - Data Direction Register).
 *      El 5to bit define la entrada o salida del
 * 	pin del atmega328p que tiene conectado un led en una board arduino
 */

void esperar(unsigned long multiplier)
{
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i = 0; i < 6000 * multiplier; i++)
		;
}

void led_init()
{
	volatile unsigned char *DDR_B = 0x24;
	volatile unsigned char *PUERTO_B = 0x25;

	//primero
	*(PUERTO_B) = *(PUERTO_B) & (~0x02);

	*(DDR_B) = *(DDR_B) | (0x02);

	//segundo

	*(PUERTO_B) = *(PUERTO_B) & (~0x04);

	*(DDR_B) = *(DDR_B) | (0x04);

	//tercero
	*(PUERTO_B) = *(PUERTO_B) & (~0x08);

	*(DDR_B) = *(DDR_B) | (0x08);
}

void contador()
{
	unsigned char *PUERTO_B = 0x25;

	esperar(30);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
	esperar(30);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
	esperar(30);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
	esperar(30);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x08);
	esperar(30);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
	esperar(30);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
	esperar(30);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
	esperar(30);
	led_init();
}

void suma_binaria(int num)
{
	unsigned char *PUERTO_B = 0x25;

	switch (num)
	{
	case 1:
		*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
		esperar(130);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
		break;

	case 2:
		*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
		esperar(130);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
		break;

	case 3:
		*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
		esperar(130);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
		break;

	case 4:
		*(PUERTO_B) = *(PUERTO_B) ^ (0x08);
		esperar(130);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x08);
		break;

	case 5:
		*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x08);
		esperar(130);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x08);
		break;

	case 6:
		*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x08);
		esperar(130);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x08);
		break;

	case 7:
		*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x08);
		esperar(130);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
		*(PUERTO_B) = *(PUERTO_B) ^ (0x08);
	}
}
