/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "utils.h"

int main(void)
{
    char rcvChar = 0;

    /* Configure the UART for the serial driver */
    serial_init();

    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
    serial_put_char('\r');
    serial_put_char('\n');

    while (rcvChar != 'q')
    {
        /* Wait for an incoming character */
        rcvChar = serial_get_char();
	serial_put_char(rcvChar);
	if (rcvChar == 'c') {
		let_init(); 
		conteo_binario();
		apagar_led();
	}
	else if (rcvChar == 'k') {
		led_init(); 
		knight_rider();
		knight_rider_reverso();
		knight_rider();
		knight_rider_reverso();
		knight_rider();
		knight_rider_reverso();
		knight_rider();
		knight_rider_reverso();
		apagar_led();
	}	
        /* Echo the character back along with a carriage return and line feed */
        
    }
    serial_put_char('\r');
    serial_put_char('\n');

    for (;;);

    return 0;
}
