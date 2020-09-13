#!/bin/bash

# Programación de sistemas embebidos 2020
# Simple hack para generar keystrokes segun tp4

# requiere: xdotool instalado


# Configurar velocidad del serial en PC (la misma que el avr)
stty -F /dev/ttyUSB0 speed 57600 

# stty -F /dev/ttyACM0 
b=0

cat /dev/ttyUSB0 | 
while read a ; do 
	
	if [ $a -lt 800 ] ; then 
		xdotool key Left Left Left Left Left Left Left
	elif [ $a -gt 1000 ] ; then 
		xdotool key Right Right Right Right Right Right Right
	fi 

done
