#include <stdint.h>
#include "adc.h"

#define CHANNEL0 0x00
#define CHANNEL1 0x01
#define CHANNEL2 0x02
#define CHANNEL3 0x03
#define CHANNEL4 0x04
#define CHANNEL5 0x05
#define CHANNEL6 0x06
#define CHANNEL7 0x07

#define ADC_ENABLE 0x80
#define ADC_START_CONVERSION 0x40
#define ADC_PRESCALAR 0x07 // factor division: 128
#define ADC_V_REF 0xC0
/* Estructura de los registros */
typedef struct
{
    uint8_t adcL;    		/* The ADC Data Register Low */
    uint8_t adcH;    		/* The ADC Data Register High */
    uint8_t adcSRA;    	/* ADC Control and Status Register A */
    uint8_t adcSRB;    	/* ADC Control and Status Register B */
    uint8_t adMUX;      /* ADC Multiplexer Selection Register */
    uint8_t _reserved;	/* espacio sin utilizar */
    uint8_t didR0;			/* Digital Input Disable */
} volatile adc_t;

/* puntero a la estructura de los registros del periferico */
adc_t *puntero_adc = (adc_t *) (0x78);

void adc_init()
{
	/* Rutina de inicializacion*/
	/* Selecciono Voltaje de referencia interno */
	puntero_adc -> adMUX = (unsigned char) ADC_V_REF;
	/* Activo el conversor y seteo el factor de division */
	puntero_adc -> adcSRA = (unsigned char) (ADC_ENABLE + ADC_PRESCALAR);


}


int adc_getData(void)
{
	/*	Obtencion de los datos de los registros L y H del adc	*/
			int dato;

			/*	Selecciono el canal de entrada de donde el adc recive Input	*/
			puntero_adc -> adMUX |= (unsigned char) CHANNEL0;

			/*	Activar la conversion del adc */
			puntero_adc -> adcSRA |= (unsigned char) ADC_START_CONVERSION;

	    while( !((puntero_adc -> adcSRA) & (ADC_START_CONVERSION)) );

			/* Ya termino la conversion, puedo leer	*/

			/*	Cuando se lee el ADCL el registro de datos del ADC no se actualiza
				hasta que se lee el ADCH, por lo tanto leo primero L y luego H*/
			dato = puntero_adc -> adcL;  //	Leo 8 bits

			dato += (puntero_adc -> adcH << 8); // Leo los 2 primeros bits para completar 10


	    /* DEBE devolver el valor que se encuentra en el registro de datos de E/S */
	    return (dato);
  }
