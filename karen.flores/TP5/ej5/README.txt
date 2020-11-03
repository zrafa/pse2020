**************************README******************************

*Verificar que la variable de velocidad en el serial.c esté definido de la siguiente manera:

#define USART_BAUDRATE 115200

*Tener en la misma carpeta un archivo de entrada en formato mp3 u otro

*Compilar con :

make clean
make 
make flash (o sudo make flash) # transfiere el firmware al AVR

*Ejecutar los siguientes comandos:


ffmpeg -i archivo_input.mp3 -ar 11000 -acodec pcm_u8 -ac 1 archivo_8bit.wav       //convertir en la PC un mp3 a 8bits

stty -F /dev/ttyUSB0                     // nos muestra la configuracion

stty -F /dev/ttyUSB00 speed 115200       // configuramos el driver serial del Linux a 115200

stty -F /dev/ttyUSB0                     // revisamos la nueva configuracion

cat archivo_8bit.wav > /dev/ttyUSB00     // enviamos el archivo wav al avr





