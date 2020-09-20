/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "utils.h"
#include "adc.h"

int main(void)
{

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

    int v;
    while (1)
    {
        v = get_adc();
        serial_put_char(v);
    }

    for (;;)
        ;

    return 0;
}
