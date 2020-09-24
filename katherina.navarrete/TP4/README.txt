-----------------------------------------README-----------------------------------------------------------------
Katherina Navarrete
-----------------------------------------------------------------------------------------------------------------

Para compilar y ejecutar:

	make clean
	
	make

	sudo make flash

------------------------------------------------------------------------------------------------------------------

main.c

	1. Se llama a la inicialización de los driver.

	2. Se solicita el valor correspondiente al ADC por el canal 0 (correspondiente A0).
	
	3. Se calcula la intencidad de 0 a 7, donde 0 se corresponde con la menor intensidad y 7  con la mayor.

	4. Se convierte el valor obtenido del ADC a ascii para poder ser enviado.

-------------------------------------------------------------------------------------------------------------------

adc.c
	1. Se configura el ADC, permitiendo las converciones de las señales analogica a digitates
	
	2. Se envian el valor de la conversión correspondiente al canal recibido por parametro

------------------------------------------------------------------------------------------------------------------

serial.c

	1. Se configura el serial, permitiendo la comunicación atraves  UART

	2. Se define el envio y recepción de caracteres o cadenas

-------------------------------------------------------------------------------------------------------------------

utils.s

	1. Se configura los registros correspondientes al puerto b

	2. Se define el prendido y apagado de los leds (conectados a los pines 13, 12 y 11)
------------------------------------------------------------------------------------------------------------------
