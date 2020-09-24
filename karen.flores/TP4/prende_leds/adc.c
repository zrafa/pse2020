#include <stdint.h>

typedef struct
{
 uint8_t adcl;
 uint8_t adch;
 uint8_t adcsra; /* ADC Control and Status Register A */
 uint8_t adcsrb;
 uint8_t admux; /* ADC Multiplexer Selection Register */
 uint8_t reserved;
 uint8_t didr0;
} volatile adc_t;

/* puntero a la estructura de los registros del periferico */
volatile adc_t * adc = (adc_t *) (0x78);

/* bits de los registros admux y adcsra */
#define REFS1 0X07
#define REFS0 0X06

#define ADEN 0X07
#define ADSC 0X06
#define ADPS2 0X02
#define ADPS1 0X01
#define ADPS0 0X00

/*variables extra*/
#define activa_bit_2_al_0 0x07
#define activa_bit_7_al_3 0xF8

void adc_init() 
{
	adc->admux = (1 << REFS1) | (1 << REFS0);
	adc->adcsra = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

int adc_get(char input)
{
	int val;
	/* 1. establecer el multiplexor a la entrada input */
	adc->admux = ((adc->admux) & activa_bit_7_al_3) | (input & activa_bit_2_al_0);
 	/* 2. iniciar una conversion ADC */
	adc->adcsra |= (1 << ADSC);
 	/* 3. completar con E/S programada */
	while(((adc->adcsra) & (1 << ADSC))!=0);
	/* 4. devolver el valor del registro de datos del ADC (Low y High)*/
	val = adc->adcl;
	val |= ((adc->adch) << 8);
	/* IMPORTANTE: hay que leer el registro L antes del H !!! */
	return val;
}
