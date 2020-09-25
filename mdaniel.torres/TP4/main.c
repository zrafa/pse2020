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
    adc_init();

    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
    serial_put_char('\r');
    serial_put_char('\n');

    int v = 0;
    while (1)
    {
        v = adc_get(0);
        evaluate(v);
	char buf[5]="";
	sprintf(buf, "%d", v);
        serial_put_str(buf);

    }

    for (;;)
        ;

    return 0;
}

void evaluate(int v)
{
    if (v < 128)
    {
        return;
    }

    if (v < 256)
    {
        suma_binaria(1);
        return;
    }

    if (v < 384)
    {
        suma_binaria(2);
        return;
    }

    if (v < 512)
    {
        suma_binaria(3);
        return;
    }

    if (v < 640)
    {
        suma_binaria(4);
        return;
    }

    if (v < 768)
    {
        suma_binaria(5);
        return;
    }

    if (v < 896)
    {
        suma_binaria(6);
        return;
    }

    if (v < 1024)
    {
        suma_binaria(7);
        return;
    }
}
