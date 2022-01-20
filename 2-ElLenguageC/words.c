#include "mis_funciones.h"

int main(int argc,char *argv[]) {
    char buf[80];
    if (argc <= 1) Usage();
    else {
        int n = argc - 1;
        int i = 0;
        while (argv[i] != 0) {
            //Falta detectar palabras
            ++i;
        }
        sprintf(buf,"%d palabras\n",n);
        write(1,buf,strlen(buf));
    }
    return 0;
}
