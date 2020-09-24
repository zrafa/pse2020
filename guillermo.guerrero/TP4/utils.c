
/*utils.c - funciones utiles al TP2 */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los
 * pines 8-13 de arduino
 */
#include "utils.h"
/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/

unsigned char Bit0 = 0x01; //D8
unsigned char Bit1 = 0x02; //D9
unsigned char Bit2 = 0x04; //D10
unsigned char Bit3 = 0x08; //D11
unsigned char Bit4 = 0x10; //D12
unsigned char Bit5 = 0x20; //D13


 void init(){
   *ddr_b |= Bit0; //Seteo a 1 a D8 (Out)
   *ddr_b |= Bit1; //Seteo a 1 a D9 (Out)
   *ddr_b |= Bit2; //Seteo a 1 a D10 (Out)
   *ddr_b |= Bit3; //Seteo a 1 a D11 (Out)

 }

void esperar1() {
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<500000; i++);
}

void esperar2() {
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<10000; i++);
}

void apagar_led() {
  *puerto_b &= ~Bit0; //Apago D8
  *puerto_b &= ~Bit1; //Apago D9
  *puerto_b &= ~Bit2; //Apago D10
  *puerto_b &= ~Bit3; //Apago D11
}

void efectoIzquierda(){
  int i;
  int parcial = 1;
  *puerto_b |= Bit2;
  esperar1();
  apagar_led();
  for(i=0; i<3; i++){
    parcial = parcial * 2;
    *puerto_b |= parcial<<2;
    esperar1();
    apagar_led();
  }

}

void efectoDerecha(){
  int i;
  int parcial = 8;
  *puerto_b |= Bit5;
  esperar1();
  apagar_led();
  for(i=0; i<3; i++){
    parcial = parcial / 2;
    *puerto_b |= parcial<<2;
    esperar1();
    apagar_led();
  }
}

void prender_led() {
	*puerto_b |= Bit3; //Prendo D11
  *puerto_b |= Bit4; //Prendo D12
  *puerto_b |= Bit5; //Prendo D13
}

void prender_led_valor(int valor) {
apagar_led();
  if(valor == 0){
    *puerto_b |= Bit2;
  } else{
    if(valor == 1){
      *puerto_b |= Bit1;
    } else{
      if(valor == 2){
        *puerto_b |= Bit0;
      }
    }
  }
}

void prender(char caracter)
{
        apagar_led();
        *puerto_b += caracter;
}


void suma(){
  int i;
  int parcial = 0;
  apagar_led();
  for(i=0; i<8; i++){
    parcial = parcial + 1;
    *puerto_b |= parcial<<2;
    esperar1();
    apagar_led();
  }
}
