#include <stdint.h>

#define ADC_ENABLE 0x80
#define ADC_START_CONVERSION 0x40
#define ADC_AUTO_TRIGGER 0x20

//#define ADMUX (0x80 | 0x40)

typedef struct
{
    uint8_t adcl;
    uint8_t adch;
    uint8_t adcsra;
    uint8_t adcsrb;
    uint8_t admux;
    uint8_t reserved;
    uint8_t didr0;

} volatile adc_t;

volatile adc_t *adc = (adc_t *)0x78;

void adc_init()
{
    //adc->adcsra |= ADC_ENABLE | ADC_START_CONVERSION | ADC_AUTO_TRIGGER;
    /*
    agregar 0x20 para freerunning
    ADPS2...ADPS0 controla el division factor

    IMPORTANTE: Supongo que si activo el freerunning no tengo en el metodo
    "adc_get() que usar ADC_START_CONVERSION ya que lo haría en este mismo
    metodo cuando utilizo ADC_ENABLE"  
    */
    adc->adcsra |= ( 0x04 | 0x02 | 0x01); //division factor 128

    adc->admux |= ( 0x80 | 0x40); // internal 1.1v voltage reference with external capacitor at aref pin
    adc->adcsra |= ADC_ENABLE;
}

int adc_get(int input)
{
    int val = 0;

    /*
    MUX[3:0] the value of these bits selects which
     analog inputs are connected to the ADC.

    I'm using AC0 so I don't need to configure it.
    */

//    adc->adcsra |= ADC_START_CONVERSION;
//    descomentar esa linea de arriba y remover en la inicializacion cuando se usa ADC_ENABLE los otros dos macros

    adc->admux |= input;

    adc->adcsra |= ADC_START_CONVERSION;
    while (!(adc->adcsra & 0x10))
        ;
    /* cuando se completa una conversión se settea este bit */

   // val = (adc->adcl << 0x08);
   // val |= adc->adch;
    val = adc->adcl;
    val |= (adc->adch << 8);

    return val;
}
