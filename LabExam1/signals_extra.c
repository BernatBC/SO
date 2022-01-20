#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int pids[];
int n;

void Usage(int a)
{
	char buff[120];
	if (a == 1) sprintf(buff, "Numero d'arguments incorrectes\n");
  if (a == 2) sprintf(buff, "Error en el fork\n");
	if (a == 3) sprintf(buff, "Error en el sigaction\n");
	write(1,buff,strlen(buff));
}

void Alarma() {
	int ret;
	while((ret = waitpid (-1, NULL, 0)) > 0) {
		kill(ret, SIGKILL);
	}
}

void Res() {
}

int main (int argc, char *argv[]){
	if (argc == 1 || argc > 11) {
		Usage(1);
		exit(1);
	}
  char buff[120];
  pids[argc - 1];
	n = argc - 1;
  for (int i = 1; i < argc; ++i)
  {
    int pid = fork();
    if (pid == 0)
    {
			sigset_t mask;

			sigfillset (&mask);
			sigdelset (&mask, SIGUSR1);
			sigprocmask (SIG_BLOCK, &mask, NULL);
			sigemptyset (&mask);
			sigaddset (&mask, SIGUSR1);
			sigsuspend (&mask);

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

	struct sigaction sa;
	sigset_t mask;

	sigfillset (&mask);
	sigdelset (&mask, SIGINT);
	sigdelset (&mask, SIGALRM);
	sigprocmask (SIG_BLOCK, &mask, NULL);

	sa.sa_handler = &Res;
	sa.sa_flags = SA_RESTART;
	sigfillset (&sa.sa_mask);

	if (sigaction (SIGINT, &sa, NULL) < 0) {
		Usage(3);
	  exit(1);
	}

	sa.sa_handler = &Alarma;
	sa.sa_flags = SA_RESTART;
	sigfillset (&sa.sa_mask);

	if (sigaction (SIGALRM, &sa, NULL) < 0) {
		Usage(3);
	  exit(1);
	}
	int tractar = fork();
	if (tractar == 0) {
		for (int i = 1; i < argc; ++i) {
			sigfillset (&mask);
			sigdelset (&mask, SIGINT);
			sigdelset (&mask, SIGALRM);
			alarm(2);
			sigsuspend (&mask);
			alarm(0);
			kill(pids[i - 1], SIGUSR1);
		}
		exit(0);
	}
	else if (tractar < 0) Usage(2);

	int ret;
	while((ret = waitpid (-1, NULL, 0)) > 0){
		if (WIFEXITED(ret)) sprintf(buff, "Pid: %d Per exit Codi: %d\n", ret, WEXITSTATUS(ret));
		else sprintf(buff, "Pid: %d Per signal Codi: %d\n", ret, WEXITSTATUS(ret));
		write(1,buff,strlen(buff));
	}
}
