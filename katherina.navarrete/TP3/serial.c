
/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion 
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <avr/io.h> /* para los tipos de datos. Ej.: uint8_t */


/*---------------------------------Registro interfaz-----------------------------*/

typedef struct
{
	uint8_t status_control_a;    /* ucsr0a USART Control and Status A */	
    	uint8_t status_control_b;    /* ucsr0b USART Control and Status B */
    	uint8_t status_control_c;    /* ucsr0c USART Control and Status C */
	uint8_t reserver;    	     /* espacio reservado */
	uint8_t baud_rate_l;         /* tasa de baudios baja */
	uint8_t baud_rate_h;         /* tasa de baudios alta */
    	uint8_t data_es;    	     /* udr0 i/o data */

} volatile uart_t;

/* puntero a la estructura de los registros del periferico */
uart_t *puerto_serial = (uart_t *) (0xc0);

/*------------------------------Rutina de Inicialización------------------------*/
#define USART_BAUDRATE 9600
//#define F_CPU 1843200
#define BAUD_PRESCALE (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define habilitarTx 0x08
#define habilitarRx 0x10

unsigned char inicializar = 0;
void serial_init() {
	if(inicializar==0){
		/* Configurar los registros High y Low con BAUD_PRESCALE */
		(*puerto_serial).baud_rate_l = (unsigned char)(BAUD_PRESCALE);
		(*puerto_serial).baud_rate_h = (unsigned char)(BAUD_PRESCALE >> 8);
		/* Configurar un frame de 8bits (bit 1 y 2 en 1), 
		   sin bit de paridad (bit 5 y 4 en 0) 
		   bit de stop (bit 3 en 0)*/
		(*puerto_serial).status_control_c = 0x06;
		/* Activar la recepcion y transmicion */
		(*puerto_serial).status_control_b = habilitarTx | habilitarRx;
		inicializar = 1;
	}
}


/* enviar un byte a traves del del dispositivo inicializado */
void serial_put_char (char outputChar)
{
 
	if(inicializar==1){
		/* Se debe esperar verificando el bit UDREn del registro UCSRnA,
       		hasta que el buffer esté listo para recibir un dato a transmitir */
		while(!((*puerto_serial).status_control_a & 0x20));
		/* (escribir el dato al registro de datos de E/S */
		(*puerto_serial).data_es = outputChar;
	}
}


char serial_get_char(void)
{
	//verificar que se realizo la inicialización
	if(inicializar==1){
		 /* Wait for the next character to arrive. */
		while(!((*puerto_serial).status_control_a & 0x80));
		/* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
		return (*puerto_serial).data_es;
	}
}



