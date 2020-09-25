
/* utils.h - funciones utiles al TP2 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#ifndef _UTILS_H
#define _UTILS_H

void let_init(void);
void esperar();
void prender_led(char intensidad);
void apagar_led();


#endif	/* _UTILS_H */
