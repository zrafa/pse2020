-----------------------------------------README-----------------------------------------------------------------
Katherina Navarrete
-----------------------------------------------------------------------------------------------------------------

Para compilar y ejecutar:

	make clean
	
	make

	sudo make flash

----------------------------------------------------------------------------------------------------------------
Para enviar los bits de audio:

	.configuramos el driver serial del Linux a 115200:

		stty -F /dev/ttyUSB0 			# nos muestra la configuracion
		stty -F /dev/ttyUSB00 speed 115200 	# configuramos el driver serial del Linux a 115200
		stty -F /dev/ttyUSB0 			# revisamos la nueva configuracion

	.enviamos los bits
		cat archivo_8bit.wav > /dev/ttyUSB00 	# enviamos el archivo wav al avr

--------------------------------------------------------------------------------------------------------------


