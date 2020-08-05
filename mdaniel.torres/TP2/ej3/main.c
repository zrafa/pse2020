
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"
void led_init();
void knight_raider();

int main(void)
{	
	led_init();
	while (1) {
		knight_raider();		
    }
}

void knight_raider(){
	unsigned char* PUERTO_B = 0x25;

	*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
	esperar(3);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
	esperar(3);

	*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
	esperar(3);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
	esperar(3);

	*(PUERTO_B) = *(PUERTO_B) ^ (0x08);
	esperar(3);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x08);
	esperar(3);

	*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
	esperar(3);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x04);
	esperar(3);

	*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
	esperar(3);
	*(PUERTO_B) = *(PUERTO_B) ^ (0x02);
	esperar(3);


}

void led_init(){
	volatile unsigned char* DDR_B = 0x24;
	volatile unsigned char* PUERTO_B = 0x25;


	//primero
	*(PUERTO_B) = *(PUERTO_B) & (~ 0x02);

	*(DDR_B) = *(DDR_B) | (0x02);

	//segundo

	*(PUERTO_B) = *(PUERTO_B) & (~ 0x04);

	*(DDR_B) = *(DDR_B) | (0x04);

	//tercero
	*(PUERTO_B) = *(PUERTO_B) & (~ 0x08);

	*(DDR_B) = *(DDR_B) | (0x08);

}
