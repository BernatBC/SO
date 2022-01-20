#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

int main(int argc,char *argv[])
{
char buf[80];
	for (int i=0;i<argc;i++){
		if (i!=0){
            int a = esNumero(argv[i]);
            if (a) sprintf(buf,"%s es un numero\n", argv[i]);
            else sprintf(buf,"%s no es un numero\n", argv[i]);
		}
		write(1,buf,strlen(buf));
    }
	return 0;
}
