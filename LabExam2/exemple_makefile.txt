all: cuenta

cuenta: cuenta.o funciones.o
	gcc -o cuenta cuenta.o funciones.o

cuenta.o: cuenta.c funciones.h
	gcc -c cuenta.c
	
funciones.o: funciones.c funciones.h
	gcc -c funciones.c
	
clean:
	rm cuenta cuenta.o funciones.o
