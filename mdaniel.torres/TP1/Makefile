all: program1 program2

program1: helloWorld.c
	mips-linux-gnu-gcc helloWorld.c -o helloWorld-mips
program2: helloWorld.c
	avr-gcc helloWorld.c -o helloWorld-avr


clean: 
	rm -rf helloWorld-mips
	rm -rf helloWorld-avr
