#include "utils.h"

unsigned char modo = 0;

int main(void)
{	
    /* configura los pines que controlan los LEDs y el pulsador. */
	init();

	while (1) {

		if(boton()){
            modo = !modo;
        }

        if(modo){
            //modo 1
            contador();
		}else{
            //modo 0 
			parpadeo();
		}


    }
}


