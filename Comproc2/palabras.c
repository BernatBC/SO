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
  int fd[2];
  pipe(fd);
  int ret = fork();
  if (ret == 0) {
    dup2(fd[1], 1);
    close(fd[0]);
    execlp ("wc", "wc", "-w", argv[1], (char *) 0);
    close(fd[1]);
  }
  else {
    close(fd[1]);
    char c[15];
    char buff[100];
    waitpid(-1, NULL, 0);
    read(fd[0], &c, 15);
    close(fd[0]);
    sprintf(buff, "El numero de palabras es %s\n", c);
    write(1,buff,strlen(buff));
  }
}
