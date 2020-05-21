/*
 * Dibuja un texto con caracteres ASCII usando un font intercambiable
 * Copyright 2020 - Guillermo Guerrero
 *
 */


#include <string.h>
#include <stdio.h>

#include "font.h"

#define ANCHO 80
#define ALTO 24

unsigned char buffer[ANCHO * ALTO];
unsigned char addr;


void render_buffer(void)
{
	int i = 0;
	char linea[81];
	char *text =  "hola";

	for (i=0; i<ALTO; i++) {
		strncpy(&linea[0], &buffer[i*80], 80);
		linea[80] = 0;
		printf("%s\n", linea);
	}
}


void draw_pixel_on_buffer(unsigned char x, unsigned char y, int color)
{
	switch(color) {
	case 0:
		buffer[y*80+x] = ' ';
		break;
	case 1:
		buffer[y*80+x] = 'X';
		break;
	default:
		break;
	}

}

/* Dibuja una letra en el buffer, comenzando con la columna [x,y]
 * para el primer pixel de la letra
 */
void draw_char_on_buffer(unsigned char x, unsigned char y, char c,
                            unsigned char color)
{

	int i; /* para recorrer el font por columnas */
	int j; /* para recorrer el font por filas */
	int pos = 5*c;
	char col; /* para almacenar cada columna de pixeles del font */
	for (i = 0; i < 5; i++) {
		col = font[pos+i];
		for (j = 0; j < 8; j++) {
			if(col & (1 << j)){
				draw_pixel_on_buffer(x + i, y + j, 1);
			} else{
				draw_pixel_on_buffer(x + i, y + j, 0);
			}


		}
	}
}


void clear_buffer(void)
{
	memset(buffer, ' ', (ANCHO * ALTO) * sizeof(unsigned char));
	/*La función memset() llena los primeros ((ANCHO * ALTO) * sizeof(unsigned char)) bytes del
		area de memoria apuntados por buffer con la constante ' '
 */
}

/* Muestra un texto en pantalla
 * x e y son coordenadas a resolución de pixel
 * Cada letra es de 6 columnas y 8 filas (1 columna es espacio)
 */
void print_text_on_buffer(unsigned char x, unsigned char y, char *text)
{
	int indice = 0;
	int i = 0;
	char *c = text;

	while (c[indice] != 0) {
		draw_char_on_buffer(x+i, y, c[indice], 0);
		indice++;
		i += 6;
	}
}


int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Error: se necesita al menos un argumento. \n");
		return -1;
	}

	printf("Programa: %s, y el argumento 1 es: %s \n", argv[0], argv[1]);
	clear_buffer();

	if (argc == 2)
		print_text_on_buffer(3, 5, argv[1]);
	else {
		print_text_on_buffer(3, 5, argv[1]);
		print_text_on_buffer(3, 15, argv[2]);
	}

	render_buffer();

	return 0;


}
