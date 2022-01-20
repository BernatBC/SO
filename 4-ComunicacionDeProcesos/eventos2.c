#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int contador;

void
error_y_exit (char *msg, int exit_status)
{
  perror (msg);
  exit (exit_status);
}

void s1() {
  contador = 0;

  struct sigaction sa;
  sa.sa_handler = SIG_DFL;
  sa.sa_flags = SA_RESETHAND;
  sigfillset (&sa.sa_mask);
  if (sigaction (SIGUSR1, &sa, NULL) < 0)
    error_y_exit ("sigaction", 1);
}

void s2() {
  char buff[256];
  sprintf (buff, "Contador: %d\n", contador);
  write (1, buff, strlen (buff));

  struct sigaction sa;
  sa.sa_handler = SIG_DFL;
  sa.sa_flags = SA_RESETHAND;
  sigfillset (&sa.sa_mask);
  if (sigaction (SIGUSR2, &sa, NULL) < 0)
    error_y_exit ("sigaction", 1);
}

void alarma() {
  ++contador;
}

int
main (int argc, char *argv[])
{
  struct sigaction sa;
  sigset_t mask;
  char buff[256];

  sigemptyset (&mask);
  sigaddset (&mask, SIGALRM);
  sigprocmask (SIG_BLOCK, &mask, NULL);

  sa.sa_handler = &s1;
  sa.sa_flags = SA_RESTART;
  sigfillset (&sa.sa_mask);

  if (sigaction (SIGUSR1, &sa, NULL) < 0)
    error_y_exit ("sigaction", 1);

  sa.sa_handler = &s2;
  if (sigaction (SIGUSR2, &sa, NULL) < 0)
    error_y_exit ("sigaction", 1);

  sa.sa_handler = &alarma;
  if (sigaction (SIGALRM, &sa, NULL) < 0)
    error_y_exit ("sigaction", 1);

  contador = 0;

  sprintf (buff, "Pid: %d\n", getpid());
  write (1, buff, strlen (buff));

  while(1) {
    alarm(1);

    sigfillset (&mask);
    sigdelset (&mask, SIGALRM);
    sigdelset (&mask, SIGUSR1);
    sigdelset (&mask, SIGUSR2);
    sigsuspend (&mask);
  }
}
