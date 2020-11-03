#include <avr/io.h>
#include <avr/interrupt.h>


#define TIMER0_CS 0x03 /* prescalar=64 CS02|CS01|CS00 = 0b011 */
#define TIMER0_CTC 0x02 /* CTC = WGM = 0b010 : modo CTC es comparar y volver a cero*/

#define SYSTEM_TICKS 16000000
#define PRESCALAR 64
#define TICKS_PER_SECOND 1000

#define TIMER0_OCR0A (SYSTEM_TICKS/PRESCALAR/TICKS_PER_SECOND)


typedef struct
{
    uint8_t tccr0a; /* Registro de control A del timer0 */
    uint8_t tccr0b; /* Registro de control B del timer0 */
    uint8_t tcnt0;  /* Registro timer/contador */
    uint8_t ocr0a;  /* Registro comparador A */
    uint8_t ocr0b;  /* Registro comparador B */

} volatile timer0_t;

volatile timer0_t *timer0 = (timer0_t *)(0x44);

/* registro mascara de interrupciones timer 0 */
volatile unsigned char *timer0_timsk0 = (unsigned char *)(0x6E);

volatile int ticks;
unsigned char anio = 0;
unsigned char mes = 0;
unsigned char dia = 0;
unsigned char hora = 0;
unsigned char min = 0;
unsigned char seg = 0;
unsigned char dec = 0;

void timer0_init( void )
{
	timer0->tccr0a |= TIMER0_CTC;
	timer0->tccr0b |= TIMER0_CS;
	timer0->ocr0a = TIMER0_OCR0A; /* valor contra el cual comparar */
	(*timer0_timsk0) |= 0x02;  /* 0x02: compara contra registro OCR0A 
				      y genera interrupcion si hay un match */
	ticks = 0;
}

ISR(TIMER0_COMPA_vect)
{
    	ticks ++;
    	if (ticks == 100) {
		ticks = 0; 
		dec++;
		if(dec == 10){
			dec = 0;
			seg++;
			if(seg == 60){
				seg = 0;
				min++;
				if(min == 60){
					min = 0;
					hora++;
				
					if(hora == 24){
						hora = 0;
						dia++;
						cont_dias(dia);
					}					
				}
			}
		}

	}
}

void cont_dias(int dia)
{
	if(dia == 32 | (dia == 31 && (mes == 4 | mes == 6 | mes == 9 | mes == 11)) | 
		(mes == 2 && dia == 29) | (mes == 2 && dia == 30) ){

		dia == 1;
		mes++;
		if(mes == 13){
			mes = 1;
			anio++;
		}
	} 
}

char timer0_rtc_get_tos()
{
	return dec;
}

char dig_ASCII(int valor, int div)
{
	return ((valor / div)+48);
}

void timer0_rtc_to_str(char buffer[])
{
	buffer[0] = dig_ASCII(hora,10);
	buffer[1] = dig_ASCII(hora % 10,1);
	buffer[2] = ':';
	buffer[3] = dig_ASCII(min,10);
	buffer[4] = dig_ASCII(min % 10,1);
	buffer[5] = ':';
	buffer[6] = dig_ASCII(seg,10);
	buffer[7] = dig_ASCII(seg % 10,1);;
	buffer[8] = '.';
	buffer[9] = dig_ASCII(dec,10);
	buffer[10] = dig_ASCII(dec % 10,1);
	buffer[11] = '	';
	buffer[12] = dig_ASCII(dia,10);
	buffer[13] = dig_ASCII(dia % 10,1);
	buffer[14] = '/';
	buffer[15] = dig_ASCII(mes,10);
	buffer[16] = dig_ASCII(mes % 10,1);
	buffer[17] = '/';
	buffer[18] = dig_ASCII(anio,1000);
	buffer[19] = dig_ASCII(anio % 1000,100);
	buffer[20] = dig_ASCII(anio % 100,10);
	buffer[21] = dig_ASCII(anio % 10,1);
	buffer[22] = '\0';
	
	
}

int cant_ticks()
{
	return ticks;
}

