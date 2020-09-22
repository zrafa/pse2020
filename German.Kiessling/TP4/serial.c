
/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */


/* Completar la estructura de datos para que se superponga a los registros
   del periferico de hardware del USART del atmega328, segun sugerido
   en el apunte */

typedef struct
{
    uint8_t status_control_a;    /* ucsr0a USART Control and Status A */
    uint8_t status_control_b;    /* ucsr0b USART Control and Status B */
    uint8_t status_control_c;    /* ucsr0c USART Control and Status C */
    uint8_t _reserved;           /* espacio sin utilizar */
    uint8_t baud_rate_l;         /* ubrr0l baud rate low */
    uint8_t baud_rate_h;         /* ubrr0h baud rate high */ 
    uint8_t data_es;             /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);



#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

unsigned char control_inicio = 0; // 0 no / 1 si

void serial_init() {

	/* Escribir una rutina de inicializacion */

	/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y
           la estructura de datos */
	if(control_inicio == 0) {
		/* Configurar los registros High y Low con BAUD_PRESCALE */
		(*puerto_serial).baud_rate_l = (unsigned char) BAUD_PRESCALE;
		(*puerto_serial).baud_rate_h = (unsigned char) (BAUD_PRESCALE>>8);
		/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
		(*puerto_serial).status_control_c = 0x06;
		/* Activar la recepcion y transmicion */
		(*puerto_serial).status_control_b = 0x18;
		control_inicio = 1;
	}

}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char c)
{
    while( !((puerto_serial -> status_control_a) & (0x20)) );
    puerto_serial -> data_es = c;

}


char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */
    while ( !((*puerto_serial).status_control_a & 0x80) ); 

    /* valor registro de datos de E/S */
    return (puerto_serial -> data_es);
}

void serial_put_str(char * string)
{
    while (*string) {
        serial_put_char(*string);
        string++;
    }

    serial_put_char('\r');
    serial_put_char('\n');
}
