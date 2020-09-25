#include <stdint.h> /* para los tipos de datos. Ej.: uint8_t */



typedef struct{

	uint8_t adc_l;    	
    	uint8_t adc_h;    
    	uint8_t adc_sra;    
	uint8_t adc_srb;    	     
	uint8_t adc_mux;         
	uint8_t reserved;         
    	uint8_t didr0;    

} volatile adc_t;

volatile adc_t *adc = (adc_t *) (0x78);

#define REFS1 0x07 
#define REFS0 0x06 

#define ADEN 0x07
#define ADPS2 0x02
#define ADPS1 0x01
#define ADPS0 0x00

void adc_init()
{
	adc -> adc_mux = (1 << REFS1) | (1 << REFS0);
	adc -> adc_sra = (1 << ADEN) | (1 << ADPS2) |(1 << ADPS1) | (1 << ADPS0) ;
}

#define activa_bits_7_al_3 0xF8
#define activa_bits_2_al_0 0x07

#define ADSC 0x06
int adc_get(char input)
{
	int val;

	/*Selecciona el canal*/
	uint8_t tmp = adc -> adc_mux;
	adc -> adc_mux = (tmp & activa_bits_7_al_3) | (input & activa_bits_2_al_0);

	/*Iniciar la conversión */
	adc -> adc_sra |= (1 << ADSC);

	/*Esperar hasta que termine de realizar la conversión */
	while(((adc -> adc_sra) & (1 << ADSC))!= 0);

	val = adc -> adc_l;
	val |= ((adc -> adc_h) << 8);
	
	return val;
}


