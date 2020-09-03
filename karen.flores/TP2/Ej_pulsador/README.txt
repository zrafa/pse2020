*******************************README****************************************
Se utiliza un Makefile para la compilación.

1) Escribir el siguiente comando en la consola de Linux: 
		
	make clean

Esto es para asegurarnos de eliminar versiones anteriores.

2) Ejecutar en la consola:

	make

De esta forma compilamos el programa y generamos los archivos necesarios.

3) Por último reiniciamos la placa con el siguiente comando:

	sudo make flash

Y la placa ya tendrá cargada la información correspondiente.

* Dos modos en la placa: 

	La placa inicia con el modo de parpadeo de tres leds. Para cambiar de modo mantener presionado el pulsador unos segunditos hasta que inicia el modo contador. Para volver al modo anterior, presionar el pulsador cuando se apaguen todos los leds unos segundos hasta que se active el modo correspondiente.
