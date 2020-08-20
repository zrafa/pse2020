/* utils.c - implementacion de funciones utiles al TP2 */

#include "utils.h" 

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los * pines 8-13 de arduino 
 */
#define MASK0 (0x01) /* 0b 0000 0001 mascara para controlar el bit 0 */
#define MASK1 (0x02) /* 0b 0000 0010 mascara para controlar el bit 1 */
#define MASK2 (0x04) /* 0b 0000 0100 mascara para controlar el bit 2 */

#define MASK4 (0x10) /* 0b 0001 0000 mascara para controlar el bit 4  */



/* puertos de E/S */
volatile unsigned char * PORTB = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * DDRB = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * PINB = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/ 


/* funciones */ 

void init(void){	

    /* LEDS */
    // el voltage de salida de los pines GPIO es establecido a cero	
    *(PORTB) &= ( ~MASK0 | ~MASK1 | ~ MASK2 ); 	
    // Configura que los pines GPIO se utilice como SALIDA a traves del registro DDRB	
    *(DDRB) |= ( MASK0 | MASK1 | MASK2 );	

    /* PULSADOR */
    // el voltage del pin GPIO es establecido a uno. PULL-UP
    *(PORTB) |= MASK4; 
    // Configura que el pin GPIO se utilice como ENTRADA a traves del registro DDRB	
    *(DDRB) &= ~MASK4; 
    	    
}


void esperar(unsigned long n){	
    volatile unsigned long i; 	
    /* delay de 1 segundo */	
    for (i = 0; i < 450000 * n; i++);
} 



void contador(){

    // el voltage de salida de los pines GPIO es establecido a cero	    
    *(PORTB) &= ( ~MASK0 & ~MASK1 &  ~MASK2);
    esperar(1);
    *(PORTB) ^= MASK0;
    esperar(1);
    *(PORTB) ^= ( MASK0 | MASK1 );
    esperar(1);
    *(PORTB) ^= MASK0;
    esperar(1);
    *(PORTB) ^= ( MASK0 | MASK1 | MASK2);
    esperar(1);
    *(PORTB) ^= MASK0;
    esperar(1);
    *(PORTB) ^= ( MASK0 | MASK1 );
    esperar(1);
    *(PORTB) ^= MASK0;
    esperar(1);
    
   
} 


void parpadeo(){	

    *(PORTB) &= ( ~MASK0 | ~MASK1 | ~ MASK2 ); 	
	*(PORTB)^= ( MASK0 | MASK1 | MASK2 );     
    esperar(1);	

} 

unsigned char boton(){	
    unsigned char leer; 
    leer = *(PINB) & MASK4; 		
    leer = ! leer;
    return leer;
} 





