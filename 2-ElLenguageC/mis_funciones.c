#include "mis_funciones.h"

void Usage() {
    char buf[80];
    sprintf(buf, "Usage:listaParametros arg1 [arg2..argn]\n");
    write(1,buf,strlen(buf));
    sprintf(buf, "Este programa escribe por su salida la lista de argumentos que recibe\n");
    write(1,buf,strlen(buf));
}

unsigned int char2int(char c) {
    return c - '0'; 
}

int mi_atoi(char *s) {
    int num = 0;
    int i = 0;
    if (s[i] == '-') ++i;
    while (s[i] != 0) {
        num *= 10;
        num += char2int(s[i]);
        ++i;
    }
    if (s[0] == '-') num*=(-1);
    return num;
}

int esNumero(char *str) {
    if (str == NULL) return 0;
    int i = 0;
    while (str[i] != 0) {
        if (str[i] < '0' || str[i] > '9') {
            if (i != 0 || str[i] != '-') return 0;
        }
        if (i >= 8) return 0;
        ++i;
    }
    return 1;
}
