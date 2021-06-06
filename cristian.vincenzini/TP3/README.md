Implementa driver para periferico UART:

- Enviar letra 'c' para iniciar conteo binario
- Enviar letra 'k' para efecto knight rider
- Enviar letra 'q' para terminar el programa
- Resto de las letras produce echo

Pasos:

1. make clean
2. make
3. make flash

Presionar el boton de reset un tiempo y soltar,
repetir si no funciona.

Para la comunicación con el UART usar
cutecom con la siguiente configuración:

* 9600bps
* 8bits data
* 1bit stop
* sin bit de paridad

Luego seleccionar opción: open device
y resetear el arduino para que el programa comience
desde el inicio.

**ATENCIÓN**

Si se desea volver a flashear el dispositivo
no olvidarse de cerrar el cutecom, de otra
manera el puerto SERIAL estará tomado por el cutecom
y no se podrá realizar la operación.