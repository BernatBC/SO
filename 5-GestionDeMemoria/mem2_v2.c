#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

#define REGION_SIZE		4096

int *p;

void sigsegv_trat() {
  sprintf (buff, "Addresses: %d\n", p);
  write (1, buff, strlen (buff));
}

int
main (int argc, char *argv[])
{
  struct sigaction sa;
  sigset_t mask;

  sigemptyset (&mask);
  sigaddset (&mask, SIGSEGV);
  sigprocmask (SIG_BLOCK, &mask, NULL);

  sa.sa_handler = &sigsegv_trat;
  sa.sa_flags = SA_RESTART;
  sigfillset (&sa.sa_mask);

  sigaction (SIGSEGV, &sa, NULL);

  int i = 0;
  char buff[256];

  sprintf (buff, "Addresses:\n");
  write (1, buff, strlen (buff));
  sprintf (buff, "\tp: %p\n", &p);
  write (1, buff, strlen (buff));

  p = malloc (sizeof (int));

  if (p == NULL)
    {
      sprintf (buff, "ERROR en el malloc\n");
      write (2, buff, strlen (buff));
    }

  while (1)
    {
      *p = i;
      sprintf (buff, "\tProgram code -- p address: %p, p value: %p, *p: %d\n",
               &p, p, *p);
      write (1, buff, strlen (buff));
      p++;
      i++;
    }

}
