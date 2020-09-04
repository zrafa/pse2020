/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "utils.h"

int main(void)
{
	char rcv_char = 0;
	lets_init();

    	/* Configure the UART for the serial driver */
    	serial_init();

    	serial_put_String("hola katy\n\r");

    	while (rcv_char != 'q') {

		rcv_char = serial_get_char();
		serial_put_char(rcv_char);

		switch (rcv_char) {

			case 'c' : 
				contar_binario();
				break;

			case 'k' :
				knight_rider();
				knight_rider();
				knight_rider();
				break;
		}
	}
	for (;;);

    return 0;
}

