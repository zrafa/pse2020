#include "adc.h"
#include "serial.h"
#include "utils.h"

int main(void)
{
	unsigned int val;
	adc_init();
	serial_init();
	lets_init();

	
	unsigned char tmp, intensidad;
	unsigned int divisor;
	while(1){

		
		/*obtener el valor del conversor*/
		val = adc_get(0);
		
		/*calcula la intencidad de 0 a 7*/
		intensidad = (7 - (val / 128))+48;

		/*mostrar intencidad en leds*/
   		prender_valor(intensidad);

		serial_put_char(intensidad); 
		serial_put_String("\n\r");
		
		/*convertir val en ascii y enviar*/
		divisor = 1000;	
		
		while ( divisor  > 0){
			tmp = (val / divisor)+48;
			val = val % divisor;
			serial_put_char(tmp);
			divisor = divisor / 10;
		}
	
		esperar_dos_seg();
		
		serial_put_String("\n\r");
		
		
	}

}
