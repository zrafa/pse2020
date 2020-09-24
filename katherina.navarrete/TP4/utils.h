
/* utils.h - funciones utiles al TP2 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#ifndef _UTILS_H
#define _UTILS_H


void esperar_medio_seg();
void esperar_dos_seg();
void prender_leds();
void prender_valor(char input);
void apagar_leds();
void lets_init();

#endif	/* _UTILS_H */
