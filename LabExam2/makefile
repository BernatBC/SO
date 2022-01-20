all: hijo1 hijo2 multiA multiB multiC multiD

hijo1: hijo1.o
	gcc -o hijo1 hijo1.c

hijo2: hijo2.o
	gcc -o hijo2 hijo2.c

multiA: multiA.o
	gcc -o multiA multiA.c

multiB: multiB.o
	gcc -o multiB multiB.c

multiC: multiC.o
	gcc -o multiC multiC.c

multiC: multiD.o
	gcc -o multiD multiD.c

clean:
	rm multiA multiB multiC multiD hijo1 hijo2
