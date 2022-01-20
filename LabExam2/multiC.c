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

int segons;
int pids[1000];
int n;

void trat_alarm() {
	char buff[120];
	++segons;
	sprintf(buff, "%d segons\n", segons);
	write(2,buff,strlen(buff));
	alarm(1);
}

void trat_sigterm() {
	char buff[120];
	sprintf(buff, "SIGTERM\n");
	write(2,buff,strlen(buff));
	for (int i = 0; i < n; ++i) kill(pids[i], SIGKILL);
	exit(0);
}

void Usage(int n)
{
	char buff[120];
	if (n == 0) sprintf(buff, "Nombre d'arguments incorrecte\n");
  else if (n == 1) sprintf(buff, "Error al fork\n");
  else if (n == 2) sprintf(buff, "Error al mutar\n");
	else if (n == 3) sprintf(buff, "Error de sigaction\n");
	write(1,buff,strlen(buff));
  exit(0);
}

int main (int argc, char *argv[]){
	struct sigaction sa;
	sigset_t mask;

	sa.sa_handler = &trat_sigterm;
	sa.sa_flags = SA_RESTART;
	sigfillset (&sa.sa_mask);
	if (sigaction (SIGTERM, &sa, NULL) < 0) Usage(3);

	sa.sa_handler = &trat_alarm;
	if (sigaction (SIGALRM, &sa, NULL) < 0) Usage(3);

	alarm(1);

  if (argc != 3) Usage(0);
  n = atoi(argv[1]);
  for (int i = 0; i < n; ++i) {
    int pid = fork();
    if (pid == 0) {
      execlp ("./hijo1", "hijo1", argv[2], (char *) 0);
      Usage(2);
  	}
    else if (pid < 0) Usage(1);
    pids[i] = pid;
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
