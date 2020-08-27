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
    let_init();
    /* Configure the UART for the serial driver */
    serial_init();
    //transmite los caracteres
    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
    serial_put_char('\r');
    serial_put_char('\n');
    serial_put_char('h');
    serial_put_char('o');
    serial_put_char('l');
    serial_put_char('a');
    serial_put_char(' ');
    serial_put_char('k');
    serial_put_char('a');
    serial_put_char('t');
    serial_put_char('y');
    serial_put_char('\r');
    serial_put_char('\n');

    while (rcvChar != 'q')
    {
        /* Esperar un caracter entrante */
       rcvChar = serial_get_char();

        /* Hacer eco del caracter*/
        serial_put_char(rcvChar);
	if(rcvChar=='c')
		contarBin();
	else{
		if(rcvChar=='k'){
			knight_rider();
			knight_rider();
			knight_rider();
		}
	}
    }
	/* hacer un salto de linea */
	serial_put_char('\r');
        serial_put_char('\n');
 	/*transmitir los caracteres*/
	serial_put_char('f');
    	serial_put_char('i');
    	serial_put_char('n');
        serial_put_char('\r');
    	serial_put_char('\n');
        

    for (;;);

    return 0;
}

