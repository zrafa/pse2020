
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/*
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los
 * pines 8-13 de arduino
 */

#include "utils.h"
#include <stdbool.h>
int main(void)
{
	init();

	while(1){
		if(boton()==1){
			suma();
		}else{
			prender_led();
			esperar1();
			apagar_led();
			esperar1();
		}
	}
}
