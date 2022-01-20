#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

/*
basicament la solució es basa en canviar el stdin dels fills per l'extrem de lectura de la pipe.
El pare anirà escrivint a l'extrem d'escriptura de la pipe el contingut del fitxer.
*/

void Usage(int n)
{
	char buff[120];
	if (n == 0) sprintf(buff, "Nombre d'arguments incorrecte\n");
  else if (n == 1) sprintf(buff, "Error al fork\n");
  else if (n == 2) sprintf(buff, "Error al mutar\n");
	else if (n == 3) sprintf(buff, "Error al crear la pipe\n");
	write(1,buff,strlen(buff));
  exit(0);
}

int main (int argc, char *argv[]){
  if (argc != 2) Usage(0);
  int n = atoi(argv[1]);
  int pids[n];
	int fd[2];
	int r = pipe(fd);
	if (r < 0) Usage(4);
  for (int i = 0; i < n; ++i) {
    int pid = fork();
    if (pid == 0) {
			dup2(fd[0], 1);
			close(fd[1]);
      execlp ("./hijo2", "hijo2", (char *) 0);
      Usage(2);
  	}
    else if (pid < 0) Usage(1);
    pids[i] = pid;
  }
	close(fd[0]);

	char route[100];
	sprintf(route, "./%s\n", argv[2]);

	int f = open(route, O_RDONLY, 700);
	char c;
	char buffer[100];
	while (read(f, c, sizeof(c)) > 0) {
		if (c == '/n') {
			sprintf(buffer, "%s\n", buffer);
			write(fd[1], buffer, strlen(buffer));
			sprintf(buffer, "\n");
		}
		else {
			sprintf(buffer, "%s%c", buffer, c);
		}
	}


  int ret;
  int proc = 0;
  int res;

  while((ret = waitpid (-1, &res, 0)) > 0){
    ++proc;
    if (WIFEXITED(res) != 0 && WEXITSTATUS(res) != 0) {
      char buff[120];
    	sprintf(buff, "pid: %d cause: %d\n", ret, WEXITSTATUS(res));
    	write(1,buff,strlen(buff));
      if (proc == n) {
        sprintf(buff, "Incalculable\n");
      	write(1,buff,strlen(buff));
      }
    }
    else {
      char buff[120];
    	sprintf(buff, "pid: %d\n", ret);
    	write(1,buff,strlen(buff));
      for (int i = 0; i < n; ++i) if (pids[i] != ret) kill(pids[i], SIGKILL);
      break;
    }
  }
}
