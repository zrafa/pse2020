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

    char ascii;
    int aux;
    /* Configure the UART for the serial driver */
    serial_init();

    led_init();
    adc_init();

    serial_put_str("Inicio");

    int val;

    while (1)
    {
        val = adc_get(2); /* obtener una conversión ADC del pin de entrada ADC 2 */
        aux = val >> 7; /*( de 0 ( luz intensa ) a 7 ( sin luz )) */
        ascii =  aux + 0x30;  /* numero en ASCII */

        serial_put_char(ascii); /* salida por pantalla intesidad de la luz*/

        conteo(aux);


    }

    for (;;)
        ;

    return 0;
}