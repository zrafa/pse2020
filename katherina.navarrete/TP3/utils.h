
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
void apagar_leds();
void lets_init();
void knight_rider();
void prender_leds_elegidos(unsigned char num);
void contar_binario();
#endif	/* _UTILS_H */
