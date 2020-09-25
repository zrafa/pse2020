#include "adc.h"
#include "serial.h"
#include "utils.h"

int main(void)
{
	unsigned int val;
	unsigned char intensidad;
	adc_init();
	serial_init();
	/*unsigned char tmp;
	unsigned int divisor; */
	while(1){

		/*serial_put_String("esperando lectura\n\r"); */
		/*obtener el valor del conversor*/
		val = adc_get(0);
		intensidad = 7-(val/128);
		serial_put_char(intensidad);
		let_init();
		prender_led(intensidad);
		esperar();
		
	}

	return 0;
}
