#include "serial.h"
#include "utils.h"
#include "adc.h"

unsigned char se_presiono_boton = 0;

int main(void)
{
        char ascii_value;
        int readADC;
        int scale;

        serial_init();
        leds_init();
        adc_init();

        serial_put_str("Start");

        while (1) {
                readADC = adc_get(0);
                scale = readADC >> 7;        /* valores entre 0 y 8 */
                ascii_value = scale + 0x30;  /* numero en ASCII */

                serial_put_char(ascii_value);
                encendido_binario(ascii_value);

                //se_presiono_boton = leer_boton();
                //serial_get_char();
        }

        return 0;
}
