/* Enciende y apaga leds para conseguir el efecto del knight-rider */

#include "utils.h"

int main(void)
{	
	setup();

	while (1) {
		knight_rider();
	}
}
