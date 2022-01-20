#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {
  char c;
  int fd;
  fd = open("pipe1", O_RDONLY);
  while (0 < read(fd, &c, 1)) {
    write(1, c, 1);
  }
  close(fd);
}
