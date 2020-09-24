
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
    uint8_t status_control_b;    /* ucsr0a USART Control and Status B */
    uint8_t status_control_c;
    uint8_t _reserved;/* espacio sin utilizar */
    uint8_t baud_rate_l;/* ubrr0l baud rate low */
    ;uint8_t baud_rate_h;/* ubrr0h baud rate high */
    uint8_t data_es;    /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);



#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)

/* Activar recepcion y transmicion*/
unsigned char RXEN = 0x10;
unsigned char TXEN = 0x08;
	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
  //Frames de 8bits
unsigned char UCSZn0 = 0x02;
unsigned char UCSZn1 = 0x04;
  //1 bit de paridad comienza en cero por default

  //1 bit de stop comienza en cero por default

  //Listo para escribir datos
unsigned char UDRE = 0x20;
 //Listo para ser leido;
unsigned char RXC = 0x80;

void serial_init() {
  	/* Configurar los registros High y Low con BAUD_PRESCALE */
  puerto_serial -> baud_rate_l = (unsigned char)(BAUD_PRESCALE);
  puerto_serial -> baud_rate_h = (unsigned char)(BAUD_PRESCALE>>8);

	/* Configurar un frame de 8bits, con un bit de paridad y bit de stop */
  puerto_serial -> status_control_c = (unsigned char)(UCSZn0 + UCSZn1);
	/* Activar la recepcion y transmicion */
  puerto_serial -> status_control_b = (unsigned)(RXEN + TXEN);


}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char c)
{
    while(  !(puerto_serial -> status_control_a & UDRE) ){

    }
    puerto_serial -> data_es = c;


}


char serial_get_char(void)
{
    while( !(puerto_serial -> status_control_a & RXC) ){

    }
    return (puerto_serial -> data_es);

}

void serial_put_str(char * mensaje)
{
    while (*mensaje) {
        serial_put_char(*mensaje);
        mensaje++;
    }

    serial_put_char('\r');
    serial_put_char('\n');
}
