
/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p 
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
    uint8_t status_control_a; /* ucsr0a USART Control and Status A */
    uint8_t status_control_b;
    uint8_t status_control_c;
    uint8_t _reserved;
    uint8_t baud_rate_l;
    uint8_t baud_rate_h;
    uint8_t data_es; /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *)(0xc0);

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define READY_TO_WRITE 0x20
#define READY_TO_READ 0x80

void serial_init()
{
    //RXEN0 bit 4    0x10  #define RECEIVER_ENABLE 0x10
    //TXEN0 bit 3	 0x08

    /* Set baud rate*/
    puerto_serial->baud_rate_h = (1 >> 8);
    puerto_serial->baud_rate_l = BAUD_PRESCALE;

    /* Enable receiver and transmitter */
    puerto_serial->status_control_b |= (0x10 | 0x08);

    /* Set frame format: 8data, 2stop bit */
    puerto_serial->status_control_c |= 0x03;
}

/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char(char c)
{
    /* Wait until the transmitter is ready for the next character. */

    /* completar con E/S programada */
    /* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       hasta que el buffer esté listo para recibir un dato a transmitir */

    // while ( /* completar con E/S programada */ )
    //     ;

    /* Send the character via the serial port. */
    /* (escribir el dato al registro de datos de E/S */

    while (!(puerto_serial->status_control_a & READY_TO_WRITE))
        ;

    puerto_serial->data_es = c;
}

char serial_get_char(void)
{
    /* Wait for the next character to arrive. */
    /* Completar con E/S programada similar a serial_put_char pero 
       utilizando el bit correcto */

    while (!(puerto_serial->status_control_a & READY_TO_READ))
        ;
    return puerto_serial->data_es;
}

void serial_put_str(char *str)
{
    while (*str)
    {
        serial_put_char(*str);
        str++;
    }

    serial_put_char('\r');
    serial_put_char('\n');
}
