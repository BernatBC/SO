#include "funciones.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    char buf[80];
    if (argc != 4) perror("arguments no valids");
    else {
        int proc = *argv[1] - '0';
        int mida = FileSize(argv[2]);
        if (mida%proc != 0) {
            sprintf(buf,"La mida del fitxer no es divisible entre el numero de processos\n");
            write(1,buf,strlen(buf));
        }
        else {
            int p;
            int pid = getpid();
            for (int i = 0; i < proc; ++i) {
                if (getpid() == pid) {
                    p = fork();
                    if (p == -1){
                        perror("Internal Error");
                        exit(1);
                    }
                }
                else 
                {
                    char c = *argv[3];
                    CountCharacter(argv[2],c,i,proc,mida);
                    exit(0);
                }
            }
            int s = 0; 
            int ret;
            while (ret = waitpid (-1, NULL, 0) > 0) {
                s += ReadPartialCount(argv[2], ret);
            }
            sprintf(buf,"El fitxer conte %d caracters\n", s);
            write(1,buf,strlen(buf));
        }
    }
}

