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


/* Paso 1: overlay*/

/* Estructura de datos (uart_t) que se superpone a los registros del periferico
 * de hardware del USART del atmega328. La estructura comienza de la dirección más baja */
typedef struct
{
    uint8_t status_control_a;   /* ucsr0a USART Control and Status A */
    uint8_t status_control_b;   /* ucsr0b USART Control and Status B */
    uint8_t status_control_c;   /* ucsr0c USART Control and Status C */

    uint8_t _reserved;          /* espacio sin utilizar */

    uint8_t baud_rate_l;        /* ubrr0l baud rate low */
    uint8_t baud_rate_h;        /* ubrr0h baud rate high */
    uint8_t data_es;            /* udr0 i/o data */ 

}volatile uart_t; 

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);



#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1) /* F_CPU y 16UL de donde se obtienen*/



/*
 *La combinacion de los bits 1 (UCSZn0) y el bit 2 (UCSZn1) del registro UCSRnC en
 *uno más el bit 2 (UCSZn2) del registro UCSRnB en cero configuran el frame de
 *8bits.
 *
 *El bit 3 (USBSn) del registro UCSRnC en cero para configurar como 1 bit de stop.
 *
 *La combinacion de los bits 5 (UPMn1) y el bit 4 (UPMn0) del registro UCSRnC en
 *cero desabilita el bit de paridad.
 *
 */
#define CHARACTER_SIZE 0x06 /* 0b 0000 0110  bit 1 y bit 2 */




/*
 * El bit 4 (RXENn) de registro UCSRnB en uno habilita la recepcion.
 * El bit 3 (TXENn) de registro UCSRnB en uno habilita la transmicion.
 */
#define EN_RX_TX 0x18 /* 0b 0001 1000  bit 3 y bit 4*/




/* El bit 5 (UDREn) del registro UCSRnA en uno indica el buffer vacio listo para escribir */
#define READY_TO_WRITE 0x20  /* 0b 0010 0000  bit 5 */


/* El bit 7 (RXCn) del registro UCSRnA en uno indica que el dato está listo para leer */
#define READY_TO_READ 0x80 /* 0b 1000 0000  bit 7 */



/* Paso 3: Rutina de inicializacion */
/* El manual del atmega328p tiene un ejemplo. Adecuarla a C y la estructura de datos */ 
void serial_init() { 	

    /* Set baud rate */
    /* Configurar los registros High y Low con BAUD_PRESCALE */	
    puerto_serial->baud_rate_h = (unsigned char) (BAUD_PRESCALE>>8);
    puerto_serial->baud_rate_l = (unsigned char) (BAUD_PRESCALE);

    /* Configurar un frame de 8bits, sin bit de paridad y bit de stop */
    puerto_serial->status_control_c = (unsigned char) (CHARACTER_SIZE);

    /* Configurar la recepcion y transmicion */
    puerto_serial->status_control_b = (unsigned char) (EN_RX_TX);


}



/* Paso 4: API del controlador de dispositivo */

/*
 * La función serial_put_char debe esperar hasta el que hardware transmisor
 * del periférico esté listo, y luego envía un caracter individual (un byte) a
 * través del puerto serial (E/S programada). La transmisión es realizada al
 * escribir el dato al registro de datos del USART.
 */

void serial_put_char (char c){ 

    /* Se debe esperar verificando el bit UDREn del registro UCSRnA, hasta que el
     * buffer esté listo para recibir un dato a transmitir */
    while ( !((puerto_serial->status_control_a) & (READY_TO_WRITE)));

    /* Send the character via the serial port. */
    /* escribir el dato al registro de datos de E/S */ 
    (puerto_serial->data_es)= c;

} 


/*
 * La función serial_get_char debe esperar hasta que un caracter es recibido, y
 * luego es posible leer el mismo desde el registro de datos del puerto serial.
 */
char serial_get_char(void){

    /* Para determinar si un caracter ha sido recibido se debe verificar el bit
     * data ready, del registro de estado del USART */
    while(!((puerto_serial->status_control_a) & (READY_TO_READ)));

    /* lee el valor que se encuentra en el registro de datos de E/S */
    return (puerto_serial->data_es);

}
