all: mips avr

mips: hello.c
	mips-linux-gnu-gcc hello.c -o hello-mips
avr: hello.c
	avr-gcc hello.c -o hello-avr


clean: 
	rm -rf hello-mips
	rm -rf hello-avr
