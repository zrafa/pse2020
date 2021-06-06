# Desarrollo de prácticas con Xinu

1. Descargar [código fuente](http://se.fi.uncoma.edu.ar/pse2020/extras/xinu-avr-pse2020.tar.gz) o bien `git clone https://github.com/zrfa/xinu-avr`.
2. Copiar uno de los ejemplos en la carpeta main, borrando lo que hubiera.
3. Compilar y transferir al avr.

El testeo se puede realizar a través de la aplicación
screen con el siguiente comando:

    screen /dev/ttyUSB0

Resetear el arduino para comenzar de cero la programación.

**Importante**

Para compilar es posible que se requiera
software adicional.
Es posible que screen no venga instalado por defecto.
Se recomienda:

    sudo apt install screen bison gawk

Para las toolchains:

    sudo apt install binutils-avr avr-ligc gcc-avr avrdude gdb-avr