
/* timer0/counter de 8bits: ejemplo que genera 1000 interrupciones por segundo.
 *
 * 1 segundo 1000 milisegundos
 * 1 milisegundo 1000 microsegundos
 *
 * Utilizamos modo CTC, el cual compara con TOP. TOP es definido por OCR0A. 
 * Cuando CONTADOR == TOP el CONTADOR se pone a cero.
 *
 * reloj del sistema: 16000000 de ticks/s  /  64 (prescalar) = 250000 ticks/s
 *
 * 250000 ticks/s  /  250 = 1000 ticks/s => 
 */

#include <avr/io.h>
#include <avr/interrupt.h>


#define TIMER0_CS 0x03  /* prescalar=64 CS02|CS01|CS00 = 0b011 */
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
unsigned int anio = 2021;
unsigned char mes = 5;
unsigned char dia = 31;
unsigned char hora = 0;
unsigned char min = 0;
unsigned char seg = 0;
unsigned char dec = 0;


void timer0_init( void )
{
        timer0->tccr0a |= TIMER0_CTC;
        timer0->tccr0b |= TIMER0_CS;
        timer0->ocr0a   = TIMER0_OCR0A; /* valor contra el cual comparar */
        *timer0_timsk0 |= 0x02;         /* 0x02: compara contra registro OCR0A 
                                           y genera interrupcion si hay un match */
        ticks = 0;
}

void incrementar_mes()
{
        mes++;
        if (mes == 13) {
                mes = 0;
                anio++;
        }
}

void incrementar_dia()
{
        dia++;
        if ( dia == 32
             | (dia == 31 & (mes == 4 | mes == 6 | mes == 9 | mes == 11)) 
             | (dia == 29 & (mes == 2))) {
             
                dia = 0;
                incrementar_mes();
        }	
}

void incrementar_hora()
{
        hora++;
        if (hora == 24) {
                hora = 0;
                incrementar_dia();
        }
}

void incrementar_min()
{
        min++;
        if (min == 60) {
                min = 0;
                incrementar_hora();
        }
}

void incrementar_seg()
{
        seg++;
        if (seg == 60) {
                seg = 0;
                incrementar_min();
        }
}

void incrementar_dec()
{
        dec++;
        if (dec == 10) {
                dec = 0;
                incrementar_seg();
        }
}

ISR(TIMER0_COMPA_vect)
{
    	ticks ++;
    	if (ticks == 100) {
                ticks = 0; 
                incrementar_dec();
        }
}

char timer0_rtc_get_tos()
{
        return dec;
}

char dig_ASCII(int valor, int div)
{
        return ((valor / div) + '0');
}

void timer0_rtc_to_str(char buffer[])
{
        buffer[0]  = dig_ASCII(hora, 10);
        buffer[1]  = dig_ASCII(hora % 10, 1);
        buffer[2]  = ':';
        buffer[3]  = dig_ASCII(min, 10);
        buffer[4]  = dig_ASCII(min % 10, 1);
        buffer[5]  = ':';
        buffer[6]  = dig_ASCII(seg, 10);
        buffer[7]  = dig_ASCII(seg % 10, 1);;
        buffer[8]  = '.';
        buffer[9]  = dig_ASCII(dec, 10);
        buffer[10] = dig_ASCII(dec % 10, 1);
        buffer[11] = '\t';
        buffer[12] = dig_ASCII(dia, 10);
        buffer[13] = dig_ASCII(dia % 10, 1);
        buffer[14] = '/';
        buffer[15] = dig_ASCII(mes, 10);
        buffer[16] = dig_ASCII(mes % 10, 1);
        buffer[17] = '/';
        buffer[18] = dig_ASCII(anio, 1000);
        buffer[19] = dig_ASCII(anio % 1000, 100);
        buffer[20] = dig_ASCII(anio % 100, 10);
        buffer[21] = dig_ASCII(anio % 10, 1);
        buffer[22] = '\0';
}

int cant_ticks()
{
        return ticks;
}
