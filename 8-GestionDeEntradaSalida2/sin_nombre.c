#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
  int fd[2];
  pipe(fd);
  int ret = fork();
  if (ret == 0) {
    dup2(fd[0], 0);
    close(fd[0]);
    close(fd[1]);
    execlp ("cat", "cat", (char *) 0);
  }
  else {
    char buff[100];
    close(fd[0]);
    sprintf(buff, "Inicio\n");
  	write(1,buff,strlen(buff));
    //close(fd[1]);
    waitpid(-1, NULL, 0);
    sprintf(buff, "Fin\n");
  	write(1,buff,strlen(buff));
  }
}
