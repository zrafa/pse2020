#include "adc.h"
#include "serial.h"

int main(void)
{
	unsigned int val;
	adc_init();
	serial_init();
	unsigned char tmp;
	unsigned int divisor;
	while(1){

		serial_put_String("esperando lectura\n\r");
		/*obtener el valor del conversor*/
		val = adc_get(0);

		/*convertir val en ascii*/
		divisor = 1000;		
		while ( divisor  > 0){
			tmp = (val / divisor)+48;
			val = val % divisor;
			serial_put_char(tmp);
			divisor = divisor / 10;
		}
		esperar();
	}

	return 0;
}
