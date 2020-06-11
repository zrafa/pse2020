

APP= Hello_world
CC= avr-gcc
MCU= atmega328p
FCPU= 16000000UL
FLAGMCU= -mmcu=$(MCU)
FLAGFCPU= -DF_CPU=$(FCPU)
ALL_FLAGS= $(FLAGFCPU) $(FLAGMCU)
all: ${APP}.c
	$(CC) -Os ${ALL_FLAGS} -c -o ${APP}.o ${APP}.c
	$(CC) ${FLAGMCU} ${APP}.o -o ${APP}.elf
clean:
	rm ${APP}.elf
	rm ${APP}.o
