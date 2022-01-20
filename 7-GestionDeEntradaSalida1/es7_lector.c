#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
  int a;
  char buf[1024];
  read(0, &a, sizeof(int));
  sprintf (buf, "%d\n", a);
  write (1, buf, strlen (buf));
  read(0, &a, sizeof(int));
  sprintf (buf, "%d\n", a);
  write (1, buf, strlen (buf));
}
