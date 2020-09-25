/* utils.c - implementacion de funciones utiles al TP2 */

#include "utils.h" 

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los
 * pines 8-13 de arduino 
 */
#define MASK0 (0x01) /* 0b 0000 0001 mascara para controlar el bit 0 */
#define MASK1 (0x02) /* 0b 0000 0010 mascara para controlar el bit 1 */
#define MASK2 (0x04) /* 0b 0000 0100 mascara para controlar el bit 2 */
#define MASK3 (0x08) /* 0b 0000 1000 mascara para controlar el bit 3 */

#define MASK5 (0x20) /* 0b 0010 0000 mascara para controlar el bit 5 */


/* puertos de E/S */
volatile unsigned char * PORTB = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * DDRB = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */


 

void leds_init(void){	

    /* LEDS */
    // el voltage de salida de los pines GPIO es establecido a cero	
    *(PORTB) &= ( ~MASK0 | ~MASK1 | ~ MASK2 | ~MASK3 | ~MASK5); 	
    // Configura que los pines GPIO se utilice como SALIDA a traves del registro DDRB	
    *(DDRB) |= ( MASK0 | MASK1 | MASK2 | MASK3 | MASK5);
}


void esperar(unsigned long n){
    unsigned long i; 	
    /* delay */
    for (i = 0; i < 4500 * n; i++);
}


void binario_leds(char binario){

    // el voltage de salida de los pines GPIO es establecido a cero	    
    *(PORTB) &= ( ~MASK0 & ~MASK1 &  ~MASK2 & ~MASK3 & ~MASK5);
    *(PORTB) += binario;
    esperar(100);
} 

void contador(void){

    // el voltage de salida de los pines GPIO es establecido a cero	    
    *(PORTB) &= ( ~MASK0 & ~MASK1 &  ~MASK2);
    esperar(100);
    int i;
    for(i=0; i<7;i++){
        *(PORTB) += MASK0;
        esperar(100);
    }  
 
} 


void efecto_led(void){	

    char arreglo_mascara[5] = {MASK0, MASK1, MASK2, MASK3, MASK5};
    int i;
    for (i=0; i<=8; i++){
        if(i>4){
            *(PORTB) |= arreglo_mascara[8-i];	
            esperar(10);	
            *(PORTB) &= ~(arreglo_mascara[8-i]);
        }else{
            *(PORTB) |= arreglo_mascara[i];	
            esperar(10);	
            *(PORTB) &= ~(arreglo_mascara[i]);

        }
    
    }	
            
} 













