**************************README******************************

*Verificar que la variable de velocidad en el serial.c esté definido de la siguiente manera:

#define USART_BAUDRATE 9600

Es muy importante tener en cuenta que en las configuraciones del CUTECOM se refleje el mismo valor de velocidad que el definido en dicha variable.

*Compilar con :

make clean
make 
make flash (o sudo make flash) # transfiere el firmware al AVR

*Ejecutar el comando 

	cutecom

por consola, para visualizar lo que recibe la PC. Y por último reiniciar el AVR para ver correctamente la información recibida. 



