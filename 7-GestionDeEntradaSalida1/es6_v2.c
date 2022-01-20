#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

int sig = 0;

void trat_int() {
  char buff[256];
  sprintf (buff, "read interrumput per signal\n");
  write (1, buff, strlen (buff));
  sig = 1;
}

int
main ()
{
  char c;
  struct sigaction sa;
  sigset_t mask;

  sa.sa_handler = &trat_int;
  sa.sa_flags = 0;
  sigfillset (&sa.sa_mask);

  sigaction(SIGINT, &sa, NULL);

  int ret = read (0, &c, sizeof (char));
  if (ret == -1) {
    char buff[256];
    sprintf (buff, "read amb error\n");
    write (1, buff, strlen (buff));
  } else if (!sig) {
    char buff[256];
    sprintf (buff, "read correcte\n");
    write (1, buff, strlen (buff));
  }
  write (1, &c, sizeof (char));
}
