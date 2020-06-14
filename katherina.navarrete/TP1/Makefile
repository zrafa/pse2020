Prog1=tp1
Prog2=tp1

Obj1=tp1-avr
Obj2= tp1-mips

#dependencia all depende de lo que esta despues de los :
#es la regla principal que se quiere hacer si no se coloca nada

all: Prog1 Prog2
#instruccion
Prog1:
	avr-gcc  tp1.c -o ${Obj1}
Prog2:
	mips-linux-gnu-gcc tp1.c -o ${Obj2}
	
#clean se usa para hacer algo, no tiene dependencia por eso no hay nada despues de los dos puntos
clean:
	rm ${Obj1}
	rm ${Obj2}
