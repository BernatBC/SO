#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	char buff[20];
	char aux[20];

	int k = open("salida.txt", O_RDWR);

	lseek(k,-1,SEEK_END);
	read(k, buff, sizeof(char));
	lseek(k,-1,SEEK_CUR);
	sprintf(aux,"X");
	write(k, aux,strlen(aux));
	write(k,buff,strlen(buff));
}
