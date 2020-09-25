/********************************************************************** 
* 
* adc.c - Driver del ACD del atmega328p
* 
* META : ocultar el hardware a la aplicacion 
*
* Configuracion:  
* 
**********************************************************************/ 

#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */


/* Paso 1: overlay*/

/* Estructura de datos (adc_t) que se superpone a los registros del periferico
 * de hardware del Analog-to-Digital Converter del atmega328. 
 * La estructura comienza de la dirección más baja */
typedef struct
{
    uint8_t adcl;       /* ADC Data Register Low byte */
    uint8_t adch;       /* ADC Data Register High byte */
    uint8_t adcsra;     /* ADC Control and Status Register A */
    uint8_t adcsrb;     /* ADC Control and Status Register B */
    uint8_t admux;      /* ADC Multiplexer Selection Register */

    uint8_t _reserved;  /* espacio sin utilizar */

    uint8_t didr0;      /* Digital Input Disable Register 0 */     

}volatile adc_t; 

/* puntero a la estructura de los registros del periferico */
volatile adc_t *adc = (adc_t *) (0x78);



/*
 *La combinacion de los bits 0 (MUX0), el bit 1 (MUX0), el bit 2 (MUX2) y el bit 3
 *(MUX3) del registro ADMUX en cero seleccionan el canal de entrada de la señal
 *analogica.
 *pin de avr ADC0
 *pin de placa arduino A0
 */
#define INPUT_CHANNEL 0x0 /* 0b 0000 0000  bit 0, bit 1 bit 2 y bit 3*/

/*
 *La combinacion de los bits 7 (REFS1) y el bit 6 (REFS0) del registro ADMUX en uno
 *selecciona el voltaje de referencia interno del ADC.
 */
#define  VOLT_REF 0xC0 /* 0b 1100 0000  bit 7 y bit 6*/

/*
 *El bit 5 (ADLAR) del registro ADMUX en cero selecciona la presentacion del
 *resultado de la conversion en 10bits de resolucion.
 */
#define RIGHT_ADJUST 0x0 /* 0b 0000 0000  bit 5*/




/*
 * El bit 7 (ADEN) de registro ADCSRA en uno habilita el ADC.
 */
#define EN_ADC 0x80 /* 0b 1000 0000  bit 7 */

/*
 *La combinacion de los bits 0 (ADPS0), el bit 1 (ADPS1) y el bit 2 (ADPS2) del
 *registro ADCSRA en uno seleccionan el factor de division 128 entre la frecuencia
 *del reloj del sistema y del reloj del ADC.
 */
#define DIVFACTOR_128 0x07 /* 0b 0000 0111  bit 0, bit 1 y bit 2 */


/*
 * El bit 6 (ADSC) de registro ADCSRA en uno selecciona el modo single conversion.
 */
#define MODO_CONV 0x40 /* 0b 0100 0000  bit 6*/




/* Paso 3: Rutina de inicializacion */
void adc_init() { 	

    adc->admux = (unsigned char) (VOLT_REF | INPUT_CHANNEL | RIGHT_ADJUST);
    adc->adcsra= (unsigned char) ( EN_ADC | DIVFACTOR_128);


}



/* Paso 4: API del controlador de dispositivo */


/*
 * Devuelve un valor de 10 bits de la conversion ADC entrada input
 */
int adc_get(char input){

    int val;

    /* 1 establecer el multiplexor a la entrada input */
    adc->admux |= input;
    /* 2 iniciar una conversion ADC */
    adc->adcsra |= MODO_CONV;
    /* 3 completar con E/S programada */
    while(!((adc->adcsra) & MODO_CONV));

    /* 4 devolver el valor del registro de datos del ADC (Low y High) */

    /* Primero debe leerse ADCL, luego ADCH, para asegurarse de que el contenido de
     * los registros de datos pertenece a la misma conversión.
     * Una vez que se lee ADCL, se bloquea el acceso de ADC a los registros de
     * datos. Esto significa que si ADCL ha sido leido, y se completa una
     * conversión antes de que se lea ADCH, ninguno de los registros se actualiza y
     * el resultado de la conversión se pierde. Cuando se lee ADCH, se vuelve a
     * habilitar el acceso de ADC a los registros ADCH y ADCL.
     */

    val = (adc->adcl);
    val += (adc->adch << 8);
    return val;

}


