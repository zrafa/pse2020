/* Enciende y apaga cada un segundo led incorporado a la placa arduino
 controlado por el PIN13 del MCU atmega328P */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
        DDRB = 0x20;  /* 0b00100000 */

        while (1) {
                PORTB ^= 0x20;
                _delay_ms(1000);
        }
}
