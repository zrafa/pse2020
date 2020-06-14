all: programMips programAvr

programMips: helloWorld.c
	mips-linux-gnu-gcc helloWorld.c -o helloWorldMips
programAvr: helloWorld.c
	avr-gcc helloWorld.c -o helloWorldAvr


clean: 
	rm -rf helloWorldMips
	rm -rf helloWorldAvr
