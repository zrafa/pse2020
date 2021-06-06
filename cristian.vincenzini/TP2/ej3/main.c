/* Enciende y apaga leds para conseguir el efecto del knight-rider */

#include "utils.h"

int main(void)
{
        leds_init();

        while (1) {
                knight_rider();
        }
}
