CC=avr-gcc
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=atmega328p -c

.PHONY: clean all

EJECUTABLE=app.elf
OBJETOS=main.o

ARCHIVOHEX = app.hex

all: $(EJECUTABLE)
	avr-objcopy -O ihex -R .eeprom $(EJECUTABLE) $(ARCHIVOHEX)

$(EJECUTABLE): $(OBJETOS)
	$(CC) $(OBJETOS) -o $@

clean:
	rm $(EJECUTABLE) $(OBJETOS) $(ARCHIVOHEX)
