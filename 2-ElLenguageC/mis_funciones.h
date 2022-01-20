#include <stdio.h>
#include <string.h>
#include <unistd.h>

//Muestra un mensage de error si no hay suficientes argumentos
void Usage();

//Devuelve el caracter c en formato de integer
unsigned int char2int(char c);

//Convierte un string en un integer
int mi_atoi(char *s);

//Devuelve 1 si el parametro es un numero, y un 0 si no lo es
int esNumero(char *str);
