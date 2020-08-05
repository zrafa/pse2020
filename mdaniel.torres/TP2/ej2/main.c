
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"
void led_init();
void pulsador_init();
int sePresiono();
int boton;
void contador();


int main(void)
{	
    led_init();
    pulsador_init();
        while (1) {
            sePresiono();
        if(!boton){
            contador();
        }else{
            esperar();
            prender_led();

            esperar();
                apagar_led();
        }
    }
}

void contador(){
    unsigned char* PUERTO_B = 0x25;

    esperar();
    *(PUERTO_B) = *(PUERTO_B) ^ (0x02);
    esperar();
    *(PUERTO_B) = *(PUERTO_B) ^ (0x02);
    *(PUERTO_B) = *(PUERTO_B) ^ (0x04);
    esperar();
    *(PUERTO_B) = *(PUERTO_B) ^ (0x02);
    esperar();
    *(PUERTO_B) = *(PUERTO_B) ^ (0x02);
    *(PUERTO_B) = *(PUERTO_B) ^ (0x04);
    *(PUERTO_B) = *(PUERTO_B) ^ (0x08);
    esperar();
    *(PUERTO_B) = *(PUERTO_B) ^ (0x02);
    esperar();
    *(PUERTO_B) = *(PUERTO_B) ^ (0x02);
    *(PUERTO_B) = *(PUERTO_B) ^ (0x04);
    esperar();
    *(PUERTO_B) = *(PUERTO_B) ^ (0x02);
    esperar();
    led_init();
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

void pulsador_init(){
    volatile unsigned char* DDR_B = 0x24;
    volatile unsigned char* PUERTO_B = 0x25;

    //pulsador
    *(PUERTO_B) = *(PUERTO_B) | (0x10);
    //*(PUERTO_B) = *(PUERTO_B) & (~0x10);

    *(DDR_B) = *(DDR_B) & (~0x10);

}

int sePresiono(){
    unsigned char* PIN_B = 0x23;

    // verificar si el bit 0x10 de puertoB esta setteado
    if((*PIN_B) & (0x10)){
        boton = 1;
        return 1;
    }
    boton = 0;
    return 1;
}
