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
    int dato;
    int rango_0_a_8;
    char valor_ascii;
    char valor_ascii2;
    int valor;

    /* Configuro el UART */
    serial_init();

    /* Configuro los pines de los leds */
    init();

    /* Configuro el adc */
    adc_init();

    serial_put_str("Arranca");

    while (1)
    {

      dato = adc_getData();
      rango_0_a_8 = dato >> 7;
      valor_ascii = rango_0_a_8 + 0x30;
      valor = (rango_0_a_8 % 4);
      valor_ascii2 = valor + 0x30;



      //prender(valor_ascii);   /*  Indica niveles de luz en binario del*/
      //serial_put_char(ascii); /*  0 al 7 en leds*/

      prender_led_valor(valor); /* Indica niveles de luz en leds del 1 al 3*/
      serial_put_char(valor_ascii2);



    }

    serial_put_str("Fin aplicacion");

    for (;;);

    return 0;
}
