#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void Usage() {
  char buff[100];
  sprintf(buff, "Arguments no valids\n");
  write(1,buff,strlen(buff));
  exit(-1);
}

int main (int argc, char *argv[]) {
  if (argc != 2) Usage;
  int ret = fork();
  mknod("npipe");
  //Fill 1
  if (ret == 0) {
    char c[1];
    int fp = open("npipe",O_WRONLY);
    while(read(/*enteros.bin*/,c,1) > 0) {
		write(fp,c,1);
	 }
	  close(fp);
    exit(0);
  }
  else {
    int ret2 = fork();
    //Fill 2
    if (ret2 == 0) {
      exit(0);
    }
    //Pare
    else {
      while(waitpid (-1, NULL, 0) > 0){}
      close("npipe");
    }
  }
}
