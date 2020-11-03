
/* 1 segundo 1000 milisegundos
 * 1 milisegundo 1000 microsegundos
 *
 * Utilizamos modo PWM
 * reloj del sistema: 16000000 de ticks/s  /  64 (prescalar) = 250000 ticks/s
 *
 * 250000 ticks/s  /  250 = 1000 ticks/s => 
 * ICR1 = 1454, es el tope en este modo
 * interrupciones = 11000
 */

#include <avr/io.h>
#include <avr/interrupt.h>


#define TIMER1_CS 0x01 /* prescalar=1 */
#define TIMER1_COM1A 0x80 /* PIN OC1A no invertido */

#define SYSTEM_TICKS 16000000

#define TIMER1_WG0 0x02 /* Fast PWM, Top ICR1 */
#define TIMER1_WG1 0x18 /*Fast PWM, Top ICR1*/

#define TIMER1_ICR1H 0x05
#define TIMER1_ICR1L 0xAE
#define MAX_OCR1A 5
#define MAX_PC 255

typedef struct
{
    uint8_t tccr1a; /* Registro de control A del timer1 */
    uint8_t tccr1b; /* Registro de control B del timer1 */
    uint8_t tccr1c; /* Registro de control C del timer1 */
    uint8_t reserved;
    uint8_t tcnt1l;  /* Registro timer/contador parte baja*/
    uint8_t tcnt1h;  /* Registro timer/contador parte alta*/
    uint8_t icr1l;   /* Registro de captura de entrada Byte parte baja*/
    uint8_t icr1h;   /* Registro de captura de entrada Byte parte alta*/
    uint8_t ocr1al;  /* Registro comparador A parte baja*/
    uint8_t ocr1ah;  /* Registro comparador A parte alta*/
    uint8_t ocr1bl;  /* Registro comparador B parte baja*/
    uint8_t ocr1bh;  /* Registro comparador B parte alta*/

} volatile timer1_t;

volatile timer1_t *timer1 = (timer1_t *)(0x80);

/* registro mascara de interrupciones timer 1 */
volatile unsigned char *timer1_timsk1 = (unsigned char *)(0x6F);

volatile int dato_pc;


void timer1_init( void )
{
	timer1->tccr1a |= (TIMER1_COM1A | TIMER1_WG0);
	timer1->tccr1b |= (TIMER1_CS | TIMER1_WG1);
	timer1->icr1h = TIMER1_ICR1H; /* valor del tope parte alta*/
	timer1->icr1l = TIMER1_ICR1L; /* valor del tope parte baja*/
	(*timer1_timsk1) |= 0x01;  /* 0x01:  Al producirse overflow se dispara una interrupción */
	timer1->ocr1ah = 0;
	timer1->ocr1al = 0;
}

ISR(TIMER1_OVF_vect)
{
	timer1->ocr1ah = dato_pc >> 8;
	timer1->ocr1al = dato_pc;

	dato_pc = 0;
}

void actualizar_dato_PC(char dato)
{
	dato_pc = dato*MAX_OCR1A/MAX_PC;
}

