
/* utils.c - funciones utiles al TP2 */
#define LED_ROJO1 (0x04) /*pin 10 0b00000100 */ 
#define LED_ROJO2 (0x02) /*pin 9  0b00000010 */
#define LED_ROJO3 (0x10) /*pin 12 0b00010000 */

#define BOTON (0x08) /* pin 11*/


/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */


/* puertos de E/S */
volatile unsigned char * PUERTO_B = (unsigned char *) 0x25; /* direccion de PORTB: SALIDA */
volatile unsigned char * DDR_B = (unsigned char *) 0x24; /* direccion de DDR B (registro de control) */
volatile unsigned char * PIN_B = (unsigned char *) 0x23; /* direccion PIN B (registro de datos)*/


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
    volatile unsigned char * PIN_B =  0x23; /* direccion PIN B (registro de datos)*/
    /* turn the GPIO pin voltage off
    * (this should be done before the pins are configured)
    */
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_ROJO1);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_ROJO2);
    *(PUERTO_B) = *(PUERTO_B) & (~ LED_ROJO3);
    *(PUERTO_B) = *(PUERTO_B) & (~ BOTON);

    /* make sure the LED control pin is set to operate as OUTPUT */
    *(DDR_B) = *(DDR_B) | (LED_ROJO1);
    *(DDR_B) = *(DDR_B) | (LED_ROJO2);
    *(DDR_B) = *(DDR_B) | (LED_ROJO3);

    *(PIN_B) = *(PIN_B) | (BOTON);
}


void esperar() {
	volatile unsigned long i;
	/* delay de 1 segundo */
	for (i=0; i<450000; i++);
}
volatile unsigned  estado = 0;
volatile unsigned  salida = 0;
int binario = 1;

void config_hardware() {
    volatile unsigned char * PUERTO_B = 0x25; /* direccion de PUERTO B */
    volatile unsigned char * PIN_B = 0x23; /* direccion PIN B (registro de datos)*/
    
    unsigned char valor_led1;
    unsigned char valor_led2;
    unsigned char valor_led3;

    

    estado = *(PIN_B);
    estado &= (BOTON) ;
    *(PIN_B) = estado;

    if(estado  == 0b00001000){
        if(salida == 1 ){
            salida = 0;
            // apago leds 
            *(PUERTO_B) = *(PUERTO_B) & (~ LED_ROJO1);
            *(PUERTO_B) = *(PUERTO_B) & (~ LED_ROJO2);
            *(PUERTO_B) = *(PUERTO_B) & (~ LED_ROJO3);
            
        }else{
            salida = 1;
            binario = 1;
        }
    }
    
    if(salida == 0){

        valor_led1 = *(PUERTO_B);
        valor_led1 ^= (LED_ROJO1);
        *(PUERTO_B) = valor_led1;

        valor_led2 = *(PUERTO_B);
        valor_led2 ^= (LED_ROJO2);
        *(PUERTO_B) = valor_led2;

        valor_led3 = *(PUERTO_B);
        valor_led3 ^= (LED_ROJO3);
        *(PUERTO_B) = valor_led3;
    }else
    {
        // apago leds 
        *(PUERTO_B) = *(PUERTO_B) & (~ LED_ROJO1);
        *(PUERTO_B) = *(PUERTO_B) & (~ LED_ROJO2);
        *(PUERTO_B) = *(PUERTO_B) & (~ LED_ROJO3);
        switch (binario){
            case 1:
                valor_led3 = *(PUERTO_B);
                valor_led3 ^= (LED_ROJO3);
                *(PUERTO_B) = valor_led3;
                binario = binario +1;
                break;
            case 2:
                valor_led2 = *(PUERTO_B);
                valor_led2 ^= (LED_ROJO2);
                *(PUERTO_B) = valor_led2;
                binario = binario +1;
                break;
            case 3:
                valor_led3 = *(PUERTO_B);
                valor_led3 ^= (LED_ROJO3);
                *(PUERTO_B) = valor_led3;

                valor_led2 = *(PUERTO_B);
                valor_led2 ^= (LED_ROJO2);
                *(PUERTO_B) = valor_led2;
                binario = binario +1;
                break;
            case 4:
                valor_led1 = *(PUERTO_B);
                valor_led1 ^= (LED_ROJO1);
                *(PUERTO_B) = valor_led1;
                binario = binario +1;
                break;
            case 5:
                valor_led3 = *(PUERTO_B);
                valor_led3 ^= (LED_ROJO3);
                *(PUERTO_B) = valor_led3;

                valor_led1 = *(PUERTO_B);
                valor_led1 ^= (LED_ROJO1);
                *(PUERTO_B) = valor_led1;
                binario = binario +1;
                break;
            case 6:
                valor_led2 = *(PUERTO_B);
                valor_led2 ^= (LED_ROJO2);
                *(PUERTO_B) = valor_led2;

                valor_led1 = *(PUERTO_B);
                valor_led1 ^= (LED_ROJO1);
                *(PUERTO_B) = valor_led1;
                binario = binario +1;
                break;        
            case 7:
                valor_led3 = *(PUERTO_B);
                valor_led3 ^= (LED_ROJO3);
                *(PUERTO_B) = valor_led3;

                valor_led2 = *(PUERTO_B);
                valor_led2 ^= (LED_ROJO2);
                *(PUERTO_B) = valor_led2;

                valor_led1 = *(PUERTO_B);
                valor_led1 ^= (LED_ROJO1);
                *(PUERTO_B) = valor_led1;
                binario = binario +1;
                break;
            
            default:
                binario = 1;
                break;
        }
  
    }
    
}

