/* 
 *
 * 1 segundo 1000 milisegundos
 * 1 milisegundo 1000 microsegundos
 *
 * Utilizamos modo PWM
 *
 * 16000000 ticks/s  /  1454,54 = 11000 ticks/s => 
 *
 *
 * tope = 1454
 * interrupciones = 11004 
 */

#include <avr/io.h>
#include <avr/interrupt.h>


typedef struct
{
        uint8_t tccr1a;  /* Registro de control A del timer1 */
        uint8_t tccr1b;  /* Registro de control B del timer1 */
        uint8_t tccr1c;  /* Registro de control C del timer1 */
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

#define SYSTEM_TICKS 16000000
#define PRESCALAR 1

#define TIMER1_CS 0x09     /* prescalar = 1 */
#define TIMER1_CTC 0x80    /* OC1A no invertido */

#define TIMER1_WG0 0x02    /* Fast PWM TOP ICR1 */
#define TIMER1_WG1 0x18    /* Fast PWM TOP ICR1 */

#define TIMER1_ICR1H 0x05  /* ICR1 = 1454 */
#define TIMER1_ICR1L 0xAF


void timer1_init( void )
{
        timer1->tccr1a = (TIMER1_CTC | TIMER1_WG0);
        timer1->tccr1b = (TIMER1_CS | TIMER1_WG1);

        timer1->icr1h = TIMER1_ICR1H; /* define la parte alta de TOP del contador */
        timer1->icr1l = TIMER1_ICR1L; /* define la parte baja de TOP del contador */

        (*timer1_timsk1) |= 0x01;  /* 0x01: al producirse overflow se dispara una interrupcion */ 

        timer1-> ocr1ah = 0;
        timer1-> ocr1al = 0;
}

volatile unsigned int dato_pc = 0;
#define MAX_OCR1A 150
#define MAX_PC 255

ISR(TIMER1_OVF_vect)
{
        timer1-> ocr1ah = dato_pc >> 8;
        timer1-> ocr1al = dato_pc;
        dato_pc = 0;
}

void actualizar_dato_pc(unsigned char dato)
{
        dato_pc = dato * MAX_OCR1A / MAX_PC;
}
