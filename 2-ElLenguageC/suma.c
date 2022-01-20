#include "mis_funciones.h"

int main(int argc,char *argv[])
{
char buf[80];
    int n = 0;
    if (argc <= 2) Usage();
	for (int i=0;i<argc;i++){
		if (i!=0){
            int a = esNumero(argv[i]);
            if (a) {
                n += mi_atoi(argv[i]);
            }
            else {
               sprintf(buf,"Error: el parametro %s no es un número\n", argv[i]);
               write(1,buf,strlen(buf));
               return -1;
            }
		}
    }
    sprintf(buf,"La suma es %d\n", n);
    write(1,buf,strlen(buf));
	return 0;
}
