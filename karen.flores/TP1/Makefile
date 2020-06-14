hello_mips = hello_world
hello_avr = hello_world

all: hello_mips hello_avr

hello_mips: 
	mips-linux-gnu-gcc -o hello_mips hello_world.c

hello_avr:
	avr-gcc -o hello_avr hello_world.c

clean:
	rm ${hello_mips}
	rm ${hello_avr}

