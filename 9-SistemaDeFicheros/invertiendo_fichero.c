#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char buff[100];
	int p1 = open(argv[1], O_RDONLY);
	char file[100];
	sprintf(file, "%s.inv", argv[1]);
  int p2 = creat(file, 0777);

  lseek(p2, 0, SEEK_SET);
  int n_chars = lseek(p2, 0, SEEK_END);

  while (n_chars) {
		lseek(p1, -1, SEEK_CUR);
    read(p1, buff, 1);
    write(p2, buff, 1);
    --n_chars;
  }
  close(p1);
  close(p2);
}
