/********************************************************************** 
* 
* main.c - the main program test file for the ADC driver
* 
**********************************************************************/ 
#include "utils.h"
#include "serial.h" 
#include "adc.h" 

#define INPUT 0 /* pin de avr ADC0 - pin de placa arduino A0*/

char convertir_a3bits(int value){
    int en_escala = value >> 7;
    char v = en_escala + 0x30;
    return v; 
}


int main(void){

    int i;

    /* Configure the UART for the serial driver */ 
    serial_init(); 

    /* Configure the UART for the adc driver*/ 
    adc_init(); 

    /* configura los pines que controlan los LEDs y el pulsador. */
	leds_init();    

    unsigned int value_10bits;
    unsigned char value_3bits;
    while (1) {
        /* valor proveniente del adc dentro del rango [0,1023] */
        value_10bits = adc_get(INPUT);
        
        /*Convierte a una escala de 0 a 7*/
        value_3bits = convertir_a3bits(value_10bits);

        binario_leds(value_3bits);
        serial_put_char(value_3bits);

    }
    return 0;
}







