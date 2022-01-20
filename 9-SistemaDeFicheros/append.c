#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	char buff[100];
	int p1 = open("file", O_RDONLY);
  int p2 = open("file", O_WRONLY);

  lseek(p1, 0, SEEK_SET);
  int n_chars = lseek(p2, 0, SEEK_END);

  while (n_chars) {
    read(p1, buff, 1);
    write(p2, buff, 1);
    --n_chars;
  }
  close(p1);
  close(p2);
}
