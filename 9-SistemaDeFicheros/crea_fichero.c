#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	char buff[50];
	int k = creat("salida.txt", 0600);
	sprintf(buff, "ABCD");
	write(k,buff,strlen(buff));
}
