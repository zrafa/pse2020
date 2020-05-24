/* 
 * Dibuja un caracter ASCII
 * Copyright 2020 - COFRE FLAVIA
 *
 */


#include <string.h>
#include <stdio.h>

#include "font.h"


int main(void){

    char letra;
	int i;
    char col;
    scanf("%c",&letra);
    printf("El caracter ingresado es %c\n", letra);

    const char *p = &font[5 * letra];
    for (i = 0; i < 5; i++) {
	    col = *(p+i);
        printf("contenido de col=%x \n", col);

	}

return 0;


}
