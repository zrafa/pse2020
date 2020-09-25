
/* utils.h - funciones utiles al TP2 */

/*
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los
 * pines 8-13 de arduino
 */
#include <stdbool.h>
#ifndef _UTILS_H
#define _UTILS_H

void init();
void esperar1();
void esperar2();
int boton();
void suma();
void prender_led();
void prender_led_valor(int);
void prender(char);
void apagar_led();
void efectoIzquierda();
void efectoDerecha();


#endif	/* _UTILS_H */
