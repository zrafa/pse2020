/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "utils.h"


int main(void)
{
    char rcvChar = 0;

    /* Configure the UART for the serial driver */
    serial_init();

    led_init();

    serial_put_str("Inicio");
    serial_put_char('\r');
    serial_put_char('\n');

    while (rcvChar != 'q')
    {
        /* Wait for an incoming character */
        rcvChar = serial_get_char();

        if(rcvChar=='c'){
		     conteo();
        }else{
	        if(rcvChar=='k'){
		        prender_led();
	        }
        }

        /* Echo del caracter */
        serial_put_char(rcvChar);
        serial_put_char('\r');
        serial_put_char('\n');
    }
    serial_put_str("Fin");

    for (;;);

    return 0;
}

