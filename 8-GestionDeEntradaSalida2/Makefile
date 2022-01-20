all: exServerSocket exClientSocket sin_nombre escritor lector

exServerSocket: exServerSocket.c socketMng.o
	gcc -o exServerSocket exServerSocket.c socketMng.o

exClientSocket: exClientSocket.c socketMng.o
	gcc -o exClientSocket exClientSocket.c socketMng.o

socketMng.o: socketMng.c
	gcc -c socketMng.c

sin_nombre: sin_nombre.c
	gcc -o sin_nombre sin_nombre.c

lector: lector.c
	gcc -o lector lector.c

escritor: escritor.c
	gcc -o escritor escritor.c

clean:
	rm -f exServerSocket exClientSocket socketMng.o sin_nombre escritor lector
