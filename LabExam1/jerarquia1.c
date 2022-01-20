#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void Usage(int a)
{
	char buff[120];
	if (a == 1) sprintf(buff, "Numero d'arguments incorrectes\n");
  if (a == 2) sprintf(buff, "Error en el fork\n");
	write(1,buff,strlen(buff));
}

int main (int argc, char *argv[]){
	if (argc == 1 || argc > 11) {
		Usage(1);
		exit(1);
	}
  char buff[120];
  int pids[argc - 1];
  for (int i = 1; i < argc; ++i)
  {
    int pid = fork();
    if (pid == 0)
    {
      sprintf(buff, "%s\n", argv[i]);
      write(1,buff,strlen(buff));
      exit(0);
  	}
    else if (pid < 0)
    {
      Usage(2);
      exit(1);
    }
    pids[i - 1] = pid;
  }
  for (int i = 1; i < argc; ++i) {
    int k;
    waitpid (pids[i - 1], k, 0);
    sprintf(buff, "Pid: %d Codi: %d\n", pids[i - 1], WEXITSTATUS(k));
    write(1,buff,strlen(buff));
  }
}
