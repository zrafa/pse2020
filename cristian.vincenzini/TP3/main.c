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
        int i;

        /* Configure the UART for the serial driver */
        serial_init();

        /* Configure pins */
        leds_init();

        serial_put_str("Start");

        while (rcvChar != 'q') {

                /* Wait for an incoming character */
                rcvChar = serial_get_char();

                switch (rcvChar) {
                        case 'c':
                                serial_put_str("Comenzando suma binaria");
                                suma_binaria();
                                serial_put_str("Fin suma binaria");
                                break;
                        case 'k':
                                serial_put_str("Comenzando knight-rider");
                                for (i = 0; i < 10; i++) {
                                        knight_rider();
                                }
                                serial_put_str("Fin knight-rider");
                                break;
                        default:
                                /* Echo the character back along with a carriage return and line feed */
                                serial_put_char(rcvChar);
                                serial_put_char('\r');
                                serial_put_char('\n');
                                break;
                }
        }

        serial_put_str("Fin aplicacion");

        for (;;);

        return 0;
}
