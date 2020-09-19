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

    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
    serial_put_char('\r');
    serial_put_char('\n');

    while (rcvChar != 'q')
    {
	    serial_init();
	    led_init();
        rcvChar = serial_get_char();

	switch (rcvChar) {
            case 'c':
             
                contador();
       
                break;
            case 'k':
                
                for (int i = 0; i < 10; i++) {
                    knight_rider();
                }
                
                break;
            default:
                
                serial_put_char(rcvChar);
                serial_put_char('\r');
                serial_put_char('\n');
                break;
        }
    }


    for (;;);

    return 0;
}

