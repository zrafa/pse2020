Pasos:

1. make clean
2. make
3. make flash

Presionar el boton de reset un tiempo y soltar,
repetir si no funciona

Configurar el driver serial del Linux a 115200:

    stty -F /dev/ttyUSB0                # nos muestra la configuracion
    stty -F /dev/ttyUSB00 speed 115200  # configuramos el driver serial del Linux a 115200
    stty -F /dev/ttyUSB0                # revisamos la nueva configuracion

Enviar audio:

    cat archivo_8bit.wav > /dev/ttyUSB0  # enviamos el archivo wav al avr

En caso de  no tener un wav con las caracteristicas deseadas (8bits - 11 kHz)
convertir un mp3 a wav usando ffmpeg:

    ffmpeg -i archivo_input.mp3 -ar 11000 -acodec pcm_u8 -ac 1 archivo_8bit.wav
