/* utils.c - funciones utiles al TP2 */

#define LED_1 (0x01) /*pin 8  0b00000001 */
#define LED_2 (0x02) /*pin 9  0b00000010 */
#define LED_3 (0x04) /*pin 10 0b00000100 */ 
#define LED_4 (0x08) /*pin 11 0b00001000 */
#define LED_5 (0x10) /*pin 12 0b00010000 */
#define LED_6 (0x20) /*pin 13 0b00100000 */




/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */


/* puertos de E/S */
volatile unsigned char * puerto_b = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * ddr_b = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * pin_b = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/


/* 
 * Configuración: Establecer el 5to bit del puerto B como entrada
 *
 * 	Poner en '0' el 5to bit de la dirección 0x24, que 
 * 	es el la dirección del registro de control
 *	(direccion de los datos) del puerto B (DDRB - Data Direction Register).
 *      El 5to bit define la entrada o salida del
 * 	pin del atmega328p que tiene conectado un led en una board arduino
 */

void led_init(void)
{
    volatile unsigned char * DDR_B = 0x24; /* direccion de DDR B */
    volatile unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */
    volatile unsigned char * puerto_d = 0x2B;
    /* turn the GPIO pin voltage off
    * (this should be done before the pins are configured)
    */
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_1);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_2);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_3);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_4);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_5);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_6);

    /* make sure the LED control pin is set to operate as OUTPUT */
    *(DDR_B) = *(DDR_B) | (LED_1);
    *(DDR_B) = *(DDR_B) | (LED_2);
    *(DDR_B) = *(DDR_B) | (LED_3);
    *(DDR_B) = *(DDR_B) | (LED_4);
    *(DDR_B) = *(DDR_B) | (LED_5);
    *(DDR_B) = *(DDR_B) | (LED_6);
}


void esperar() {
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<40000; i++);
}

void conteo()
{
	int i, j;
     volatile unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */

	for (i = 0; i < 15; i++) {
		*(PUERTO_B) += 1;
		esperar();
	}

	// setea en OFF el voltaje de los pines
	*(PUERTO_B) &= ( ~LED_1 & ~LED_2 & ~LED_3 & ~LED_4 );
}

void esperar_leds() {
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<10000; i++);
}

int led = 1;
int recorrido = 0; /* ida = 0 y vuelta = 1*/


// Se puede unificar los metodos de prender_led y apagar ya que ambos relizan 
// la accion de cambiar el estado del bit de 0 a 1 o de 1 a 0
void prender_led() {
    volatile unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */

    *(PUERTO_B) = *(PUERTO_B) & (~ LED_1);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_2);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_3);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_4);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_5);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_6);
    unsigned char valor_led1;
    unsigned char valor_led2;
    unsigned char valor_led3;
    unsigned char valor_led4;
    unsigned char valor_led5;
    unsigned char valor_led6;
    
    if (recorrido == 0 ){

        switch (led){
                case 1:
                    valor_led1 = *(PUERTO_B);
                    valor_led1 ^= (LED_1);
                    *(PUERTO_B) = valor_led1;
                    esperar_leds();
                    valor_led2 = *(PUERTO_B);
                    valor_led2 ^= (LED_2);
                    *(PUERTO_B) = valor_led2;
                    led = led +1;
                    break;
                case 2:
                    valor_led2 = *(PUERTO_B);
                    valor_led2 ^= (LED_2);
                    *(PUERTO_B) = valor_led2;
                    esperar_leds();
                    valor_led3 = *(PUERTO_B);
                    valor_led3 ^= (LED_3);
                    *(PUERTO_B) = valor_led3;
                    led = led +1;
                    break;
                case 3:
                    valor_led3 = *(PUERTO_B);
                    valor_led3 ^= (LED_3);
                    *(PUERTO_B) = valor_led3;
                    esperar_leds();
                    valor_led4 = *(PUERTO_B);
                    valor_led4 ^= (LED_4);
                    *(PUERTO_B) = valor_led4;
                    led = led +1;
                    break;
                case 4:
                    valor_led4 = *(PUERTO_B);
                    valor_led4 ^= (LED_4);
                    *(PUERTO_B) = valor_led4;
                    esperar_leds();
                    valor_led5 = *(PUERTO_B);
                    valor_led5 ^= (LED_5);
                    *(PUERTO_B) = valor_led5;
                    led = led +1;
                    break;
                case 5:
                    valor_led5 = *(PUERTO_B);
                    valor_led5 ^= (LED_5);
                    *(PUERTO_B) = valor_led5;
                    esperar_leds();
                    valor_led6 = *(PUERTO_B);
                    valor_led6 ^= (LED_6);
                    *(PUERTO_B) = valor_led6;
                    led = led +1;
                    break;
                case 6:
                    valor_led6 = *(PUERTO_B);
                    valor_led6 ^= (LED_6);
                    *(PUERTO_B) = valor_led6;
                    led = led +1;
                    break;
                
                default:
                    led = 6;
                    recorrido = 1;
                    break;
            }
    }else{
        switch (led){
                case 1:
                    valor_led1 = *(PUERTO_B);
                    valor_led1 ^= (LED_1);
                    *(PUERTO_B) = valor_led1;
                    led = led -1;
                    break;
                case 2:
                    
                    valor_led2 = *(PUERTO_B);
                    valor_led2 ^= (LED_2);
                    *(PUERTO_B) = valor_led2;
                    esperar_leds();
                    valor_led1 = *(PUERTO_B);
                    valor_led1 ^= (LED_1);
                    *(PUERTO_B) = valor_led1;
                    
                    led = led -1;
                    break;
                case 3:
                
                    valor_led3 = *(PUERTO_B);
                    valor_led3 ^= (LED_3);
                    *(PUERTO_B) = valor_led3;
                    esperar_leds();
                    valor_led2 = *(PUERTO_B);
                    valor_led2 ^= (LED_2);
                    *(PUERTO_B) = valor_led2;
                    
                    led = led -1;
                    break;
                case 4:
                    valor_led4 = *(PUERTO_B);
                    valor_led4 ^= (LED_4);
                    *(PUERTO_B) = valor_led4;
                    esperar_leds();
                    valor_led3 = *(PUERTO_B);
                    valor_led3 ^= (LED_3);
                    *(PUERTO_B) = valor_led3;
                    led = led -1;
                    break;
                case 5:
                    valor_led5 = *(PUERTO_B);
                    valor_led5 ^= (LED_5);
                    *(PUERTO_B) = valor_led5;
                    esperar_leds();
                    valor_led4 = *(PUERTO_B);
                    valor_led4 ^= (LED_4);
                    *(PUERTO_B) = valor_led4;  
                    led = led -1;
                    break;
                case 6:
                    valor_led6 = *(PUERTO_B);
                    valor_led6 ^= (LED_6);
                    *(PUERTO_B) = valor_led6;
                    esperar_leds();
                    valor_led5 = *(PUERTO_B);
                    valor_led5 ^= (LED_5);
                    *(PUERTO_B) = valor_led5;
                    led = led -1;
                    break;
                
                default:
                    led = 2;
                    recorrido = 0;
                    break;
            }
    }


}
