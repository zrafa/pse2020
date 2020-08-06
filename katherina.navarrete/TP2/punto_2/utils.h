
/* utils.h - funciones utiles al TP2 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#ifndef _UTILS_H
#define _UTILS_H


void esperar();
void prender_led();
void apagar_led();
void let_init();
void contar(unsigned char num);
unsigned char get_estado();

#endif	/* _UTILS_H */
