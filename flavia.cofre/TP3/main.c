/********************************************************************** 
* 
* main.c - the main program test file for the serial driver
* 
**********************************************************************/ 
#include "utils.h"
#include "serial.h" 

int main(void){
    char rcvChar = 0;
    int i;

    /* configura los pines que controlan los LEDs y el pulsador. */
	leds_init();  

    /* Configure the UART for the serial driver */ 
    serial_init(); 



    serial_put_char('s'); 
    serial_put_char('t'); 
    serial_put_char('a'); 
    serial_put_char('r'); 
    serial_put_char('t'); 
    serial_put_char('\r'); 
    serial_put_char('\n'); 

    while (rcvChar != 'q') { 
        /* Wait for an incoming character */ 
        rcvChar = serial_get_char();
        switch (rcvChar) {
            case 'c':
                serial_put_char('C');
                serial_put_char('o'); 
                serial_put_char('n'); 
                serial_put_char('t'); 
                serial_put_char('e'); 
                serial_put_char('o');
                serial_put_char('\r'); 
                serial_put_char('\n');
                for (i = 0; i < 2; i++) {
                    contador();
                }
                break;
            case 'k':
                serial_put_char('K');
                serial_put_char('n'); 
                serial_put_char('i'); 
                serial_put_char('g'); 
                serial_put_char('h'); 
                serial_put_char('t');
                serial_put_char('\r'); 
                serial_put_char('\n');
                for (i = 0; i < 5; i++) {
                    efecto_led();
                }
                break;
            default:
                /* Echo the character back along with a carriage return and line feed */
                serial_put_char(rcvChar);
                serial_put_char('\r');
                serial_put_char('\n');
                break;
        }
    } 

    for (;;); 
    return 0;

}

