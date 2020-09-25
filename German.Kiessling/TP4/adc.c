#include <stdint.h>
#include "adc.h"

/* 0b 1000 0000 - bit 7  */
#define ADC_ENABLE 0x80

// Definir una estructura que represente los registros de estado, control y datos del periférico
typedef struct
{
    uint8_t adcl; /*low*/
    uint8_t adch; /* high*/
    uint8_t adcsra; /* ADC Control and Status Register A */
    uint8_t adcsrb;
    uint8_t admux;  /* ADC Multiplexer Selection Register */
    uint8_t reserved;
    uint8_t didr0;

} volatile adc_t;

/* puntero a la estructura de los registros del periferico */
volatile adc_t *adc = (adc_t *) 0x78;

// ● Crear la rutina de inicialización (init)
// Ejemplo: Establecer los registros de control para usar la referencia interna y habilitar el periférico.
// Establecer el prescalar (divisor).
void adc_init()
{
    /* Escribir una rutina de inicializacion */

    /* Configurar los registros ADMUX y ADCSRA para utilizar el voltage de referencia interno y
        encender (habilitar) el periférico */
    
    /* Establecer el prescalar (divisor) */
    adc->admux = (unsigned char)( 0x80 + 0x40); //  1100 0000

    adc->adcsra = (unsigned char)( ADC_ENABLE + 0x04 + 0x02 + 0x01); // 1000 0111

    
}

int adc_get(char input)
{
    int val = 0;

     /* 1. establecer el multiplexor a la entrada input */
     adc->admux |= input;

     /* 2. iniciar una conversion ADC */
     adc->adcsra |= 1 << 6;

     /* 3. completar con E/S programada */
     while ( !((adc->adcsra) & (1 << 6)) );

     /* 4. devolver el valor del registro de datos del ADC (Low y High)*/
     /* IMPORTANTE: hay que leer el registro L antes del H !!! */
     val = adc->adcl;

    val += (adc->adch << 8);

    return val;
}
